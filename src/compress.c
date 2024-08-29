// This is a very baby version of LZ4 compression algorithm

#include "compress.h"

#include "savestate.h"
#include "bool.h"
#include "libc/string.h"

#define PACKED __attribute__((packed))
#define __GET_UNALIGNED_T(type, ptr)              \
	({                                            \
		const struct                              \
		{                                         \
			type x;                               \
		} PACKED *__pptr = (typeof(__pptr))(ptr); \
		__pptr->x;                                \
	})

#define __PUT_UNALIGNED_T(type, val, ptr)         \
	do                                            \
	{                                             \
		struct                                    \
		{                                         \
			type x;                               \
		} PACKED *__pptr = (typeof(__pptr))(ptr); \
		__pptr->x = (val);                        \
	} while (0)

#define GET_UNALIGNED4(ptr) __GET_UNALIGNED_T(uint32_t, (ptr))
#define PUT_UNALIGNED4(val, ptr) __PUT_UNALIGNED_T(uint32_t, (val), (ptr))

#define MINMATCH 3

typedef struct
{
	uint32_t match3;
	uint32_t match4;
} MinMatch;

static MinMatch readMinMatch(const uint8_t *buf)
{
	const uint32_t mask = 0xffffff00;
	const uint32_t match4 = GET_UNALIGNED4(buf);
	const uint32_t match3 = match4 & mask;
	return (MinMatch){match3, match4};
}

static uint32_t readMinMatch3(const uint8_t *buf)
{
	const uint32_t mask = 0xffffff00;
	const uint32_t match4 = GET_UNALIGNED4(buf);
	return match4 & mask;
}

#define HASH_CHAINS_BITS 12
#define HASH_CHAINS_SIZE (1 << HASH_CHAINS_BITS)

typedef struct
{
	uint32_t hash3;
	uint32_t hash4;
} MinMatcHash;

static MinMatcHash hashMinMatch(MinMatch match)
{
	return (MinMatcHash){((match.match3 * 506832829U)) >> (32 - HASH_CHAINS_BITS), (match.match4 * 2654435761U) >> (32 - HASH_CHAINS_BITS)};
}

static void wildCopy4(uint8_t *dst, const uint8_t *src, const uint8_t *dstEnd)
{
	do
	{
		PUT_UNALIGNED4(GET_UNALIGNED4(src), dst);
		src += 4;
		dst += 4;
	} while (dst < dstEnd);
}

#define WILD_COPY_MOVE(dst, src, amount) \
	do                                   \
	{                                    \
		uint8_t *start = dst;            \
		dst += (amount);                 \
		wildCopy4(start, src, dst);      \
	} while (0)

static void encodeLargeInt(uint8_t **_out, int leftToEncode)
{
#define out (*_out)
	bool keepEncoding = true;
	while (keepEncoding)
	{
		keepEncoding = leftToEncode >= 255;
		*(out++) = (uint8_t)(keepEncoding ? 255 : leftToEncode);
		leftToEncode -= 255;
	}
#undef out
}

typedef struct
{
	int matchLen;
	const uint8_t *inMatch;
} MinMatchPtr;

static MinMatchPtr tryMinMatch(uint32_t potentialMinMatchOffset, MinMatch minMatch, const uint8_t *inCursor, const uint8_t *inLimit, int inCursorOffset)
{
	const uint8_t *potentialMinMatch = inCursor - inCursorOffset + potentialMinMatchOffset;

	// need to do some fun wraparound stuff
	if (potentialMinMatch > inCursor - 4)
		potentialMinMatch -= 256;

	if (minMatch.match3 == readMinMatch3(potentialMinMatch))
	{
		// find the longest match we have with the potential match
		int matchLen = MINMATCH;
		while (1)
		{
			if (inCursor + matchLen >= inLimit)
				break;
			if (inCursor[matchLen] != potentialMinMatch[matchLen])
				break;

			matchLen++;
		}

		return (MinMatchPtr){matchLen, potentialMinMatch};
	}
	else
	{
		return (MinMatchPtr){0, NULL};
	}
}

uint32_t mlz4_compress(const uint8_t *in, const uint32_t inSize, uint8_t *out)
{
	uint8_t *compressedData = out;

	uint8_t *outCursor = compressedData;
#ifndef TARGET_N64
	uint8_t hashChains3[HASH_CHAINS_SIZE] = {};
	uint8_t hashChains4[HASH_CHAINS_SIZE] = {};
#else
	// placed in gDecompressionHeap
	uint8_t *hashChains3 = Hacktice_gState->memory + MaxStateSize - HASH_CHAINS_SIZE * 2 - 0xf00;
	uint8_t *hashChains4 = hashChains3 + HASH_CHAINS_SIZE;
	bzero(hashChains3, 2 * HASH_CHAINS_SIZE);
#endif

	// should be safe to do
	PUT_UNALIGNED4(inSize, outCursor);
	outCursor += 4;

#if 0
	// uncompressible data, just write it out as literals
	if (inSize <= 8)
	{
		outCursor[0] = ((uint8_t)inSize) << 4;
		outCursor++;
		WILD_COPY_MOVE(outCursor, in, inSize);
		return (uint32_t) (outCursor - compressedData);
	}
#endif

	const uint8_t *inEnd = in + inSize;
	const uint8_t *inCursor = in + 4;
	const uint8_t *inLimit = inEnd - 4;
	const uint8_t *inLiteralStart = in;

	// start the loop
	while (1)
	{
		// push match we took last time
		{
			MinMatch prevMinMatch = readMinMatch(inCursor - 4);
			MinMatcHash hashValue = hashMinMatch(prevMinMatch);
			uint8_t offset = (uint8_t)(inCursor - 4 - in);
			hashChains3[hashValue.hash3] = offset;
			hashChains4[hashValue.hash4] = offset;
		}

		if (inCursor >= inLimit)
		{
			// printf("Final literals: %lld\n", inEnd - inLiteralStart);
			const int literalsCount = inEnd - inLiteralStart;
			if (literalsCount >= 15)
			{
				*(outCursor++) = 0xf0;
				encodeLargeInt(&outCursor, literalsCount - 15);
			}
			else
			{
				*(outCursor++) = ((uint8_t)literalsCount) << 4;
			}

			WILD_COPY_MOVE(outCursor, inLiteralStart, literalsCount);
			return (uint32_t)(outCursor - compressedData);
		}

		MinMatch minMatch = readMinMatch(inCursor);
		MinMatcHash hashValue = hashMinMatch(minMatch);
		uint8_t inCursorOffset = (uint8_t)(inCursor - in);

		uint8_t potentialMinMatchOffset3 = hashChains3[hashValue.hash3];
		uint8_t potentialMinMatchOffset4 = hashChains4[hashValue.hash4];

		MinMatchPtr match3 = tryMinMatch(potentialMinMatchOffset3, minMatch, inCursor, inLimit, inCursorOffset);
		MinMatchPtr match4 = tryMinMatch(potentialMinMatchOffset4, minMatch, inCursor, inLimit, inCursorOffset);

		MinMatchPtr match = match3.matchLen > match4.matchLen ? match3 : match4;
		if (match.matchLen)
		{
			// write the match...
			uint8_t *pnibble = outCursor++;
			const int literalsCount = (int)(inCursor - inLiteralStart);
			if (literalsCount >= 15)
			{
				*pnibble = 0xf0;
				encodeLargeInt(&outCursor, literalsCount - 15);
			}
			else
			{
				*pnibble = ((uint8_t)literalsCount) << 4;
			}

			WILD_COPY_MOVE(outCursor, inLiteralStart, literalsCount);
			*(outCursor++) = (uint8_t)(inCursor - match.inMatch - 4);

			const int matchesCount = match.matchLen - MINMATCH;
			if (matchesCount >= 15)
			{
				*pnibble |= 0x0f;
				encodeLargeInt(&outCursor, matchesCount - 15);
			}
			else
			{
				*pnibble |= (uint8_t)matchesCount;
			}

			// printf("Literals: %lld, Offset: %lld, Match: %d\n", inCursor - inLiteralStart, inCursor - match.inMatch, match.matchLen);
			inCursor += match.matchLen;
			inLiteralStart = inCursor;
		}
		else
		{
			inCursor++;
		}
	}
}

uint32_t mlz4_decompress(const uint8_t *in, uint8_t *out)
{
	const uint8_t *inCursor = in;
	uint32_t originalSize = GET_UNALIGNED4(inCursor);
	inCursor += 4;

	uint8_t *outCursor = out;
	uint8_t *outEnd = out + originalSize;
	uint8_t *outSafetyMargin = outEnd - 4;
	while (1)
	{
		uint8_t nibble = *(inCursor++);
		int literalsCount = nibble >> 4;
		if (literalsCount == 15)
		{
			while (1)
			{
				uint8_t nextNibble = *(inCursor++);
				literalsCount += nextNibble;
				if (nextNibble != 255)
					break;
			}
		}

		if (literalsCount)
		{
			uint8_t *literalsEnd = outCursor + literalsCount;
			if (literalsEnd >= outSafetyMargin)
			{
				// last 4 literals must be in safety margin
				memcpy(outCursor, inCursor, literalsCount);
				outCursor += literalsCount;
				inCursor += literalsCount;
				break;
			}
			else
			{
				wildCopy4(outCursor, inCursor, literalsEnd);
				outCursor = literalsEnd;
				inCursor += literalsCount;
			}
		}

		int offset = 4 + *(inCursor++);
		int matchesCount = nibble & 0x0f;
		if (matchesCount == 15)
		{
			while (1)
			{
				uint8_t nextNibble = *(inCursor++);
				matchesCount += nextNibble;
				if (nextNibble != 255)
					break;
			}
		}
		matchesCount += MINMATCH;

		const uint8_t *matchStart = outCursor - offset;
		WILD_COPY_MOVE(outCursor, matchStart, matchesCount);
	}

	// TODO: this is incredibly ugly, rework this mess
	return inCursor - in;
}

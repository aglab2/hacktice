using System;
using System.Collections.Generic;
using System.Text;

namespace Hacktice
{
    class N64CRC
    {
		static uint ROL(uint i, int b)
		{
			return (((i) << (b)) | ((i) >> (32 - (b))));
		}

		static uint BYTES2LONG(byte[] b, int off)
		{
			return (uint) (((b)[off + 0] << 24 | (b)[off + 1] << 16 | (b)[off + 2] << 8 | (b)[off + 3]));
		}

		const byte N64_HEADER_SIZE = 0x40;
		const uint N64_BC_SIZE = (0x1000 - N64_HEADER_SIZE);

		const byte N64_CRC1 = 0x10;
		const byte N64_CRC2 = 0x14;

		const uint CHECKSUM_START   = 0x00001000;
		const uint CHECKSUM_LENGTH  = 0x00100000;
		const uint CHECKSUM_CIC6102 = 0xF8CA4DDC;
		const uint CHECKSUM_CIC6103 = 0xA3886759;
		const uint CHECKSUM_CIC6105 = 0xDF26F436;
		const uint CHECKSUM_CIC6106 = 0x1FEA617A;

		static void Write32(byte[] b, int off, uint value)
		{
			b[off + 0] = (byte)((value & 0xFF000000) >> 24);
			b[off + 1] = (byte)((value & 0x00FF0000) >> 16);
			b[off + 2] = (byte)((value & 0x0000FF00) >> 8);
			b[off + 3] = (byte)((value & 0x000000FF));
		}

		readonly uint[] crc_table = new uint[256];

		public N64CRC()
		{
			uint crc, poly;
			int i, j;

			poly = 0xEDB88320;
			for (i = 0; i < 256; i++)
			{
				crc = (uint) i;
				for (j = 8; j > 0; j--)
				{
					if ((crc & 1) != 0) 
						crc = (crc >> 1) ^ poly;

					else crc >>= 1;
				}
				crc_table[i] = crc;
			}
		}

		uint crc32(byte[] data, uint off, uint len)
		{
			uint crc = 0xffffffff;
			int i;

			for (i = 0; i < len; i++)
				crc = (crc >> 8) ^ crc_table[(crc ^ data[off + i]) & 0xFF];

			return ~crc;
		}

		uint N64GetCIC(byte[] data)
		{
			switch (crc32(data, N64_HEADER_SIZE, N64_BC_SIZE))
			{
				case 0x6170A4A1: return 6101;
				case 0x90BB6CB5: return 6102;
				case 0x0B050EE0: return 6103;
				case 0x98BC2C86: return 6105;
				case 0xACC8580A: return 6106;
			}

			return 6105;
		}

		void N64CalcCRC(uint[] crc, byte[] data)
		{
			uint bootcode;
			int i;
			uint seed;

			uint t1, t2, t3;
			uint t4, t5, t6;
			uint r, d;


			switch ((bootcode = N64GetCIC(data)))
			{
				case 6101:
				case 6102:
					seed = CHECKSUM_CIC6102;
					break;
				case 6103:
					seed = CHECKSUM_CIC6103;
					break;
				case 6105:
					seed = CHECKSUM_CIC6105;
					break;
				case 6106:
					seed = CHECKSUM_CIC6106;
					break;
				default:
					throw new ArgumentException($"bootcode {bootcode} is invalid");
			}

			t1 = t2 = t3 = t4 = t5 = t6 = seed;

			i = (int) CHECKSUM_START;
			while (i < (CHECKSUM_START + CHECKSUM_LENGTH))
			{
				d = BYTES2LONG(data, i);
				if ((t6 + d) < t6) t4++;
				t6 += d;
				t3 ^= d;
				r = ROL(d, (int) (d & 0x1F));
				t5 += r;
				if (t2 > d) t2 ^= r;
				else t2 ^= t6 ^ d;

				if (bootcode == 6105) t1 += BYTES2LONG(data, N64_HEADER_SIZE + 0x0710 + (i & 0xFF)) ^ d;
				else t1 += t5 ^ d;

				i += 4;
			}
			if (bootcode == 6103)
			{
				crc[0] = (t6 ^ t4) + t3;
				crc[1] = (t5 ^ t2) + t1;
			}
			else if (bootcode == 6106)
			{
				crc[0] = (t6 * t4) + t3;
				crc[1] = (t5 * t2) + t1;
			}
			else
			{
				crc[0] = t6 ^ t4 ^ t3;
				crc[1] = t5 ^ t2 ^ t1;
			}
		}

		public void crc(byte[] buffer)
		{
			var cic = N64GetCIC(buffer);
			uint[] crc = new uint[2];
			N64CalcCRC(crc, buffer);
			Write32(buffer, N64_CRC1, crc[0]);
			Write32(buffer, N64_CRC2, crc[1]);
		}
	}
}

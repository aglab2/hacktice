using System;
using static System.Net.IPAddress;

namespace EndianExtension
{
    public static class Endian
    {
        public static short ToBigEndian(this short value) => HostToNetworkOrder(value);
        public static int ToBigEndian(this int value) => HostToNetworkOrder(value);
        public static long ToBigEndian(this long value) => HostToNetworkOrder(value);
        public static short FromBigEndian(this short value) => NetworkToHostOrder(value);
        public static int FromBigEndian(this int value) => NetworkToHostOrder(value);
        public static long FromBigEndian(this long value) => NetworkToHostOrder(value);

        public static void CopyByteswap(byte[] src, int srcOff, byte[] dst, int dstOff, int amount)
        {
            if (amount % 4 != 0)
                throw new ArgumentException($"Amount {amount} is not divisible by 4");

            for (int i = 0; i < amount; i++)
            {
                int iswap = (4 * (i / 4)) + (3 - (i % 4));
                dst[dstOff + i] = src[srcOff + iswap];
            }
        }
    }
}

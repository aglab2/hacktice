using BigEndianExtension;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Xml;
using static System.Net.IPAddress;

namespace BigEndianExtension
{
    public static class BigEndian
    {
        public static short ToBigEndian(this short value) => HostToNetworkOrder(value);
        public static int ToBigEndian(this int value) => HostToNetworkOrder(value);
        public static long ToBigEndian(this long value) => HostToNetworkOrder(value);
        public static short FromBigEndian(this short value) => NetworkToHostOrder(value);
        public static int FromBigEndian(this int value) => NetworkToHostOrder(value);
        public static long FromBigEndian(this long value) => NetworkToHostOrder(value);
    }
}

namespace Hacktice
{
    internal class Patcher
    {
        readonly byte[] _rom;

        const uint BinaryCheck = 0x00602480;

        public Patcher(byte[] rom)
        {
            _rom = rom;
        }

        static string AppendToFileName(string source, string appendValue)
        {
            return $"{Path.Combine(Path.GetDirectoryName(source), Path.GetFileNameWithoutExtension(source))}{appendValue}{Path.GetExtension(source)}";
        }

        public bool IsBinary()
        {
            // this is pretty terrible check but it works for now
            uint call = BitConverter.ToUInt32(_rom, 8);
            return call == BinaryCheck;
        }

        public void Apply()
        {
            XmlPatches patches = new XmlPatches();
            foreach (var patch in patches)
            {
                // Ignore upgrade hacktice codes
                if (patch.Offset == 0x7f1400 || patch.Offset == 0x7f1500)
                    continue;

                Array.Copy(patch.Data, 0, _rom, patch.Offset, patch.Data.Length);
            }

            Array.Copy(Resource.payload_header, 0, _rom, 0x7f2000, Resource.payload_header.Length);
            Array.Copy(Resource.payload_data, 0, _rom, 0x7f2000 + Resource.payload_header.Length, Resource.payload_data.Length);

            // For backwards compatibility we write in the rom stuff that was overwritten in previous hacktice versions
            _rom[0x57e9c] = 0xad;
            _rom[0x57e9d] = 0xe8;

            _rom[0x57ec0] = 0xa5;
            _rom[0x57ec1] = 0x4d;
        }

        public Version FindHackticeVersion()
        {
            foreach (var location in MemFind.All(_rom, (uint) ((int) Canary.HackticeMagic).ToBigEndian()))
            {
                try
                {
                    var check = BitConverter.ToUInt32(_rom, location + 8);
                    if (check != 0x54494e49)
                        continue;

                    var version = new Version(BitConverter.ToInt32(_rom, location + 4).ToBigEndian());
                    if (version.IsReasonable())
                        return version;
                }
                catch (Exception) { }
            }

            return null;
        }

        void CopyByteswap(byte[] src, int srcOff, byte[] dst, int dstOff, int amount) 
        {
            if (amount % 4 != 0)
                throw new ArgumentException($"Amount {amount} is not divisible by 4");

            for (int i = 0; i < amount; i++)
            {
                int iswap = (4 * (i / 4)) + (3 - (i % 4));
                dst[dstOff + i] = src[srcOff + iswap];
            }
        }

        public void WriteConfig(Config cfg)
        {
            int configLocation = 0;
            int hackticeConfigSize = 0;
            foreach (var location in MemFind.All(_rom, (uint)((int)Canary.ConfigMagic).ToBigEndian()))
            {
                hackticeConfigSize = BitConverter.ToInt32(_rom, location + 4).ToBigEndian();
                if (hackticeConfigSize < 0x10000)
                {
                    configLocation = location;
                    break;
                }
            }

            if (0 == configLocation)
            {
                throw new Exception("Failed to find config location!");
            }

            var size = Marshal.SizeOf(typeof(Config));
            int writeSize = Math.Min(size, hackticeConfigSize);
            if (0 == writeSize)
                throw new Exception("Config size cannot be 0");

            var bytes = new byte[size];
            var ptr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(cfg, ptr, false);
            Marshal.Copy(ptr, bytes, 0, size);
            Marshal.FreeHGlobal(ptr);

            CopyByteswap(bytes, 0, _rom, configLocation + 8, writeSize);
        }

        public void Save(string path)
        {
            N64CRC crcCalculator = new N64CRC();
            crcCalculator.crc(_rom);

            var hackticePath = AppendToFileName(path, ".hacktice");
            File.WriteAllBytes(hackticePath, _rom);
        }
    }
}

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;

namespace Hacktice
{
    internal class Patcher
    {
        readonly byte[] _rom;

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
            return call == 0x00602480;
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

        public void Save(string path)
        {
            N64CRC crcCalculator = new N64CRC();
            crcCalculator.crc(_rom);

            var hackticePath = AppendToFileName(path, ".hacktice");
            File.WriteAllBytes(hackticePath, _rom);
        }
    }
}

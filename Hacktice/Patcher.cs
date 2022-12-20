﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;

namespace Hacktice
{
    internal class Patcher
    {
        readonly string _romPath;

        public Patcher(string path)
        {
            _romPath = path;
        }

        static string AppendToFileName(string source, string appendValue)
        {
            return $"{Path.Combine(Path.GetDirectoryName(source), Path.GetFileNameWithoutExtension(source))}{appendValue}{Path.GetExtension(source)}";
        }

        public void Apply()
        {
            var rom = File.ReadAllBytes(_romPath);
            var hackticePath = AppendToFileName(_romPath, ".hacktice");

            XmlPatches patches = new XmlPatches();
            foreach (var patch in patches)
            {
                // Ignore upgrade hacktice codes
                if (patch.Offset == 0x7f1400 || patch.Offset == 0x7f1500)
                    continue;

                Array.Copy(patch.Data, 0, rom, patch.Offset, patch.Data.Length);
            }

            Array.Copy(Resource.payload_header, 0, rom, 0x7f2000, Resource.payload_header.Length);
            Array.Copy(Resource.payload_data, 0, rom, 0x7f2000 + Resource.payload_header.Length, Resource.payload_data.Length);

            N64CRC crcCalculator = new N64CRC();
            crcCalculator.crc(rom);

            File.WriteAllBytes(hackticePath, rom);
        }
    }
}

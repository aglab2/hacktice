using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;

namespace Hacktice
{
    internal class Patcher
    {
        private readonly string RomPath;

        public Patcher(string path)
        {
            RomPath = path;
        }

        static string AppendToFileName(string source, string appendValue)
        {
            return $"{Path.Combine(Path.GetDirectoryName(source), Path.GetFileNameWithoutExtension(source))}{appendValue}{Path.GetExtension(source)}";
        }

        public void Apply()
        {
            var rom = File.ReadAllBytes(RomPath);
            var hackticePath = AppendToFileName(RomPath, ".hacktice");

            var hookDoc = new XmlDocument();
            hookDoc.LoadXml(Resource.hook);

            var elem = hookDoc.DocumentElement;
            foreach (XmlNode patch in elem)
            {
                var addressNode = patch.SelectSingleNode("address");
                var dataNode = patch.SelectSingleNode("bytes");

                if (addressNode is null || dataNode is null)
                    continue;

                var addressStr = addressNode.InnerText;
                var dataStr = dataNode.InnerText;

                var address = Convert.ToInt32(addressStr, 16);
                var dataSplit = dataStr.Split(',');
                var data = Array.ConvertAll(dataSplit, i => Convert.ToByte(i, 16));

                Array.Copy(data, 0, rom, address, data.Length);
            }

            Array.Copy(Resource.data, 0, rom, 0x7f2000, Resource.data.Length);

            N64CRC crcCalculator = new N64CRC();
            crcCalculator.crc(rom);

            File.WriteAllBytes(hackticePath, rom);
        }
    }
}

using System;
using System.Collections;
using System.Collections.Generic;
using System.Xml;

namespace Hacktice
{
    class Patch
    {
        public int Offset { get; }
        public byte[] Data { get; }

        public Patch(int offset, byte[] data)
        {
            Offset = offset;
            Data = data;
        }
    }

    internal class XmlPatches : IEnumerable<Patch>
    {
        public IEnumerator<Patch> GetEnumerator()
        {
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

                var offset = Convert.ToInt32(addressStr, 16);
                var dataSplit = dataStr.Split(',');
                var data = Array.ConvertAll(dataSplit, i => Convert.ToByte(i, 16));

                yield return new Patch(offset, data);
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}

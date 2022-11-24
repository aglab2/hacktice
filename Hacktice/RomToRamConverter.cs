using System;
using System.Collections.Generic;
using System.Text;

namespace Hacktice
{
    internal class RomToRamConverter
    {
        class Entry
        {
            readonly uint _start;
            readonly uint _length;
            // TODO: This will work for my case but in general it does not cover all possible variants of conversions
            readonly uint _offset;

            public Entry(uint start, uint length, uint to)
            {
                _start = start;
                _length = length;
                _offset = to - start;
            }

            public bool IsIn(uint val)
            {
                return _start <= val && val < _start + _length;
            }

            public uint Convert(uint val)
            {
                return val + _offset;
            }
        }

        static readonly List<Entry> Converters = new List<Entry>{
            new Entry(0x1000  , 0xF4580, 0x80246000), // main
            new Entry(0xF5580 , 0x13490, 0x80378800), // engine
            new Entry(0x7f1200, 0x800000 - 0x7f1200, 0x8005c000 - 0xEE00), // hook
        };

        static public uint Convert(uint romAddr)
        {
            foreach (var conv in Converters)
            {
                if (conv.IsIn(romAddr))
                {
                    return conv.Convert(romAddr);
                }
            }

            throw new ArgumentException($"Unknown romAddr 0x{romAddr:X}");
        }
    }
}

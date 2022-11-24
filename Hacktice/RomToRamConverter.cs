using System;
using System.Collections.Generic;
using System.Text;

namespace Hacktice
{
    internal class RomToRamConverter
    {
        readonly uint _start;
        readonly uint _length;
        // TODO: This will work for my case but in general it does not cover all possible variants of conversions
        readonly uint _offset;

        public RomToRamConverter(uint start, uint length, uint to)
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
}

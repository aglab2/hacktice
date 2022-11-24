using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hacktice
{
    internal class Version : IFormattable
    {
        int major;
        int minor;
        int patch;

        public Version(int combo)
        {
            major = (combo >> 24) & 0xff;
            minor = (combo >> 16) & 0xff;
            patch = combo & 0xffff;
        }

        public string ToString(string format, IFormatProvider formatProvider)
        {
            return $"{major.ToString(format, formatProvider)}.{minor.ToString(format, formatProvider)}.{patch.ToString(format, formatProvider)}";
        }
    }
}

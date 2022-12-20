using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hacktice
{
    internal class Version : IFormattable, IComparable
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

        public Version(int major, int minor, int patch)
        {
            this.major = major;
            this.minor = minor;
            this.patch = patch;
        }

        public int CompareTo(object obj)
        {
            if (obj == null)
                return 1;

            var version = obj as Version;
            if (!(version is object))
            {
                throw new ArgumentException("Object is not a Version");
            }

            {
                var cmp = major.CompareTo(version.major);
                if (cmp != 0)
                    return cmp;
            }
            {
                var cmp = minor.CompareTo(version.minor);
                if (cmp != 0)
                    return cmp;
            }

            return patch.CompareTo(version.patch);
        }

        public static bool operator <(Version v1, Version v2)
        {
            return v1.CompareTo(v2) < 0;
        }

        public static bool operator >(Version v1, Version v2)
        {
            return v1.CompareTo(v2) > 0;
        }

        public static bool operator <=(Version v1, Version v2)
        {
            return v1.CompareTo(v2) <= 0;
        }

        public static bool operator >=(Version v1, Version v2)
        {
            return v1.CompareTo(v2) >= 0;
        }

        public static bool operator ==(Version v1, Version v2)
        {
            return v1.CompareTo(v2) == 0;
        }

        public static bool operator !=(Version v1, Version v2)
        {
            return v1.CompareTo(v2) != 0;
        }

        public string ToString(string format, IFormatProvider formatProvider)
        {
            return $"{major.ToString(format, formatProvider)}.{minor.ToString(format, formatProvider)}.{patch.ToString(format, formatProvider)}";
        }
    }
}

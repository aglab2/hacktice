using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hacktice
{
    internal class Version : IFormattable, IComparable
    {
        public readonly int major;
        public readonly int minor;
        public readonly int patch;

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

        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;

            var version = obj as Version;
            if (!(version is object))
            {
                throw new ArgumentException("Object is not a Version");
            }

            return major.Equals(version.major) && minor.Equals(version.minor) && patch.Equals(version.patch);
        }

        public override int GetHashCode()
        {
            return major.GetHashCode() ^ minor.GetHashCode() ^ patch.GetHashCode();
        }

        public string ToString(string format, IFormatProvider formatProvider)
        {
            return $"{major.ToString(format, formatProvider)}.{minor.ToString(format, formatProvider)}.{patch.ToString(format, formatProvider)}";
        }

        public bool IsReasonable()
        {
            return major < 10 && minor < 100 && patch < 1000;
        }
    }
}

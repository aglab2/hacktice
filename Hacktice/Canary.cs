using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hacktice
{
    internal class Canary
    {
        public const uint BinaryRamMagic = 0x3C1A8032;
        public const uint HackticeMagic = 0x484B5443; // HKTC
        public const uint ConfigMagic = 0x48434647; // HCFG
        public const long OnFrameHookMagic = 0x000000000c0134c0;

        public const uint HackticeStatusInit = 0x494E4954; // INIT
        public const uint HackticeStatusActive = 0x41435456; // ACTV
        public const uint HackticeStatusDisabled = 0x4453424c; // DSBL
        public const uint HackticeStatusUpgrading = 0x55504752; // UPGR
        public const uint HackticeStatusHeartbeat = 0x48524254; // HRBT
    }
}

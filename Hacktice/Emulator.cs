using EndianExtension;
using Hacktice.ProcessExtensions;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms.VisualStyles;

namespace Hacktice
{
    internal class Emulator
    {
        private Process _process;
        private ulong _ramPtrBase = 0;

        private IntPtr _ptrRam;
        private IntPtr _ptrEEPROMName;

        /*
         Hacktice header has 20 bytes in size and consists of
         +0 - Canary.HackticeMagic
         +4 - Encoded version in uint
         +8 - Hacktice state as one of Canary.HackticeStatus*
         +12 - Pointer in N64 RAM to hacktice config
         +16 - Pointer in N64 RAM to hacktice savestate
         */
        const int HackticeHeaderSize = 20;
        private IntPtr? _ptrHackticeHeader;
        private IntPtr? _ptrHackticeStatus;
        private byte[] _hackticeHeader = new byte[HackticeHeaderSize];
        private byte[] _ram; // just a cache

        const int ConfigHeaderSize = 8;
        const int RAMSize = 0x400000;

        private IntPtr _ptrOnFrameHook;

        public int HackticeCanary { get { return BitConverter.ToInt32(_hackticeHeader, 0); } }
        public Version HackticeVersion { get { return new Version(BitConverter.ToInt32(_hackticeHeader, 4)); } }
        public int HackticeStatus { get { return BitConverter.ToInt32(_hackticeHeader, 8); } }

        uint HackticeConfigVPtr { get { return BitConverter.ToUInt32(_hackticeHeader, 12); } }
        uint HackticeSavestateVPtr { get { return BitConverter.ToUInt32(_hackticeHeader, 16); } }

        static readonly string[] s_ProcessNames = {
            "project64", "project64d",
            "mupen64-rerecording",
            "mupen64-pucrash",
            "mupen64_lua",
            "mupen64-wiivc",
            "mupen64-RTZ",
            "mupen64-rerecording-v2-reset",
            "mupen64-rrv8-avisplit",
            "mupen64-rerecording-v2-reset",
            "mupen64",
            "retroarch" };

        private Process FindEmulatorProcess()
        {
            foreach (string name in s_ProcessNames)
            {
                Process process = Process.GetProcessesByName(name).Where(p => !p.HasExited).FirstOrDefault();
                if (process != null)
                    return process;
            }
            return null;
        }

        public enum PrepareResult
        {
            NOT_FOUND,
            ONLY_EMULATOR,
            OK,
        }

        public PrepareResult Prepare()
        {
            PrepareResult result = PrepareResult.NOT_FOUND;
            try
            {
                if (!(_process is object) || _process.HasExited)
                {
                    _process = FindEmulatorProcess();
                }

                if (!(_process is object))
                {
                    return PrepareResult.NOT_FOUND;
                }

                result = PrepareResult.ONLY_EMULATOR;
                List<long> romPtrBaseSuggestions = new List<long>();
                List<long> ramPtrBaseSuggestions = new List<long>();

                var name = _process.ProcessName.ToLower();
                int offset = 0;

                if (name.Contains("project64") || name.Contains("wine-preloader"))
                {
                    DeepPointer[] ramPtrBaseSuggestionsDPtrs = { new DeepPointer("Project64.exe", 0xD6A1C),     //1.6
                        new DeepPointer("RSP 1.7.dll", 0x4C054), new DeepPointer("RSP 1.7.dll", 0x44B5C),        //2.3.2; 2.4 
                    };

                    DeepPointer[] romPtrBaseSuggestionsDPtrs = { new DeepPointer("Project64.exe", 0xD6A2C),     //1.6
                        new DeepPointer("RSP 1.7.dll", 0x4C050), new DeepPointer("RSP 1.7.dll", 0x44B58)        //2.3.2; 2.4
                    };

                    // Time to generate some addesses for magic check
                    foreach (DeepPointer romSuggestionPtr in romPtrBaseSuggestionsDPtrs)
                    {
                        int ptr = -1;
                        try
                        {
                            ptr = romSuggestionPtr.Deref<int>(_process);
                            romPtrBaseSuggestions.Add(ptr);
                        }
                        catch (Exception)
                        {
                            continue;
                        }
                    }

                    foreach (DeepPointer ramSuggestionPtr in ramPtrBaseSuggestionsDPtrs)
                    {
                        int ptr = -1;
                        try
                        {
                            ptr = ramSuggestionPtr.Deref<int>(_process);
                            ramPtrBaseSuggestions.Add(ptr);
                        }
                        catch (Exception)
                        {
                            continue;
                        }
                    }
                }

                if (name.Contains("mupen64"))
                {
                    if (name == "mupen64")
                    {
                        // Current mupen releases
                        {
                            ramPtrBaseSuggestions.Add(0x00505CB0); // 1.0.9
                            ramPtrBaseSuggestions.Add(0x00505D80); // 1.0.9.1
                            ramPtrBaseSuggestions.Add(0x0050B110); // 1.0.10
                        }
                    }
                    else
                    {
                        // Legacy mupen versions
                        Dictionary<string, int> mupenRAMSuggestions = new Dictionary<string, int>
                    {
                        { "mupen64-rerecording", 0x008EBA80 },
                        { "mupen64-pucrash", 0x00912300 },
                        { "mupen64_lua", 0x00888F60 },
                        { "mupen64-wiivc", 0x00901920 },
                        { "mupen64-RTZ", 0x00901920 },
                        { "mupen64-rrv8-avisplit", 0x008ECBB0 },
                        { "mupen64-rerecording-v2-reset", 0x008ECA90 },
                    };
                        ramPtrBaseSuggestions.Add(mupenRAMSuggestions[name]);
                    }

                    offset = 0x20;
                }

                if (name.Contains("retroarch"))
                {
                    ramPtrBaseSuggestions.Add(0x80000000);
                    romPtrBaseSuggestions.Add(0x90000000);
                    offset = 0x40;
                }

                MagicManager mm = new MagicManager(_process, romPtrBaseSuggestions.ToArray(), ramPtrBaseSuggestions.ToArray(), offset);
                _ramPtrBase = mm.ramPtrBase;
                _ptrRam = new IntPtr((long)_ramPtrBase);
                _ptrEEPROMName = new IntPtr((long)mm.romPtrBase + 0x20);
                // only for binary
                _ptrOnFrameHook = new IntPtr((long)(_ramPtrBase + 0x3805D4));
                return PrepareResult.OK;
            }
            catch (Exception)
            { }

            return result;
        }

        private uint ToBigEndianEmuOffset1(uint ramOffset)
        {
            uint lo = ramOffset & 0x00000003;
            uint hi = ramOffset & 0xfffffffc;
            return hi | (3 - lo);
        }

        private uint ToBigEndianEmuOffset2(uint ramOffset)
        {
            uint lo = ramOffset & 0x00000003;
            uint hi = ramOffset & 0xfffffffc;
            return hi | (2 - lo);
        }

        // Writes carefully to emulator considering the endianness
        public void WriteToEmulator(uint romAddr, byte[] data)
        {
            var ramAddr = RomToRamConverter.Convert(romAddr);
            var offset = 0x7fffffff & ramAddr;
            if (data.Length == 1)
            {
                var emuPtr = new IntPtr((long)(_ramPtrBase + ToBigEndianEmuOffset1(offset)));
                _process.WriteBytes(emuPtr, data);
            }
            else if (data.Length == 2)
            {
                if (0 != ramAddr % 2)
                {
                    throw new ArgumentException($"Unsupported write to {ramAddr:X} for length {data.Length}");
                }

                byte[] dataClone = (byte[])data.Clone();
                Array.Reverse(dataClone);

                var emuPtr = new IntPtr((long)(_ramPtrBase + ToBigEndianEmuOffset2(offset)));
                _process.WriteBytes(emuPtr, dataClone);
            }
            else if (0 == (data.Length % 4))
            {
                if (0 != ramAddr % 4)
                {
                    throw new ArgumentException($"Unsupported write to {ramAddr:X} for length {data.Length}");
                }

                var emuPtr = new IntPtr((long)(_ramPtrBase + offset));
                byte[] dataClone = (byte[])data.Clone();
                for (int i = 0; i < dataClone.Length; i += 4)
                {
                    Array.Reverse(dataClone, i, 4);
                }

                _process.WriteBytes(emuPtr, dataClone);
            }
            else
            {
                throw new ArgumentException($"Unsupported write size to {ramAddr:X} for length {data.Length}");
            }
        }

        public bool LooksLikeN64VPtr(uint vptr)
        {
            if (0 == (0x80000000 & vptr))
                return false;

            uint physAddr = vptr & 0x7fffffff;
            return physAddr < 0x800000;
        }

        bool LooksLikeHackticeHeader()
        {
            if (!HackticeVersion.IsReasonable())
                return false;

            if (!LooksLikeN64VPtr(HackticeConfigVPtr))
                return false;

            if (!LooksLikeN64VPtr(HackticeSavestateVPtr))
                return false;

            // not checking for state but it is fine
            return true;
        }

        bool RefreshHackticeHeaderAndCheckIfValid()
        {
            if (!Ok())
                return false;

            _process.FetchBytes(_ptrHackticeHeader.Value, HackticeHeaderSize, _hackticeHeader);
            if (HackticeCanary != Canary.HackticeMagic)
                return false;

            bool ok = LooksLikeHackticeHeader();
            if (ok)
            {
                _ram = null;
            }

            return ok;
        }

        public bool RefreshHacktice()
        {
            if (_ptrHackticeHeader.HasValue)
            {
                // refresh the pointers and check if it is still reasonable
                if (RefreshHackticeHeaderAndCheckIfValid())
                    return true;

                _ptrHackticeHeader = null;
                _ptrHackticeStatus = null;
            }

            if (!(_ram is object))
            {
                _ram = new byte[RAMSize];
            }
            _process.FetchBytes(_ptrRam, RAMSize, _ram);

            foreach (var location in MemFind.All(_ram, Canary.HackticeMagic))
            {
                // attempt all locations and find if any is reasonable
                _ptrHackticeHeader = new IntPtr((long)(_ramPtrBase + (ulong)location));
                _ptrHackticeStatus = new IntPtr((long)(_ramPtrBase + (ulong)location + 8));
                if (RefreshHackticeHeaderAndCheckIfValid())
                    return true;
            }

            // it is over
            return false;
        }

        public bool Ok()
        {
            return !_process.HasExited;
        }

        private static bool LooksLikeConfigHeader(byte[] header)
        {
            uint magic = BitConverter.ToUInt32(header, 0);
            if (magic != Canary.ConfigMagic)
                return false;

            int size = BitConverter.ToInt32(header, 4);
            if (size <= 8 || size > 0x10000)
                return false;

            return true;
        }

        public void Write(Config cfg)
        {
            var configOff = HackticeConfigVPtr & 0x7fffffff;
            var ptrConfigHeader = new IntPtr((long)(_ramPtrBase + configOff));
            var configHeader = _process.ReadBytes(ptrConfigHeader, ConfigHeaderSize);
            if (!LooksLikeConfigHeader(configHeader))
                throw new ArgumentException($"Bad config");

            int hackticeConfigSize = BitConverter.ToInt32(configHeader, 4);
            var size = Marshal.SizeOf(typeof(Config));
            int writeSize = Math.Min(size, hackticeConfigSize);
            if (0 == writeSize)
                throw new ArgumentException($"Config size cannot be 0");

            var bytes = new byte[size];
            var ptr = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(cfg, ptr, false);
            Marshal.Copy(ptr, bytes, 0, size);
            Marshal.FreeHGlobal(ptr);

            var configPtr = new IntPtr((long)(_ramPtrBase + configOff + 8));
            _process.WriteBytes(configPtr, bytes, new UIntPtr((uint) writeSize));
        }

        public Config ReadConfig()
        {
            // We might read more than needed but that is OK as the size is constant
            var readSize = 8 + Marshal.SizeOf(typeof(Config));
            var configOff = HackticeConfigVPtr & 0x7fffffff;
            var ptrConfig = new IntPtr((long)(_ramPtrBase + configOff));
            var configBytes = _process.ReadBytes(ptrConfig, readSize);
            if (!LooksLikeConfigHeader(configBytes))
                throw new ArgumentException($"Bad config");

            var size = Marshal.SizeOf(typeof(Config));
            var ptr = Marshal.AllocHGlobal(size);
            Marshal.Copy(configBytes, ConfigHeaderSize, ptr, size);
            var config = (Config) Marshal.PtrToStructure(ptr, typeof(Config));
            Marshal.FreeHGlobal(ptr);

            int hackticeConfigSize = BitConverter.ToInt32(configBytes, 4);
            if (hackticeConfigSize <= (int) Marshal.OffsetOf<Config>("showCustomText"))
            {
                config.SetCustomText("PRACTICE");
                config._pad0 = 0;
                config.showCollision = 0;
                config.softReset = 0;
                config.showCustomText = 0;
            }

            return config;
        }

        public uint ReadRAMHeader()
        { 
            return _process.ReadValue<uint>(_ptrRam);
        }

        public long OnFrameHook()
        {
            return _process.ReadValue<long>(_ptrOnFrameHook);
        }

        public bool IsDecomp()
        {
            return Canary.BinaryRamMagic != ReadRAMHeader();
        }

        public void WriteHackticeDetours(uint fn, int repeats)
        {
            var fnBytes = BitConverter.GetBytes(fn);
            var bytes = new byte[sizeof(uint) * repeats];
            for (int i = 0; i < repeats; i++)
            {
                Array.Copy(fnBytes, 0, bytes, sizeof(uint) * i, 4);
            }
            _process.WriteBytes(new IntPtr((long)(_ramPtrBase + 0x4e000)), bytes);
        }

        public string EEPROMName()
        {
            try
            {
                var bytes = _process.ReadBytes(_ptrEEPROMName, 20);
                var stringBytes = new byte[20];
                Endian.CopyByteswap(bytes, 0, stringBytes, 0, bytes.Length);
                return Encoding.ASCII.GetString(stringBytes, 0, stringBytes.Length).Trim();
            }
            catch (Exception)
            {
                return "";
            }
        }

        public void FixSapphireTimer()
        {
            // 812E3A66 011B
            // 812E3A4E 00F9
            // 812E3A36 00E5
            _process.WriteBytes(new IntPtr((long)(_ramPtrBase + 0x2E3A64)), new byte[] { 0x1b, 0x01 });
            _process.WriteBytes(new IntPtr((long)(_ramPtrBase + 0x2E3A4C)), new byte[] { 0xf9, 0x00 });
            _process.WriteBytes(new IntPtr((long)(_ramPtrBase + 0x2E3A34)), new byte[] { 0xe5, 0x00 });
        }

        public void WriteStatus(uint status)
        {
            _process.WriteBytes(_ptrHackticeStatus.Value, BitConverter.GetBytes(status));
        }
    }
}

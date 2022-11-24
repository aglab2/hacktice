﻿using Hacktice.ProcessExtensions;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Hacktice
{
    class MagicManager
    {
        const uint ramMagic = 0x3C1A8000;
        const uint ramMagicMask = 0xfffff000;
        const uint romMagic = 0x80371240;

        private Process process;
        public readonly ulong romPtrBase;
        public readonly ulong ramPtrBase;

        [DllImport("kernel32.dll")]
        static extern int VirtualQueryEx(IntPtr hProcess, UIntPtr lpAddress, out MEMORY_BASIC_INFORMATION lpBuffer, uint dwLength);

        [StructLayout(LayoutKind.Sequential)]
        public struct MEMORY_BASIC_INFORMATION
        {
            public IntPtr BaseAddress;
            public IntPtr AllocationBase;
            public uint AllocationProtect;
            public IntPtr RegionSize;
            public uint State;
            public uint Protect;
            public uint Type;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct MEMORY_BASIC_INFORMATION64
        {
            public ulong BaseAddress;
            public ulong AllocationBase;
            public int AllocationProtect;
            public int __alignment1;
            public ulong RegionSize;
            public int State;
            public int Protect;
            public int Type;
            public int __alignment2;
        }

        public enum AllocationProtect : uint
        {
            PAGE_EXECUTE = 0x00000010,
            PAGE_EXECUTE_READ = 0x00000020,
            PAGE_EXECUTE_READWRITE = 0x00000040,
            PAGE_EXECUTE_WRITECOPY = 0x00000080,
            PAGE_NOACCESS = 0x00000001,
            PAGE_READONLY = 0x00000002,
            PAGE_READWRITE = 0x00000004,
            PAGE_WRITECOPY = 0x00000008,
        }

        public MagicManager(Process process, long[] romPtrBaseSuggestions, long[] ramPtrBaseSuggestions, int offset)
        {
            GC.Collect();
            this.process = process;

            bool isRomFound = false;
            bool isRamFound = false;

            foreach (uint romPtrBaseSuggestion in romPtrBaseSuggestions)
            {
                romPtrBase = romPtrBaseSuggestion;
                if (IsRomBaseValid())
                {
                    isRomFound = true;
                    break;
                }
            }

            foreach (uint ramPtrBaseSuggestion in ramPtrBaseSuggestions)
            {
                ramPtrBase = ramPtrBaseSuggestion;
                if (IsRamBaseValid())
                {
                    isRamFound = true;
                    break;
                }
            }

            ulong parallelStart = 0;
            ulong parallelEnd = 0;
            foreach (ProcessModule module in process.Modules)
            {
                if (module.ModuleName.Contains("parallel_n64"))
                {
                    parallelStart = (ulong)module.BaseAddress;
                    parallelEnd = parallelStart + (ulong)module.ModuleMemorySize;
                }
            }

            ulong MaxAddress = process.Is64Bit() ? 0x800000000000U : 0xffffffffU;
            ulong address = 0;
            do
            {
                if (isRomFound && isRamFound)
                    break;

                MEMORY_BASIC_INFORMATION m;
                int result = VirtualQueryEx(process.Handle, new UIntPtr(address), out m, (uint)Marshal.SizeOf(typeof(MEMORY_BASIC_INFORMATION)));
                if (address == (ulong)m.BaseAddress + (ulong)m.RegionSize || result == 0)
                    break;

                AllocationProtect prot = (AllocationProtect)(m.Protect & 0xff);
                if (prot == AllocationProtect.PAGE_EXECUTE_READWRITE
                 || prot == AllocationProtect.PAGE_EXECUTE_WRITECOPY
                 || prot == AllocationProtect.PAGE_READWRITE
                 || prot == AllocationProtect.PAGE_WRITECOPY
                 || prot == AllocationProtect.PAGE_READONLY)
                {
                    uint value;
                    bool readSuccess = process.ReadValue(new IntPtr((long)(address + (ulong)offset)), out value);
                    if (readSuccess)
                    {
                        if (!isRamFound && ((value & ramMagicMask) == ramMagic))
                        {
                            ramPtrBase = address + (ulong)offset;
                            isRamFound = true;
                        }

                        if (!isRomFound && value == romMagic)
                        {
                            romPtrBase = address + (ulong)offset;
                            isRomFound = true;
                        }
                    }

                    // scan only large regions - we want to find g_rdram
                    ulong regionSize = (ulong)m.RegionSize;
                    if (parallelStart <= address && address <= parallelEnd && regionSize >= 0x800000)
                    {
                        // g_rdram is aligned to 0x1000
                        ulong maxCnt = (ulong)m.RegionSize / 0x1000;
                        for (ulong num = 0; num < maxCnt; num++)
                        {
                            readSuccess = process.ReadValue(new IntPtr((long)(address + num * 0x1000)), out value);
                            if (readSuccess)
                            {
                                if (!isRamFound && ((value & ramMagicMask) == ramMagic))
                                {
                                    ramPtrBase = address + num * 0x1000;
                                    isRamFound = true;
                                }
                            }

                            if (isRamFound)
                                break;
                        }
                    }
                }

                address = (ulong)m.BaseAddress + (ulong)m.RegionSize;
            }
            while (address <= MaxAddress);

            if (!isRomFound || !isRamFound)
                throw new ArgumentException("Failed to find rom and ram!");
        }

        bool IsRamBaseValid()
        {
            uint value = 0;
            bool readSuccess = process.ReadValue(new IntPtr((long)ramPtrBase), out value);
            return readSuccess && ((value & ramMagicMask) == ramMagic);
        }

        bool IsRomBaseValid()
        {
            uint value = 0;
            bool readSuccess = process.ReadValue(new IntPtr((long)romPtrBase), out value);
            return readSuccess && (value == romMagic);
        }

        public bool isValid()
        {
            return IsRamBaseValid() && IsRomBaseValid();
        }
    }
}

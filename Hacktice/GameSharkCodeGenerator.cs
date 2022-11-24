using System;
using System.Collections.Generic;
using System.Text;

namespace Hacktice
{
    internal class GameSharkCodeGenerator
    {
        static readonly List<RomToRamConverter> Converters = new List<RomToRamConverter>{
            new RomToRamConverter(0x1000  , 0xF4580, 0x80246000), // main
            new RomToRamConverter(0xF5580 , 0x13490, 0x80378800), // engine
            new RomToRamConverter(0x7f1200, 0x800000 - 0x7f1200, 0x8005c000 - 0xEE00), // hook
        };

        const string HackticeCheckVerifier = "D104E012 4753\n";
        const string HackticeWriteVerifier = "8104E012 4753\n";

        StringBuilder codeBuilder = new StringBuilder();
        public GameSharkCodeGenerator()
        {
        }

        public string Create()
        {
            codeBuilder.Append(HackticeWriteVerifier);
            return codeBuilder.ToString();
        }

        private uint ToRamAddr(uint romAddr)
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

        public void Add(uint romAddr, byte[] patch, int off, int size, bool isConst)
        {
            uint ramAddr = ToRamAddr(romAddr);
            while (0 != size)
            {
                if (!isConst)
                {
                    codeBuilder.Append(HackticeCheckVerifier);
                }

                if (1 == size)
                {
                    string code = $"{ramAddr:X} 00{patch[off]:X2}\n";
                    codeBuilder.Append(code);
                    size--;
                    off++;
                    ramAddr++;
                }
                else
                {
                    string code = $"{ramAddr | 0x1000000:X} {patch[off]:X2}{patch[off + 1]:X2}\n";
                    codeBuilder.Append(code);
                    size -= 2;
                    off += 2;
                    ramAddr += 2;
                }
            }
        }
    }
}

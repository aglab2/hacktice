using System;
using System.Collections.Generic;
using System.Text;

namespace Hacktice
{
    internal class GameSharkCodeGenerator
    {
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

        public void Add(uint romAddr, byte[] patch, int off, int size, bool isConst)
        {
            uint ramAddr = RomToRamConverter.Convert(romAddr);
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

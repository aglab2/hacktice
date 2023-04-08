using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hacktice
{
    internal class MemFind
    {
        public static unsafe List<int> All(byte[] arrayToSearchThrough, uint val)
        {
            var list = new List<int>();
            if (arrayToSearchThrough.Length < 4)
                return list;

            fixed (byte* bptr = arrayToSearchThrough)
            {
                uint* ptr = (uint*)bptr;
                int uintCount = arrayToSearchThrough.Length / 4 - 1;
                for (int i = 0; i < uintCount; i++)
                {
                    if (ptr[i] == val)
                        list.Add(i * 4);
                }
            }

            return list;
        }
    }
}

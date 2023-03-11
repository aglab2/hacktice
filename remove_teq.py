import sys

header_size = int(sys.argv[1])
path_from = sys.argv[2]
path_to = sys.argv[3]

passthru = False
amount_of_zeros = 0
offset = 0

with open(path_from, "rb") as f_from, open(path_to, "wb") as f_to:
    while buf := f_from.read(4):
        val = int.from_bytes(buf, byteorder='big')
        if header_size:
            header_size -= 4
        elif not passthru:
            if val == 0:
                amount_of_zeros += 1
            else:
                amount_of_zeros = 0
            
            if amount_of_zeros > 4:
                print(f'0x{offset:X}: passthrough enabled')
                passthru = True
        
            mask = 0b11111100000000000000000000111111
            teq = 0b00000000000000000000000000110100
            if val & mask == teq:
                print(f'0x{offset:X}: teq {val:08X} patched')
                val = 0

        offset += 4
        f_to.write(val.to_bytes(4, byteorder='big'))

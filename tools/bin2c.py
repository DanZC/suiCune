import sys 

if len(sys.argv) < 4:
    print('Usage: bin2c.py <file> <out> <name>')

with open(sys.argv[1], 'rb') as f:
    data = f.read()

with open(sys.argv[2], 'w') as f:
    f.write('#pragma once\n')
    f.write('inline const uint8_t {}[] = {{\n    '.format(sys.argv[3]))
    for i, byte in enumerate(data):
        f.write('0x{:02X},'.format(byte))
        if i & 0x1f == 0x1f:
            f.write('\n    ')
    f.write('\n};\n')


import zipfile
import hashlib
import os.path
from dataclasses import dataclass
from typing import List
import glob

CRYSTAL_UE_10_SHA1 = 'f4cd194bdee0d04ca4eac29e09b8e4e9d818c133'
CRYSTAL_UE_11_SHA1 = 'f2f52230b536214ef7c9924f483392993e226cfb'
CRYSTAL_A_SHA1 = 'a0fc810f1d4e124434f7be2c989ab5b5892ddf36'

listing = [
    ('audio', ['bin']),
    ('data/items', ['json']),
    ('data/pokemon', ['json']),
    ('data/tilesets', ['bin']),
    ('data/wild', ['json']),
    ('gfx/**', ['png', 'pal', 'tilemap', 'attrmap', 'bin', 'rle']),
    ('maps', ['blk'])
]

print('Finding files...', end='')

files_list = []
for lt in listing:
    for ext in lt[1]:
        files_list.extend(glob.glob(f'{lt[0]}/*.{ext}', recursive=True))

files_list.sort()

print('done.')

base_files = files_list

@dataclass
class AFile:
    path: str
    offset: int
    size: int

@dataclass
class Extractor:
    name: str
    hash: str
    longname: str
    files: List[AFile]

extractors: List[Extractor] = [
    Extractor("crystal_ue_10", CRYSTAL_UE_10_SHA1, "Pokemon - Crystal Version (UE) (V1.0) [C][!]", []),
    Extractor("crystal_ue_11", CRYSTAL_UE_11_SHA1, "Pokemon - Crystal Version (UE) (V1.1) [C][!]", []),
    Extractor("crystal_a", CRYSTAL_A_SHA1, "Pokemon - Crystal Version (A) [C][!]", []),
]

if not os.path.exists('./base_assets.zip'):
    print('Copying base files to archive...', end='')

    with zipfile.ZipFile(f"./base_assets.zip", 'w', compression=zipfile.ZIP_DEFLATED) as z:
        for file in base_files:
            z.write(file, f'./{file}')

    print('Done.')
else:
    print('Base assets already extracted.')

exit(0)

try:
    with open('./baserom.gbc', 'rb') as f:
        rom = f.read()
except FileNotFoundError:
    print('Could not find ROM file in working directory. Did you copy it and name it "baserom.gbc"?')
    exit(-1)

rom_hash = hashlib.sha1(rom).hexdigest()

print('ROM SHA1: ', rom_hash)

for e in extractors:
    if e.hash == rom_hash:
        print(f'{e.longname} detected.')
        with zipfile.ZipFile(f"./{e.name}.zip", 'w') as z:
            print('Extracting ROM data to archive...', end='')
            z.writestr('hash.sha1', rom_hash)
            for file in e.files:
                z.writestr(file.path, rom[file.offset:file.offset+file.size])
        print('Done.')
        exit(0)

print('ROM file found, but did not have a matching hash. Either the ROM file is corrupted or the version is unsupported at this time.')
exit(-1)
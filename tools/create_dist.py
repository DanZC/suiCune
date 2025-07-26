import os
import os.path
import shutil
import zipfile
import os.path
import glob

if not os.path.exists('./dist'):
    print("Creating directory 'dist'")
    os.mkdir('./dist')

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

    def copy_file_if_not_exists(path):
        if not os.path.exists(f"./dist/{path}"):
            shutil.copy(f"./{path}", f"./dist/{path}")
            print(f"Copied '{path}'.")
        else:
            print(f"'{path}' already exists.")

    if not os.path.exists('./dist/base_assets.zip'):
        print('Copying base files to archive...', end='')

        with zipfile.ZipFile(f"./dist/base_assets.zip", 'w', compression=zipfile.ZIP_DEFLATED) as z:
            for file in base_files:
                z.write(file, f'./{file}')

        print('Done.')
    else:
        print('Base assets already extracted.')

    if os.path.exists("./suiCune"):
        copy_file_if_not_exists("suiCune")
    if os.path.exists("./suiCune.exe"):
        copy_file_if_not_exists("suiCune.exe")
    
    copy_file_if_not_exists("icon.png")

    if not os.path.exists('./dist/server.json'):
        with open('./dist/server.json', 'w') as f:
            f.write("""{
        "hostname": "",
        "use_ssl": false,
        "login_name": "",
        "email_id": "",
        "pop_host": "",
        "mail_host": "",
        "login_pass": "",
        "use_relay": false,
        "relay_host": "",
        "relay_port": 0
    }
    """)
else:
    print("'dist' already exists. To regenerate it, delete or rename the existing 'dist' folder.")

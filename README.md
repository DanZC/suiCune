# suiCune

This is an attempt at a PC port of Pokemon Crystal. It currently runs, but is not recommended to be used for any projects until completed. Additionally, it may be prone to crashes/buggy behavior. The maintainer is not to be held liable for any mishaps.

The goal is to get assets to load from outside files, and to be able to rewrite parts of the game in C. The game currently relies on a base rom (Not provided). Eventually, this requirement should be phased out. A good example to look at is audio/engine.c


**Overview**

The project starts off with a modified version of pokecrystal, with no reliance on some GameBoy specific features, like interrupts. The game is emulated, and parts of the ASM are converted to C macros. As these are converted, they are set up to re-direct the emulation code, to these macros. Since this is technically C, the workflow works as follows:
- Convert an ASM script to C macros
- Check that it works, make adjustments if needed
- After it's working, it's technically C, so the functions should be able to be re-written in actual C, and recompiled for testing


**Setup**

Copy a rom of pokemon crystal US to the root directory, and name it "baserom.gbc"
in the root folder, run

    make clean && make

Then run suiCune to launch

***For Visual Studio***

- Download the latest SDL2 VC devel libraries
- Extract SDL2 into `deps/` and rename the `SDL2-{version}` to just `SDL2`
	- `deps/SDL2/`
- Run `generate.bat` for Visual Studio 2022
	- Edit `generate.bat` `vs2022` line to whatever you want
	- All platforms and IDEs available [here](https://premake.github.io/docs/Using-Premake/)
- Open the solution in the newly created `build` folder
- Build
- ???
- Profit


**Process (Beginning)**

Converting begins with running convASM.py (with python 3) with an ASM file (run from the root directory)

    ./tools/convASM.py home/init.asm

The above will attempt to convert init.asm, and create home/init.c and home/init.h

The output will also list any lines that it may have not known how to convert

The redirects should automatically be copied into functions.h

Additionally, the .h file should be included (In this case, it is in home.h, which is included in main.h)

After linking a converted ASM script, try building and running. If everything runs correctly, awesome! Otherwise some constants, macros, etc may need to be converted by hand

Occasionally, a modification to convASM.py may need to be made to handle future conversions


**Process (Finalizing/Converting a function)**

After a function is converted, it can be rewritten. Keep in mind that if a function is not set to "REDIRECTED" or "CONVERTED" in functions.h, it will not be called, except for explicit calls to the function (see audio/engine.c). In some cases, the "REDIRECTED" or "CONVERTED" macro should be removed in case the function is rewritten to take parameters, or return values (again see audio/engine.c). Currently there should not be any functional difference between "REDIRECTED" and "CONVERTED" in functions.h. This was a left over from the old emulation method in the Silver port, but the two can still be used to denote which functions have been rewritten, that still might have calls from code that's not converted.


**Things to note**

- The emulator will run a frame of the game, until address 0x0018 is hit (considered the game's main loop/vblank)
- When looking to fetch an opcode, the game will check for redirects, if one is found on the current address, it will jump to that script instead
- Any return from this script will jump back to emulation, until a new redirect is found
- Any data reads are initially read from ROM (But should be factored out to not need reliance to ROM when being re-written in actual C)
- Functions are prefixed automatically with convASM.py as follows:
    - Func - The original C function
    - mFunc - The address of the function if it were currently loaded in ROM (0x0000 - 0x7FFF) (Not really used much)
    - bFunc - The bank of the function in ROM
    - aFunc - The absolute address of the function in the ROM
- When first converted, if the original asm file had any includes, they will be commented out in the C file, and copied to the header file (also commented out). These will need to be manually uncommented (and the path corrected)


**Troubleshooting**

- If a crash occurs, try enabling the "PEEK("EMU")" line in tools/emu/peanut-gb.c. This should print all opcodes ran by the emulator, to give a better scope of where the issue may be
- Common causes for crashes are things that wait for a register, like LY. These should usually be patched out (Since VRAM doesn't need to be in a certain state to be written/read, unlike real hardware
- To keep compatibility with a vanilla baserom, these can be patched (usually the relative jump turned to nops) in tools/emu/rom_patches.h, otherwise rewriting the offending section in C should take it into account


**Misc**

- Due to the removal of reliance on interrupts, the following have been diabled and should be re-implemented once in C:
    - Some delays that would wait for scanlines
        - This includes a lot of things, especially noticable in battles (like battle animations, and waiting for SFX/fanfares to finish)
    - Probably some more things I missed


**Closing**

- This project is for educational purposes, and should not be used for any commercial or profitable causes


## See also

Other disassembly projects:

- [**Pokémon Red/Blue**][pokered]
- [**Pokémon Yellow**][pokeyellow]
- [**Pokémon Crystal**][pokecrystal]
- [**Pokémon Pinball**][pokepinball]
- [**Pokémon TCG**][poketcg]
- [**Pokémon Ruby**][pokeruby]
- [**Pokémon FireRed**][pokefirered]
- [**Pokémon Emerald**][pokeemerald]

[pokered]: https://github.com/pret/pokered
[pokeyellow]: https://github.com/pret/pokeyellow
[pokecrystal]: https://github.com/pret/pokecrystal
[pokepinball]: https://github.com/pret/pokepinball
[poketcg]: https://github.com/pret/poketcg
[pokeruby]: https://github.com/pret/pokeruby
[pokefirered]: https://github.com/pret/pokefirered
[pokeemerald]: https://github.com/pret/pokeemerald
[discord]: https://discord.gg/d5dubZ3
[irc]: https://web.libera.chat/?#pret
[ci]: https://github.com/pret/pokecrystal/actions
[ci-badge]: https://github.com/pret/pokecrystal/actions/workflows/main.yml/badge.svg

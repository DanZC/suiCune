# suiCune

suiCune is an in development PC port of Pokemon Crystal. The game's code is rewritten in C99 and uses SDL2 to emulate the graphics and sound of the Gameboy Color. It currently runs, but is not recommended to be used for any projects until completed. Additionally, it may be prone to crashes/buggy behavior. The maintainer is not to be held liable for any mishaps.

The project restores the networking features present in the original Japanese release of Pokemon Crystal. These features relied on the Japanese-exclusive [Mobile Adapter GB](https://bulbapedia.bulbagarden.net/wiki/Mobile_Game_Boy_Adapter), which allowed the GameBoy Color to connect to the internet via a cellphone. The adapter is emulated using [libmobile](https://github.com/REONTeam/libmobile) and the game utilizes custom servers to recreate the original features. For more information on how to set up the game to use a custom server, see [here](./SERVER.md)


## Overview

The project started off with a modified version of pokecrystal, with no reliance on some GameBoy specific features, like interrupts. The game was emulated, and parts of the ASM were converted to C macros. As these were converted, they were set up to re-direct the emulation code, to these macros. Since this is technically C, the workflow works as follows:
- Convert an ASM script to C macros
- Check that it works, make adjustments if needed
- After it's working, it's technically C, so the functions should be able to be re-written in actual C, and recompiled for testing


## Setup

Clone the repository using

    git clone --recursive https://github.com/DanZC/suiCune.git

If you already have the repository cloned, but are missing the libmobile library, run

    git pull
    git submodule init
    git submodule update

### MSYS2

Install gcc, make, SDL2-devel, SDL2_net-devel, and PhysFS using pacman. The UCRT repositories are recommended.

Then run

    make clean; make RELEASE=1

Then run suiCune to launch

### Linux

Install gcc, make, SDL2-devel, SDL2_net-devel, and PhysFS using your distro's package manager.

Then run

    make clean && make RELEASE=1

Then run suiCune to launch

### Visual Studio

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


### Build options

#### make

| Option | Notes
|--------|--------
| `RELEASE=1` | Release mode with debug features disabled.
| `FASTBG=1`  | Removes extra frame delays on render, increasing the framerate.
| `BUGFIX=1`  | Enables bugfixes for suiCune (see util/bugfix.h).
| `USE_PCG=1` | Uses the PCG rng instead of the default Crystal one.

## Save compatibility

- Efforts have been made to make the game saves backwards compatible with saves from the original english version of the game. Just copy the save over to the folder and rename it to "baserom.sav". However, there are some things to note:
    - The time of day may be wrong. You can reset the time using the in-game clock reset function.
    - Some maps from the original game have changed. If you saved in the Goldenrod center or Goldenrod City, you may be stuck in a wall and have incorrectly loaded NPCs. Save elsewhere and recopy the file.
    - Saves made with suiCune may not work when loaded back in the original game. Due to how the game stores script pointers, NPCs will not have their scripts properly loaded. If you reload the area, it should fix itself. Also, the time of day may be wrong and may need to be reset.


## Closing

- This project is for educational purposes, and should not be used for any commercial or profitable causes
- Follow development of this port on **[Discord](https://discord.gg/29ay2SFRHm)**


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

# Modified from peanut-gb SDL example
NAME		:= suiCune

# Default compiler options for GCC and Clang
CC	:= cc
OBJEXT	:= o
RM	:= rm -f
EXEOUT	:= -o
EXTRA_CFLAGS := -std=c99 -Wall -Wextra -Werror -Wno-unused-label -Og -g3
EXE	:= $(NAME)

# File extension ".exe" is automatically appended on MinGW and MSVC builds, even
# if we don't ask for it.
ifeq ($(OS),Windows_NT)
	STATIC := yes
	EXE := $(NAME).exe
endif

TARGET := $(NAME)
SRCS   := tools/emu/peanut_sdl.c tools/emu/minigb_apu/minigb_apu.c \
	$(wildcard home/*.c) \
	$(wildcard audio/*.c) \
	$(wildcard data/*.c) \
	$(wildcard data/battle/*.c) \
	$(wildcard data/battle/ai/*.c) \
	$(wildcard data/battle_anims/*.c) \
	$(wildcard data/collision/*.c) \
	$(wildcard data/decorations/*.c) \
	$(wildcard data/events/*.c) \
	$(wildcard data/items/*.c) \
	$(wildcard data/maps/*.c) \
	$(wildcard data/moves/*.c) \
	$(wildcard data/phone/*.c) \
	$(wildcard data/phone/text/*.c) \
	$(wildcard data/pokemon/*.c) \
	$(wildcard data/radio/*.c) \
	$(wildcard data/sprite_anims/*.c) \
	$(wildcard data/sprites/*.c) \
	$(wildcard data/text/*.c) \
	$(wildcard data/trainers/*.c) \
	$(wildcard data/types/*.c) \
	$(wildcard data/wild/*.c) \
	$(wildcard engine/battle/*.c) \
	$(wildcard engine/battle/ai/*.c) \
	$(wildcard engine/battle/move_effects/*.c) \
	$(wildcard engine/battle_anims/*.c) \
	$(wildcard engine/events/*.c) \
	$(wildcard engine/gfx/*.c) \
	$(wildcard engine/items/*.c) \
	$(wildcard engine/link/*.c) \
	$(wildcard engine/math/*.c) \
	$(wildcard engine/menus/*.c) \
	$(wildcard engine/movie/*.c) \
	$(wildcard engine/overworld/*.c) \
	$(wildcard engine/phone/*.c) \
	$(wildcard engine/phone/scripts/*.c) \
	$(wildcard engine/pokedex/*.c) \
	$(wildcard engine/pokegear/*.c) \
	$(wildcard engine/pokemon/*.c) \
	$(wildcard engine/rtc/*.c) \
	$(wildcard engine/tilesets/*.c) \
	$(wildcard engine/*.c) \
	$(wildcard gfx/*.c) \
	$(wildcard gfx/sgb/*.c) \
	$(wildcard input_system/*.c) \
	$(wildcard maps/*.c) \
	$(wildcard mobile/*.c) \
	$(wildcard util/*.c) \
	functions.c hram.c vram.c wram.c
#	$(wildcard ../*/*/*/*.c)
CFLAGS += $(shell sdl2-config --cflags)

ifeq ($(STATIC),yes)
	CFLAGS += -static
	LDLIBS += -lSDL2_net -lmingw32 -lSDL2main -lSDL2 -lws2_32 -liphlpapi -ldinput8 -lshell32 -lsetupapi -ladvapi32 -luuid -lversion -loleaut32 -lole32 -limm32 -lwinmm -lgdi32 -luser32 -lm -lphysfs -Wl,--no-undefined 
#	LDLIBS += $(shell sdl2-config --static-libs)
else
	LDLIBS += -lSDL2main -lmingw32 -lSDL2 -mconsole -ldinput8 -lshell32 -lsetupapi -ladvapi32 -luuid -lversion -loleaut32 -lole32 -limm32 -lwinmm -lgdi32 -luser32 -lm -lphysfs -Wl,--no-undefined 
#	LDLIBS += $(shell sdl2-config --libs)
endif

LDLIBS += -lm

CFLAGS += $(EXTRA_CFLAGS)

OBJS := $(SRCS:.c=.$(OBJEXT))

all: $(TARGET)
$(TARGET): $(OBJS) icon.o
	$(CC) $(CFLAGS) $(EXEOUT)$@ $^ $(LDFLAGS) $(LDLIBS) 

%.obj: %.c
	$(CC) $(CFLAGS) $^

# %.res: %.rc
# 	rc /nologo /DCOMPANY="$(COMPANY)" /DDESCRIPTION="$(DESCRIPTION)" \
# 		/DLICENSE="$(LICENSE)" /DGIT_VER="$(GIT_VER)" \
# 		/DNAME="$(NAME)" /DICON_FILE="$(ICON_FILE)" $^
%.o: %.rc
	windres -i $^ -o $@

clean:
	$(RM) $(SRCS:.c=.$(OBJEXT)) $(TARGET) icon.o \
	$(wildcard home/*.o) \
	$(wildcard audio/*.o) \
	$(wildcard data/*.o) \
	$(wildcard data/battle/*.o) \
	$(wildcard data/battle/ai/*.o) \
	$(wildcard data/battle_anims/*.o) \
	$(wildcard data/collision/*.o) \
	$(wildcard data/decorations/*.o) \
	$(wildcard data/events/*.o) \
	$(wildcard data/items/*.o) \
	$(wildcard data/maps/*.o) \
	$(wildcard data/moves/*.o) \
	$(wildcard data/phone/*.o) \
	$(wildcard data/phone/text/*.o) \
	$(wildcard data/pokemon/*.o) \
	$(wildcard data/radio/*.o) \
	$(wildcard data/sprite_anims/*.o) \
	$(wildcard data/sprites/*.o) \
	$(wildcard data/text/*.o) \
	$(wildcard data/trainers/*.o) \
	$(wildcard data/types/*.o) \
	$(wildcard data/wild/*.o) \
	$(wildcard engine/battle/*.o) \
	$(wildcard engine/battle/ai/*.o) \
	$(wildcard engine/battle/move_effects/*.o) \
	$(wildcard engine/battle_anims/*.o) \
	$(wildcard engine/events/*.o) \
	$(wildcard engine/gfx/*.o) \
	$(wildcard engine/items/*.o) \
	$(wildcard engine/link/*.o) \
	$(wildcard engine/math/*.o) \
	$(wildcard engine/menus/*.o) \
	$(wildcard engine/movie/*.o) \
	$(wildcard engine/overworld/*.o) \
	$(wildcard engine/phone/*.o) \
	$(wildcard engine/phone/scripts/*.o) \
	$(wildcard engine/pokedex/*.o) \
	$(wildcard engine/pokegear/*.o) \
	$(wildcard engine/pokemon/*.o) \
	$(wildcard engine/rtc/*.o) \
	$(wildcard engine/tilesets/*.o) \
	$(wildcard engine/*.o) \
	$(wildcard gfx/*.o) \
	$(wildcard gfx/sgb/*.o) \
	$(wildcard input_system/*.o) \
	$(wildcard maps/*.o) \
	$(wildcard mobile/*.o) \
	$(wildcard util/*.o)
#	$(wildcard ../*/*/*/*.o)

# rom.o: pokecrystal/pokecrystal.gbc
# 	$(MAKE) -C pokecrystal
# 	python tools/bin2c.py $^ $@ pokecrystal
# 	$(CC) $(CFLAGS) $(EXEOUT)$@ $^ $(LDFLAGS) $(LDLIBS) 
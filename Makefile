# Modified from peanut-gb SDL example
NAME		:= suiCune

# Default compiler options for GCC and Clang
CC	:= cc
OBJEXT	:= o
RM	:= rm -f
EXEOUT	:= -o
EXTRA_CFLAGS := -Wall -Wextra -Werror -Wno-unused-label
EXE	:= $(NAME)

ifeq ($(RELEASE), 1)
	EXTRA_CFLAGS += -O2
else
	EXTRA_CFLAGS += -Og -g -DDEBUG=1
endif

ifeq ($(BUGFIX), 1)
	EXTRA_CFLAGS += -DBUGFIX=1
endif

ifeq ($(FASTBG), 1)
	EXTRA_CFLAGS += -DENHANCEMENT_DRAW_BG_IN_ONE_FRAME=1
endif

ifeq ($(USE_PCG), 1)
	EXTRA_CFLAGS += -DENHANCEMENT_USE_PCG=1
endif

ifeq ($(USE_PHYSFS), 1)
	EXTRA_CFLAGS += -DUSE_PHYSFS=1
endif

# File extension ".exe" is automatically appended on MinGW and MSVC builds, even
# if we don't ask for it.
ifeq ($(OS),Windows_NT)
	STATIC := yes
	EXE := $(NAME).exe
	EXTRA_CFLAGS += -std=c99
else
	EXTRA_CFLAGS += -std=gnu99
endif

TARGET := $(NAME)
SRCS   := tools/emu/peanut_sdl.c tools/emu/minigb_apu/minigb_apu.c \
	$(wildcard home/*.c) \
	$(wildcard audio/*.c) \
	$(wildcard data/*.c) \
	$(wildcard data/battle/*.c) \
	$(wildcard data/battle/ai/*.c) \
	$(wildcard data/battle_anims/*.c) \
	$(wildcard data/battle_tower/*.c) \
	$(wildcard data/collision/*.c) \
	$(wildcard data/decorations/*.c) \
	$(wildcard data/events/*.c) \
	$(wildcard data/items/*.c) \
	$(wildcard data/maps/*.c) \
	$(wildcard data/mobile/*.c) \
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
	$(wildcard engine/battle_anims/*.c) \
	$(wildcard engine/events/*.c) \
	$(wildcard engine/events/battle_tower/*.c) \
	$(wildcard engine/events/bug_contest/*.c) \
	$(wildcard engine/events/pokerus/*.c) \
	$(wildcard engine/games/*.c) \
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
	$(wildcard engine/printer/*.c) \
	$(wildcard engine/rtc/*.c) \
	$(wildcard engine/tilesets/*.c) \
	$(wildcard engine/*.c) \
	$(wildcard gfx/*.c) \
	$(wildcard gfx/pokemon/*.c) \
	$(wildcard gfx/sgb/*.c) \
	$(wildcard input_system/*.c) \
	$(wildcard lib/mobile/*.c) \
	$(wildcard maps/*.c) \
	$(wildcard mobile/*.c) \
	$(wildcard util/*.c) \
	functions.c hram.c vram.c wram.c
#	$(wildcard ../*/*/*/*.c)
CFLAGS += $(shell sdl2-config --cflags)

ifeq ($(OS),Windows_NT)
ifeq ($(STATIC),yes)
	CFLAGS += -static
	LDLIBS += -lSDL2_net -lmingw32 -lSDL2main -lSDL2 -lws2_32 -liphlpapi -ldinput8 -lshell32 -lsetupapi -ladvapi32 -luuid -lversion -loleaut32 -lole32 -limm32 -lwinmm -lgdi32 -luser32 -lm -lphysfs -Wl,--no-undefined 
#	LDLIBS += $(shell sdl2-config --static-libs)
else
	LDLIBS += -lSDL2main -lmingw32 -lSDL2 -mconsole -ldinput8 -lshell32 -lsetupapi -ladvapi32 -luuid -lversion -loleaut32 -lole32 -limm32 -lwinmm -lgdi32 -luser32 -lm -lphysfs -Wl,--no-undefined 
#	LDLIBS += $(shell sdl2-config --libs)
endif
else
ifeq ($(STATIC),yes)
	LDLIBS += $(shell sdl2-config --static-libs) -lSDL2_net
else
	LDLIBS += $(shell sdl2-config --libs) -lSDL2_net
endif
endif

LDLIBS += -lm

ifeq ($(USE_PHYSFS), 1)
	LDLIBS += -lphysfs
endif

CFLAGS += $(EXTRA_CFLAGS)

OBJS := $(SRCS:.c=.$(OBJEXT))

ifeq ($(OS),Windows_NT)
	OBJS += icon.o
endif

all: $(TARGET)
$(TARGET): $(OBJS) lib/libmobile.a
	$(CC) $(CFLAGS) $(EXEOUT)$@ $^ $(LDFLAGS) $(LDLIBS) 

%.obj: %.c
	$(CC) $(CFLAGS) $^

# %.res: %.rc
# 	rc /nologo /DCOMPANY="$(COMPANY)" /DDESCRIPTION="$(DESCRIPTION)" \
# 		/DLICENSE="$(LICENSE)" /DGIT_VER="$(GIT_VER)" \
# 		/DNAME="$(NAME)" /DICON_FILE="$(ICON_FILE)" $^
%.o: %.rc
	windres -i $^ -o $@

LIBMOBILE_SRCS := $(wildcard lib/libmobile/*.c)
lib/libmobile.a: $(LIBMOBILE_SRCS:.c=.o)
	$(AR) rcs $@ $^

clean:
	$(RM) $(SRCS:.c=.$(OBJEXT)) $(TARGET) icon.o \
	$(wildcard home/*.o) \
	$(wildcard audio/*.o) \
	$(wildcard data/*.o) \
	$(wildcard data/battle/*.o) \
	$(wildcard data/battle/ai/*.o) \
	$(wildcard data/battle_anims/*.o) \
	$(wildcard data/battle_tower/*.o) \
	$(wildcard data/collision/*.o) \
	$(wildcard data/decorations/*.o) \
	$(wildcard data/events/*.o) \
	$(wildcard data/items/*.o) \
	$(wildcard data/maps/*.o) \
	$(wildcard data/mobile/*.o) \
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
	$(wildcard engine/battle_anims/*.o) \
	$(wildcard engine/events/*.o) \
	$(wildcard engine/events/battle_tower/*.o) \
	$(wildcard engine/events/bug_contest/*.o) \
	$(wildcard engine/events/pokerus/*.o) \
	$(wildcard engine/games/*.o) \
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
	$(wildcard engine/printer/*.o) \
	$(wildcard engine/rtc/*.o) \
	$(wildcard engine/tilesets/*.o) \
	$(wildcard engine/*.o) \
	$(wildcard gfx/*.o) \
	$(wildcard gfx/pokemon/*.o) \
	$(wildcard gfx/sgb/*.o) \
	$(wildcard input_system/*.o) \
	$(wildcard lib/mobile/*.o) \
	$(wildcard maps/*.o) \
	$(wildcard mobile/*.o) \
	$(wildcard util/*.o)
#	$(wildcard ../*/*/*/*.o)

# rom.o: pokecrystal/pokecrystal.gbc
# 	$(MAKE) -C pokecrystal
# 	python tools/bin2c.py $^ $@ pokecrystal
# 	$(CC) $(CFLAGS) $(EXEOUT)$@ $^ $(LDFLAGS) $(LDLIBS) 
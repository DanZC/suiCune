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
	$(wildcard engine/battle/*.c) \
	$(wildcard engine/battle_anims/*.c) \
	$(wildcard engine/gfx/*.c) \
	$(wildcard engine/items/*.c) \
	$(wildcard engine/math/*.c) \
	$(wildcard engine/menus/*.c) \
	$(wildcard engine/movie/*.c) \
	$(wildcard engine/overworld/*.c) \
	$(wildcard engine/phone/*.c) \
	$(wildcard engine/pokegear/*.c) \
	$(wildcard engine/rtc/*.c) \
	functions.c hram.c vram.c 
#	$(wildcard ../*/*/*/*.c)
CFLAGS += $(shell sdl2-config --cflags)

ifeq ($(STATIC),yes)
	CFLAGS += -static
	LDLIBS += -lmingw32 -lSDL2main -lSDL2 -ldinput8 -lshell32 -lsetupapi -ladvapi32 -luuid -lversion -loleaut32 -lole32 -limm32 -lwinmm -lgdi32 -luser32 -lm -Wl,--no-undefined 
#	LDLIBS += $(shell sdl2-config --static-libs)
else
	LDLIBS += -lSDL2main -lmingw32 -lSDL2 -mconsole -ldinput8 -lshell32 -lsetupapi -ladvapi32 -luuid -lversion -loleaut32 -lole32 -limm32 -lwinmm -lgdi32 -luser32 -lm -Wl,--no-undefined 
#	LDLIBS += $(shell sdl2-config --libs)
endif

LDLIBS += -lm

CFLAGS += $(EXTRA_CFLAGS)

OBJS := $(SRCS:.c=.$(OBJEXT))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(EXEOUT)$@ $^ $(LDFLAGS) $(LDLIBS) 

%.obj: %.c
	$(CC) $(CFLAGS) $^

%.res: %.rc
	rc /nologo /DCOMPANY="$(COMPANY)" /DDESCRIPTION="$(DESCRIPTION)" \
		/DLICENSE="$(LICENSE)" /DGIT_VER="$(GIT_VER)" \
		/DNAME="$(NAME)" /DICON_FILE="$(ICON_FILE)" $^

clean:
	$(RM) $(SRCS:.c=.$(OBJEXT)) $(TARGET) \
	$(wildcard home/*.o) \
	$(wildcard audio/*.o) \
	$(wildcard engine/battle/*.o) \
	$(wildcard engine/battle_anims/*.o) \
	$(wildcard engine/gfx/*.o) \
	$(wildcard engine/items/*.o) \
	$(wildcard engine/menus/*.o) \
	$(wildcard engine/movie/*.o) \
	$(wildcard engine/overworld/*.o) \
	$(wildcard engine/phone/*.o) \
	$(wildcard engine/pokegear/*.o) \
	$(wildcard engine/rtc/*.o)
#	$(wildcard ../*/*/*/*.o)

# rom.o: pokecrystal/pokecrystal.gbc
# 	$(MAKE) -C pokecrystal
# 	python tools/bin2c.py $^ $@ pokecrystal
# 	$(CC) $(CFLAGS) $(EXEOUT)$@ $^ $(LDFLAGS) $(LDLIBS) 
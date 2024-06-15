/*
; pic + oam animations

frame: MACRO
	db \1
x = \2
if _NARG > 2
rept _NARG - 2
x |= 1 << (\3 + 1)
	shift
endr
endc
	db x
ENDM

	const_def -1, -1

	const endanim_command ; $ff
endanim: MACRO
	db endanim_command
ENDM

	const dorestart_command ; $fe
dorestart: MACRO
	db dorestart_command
ENDM

	const dowait_command ; $fd
dowait: MACRO
	db dowait_command
	db \1 ; frames
ENDM

	const delanim_command ; $fc
delanim: MACRO
; Removes the object from the screen, as opposed to `endanim` which just stops all motion
	db delanim_command
ENDM


; Used for pic animations
	const_def -2, -1

	const setrepeat_command ; $fe
setrepeat: MACRO
	db setrepeat_command
	db \1 ; amount of times to repeat
ENDM

	const dorepeat_command ; $fd
dorepeat: MACRO
	db dorepeat_command
	db \1 ; command offset to jump to
ENDM
*/

#define endanim_command 0xff
#define dorestart_command 0xfe
#define dowait_command 0xfd
#define delanim_command 0xfc
#define setrepeat_command 0xfe
#define dorepeat_command 0xfd

#define endanim endanim_command
#define dowait(_f) dowait_command, (_f)
#define dorepeat(_o) dorepeat_command, (_o)
#define setrepeat(_n) setrepeat_command, (_n)
#define frame2(_x, _0) (_x), (_0)
#define frame3(_x, _0, _1) (_x), ((_0) | (1 << (_1) + 1))
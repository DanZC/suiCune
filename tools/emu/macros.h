#ifndef MACROS_H
#define MACROS_H
#include "../../funcmap.h"

#define SET_PC(x)                                                                                     \
    do {                                                                                              \
        gb.cpu_reg.pc = (uint16_t)(x);                                                                \
        gb.cpu_reg.pc = gb.cpu_reg.pc < 0x4000 ? gb.cpu_reg.pc : ((gb.cpu_reg.pc & 0x3FFF) | 0x4000); \
    } while (0)

#define INC_PC(x) gb.cpu_reg.pc += x;

#define PEEK(message)                                                                                                                                                                                 \
    do {                                                                                                                                                                                              \
        uint16_t temp = gb_read(REG_SP);                                                                                                                                                              \
        temp |= (gb_read(REG_SP + 1) << 8);                                                                                                                                                           \
        printf("%d#%s::%s: SP@%X:%X PC@%X:%X, AF:%X%X, BC:%X, DE:%X, HL:%X,\n", gb.nestedCalls, __func__, message, REG_SP, temp, gb.selected_rom_bank, REG_PC, REG_A, REG_F, REG_BC, REG_DE, REG_HL); \
    } while (0)

// printf("CALL#%d: %X, PC@%X:%X\n", gb.nestedCalls, dest, gb.selected_rom_bank, REG_PC);
#define DBG_CALL(dest)                                  \
    do {                                                \
        gb.nestedCalls++;                               \
        gb.stackCalls[gb.stackDepth++] = gb.cpu_reg.sp; \
    } while (0)

// printf("RET #%d: %X, PC@%X:%X\n", gb.nestedCalls, dest, gb.selected_rom_bank, REG_PC);
#define DBG_RET(dest)                                                                                                                                                                                                                                             \
    do {                                                                                                                                                                                                                                                          \
        gb.nestedCalls--;                                                                                                                                                                                                                                         \
        if (gb.stackCalls[--gb.stackDepth] != gb.cpu_reg.sp) printf("Unexpected Stack: %X -> %X @%X (from: %X)\n", gb.stackCalls[gb.stackDepth + 1], gb.cpu_reg.sp, gb.cpu_reg.pc < 0x4000 ? gb.cpu_reg.pc : gb.cpu_reg.pc | (gb.selected_rom_bank << 14), dest); \
    } while (0)

#define CHIRP printf("%s test\n", __func__);

#define gb_read16(x) (gb_read(x) | (gb_read((x) + 1) << 8))
#define gb_write16(x, y)   \
    gb_write(x, (y)&0xFF); \
    gb_write((x) + 1, (y) >> 8);

#define gb_pointer(x) (void*)&gb.wram[(x)-WRAM_0_ADDR];

//---- Only use these for the goto commands ----
#define IF_C  \
    INC_PC(2) \
    if (gb.cpu_reg.f_bits.c)
#define IF_NC \
    INC_PC(2) \
    if (!gb.cpu_reg.f_bits.c)
#define IF_Z  \
    INC_PC(2) \
    if (gb.cpu_reg.f_bits.z)
#define IF_NZ \
    INC_PC(2) \
    if (!gb.cpu_reg.f_bits.z)
//----------------------------------------------

#define imm8 gb_read(gb.cpu_reg.pc)
#define imm16 gb_read(gb.cpu_reg.pc) + (gb_read(gb.cpu_reg.pc + 1) << 8)
#define reg_bc_ gb_read(gb.cpu_reg.bc)
#define reg_de_ gb_read(gb.cpu_reg.de)
#define reg_hl_ gb_read(gb.cpu_reg.hl)
#define reg_hli_ gb_read(gb.cpu_reg.hl++)
#define reg_hld_ gb_read(gb.cpu_reg.hl--)
#define REG_A gb.cpu_reg.a
#define REG_F gb.cpu_reg.f
#define REG_B gb.cpu_reg.b
#define REG_C gb.cpu_reg.c
#define REG_D gb.cpu_reg.d
#define REG_E gb.cpu_reg.e
#define REG_H gb.cpu_reg.h
#define REG_L gb.cpu_reg.l
#define REG_AF gb.cpu_reg.af
#define REG_BC gb.cpu_reg.bc
#define REG_DE gb.cpu_reg.de
#define REG_HL gb.cpu_reg.hl
#define REG_PC gb.cpu_reg.pc
#define REG_SP gb.cpu_reg.sp
#define REG_F_Z gb.cpu_reg.f_bits.z
#define REG_F_C gb.cpu_reg.f_bits.c

#define WRITE(dest, value) (gb_write(dest, value))
#define NOP       \
    do {          \
        INC_PC(1) \
    } while (0)

#define PUSH_AF                                                            \
    do {                                                                   \
        gb_write(--gb.cpu_reg.sp, gb.cpu_reg.a);                           \
        gb_write(--gb.cpu_reg.sp,                                          \
                 gb.cpu_reg.f_bits.z << 7 | gb.cpu_reg.f_bits.n << 6 |     \
                     gb.cpu_reg.f_bits.h << 5 | gb.cpu_reg.f_bits.c << 4); \
        INC_PC(1)                                                          \
    } while (0)

#define PUSH_BC                                  \
    do {                                         \
        gb_write(--gb.cpu_reg.sp, gb.cpu_reg.b); \
        gb_write(--gb.cpu_reg.sp, gb.cpu_reg.c); \
        INC_PC(1)                                \
    } while (0)

#define PUSH_DE                                  \
    do {                                         \
        gb_write(--gb.cpu_reg.sp, gb.cpu_reg.d); \
        gb_write(--gb.cpu_reg.sp, gb.cpu_reg.e); \
        INC_PC(1)                                \
    } while (0)

#define PUSH_HL                                  \
    do {                                         \
        gb_write(--gb.cpu_reg.sp, gb.cpu_reg.h); \
        gb_write(--gb.cpu_reg.sp, gb.cpu_reg.l); \
        INC_PC(1)                                \
    } while (0)

#define PUSH_PC                                          \
    do {                                                 \
        gb_write(--gb.cpu_reg.sp, gb.cpu_reg.pc >> 8);   \
        gb_write(--gb.cpu_reg.sp, gb.cpu_reg.pc & 0xFF); \
    } while (0)

#define POP_AF                                     \
    do {                                           \
        uint8_t temp_8 = gb_read(gb.cpu_reg.sp++); \
        gb.cpu_reg.f_bits.z = (temp_8 >> 7) & 1;   \
        gb.cpu_reg.f_bits.n = (temp_8 >> 6) & 1;   \
        gb.cpu_reg.f_bits.h = (temp_8 >> 5) & 1;   \
        gb.cpu_reg.f_bits.c = (temp_8 >> 4) & 1;   \
        gb.cpu_reg.a = gb_read(gb.cpu_reg.sp++);   \
        INC_PC(1)                                  \
    } while (0)

#define POP_BC                                   \
    do {                                         \
        gb.cpu_reg.c = gb_read(gb.cpu_reg.sp++); \
        gb.cpu_reg.b = gb_read(gb.cpu_reg.sp++); \
        INC_PC(1)                                \
    } while (0)

#define POP_DE                                   \
    do {                                         \
        gb.cpu_reg.e = gb_read(gb.cpu_reg.sp++); \
        gb.cpu_reg.d = gb_read(gb.cpu_reg.sp++); \
        INC_PC(1)                                \
    } while (0)

#define POP_HL                                   \
    do {                                         \
        gb.cpu_reg.l = gb_read(gb.cpu_reg.sp++); \
        gb.cpu_reg.h = gb_read(gb.cpu_reg.sp++); \
        INC_PC(1)                                \
    } while (0)

#define POP_PC                                            \
    do {                                                  \
        gb.cpu_reg.pc = gb_read(gb.cpu_reg.sp++);         \
        gb.cpu_reg.pc |= (gb_read(gb.cpu_reg.sp++) << 8); \
    } while (0)

#define LD_A(x)           \
    do {                  \
        gb.cpu_reg.a = x; \
        INC_PC(2)         \
    } while (0)

#define LD_A_A    \
    do {          \
        INC_PC(1) \
    } while (0)

#define LD_A_B                       \
    do {                             \
        gb.cpu_reg.a = gb.cpu_reg.b; \
        INC_PC(1)                    \
    } while (0)

#define LD_A_C                       \
    do {                             \
        gb.cpu_reg.a = gb.cpu_reg.c; \
        INC_PC(1)                    \
    } while (0)

#define LD_A_D                       \
    do {                             \
        gb.cpu_reg.a = gb.cpu_reg.d; \
        INC_PC(1)                    \
    } while (0)

#define LD_A_E                       \
    do {                             \
        gb.cpu_reg.a = gb.cpu_reg.e; \
        INC_PC(1)                    \
    } while (0)

#define LD_A_H                       \
    do {                             \
        gb.cpu_reg.a = gb.cpu_reg.h; \
        INC_PC(1)                    \
    } while (0)

#define LD_A_L                       \
    do {                             \
        gb.cpu_reg.a = gb.cpu_reg.l; \
        INC_PC(1)                    \
    } while (0)

#define LD_A_bc                                \
    do {                                       \
        gb.cpu_reg.a = gb_read(gb.cpu_reg.bc); \
        INC_PC(1)                              \
    } while (0)

#define LD_A_de                                \
    do {                                       \
        gb.cpu_reg.a = gb_read(gb.cpu_reg.de); \
        INC_PC(1)                              \
    } while (0)

#define LD_A_hl                                \
    do {                                       \
        gb.cpu_reg.a = gb_read(gb.cpu_reg.hl); \
        INC_PC(1)                              \
    } while (0)

#define LD_A_hli                                 \
    do {                                         \
        gb.cpu_reg.a = gb_read(gb.cpu_reg.hl++); \
        INC_PC(1)                                \
    } while (0)

#define LD_A_hld                                 \
    do {                                         \
        gb.cpu_reg.a = gb_read(gb.cpu_reg.hl--); \
        INC_PC(1)                                \
    } while (0)

#define LD_B(x)           \
    do {                  \
        gb.cpu_reg.b = x; \
        INC_PC(2)         \
    } while (0)

#define LD_B_A                       \
    do {                             \
        gb.cpu_reg.b = gb.cpu_reg.a; \
        INC_PC(1)                    \
    } while (0)

#define LD_B_B    \
    do {          \
        INC_PC(1) \
    } while (0)

#define LD_B_C                       \
    do {                             \
        gb.cpu_reg.b = gb.cpu_reg.c; \
        INC_PC(1)                    \
    } while (0)

#define LD_B_D                       \
    do {                             \
        gb.cpu_reg.b = gb.cpu_reg.d; \
        INC_PC(1)                    \
    } while (0)

#define LD_B_E                       \
    do {                             \
        gb.cpu_reg.b = gb.cpu_reg.e; \
        INC_PC(1)                    \
    } while (0)

#define LD_B_H                       \
    do {                             \
        gb.cpu_reg.b = gb.cpu_reg.h; \
        INC_PC(1)                    \
    } while (0)

#define LD_B_L                       \
    do {                             \
        gb.cpu_reg.b = gb.cpu_reg.l; \
        INC_PC(1)                    \
    } while (0)

#define LD_B_hl                                \
    do {                                       \
        gb.cpu_reg.b = gb_read(gb.cpu_reg.hl); \
        INC_PC(1)                              \
    } while (0)

#define LD_C(x)           \
    do {                  \
        gb.cpu_reg.c = x; \
        INC_PC(2)         \
    } while (0)

#define LD_C_A                       \
    do {                             \
        gb.cpu_reg.c = gb.cpu_reg.a; \
        INC_PC(1)                    \
    } while (0)

#define LD_C_B                       \
    do {                             \
        gb.cpu_reg.c = gb.cpu_reg.b; \
        INC_PC(1)                    \
    } while (0)

#define LD_C_C    \
    do {          \
        INC_PC(1) \
    } while (0)

#define LD_C_D                       \
    do {                             \
        gb.cpu_reg.c = gb.cpu_reg.d; \
        INC_PC(1)                    \
    } while (0)

#define LD_C_E                       \
    do {                             \
        gb.cpu_reg.c = gb.cpu_reg.e; \
        INC_PC(1)                    \
    } while (0)

#define LD_C_H                       \
    do {                             \
        gb.cpu_reg.c = gb.cpu_reg.h; \
        INC_PC(1)                    \
    } while (0)

#define LD_C_L                       \
    do {                             \
        gb.cpu_reg.c = gb.cpu_reg.l; \
        INC_PC(1)                    \
    } while (0)

#define LD_C_hl                                \
    do {                                       \
        gb.cpu_reg.c = gb_read(gb.cpu_reg.hl); \
        INC_PC(1)                              \
    } while (0)

#define LD_D(x)           \
    do {                  \
        gb.cpu_reg.d = x; \
        INC_PC(2)         \
    } while (0)

#define LD_D_A                       \
    do {                             \
        gb.cpu_reg.d = gb.cpu_reg.a; \
        INC_PC(1)                    \
    } while (0)

#define LD_D_B                       \
    do {                             \
        gb.cpu_reg.d = gb.cpu_reg.b; \
        INC_PC(1)                    \
    } while (0)

#define LD_D_C                       \
    do {                             \
        gb.cpu_reg.d = gb.cpu_reg.c; \
        INC_PC(1)                    \
    } while (0)

#define LD_D_D    \
    do {          \
        INC_PC(1) \
    } while (0)

#define LD_D_E                       \
    do {                             \
        gb.cpu_reg.d = gb.cpu_reg.e; \
        INC_PC(1)                    \
    } while (0)

#define LD_D_H                       \
    do {                             \
        gb.cpu_reg.d = gb.cpu_reg.h; \
        INC_PC(1)                    \
    } while (0)

#define LD_D_L                       \
    do {                             \
        gb.cpu_reg.d = gb.cpu_reg.l; \
        INC_PC(1)                    \
    } while (0)

#define LD_D_hl                                \
    do {                                       \
        gb.cpu_reg.d = gb_read(gb.cpu_reg.hl); \
        INC_PC(1)                              \
    } while (0)

#define LD_E(x)           \
    do {                  \
        gb.cpu_reg.e = x; \
        INC_PC(2)         \
    } while (0)

#define LD_E_A                       \
    do {                             \
        gb.cpu_reg.e = gb.cpu_reg.a; \
        INC_PC(1)                    \
    } while (0)

#define LD_E_B                       \
    do {                             \
        gb.cpu_reg.e = gb.cpu_reg.b; \
        INC_PC(1)                    \
    } while (0)

#define LD_E_C                       \
    do {                             \
        gb.cpu_reg.e = gb.cpu_reg.c; \
        INC_PC(1)                    \
    } while (0)

#define LD_E_D                       \
    do {                             \
        gb.cpu_reg.e = gb.cpu_reg.d; \
        INC_PC(1)                    \
    } while (0)

#define LD_E_E    \
    do {          \
        INC_PC(1) \
    } while (0)

#define LD_E_H                       \
    do {                             \
        gb.cpu_reg.e = gb.cpu_reg.h; \
        INC_PC(1)                    \
    } while (0)

#define LD_E_L                       \
    do {                             \
        gb.cpu_reg.e = gb.cpu_reg.l; \
        INC_PC(1)                    \
    } while (0)

#define LD_E_hl                                \
    do {                                       \
        gb.cpu_reg.e = gb_read(gb.cpu_reg.hl); \
        INC_PC(1)                              \
    } while (0)

#define LD_H(x)           \
    do {                  \
        gb.cpu_reg.h = x; \
        INC_PC(2)         \
    } while (0)

#define LD_H_A                       \
    do {                             \
        gb.cpu_reg.h = gb.cpu_reg.a; \
        INC_PC(1)                    \
    } while (0)

#define LD_H_B                       \
    do {                             \
        gb.cpu_reg.h = gb.cpu_reg.b; \
        INC_PC(1)                    \
    } while (0)

#define LD_H_C                       \
    do {                             \
        gb.cpu_reg.h = gb.cpu_reg.c; \
        INC_PC(1)                    \
    } while (0)

#define LD_H_D                       \
    do {                             \
        gb.cpu_reg.h = gb.cpu_reg.d; \
        INC_PC(1)                    \
    } while (0)

#define LD_H_E                       \
    do {                             \
        gb.cpu_reg.h = gb.cpu_reg.e; \
        INC_PC(1)                    \
    } while (0)

#define LD_H_H    \
    do {          \
        INC_PC(1) \
    } while (0)

#define LD_H_L                       \
    do {                             \
        gb.cpu_reg.h = gb.cpu_reg.l; \
        INC_PC(1)                    \
    } while (0)

#define LD_H_hl                                \
    do {                                       \
        gb.cpu_reg.h = gb_read(gb.cpu_reg.hl); \
        INC_PC(1)                              \
    } while (0)

#define LD_L(x)           \
    do {                  \
        gb.cpu_reg.l = x; \
        INC_PC(2)         \
    } while (0)

#define LD_L_A                       \
    do {                             \
        gb.cpu_reg.l = gb.cpu_reg.a; \
        INC_PC(1)                    \
    } while (0)

#define LD_L_B                       \
    do {                             \
        gb.cpu_reg.l = gb.cpu_reg.b; \
        INC_PC(1)                    \
    } while (0)

#define LD_L_C                       \
    do {                             \
        gb.cpu_reg.l = gb.cpu_reg.c; \
        INC_PC(1)                    \
    } while (0)

#define LD_L_D                       \
    do {                             \
        gb.cpu_reg.l = gb.cpu_reg.d; \
        INC_PC(1)                    \
    } while (0)

#define LD_L_E                       \
    do {                             \
        gb.cpu_reg.l = gb.cpu_reg.e; \
        INC_PC(1)                    \
    } while (0)

#define LD_L_H                       \
    do {                             \
        gb.cpu_reg.l = gb.cpu_reg.h; \
        INC_PC(1)                    \
    } while (0)

#define LD_L_L    \
    do {          \
        INC_PC(1) \
    } while (0)

#define LD_L_hl                                \
    do {                                       \
        gb.cpu_reg.l = gb_read(gb.cpu_reg.hl); \
        INC_PC(1)                              \
    } while (0)

#define LD_hl(x)                    \
    do {                            \
        gb_write(gb.cpu_reg.hl, x); \
        INC_PC(2)                   \
    } while (0)

#define LD_hl_A                                \
    do {                                       \
        gb_write(gb.cpu_reg.hl, gb.cpu_reg.a); \
        INC_PC(1)                              \
    } while (0)

#define LD_hli_A                                 \
    do {                                         \
        gb_write(gb.cpu_reg.hl++, gb.cpu_reg.a); \
        INC_PC(1)                                \
    } while (0)

#define LD_hld_A                                 \
    do {                                         \
        gb_write(gb.cpu_reg.hl--, gb.cpu_reg.a); \
        INC_PC(1)                                \
    } while (0)

#define LD_hl_B                                \
    do {                                       \
        gb_write(gb.cpu_reg.hl, gb.cpu_reg.b); \
        INC_PC(1)                              \
    } while (0)

#define LD_hl_C                                \
    do {                                       \
        gb_write(gb.cpu_reg.hl, gb.cpu_reg.c); \
        INC_PC(1)                              \
    } while (0)

#define LD_hl_D                                \
    do {                                       \
        gb_write(gb.cpu_reg.hl, gb.cpu_reg.d); \
        INC_PC(1)                              \
    } while (0)

#define LD_hl_E                                \
    do {                                       \
        gb_write(gb.cpu_reg.hl, gb.cpu_reg.e); \
        INC_PC(1)                              \
    } while (0)

#define LD_hl_H                                \
    do {                                       \
        gb_write(gb.cpu_reg.hl, gb.cpu_reg.h); \
        INC_PC(1)                              \
    } while (0)

#define LD_hl_L                                \
    do {                                       \
        gb_write(gb.cpu_reg.hl, gb.cpu_reg.l); \
        INC_PC(1)                              \
    } while (0)

#define LD_hl_hl  \
    do {          \
        INC_PC(1) \
    } while (0)

#define LD_bc_A                                \
    do {                                       \
        gb_write(gb.cpu_reg.bc, gb.cpu_reg.a); \
        INC_PC(1)                              \
    } while (0)

#define LD_de_A                                \
    do {                                       \
        gb_write(gb.cpu_reg.de, gb.cpu_reg.a); \
        INC_PC(1)                              \
    } while (0)

#define LD_BC(x)           \
    do {                   \
        gb.cpu_reg.bc = x; \
        INC_PC(3)          \
    } while (0)

#define LD_DE(x)           \
    do {                   \
        gb.cpu_reg.de = x; \
        INC_PC(3)          \
    } while (0)

#define LD_HL(x)           \
    do {                   \
        gb.cpu_reg.hl = x; \
        INC_PC(3)          \
    } while (0)

#define LD_SP(x)           \
    do {                   \
        gb.cpu_reg.sp = x; \
        INC_PC(3)          \
    } while (0)

#define LD_SP_HL                       \
    do {                               \
        gb.cpu_reg.sp = gb.cpu_reg.hl; \
        INC_PC(1)                      \
    } while (0)

#define IF0_C(x)                   \
    do {                           \
        if (gb.cpu_reg.f_bits.c) { \
            x;                     \
        }                          \
    } while (0)

#define IF0_NC(x)                   \
    do {                            \
        if (!gb.cpu_reg.f_bits.c) { \
            x;                      \
        }                           \
    } while (0)

#define IF0_Z(x)                   \
    do {                           \
        if (gb.cpu_reg.f_bits.z) { \
            x;                     \
        }                          \
    } while (0)

#define IF0_NZ(x)                   \
    do {                            \
        if (!gb.cpu_reg.f_bits.z) { \
            x;                      \
        }                           \
    } while (0)

#define RET                         \
    do {                            \
        if (!gb.redirected) POP_PC; \
        return;                     \
    } while (0)

#define RETI RET

#define RET_C       \
    do {            \
        INC_PC(1)   \
        IF0_C(RET); \
    } while (0)

#define RET_NC       \
    do {             \
        INC_PC(1)    \
        IF0_NC(RET); \
    } while (0)

#define RET_Z       \
    do {            \
        INC_PC(1)   \
        IF0_Z(RET); \
    } while (0)

#define RET_NZ       \
    do {             \
        INC_PC(1)    \
        IF0_NZ(RET); \
    } while (0)

#define _RET                       \
    do {                           \
        if (gb.redirected) return; \
        POP_PC;                    \
    } while (0)

#define _RETI _RET

#define _RET_C       \
    do {             \
        IF0_C(_RET); \
    } while (0)

#define _RET_NC       \
    do {              \
        IF0_NC(_RET); \
    } while (0)

#define _RET_Z       \
    do {             \
        IF0_Z(_RET); \
    } while (0)

#define _RET_NZ       \
    do {              \
        IF0_NZ(_RET); \
    } while (0)

#define IF1_C(x)                   \
    do {                           \
        if (gb.cpu_reg.f_bits.c) { \
            x;                     \
        } else {                   \
            gb.cpu_reg.pc++;       \
        }                          \
    } while (0)

#define IF1_NC(x)                   \
    do {                            \
        if (!gb.cpu_reg.f_bits.c) { \
            x;                      \
        } else {                    \
            gb.cpu_reg.pc++;        \
        }                           \
    } while (0)

#define IF1_Z(x)                   \
    do {                           \
        if (gb.cpu_reg.f_bits.z) { \
            x;                     \
        } else {                   \
            gb.cpu_reg.pc++;       \
        }                          \
    } while (0)

#define IF1_NZ(x)                   \
    do {                            \
        if (!gb.cpu_reg.f_bits.z) { \
            x;                      \
        } else {                    \
            gb.cpu_reg.pc++;        \
        }                           \
    } while (0)

#define JR(x)                                                              \
    do {                                                                   \
        uint32_t dest = x;                                                 \
        gb.cpu_reg.pc = dest < 0x4000 ? dest : ((dest & 0x3FFF) | 0x4000); \
        if (convertedFunc[dest]) {                                         \
            DBG_CALL(dest);                                                \
            convertedFunc[dest]();                                         \
            DBG_RET(dest);                                                 \
        } else {                                                           \
            if (!gb.redirected) return;                                    \
            DBG_CALL(dest);                                                \
            gb_run_frame();                                                \
            DBG_RET(dest);                                                 \
        }                                                                  \
        return;                                                            \
    } while (0)

#define JR_C(x)       \
    do {              \
        INC_PC(1)     \
        IF1_C(JR(x)); \
    } while (0)

#define JR_NC(x)       \
    do {               \
        INC_PC(1)      \
        IF1_NC(JR(x)); \
    } while (0)

#define JR_Z(x)       \
    do {              \
        INC_PC(1)     \
        IF1_Z(JR(x)); \
    } while (0)

#define JR_NZ(x)       \
    do {               \
        INC_PC(1)      \
        IF1_NZ(JR(x)); \
    } while (0)

#define _JR(x)                                                                                                                \
    do {                                                                                                                      \
        gb.cpu_reg.pc += (int8_t)x + 1;                                                                                       \
        if (gb.redirected) {                                                                                                  \
            uint32_t dest = gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE));      \
            if (convertedFunc[gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE))]) { \
                DBG_CALL(dest);                                                                                               \
                convertedFunc[gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE))](); \
                DBG_RET(dest);                                                                                                \
                return;                                                                                                       \
            }                                                                                                                 \
        }                                                                                                                     \
    } while (0)

#define _JR_C(x)       \
    do {               \
        IF1_C(_JR(x)); \
    } while (0)

#define _JR_NC(x)       \
    do {                \
        IF1_NC(_JR(x)); \
    } while (0)

#define _JR_Z(x)       \
    do {               \
        IF1_Z(_JR(x)); \
    } while (0)

#define _JR_NZ(x)       \
    do {                \
        IF1_NZ(_JR(x)); \
    } while (0)

#define IF2_C(x)                   \
    do {                           \
        if (gb.cpu_reg.f_bits.c) { \
            x;                     \
        } else {                   \
            gb.cpu_reg.pc += 2;    \
        }                          \
    } while (0)

#define IF2_NC(x)                   \
    do {                            \
        if (!gb.cpu_reg.f_bits.c) { \
            x;                      \
        } else {                    \
            gb.cpu_reg.pc += 2;     \
        }                           \
    } while (0)

#define IF2_Z(x)                   \
    do {                           \
        if (gb.cpu_reg.f_bits.z) { \
            x;                     \
        } else {                   \
            gb.cpu_reg.pc += 2;    \
        }                          \
    } while (0)

#define IF2_NZ(x)                   \
    do {                            \
        if (!gb.cpu_reg.f_bits.z) { \
            x;                      \
        } else {                    \
            gb.cpu_reg.pc += 2;     \
        }                           \
    } while (0)

#define JP(x)                                                              \
    do {                                                                   \
        uint32_t dest = x;                                                 \
        gb.cpu_reg.pc = dest < 0x4000 ? dest : ((dest & 0x3FFF) | 0x4000); \
        if (convertedFunc[dest]) {                                         \
            DBG_CALL(dest);                                                \
            convertedFunc[dest]();                                         \
            DBG_RET(dest);                                                 \
        } else {                                                           \
            if (!gb.redirected) return;                                    \
            DBG_CALL(dest);                                                \
            gb_run_frame();                                                \
            DBG_RET(dest);                                                 \
        }                                                                  \
        return;                                                            \
    } while (0)

#define JP_C(x)       \
    do {              \
        INC_PC(1)     \
        IF2_C(JP(x)); \
    } while (0)

#define JP_NC(x)       \
    do {               \
        INC_PC(1)      \
        IF2_NC(JP(x)); \
    } while (0)

#define JP_Z(x)       \
    do {              \
        INC_PC(1)     \
        IF2_Z(JP(x)); \
    } while (0)

#define JP_NZ(x)       \
    do {               \
        INC_PC(1)      \
        IF2_NZ(JP(x)); \
    } while (0)

#define JP_hl                                                                                                        \
    do {                                                                                                             \
        gb.cpu_reg.pc = gb.cpu_reg.hl;                                                                               \
        if (!gb.redirected) return;                                                                                  \
        uint32_t dest = gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE)); \
        DBG_CALL(dest);                                                                                              \
        gb_run_frame();                                                                                              \
        DBG_RET(dest);                                                                                               \
        return;                                                                                                      \
    } while (0)

#define _JP(x)                                                                                                                \
    do {                                                                                                                      \
        uint32_t dest = x;                                                                                                    \
        gb.cpu_reg.pc = dest;                                                                                                 \
        if (gb.redirected) {                                                                                                  \
            dest = gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE));               \
            if (convertedFunc[gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE))]) { \
                DBG_CALL(dest);                                                                                               \
                convertedFunc[gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE))](); \
                DBG_RET(dest);                                                                                                \
                return;                                                                                                       \
            }                                                                                                                 \
        }                                                                                                                     \
    } while (0)

#define _JP_C(x)       \
    do {               \
        IF2_C(_JP(x)); \
    } while (0)

#define _JP_NC(x)       \
    do {                \
        IF2_NC(_JP(x)); \
    } while (0)

#define _JP_Z(x)       \
    do {               \
        IF2_Z(_JP(x)); \
    } while (0)

#define _JP_NZ(x)       \
    do {                \
        IF2_NZ(_JP(x)); \
    } while (0)

#define _JP_hl                                                                                                                \
    do {                                                                                                                      \
        gb.cpu_reg.pc = gb.cpu_reg.hl;                                                                                        \
        if (gb.redirected) {                                                                                                  \
            uint32_t dest = gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE));      \
            if (convertedFunc[gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE))]) { \
                DBG_CALL(dest);                                                                                               \
                convertedFunc[gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE))](); \
                DBG_RET(dest);                                                                                                \
                return;                                                                                                       \
            }                                                                                                                 \
        }                                                                                                                     \
    } while (0)

#define CALL(x)                                                                          \
    do {                                                                                 \
        INC_PC(3);                                                                       \
        uint32_t dest = x;                                                               \
        if ((!gb.redirected) && (redirectFunc[dest] || !(convertedFunc[dest]))) PUSH_PC; \
        gb.cpu_reg.pc = dest < 0x4000 ? dest : ((dest & 0x3FFF) | 0x4000);               \
        if (convertedFunc[dest]) {                                                       \
            DBG_CALL(dest);                                                              \
            convertedFunc[dest]();                                                       \
            DBG_RET(dest);                                                               \
        } else {                                                                         \
            if (!gb.redirected) return;                                                  \
            DBG_CALL(dest);                                                              \
            gb_run_frame();                                                              \
            DBG_RET(dest);                                                               \
        }                                                                                \
    } while (0)

#define CALL_C(x)                                                                            \
    do {                                                                                     \
        INC_PC(3);                                                                           \
        IF2_C(                                                                               \
            uint32_t dest = x;                                                               \
            if ((!gb.redirected) && (redirectFunc[dest] || !(convertedFunc[dest]))) PUSH_PC; \
            gb.cpu_reg.pc = dest < 0x4000 ? dest : ((dest & 0x3FFF) | 0x4000);               \
            if (convertedFunc[dest]) {                                                       \
                DBG_CALL(dest);                                                              \
                convertedFunc[dest]();                                                       \
                DBG_RET(dest);                                                               \
            } else {                                                                         \
                if (!gb.redirected) return;                                                  \
                DBG_CALL(dest);                                                              \
                gb_run_frame();                                                              \
                DBG_RET(dest);                                                               \
            });                                                                              \
    } while (0)

#define CALL_NC(x)                                                                           \
    do {                                                                                     \
        INC_PC(3);                                                                           \
        IF2_NC(                                                                              \
            uint32_t dest = x;                                                               \
            if ((!gb.redirected) && (redirectFunc[dest] || !(convertedFunc[dest]))) PUSH_PC; \
            gb.cpu_reg.pc = dest < 0x4000 ? dest : ((dest & 0x3FFF) | 0x4000);               \
            if (convertedFunc[dest]) {                                                       \
                DBG_CALL(dest);                                                              \
                convertedFunc[dest]();                                                       \
                DBG_RET(dest);                                                               \
            } else {                                                                         \
                if (!gb.redirected) return;                                                  \
                DBG_CALL(dest);                                                              \
                gb_run_frame();                                                              \
                DBG_RET(dest);                                                               \
            });                                                                              \
    } while (0)

#define CALL_Z(x)                                                                            \
    do {                                                                                     \
        INC_PC(3);                                                                           \
        IF2_Z(                                                                               \
            uint32_t dest = x;                                                               \
            if ((!gb.redirected) && (redirectFunc[dest] || !(convertedFunc[dest]))) PUSH_PC; \
            gb.cpu_reg.pc = dest < 0x4000 ? dest : ((dest & 0x3FFF) | 0x4000);               \
            if (convertedFunc[dest]) {                                                       \
                DBG_CALL(dest);                                                              \
                convertedFunc[dest]();                                                       \
                DBG_RET(dest);                                                               \
            } else {                                                                         \
                if (!gb.redirected) return;                                                  \
                DBG_CALL(dest);                                                              \
                gb_run_frame();                                                              \
                DBG_RET(dest);                                                               \
            });                                                                              \
    } while (0)

#define CALL_NZ(x)                                                                           \
    do {                                                                                     \
        INC_PC(3);                                                                           \
        IF2_NZ(                                                                              \
            uint32_t dest = x;                                                               \
            if ((!gb.redirected) && (redirectFunc[dest] || !(convertedFunc[dest]))) PUSH_PC; \
            gb.cpu_reg.pc = dest < 0x4000 ? dest : ((dest & 0x3FFF) | 0x4000);               \
            if (convertedFunc[dest]) {                                                       \
                DBG_CALL(dest);                                                              \
                convertedFunc[dest]();                                                       \
                DBG_RET(dest);                                                               \
            } else {                                                                         \
                if (!gb.redirected) return;                                                  \
                DBG_CALL(dest);                                                              \
                gb_run_frame();                                                              \
                DBG_RET(dest);                                                               \
            });                                                                              \
    } while (0)

#define _CALL(x)                                                                                                              \
    do {                                                                                                                      \
        uint32_t dest = x;                                                                                                    \
        INC_PC(2);                                                                                                            \
        PUSH_PC;                                                                                                              \
        gb.cpu_reg.pc = dest;                                                                                                 \
        if (gb.redirected) {                                                                                                  \
            dest = gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE));               \
            DBG_CALL(dest);                                                                                                   \
            if (convertedFunc[gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE))])   \
                convertedFunc[gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE))](); \
            else                                                                                                              \
                gb_run_frame();                                                                                               \
            DBG_RET(dest);                                                                                                    \
            POP_PC;                                                                                                           \
        }                                                                                                                     \
    } while (0)

#define _CALL_C(x)       \
    do {                 \
        IF2_C(_CALL(x)); \
    } while (0)

#define _CALL_NC(x)       \
    do {                  \
        IF2_NC(_CALL(x)); \
    } while (0)

#define _CALL_Z(x)       \
    do {                 \
        IF2_Z(_CALL(x)); \
    } while (0)

#define _CALL_NZ(x)       \
    do {                  \
        IF2_NZ(_CALL(x)); \
    } while (0)

#define RST(x)                                                                           \
    do {                                                                                 \
        INC_PC(1);                                                                       \
        uint32_t dest = (x)&0x38;                                                        \
        if ((!gb.redirected) && (redirectFunc[dest] || !(convertedFunc[dest]))) PUSH_PC; \
        gb.cpu_reg.pc = dest;                                                            \
        if (convertedFunc[dest]) {                                                       \
            DBG_CALL(dest);                                                              \
            convertedFunc[dest]();                                                       \
            DBG_RET(dest);                                                               \
        } else {                                                                         \
            if (!gb.redirected) return;                                                  \
            DBG_CALL(dest);                                                              \
            gb_run_frame();                                                              \
            DBG_RET(dest);                                                               \
        }                                                                                \
    } while (0)

#define _RST(x)                                                                                                               \
    do {                                                                                                                      \
        uint32_t dest = ((x)&0x38);                                                                                           \
        PUSH_PC;                                                                                                              \
        gb.cpu_reg.pc = dest;                                                                                                 \
        if (gb.redirected) {                                                                                                  \
            DBG_CALL(dest);                                                                                                   \
            if (convertedFunc[gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE))])   \
                convertedFunc[gb.cpu_reg.pc + (gb.cpu_reg.pc < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE))](); \
            else                                                                                                              \
                gb_run_frame();                                                                                               \
            DBG_RET(dest);                                                                                                    \
            POP_PC;                                                                                                           \
        }                                                                                                                     \
    } while (0)

#define INC_FLAGS(x)                                \
    do {                                            \
        gb.cpu_reg.f_bits.z = ((x) == 0x00);        \
        gb.cpu_reg.f_bits.n = 0;                    \
        gb.cpu_reg.f_bits.h = (((x)&0x0F) == 0x00); \
        INC_PC(1)                                   \
    } while (0)

#define INC_A                    \
    do {                         \
        gb.cpu_reg.a++;          \
        INC_FLAGS(gb.cpu_reg.a); \
    } while (0)

#define INC_B                    \
    do {                         \
        gb.cpu_reg.b++;          \
        INC_FLAGS(gb.cpu_reg.b); \
    } while (0)

#define INC_C                    \
    do {                         \
        gb.cpu_reg.c++;          \
        INC_FLAGS(gb.cpu_reg.c); \
    } while (0)

#define INC_D                    \
    do {                         \
        gb.cpu_reg.d++;          \
        INC_FLAGS(gb.cpu_reg.d); \
    } while (0)

#define INC_E                    \
    do {                         \
        gb.cpu_reg.e++;          \
        INC_FLAGS(gb.cpu_reg.e); \
    } while (0)

#define INC_H                    \
    do {                         \
        gb.cpu_reg.h++;          \
        INC_FLAGS(gb.cpu_reg.h); \
    } while (0)

#define INC_L                    \
    do {                         \
        gb.cpu_reg.l++;          \
        INC_FLAGS(gb.cpu_reg.l); \
    } while (0)

#define INC_hl                         \
    do {                               \
        uint8_t temp = reg_hl_ + 1;    \
        INC_FLAGS(temp);               \
        gb_write(gb.cpu_reg.hl, temp); \
    } while (0)

#define INC_BC           \
    do {                 \
        gb.cpu_reg.bc++; \
        INC_PC(1)        \
    } while (0)

#define INC_DE           \
    do {                 \
        gb.cpu_reg.de++; \
        INC_PC(1)        \
    } while (0)

#define INC_HL           \
    do {                 \
        gb.cpu_reg.hl++; \
        INC_PC(1)        \
    } while (0)

#define INC_SP           \
    do {                 \
        gb.cpu_reg.sp++; \
        INC_PC(1)        \
    } while (0)

#define DEC_FLAGS(x)                                \
    do {                                            \
        gb.cpu_reg.f_bits.z = ((x) == 0x00);        \
        gb.cpu_reg.f_bits.n = 1;                    \
        gb.cpu_reg.f_bits.h = (((x)&0x0F) == 0x0F); \
        INC_PC(1)                                   \
    } while (0)

#define DEC_A                    \
    do {                         \
        gb.cpu_reg.a--;          \
        DEC_FLAGS(gb.cpu_reg.a); \
    } while (0)

#define DEC_B                    \
    do {                         \
        gb.cpu_reg.b--;          \
        DEC_FLAGS(gb.cpu_reg.b); \
    } while (0)

#define DEC_C                    \
    do {                         \
        gb.cpu_reg.c--;          \
        DEC_FLAGS(gb.cpu_reg.c); \
    } while (0)

#define DEC_D                    \
    do {                         \
        gb.cpu_reg.d--;          \
        DEC_FLAGS(gb.cpu_reg.d); \
    } while (0)

#define DEC_E                    \
    do {                         \
        gb.cpu_reg.e--;          \
        DEC_FLAGS(gb.cpu_reg.e); \
    } while (0)

#define DEC_H                    \
    do {                         \
        gb.cpu_reg.h--;          \
        DEC_FLAGS(gb.cpu_reg.h); \
    } while (0)

#define DEC_L                    \
    do {                         \
        gb.cpu_reg.l--;          \
        DEC_FLAGS(gb.cpu_reg.l); \
    } while (0)

#define DEC_hl                         \
    do {                               \
        uint8_t temp = reg_hl_ - 1;    \
        DEC_FLAGS(temp);               \
        gb_write(gb.cpu_reg.hl, temp); \
    } while (0)

#define DEC_BC           \
    do {                 \
        gb.cpu_reg.bc--; \
        INC_PC(1)        \
    } while (0)

#define DEC_DE           \
    do {                 \
        gb.cpu_reg.de--; \
        INC_PC(1)        \
    } while (0)

#define DEC_HL           \
    do {                 \
        gb.cpu_reg.hl--; \
        INC_PC(1)        \
    } while (0)

#define DEC_SP           \
    do {                 \
        gb.cpu_reg.sp--; \
        INC_PC(1)        \
    } while (0)

#define ADD_(x)                                        \
    do {                                               \
        uint16_t temp = gb.cpu_reg.a + (x);            \
        gb.cpu_reg.f_bits.z = ((temp & 0xFF) == 0x00); \
        gb.cpu_reg.f_bits.n = 0;                       \
        gb.cpu_reg.f_bits.h = temp & 0x10 ? 1 : 0;     \
        gb.cpu_reg.f_bits.c = (temp & 0xFF00) ? 1 : 0; \
        gb.cpu_reg.a = (temp & 0xFF);                  \
        INC_PC(1)                                      \
    } while (0)

#define ADD_A_A             \
    do {                    \
        ADD_(gb.cpu_reg.a); \
    } while (0)

#define ADD_A_B             \
    do {                    \
        ADD_(gb.cpu_reg.b); \
    } while (0)

#define ADD_A_C             \
    do {                    \
        ADD_(gb.cpu_reg.c); \
    } while (0)

#define ADD_A_D             \
    do {                    \
        ADD_(gb.cpu_reg.d); \
    } while (0)

#define ADD_A_E             \
    do {                    \
        ADD_(gb.cpu_reg.e); \
    } while (0)

#define ADD_A_H             \
    do {                    \
        ADD_(gb.cpu_reg.h); \
    } while (0)

#define ADD_A_L             \
    do {                    \
        ADD_(gb.cpu_reg.l); \
    } while (0)

#define ADD_A_hl       \
    do {               \
        ADD_(reg_hl_); \
    } while (0)

/* Taken from SameBoy, which is released under MIT Licence. */
#define ADD_A(x)                                                                     \
    do {                                                                             \
        uint8_t value = x;                                                           \
        uint16_t calc = gb.cpu_reg.a + value;                                        \
        gb.cpu_reg.f_bits.z = ((uint8_t)calc == 0) ? 1 : 0;                          \
        gb.cpu_reg.f_bits.h = ((gb.cpu_reg.a & 0xF) + (value & 0xF) > 0x0F) ? 1 : 0; \
        gb.cpu_reg.f_bits.c = calc > 0xFF ? 1 : 0;                                   \
        gb.cpu_reg.f_bits.n = 0;                                                     \
        gb.cpu_reg.a = (uint8_t)calc;                                                \
        INC_PC(2)                                                                    \
    } while (0)

#define ADC_(x)                                                           \
    do {                                                                  \
        uint16_t temp = gb.cpu_reg.a + (x) + gb.cpu_reg.f_bits.c;         \
        gb.cpu_reg.f_bits.z = ((temp & 0xFF) == 0x00);                    \
        gb.cpu_reg.f_bits.n = 0;                                          \
        gb.cpu_reg.f_bits.h = (gb.cpu_reg.a ^ (x) ^ temp) & 0x10 ? 1 : 0; \
        gb.cpu_reg.f_bits.c = (temp & 0xFF00) ? 1 : 0;                    \
        gb.cpu_reg.a = (temp & 0xFF);                                     \
        INC_PC(1)                                                         \
    } while (0)

#define ADC_A_A             \
    do {                    \
        ADC_(gb.cpu_reg.a); \
    } while (0)

#define ADC_A_B             \
    do {                    \
        ADC_(gb.cpu_reg.b); \
    } while (0)

#define ADC_A_C             \
    do {                    \
        ADC_(gb.cpu_reg.c); \
    } while (0)

#define ADC_A_D             \
    do {                    \
        ADC_(gb.cpu_reg.d); \
    } while (0)

#define ADC_A_E             \
    do {                    \
        ADC_(gb.cpu_reg.e); \
    } while (0)

#define ADC_A_H             \
    do {                    \
        ADC_(gb.cpu_reg.h); \
    } while (0)

#define ADC_A_L             \
    do {                    \
        ADC_(gb.cpu_reg.l); \
    } while (0)

#define ADC_A_hl       \
    do {               \
        ADC_(reg_hl_); \
    } while (0)

#define ADC_A(x)                                                                          \
    do {                                                                                  \
        uint8_t value, a, carry;                                                          \
        value = x;                                                                        \
        a = gb.cpu_reg.a;                                                                 \
        carry = gb.cpu_reg.f_bits.c;                                                      \
        gb.cpu_reg.a = a + value + carry;                                                 \
        gb.cpu_reg.f_bits.z = gb.cpu_reg.a == 0 ? 1 : 0;                                  \
        gb.cpu_reg.f_bits.h = ((a & 0xF) + (value & 0xF) + carry > 0x0F) ? 1 : 0;         \
        gb.cpu_reg.f_bits.c = (((uint16_t)a) + ((uint16_t)value) + carry > 0xFF) ? 1 : 0; \
        gb.cpu_reg.f_bits.n = 0;                                                          \
        INC_PC(2)                                                                         \
    } while (0)

#define SUB_(x)                                                           \
    do {                                                                  \
        uint16_t temp = gb.cpu_reg.a - (x);                               \
        gb.cpu_reg.f_bits.z = ((temp & 0xFF) == 0x00);                    \
        gb.cpu_reg.f_bits.n = 1;                                          \
        gb.cpu_reg.f_bits.h = (gb.cpu_reg.a ^ (x) ^ temp) & 0x10 ? 1 : 0; \
        gb.cpu_reg.f_bits.c = (temp & 0xFF00) ? 1 : 0;                    \
        gb.cpu_reg.a = (temp & 0xFF);                                     \
        INC_PC(1)                                                         \
    } while (0)

#define SUB_A_A             \
    do {                    \
        SUB_(gb.cpu_reg.a); \
    } while (0)

#define SUB_A_B             \
    do {                    \
        SUB_(gb.cpu_reg.b); \
    } while (0)

#define SUB_A_C             \
    do {                    \
        SUB_(gb.cpu_reg.c); \
    } while (0)

#define SUB_A_D             \
    do {                    \
        SUB_(gb.cpu_reg.d); \
    } while (0)

#define SUB_A_E             \
    do {                    \
        SUB_(gb.cpu_reg.e); \
    } while (0)

#define SUB_A_H             \
    do {                    \
        SUB_(gb.cpu_reg.h); \
    } while (0)

#define SUB_A_L             \
    do {                    \
        SUB_(gb.cpu_reg.l); \
    } while (0)

#define SUB_A_hl       \
    do {               \
        SUB_(reg_hl_); \
    } while (0)

#define SUB_A(x)                                                          \
    do {                                                                  \
        uint8_t val = x;                                                  \
        uint16_t temp = gb.cpu_reg.a - val;                               \
        gb.cpu_reg.f_bits.z = ((temp & 0xFF) == 0x00);                    \
        gb.cpu_reg.f_bits.n = 1;                                          \
        gb.cpu_reg.f_bits.h = (gb.cpu_reg.a ^ val ^ temp) & 0x10 ? 1 : 0; \
        gb.cpu_reg.f_bits.c = (temp & 0xFF00) ? 1 : 0;                    \
        gb.cpu_reg.a = (temp & 0xFF);                                     \
        INC_PC(2)                                                         \
    } while (0)

#define SBC_(x)                                                           \
    do {                                                                  \
        uint16_t temp = gb.cpu_reg.a - (x)-gb.cpu_reg.f_bits.c;           \
        gb.cpu_reg.f_bits.z = ((temp & 0xFF) == 0x00);                    \
        gb.cpu_reg.f_bits.n = 1;                                          \
        gb.cpu_reg.f_bits.h = (gb.cpu_reg.a ^ (x) ^ temp) & 0x10 ? 1 : 0; \
        gb.cpu_reg.f_bits.c = (temp & 0xFF00) ? 1 : 0;                    \
        gb.cpu_reg.a = (temp & 0xFF);                                     \
        INC_PC(1)                                                         \
    } while (0)

#define SBC_A_A             \
    do {                    \
        SBC_(gb.cpu_reg.a); \
    } while (0)

#define SBC_A_B             \
    do {                    \
        SBC_(gb.cpu_reg.b); \
    } while (0)

#define SBC_A_C             \
    do {                    \
        SBC_(gb.cpu_reg.c); \
    } while (0)

#define SBC_A_D             \
    do {                    \
        SBC_(gb.cpu_reg.d); \
    } while (0)

#define SBC_A_E             \
    do {                    \
        SBC_(gb.cpu_reg.e); \
    } while (0)

#define SBC_A_H             \
    do {                    \
        SBC_(gb.cpu_reg.h); \
    } while (0)

#define SBC_A_L             \
    do {                    \
        SBC_(gb.cpu_reg.l); \
    } while (0)

#define SBC_A_hl       \
    do {               \
        SBC_(reg_hl_); \
    } while (0)

#define SBC_A(x)                                                                \
    do {                                                                        \
        uint8_t temp_8 = x;                                                     \
        uint16_t temp_16 = gb.cpu_reg.a - temp_8 - gb.cpu_reg.f_bits.c;         \
        gb.cpu_reg.f_bits.z = ((temp_16 & 0xFF) == 0x00);                       \
        gb.cpu_reg.f_bits.n = 1;                                                \
        gb.cpu_reg.f_bits.h = (gb.cpu_reg.a ^ temp_8 ^ temp_16) & 0x10 ? 1 : 0; \
        gb.cpu_reg.f_bits.c = (temp_16 & 0xFF00) ? 1 : 0;                       \
        gb.cpu_reg.a = (temp_16 & 0xFF);                                        \
        INC_PC(2)                                                               \
    } while (0)

#define AND_(x)                                       \
    do {                                              \
        gb.cpu_reg.a = gb.cpu_reg.a & (x);            \
        gb.cpu_reg.f_bits.z = (gb.cpu_reg.a == 0x00); \
        gb.cpu_reg.f_bits.n = 0;                      \
        gb.cpu_reg.f_bits.h = 1;                      \
        gb.cpu_reg.f_bits.c = 0;                      \
        INC_PC(1)                                     \
    } while (0)

#define AND_A_A             \
    do {                    \
        AND_(gb.cpu_reg.a); \
    } while (0)

#define AND_A_B             \
    do {                    \
        AND_(gb.cpu_reg.b); \
    } while (0)

#define AND_A_C             \
    do {                    \
        AND_(gb.cpu_reg.c); \
    } while (0)

#define AND_A_D             \
    do {                    \
        AND_(gb.cpu_reg.d); \
    } while (0)

#define AND_A_E             \
    do {                    \
        AND_(gb.cpu_reg.e); \
    } while (0)

#define AND_A_H             \
    do {                    \
        AND_(gb.cpu_reg.h); \
    } while (0)

#define AND_A_L             \
    do {                    \
        AND_(gb.cpu_reg.l); \
    } while (0)

#define AND_A_hl       \
    do {               \
        AND_(reg_hl_); \
    } while (0)

#define AND_A(x)                                      \
    do {                                              \
        gb.cpu_reg.a = gb.cpu_reg.a & (x);            \
        gb.cpu_reg.f_bits.z = (gb.cpu_reg.a == 0x00); \
        gb.cpu_reg.f_bits.n = 0;                      \
        gb.cpu_reg.f_bits.h = 1;                      \
        gb.cpu_reg.f_bits.c = 0;                      \
        INC_PC(2)                                     \
    } while (0)

#define XOR_(x)                                       \
    do {                                              \
        gb.cpu_reg.a = gb.cpu_reg.a ^ (x);            \
        gb.cpu_reg.f_bits.z = (gb.cpu_reg.a == 0x00); \
        gb.cpu_reg.f_bits.n = 0;                      \
        gb.cpu_reg.f_bits.h = 0;                      \
        gb.cpu_reg.f_bits.c = 0;                      \
        INC_PC(1)                                     \
    } while (0)

#define XOR_A_A             \
    do {                    \
        XOR_(gb.cpu_reg.a); \
    } while (0)

#define XOR_A_B             \
    do {                    \
        XOR_(gb.cpu_reg.b); \
    } while (0)

#define XOR_A_C             \
    do {                    \
        XOR_(gb.cpu_reg.c); \
    } while (0)

#define XOR_A_D             \
    do {                    \
        XOR_(gb.cpu_reg.d); \
    } while (0)

#define XOR_A_E             \
    do {                    \
        XOR_(gb.cpu_reg.e); \
    } while (0)

#define XOR_A_H             \
    do {                    \
        XOR_(gb.cpu_reg.h); \
    } while (0)

#define XOR_A_L             \
    do {                    \
        XOR_(gb.cpu_reg.l); \
    } while (0)

#define XOR_A_hl       \
    do {               \
        XOR_(reg_hl_); \
    } while (0)

#define XOR_A(x)                                      \
    do {                                              \
        gb.cpu_reg.a = gb.cpu_reg.a ^ (x);            \
        gb.cpu_reg.f_bits.z = (gb.cpu_reg.a == 0x00); \
        gb.cpu_reg.f_bits.n = 0;                      \
        gb.cpu_reg.f_bits.h = 0;                      \
        gb.cpu_reg.f_bits.c = 0;                      \
        INC_PC(2)                                     \
    } while (0)

#define OR_(x)                                        \
    do {                                              \
        gb.cpu_reg.a = gb.cpu_reg.a | (x);            \
        gb.cpu_reg.f_bits.z = (gb.cpu_reg.a == 0x00); \
        gb.cpu_reg.f_bits.n = 0;                      \
        gb.cpu_reg.f_bits.h = 0;                      \
        gb.cpu_reg.f_bits.c = 0;                      \
        INC_PC(1)                                     \
    } while (0)

#define OR_A_A             \
    do {                   \
        OR_(gb.cpu_reg.a); \
    } while (0)

#define OR_A_B             \
    do {                   \
        OR_(gb.cpu_reg.b); \
    } while (0)

#define OR_A_C             \
    do {                   \
        OR_(gb.cpu_reg.c); \
    } while (0)

#define OR_A_D             \
    do {                   \
        OR_(gb.cpu_reg.d); \
    } while (0)

#define OR_A_E             \
    do {                   \
        OR_(gb.cpu_reg.e); \
    } while (0)

#define OR_A_H             \
    do {                   \
        OR_(gb.cpu_reg.h); \
    } while (0)

#define OR_A_L             \
    do {                   \
        OR_(gb.cpu_reg.l); \
    } while (0)

#define OR_A_hl       \
    do {              \
        OR_(reg_hl_); \
    } while (0)

#define OR_A(x)                                       \
    do {                                              \
        gb.cpu_reg.a = gb.cpu_reg.a | (x);            \
        gb.cpu_reg.f_bits.z = (gb.cpu_reg.a == 0x00); \
        gb.cpu_reg.f_bits.n = 0;                      \
        gb.cpu_reg.f_bits.h = 0;                      \
        gb.cpu_reg.f_bits.c = 0;                      \
        INC_PC(2)                                     \
    } while (0)

#define CP_(x)                                                            \
    do {                                                                  \
        uint16_t temp = gb.cpu_reg.a - (x);                               \
        gb.cpu_reg.f_bits.z = ((temp & 0xFF) == 0x00);                    \
        gb.cpu_reg.f_bits.n = 1;                                          \
        gb.cpu_reg.f_bits.h = (gb.cpu_reg.a ^ (x) ^ temp) & 0x10 ? 1 : 0; \
        gb.cpu_reg.f_bits.c = (temp & 0xFF00) ? 1 : 0;                    \
        INC_PC(1)                                                         \
    } while (0)

#define CP_A_A             \
    do {                   \
        CP_(gb.cpu_reg.a); \
    } while (0)

#define CP_A_B             \
    do {                   \
        CP_(gb.cpu_reg.b); \
    } while (0)

#define CP_A_C             \
    do {                   \
        CP_(gb.cpu_reg.c); \
    } while (0)

#define CP_A_D             \
    do {                   \
        CP_(gb.cpu_reg.d); \
    } while (0)

#define CP_A_E             \
    do {                   \
        CP_(gb.cpu_reg.e); \
    } while (0)

#define CP_A_H             \
    do {                   \
        CP_(gb.cpu_reg.h); \
    } while (0)

#define CP_A_L             \
    do {                   \
        CP_(gb.cpu_reg.l); \
    } while (0)

#define CP_A_hl       \
    do {              \
        CP_(reg_hl_); \
    } while (0)

#define CP_A(x)                                                                   \
    do {                                                                          \
        uint8_t temp_8 = x;                                                       \
        uint16_t temp_16 = gb.cpu_reg.a - temp_8;                                 \
        gb.cpu_reg.f_bits.z = ((temp_16 & 0xFF) == 0x00);                         \
        gb.cpu_reg.f_bits.n = 1;                                                  \
        gb.cpu_reg.f_bits.h = ((gb.cpu_reg.a ^ temp_8 ^ temp_16) & 0x10) ? 1 : 0; \
        gb.cpu_reg.f_bits.c = (temp_16 & 0xFF00) ? 1 : 0;                         \
        INC_PC(2)                                                                 \
    } while (0)

#define DAA                                                       \
    do {                                                          \
        uint16_t a = gb.cpu_reg.a;                                \
        if (gb.cpu_reg.f_bits.n) {                                \
            if (gb.cpu_reg.f_bits.h) a = (a - 0x06) & 0xFF;       \
            if (gb.cpu_reg.f_bits.c) a -= 0x60;                   \
        } else {                                                  \
            if (gb.cpu_reg.f_bits.h || (a & 0x0F) > 9) a += 0x06; \
            if (gb.cpu_reg.f_bits.c || a > 0x9F) a += 0x60;       \
        }                                                         \
        if ((a & 0x100) == 0x100) gb.cpu_reg.f_bits.c = 1;        \
        gb.cpu_reg.a = a;                                         \
        gb.cpu_reg.f_bits.z = (gb.cpu_reg.a == 0);                \
        gb.cpu_reg.f_bits.h = 0;                                  \
        INC_PC(1)                                                 \
    } while (0)

#define ADD_HL_(x)                                                           \
    do {                                                                     \
        uint_fast32_t temp = gb.cpu_reg.hl + (x);                            \
        gb.cpu_reg.f_bits.n = 0;                                             \
        gb.cpu_reg.f_bits.h = (temp ^ gb.cpu_reg.hl ^ (x)) & 0x1000 ? 1 : 0; \
        gb.cpu_reg.f_bits.c = (temp & 0xFFFF0000) ? 1 : 0;                   \
        gb.cpu_reg.hl = (temp & 0x0000FFFF);                                 \
        INC_PC(1)                                                            \
    } while (0)

#define ADD_HL_BC               \
    do {                        \
        ADD_HL_(gb.cpu_reg.bc); \
    } while (0)

#define ADD_HL_DE               \
    do {                        \
        ADD_HL_(gb.cpu_reg.de); \
    } while (0)

#define ADD_HL_HL               \
    do {                        \
        ADD_HL_(gb.cpu_reg.hl); \
    } while (0)

#define ADD_HL_SP                                                                                   \
    do {                                                                                            \
        uint_fast32_t temp = gb.cpu_reg.hl + gb.cpu_reg.sp;                                         \
        gb.cpu_reg.f_bits.n = 0;                                                                    \
        gb.cpu_reg.f_bits.h = ((gb.cpu_reg.hl & 0xFFF) + (gb.cpu_reg.sp & 0xFFF)) & 0x1000 ? 1 : 0; \
        gb.cpu_reg.f_bits.c = temp & 0x10000 ? 1 : 0;                                               \
        gb.cpu_reg.hl = (uint16_t)temp;                                                             \
        INC_PC(1)                                                                                   \
    } while (0)

#define ADD_SP(x)                                                                     \
    do {                                                                              \
        int8_t offset = (int8_t)x;                                                    \
        gb.cpu_reg.f_bits.z = 0;                                                      \
        gb.cpu_reg.f_bits.n = 0;                                                      \
        gb.cpu_reg.f_bits.h = ((gb.cpu_reg.sp & 0xF) + (offset & 0xF) > 0xF) ? 1 : 0; \
        gb.cpu_reg.f_bits.c = ((gb.cpu_reg.sp & 0xFF) + (offset & 0xFF) > 0xFF);      \
        gb.cpu_reg.sp += offset;                                                      \
        INC_PC(2)                                                                     \
    } while (0)

#define SCF                      \
    do {                         \
        gb.cpu_reg.f_bits.n = 0; \
        gb.cpu_reg.f_bits.h = 0; \
        gb.cpu_reg.f_bits.c = 1; \
        INC_PC(1)                \
    } while (0)

#define CCF                       \
    do {                          \
        gb.cpu_reg.f_bits.n = 0;  \
        gb.cpu_reg.f_bits.h = 0;  \
        gb.cpu_reg.f_bits.c ^= 1; \
        INC_PC(1)                 \
    } while (0)

#define CPL                           \
    do {                              \
        gb.cpu_reg.a = ~gb.cpu_reg.a; \
        gb.cpu_reg.f_bits.n = 1;      \
        gb.cpu_reg.f_bits.h = 1;      \
        INC_PC(1)                     \
    } while (0)

#define LD_addr_SP(x)                           \
    do {                                        \
        uint16_t temp = x;                      \
        gb_write(temp++, gb.cpu_reg.sp & 0xFF); \
        gb_write(temp, gb.cpu_reg.sp >> 8);     \
        INC_PC(3)                               \
    } while (0)

#define RLCA                                                      \
    do {                                                          \
        gb.cpu_reg.a = (gb.cpu_reg.a << 1) | (gb.cpu_reg.a >> 7); \
        gb.cpu_reg.f_bits.z = 0;                                  \
        gb.cpu_reg.f_bits.n = 0;                                  \
        gb.cpu_reg.f_bits.h = 0;                                  \
        gb.cpu_reg.f_bits.c = (gb.cpu_reg.a & 0x01);              \
        INC_PC(1)                                                 \
    } while (0)

#define RRCA                                                      \
    do {                                                          \
        gb.cpu_reg.f_bits.c = gb.cpu_reg.a & 0x01;                \
        gb.cpu_reg.a = (gb.cpu_reg.a >> 1) | (gb.cpu_reg.a << 7); \
        gb.cpu_reg.f_bits.z = 0;                                  \
        gb.cpu_reg.f_bits.n = 0;                                  \
        gb.cpu_reg.f_bits.h = 0;                                  \
        INC_PC(1)                                                 \
    } while (0)

#define RLA                                                       \
    do {                                                          \
        uint8_t temp = gb.cpu_reg.a;                              \
        gb.cpu_reg.a = (gb.cpu_reg.a << 1) | gb.cpu_reg.f_bits.c; \
        gb.cpu_reg.f_bits.z = 0;                                  \
        gb.cpu_reg.f_bits.n = 0;                                  \
        gb.cpu_reg.f_bits.h = 0;                                  \
        gb.cpu_reg.f_bits.c = (temp >> 7) & 0x01;                 \
        INC_PC(1)                                                 \
    } while (0)

#define RRA                                                            \
    do {                                                               \
        uint8_t temp = gb.cpu_reg.a;                                   \
        gb.cpu_reg.a = gb.cpu_reg.a >> 1 | (gb.cpu_reg.f_bits.c << 7); \
        gb.cpu_reg.f_bits.z = 0;                                       \
        gb.cpu_reg.f_bits.n = 0;                                       \
        gb.cpu_reg.f_bits.h = 0;                                       \
        gb.cpu_reg.f_bits.c = temp & 0x1;                              \
        INC_PC(1)                                                      \
    } while (0)

#define LD_addr_A(x)                 \
    do {                             \
        gb_write((x), gb.cpu_reg.a); \
        INC_PC(3)                    \
    } while (0)

#define LD_A_addr(x)               \
    do {                           \
        gb.cpu_reg.a = gb_read(x); \
        INC_PC(3)                  \
    } while (0)

#define LDH_addr_A(x)                \
    do {                             \
        gb_write((x), gb.cpu_reg.a); \
        INC_PC(2)                    \
    } while (0)

#define LDH_A_addr(x)              \
    do {                           \
        gb.cpu_reg.a = gb_read(x); \
        INC_PC(2)                  \
    } while (0)

#define LDH_c_A                                        \
    do {                                               \
        gb_write(0xFF00 + gb.cpu_reg.c, gb.cpu_reg.a); \
        INC_PC(1)                                      \
    } while (0)

#define LDH_A_c                                        \
    do {                                               \
        gb.cpu_reg.a = gb_read(0xFF00 + gb.cpu_reg.c); \
        INC_PC(1)                                      \
    } while (0)

/* Taken from SameBoy, which is released under MIT Licence. */
#define LD_HL_SP(x)                                                                      \
    do {                                                                                 \
        int8_t offset = x;                                                               \
        gb.cpu_reg.hl = gb.cpu_reg.sp + offset;                                          \
        gb.cpu_reg.f_bits.z = 0;                                                         \
        gb.cpu_reg.f_bits.n = 0;                                                         \
        gb.cpu_reg.f_bits.h = ((gb.cpu_reg.sp & 0xF) + (offset & 0xF) > 0xF) ? 1 : 0;    \
        gb.cpu_reg.f_bits.c = ((gb.cpu_reg.sp & 0xFF) + (offset & 0xFF) > 0xFF) ? 1 : 0; \
        INC_PC(2)                                                                        \
    } while (0)

// CB Prefixed opcodes
#define ROT_FLAG(val, carry)                 \
    do {                                     \
        gb.cpu_reg.f_bits.z = (val == 0x00); \
        gb.cpu_reg.f_bits.n = 0;             \
        gb.cpu_reg.f_bits.h = 0;             \
        gb.cpu_reg.f_bits.c = carry;         \
        INC_PC(2)                            \
    } while (0)

#define RL_B                                 \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.b >> 7); \
        gb.cpu_reg.b <<= 1;                  \
        gb.cpu_reg.b += gb.cpu_reg.f_bits.c; \
        ROT_FLAG(gb.cpu_reg.b, carry);       \
    } while (0)

#define RL_C                                 \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.c >> 7); \
        gb.cpu_reg.c <<= 1;                  \
        gb.cpu_reg.c += gb.cpu_reg.f_bits.c; \
        ROT_FLAG(gb.cpu_reg.c, carry);       \
    } while (0)

#define RL_D                                 \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.d >> 7); \
        gb.cpu_reg.d <<= 1;                  \
        gb.cpu_reg.d += gb.cpu_reg.f_bits.c; \
        ROT_FLAG(gb.cpu_reg.d, carry);       \
    } while (0)

#define RL_E                                 \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.e >> 7); \
        gb.cpu_reg.e <<= 1;                  \
        gb.cpu_reg.e += gb.cpu_reg.f_bits.c; \
        ROT_FLAG(gb.cpu_reg.e, carry);       \
    } while (0)

#define RL_H                                 \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.h >> 7); \
        gb.cpu_reg.h <<= 1;                  \
        gb.cpu_reg.h += gb.cpu_reg.f_bits.c; \
        ROT_FLAG(gb.cpu_reg.h, carry);       \
    } while (0)

#define RL_L                                 \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.l >> 7); \
        gb.cpu_reg.l <<= 1;                  \
        gb.cpu_reg.l += gb.cpu_reg.f_bits.c; \
        ROT_FLAG(gb.cpu_reg.l, carry);       \
    } while (0)

#define RL_A                                 \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.a >> 7); \
        gb.cpu_reg.a <<= 1;                  \
        gb.cpu_reg.a += gb.cpu_reg.f_bits.c; \
        ROT_FLAG(gb.cpu_reg.a, carry);       \
    } while (0)

#define RL_hl                                  \
    do {                                       \
        uint8_t temp = gb_read(gb.cpu_reg.hl); \
        uint8_t carry = (temp >> 7);           \
        temp <<= 1;                            \
        temp += gb.cpu_reg.f_bits.c;           \
        ROT_FLAG(temp, carry);                 \
        gb_write(gb.cpu_reg.hl, temp);         \
    } while (0)

#define RLC_B                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.b >> 7); \
        gb.cpu_reg.b <<= 1;                  \
        gb.cpu_reg.b += carry;               \
        ROT_FLAG(gb.cpu_reg.b, carry);       \
    } while (0)

#define RLC_C                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.c >> 7); \
        gb.cpu_reg.c <<= 1;                  \
        gb.cpu_reg.c += carry;               \
        ROT_FLAG(gb.cpu_reg.c, carry);       \
    } while (0)

#define RLC_D                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.d >> 7); \
        gb.cpu_reg.d <<= 1;                  \
        gb.cpu_reg.d += carry;               \
        ROT_FLAG(gb.cpu_reg.d, carry);       \
    } while (0)

#define RLC_E                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.e >> 7); \
        gb.cpu_reg.e <<= 1;                  \
        gb.cpu_reg.e += carry;               \
        ROT_FLAG(gb.cpu_reg.e, carry);       \
    } while (0)

#define RLC_H                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.h >> 7); \
        gb.cpu_reg.h <<= 1;                  \
        gb.cpu_reg.h += carry;               \
        ROT_FLAG(gb.cpu_reg.h, carry);       \
    } while (0)

#define RLC_L                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.l >> 7); \
        gb.cpu_reg.l <<= 1;                  \
        gb.cpu_reg.l += carry;               \
        ROT_FLAG(gb.cpu_reg.l, carry);       \
    } while (0)

#define RLC_A                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.a >> 7); \
        gb.cpu_reg.a <<= 1;                  \
        gb.cpu_reg.a += carry;               \
        ROT_FLAG(gb.cpu_reg.a, carry);       \
    } while (0)

#define RLC_hl                                 \
    do {                                       \
        uint8_t temp = gb_read(gb.cpu_reg.hl); \
        uint8_t carry = (temp >> 7);           \
        temp <<= 1;                            \
        temp += carry;                         \
        ROT_FLAG(temp, carry);                 \
        gb_write(gb.cpu_reg.hl, temp);         \
    } while (0)

#define RR_B                                        \
    do {                                            \
        uint8_t carry = (gb.cpu_reg.b & 1);         \
        gb.cpu_reg.b >>= 1;                         \
        gb.cpu_reg.b += (gb.cpu_reg.f_bits.c << 7); \
        ROT_FLAG(gb.cpu_reg.b, carry);              \
    } while (0)

#define RR_C                                        \
    do {                                            \
        uint8_t carry = (gb.cpu_reg.c & 1);         \
        gb.cpu_reg.c >>= 1;                         \
        gb.cpu_reg.c += (gb.cpu_reg.f_bits.c << 7); \
        ROT_FLAG(gb.cpu_reg.c, carry);              \
    } while (0)

#define RR_D                                        \
    do {                                            \
        uint8_t carry = (gb.cpu_reg.d & 1);         \
        gb.cpu_reg.d >>= 1;                         \
        gb.cpu_reg.d += (gb.cpu_reg.f_bits.c << 7); \
        ROT_FLAG(gb.cpu_reg.d, carry);              \
    } while (0)

#define RR_E                                        \
    do {                                            \
        uint8_t carry = (gb.cpu_reg.e & 1);         \
        gb.cpu_reg.e >>= 1;                         \
        gb.cpu_reg.e += (gb.cpu_reg.f_bits.c << 7); \
        ROT_FLAG(gb.cpu_reg.e, carry);              \
    } while (0)

#define RR_H                                        \
    do {                                            \
        uint8_t carry = (gb.cpu_reg.h & 1);         \
        gb.cpu_reg.h >>= 1;                         \
        gb.cpu_reg.h += (gb.cpu_reg.f_bits.c << 7); \
        ROT_FLAG(gb.cpu_reg.h, carry);              \
    } while (0)

#define RR_L                                        \
    do {                                            \
        uint8_t carry = (gb.cpu_reg.l & 1);         \
        gb.cpu_reg.l >>= 1;                         \
        gb.cpu_reg.l += (gb.cpu_reg.f_bits.c << 7); \
        ROT_FLAG(gb.cpu_reg.l, carry);              \
    } while (0)

#define RR_A                                        \
    do {                                            \
        uint8_t carry = (gb.cpu_reg.a & 1);         \
        gb.cpu_reg.a >>= 1;                         \
        gb.cpu_reg.a += (gb.cpu_reg.f_bits.c << 7); \
        ROT_FLAG(gb.cpu_reg.a, carry);              \
    } while (0)

#define RR_hl                                  \
    do {                                       \
        uint8_t temp = gb_read(gb.cpu_reg.hl); \
        uint8_t carry = (temp & 1);            \
        temp >>= 1;                            \
        temp += (gb.cpu_reg.f_bits.c << 7);    \
        ROT_FLAG(temp, carry);                 \
        gb_write(gb.cpu_reg.hl, temp);         \
    } while (0)

#define RRC_B                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.b & 1); \
        gb.cpu_reg.b >>= 1;                 \
        gb.cpu_reg.b += (carry << 7);       \
        ROT_FLAG(gb.cpu_reg.b, carry);      \
    } while (0)

#define RRC_C                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.c & 1); \
        gb.cpu_reg.c >>= 1;                 \
        gb.cpu_reg.c += (carry << 7);       \
        ROT_FLAG(gb.cpu_reg.c, carry);      \
    } while (0)

#define RRC_D                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.d & 1); \
        gb.cpu_reg.d >>= 1;                 \
        gb.cpu_reg.d += (carry << 7);       \
        ROT_FLAG(gb.cpu_reg.d, carry);      \
    } while (0)

#define RRC_E                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.e & 1); \
        gb.cpu_reg.e >>= 1;                 \
        gb.cpu_reg.e += (carry << 7);       \
        ROT_FLAG(gb.cpu_reg.e, carry);      \
    } while (0)

#define RRC_H                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.h & 1); \
        gb.cpu_reg.h >>= 1;                 \
        gb.cpu_reg.h += (carry << 7);       \
        ROT_FLAG(gb.cpu_reg.h, carry);      \
    } while (0)

#define RRC_L                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.l & 1); \
        gb.cpu_reg.l >>= 1;                 \
        gb.cpu_reg.l += (carry << 7);       \
        ROT_FLAG(gb.cpu_reg.l, carry);      \
    } while (0)

#define RRC_A                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.a & 1); \
        gb.cpu_reg.a >>= 1;                 \
        gb.cpu_reg.a += (carry << 7);       \
        ROT_FLAG(gb.cpu_reg.a, carry);      \
    } while (0)

#define RRC_hl                                 \
    do {                                       \
        uint8_t temp = gb_read(gb.cpu_reg.hl); \
        uint8_t carry = (temp & 1);            \
        temp >>= 1;                            \
        temp += (carry << 7);                  \
        ROT_FLAG(temp, carry);                 \
        gb_write(gb.cpu_reg.hl, temp);         \
    } while (0)

#define SLA_B                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.b >> 7); \
        gb.cpu_reg.b <<= 1;                  \
        ROT_FLAG(gb.cpu_reg.b, carry);       \
    } while (0)

#define SLA_C                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.c >> 7); \
        gb.cpu_reg.c <<= 1;                  \
        ROT_FLAG(gb.cpu_reg.c, carry);       \
    } while (0)

#define SLA_D                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.d >> 7); \
        gb.cpu_reg.d <<= 1;                  \
        ROT_FLAG(gb.cpu_reg.d, carry);       \
    } while (0)

#define SLA_E                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.e >> 7); \
        gb.cpu_reg.e <<= 1;                  \
        ROT_FLAG(gb.cpu_reg.e, carry);       \
    } while (0)

#define SLA_H                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.h >> 7); \
        gb.cpu_reg.h <<= 1;                  \
        ROT_FLAG(gb.cpu_reg.h, carry);       \
    } while (0)

#define SLA_L                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.l >> 7); \
        gb.cpu_reg.l <<= 1;                  \
        ROT_FLAG(gb.cpu_reg.l, carry);       \
    } while (0)

#define SLA_A                                \
    do {                                     \
        uint8_t carry = (gb.cpu_reg.a >> 7); \
        gb.cpu_reg.a <<= 1;                  \
        ROT_FLAG(gb.cpu_reg.a, carry);       \
    } while (0)

#define SLA_hl                                 \
    do {                                       \
        uint8_t temp = gb_read(gb.cpu_reg.hl); \
        uint8_t carry = (temp >> 7);           \
        temp <<= 1;                            \
        ROT_FLAG(temp, carry);                 \
        gb_write(gb.cpu_reg.hl, temp);         \
    } while (0)

#define SRA_B                                         \
    do {                                              \
        uint8_t carry = (gb.cpu_reg.b & 1);           \
        gb.cpu_reg.b >>= 1;                           \
        gb.cpu_reg.b += ((gb.cpu_reg.b << 1) & 0x80); \
        ROT_FLAG(gb.cpu_reg.b, carry);                \
    } while (0)

#define SRA_C                                         \
    do {                                              \
        uint8_t carry = (gb.cpu_reg.c & 1);           \
        gb.cpu_reg.c >>= 1;                           \
        gb.cpu_reg.c += ((gb.cpu_reg.c << 1) & 0x80); \
        ROT_FLAG(gb.cpu_reg.c, carry);                \
    } while (0)

#define SRA_D                                         \
    do {                                              \
        uint8_t carry = (gb.cpu_reg.d & 1);           \
        gb.cpu_reg.d >>= 1;                           \
        gb.cpu_reg.d += ((gb.cpu_reg.d << 1) & 0x80); \
        ROT_FLAG(gb.cpu_reg.d, carry);                \
    } while (0)

#define SRA_E                                         \
    do {                                              \
        uint8_t carry = (gb.cpu_reg.e & 1);           \
        gb.cpu_reg.e >>= 1;                           \
        gb.cpu_reg.e += ((gb.cpu_reg.e << 1) & 0x80); \
        ROT_FLAG(gb.cpu_reg.e, carry);                \
    } while (0)

#define SRA_H                                         \
    do {                                              \
        uint8_t carry = (gb.cpu_reg.h & 1);           \
        gb.cpu_reg.h >>= 1;                           \
        gb.cpu_reg.h += ((gb.cpu_reg.h << 1) & 0x80); \
        ROT_FLAG(gb.cpu_reg.h, carry);                \
    } while (0)

#define SRA_L                                         \
    do {                                              \
        uint8_t carry = (gb.cpu_reg.l & 1);           \
        gb.cpu_reg.l >>= 1;                           \
        gb.cpu_reg.l += ((gb.cpu_reg.l << 1) & 0x80); \
        ROT_FLAG(gb.cpu_reg.l, carry);                \
    } while (0)

#define SRA_A                                         \
    do {                                              \
        uint8_t carry = (gb.cpu_reg.a & 1);           \
        gb.cpu_reg.a >>= 1;                           \
        gb.cpu_reg.a += ((gb.cpu_reg.a << 1) & 0x80); \
        ROT_FLAG(gb.cpu_reg.a, carry);                \
    } while (0)

#define SRA_hl                                 \
    do {                                       \
        uint8_t temp = gb_read(gb.cpu_reg.hl); \
        uint8_t carry = (temp & 1);            \
        temp >>= 1;                            \
        temp += ((temp << 1) & 0x80);          \
        ROT_FLAG(temp, carry);                 \
        gb_write(gb.cpu_reg.hl, temp);         \
    } while (0)

#define SWAP_FLAGS(x)                        \
    do {                                     \
        gb.cpu_reg.f_bits.z = ((x) == 0x00); \
        gb.cpu_reg.f_bits.n = 0;             \
        gb.cpu_reg.f_bits.h = 0;             \
        gb.cpu_reg.f_bits.c = 0;             \
        INC_PC(2)                            \
    } while (0)

#define SWAP_B                              \
    do {                                    \
        uint8_t temp = (gb.cpu_reg.b << 4); \
        gb.cpu_reg.b >>= 4;                 \
        gb.cpu_reg.b |= temp;               \
        SWAP_FLAGS(gb.cpu_reg.b);           \
    } while (0)

#define SWAP_C                              \
    do {                                    \
        uint8_t temp = (gb.cpu_reg.c << 4); \
        gb.cpu_reg.c >>= 4;                 \
        gb.cpu_reg.c |= temp;               \
        SWAP_FLAGS(gb.cpu_reg.c);           \
    } while (0)

#define SWAP_D                              \
    do {                                    \
        uint8_t temp = (gb.cpu_reg.d << 4); \
        gb.cpu_reg.d >>= 4;                 \
        gb.cpu_reg.d |= temp;               \
        SWAP_FLAGS(gb.cpu_reg.d);           \
    } while (0)

#define SWAP_E                              \
    do {                                    \
        uint8_t temp = (gb.cpu_reg.e << 4); \
        gb.cpu_reg.e >>= 4;                 \
        gb.cpu_reg.e |= temp;               \
        SWAP_FLAGS(gb.cpu_reg.e);           \
    } while (0)

#define SWAP_H                              \
    do {                                    \
        uint8_t temp = (gb.cpu_reg.h << 4); \
        gb.cpu_reg.h >>= 4;                 \
        gb.cpu_reg.h |= temp;               \
        SWAP_FLAGS(gb.cpu_reg.h);           \
    } while (0)

#define SWAP_L                              \
    do {                                    \
        uint8_t temp = (gb.cpu_reg.l << 4); \
        gb.cpu_reg.l >>= 4;                 \
        gb.cpu_reg.l |= temp;               \
        SWAP_FLAGS(gb.cpu_reg.l);           \
    } while (0)

#define SWAP_A                              \
    do {                                    \
        uint8_t temp = (gb.cpu_reg.a << 4); \
        gb.cpu_reg.a >>= 4;                 \
        gb.cpu_reg.a |= temp;               \
        SWAP_FLAGS(gb.cpu_reg.a);           \
    } while (0)

#define SWAP_hl                               \
    do {                                      \
        uint8_t val = gb_read(gb.cpu_reg.hl); \
        uint8_t temp = (val << 4);            \
        val >>= 4;                            \
        val |= temp;                          \
        SWAP_FLAGS(val);                      \
        gb_write(gb.cpu_reg.hl, val);         \
    } while (0)

#define SRL_B                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.b & 1); \
        gb.cpu_reg.b >>= 1;                 \
        ROT_FLAG(gb.cpu_reg.b, carry);      \
    } while (0)

#define SRL_C                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.c & 1); \
        gb.cpu_reg.c >>= 1;                 \
        ROT_FLAG(gb.cpu_reg.c, carry);      \
    } while (0)

#define SRL_D                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.d & 1); \
        gb.cpu_reg.d >>= 1;                 \
        ROT_FLAG(gb.cpu_reg.d, carry);      \
    } while (0)

#define SRL_E                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.e & 1); \
        gb.cpu_reg.e >>= 1;                 \
        ROT_FLAG(gb.cpu_reg.e, carry);      \
    } while (0)

#define SRL_H                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.h & 1); \
        gb.cpu_reg.h >>= 1;                 \
        ROT_FLAG(gb.cpu_reg.h, carry);      \
    } while (0)

#define SRL_L                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.l & 1); \
        gb.cpu_reg.l >>= 1;                 \
        ROT_FLAG(gb.cpu_reg.l, carry);      \
    } while (0)

#define SRL_A                               \
    do {                                    \
        uint8_t carry = (gb.cpu_reg.a & 1); \
        gb.cpu_reg.a >>= 1;                 \
        ROT_FLAG(gb.cpu_reg.a, carry);      \
    } while (0)

#define SRL_hl                                 \
    do {                                       \
        uint8_t temp = gb_read(gb.cpu_reg.hl); \
        uint8_t carry = (temp & 1);            \
        temp >>= 1;                            \
        ROT_FLAG(temp, carry);                 \
        gb_write(gb.cpu_reg.hl, temp);         \
    } while (0)

#define BIT_(x, bit)                                   \
    do {                                               \
        uint8_t val = x;                               \
        gb.cpu_reg.f_bits.z = !((val >> (bit)) & 0x1); \
        gb.cpu_reg.f_bits.n = 0;                       \
        gb.cpu_reg.f_bits.h = 1;                       \
        INC_PC(2)                                      \
    } while (0)

#define BIT_B(bit)               \
    do {                         \
        BIT_(gb.cpu_reg.b, bit); \
    } while (0)

#define BIT_C(bit)               \
    do {                         \
        BIT_(gb.cpu_reg.c, bit); \
    } while (0)

#define BIT_D(bit)               \
    do {                         \
        BIT_(gb.cpu_reg.d, bit); \
    } while (0)

#define BIT_E(bit)               \
    do {                         \
        BIT_(gb.cpu_reg.e, bit); \
    } while (0)

#define BIT_H(bit)               \
    do {                         \
        BIT_(gb.cpu_reg.h, bit); \
    } while (0)

#define BIT_L(bit)               \
    do {                         \
        BIT_(gb.cpu_reg.l, bit); \
    } while (0)

#define BIT_A(bit)               \
    do {                         \
        BIT_(gb.cpu_reg.a, bit); \
    } while (0)

#define BIT_hl(bit)                        \
    do {                                   \
        BIT_(gb_read(gb.cpu_reg.hl), bit); \
    } while (0)

#define RES_(x, bit)                              \
    do {                                          \
        x &= (0xFE << bit) | (0xFF >> (8 - bit)); \
    } while (0)

#define RES_B(bit)                           \
    do {                                     \
        gb.cpu_reg.b &= ((1 << bit) ^ 0xFF); \
        INC_PC(2)                            \
    } while (0)

#define RES_C(bit)                           \
    do {                                     \
        gb.cpu_reg.c &= ((1 << bit) ^ 0xFF); \
        INC_PC(2)                            \
    } while (0)

#define RES_D(bit)                           \
    do {                                     \
        gb.cpu_reg.d &= ((1 << bit) ^ 0xFF); \
        INC_PC(2)                            \
    } while (0)

#define RES_E(bit)                           \
    do {                                     \
        gb.cpu_reg.e &= ((1 << bit) ^ 0xFF); \
        INC_PC(2)                            \
    } while (0)

#define RES_H(bit)                           \
    do {                                     \
        gb.cpu_reg.h &= ((1 << bit) ^ 0xFF); \
        INC_PC(2)                            \
    } while (0)

#define RES_L(bit)                           \
    do {                                     \
        gb.cpu_reg.l &= ((1 << bit) ^ 0xFF); \
        INC_PC(2)                            \
    } while (0)

#define RES_A(bit)                           \
    do {                                     \
        gb.cpu_reg.a &= ((1 << bit) ^ 0xFF); \
        INC_PC(2)                            \
    } while (0)

#define RES_hl(bit)                           \
    do {                                      \
        uint8_t val = gb_read(gb.cpu_reg.hl); \
        val &= ((1 << bit) ^ 0xFF);           \
        gb_write(gb.cpu_reg.hl, val);         \
        INC_PC(2)                             \
    } while (0)

#define SET_(x, bit)       \
    do {                   \
        x |= (0x1 << bit); \
    } while (0)

#define SET_B(bit)                  \
    do {                            \
        gb.cpu_reg.b |= (1 << bit); \
        INC_PC(2)                   \
    } while (0)

#define SET_C(bit)                  \
    do {                            \
        gb.cpu_reg.c |= (1 << bit); \
        INC_PC(2)                   \
    } while (0)

#define SET_D(bit)                  \
    do {                            \
        gb.cpu_reg.d |= (1 << bit); \
        INC_PC(2)                   \
    } while (0)

#define SET_E(bit)                  \
    do {                            \
        gb.cpu_reg.e |= (1 << bit); \
        INC_PC(2)                   \
    } while (0)

#define SET_H(bit)                  \
    do {                            \
        gb.cpu_reg.h |= (1 << bit); \
        INC_PC(2)                   \
    } while (0)

#define SET_L(bit)                  \
    do {                            \
        gb.cpu_reg.l |= (1 << bit); \
        INC_PC(2)                   \
    } while (0)

#define SET_A(bit)                  \
    do {                            \
        gb.cpu_reg.a |= (1 << bit); \
        INC_PC(2)                   \
    } while (0)

#define SET_hl(bit)                           \
    do {                                      \
        uint8_t val = gb_read(gb.cpu_reg.hl); \
        val |= (0x1 << bit);                  \
        gb_write(gb.cpu_reg.hl, val);         \
        INC_PC(2)                             \
    } while (0)

// Pokegold macros

#define BANK(x) ((x) >> 14)
#define MBANK(x) ((x) >> 16)
#define HIGH(x) (((x) >> 8) & 0xFF)
#define LOW(x) ((x)&0xFF)

#define FARCALL(x)                                           \
    do {                                                     \
        uint32_t val = x;                                    \
        LD_A(BANK(val));                                     \
        LD_HL((val & 0x3FFF) | (val < 0x4000 ? 0 : 0x4000)); \
        RST(mFarCall);                                       \
    } while (0)

#define CALLFAR(x)                                           \
    do {                                                     \
        uint32_t val = x;                                    \
        LD_HL((val & 0x3FFF) | (val < 0x4000 ? 0 : 0x4000)); \
        LD_A(BANK(val));                                     \
        RST(mFarCall);                                       \
    } while (0)

#define HOMECALL(x)                                         \
    do {                                                    \
        uint32_t val = x;                                   \
        LDH_A_addr(hROMBank);                               \
        PUSH_AF;                                            \
        LD_A(BANK(val));                                    \
        RST(mBankswitch);                                   \
        CALL((val & 0x3FFF) | (val < 0x4000 ? 0 : 0x4000)); \
        POP_AF;                                             \
        RST(mBankswitch);                                   \
    } while (0)

#define LDA_PREDEF(x) \
    do {              \
        LD_A(x);      \
    } while (0)

#define PREDEF(x)      \
    do {               \
        LDA_PREDEF(x); \
        CALL(mPredef); \
    } while (0)

#define PREDEF_JUMP(x) \
    do {               \
        LDA_PREDEF(x); \
        JP(mPredef);   \
    } while (0)

#define percent *0xFF / 100

#define maskbits(num, shift)                     \
    do {                                         \
        int x = 1;                               \
        for (int i = 0; i < 8; i++) {            \
            if (x + 1 < (num)) x = (x << 1) | 1; \
        }                                        \
        AND_(x << (shift));                      \
    } while (0)

#define jumptable(dest, value) \
    do {                       \
        LD_A_addr(value);      \
        LD_E_A;                \
	    LD_D(0);               \
	    LD_HL((uint16_t)(dest));\
	    ADD_HL_DE;             \
	    ADD_HL_DE;             \
	    LD_A_hli;              \
	    LD_H_hl;               \
	    LD_L_A;                \
	    JP_hl;                 \
    } while(0)

#define fast_jumptable(dest, value) \
    do {\
        uint16_t index = (uint16_t)gb_read(value);\
        REG_HL = gb_read16((uint16_t)dest + (2 * index));\
        JP_hl;\
    } while(0)

#define bank_push(bank) \
    uint8_t oldBank = gb_read(hROMBank);\
    Bankswitch_Conv(bank);

#define bank_pop Bankswitch_Conv(oldBank);

#define farcall(_x, ...) \
    do {                                                     \
        uint8_t oldBank = gb_read(hROMBank);                 \
        Bankswitch_Conv(BANK(a##_x));                        \
        _x##_Conv(__VA_ARGS__);                              \
        Bankswitch_Conv(oldBank);                            \
    } while (0)

#define bit_test(_x, _n) (((_x) >> (_n)) & 0x1)

#define calc_sin_wave \
    do {\
        AND_A(0b111111); \
	    CP_A(0b100000); \
	    IF_NC goto negative; \
	    CALL(apply); \
	    LD_A_H; \
        RET; \
    negative: \
        AND_A(0b011111); \
        CALL(apply); \
        LD_A_H; \
        XOR_A(0xff); \
        INC_A; \
        RET; \
    apply: \
	    LD_E_A; \
	    LD_A_D; \
	    LD_D(0); \
        LD_HL(Jumptable); \
    } while(0)
//#include "macros/coords.h"
//#include "macros/scripts/audio.h"
//#include "macros/scripts/text.h"

#endif

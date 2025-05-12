#include "../constants.h"
#include "decompress.h"

//  Decompress graphics data from a:hl to de.
void FarDecompress(uint8_t bank, uint16_t src, uint16_t dest){
    // gb_write(wLZBank, bank);
    bank_push(bank);

    Decompress_GB(dest, src);
    // REG_DE = dest;
    // REG_HL = src;
    // CALL(aDecompress);

    bank_pop;
}

//  Pokemon GSC uses an lz variant (lz3) for compression.
//  This is mainly (but not necessarily) used for graphics.
// 
//  This function decompresses lz-compressed data from hl to de.
void Decompress_GB(uint16_t de, uint16_t hl){
#define LZ_END (0xff)  //  Compressed data is terminated with $ff.

//  A typical control command consists of:

#define LZ_CMD (0b11100000)  //  command id (bits 5-7)
#define LZ_LEN (0b00011111)  //  length n   (bits 0-4)

//  Additional parameters are read during command execution.

//  Commands:

#define LZ_LITERAL (0 << 5)  //  Read literal data for n bytes.
#define LZ_ITERATE (1 << 5)  //  Write the same byte for n bytes.
#define LZ_ALTERNATE (2 << 5)  //  Alternate two bytes for n bytes.
#define LZ_ZERO     (3 << 5)  //  Write 0 for n bytes.

//  Another class of commands reuses data from the decompressed output.
#define LZ_RW (2 + 5)  //  bit

//  These commands take a signed offset to start copying from.
//  Wraparound is simulated.
//  Positive offsets (15-bit) are added to the start address.
//  Negative offsets (7-bit) are subtracted from the current position.

#define LZ_REPEAT (4 << 5)  //  Repeat n bytes from the offset.
#define LZ_FLIP (5 << 5)  //  Repeat n bitflipped bytes.
#define LZ_REVERSE (6 << 5)  //  Repeat n bytes in reverse.

//  If the value in the count needs to be larger than 5 bits,
//  LZ_LONG can be used to expand the count to 10 bits.
#define LZ_LONG (7 << 5)

//  A new control command is read in bits 2-4.
//  The top two bits of the length are bits 0-1.
//  Another byte is read containing the bottom 8 bits.
#define LZ_LONG_HI (0b00000011)

//  In other words, the structure of the command becomes
//  111xxxyy yyyyyyyy
//  x: the new control command
//  y: the length

//  For more information, refer to the code below and in extras/gfx.py.

// Save the output address
// for rewrite commands.
    // LD_A_E;
    // LD_addr_A(wLZAddress);
    // LD_A_D;
    // LD_addr_A(wLZAddress + 1);
    uint16_t LZAddress = de;
    uint8_t byte;

    // FILE* out = fopen("decompress_conv.bin", "ab");

    while(byte = gb_read(hl), byte != LZ_END) {
        // REG_DE = de;
        // REG_HL = hl;
        // PEEK("Loop");
        uint8_t ctrl;
        uint16_t cnt;
        // LD_A_hl;
        // CP_A(LZ_END);
        // RET_Z ;

        // AND_A(LZ_CMD);
        byte &= LZ_CMD;

        // CP_A(LZ_LONG);
        // IF_NZ goto l_short;
        if(byte == LZ_LONG) {
        //  The count is now 10 bits.

        // Read the next 3 bits.
        // %00011100 -> %11100000
            // LD_A_hl;
            // ADD_A_A;
            // ADD_A_A;  // << 3
            // ADD_A_A;

        // This is our new control code.
            // AND_A(LZ_CMD);
            // PUSH_AF;
            ctrl = (gb_read(hl) << 3) & LZ_CMD;

            // LD_A_hli;
            // AND_A(LZ_LONG_HI);
            // LD_B_A;
            // LD_A_hli;
            // LD_C_A;
            cnt = ((gb_read(hl + 0) & LZ_LONG_HI) << 8) | gb_read(hl + 1);
            hl += 2;


        // read at least 1 byte
            cnt++;
            // goto command;
        }
        else {
        // l_short:
            ctrl = byte;
            // PUSH_AF;

            // LD_A_hli;
            // AND_A(LZ_LEN);
            // LD_C_A;
            // LD_B(0);
            cnt = gb_read(hl++) & LZ_LEN;

        // read at least 1 byte
            // INC_C;
            cnt++;
        }

        // Increment loop counts.
    // We bail the moment they hit 0.
        // INC_B;
        // INC_C;
        // REG_B++, REG_C++;
        // cnt.lo++;


        // POP_AF;

        // BIT_A(LZ_RW);
        // IF_NZ goto rewrite;
        if(bit_test(ctrl, LZ_RW)) {
            //  Repeat decompressed data from output.
            // PUSH_HL;
            // PUSH_AF;
            uint16_t hltemp = hl;

            // LD_A_hli;
            // BIT_A(7);  // sign
            // IF_Z goto positive;
            uint8_t a = gb_read(hl++);
            if(!bit_test(a, 7)) {
                //  Positive offsets are two bytes.
                // LD_L_hl;
                // LD_H_A;
                // hl = ((uint16_t)a << 8) | gb_read(hl);
            // add to starting output address
                // LD_A_addr(wLZAddress);
                // ADD_A_L;
                // LD_L_A;
                // LD_A_addr(wLZAddress + 1);
                // ADC_A_H;
                // LD_H_A;
                hl = LZAddress + (uint16_t)(((uint16_t)(uint8_t)a) << 8 | gb_read(hl));
            }
            else {
            //  negative
            // hl = de + -a
                // AND_A(0b01111111);
                // CPL;
                // ADD_A_E;
                // LD_L_A;
                // LD_A(-1);
                // ADC_A_D;
                // LD_H_A;
                hl = de + ~(a & 0x7f);
            }

            // POP_AF;

            // CP_A(LZ_REPEAT);
            // IF_Z goto Repeat;
            // CP_A(LZ_FLIP);
            // IF_Z goto Flip;
            // CP_A(LZ_REVERSE);
            // IF_Z goto Reverse;


            //  Since LZ_LONG is command 7,
            //  only commands 0-6 are passed in.
            //  This leaves room for an extra command 7.
            //  However, lengths longer than 768
            //  would be interpreted as LZ_END.

            //  More practically, LZ_LONG is not recursive.
            //  For now, it defaults to LZ_REPEAT.
            switch(ctrl) {
            default: // fallthrough
            case LZ_REPEAT:    //  Copy decompressed data for bc bytes.
                // DEC_C;
                // IF_NZ goto rnext;
                // DEC_B;
                // IF_Z goto donerw;
                // printf("Repeat (%d bytes) hl:%04x\n", cnt.reg, hl);
                // fprintf(out, "HL=%04x DE=%04x REPEAT %d ", hl, de, cnt.reg);
                while(cnt--) {
                    // LD_A_hli;
                    // LD_de_A;
                    // INC_DE;
                    // fputc(gb_read(hl), out);
                    gb_write(de++, gb_read(hl++));
                }
                break;
            case LZ_FLIP:
                //  Copy bitflipped decompressed data for bc bytes.
                // DEC_C;
                // IF_NZ goto fnext;
                // DEC_B;
                // JP_Z (mDecompress_donerw);
                // printf("Flipped (%d bytes) hl:%04x\n", cnt.reg, hl);
                // fprintf(out, "HL=%04x DE=%04x FLIP %d ", hl, de, cnt.reg);
                while(cnt--) {
                    // LD_A_hli;
                    // PUSH_BC;
                    // LD_BC((0 << 8) | 8);
                    uint8_t data = gb_read(hl++);
                    data = ((data & 0xaa) >> 1) | ((data & 0x55) << 1);
                    data = ((data & 0xcc) >> 2) | ((data & 0x33) << 2);
                    data = ((data & 0xf0) >> 4) | ((data & 0x0f) << 4);

                    // do {
                    //     // RRA;
                    //     // RL_B;
                    //     // DEC_C;
                    //     // IF_NZ goto floop;
                    // } while(--bc.lo != 0);

                    // LD_A_B;
                    // POP_BC;

                    // LD_de_A;
                    // INC_DE;
                    // goto Flip;
                    // fputc(data, out);
                    gb_write(de++, data);
                    #undef rotr8
                    #undef rotl8
                }
                break;
            case LZ_REVERSE:    //  Copy reversed decompressed data for bc bytes.
                // DEC_C;
                // IF_NZ goto rvnext;

                // DEC_B;
                // JP_Z (mDecompress_donerw);
                // printf("Reversed (%d bytes) hl:%04x\n", cnt.reg, hl);
                // fprintf(out, "HL=%04x DE=%04x REVERSE %d ", hl, de, cnt.reg);
                while(cnt--) {
                    // LD_A_hld;
                    // LD_de_A;
                    // INC_DE;
                    // fputc(gb_read(hl), out);
                    gb_write(de++, gb_read(hl--));
                }
                break;
            }

            // POP_HL;
            hl = hltemp;

            // BIT_hl(7);
            // IF_NZ goto next;
            // INC_HL;  // positive offset is two bytes
            if(!bit_test(gb_read(hl), 7)) {
                hl++;
            }
            // INC_HL;
            hl++;
            // JP(mDecompress_Main);
            continue;
        }

        // CP_A(LZ_ITERATE);
        // IF_Z goto Iter;
        if(ctrl == LZ_ITERATE) {
            //  Write the same byte for bc bytes.
            // LD_A_hli;
            // fprintf(out, "HL=%04x DE=%04x ITER %d ", hl, de, cnt.reg);
            uint8_t same = gb_read(hl++);
            // printf("Iterate %d (%d bytes)\n", same, cnt.reg);
            // iloop:
            //         DEC_C;
            //     IF_NZ goto inext;
            //     DEC_B;
            //     JP_Z (mDecompress_Main);
            while(cnt--) {
                // inext:
                // LD_de_A;
                // INC_DE;
                // fputc(same, out);
                gb_write(de++, same);
                // goto iloop;
            }
            continue;
        }
        // CP_A(LZ_ALTERNATE);
        // IF_Z goto Alt;
        if(ctrl == LZ_ALTERNATE) {
            //  Alternate two bytes for bc bytes.
            // printf("Alternate (%d bytes)\n", cnt.reg);
            // fprintf(out, "HL=%04x DE=%04x ALT %d ", hl, de, cnt.reg);
            const uint8_t bytes[] = {gb_read(hl), gb_read(hl + 1)};
            uint8_t alt = 0;
            while(cnt--) {
                // fputc(bytes[alt], out);
                gb_write(de++, bytes[alt]);
                alt ^= 1;
            }
            // Skip past the bytes we were alternating.
            hl += 2;
            continue;
        }
        // CP_A(LZ_ZERO);
        // IF_Z goto Zero;
        if(ctrl == LZ_ZERO) {
        // Zero:
            //  Write 0 for bc bytes.
            // XOR_A_A;


        // zloop:
            // DEC_C;
            // IF_NZ goto znext;
            // DEC_B;
            // JP_Z (mDecompress_Main);
            // IF_Z continue;
            // printf("Zero (%d bytes)\n", cnt.reg);
            // fprintf(out, "ZERO ");
            while(cnt--) {
            // znext:
                // LD_de_A;
                // INC_DE;
                gb_write(de++, 0);
                // goto zloop;
            }
            continue;
        }

    //  Literal
    //  Read literal data for bc bytes.

    // lloop:
        // DEC_C;
        // IF_NZ goto lnext;
        // DEC_B;
        // JP_Z (mDecompress_Main);
        // printf("Literal (%d bytes)\n", cnt.reg);
        // fprintf(out, "HL=%04x DE=%04x LITERAL %d ", hl, de, cnt.reg);
        while(cnt--) {
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            // goto lloop;
            // fputc(gb_read(hl), out);
            gb_write(de++, gb_read(hl++));
        }
    }
    // fprintf(out, "END");
    // fclose(out);
}

//  Pokemon GSC uses an lz variant (lz3) for compression.
//  This is mainly (but not necessarily) used for graphics.
// 
//  This function decompresses lz-compressed data from hl to de.
//  Uses pointers instead of virtual gb addresses.
void Decompress(uint8_t* de, const uint8_t* hl){
#define LZ_END (0xff)  //  Compressed data is terminated with $ff.

//  A typical control command consists of:

#define LZ_CMD (0b11100000)  //  command id (bits 5-7)
#define LZ_LEN (0b00011111)  //  length n   (bits 0-4)

//  Additional parameters are read during command execution.

//  Commands:

#define LZ_LITERAL (0 << 5)  //  Read literal data for n bytes.
#define LZ_ITERATE (1 << 5)  //  Write the same byte for n bytes.
#define LZ_ALTERNATE (2 << 5)  //  Alternate two bytes for n bytes.
#define LZ_ZERO     (3 << 5)  //  Write 0 for n bytes.

//  Another class of commands reuses data from the decompressed output.
#define LZ_RW (2 + 5)  //  bit

//  These commands take a signed offset to start copying from.
//  Wraparound is simulated.
//  Positive offsets (15-bit) are added to the start address.
//  Negative offsets (7-bit) are subtracted from the current position.

#define LZ_REPEAT (4 << 5)  //  Repeat n bytes from the offset.
#define LZ_FLIP (5 << 5)  //  Repeat n bitflipped bytes.
#define LZ_REVERSE (6 << 5)  //  Repeat n bytes in reverse.

//  If the value in the count needs to be larger than 5 bits,
//  LZ_LONG can be used to expand the count to 10 bits.
#define LZ_LONG (7 << 5)

//  A new control command is read in bits 2-4.
//  The top two bits of the length are bits 0-1.
//  Another byte is read containing the bottom 8 bits.
#define LZ_LONG_HI (0b00000011)

//  In other words, the structure of the command becomes
//  111xxxyy yyyyyyyy
//  x: the new control command
//  y: the length

//  For more information, refer to the code below and in extras/gfx.py.

// Save the output address
// for rewrite commands.
    uint8_t* LZAddress = de;
    uint8_t byte;

    while(byte = *(hl), byte != LZ_END) {
        uint8_t ctrl;
        uint16_t cnt;
        byte &= LZ_CMD;
        if(byte == LZ_LONG) {
        //  The count is now 10 bits.

        // Read the next 3 bits.
        // %00011100 -> %11100000
        // This is our new control code.
            ctrl = (*(hl) << 3) & LZ_CMD;
            cnt = ((hl[0] & LZ_LONG_HI) << 8) | hl[1];
            hl += 2;
        // read at least 1 byte
            cnt++;
        }
        else {
            ctrl = byte;
            cnt = *(hl++) & LZ_LEN;

        // read at least 1 byte
            cnt++;
        }

        // Increment loop counts.
    // We bail the moment they hit 0.
        if(bit_test(ctrl, LZ_RW)) {
            //  Repeat decompressed data from output.
            const uint8_t* hltemp = hl;
            uint8_t a = *(hl++);
            if(!bit_test(a, 7)) {
                //  Positive offsets are two bytes.
            // add to starting output address
                hl = LZAddress + (uintptr_t)(((uint16_t)(uint8_t)a) << 8 | *(hl));
            }
            else {
            //  negative
                hl = de + ~(a & 0x7f);
            }
            //  Since LZ_LONG is command 7,
            //  only commands 0-6 are passed in.
            //  This leaves room for an extra command 7.
            //  However, lengths longer than 768
            //  would be interpreted as LZ_END.

            //  More practically, LZ_LONG is not recursive.
            //  For now, it defaults to LZ_REPEAT.
            switch(ctrl) {
            default: // fallthrough
            case LZ_REPEAT:    //  Copy decompressed data for bc bytes.
                while(cnt--) {
                    *(de++) = *(hl++);
                }
                break;
            case LZ_FLIP:
                //  Copy bitflipped decompressed data for bc bytes.
                while(cnt--) {
                    uint8_t data = *(hl++);
                    data = ((data & 0xaa) >> 1) | ((data & 0x55) << 1);
                    data = ((data & 0xcc) >> 2) | ((data & 0x33) << 2);
                    data = ((data & 0xf0) >> 4) | ((data & 0x0f) << 4);
                    *(de++) = data;
                }
                break;
            case LZ_REVERSE:    //  Copy reversed decompressed data for bc bytes.
                while(cnt--) {
                    *(de++) = *(hl--);
                }
                break;
            }

            // POP_HL;
            hl = hltemp;

            // BIT_hl(7);
            // IF_NZ goto next;
            // INC_HL;  // positive offset is two bytes
            if(!bit_test(*(hl), 7)) {
                hl++;
            }
            // INC_HL;
            hl++;
            // JP(mDecompress_Main);
            continue;
        }
        if(ctrl == LZ_ITERATE) {
            //  Write the same byte for bc bytes.
            uint8_t same = *(hl++);
            while(cnt--) {
                *(de++) = same;
            }
            continue;
        }
        if(ctrl == LZ_ALTERNATE) {
            //  Alternate two bytes for bc bytes.
            const uint8_t bytes[] = {*(hl), *(hl + 1)};
            uint8_t alt = 0;
            while(cnt--) {
                *(de++) = bytes[alt];
                alt ^= 1;
            }
            // Skip past the bytes we were alternating.
            hl += 2;
            continue;
        }
        if(ctrl == LZ_ZERO) {
            //  Write 0 for bc bytes.
            while(cnt--) {
                *(de++) = 0;
            }
            continue;
        }

        //  Literal
        //  Read literal data for bc bytes.
        while(cnt--) {
            *(de++) = *(hl++);
        }
    }
}

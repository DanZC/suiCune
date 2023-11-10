#include <stdint.h>
#include <stdlib.h>
#include <uchar.h>
#include <string.h>
#include "../charmap.h"
#include "../constants.h"

uint8_t lCrystalTextConvBuffer[1024];

#define KEY_AND_SIZE(_key) _key, sizeof(_key) - 1
#define CHARMAP_ENTRY(_key, _value) {KEY_AND_SIZE(_key), _value}

// Character mapping of UTF-8 character sequences to Crystal encoded characters.
static const struct {
    const char* const key;
    unsigned int key_size;
    uint8_t value;
} charmp[] = {
    CHARMAP_ENTRY("<NULL>", CHAR_NULL),
    CHARMAP_ENTRY("<PLAY_G>", CHAR_PLAY_G),
    CHARMAP_ENTRY("<MOBILE>", CHAR_MOBILE),
    CHARMAP_ENTRY("<CR>", CHAR_CR),
    CHARMAP_ENTRY("¯", CHAR_SOFTLB),
    CHARMAP_ENTRY("<LF>", CHAR_LF),
    CHARMAP_ENTRY("<POKE>", CHAR_POKE),
    CHARMAP_ENTRY("%", CHAR_LM_SLB),
    CHARMAP_ENTRY("<RED>", CHAR_RED),
    CHARMAP_ENTRY("<GREEN>", CHAR_GREEN),
    CHARMAP_ENTRY("<ENEMY>", CHAR_ENEMY),
    CHARMAP_ENTRY("<MOM>", CHAR_MOM),
    CHARMAP_ENTRY("<PKMN>", CHAR_PKMN),
    CHARMAP_ENTRY("<_CONT>", CHAR__CONT),
    CHARMAP_ENTRY("<SCROLL>", CHAR_SCROLL),
    CHARMAP_ENTRY("<NEXT>", CHAR_NEXT),
    CHARMAP_ENTRY("<LINE>", CHAR_LINE),
    CHARMAP_ENTRY("@", CHAR_TERM),
    CHARMAP_ENTRY("<PARA>", CHAR_PARA),
    CHARMAP_ENTRY("<PLAYER>", CHAR_PLAYER),
    CHARMAP_ENTRY("<RIVAL>", CHAR_RIVAL),
    CHARMAP_ENTRY("#", CHAR_POKe),
    CHARMAP_ENTRY("<CONT>", CHAR_CONT),
    CHARMAP_ENTRY("<……>", CHAR_SIXDOTS),
    CHARMAP_ENTRY("<DONE>", CHAR_DONE),
    CHARMAP_ENTRY("<PROMPT>", CHAR_PROMPT),
    CHARMAP_ENTRY("<TARGET>", CHAR_TARGET),
    CHARMAP_ENTRY("<USER>", CHAR_USER),
    CHARMAP_ENTRY("<PC>", CHAR_PC),
    CHARMAP_ENTRY("<TM>", CHAR_TM),
    CHARMAP_ENTRY("<TRAINER>", CHAR_TRAINER),
    CHARMAP_ENTRY("<ROCKET>", CHAR_ROCKET),
    CHARMAP_ENTRY("<DEXEND>", CHAR_DEXEND),

    CHARMAP_ENTRY("<BOLD_V>", CHAR_BOLD_V),
    CHARMAP_ENTRY("<BOLD_S>", CHAR_BOLD_S),
    CHARMAP_ENTRY("<COLON>", CHAR_COLON),
    CHARMAP_ENTRY("<PO>", CHAR_PO),
    CHARMAP_ENTRY("<KE>", CHAR_KE),
    CHARMAP_ENTRY("“", CHAR_OPEN_QUOTE),
    CHARMAP_ENTRY("”", CHAR_CLOSE_QUOTE),
    CHARMAP_ENTRY("…", CHAR_ELLIPSIS),

    CHARMAP_ENTRY("<LV>", CHAR_LV),
    CHARMAP_ENTRY("◀", CHAR_LEFT_CURSOR),
    CHARMAP_ENTRY("<ID>", CHAR_ID),
    CHARMAP_ENTRY("№", CHAR_NO),

    CHARMAP_ENTRY("?", CHAR_QMARK),
    CHARMAP_ENTRY("!", CHAR_EMARK),
    CHARMAP_ENTRY(".", CHAR_PERIOD),
    CHARMAP_ENTRY("&", CHAR_AMPERSAND),

    CHARMAP_ENTRY("(", CHAR_LPAREN),
    CHARMAP_ENTRY(")", CHAR_RPAREN),
    CHARMAP_ENTRY(":", CHAR_COLON2),
    CHARMAP_ENTRY("[", CHAR_LBRACKET),
    CHARMAP_ENTRY("]", CHAR_RBRACKET),

    CHARMAP_ENTRY("'d", CHAR_APOS_D),
    CHARMAP_ENTRY("'l", CHAR_APOS_L),
    CHARMAP_ENTRY("'m", CHAR_APOS_M),
    CHARMAP_ENTRY("'r", CHAR_APOS_R),
    CHARMAP_ENTRY("'s", CHAR_APOS_S),
    CHARMAP_ENTRY("'t", CHAR_APOS_T),
    CHARMAP_ENTRY("'v", CHAR_APOS_V),

    CHARMAP_ENTRY("←", CHAR_LEFT_ARROW),
    CHARMAP_ENTRY("'", CHAR_SINGLE_QUOTE),
    CHARMAP_ENTRY("<PK>", CHAR_PK),
    CHARMAP_ENTRY("<MN>", CHAR_MN),
    CHARMAP_ENTRY("-", CHAR_DASH),

    CHARMAP_ENTRY("┌", CHAR_FRAME_TOP_LEFT),
    CHARMAP_ENTRY("─", CHAR_FRAME_TOP),
    CHARMAP_ENTRY("┐", CHAR_FRAME_TOP_RIGHT),
    CHARMAP_ENTRY("│", CHAR_FRAME_SIDE),
    CHARMAP_ENTRY("└", CHAR_FRAME_BOTTOM_LEFT),
    CHARMAP_ENTRY("┘", CHAR_FRAME_BOTTOM_RIGHT),
    CHARMAP_ENTRY(" ", CHAR_SPACE),

    CHARMAP_ENTRY("é", CHAR_ACCENT_E),
    CHARMAP_ENTRY("→", CHAR_RIGHT_ARROW),
    CHARMAP_ENTRY("▷", CHAR_RIGHT_CURSOR_SEL),
    CHARMAP_ENTRY("▶", CHAR_RIGHT_CURSOR),
    CHARMAP_ENTRY("▼", CHAR_DOWN_CURSOR),
    CHARMAP_ENTRY("♂", CHAR_MALE_ICON),
    CHARMAP_ENTRY("¥", CHAR_MONEY_ICON),
    CHARMAP_ENTRY("×", CHAR_TIMES),
    CHARMAP_ENTRY("<DOT>", CHAR_DOT),
    CHARMAP_ENTRY("/", CHAR_FWD_SLASH),
    CHARMAP_ENTRY(",", CHAR_COMMA),
    CHARMAP_ENTRY("♀", CHAR_FEMALE_ICON),

    CHARMAP_ENTRY("■", CHAR_BLACK_SQUARE),
    CHARMAP_ENTRY("▲", CHAR_UP_ARROW),
    CHARMAP_ENTRY("☎", CHAR_PHONE_ICON),
    
    CHARMAP_ENTRY("⁂", CHAR_SHINY_ICON),
};

// Converts UTF-8 encoded string to Crystal encoding.
// Returns address to temp buffer containing encoded string.
uint8_t* Utf8ToCrystal(const char* src)
{
    size_t i = 0;
    while(i < sizeof(lCrystalTextConvBuffer) - 1 && *src)
    {
        for(unsigned int j = 0; j < lengthof(charmp); j++)
        {
            if(strncmp(src, charmp[j].key, charmp[j].key_size) == 0) { 
                lCrystalTextConvBuffer[i++] = charmp[j].value; 
                src += charmp[j].key_size; 
                goto nextchar; 
            }
        }
        // Check capital letter
        if(*src >= 'A' && *src <= 'Z') {
            lCrystalTextConvBuffer[i++] = CHAR_A + (*src - 'A'); 
            src++; 
            goto nextchar; 
        }
        // Check lowercase letter
        if(*src >= 'a' && *src <= 'z') {
            lCrystalTextConvBuffer[i++] = CHAR_a + (*src - 'a'); 
            src++; 
            goto nextchar; 
        }
        // Check number
        if(*src >= '0' && *src <= '9') {
            lCrystalTextConvBuffer[i++] = CHAR_0 + (*src - '0'); 
            src++; 
            goto nextchar; 
        }
        // Unknown char sequence
        lCrystalTextConvBuffer[i++] = CHAR_QMARK;
        src++;
    nextchar:;
    }
    lCrystalTextConvBuffer[i] = CHAR_TERM;
    return lCrystalTextConvBuffer;
}

// Converts UTF-8 encoded string to Crystal encoding.
// Returns address to passed buffer containing encoded string.
uint8_t* Utf8ToCrystalBuffer(uint8_t* dest, size_t dest_size, const char* src)
{
    size_t i = 0;
    while(i < dest_size - 1 && *src)
    {
        for(unsigned int j = 0; j < lengthof(charmp); j++)
        {
            if(strncmp(src, charmp[j].key, charmp[j].key_size) == 0) { 
                dest[i++] = charmp[j].value; 
                src += charmp[j].key_size; 
                goto nextchar; 
            }
        }
        // Check capital letter
        if(*src >= 'A' && *src <= 'Z') {
            dest[i++] = CHAR_A + (*src - 'A'); 
            src++; 
            goto nextchar; 
        }
        // Check lowercase letter
        if(*src >= 'a' && *src <= 'z') {
            dest[i++] = CHAR_a + (*src - 'a'); 
            src++; 
            goto nextchar; 
        }
        // Check number
        if(*src >= '0' && *src <= '9') {
            dest[i++] = CHAR_0 + (*src - '0'); 
            src++; 
            goto nextchar; 
        }
        // Unknown char sequence
        dest[i++] = CHAR_QMARK;
        src++;
    nextchar:;
    }
    dest[i] = CHAR_TERM;
    return dest;
}

// Copies Crystal string from buffer to GB address.
void CopyStringToGB(uint16_t dest, const char* src) 
{
    while((*src) != CHAR_TERM)
    {
        gb_write(dest++, *(src++));
    }
    gb_write(dest, CHAR_TERM);
}

// Converts a UTF-8 encoded string to Crystal encoding, 
// then copies the converted string to GB address.
void CopyUTF8StringToGB(uint16_t dest, const char* src)
{
    const uint8_t* src2 = Utf8ToCrystal(src);
    while((*src2) != CHAR_TERM)
    {
        gb_write(dest++, *(src2++));
    }
    gb_write(dest, CHAR_TERM);
}

// Converts a UTF-8 encoded string to Crystal encoding, 
// then copies n characters of the converted string to GB address.
void CopyUTF8NStringToGB(uint16_t dest, uint16_t n, const char* src)
{
    const uint8_t* src2 = Utf8ToCrystal(src);
    for(uint16_t i = 0; i < n - 1; ++i)
    {
        gb_write(dest++, *(src2++));
    }
    gb_write(dest, CHAR_TERM);
}

// Copies Crystal string from GB address to buffer.
void CopyStringFromGB(uint8_t* dest, size_t dest_size, uint16_t src)
{
    size_t i = 0;
    uint8_t c = gb_read(src);
    while(i < dest_size - 1 && c != CHAR_TERM) {
        dest[i++] = c;
        c = gb_read(++src);
    }
    dest[i] = CHAR_TERM;
}

// Prints Crystal encoded string from GB address to standard output as UTF-8 text.
uint16_t PrintCrystalStringFromGB(uint16_t ptr) {
    uint8_t c = gb_read(ptr);
    char buf[2];
    buf[1] = '\0';
    while(c != CHAR_TERM && c != CHAR_DONE && c != CHAR_PROMPT) {
        if(c >= CHAR_A && c <= CHAR_Z) {
            buf[0] = 'A' + (c - CHAR_A);
            printf("%s", buf);
            c = gb_read(++ptr);
            continue;
        }
        if(c >= CHAR_a && c <= CHAR_z) {
            buf[0] = 'a' + (c - CHAR_a);
            printf("%s", buf);
            c = gb_read(++ptr);
            continue;
        }
        if(c >= CHAR_0) {
            buf[0] = '0' + (c - CHAR_0);
            printf("%s", buf);
            c = gb_read(++ptr);
            continue;
        }
        switch(c) {
            case CHAR_SPACE: printf(" "); break;
            case CHAR_POKe: printf("#"); break;
            case CHAR_CR: printf("<CR>"); break;
            case CHAR_PARA: printf("<PARA>"); break;
            case CHAR_LF: printf("<LF>"); break;
            case CHAR_CONT: printf("<CONT>"); break;
            case CHAR__CONT: printf("<_CONT>"); break;
            case CHAR_LINE: printf("<LINE>"); break;
            case CHAR_SCROLL: printf("<SCROLL>"); break;
            case CHAR_DONE: printf("<DONE>"); break;
            case CHAR_PLAYER: printf("<PLAYER>"); break;
            case CHAR_PLAY_G: printf("<PLAY_G>"); break;
            case CHAR_COMMA: printf(","); break;
            case CHAR_SINGLE_QUOTE: printf("'"); break;
            case CHAR_FWD_SLASH: printf("/"); break;
            case CHAR_PERIOD: printf("."); break;
            case CHAR_DOT: printf("."); break;
            case CHAR_EMARK: printf("!"); break;
            case CHAR_QMARK: printf("?"); break;
            case CHAR_ELLIPSIS: printf("…"); break;
            case CHAR_SIXDOTS: printf("<……>"); break;
            case CHAR_ID: printf("<ID>"); break;
            case CHAR_APOS_D: printf("'d"); break;
            case CHAR_APOS_S: printf("'s"); break;
            case CHAR_APOS_M: printf("'m"); break;
            case CHAR_APOS_L: printf("'l"); break;
            case CHAR_APOS_V: printf("'v"); break;
            case CHAR_APOS_R: printf("'r"); break;
            case CHAR_APOS_T: printf("'t"); break;
            case CHAR_MONEY_ICON: printf("$"); break;
            default: printf("?"); break;
        }
        c = gb_read(++ptr);
    }
    return ptr + 1;
}

// Prints Crystal encoded string from RAM address to standard output as UTF-8 text.
uint8_t* PrintCrystalStringFromRAM(uint8_t* ptr) {
    uint8_t c = *(ptr);
    char buf[2];
    buf[1] = '\0';
    while(c != CHAR_TERM && c != CHAR_DONE && c != CHAR_PROMPT) {
        if(c >= CHAR_A && c <= CHAR_Z) {
            buf[0] = 'A' + (c - CHAR_A);
            printf("%s", buf);
            c = *(++ptr);
            continue;
        }
        if(c >= CHAR_a && c <= CHAR_z) {
            buf[0] = 'a' + (c - CHAR_a);
            printf("%s", buf);
            c = *(++ptr);
            continue;
        }
        if(c >= CHAR_0) {
            buf[0] = '0' + (c - CHAR_0);
            printf("%s", buf);
            c = *(++ptr);
            continue;
        }
        switch(c) {
            case CHAR_SPACE: printf(" "); break;
            case CHAR_POKe: printf("#"); break;
            case CHAR_CR: printf("<CR>"); break;
            case CHAR_PARA: printf("<PARA>"); break;
            case CHAR_LF: printf("<LF>"); break;
            case CHAR_CONT: printf("<CONT>"); break;
            case CHAR__CONT: printf("<_CONT>"); break;
            case CHAR_LINE: printf("<LINE>"); break;
            case CHAR_SCROLL: printf("<SCROLL>"); break;
            case CHAR_DONE: printf("<DONE>"); break;
            case CHAR_PLAYER: printf("<PLAYER>"); break;
            case CHAR_PLAY_G: printf("<PLAY_G>"); break;
            case CHAR_COMMA: printf(","); break;
            case CHAR_SINGLE_QUOTE: printf("'"); break;
            case CHAR_FWD_SLASH: printf("/"); break;
            case CHAR_PERIOD: printf("."); break;
            case CHAR_DOT: printf("."); break;
            case CHAR_EMARK: printf("!"); break;
            case CHAR_QMARK: printf("?"); break;
            case CHAR_ELLIPSIS: printf("…"); break;
            case CHAR_SIXDOTS: printf("<……>"); break;
            case CHAR_ID: printf("<ID>"); break;
            case CHAR_APOS_D: printf("'d"); break;
            case CHAR_APOS_S: printf("'s"); break;
            case CHAR_APOS_M: printf("'m"); break;
            case CHAR_APOS_L: printf("'l"); break;
            case CHAR_APOS_V: printf("'v"); break;
            case CHAR_APOS_R: printf("'r"); break;
            case CHAR_APOS_T: printf("'t"); break;
            case CHAR_MONEY_ICON: printf("$"); break;
            default: printf("?"); break;
        }
        c = *(++ptr);
    }
    return ptr + 1;
}

void PrintCrystalTextFromGB(uint16_t ptr) {
    uint8_t cmd = gb_read(ptr++);
    uint8_t oldbank;
    while(cmd != TX_END) {
        switch(cmd)
        {
            case TX_START: 
                printf("text \""); 
                ptr = PrintCrystalStringFromGB(ptr); 
                printf("\"\n"); 
                if(gb_read(ptr - 1) == CHAR_DONE) 
                    return; 
                break;
            case TX_RAM: printf("text_ram \""); PrintCrystalStringFromGB(gb_read16(ptr)); ptr += 2; printf("\"\n"); break;
            case TX_FAR: 
                printf("text_far \"");
                oldbank = hram->hROMBank;
                Bankswitch_Conv(gb_read(ptr++));
                PrintCrystalStringFromGB(gb_read16(ptr)); 
                ptr += 2;
                Bankswitch_Conv(oldbank);
                break;
            default: 
                printf("text_unk\n"); break;
        }
        cmd = gb_read(ptr++);
    }
    printf("text_end\n");
}
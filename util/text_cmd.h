#pragma once
struct TextCmdState;

struct TextCmd {
    uint8_t cmd;
    union {
        const char* const text;
        uint8_t* const ram;
        uint8_t n;
        uint16_t coord;
        void (*const as)(struct TextCmdState*);
        int end;
        const struct TextCmd* const far_ptr;
        struct {
            uint16_t box_coord;
            uint8_t box_h;
            uint8_t box_w;
        };
        struct {
            uint8_t* const dec_addr;
            uint8_t bytes;
            uint8_t digits;
        };
        struct {
            uint8_t* const bcd_addr;
            uint8_t bcd_flags;
        };
    };
};

#define text_start(_s)              {TX_START, .text=_s},
#define text_ram(_r)                {TX_RAM, .ram=_r},
#define text_bcd(_p, _f)            {TX_BCD, .bcd_addr=_p, .bcd_flags=_f},
#define text_move(_x, _y)           {TX_MOVE, .coord=coord(_x, _y, 0)},
#define text_box(_x, _y, _h, _w)    {TX_BOX, .box_coord=coord(_x, _y, 0), .box_w=_w, .box_h=_h},
#define text_low                    {TX_LOW, .end=0},
#define text_promptbutton           {TX_PROMPT_BUTTON, .end=0},
#define text_scroll                 {TX_SCROLL, .end=0},
#define text_decimal(_p, _b, _d)    {TX_DECIMAL, .dec_addr=_p, .bytes=_b, .digits=_d},
#define text_pause                  {TX_PAUSE, .end=0},
#define text_dots(_n)               {TX_DOTS, .n=_n},
#define text_waitbutton             {TX_WAIT_BUTTON, .end=0},
#define text_asm(_fn)               {TX_START_ASM, .as=_fn},
#define text_buffer(_n)             {TX_STRINGBUFFER, .n=_n},
#define text_today                  {TX_DAY, .end=0},
#define text_far(_s)                {TX_FAR, .far_ptr=_s},
#define text_end                    {TX_END, .end=0},
#define sound_dex_fanfare_50_79     {TX_SOUND_DEX_FANFARE_50_79, .end=0},
#define sound_dex_fanfare_20_49     {TX_SOUND_DEX_FANFARE_20_49, .end=0},
#define sound_item                  {TX_SOUND_ITEM, .end=0},
#define sound_caught_mon            {TX_SOUND_CAUGHT_MON, .end=0},
#define sound_dex_fanfare_80_109    {TX_SOUND_DEX_FANFARE_80_109, .end=0},
#define sound_fanfare               {TX_SOUND_FANFARE, .end=0},
#define sound_slot_machine_start    {TX_SOUND_SLOT_MACHINE_START, .end=0},

#define wram_ptr(_p)        (gb.wram + (WRAM_BANK_SIZE * (MBANK(a##_p))) + (_p - WRAM_0_ADDR))
#define hram_ptr(_p)        (gb.hram + (_p - HRAM_ADDR))

#define t_line      "<LINE>"
#define t_next      "<NEXT>"
#define t_cont      "<CONT>"
#define t_para      "<PARA>"
#define t_sixdots   "<……>"
#define t__cont     "<_CONT>"
#define t_done      "<DONE>"
#define t_prompt    "<PROMPT>"

void ShowTestText(void);

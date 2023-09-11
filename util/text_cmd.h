
struct TextCmdState;

struct TextCmd {
    uint8_t cmd;
    union {
        const char* const text;
        uint8_t* const ram;
        void (*const as)(struct TextCmdState*);
        int end;
        struct {
            uint8_t far_bank;
            uint16_t far_address;
        };
    };
};

#define text_start(_s) {TX_START, .text=_s},
#define text_far(_s)   {TX_FAR, .far_bank=BANK(a##_s), .far_address=m##_s}
#define text_ram(_r)   {TX_RAM, .ram=_r},
#define text_asm(_fn)  {TX_START_ASM, .as=_fn},
#define text_end       {TX_END, .ram=NULL},
#define wram_ptr(_p)   (gb.wram + (WRAM_BANK_SIZE * (MBANK(a##_p))) + (_p - WRAM_0_ADDR))

#pragma once

struct SpecialCall {
    bool (*const condition)(void);
    uint8_t contact;
    const Script_fn_t script;
};

extern const struct SpecialCall SpecialPhoneCallList[];

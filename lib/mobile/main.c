#include "../../constants.h"
#include "main.h"
#include "../../home/delay.h"
#include "../../home/mobile.h"

//  A library included as part of the Mobile Adapter GB SDK.

// INCLUDE "macros/const.asm"
// INCLUDE "constants/hardware_constants.asm"
// INCLUDE "constants/mobile_constants.asm"

//  Mobile Adapter protocol commands
#define MOBILE_COMMAND_BEGIN_SESSION     (0x10)
#define MOBILE_COMMAND_END_SESSION (0x11)
#define MOBILE_COMMAND_DIAL_TELEPHONE (0x12)
#define MOBILE_COMMAND_HANG_UP_TELEPHONE (0x13)
#define MOBILE_COMMAND_WAIT_FOR_TELEPHONE_CALL (0x14)
#define MOBILE_COMMAND_TRANSFER_DATA (0x15)
#define MOBILE_COMMAND_TELEPHONE_STATUS (0x17)
#define MOBILE_COMMAND_READ_CONFIGURATION_DATA (0x19)
#define MOBILE_COMMAND_WRITE_CONFIGURATION_DATA (0x1a)
#define MOBILE_COMMAND_TRANSFER_DATA_END (0x1f)
#define MOBILE_COMMAND_ISP_LOGIN (0x21)
#define MOBILE_COMMAND_ISP_LOGOUT (0x22)
#define MOBILE_COMMAND_OPEN_TCP_CONNECTION (0x23)
#define MOBILE_COMMAND_CLOSE_TCP_CONNECTION (0x24)
#define MOBILE_COMMAND_DNS_QUERY (0x28)
#define MOBILE_COMMAND_ERROR (0x6e)

const uint8_t MobilePacket_Idle[] = {
    0x4b
};

const uint8_t MobilePacket_BeginSession[] = {
    0x99, 0x66, MOBILE_COMMAND_BEGIN_SESSION, 0x00, 0x00, 0x08, 
    'N', 'I', 'N', 'T', 'E', 'N', 'D', 'O', // "NINTENDO", 
    0x02, 0x77, 0x80, 0x00
};

const uint8_t MobilePacket_EndSession[] = {
    0x99, 0x66, MOBILE_COMMAND_END_SESSION, 0x00, 0x00, 0x00, 0x00, 0x11, 0x80, 0x00
};

const uint8_t MobilePacket_DialTelephone[] = {
    0x99, 0x66, MOBILE_COMMAND_DIAL_TELEPHONE, 0x00, 0x00, 0x00
};

const uint8_t MobilePacket_HangUpTelephone[] = {
    0x99, 0x66, MOBILE_COMMAND_HANG_UP_TELEPHONE, 0x00, 0x00, 0x00, 0x00, 0x13, 0x80, 0x00
};

const uint8_t MobilePacket_TelephoneStatus[] = {
    0x99, 0x66, MOBILE_COMMAND_TELEPHONE_STATUS, 0x00, 0x00, 0x00, 0x00, 0x17, 0x80, 0x00
};

const uint8_t MobilePacket_ISPLogin[] = {
    0x99, 0x66, MOBILE_COMMAND_ISP_LOGIN, 0x00, 0x00
};

const uint8_t MobilePacket_ISPLogout[] = {
    0x99, 0x66, MOBILE_COMMAND_ISP_LOGOUT, 0x00, 0x00, 0x00, 0x00, 0x22, 0x80, 0x00
};

const uint8_t MobilePacket_ReadConfigurationDataPart1[] = {
    0x99, 0x66, MOBILE_COMMAND_READ_CONFIGURATION_DATA, 0x00, 0x00, 0x02, 0x00, 0x60, 0x00, 0x7b, 0x80, 0x00
};

const uint8_t MobilePacket_ReadConfigurationDataPart2[] = {
    0x99, 0x66, MOBILE_COMMAND_READ_CONFIGURATION_DATA, 0x00, 0x00, 0x02, 0x60, 0x60, 0x00, 0xdb, 0x80, 0x00
};

const uint8_t MobilePacket_WriteConfigurationData[] = {
    0x99, 0x66, MOBILE_COMMAND_WRITE_CONFIGURATION_DATA, 0x00, 0x00
};

const uint8_t MobilePacket_DNSQuery[] = {
    0x99, 0x66, MOBILE_COMMAND_DNS_QUERY, 0x00, 0x00
};

const uint8_t MobilePacket_WaitForTelephoneCall[] = {
    0x99, 0x66, MOBILE_COMMAND_WAIT_FOR_TELEPHONE_CALL, 0x00, 0x00, 0x00, 0x00, 0x14, 0x80, 0x00
};

const uint8_t MobilePacket_TransferData[] = {
    0x99, 0x66, MOBILE_COMMAND_TRANSFER_DATA, 0x00, 0x00, 0x01, 0xff, 0x01, 0x15, 0x80, 0x00
};

const uint8_t MobilePacket_OpenTCPConnection[] = {
    0x99, 0x66, MOBILE_COMMAND_OPEN_TCP_CONNECTION, 0x00, 0x00, 0x06
};

const uint8_t MobilePacket_CloseTCPConnection[] = {
    0x99, 0x66, MOBILE_COMMAND_CLOSE_TCP_CONNECTION, 0x00, 0x00, 0x01
};

const char URIPrefix[] = "http://";
const char HTTPDownloadURL[] = "gameboy.datacenter.ne.jp/cgb/download";
const char HTTPUploadURL[] = "gameboy.datacenter.ne.jp/cgb/upload";
const char HTTPUtilityURL[] = "gameboy.datacenter.ne.jp/cgb/utility";
const char HTTPRankingURL[] = "gameboy.datacenter.ne.jp/cgb/ranking";

uint16_t gMobilePacketSize;
const uint8_t* gMobilePacketPointer;
uint16_t gMobileSendPacketSize;
const uint8_t* gMobileSendPacketPointer;
uint8_t* gMobileReceiveBuffer_Destination;

// SECTION "Mobile Adapter SDK", ROMX

//  Copy b bytes from hl to de
void* MobileSDK_CopyBytes(void* de, const void* hl, uint8_t b){
    uint8_t* de_ = de;
    const uint8_t* hl_ = hl;

    do {
    // loop:
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        *(de_++) = *(hl_++);
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
    return de;
}

//  Copy bytes from hl to de until a 0 is encountered.
//  Include the 0 in the copy, and count the number of
//  nonzero bytes copied.  Keep the de pointer at the
//  copied zero.
char* MobileSDK_CopyString(char* de, const char* hl){
    while(1) {
    // loop:
        // LD_A_hli;
        char c = *(hl++);
        // LD_de_A;
        *de = c;
        // OR_A_A;
        // RET_Z ;
        if(c == '\0')
            return de;
        // INC_DE;
        de++;
        // INC_BC;
        // goto loop;
    }
}

//  Copy bytes from hl to de until a 0 is encountered,
//  or a bytes have been copied, whichever comes first.
//  Add the byte count to the count previously stored
//  in bc.
char* MobileSDK_CopyStringLen(char* de, const char* hl, uint16_t* bc, uint8_t a){
    // PUSH_BC;
    // LD_C(0x0);
    uint8_t c = 0x0;
    // LD_B_A;
    uint8_t b = a;
    // DEC_B;
    --b;

    do {
    // loop:
        // LD_A_hli;
        char c = *(hl++);
        // LD_de_A;
        *de = c;
        // OR_A_A;
        // IF_Z goto done;
        if(c == '\0')
            goto done;
        // INC_DE;
        de++;
        // INC_C;
        c++;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // XOR_A_A;
    // LD_de_A;
    *de = '\0';

done:
    // LD_A_C;
    // POP_BC;
    // ADD_A_C;
    // LD_C_A;
    // LD_A_B;
    // ADC_A(0);
    // LD_B_A;
    *bc += c;
    // RET;
    return de;
}

//  Clear two bytes at wMobileSDK_ReceivedBytes
void ResetReceivePacketBuffer(void){
    // XOR_A_A;
    // LD_HL(wMobileSDK_ReceivedBytes);
    wram->wMobileSDK_ReceivedBytes = 0;
    // LD_hli_A;
    // LD_hl_A;
    // RET;
}

//  Use the byte at wMobileAPIIndex as a parameter
//  for a dw.
void v_MobileAPI(mobile_api_data_s *api){
    static void (*const jt[])(mobile_api_data_s*) = {
        [MOBILEAPI_00] = Function110115,
        [MOBILEAPI_01] = Function110236,
        [MOBILEAPI_02] = Function110291,
        [MOBILEAPI_03] = Function1103ac,
        [MOBILEAPI_04] = Function110438,
        // [MOBILEAPI_05] = Function1104c6,
        // [MOBILEAPI_06] = Function110578,
        // [MOBILEAPI_07] = Function110582,
        // [MOBILEAPI_08] = Function11058c,
        // [MOBILEAPI_09] = Function1105dd,
        // [MOBILEAPI_0A] = Function1106ef,
        // [MOBILEAPI_0B] = Function110757,
        // [MOBILEAPI_0C] = Function1107ff,
        // [MOBILEAPI_0D] = Function110899,
        // [MOBILEAPI_0E] = Function1108a3,
        // [MOBILEAPI_0F] = Function110905,
        // [MOBILEAPI_10] = Function1109a4,
        // [MOBILEAPI_11] = Function1109f9,
        // [MOBILEAPI_12] = Function110a5b,
        // [MOBILEAPI_13] = Function110c3c,
        // [MOBILEAPI_14] = Function110c9e,
        // [MOBILEAPI_15] = Function110ddd,
        // [MOBILEAPI_16] = Function1111fe,
        [MOBILEAPI_17] = Function1113fe,
        [MOBILEAPI_SETTIMER] = MobileAPI_SetTimer,
        // [MOBILEAPI_19] = Function111541,
        // [MOBILEAPI_1A] = Function111596,
        [MOBILEAPI_1B] = Function11162d,
        // [MOBILEAPI_1C] = Function11032c,
        // [MOBILEAPI_1D] = Function11148c,
        // [MOBILEAPI_1E] = Function111610,
        // [MOBILEAPI_1F] = Function1103ac,
        [MOBILEAPI_20] = Function110235,
        // [MOBILEAPI_21] = Function111540,
    };
//  If [wMobileAPIIndex] not in {MOBILEAPI_06, MOBILEAPI_07, MOBILEAPI_08},
//  clear [wc835].
    // PUSH_DE;
    // LD_A_addr(wMobileAPIIndex);
    // CP_A(MOBILEAPI_06);
    // IF_Z goto noreset;
    // CP_A(MOBILEAPI_07);
    // IF_Z goto noreset;
    // CP_A(MOBILEAPI_08);
    // IF_Z goto noreset;
    if(wram->wMobileAPIIndex != MOBILEAPI_06 && wram->wMobileAPIIndex != MOBILEAPI_07 && wram->wMobileAPIIndex != MOBILEAPI_08) {
        // XOR_A_A;
        // LD_addr_A(wc835);
        wram->wc835 = 0x0;
    }
    // LD_A_addr(wMobileAPIIndex);

// noreset:
// Get the pointer
    // LD_D(0);
    // LD_E_A;
    // LD_HL(mv_MobileAPI_dw);
    // ADD_HL_DE;
// Store the low byte in [wMobileAPIIndex]
    // LD_A_hli;
    // LD_addr_A(wMobileAPIIndex);
    // LD_A_hl;
// restore de
    // POP_DE;
    // LD_HL(mReturnMobileAPI);  // return here
    // PUSH_HL;
// If the destination function is not Function110236,
// call Function1100b4.
    // LD_H_A;
    // LD_A_addr(wMobileAPIIndex);
    // LD_L_A;
    // PUSH_HL;
    // LD_A(LOW(aFunction110236));
    // CP_A_L;
    // IF_NZ goto okay;
    // LD_A(HIGH(aFunction110236));
    // CP_A_H;

// okay:
    // CALL_NZ (aFunction1100b4);
    if(jt[wram->wMobileAPIIndex] != Function110236)
        Function1100b4();
    // LD_HL(wc986);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // RET;  // indirectly jump to the function loaded from the dw, which returns to ReturnMobileAPI.
    if(jt[wram->wMobileAPIIndex])
        jt[wram->wMobileAPIIndex](api);
    ReturnMobileAPI(api);
}

bool Function1100b4(void){
    // PUSH_BC;
    uint8_t b, c;

    do {
    // loop:
        DelayFrame();
        // NOP;
        // LD_A_addr(wc800);
        // LD_B_A;
        b = wram->wc800;
        // LD_A_addr(wc80b);
        // LD_C_A;
        c = wram->wc80b;
        // LD_A_addr(wc822);
        // NOP;
        // OR_A_A;
        // BIT_A(0);
        // IF_Z goto done;
        if(!bit_test(wram->wc822, 0))
            return false;
        // LD_A_B;
        // OR_A_A;
        // IF_NZ goto loop;
        // LD_A_C;
        // CP_A(0x4);
        // IF_Z goto loop;
    } while(b != 0 || c == 0x4);
    // XOR_A_A;
    // LD_addr_A(wc80f);
    wram->wc80f = 0x0;
    // LD_HL(wc821);
    // SET_hl(1);
    bit_set(wram->wc821, 1);
    // SCF;

// done:
    // POP_BC;
    // RET;
    return true;
}

void MobileAPI_SetTimer(mobile_api_data_s *data){
    // XOR_A_A;
    // LDH_addr_A(rTAC);
    gb_write(rTAC, 0x0);
    // LD_E_C;
    uint8_t e = LOW(data->bc);
    // LD_B_A;
    // LD_HL(mUnknown_112089);
    const uint8_t* hl = Unknown_112089;
    // ADD_HL_BC;
    hl += data->bc;
    // LD_C_hl;
    uint8_t c = *hl;
    // INC_HL;
    hl++;
    // LDH_A_addr(rKEY1);
    // BIT_A(7);
    // IF_NZ goto asm_1100f9;
    if(!bit_test(gb_read(rKEY1), 7)) {
        // LD_A_E;
        // SRA_C;
        c = (uint8_t)((int8_t)c >> 1);
        // LD_A_E;
        // CP_A(0x4);
        // IF_NC goto asm_1100f9;
        if(e < 0x4) {
            // LD_DE(0x000f);
            // ADD_HL_DE;
            hl += 0x000f;
        }
    }

// asm_1100f9:
    // LD_A_C;
    // LDH_addr_A(rTMA);
    gb_write(rTMA, c);
    // LDH_addr_A(rTIMA);
    gb_write(rTIMA, c);
    // LD_A_hli;
    uint8_t a = *(hl++);
    // LD_addr_A(wc81f);
    wram->wc81f = a;
    // LD_addr_A(wc816);
    wram->wc816 = a;
    // LD_A_hl;
    a = *(hl++);
    // LD_addr_A(wc820);
    wram->wc820 = a;
    // LD_addr_A(wc815);
    wram->wc815 = a;
    // LD_C(LOW(rTAC));
    // LD_A(rTAC_65536_HZ);
    // LDH_c_A;
    gb_write(rTAC, rTAC_65536_HZ);
    // LD_A(1 << rTAC_ON | rTAC_65536_HZ);
    // LDH_c_A;
    gb_write(rTAC, (1 << rTAC_ON) | rTAC_65536_HZ);
    // RET;
}

// MobileAPI00
void Function110115(mobile_api_data_s* data){
    (void)data;
    LD_HL(wc821);
    BIT_hl(1);
    IF_NZ goto asm_110120;
    XOR_A_A;
    LD_L_A;
    LD_H_A;
    RET;


asm_110120:
    RES_hl(1);
    LD_A_addr(wc80f);
    LD_E_A;
    CP_A(0x22);
    IF_Z goto asm_11016a;
    CP_A(0x23);
    IF_Z goto asm_11016a;
    CP_A(0x25);
    IF_Z goto asm_11016a;
    CP_A(0x26);
    IF_Z goto asm_11018e;
    CP_A(0x24);
    IF_Z goto asm_1101a4;
    CP_A(0x30);
    JP_Z (mFunction110115_asm_1101f8);
    CP_A(0x31);
    JP_Z (mFunction110115_asm_11020d);
    CP_A(0x32);
    IF_Z goto asm_1101a4;
    CP_A(0x33);
    IF_Z goto asm_1101a4;
    SWAP_A;
    AND_A(0xf);
    CP_A(0x1);
    IF_Z goto asm_11016a;
    CP_A(0x0);
    IF_Z goto asm_11015d;

asm_110158:
    LD_HL(0);

asm_11015b:
    LD_A_E;
    RET;


asm_11015d:
    LD_A_E;
    ADD_A(0x15);
    LD_E_A;
    XOR_A_A;
    LD_HL(wc810);
    LD_hli_A;
    LD_hl_A;
    LD_HL(wc821);


asm_11016a:
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_hl_A;
    LD_addr_A(wc807);
    INC_A;
    LD_addr_A(wc86a);
    LD_HL(wc822);
    RES_hl(0);
    RES_hl(5);
    LD_HL(wMobileSDK_PacketBuffer);
    XOR_A_A;
    LD_hli_A;
    INC_A;
    LD_hl_A;
    CALL(aFunction111686);
    LD_A(0x15);
    CP_A_E;
    IF_NZ goto asm_110158;
    goto asm_1101d7;


asm_11018e:
    LD_A_addr(wc821);
    BIT_A(4);
    LD_A(0x1);
    IF_Z goto asm_11016a;
    LD_A(0x2);
    LD_addr_A(wc86a);
    LD_A_addr(wc805);
    LD_addr_A(wc807);
    goto asm_110158;


asm_1101a4:
    RES_hl(0);
    LD_HL(wc822);
    RES_hl(5);
    LD_HL(wc821);
    RES_hl(7);
    RES_hl(6);
    SET_hl(5);
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_addr_A(wc9af);
    LD_A(0x2);
    LD_addr_A(wc86a);
    LD_A(0x4);
    LD_addr_A(wc807);
    LD_A_E;
    CP_A(0x32);
    IF_Z goto asm_1101d7;
    CP_A(0x33);
    IF_Z goto asm_1101d7;
    CP_A(0x30);
    IF_Z goto asm_1101d7;
    CP_A(0x31);
    JP_NZ (mFunction110115_asm_110158);


asm_1101d7:
    LD_HL(wc810);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A(0x32);
    CP_A_E;
    JP_NZ (mFunction110115_asm_11015b);
    LD_A(0x3);
    CP_A_H;
    JP_NZ (mFunction110115_asm_11015b);
    DEC_A;
    CP_A_L;
    IF_Z goto asm_1101f2;
    DEC_A;
    CP_A_L;
    JP_NZ (mFunction110115_asm_11015b);


asm_1101f2:
    LD_BC(wc880);
    JP(mFunction110115_asm_11015b);


asm_1101f8:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0xa4);
    IF_Z goto asm_1101a4;
    LD_A(0x3);
    LD_addr_A(wc86a);
    LD_HL(wc810);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP(mFunction110115_asm_11015b);


asm_11020d:
    LD_A_addr(wc810);
    CP_A(0x2);
    IF_Z goto asm_1101a4;
    CP_A(0x3);
    IF_Z goto asm_1101a4;
    LD_A(0x4);
    LD_addr_A(wc86a);
    LD_HL(wc810);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP(mFunction110115_asm_11015b);
}

// Mobile_SetW80Fto33
void Function110226(void){
    // LD_A(0x21);

    return Function110228(0x21);
}

// Mobile_SetW80FtoA
void Function110228(uint8_t a){
    // LD_addr_A(wc80f);
    wram->wc80f = a;
    // LD_HL(wc821);
    // SET_hl(1);
    bit_set(wram->wc821, 1);
    // RET;
}

void Function110231(void){
    // LD_A(0x20);
    // JR(mFunction110228);

    return Function110228(0x20);
}

// MobileAPI20
void Function110235(mobile_api_data_s* data){
    // NOP;
    return Function110236(data);
}

// MobileAPI01
void Function110236(mobile_api_data_s* data){
    (void)data;
    // LD_A_addr(wMobileAPIIndex);
    uint8_t a = wram->wMobileAPIIndex;
    // PUSH_AF;
    // PUSH_BC;
    // PUSH_HL;
    // XOR_A_A;
    // LDH_addr_A(rTAC);
    gb_write(rTAC, 0x0);
    // LDH_A_addr(rIF);
    // AND_A(0x1b);
    // LDH_addr_A(rIF);
    gb_write(rIF, gb_read(rIF) & ((1 << VBLANK) | (1 << LCD_STAT) | (1 << SERIAL) | (1 << JOYPAD)));
    // CALL(aResetReceivePacketBuffer);
    ResetReceivePacketBuffer();
    // LD_BC(0x0452);
    // LD_HL(wc800);

    for(uint16_t bc = 0; bc < 0x0452; ++bc) {
    // asm_11024e:
        // XOR_A_A;
        // LD_hli_A;
        (&wram->wc800)[bc] = 0x0;
        // DEC_BC;
        // LD_A_C;
        // OR_A_B;
        // IF_NZ goto asm_11024e;
    }
    // LD_A_addr(wc822);
    // SET_A(6);
    // LD_addr_A(wc822);
    bit_set(wram->wc822, 6);
    // POP_HL;
    // LD_A_L;
    // LD_addr_A(wc981);
    wram->wc981 = data->l;
    // LD_A_H;
    // LD_addr_A(wc982);
    wram->wc982 = data->h;
    // POP_BC;
    // LD_HL(wc983);
    // LD_A_C;
    // LD_hli_A;
    // LD_A_B;
    // LD_hl_A;
    wram->wc983 = data->bc;
    // LD_HL(wc86e);
    // LD_A_E;
    // LD_hli_A;
    // LD_hl_D;
    // XOR_A_A;
    // LD_addr_A(wc819);
    wram->wc819 = 0x0;
    // LD_C(0xc);
    data->bc = 0xc;
    // CALL(aMobileAPI_SetTimer);
    MobileAPI_SetTimer(data);
    // CALL(aFunction1104b0);
    Function1104b0();
    // POP_AF;
    // CP_A(0x35);
    // IF_NZ goto asm_110289;
    if(a == 0x35) {
        // LD_A(0x2b);
        wram->wc86a = 0x2b;
        // goto asm_11028b;
    }
    else {
    // asm_110289:
        // LD_A(0xa);
        wram->wc86a = 0xa;
    }

// asm_11028b:
    // LD_addr_A(wc86a);
    // JP(mFunction110432);
    Function110432();
}

// MobileAPI02
void Function110291(mobile_api_data_s* data){
    (void)data;
    LD_A_addr(wc821);
    BIT_A(1);
    IF_Z goto asm_1102a6;
    LD_A_addr(wc80f);
    CP_A(0x14);
    IF_Z goto asm_1102b3;
    CP_A(0x25);
    IF_Z goto asm_1102b3;
    LD_A_addr(wc821);


asm_1102a6:
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x1);
    JP_NZ (mFunction110226);


asm_1102b3:
    XOR_A_A;
    LDH_addr_A(rTAC);
    XOR_A_A;
    LD_addr_A(wc819);
    LD_A_L;
    LD_B_H;
    LD_HL(wc880);
    LD_hli_A;
    LD_A_B;
    LD_hli_A;
    LD_A_C;
    LD_hli_A;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;
    LD_A_addr(wc870);
    LD_C_A;
    CALL(aMobileAPI_SetTimer);
    // LD_HL(wc829);
    // LD_A(0x72);
    // LD_hli_A;
    wram->wc829 = 0x72;
    // LD_A(0xc8);
    // LD_hl_A;
    wram->wc82a = 0xc8;
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_B(sizeof(MobilePacket_WriteConfigurationData));
    // LD_HL(mMobilePacket_WriteConfigurationData);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_WriteConfigurationData, sizeof(MobilePacket_WriteConfigurationData));
    LD_A_addr(wc882);
    LD_C_A;
    OR_A_A;
    IF_Z goto asm_1102f2;
    CP_A(0x80);
    IF_NC goto asm_1102f2;
    LD_C(0x80);
    goto asm_1102f4;


asm_1102f2:
    LD_A(0x80);


asm_1102f4:
    LD_B_A;
    INC_A;
    LD_de_A;
    INC_DE;
    LD_A(0x80);
    ADD_A_C;
    LD_HL(wc882);
    LD_hli_A;
    LD_A_hl;
    LD_de_A;
    INC_DE;
    ADD_A(0x80);
    LD_hl_A;
    LD_HL(wc880);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_C_B;
    CALL(aMobileSDK_CopyBytes);
    LD_A_L;
    LD_addr_A(wc880);
    LD_A_H;
    LD_addr_A(wc881);
    LD_B_C;
    INC_B;
    CALL(aFunction111f63);
    CALL(aFunction1104b0);
    LD_A(0x2e);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    RES_hl(1);
    SET_hl(0);
    RET;

}

void Function11032c(void){
    LD_A_addr(wc821);
    BIT_A(1);
    JP_NZ (mFunction110226);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x1);
    JP_NZ (mFunction110226);
    XOR_A_A;
    LDH_addr_A(rTAC);
    LD_addr_A(wc819);
    LD_HL(wc880);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_A_C;
    LD_hli_A;
    LD_A_B;
    LD_hli_A;
    LD_HL(wc829);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;
    LD_A_addr(wc870);
    LD_C_A;
    CALL(aMobileAPI_SetTimer);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_B(6);  // header size
    LD_HL(mMobilePacket_ReadConfigurationDataPart1);
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc883);
    LD_de_A;
    INC_DE;
    LD_A_addr(wc882);
    LD_C_A;
    OR_A_A;
    IF_Z goto asm_11037f;
    CP_A(0x80);
    IF_NC goto asm_11037f;
    LD_C(0x80);
    goto asm_110381;


asm_11037f:
    LD_A(0x80);


asm_110381:
    LD_de_A;
    INC_DE;
    LD_B(0x2);
    CALL(aFunction111f63);
    CALL(aFunction1104b0);
    LD_A(0x2d);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

// MobileSDK_EnableSerialAndTimer
void Function110393(void){
    // LD_C(LOW(rIE));
    // LDH_A_c;
    // OR_A((1 << SERIAL) | (1 << TIMER));
    // LDH_c_A;
    gb_write(rIE, gb_read(rIE) | ((1 << SERIAL) | (1 << TIMER)));
    // RET;
}

void Function11039a(void){
    LD_B(0x0);

asm_11039c:
    INC_B;
    IF_Z goto asm_1103a3;
    LD_A_hli;
    OR_A_A;
    IF_NZ goto asm_11039c;


asm_1103a3:
    LD_A_B;
    CP_A_C;
    IF_NC goto asm_1103aa;
    CP_A(0x2);
    RET;


asm_1103aa:
    SCF;
    RET;

}

// MobileAPI03
void Function1103ac(mobile_api_data_s* data){
    (void)data;
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x1);
    JP_NZ (mFunction110226);
    PUSH_HL;
    LD_C(0x15);
    CALL(aFunction11039a);
    IF_C goto asm_1103d2;
    LD_C(0x22);
    CALL(aFunction11039a);
    IF_C goto asm_1103d2;
    LD_C(0x12);
    CALL(aFunction11039a);
    IF_NC goto asm_1103d6;


asm_1103d2:
    POP_HL;
    JP(mFunction110231);


asm_1103d6:
    XOR_A_A;
    LDH_addr_A(rTAC);
    LD_addr_A(wc86d);
    LD_addr_A(wc97a);
    LD_A_addr(wc870);
    LD_C_A;
    CALL(aMobileAPI_SetTimer);
    LD_HL(wc829);
    LD_A(0x80);
    LD_hli_A;
    LD_A(0xc8);
    LD_hl_A;
    CALL(aFunction110485);
    PUSH_HL;
    LD_B_A;
    CALL(aFunction111f63);
    LD_B(lengthof(MobilePacket_ISPLogin));
    LD_HL(mMobilePacket_ISPLogin);
    LD_DE(wMobileSDK_PacketBuffer + 45);
    CALL(aMobileSDK_CopyBytes);
    INC_DE;
    INC_DE;
    POP_HL;
    LD_BC(0);
    CALL(aMobileSDK_CopyString);
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 51);
    LD_addr_A(wc86b);
    PUSH_DE;
    INC_DE;
    LD_BC(0);
    LD_A(0x20);
    CALL(aMobileSDK_CopyStringLen);
    LD_L_E;
    LD_H_D;
    POP_DE;
    LD_A_C;
    LD_de_A;
    LD_A_addr(wc86b);
    ADD_A_C;
    ADD_A(0xa);
    LD_addr_A(wMobileSDK_PacketBuffer + 50);
    CALL(aFunction1104b0);
    LD_A(0xb);
    LD_addr_A(wc86a);

    return Function110432();
}

// Mobile_SetWC821Bit0
void Function110432(void){
    // LD_HL(wc821);
    // SET_hl(0);
    // RET;
    bit_set(wram->wc821, 0);
}

// MobileAPI04
void Function110438(mobile_api_data_s* data){
    (void)data;
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x1);
    JP_NZ (mFunction110226);
    PUSH_HL;
    LD_C(0x15);
    CALL(aFunction11039a);
    IF_NC goto asm_110454;
    POP_HL;
    JP(mFunction110231);


asm_110454:
    XOR_A_A;
    LDH_addr_A(rTAC);
    LD_addr_A(wc97a);
    LD_A_addr(wc870);
    LD_C_A;
    CALL(aMobileAPI_SetTimer);
    LD_HL(wc98f);
    LD_A(0x81);
    LD_hli_A;
    LD_A(0xc8);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    LD_A(0xff);
    LD_addr_A(wc86e);
    CALL(aFunction110485);
    LD_B_A;
    CALL(aFunction111f63);
    CALL(aFunction1104b0);
    LD_A(0xc);
    LD_addr_A(wc86a);
    JR(mFunction110432);

}

void Function110485(void){
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_DialTelephone);
    LD_B(lengthof(MobilePacket_DialTelephone));
    CALL(aMobileSDK_CopyBytes);
    POP_BC;
    POP_HL;
    PUSH_BC;
    LD_A_addr(wMobileSDK_AdapterType);
    CP_A(0x8c);
    IF_C goto asm_11049e;
    LD_A(0x3);
    goto asm_1104a1;


asm_11049e:
    LD_A_addr(wc871);


asm_1104a1:
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    LD_A(MOBILE_PHONE_NUMBER_LENGTH);
    CALL(aMobileSDK_CopyStringLen);
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 5);
    RET;

}

// MobileSDK_SendIdle
void Function1104b0(void){
    // XOR_A_A;
    // LD_addr_A(wMobileSDK_SendCommandID);
    wram->wMobileSDK_SendCommandID = 0x0;
    // CALL(aFunction110393);
    Function110393();
    // XOR_A_A;
    // LD_addr_A(wc86b);
    wram->wc86b = 0x0;
    // LD_DE(lengthof(MobilePacket_Idle));
    // LD_HL(mMobilePacket_Idle);
    // LD_B(1);
    // JP(mPacketSendBytes);
    PacketSendBytes(MobilePacket_Idle, lengthof(MobilePacket_Idle), 1);
}

void Function1104c6(void){
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x4);
    IF_Z goto asm_110526;
    CP_A(0x3);
    IF_Z goto asm_110526;
    CP_A(0x2);
    JP_NZ (mFunction110226);
    LD_HL(wc822);
    BIT_hl(4);
    IF_NZ goto asm_110507;
    LD_A(0x2);
    LD_addr_A(wc86b);
    LD_A(MOBILE_COMMAND_ISP_LOGOUT | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_DE(lengthof(MobilePacket_ISPLogout));
    LD_HL(mMobilePacket_ISPLogout);
    LD_B(0x5);
    CALL(aPacketSendBytes);

asm_1104fa:
    LD_A(0xe);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    SET_hl(0);
    RES_hl(3);
    RET;


asm_110507:
    LD_A_addr(wc807);
    OR_A_A;
    IF_NZ goto asm_11051f;
    LD_A(0x1);
    LD_addr_A(wc86a);
    LD_HL(wc822);
    RES_hl(4);
    LD_HL(wc821);
    LD_A_hl;
    AND_A(0x17);
    LD_hl_A;
    RET;


asm_11051f:
    LD_A(0x2);
    LD_addr_A(wc86b);
    goto asm_1104fa;


asm_110526:
    CALL(aFunction112724);
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_DE(wMobileSDK_PacketBuffer + 32);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_B(0x1);
    CALL(aFunction111f63);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_A(0x7);
    LD_de_A;
    INC_DE;
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    LD_HL(mUnknown_1120c1);
    CALL(aMobileSDK_CopyString);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0xe);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

void Function110578(void){
    LD_B(0x25);
    CALL(aFunction110596);
    OR_A_A;
    JP_NZ (mFunction1135ba);
    RET;

}

void Function110582(void){
    LD_B(0x26);
    CALL(aFunction110596);
    OR_A_A;
    JP_NZ (mFunction11359d);
    RET;

}

void Function11058c(void){
    LD_B(0x27);
    CALL(aFunction110596);
    OR_A_A;
    JP_NZ (mFunction1135ad);
    RET;

}

void Function110596(void){
    LD_A_addr(wc821);
    BIT_A(0);
    IF_NZ goto asm_1105d9;
    LD_A_addr(wc86a);
    CP_A(0x1);
    IF_NZ goto asm_1105d9;
    LD_A_addr(wc835);
    OR_A_A;
    RET_NZ ;
    LD_A_B;
    LD_addr_A(wcb36);
    XOR_A_A;
    LDH_addr_A(rTAC);
    LD_A_E;
    LD_addr_A(wc86e);
    LD_A_D;
    LD_addr_A(wc86f);
    XOR_A_A;
    LD_addr_A(wc819);
    LD_A_addr(wc870);
    LD_C_A;
    CALL(aMobileAPI_SetTimer);
    LD_HL(wc829);
    LD_A(0x80);
    LD_hli_A;
    LD_A(0xc8);
    LD_hl_A;
    CALL(aFunction1104b0);
    LD_A_addr(wcb36);
    LD_addr_A(wc86a);
    XOR_A_A;
    JP(mFunction110432);


asm_1105d9:
    POP_HL;
    JP(mFunction110226);

}

void Function1105dd(void){
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x1);
    JP_NZ (mFunction110226);
    XOR_A_A;
    LDH_addr_A(rTAC);
    LD_A_addr(wc870);
    LD_C_A;
    CALL(aMobileAPI_SetTimer);
    LD_HL(wc98f);
    LD_A(0x81);
    LD_hli_A;
    LD_A(0xc8);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    LD_A(0xff);
    LD_addr_A(wc86e);
    CALL(aFunction1104b0);
    LD_A(0xd);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

void Function110615(void){
    LD_B(0x15);
    LD_addr_A(wc86e);
    OR_A_A;
    IF_Z goto asm_110625;
    DEC_A;
    IF_Z goto asm_11062c;
    DEC_A;
    JP_Z (mFunction110615_asm_1106c1);
    RET;


asm_110625:
    LD_A(0x19);
    LD_HL(wc83e);
    goto asm_110631;


asm_11062c:
    LD_A(0x6e);
    LD_HL(wc852);


asm_110631:
    PUSH_HL;
    PUSH_BC;
    LD_addr_A(wMobileSDK_PacketBuffer + 91);
    LD_HL(wc829);
    LD_A(0x9d);
    LD_hli_A;
    LD_A(0xcb);
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wMobileSDK_PacketBuffer + 90);
    LD_addr_A(wc86b);
    LD_addr_A(wc9af);
    LD_DE(wMobileSDK_PacketBuffer + 80);
    LD_HL(mMobilePacket_OpenTCPConnection);
    LD_B(lengthof(MobilePacket_OpenTCPConnection));
    CALL(aMobileSDK_CopyBytes);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_DNSQuery);
    LD_B(lengthof(MobilePacket_DNSQuery));
    CALL(aMobileSDK_CopyBytes);
    POP_BC;
    POP_HL;
    PUSH_DE;
    INC_DE;
    LD_A_B;
    LD_BC(0);
    CALL(aMobileSDK_CopyStringLen);
    LD_A_C;
    POP_HL;
    LD_hl_A;
    LD_B_C;
    CALL(aFunction111f63);
    LD_A_addr(wc86e);
    CP_A(0x2);
    IF_NZ goto asm_1106ac;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 128);
    OR_A_A;
    IF_Z goto asm_1106ac;
    LD_HL(wc995);
    LD_A_hli;
    CP_A(0x99);
    IF_NZ goto asm_1106ac;
    LD_A_hli;
    CP_A(0x66);
    IF_NZ goto asm_1106ac;
    LD_A_hli;
    CP_A(0x23);
    IF_NZ goto asm_1106ac;
    LD_A(0x2);
    LD_addr_A(wc86e);
    DEC_A;
    LD_addr_A(wc86b);
    LD_A(0xa3);
    LD_DE(0x0010);
    LD_HL(wc995);
    CALL(aFunction111f02);
    LD_A(0xf);
    LD_addr_A(wc86a);
    JP(mFunction110432);


asm_1106ac:
    LD_HL(wMobileSDK_PacketBuffer);
    LD_A(MOBILE_COMMAND_DNS_QUERY | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0xf);
    LD_addr_A(wc86a);
    JP(mFunction110432);


asm_1106c1:
    LD_B(0x50);
    LD_HL(wc876);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(0x0007);
    ADD_HL_DE;
    LD_DE(wc8ff);

asm_1106d0:
    LD_A_hli;
    LD_de_A;
    CP_A(0x2f);
    IF_Z goto asm_1106da;
    INC_DE;
    DEC_B;
    IF_NZ goto asm_1106d0;


asm_1106da:
    XOR_A_A;
    LD_de_A;
    DEC_HL;
    LD_A_L;
    LD_addr_A(wc876);
    LD_A_H;
    LD_addr_A(wc877);
    LD_HL(wc8ff);
    LD_A(0x50);
    LD_B(0x40);
    JP(mFunction110615_asm_110631);

    return Function1106ef();
}

void Function1106ef(void){
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x2);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86d);
    OR_A_A;
    JP_NZ (mFunction110226);
    PUSH_HL;
    LD_C(0x20);
    CALL(aFunction11039a);
    IF_NC goto asm_110712;
    POP_HL;
    JP(mFunction110231);


asm_110712:
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_DE(wMobileSDK_PacketBuffer + 96);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_DE(wMobileSDK_PacketBuffer + 112);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    INC_DE;
    INC_DE;
    LD_BC(0x0001);
    LD_HL(mUnknown_11209e);
    CALL(aMobileSDK_CopyString);
    POP_HL;
    PUSH_HL;
    LD_B(0xff);

asm_11073b:
    INC_B;
    LD_A_hli;
    OR_A_A;
    IF_Z goto asm_110744;
    CP_A(0x40);
    IF_NZ goto asm_11073b;


asm_110744:
    LD_A_C;
    ADD_A_B;
    ADD_A(0x2);
    LD_addr_A(wMobileSDK_PacketBuffer + 117);
    POP_HL;
    CALL(aMobileSDK_CopyBytes);
    CALL(aFunction11295e);
    LD_A(0x0);
    JP(mFunction110615);

}

void Function110757(void){
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x3);
    JP_NZ (mFunction110226);
    LD_A_addr(wc98a);
    OR_A_A;
    JP_NZ (mFunction110226);
    PUSH_HL;

asm_11076f:
    LD_A_hli;
    OR_A_A;
    IF_NZ goto asm_11076f;
    LD_A_hl;
    OR_A_A;
    JP_Z (mFunction110757_asm_1107fb);
    POP_HL;
    PUSH_HL;
    LD_C(0x20);
    CALL(aFunction11039a);
    IF_C goto asm_1107fb;

asm_110781:
    LD_C(0x81);
    CALL(aFunction11039a);
    IF_C goto asm_1107fb;
    XOR_A_A;
    CP_A_hl;
    IF_NZ goto asm_110781;
    CALL(aFunction112724);
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_B(0x1);
    CALL(aFunction111f63);
    LD_DE(wMobileSDK_PacketBuffer + 12);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_DE(wMobileSDK_PacketBuffer + 18);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    LD_DE(wMobileSDK_PacketBuffer + 19);
    LD_HL(mUnknown_1120a4);
    CALL(aMobileSDK_CopyString);
    POP_HL;
    CALL(aMobileSDK_CopyString);
    LD_A(0x3e);
    LD_de_A;
    INC_DE;
    INC_C;
    LD_A_L;
    LD_addr_A(wc87c);
    LD_A_H;
    LD_addr_A(wc87d);
    CALL(aFunction11295e);
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 17);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wMobileSDK_PacketBuffer + 12);
    LD_D(0x0);
    LD_E_C;
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0x15);
    LD_addr_A(wc86a);
    JP(mFunction110432);


asm_1107fb:
    POP_HL;
    JP(mFunction110231);

}

void Function1107ff(void){
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x3);
    JP_NZ (mFunction110226);
    LD_A_addr(wc98a);
    OR_A_A;
    JP_Z (mFunction110226);
    LD_A_C;
    OR_A_B;
    JP_Z (mFunction110231);
    LD_A_L;
    LD_addr_A(wc87c);
    LD_A_H;
    LD_addr_A(wc87d);
    LD_HL(wc87e);
    LD_A_C;
    LD_hli_A;
    LD_A_B;
    LD_hli_A;
    LD_A_D;
    LD_addr_A(wc86f);
    CALL(aFunction112724);
    LD_HL(wc98a);
    LD_A_hl;
    AND_A(0x1);
    XOR_A(0x1);
    LD_addr_A(wc86b);
    INC_hl;
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_DE(wMobileSDK_PacketBuffer + 6);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_B(0x1);
    CALL(aFunction111f63);
    LD_DE(wMobileSDK_PacketBuffer + 150);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_DE(wMobileSDK_PacketBuffer + 156);
    LD_A_addr(wc86c);
    LD_de_A;
    LD_A_addr(wc86b);
    OR_A_A;
    IF_NZ goto asm_110891;
    LD_BC(0x0001);
    LD_DE(wMobileSDK_PacketBuffer + 157);
    LD_HL(mUnknown_1120ba);
    CALL(aMobileSDK_CopyString);
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 155);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_DE(0x0011);
    LD_HL(wMobileSDK_PacketBuffer + 150);
    LD_B(0x5);
    CALL(aPacketSendBytes);


asm_110891:
    LD_A(0x16);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

void Function110899(void){
    LD_A_addr(wc86a);
    CP_A(0x3);
    JP_NZ (mFunction110226);
    JR(mFunction1108ab);

}

void Function1108a3(void){
    LD_A_addr(wc86a);
    CP_A(0x4);
    JP_NZ (mFunction110226);

    return Function1108ab();
}

void Function1108ab(void){
    LD_HL(wc821);
    BIT_hl(0);
    JP_NZ (mFunction110226);
    CALL(aFunction112724);
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_DE(wMobileSDK_PacketBuffer + 32);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_B(0x1);
    CALL(aFunction111f63);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_A(0x7);
    LD_de_A;
    INC_DE;
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    LD_HL(mUnknown_1120c1);
    CALL(aMobileSDK_CopyString);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0x17);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

void Function110905(void){
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x2);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86d);
    OR_A_A;
    JP_NZ (mFunction110226);
    XOR_A_A;
    LD_addr_A(wc86b);
    PUSH_HL;
    LD_C(0x20);
    CALL(aFunction11039a);
    IF_C goto asm_11092f;
    LD_C(0x22);
    CALL(aFunction11039a);
    IF_NC goto asm_110933;


asm_11092f:
    POP_HL;
    JP(mFunction110231);


asm_110933:
    LD_DE(wMobileSDK_PacketBuffer + 96);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    INC_DE;
    INC_DE;
    LD_HL(mUnknown_1120c8);
    CALL(aMobileSDK_CopyString);
    POP_HL;
    PUSH_HL;
    LD_B(0xff);

asm_11094a:
    INC_B;
    LD_A_hli;
    OR_A_A;
    IF_Z goto asm_110953;
    CP_A(0x40);
    IF_NZ goto asm_11094a;


asm_110953:
    LD_A_B;
    ADD_A(0x6);
    LD_C_A;
    LD_addr_A(wMobileSDK_PacketBuffer + 101);
    POP_HL;
    LD_DE(wMobileSDK_PacketBuffer + 108);
    CALL(aMobileSDK_CopyBytes);

asm_110961:
    LD_A_hli;
    OR_A_A;
    IF_NZ goto asm_110961;
    CALL(aFunction11295e);
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 101);
    LD_BC(0x0006);
    LD_DE(wMobileSDK_PacketBuffer + 172);
    LD_A(0x20);
    CALL(aMobileSDK_CopyStringLen);
    CALL(aFunction11295e);
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 165);
    LD_DE(wMobileSDK_PacketBuffer + 160);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_DE(wMobileSDK_PacketBuffer + 167);
    LD_HL(mUnknown_1120ce);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_DE(wMobileSDK_PacketBuffer + 128);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_A(0x1);
    JP(mFunction110615);

}

void Function1109a4(void){
    LD_HL(wc821);
    BIT_hl(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x4);
    JP_NZ (mFunction110226);
    LD_A_E;
    LD_addr_A(wc86e);
    LD_A_D;
    LD_addr_A(wc86f);
    XOR_A_A;
    LD_addr_A(wc86b);
    CALL(aFunction112729);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_A(0x7);
    LD_de_A;
    INC_DE;
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    LD_HL(mUnknown_1120d4);
    CALL(aMobileSDK_CopyString);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0x18);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

void Function1109f9(void){
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x4);
    JP_NZ (mFunction110226);
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_A_E;
    LD_addr_A(wc86e);
    LD_A_D;
    LD_addr_A(wc86f);
    LD_A_L;
    OR_A_H;
    JP_Z (mFunction110231);
    PUSH_HL;
    CALL(aFunction112729);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_A(0xd);
    LD_de_A;
    INC_DE;
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    LD_HL(mUnknown_1120db);
    CALL(aMobileSDK_CopyString);
    LD_DE(wMobileSDK_PacketBuffer + 12);
    POP_HL;
    CALL(aFunction110d37);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0x1d);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

void Function110a5b(void){
    LD_A_addr(wc821);
    BIT_A(2);
    IF_Z goto asm_110a6d;
    LD_A_addr(wc86a);
    CP_A(0x1a);
    JP_NZ (mFunction110226);
    JP(mFunction110af4);


asm_110a6d:
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x4);
    JP_NZ (mFunction110226);
    LD_A_L;
    OR_A_H;
    JP_Z (mFunction110231);
    LD_A_L;
    LD_addr_A(wc86e);
    LD_A_H;
    LD_addr_A(wc86f);
    LD_HL(wc827);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    INC_DE;
    INC_DE;
    DEC_BC;
    DEC_BC;
    LD_HL(wc98f);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_A_C;
    LD_hli_A;
    LD_A_B;
    LD_hl_A;
    LD_HL(wc829);
    LD_A(0x80);
    LD_hli_A;
    LD_A(0xc8);
    LD_hli_A;
    LD_A(0x80);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_A(0xd);
    LD_de_A;
    INC_DE;
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    LD_HL(mUnknown_1120e8);
    CALL(aMobileSDK_CopyString);
    LD_DE(wMobileSDK_PacketBuffer + 12);
    LD_HL(wc86e);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aFunction110d37);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0x1a);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

void Function110af4(void){
    LD_HL(wc827);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    INC_DE;
    INC_DE;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_E_hl;
    LD_A_B;
    OR_A_C;
    LD_addr_A(wc86e);
    LD_addr_A(wc86f);
    IF_Z goto asm_110b5c;
    DEC_BC;
    DEC_BC;
    LD_A_addr(wc993);
    OR_A_A;
    JP_NZ (mFunction110af4_asm_110bd5);
    LD_A_addr(wc994);
    OR_A_A;
    IF_Z goto asm_110b1c;
    LD_E_A;


asm_110b1c:
    XOR_A_A;
    LD_addr_A(wc994);
    CP_A_B;
    IF_NZ goto asm_110b5c;
    LD_A_E;
    CP_A_C;
    IF_C goto asm_110b5c;
    PUSH_BC;
    SUB_A_C;
    LD_hl_A;
    LD_B_C;
    LD_HL(wc82d);
    LD_A_addr(wc993);
    ADD_A_C;
    LD_hli_A;
    LD_A_B;
    ADC_A(0);
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wc993);
    LD_HL(wMobileSDK_ReceivePacketBuffer + 3);
    LD_A_hli;
    INC_HL;
    SUB_A_E;
    DEC_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_addr(wc829);
    LD_E_A;
    LD_A_addr(wc82a);
    LD_D_A;
    CALL(aMobileSDK_CopyBytes);
    POP_BC;
    LD_HL(wc827);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_C;
    LD_hli_A;
    LD_hl_B;
    RET;


asm_110b5c:
    LD_A_C;
    SUB_A_E;
    LD_C_A;
    LD_A_B;
    SBC_A(0x0);
    LD_B_A;
    LD_A_C;
    LD_hli_A;
    LD_hl_B;
    LD_HL(wc82d);
    LD_A_addr(wc993);
    ADD_A_E;
    LD_hli_A;
    LD_A(0);
    ADC_A(0);
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wc993);
    LD_A_addr(wc86e);
    OR_A_A;
    IF_Z goto asm_110b9b;
    LD_B_E;
    LD_HL(wMobileSDK_ReceivePacketBuffer + 3);
    LD_A_hli;
    INC_HL;
    SUB_A_E;
    DEC_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_addr(wc829);
    LD_E_A;
    LD_A_addr(wc82a);
    LD_D_A;
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc829);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;


asm_110b9b:
    CALL(aFunction1127f3);
    IF_Z goto asm_110bbb;
    NOP;
    LD_HL(wc821);
    RES_hl(2);
    LD_A(0x1);
    LD_addr_A(wc86b);
    LD_DE(0x000b);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wMobileSDK_PacketBuffer + 128);
    LD_B(0x5);
    JP(mPacketSendBytes);


asm_110bbb:
    LD_A(0x4);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    RES_hl(0);
    RES_hl(2);
    LD_HL(wc827);
    LD_A_hli;
    LD_E_A;
    LD_D_hl;
    LD_HL(wc82d);
    LD_B(0x2);
    JP(mMobileSDK_CopyBytes);


asm_110bd5:
    LD_E_A;
    XOR_A_A;
    CP_A_B;
    IF_NZ goto asm_110c05;
    LD_A_E;
    CP_A_C;
    IF_C goto asm_110c05;
    LD_B_C;
    LD_HL(wc993);
    LD_A_hl;
    SUB_A_C;
    LD_hl_A;
    LD_A(0x80);
    SUB_A_E;
    LD_E_A;
    LD_D(0);
    LD_HL(wc880);
    ADD_HL_DE;
    LD_A_addr(wc829);
    LD_E_A;
    LD_A_addr(wc82a);
    LD_D_A;
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc827);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_C;
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    RET;


asm_110c05:
    PUSH_HL;
    PUSH_BC;
    LD_A_addr(wc993);
    LD_B_A;
    LD_A(0x80);
    SUB_A_E;
    LD_E_A;
    LD_D(0);
    LD_HL(wc880);
    ADD_HL_DE;
    LD_A_addr(wc829);
    LD_E_A;
    LD_A_addr(wc82a);
    LD_D_A;
    CALL(aMobileSDK_CopyBytes);
    LD_A_E;
    LD_addr_A(wc829);
    LD_A_D;
    LD_addr_A(wc82a);
    POP_BC;
    LD_A_addr(wc993);
    LD_E_A;
    LD_A_C;
    SUB_A_E;
    LD_C_A;
    LD_A_B;
    SBC_A(0x0);
    LD_B_A;
    LD_A_addr(wc994);
    LD_E_A;
    POP_HL;
    JP(mFunction110af4_asm_110b1c);

    return Function110c3c();
}

void Function110c3c(void){
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x4);
    JP_NZ (mFunction110226);
    LD_A_L;
    OR_A_H;
    JP_Z (mFunction110231);
    LD_A_L;
    LD_addr_A(wc86e);
    LD_A_H;
    LD_addr_A(wc86f);
    CALL(aFunction112729);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_A(0xd);
    LD_de_A;
    INC_DE;
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    LD_HL(mUnknown_1120f5);
    CALL(aMobileSDK_CopyString);
    LD_DE(wMobileSDK_PacketBuffer + 12);
    LD_HL(wc86e);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aFunction110d37);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0x1b);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

void Function110c9e(void){
    LD_A_addr(wc821);
    BIT_A(2);
    IF_Z goto asm_110cb0;
    LD_A_addr(wc86a);
    CP_A(0x1c);
    JP_NZ (mFunction110226);
    JP(mFunction110af4);


asm_110cb0:
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x4);
    JP_NZ (mFunction110226);
    LD_A_L;
    OR_A_H;
    JP_Z (mFunction110231);
    LD_A_L;
    LD_addr_A(wc86e);
    LD_A_H;
    LD_addr_A(wc86f);
    LD_HL(wc827);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    INC_DE;
    INC_DE;
    DEC_BC;
    DEC_BC;
    LD_HL(wc98f);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_A_C;
    LD_hli_A;
    LD_A_B;
    LD_hl_A;
    LD_HL(wc829);
    LD_A(0x80);
    LD_hli_A;
    LD_A(0xc8);
    LD_hli_A;
    LD_A(0x80);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    LD_A(0xe);
    LD_de_A;
    INC_DE;
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    LD_HL(mUnknown_112102);
    CALL(aMobileSDK_CopyString);
    LD_DE(wMobileSDK_PacketBuffer + 11);
    LD_HL(wc86e);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aFunction110d37);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0x1c);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

void Function110d37(void){
    PUSH_BC;
    PUSH_DE;
    LD_B(0);

check_under_10k:
    LD_A(HIGH(10000));
    CP_A_H;
    IF_C goto subtract_10k;
    IF_NZ goto done_10k;
    LD_A(LOW(10000));
    CP_A_L;
    IF_Z goto subtract_10k;
    IF_NC goto done_10k;


subtract_10k:
    INC_B;
    LD_A_B;
    LD_BC(-10000);
    ADD_HL_BC;
    LD_B_A;
    goto check_under_10k;


done_10k:
    LD_A(0x30);
    OR_A_B;
    LD_de_A;
    INC_DE;
    LD_B(0);

check_under_1k:
    LD_A(HIGH(1000));
    CP_A_H;
    IF_C goto subtract_1k;
    IF_NZ goto done_1k;
    LD_A(LOW(1000));
    CP_A_L;
    IF_Z goto subtract_1k;
    IF_NC goto done_1k;


subtract_1k:
    INC_B;
    LD_A_B;
    LD_BC(-1000);
    ADD_HL_BC;
    LD_B_A;
    goto check_under_1k;


done_1k:
    LD_A(0x30);
    OR_A_B;
    LD_de_A;
    INC_DE;
    LD_B(0);

check_under_100:
    LD_A(HIGH(100));
    CP_A_H;
    IF_NZ goto subtract_100;
    LD_A(LOW(100));
    CP_A_L;
    IF_Z goto subtract_100;
    IF_NC goto check_under_10;


subtract_100:
    INC_B;
    LD_A_B;
    LD_BC(-100);
    ADD_HL_BC;
    LD_B_A;
    goto check_under_100;


check_under_10:
    LD_A(0x30);
    OR_A_B;
    LD_de_A;
    INC_DE;
    LD_B(0x0);
    LD_A_L;

subtract_10:
    CP_A(10);
    IF_C goto done_10;
    SUB_A(10);
    INC_B;
    goto subtract_10;


done_10:
    LD_L_A;
    LD_A(0x30);
    OR_A_B;
    LD_de_A;
    INC_DE;
    LD_A(0x30);
    OR_A_L;
    LD_de_A;
    POP_DE;
    LD_L_E;
    LD_H_D;
    LD_B(0x5);

find_first_digit:
    LD_A_hl;
    CP_A(0x30);
    IF_NZ goto found_first_digit;
    INC_HL;
    DEC_B;
    IF_NZ goto find_first_digit;
    goto done;


found_first_digit:
    LD_A(0x5);
    CP_A_B;
    IF_Z goto done;
    SUB_A_B;
    LD_C_A;
    LD_A_addr(wMobileSDK_PacketBuffer + 5);
    SUB_A_C;
    LD_C_A;
    LD_addr_A(wMobileSDK_PacketBuffer + 5);
    PUSH_HL;
    LD_B(0x1);

penultimate_loop:
    INC_B;
    LD_A_hli;
    CP_A(0xd);
    IF_NZ goto penultimate_loop;
    POP_HL;
    CALL(aMobileSDK_CopyBytes);
    POP_HL;
    RET;


done:
    POP_BC;

last_loop:
    LD_A_de;
    INC_DE;
    CP_A(0xa);
    IF_NZ goto last_loop;
    RET;

}

void Function110ddd(void){
    LD_A_addr(wc821);
    BIT_A(2);
    LD_A_addr(wc86a);
    IF_Z goto asm_110e00;
    CP_A(0x13);
    JP_Z (mFunction111044);
    CP_A(0x1f);
    JP_Z (mFunction111044);
    CP_A(0x21);
    JP_Z (mFunction111044);
    JP(mFunction110226);


asm_110df9:
    POP_HL;

asm_110dfa:
    POP_HL;
    POP_HL;
    POP_HL;

asm_110dfd:
    JP(mFunction110231);


asm_110e00:
    CP_A(0x2);
    JP_NZ (mFunction110226);
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86d);
    OR_A_A;
    JP_NZ (mFunction110226);
    LD_A_L;
    LD_addr_A(wc9b5);
    LD_A_H;
    LD_addr_A(wc9b6);
    XOR_A_A;
    LD_addr_A(wc989);
    LD_addr_A(wc9a5);
    LD_addr_A(wc98a);
    LD_addr_A(wc993);
    LD_A_hli;
    LD_addr_A(wc833);
    LD_A_hli;
    LD_addr_A(wc834);
    INC_HL;
    INC_HL;
    LD_A_L;
    LD_addr_A(wc97f);
    LD_A_H;
    LD_addr_A(wc980);
    DEC_HL;
    DEC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A(0x80);
    CP_A_L;
    IF_NZ goto asm_110e4a;
    LD_A(0xc8);
    CP_A_H;
    IF_Z goto asm_110dfd;


asm_110e4a:
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_HL;
    LD_B(sizeof(URIPrefix));
    LD_DE(mURIPrefix);

asm_110e53:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto asm_110df9;
    INC_HL;
    DEC_B;
    IF_NZ goto asm_110e53;
    PUSH_HL;
    LD_B(lengthof(HTTPUploadURL));
    LD_C(0x0);
    LD_DE(mHTTPUploadURL);

asm_110e64:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto asm_110e70;
    INC_HL;
    DEC_B;
    IF_NZ goto asm_110e64;
    POP_HL;
    goto asm_110df9;


asm_110e70:
    POP_HL;
    PUSH_HL;
    LD_B(lengthof(HTTPRankingURL));
    LD_C(0x0);
    LD_DE(mHTTPRankingURL);

asm_110e79:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto asm_110e86;
    INC_HL;
    DEC_B;
    IF_NZ goto asm_110e79;
    POP_HL;
    JP(mFunction110ddd_asm_110df9);


asm_110e86:
    POP_HL;
    PUSH_HL;
    LD_B(sizeof(HTTPUtilityURL));
    LD_C(0x0);
    LD_DE(mHTTPUtilityURL);

asm_110e8f:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto asm_110ea2;
    INC_HL;
    DEC_B;
    IF_NZ goto asm_110e8f;
    POP_HL;
    LD_A(0x1);
    LD_addr_A(wc98a);
    LD_C(0x1);
    goto asm_110eb3;


asm_110ea2:
    POP_HL;
    LD_B(sizeof(HTTPDownloadURL));
    LD_C(0x0);
    LD_DE(mHTTPDownloadURL);

asm_110eaa:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto asm_110ecb;
    INC_HL;
    DEC_B;
    IF_NZ goto asm_110eaa;


asm_110eb3:
    LD_HL(wc97f);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_C(0x12);
    CALL(aFunction11039a);
    JP_C (mFunction110ddd_asm_110df9);
    LD_C(0x12);
    CALL(aFunction11039a);
    JP_C (mFunction110ddd_asm_110df9);
    LD_C(0x1);


asm_110ecb:
    LD_A_C;
    LD_addr_A(wc98f);
    LD_addr_A(wMobileSDK_ReceivePacketBuffer + 128);
    POP_HL;
    CALL(aFunction1111d7);
    LD_A_B;
    CP_A(0x4);
    IF_C goto asm_110ee3;
    JP_NZ (mFunction110ddd_asm_110dfa);
    XOR_A_A;
    OR_A_C;
    JP_NZ (mFunction110ddd_asm_110dfa);


asm_110ee3:
    LD_HL(wc98b);
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    POP_BC;
    POP_DE;
    POP_HL;
    LD_A_L;
    LD_addr_A(wc876);
    LD_A_H;
    LD_addr_A(wc877);
    LD_HL(wc872);
    LD_A_C;
    LD_hli_A;
    LD_A_B;
    LD_hli_A;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    INC_HL;
    INC_HL;
    XOR_A_A;
    LD_addr_A(wc994);

    return Function110f07();
}

void Function110f07(void){
    LD_HL(wc833);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    OR_A_H;
    IF_Z goto asm_110f12;
    XOR_A_A;
    LD_hl_A;


asm_110f12:
    LD_HL(wc991);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    LD_HL(wc866);
    LD_A_hli;
    OR_A_hl;
    INC_HL;
    OR_A_hl;
    INC_HL;
    OR_A_hl;
    IF_NZ goto asm_110f28;
    LD_A(0x2);
    JP(mFunction110615);


asm_110f28:
    LD_A(0x2);
    LD_addr_A(wc86e);
    LD_A(0x1f);
    LD_addr_A(wMobileSDK_PacketBuffer + 10);
    LD_A(0x90);
    LD_addr_A(wMobileSDK_PacketBuffer + 11);
    LD_A(0x1);
    LD_addr_A(wc86b);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_OpenTCPConnection);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc866);
    LD_B(0x4);
    CALL(aMobileSDK_CopyBytes);
    INC_DE;
    INC_DE;
    LD_B(0x6);
    CALL(aFunction111f63);
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 128);
    OR_A_A;
    IF_Z goto asm_110f95;
    LD_HL(wc995);
    LD_A_hli;
    CP_A(0x99);
    IF_NZ goto asm_110f8a;
    LD_A_hli;
    CP_A(0x66);
    IF_NZ goto asm_110f8a;
    LD_A_hli;
    CP_A(0x23);
    IF_NZ goto asm_110f8a;
    LD_A(0x2);
    LD_addr_A(wc86e);
    DEC_A;
    LD_addr_A(wc86b);
    LD_A(0xa3);
    LD_DE(0x0010);
    LD_HL(wc995);
    CALL(aFunction111f02);
    LD_A(0xf);
    LD_addr_A(wc86a);
    JP(mFunction110432);


asm_110f8a:
    LD_HL(wMobileSDK_PacketBuffer);
    LD_DE(wc995);
    LD_B(0x10);
    CALL(aMobileSDK_CopyBytes);


asm_110f95:
    LD_DE(0x0010);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_A(MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0xf);
    LD_addr_A(wc86a);
    JP(mFunction110432);

}

void Function111044(void){
    LD_HL(wc827);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    INC_DE;
    INC_DE;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_E_hl;
    LD_A_B;
    OR_A_C;
    LD_addr_A(wc86e);
    LD_addr_A(wc86f);
    DEC_BC;
    DEC_BC;
    JP_Z (mFunction1111ca);
    LD_A_addr(wc991);
    OR_A_A;
    CALL_NZ (aFunction11115f);
    XOR_A_A;
    CP_A_E;
    JP_Z (mFunction111044_asm_1110eb);
    XOR_A_A;
    CP_A_B;
    IF_NZ goto asm_1110ac;
    LD_A_E;
    CP_A_C;
    IF_C goto asm_1110ac;
    PUSH_BC;
    SUB_A_C;
    LD_hl_A;
    LD_B_C;
    LD_HL(wc82d);
    LD_A_C;
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    LD_HL(wMobileSDK_ReceivePacketBuffer + 3);
    LD_A_hli;
    INC_HL;
    SUB_A_E;
    DEC_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_addr(wc829);
    LD_E_A;
    LD_A_addr(wc82a);
    LD_D_A;
    CALL(aMobileSDK_CopyBytes);
    POP_BC;
    LD_A_addr(wc991);
    LD_L_A;
    LD_H(0);
    ADD_HL_BC;
    LD_C_L;
    LD_B_H;
    XOR_A_A;
    LD_addr_A(wc991);
    LD_HL(wc827);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_C;
    LD_hli_A;
    LD_hl_B;
    RET;


asm_1110ac:
    LD_A_C;
    SUB_A_E;
    LD_C_A;
    LD_A_B;
    SBC_A(0x0);
    LD_B_A;
    LD_A_C;
    LD_hli_A;
    LD_hl_B;
    LD_HL(wc82d);
    LD_A_addr(wc991);
    ADD_A_E;
    LD_hli_A;
    LD_A(0);
    ADC_A(0);
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wc991);
    LD_A_addr(wc86e);
    OR_A_A;
    IF_Z goto asm_1110eb;
    LD_B_E;
    LD_HL(wMobileSDK_ReceivePacketBuffer + 3);
    LD_A_hli;
    INC_HL;
    SUB_A_E;
    DEC_A;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_addr(wc829);
    LD_E_A;
    LD_A_addr(wc82a);
    LD_D_A;
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc829);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;


asm_1110eb:
    NOP;
    LD_A(0x2);
    LD_addr_A(wc989);
    LD_HL(wc821);
    RES_hl(2);
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    IF_Z goto asm_111144;
    LD_DE(0x000b);
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    LD_A(0x1);
    LD_addr_A(wc86b);
    RET;

    LD_HL(wc827);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wc82d);
    LD_hli_A;
    LD_A_addr(wc82e);
    LD_hl_A;
    LD_HL(wc98f);
    INC_hl;
    LD_A(0xf);
    LD_addr_A(wc86a);
    LD_A(0x1);
    LD_addr_A(wc86b);
    LD_A_addr(wc86d);
    LD_addr_A(wc86e);
    XOR_A_A;
    LD_addr_A(wc989);
    LD_A(0xa3);
    LD_DE(0x0010);
    LD_HL(wc995);
    JP(mFunction111f02);


asm_111144:
    RES_hl(0);
    LD_HL(wc827);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wc82d);
    LD_hli_A;
    LD_A_addr(wc82e);
    LD_hl_A;
    LD_A(0x2);
    LD_addr_A(wc86a);
    XOR_A_A;
    LD_addr_A(wc86d);
    NOP;
    RET;

}

void Function11115f(void){
    LD_E_A;
    XOR_A_A;
    CP_A_B;
    IF_NZ goto asm_111168;
    LD_A_C;
    CP_A_E;
    IF_C goto asm_1111a2;


asm_111168:
    PUSH_HL;
    PUSH_BC;
    LD_B_E;
    LD_C_E;
    LD_A_addr(wc993);
    SUB_A_E;
    LD_E_A;
    LD_D(0);
    LD_HL(wc880);
    ADD_HL_DE;
    LD_A_addr(wc829);
    LD_E_A;
    LD_A_addr(wc82a);
    LD_D_A;
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc829);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;
    LD_E_C;
    LD_A_C;
    LD_HL(wc82d);
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    POP_BC;
    LD_A_C;
    SUB_A_E;
    LD_C_A;
    LD_A_B;
    SBC_A(0x0);
    LD_B_A;
    LD_A_addr(wc992);
    LD_addr_A(wc82b);
    LD_E_A;
    POP_HL;
    RET;


asm_1111a2:
    LD_A_E;
    SUB_A_C;
    LD_addr_A(wc991);
    LD_A_addr(wc993);
    SUB_A_E;
    LD_E_A;
    LD_D(0);
    LD_HL(wc880);
    ADD_HL_DE;
    LD_A_addr(wc829);
    LD_E_A;
    LD_A_addr(wc82a);
    LD_D_A;
    LD_B_C;
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc827);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_C;
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    POP_AF;
    RET;

}

void Function1111ca(void){
    LD_HL(wc821);
    RES_hl(2);
    LD_A(0x6);
    LD_addr_A(wc86b);
    JP(mFunction112430);

}

void Function1111d7(void){
    PUSH_HL;
    LD_HL(wc866);
    LD_A_hli;
    OR_A_hl;
    INC_HL;
    OR_A_hl;
    INC_HL;
    OR_A_hl;
    POP_HL;
    IF_NZ goto asm_1111ee;
    LD_DE(0x0007);
    ADD_HL_DE;

asm_1111e8:
    LD_A_hli;
    CP_A(0x2f);
    IF_NZ goto asm_1111e8;
    DEC_HL;


asm_1111ee:
    LD_BC(-1);

asm_1111f1:
    LD_A_hli;
    INC_BC;
    OR_A_A;
    IF_NZ goto asm_1111f1;
    LD_HL(wc87a);
    LD_A_C;
    LD_hli_A;
    LD_A_B;
    LD_hl_A;
    RET;

}

void Function1111fe(void){
    LD_A_addr(wc821);
    BIT_A(2);
    LD_A_addr(wc86a);
    JP_NZ (mFunction1113ea);
    CP_A(0x2);
    JP_NZ (mFunction110226);
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86d);
    OR_A_A;
    JP_NZ (mFunction110226);
    XOR_A_A;
    LD_addr_A(wc989);
    LD_addr_A(wc98a);
    LD_addr_A(wc993);
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    PUSH_HL;
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }
    LD_A_hli;
    LD_addr_A(wc833);
    LD_A_hli;
    LD_addr_A(wc834);
    INC_HL;
    INC_HL;
    LD_A_L;
    LD_addr_A(wc97f);
    LD_A_H;
    LD_addr_A(wc980);
    DEC_HL;
    DEC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A(0x80);
    CP_A_L;
    IF_NZ goto asm_111251;
    LD_A(0xc8);
    CP_A_H;
    JP_Z (mFunction1113f7);


asm_111251:
    LD_B(lengthof(URIPrefix));
    LD_DE(mURIPrefix);

asm_111256:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    JP_NZ (mFunction1113f7);
    INC_HL;
    DEC_B;
    IF_NZ goto asm_111256;
    PUSH_HL;
    LD_B(lengthof(HTTPDownloadURL));
    LD_C(0x0);
    LD_DE(mHTTPDownloadURL);

asm_111268:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto asm_111275;
    INC_HL;
    DEC_B;
    IF_NZ goto asm_111268;
    POP_HL;
    JP(mFunction1113f7);


asm_111275:
    POP_HL;
    PUSH_HL;
    LD_B(lengthof(HTTPRankingURL));
    LD_C(0x0);
    LD_DE(mHTTPRankingURL);

asm_11127e:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto asm_11128f;
    INC_HL;
    DEC_B;
    IF_NZ goto asm_11127e;
    LD_A(0x2);
    LD_addr_A(wc98a);
    POP_HL;
    goto asm_1112a0;


asm_11128f:
    POP_HL;
    LD_B(lengthof(HTTPUploadURL));
    LD_C(0x0);
    LD_DE(mHTTPUploadURL);

asm_111297:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto asm_1112cc;
    INC_HL;
    DEC_B;
    IF_NZ goto asm_111297;


asm_1112a0:
    LD_A_hli;
    OR_A_A;
    IF_NZ goto asm_1112a0;

asm_1112a4:
    LD_A_hld;
    CP_A(0x2f);
    IF_NZ goto asm_1112a4;
    INC_HL;
    INC_HL;
    LD_A_hl;
    CP_A(0x30);
    IF_C goto asm_1112cc;
    CP_A(0x3a);
    IF_NC goto asm_1112cc;
    LD_HL(wc97f);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_C(0x12);
    CALL(aFunction11039a);
    JP_C (mFunction1113f7);
    LD_C(0x12);
    CALL(aFunction11039a);
    JP_C (mFunction1113f7);
    LD_C(0x1);


asm_1112cc:
    LD_A_C;
    LD_addr_A(wc98f);
    LD_addr_A(wMobileSDK_ReceivePacketBuffer + 128);
    POP_HL;
    LD_DE(0x0006);
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aFunction1111d7);
    LD_A_B;
    CP_A(0x4);
    IF_C goto asm_1112eb;
    JP_NZ (mFunction1113f8);
    XOR_A_A;
    OR_A_C;
    JP_NZ (mFunction1113f8);


asm_1112eb:
    POP_BC;
    POP_DE;
    POP_HL;
    LD_A_L;
    LD_addr_A(wc876);
    LD_A_H;
    LD_addr_A(wc877);
    LD_HL(wc872);
    LD_A_C;
    LD_hli_A;
    LD_A_B;
    LD_hli_A;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    INC_HL;
    INC_HL;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;
    CALL(aFunction111335);
    LD_HL(wc876);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hli;
    LD_addr_A(wc9aa);
    LD_A_hli;
    LD_addr_A(wc9ab);
    LD_A_hli;
    LD_addr_A(wc9ac);
    LD_A_hli;
    LD_addr_A(wc9ad);
    INC_HL;
    INC_HL;
    LD_A_hli;
    LD_addr_A(wc876);
    LD_A_hl;
    LD_addr_A(wc877);
    LD_A_addr(wc98f);
    XOR_A(0x1);
    LD_addr_A(wc994);
    JP(mFunction110f07);

}

void Function111335(void){
    LD_HL(wc876);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    INC_HL;
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    XOR_A_A;
    LD_addr_A(wc8c9);

asm_111344:
    LD_DE(0x8ad0);
    ADD_HL_DE;
    IF_NC goto asm_11134e;
    ADD_A(0x3);
    goto asm_111344;


asm_11134e:
    LD_DE(0x7530);
    ADD_HL_DE;

asm_111352:
    LD_DE(0xd8f0);
    ADD_HL_DE;
    IF_NC goto asm_11135b;
    INC_A;
    goto asm_111352;


asm_11135b:
    LD_DE(0x2710);
    ADD_HL_DE;
    LD_addr_A(wc8c6);
    XOR_A_A;

asm_111363:
    LD_DE(0xf448);
    ADD_HL_DE;
    IF_NC goto asm_11136d;
    ADD_A(0x30);
    goto asm_111363;


asm_11136d:
    LD_DE(0x0bb8);
    ADD_HL_DE;

asm_111371:
    LD_DE(0xfc18);
    ADD_HL_DE;
    IF_NC goto asm_11137b;
    ADD_A(0x10);
    goto asm_111371;


asm_11137b:
    LD_DE(0x03e8);
    ADD_HL_DE;

asm_11137f:
    LD_DE(0xfed4);
    ADD_HL_DE;
    IF_NC goto asm_111389;
    ADD_A(0x3);
    goto asm_11137f;


asm_111389:
    LD_DE(0x012c);
    ADD_HL_DE;

asm_11138d:
    LD_DE(0xff9c);
    ADD_HL_DE;
    IF_NC goto asm_111396;
    INC_A;
    goto asm_11138d;


asm_111396:
    LD_DE(0x0064);
    ADD_HL_DE;
    LD_addr_A(wc8c7);
    XOR_A_A;

asm_11139e:
    LD_DE(0xffe2);
    ADD_HL_DE;
    IF_NC goto asm_1113a8;
    ADD_A(0x30);
    goto asm_11139e;


asm_1113a8:
    LD_DE(0x001e);
    ADD_HL_DE;

asm_1113ac:
    LD_DE(0xfff6);
    ADD_HL_DE;
    IF_NC goto asm_1113b6;
    ADD_A(0x10);
    goto asm_1113ac;


asm_1113b6:
    LD_DE(0x000a);
    ADD_HL_DE;
    ADD_A_L;
    LD_addr_A(wc8c8);
    LD_DE(wc9a5);
    LD_HL(wc8c6);
    LD_A_hli;
    OR_A(0x30);
    LD_de_A;
    INC_DE;
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    OR_A(0x30);
    LD_de_A;
    INC_DE;
    LD_A_hli;
    AND_A(0xf);
    OR_A(0x30);
    LD_de_A;
    INC_DE;
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    OR_A(0x30);
    LD_de_A;
    INC_DE;
    LD_A_hl;
    AND_A(0xf);
    OR_A(0x30);
    LD_de_A;
    INC_DE;
    RET;

}

void Function1113ea(void){
    CP_A(0x14);
    JP_Z (mFunction111044);
    CP_A(0x24);
    JP_Z (mFunction111044);
    JP(mFunction110226);

}

void Function1113f7(void){
    POP_HL;

    return Function1113f8();
}

void Function1113f8(void){
    POP_HL;
    POP_HL;
    POP_HL;
    JP(mFunction110231);

}

// MobileAPI17
void Function1113fe(mobile_api_data_s* data){
    uint8_t* hl = data->hl;
    // LD_A_addr(wc822);
    // BIT_A(4);
    // JP_Z (mFunction1113fe_asm_11147f);
    // BIT_A(7);
    // JP_NZ (mFunction1113fe_asm_11147f);
    // LD_A_addr(wc821);
    // BIT_A(0);
    // JP_NZ (mFunction1113fe_asm_11147f);
    if(!bit_test(wram->wc822, 4) || bit_test(wram->wc822, 7) || bit_test(wram->wc821, 0)) {
    // asm_11147f:
        // CALL(aFunction110226);
        Function110226();
        // LD_A(0xff);
        data->a = 0xff;
        // RET;
        return;
    }

    do {
    // asm_111413:
        DelayFrame();
        // LD_A_addr(wc800);
        // OR_A_A;
        // IF_NZ goto asm_111413;
    } while(wram->wc800 != 0); // Idle loop?
    // NOP;
    // LD_A_addr(wc821);
    // BIT_A(3);
    // JP_NZ (mFunction1113fe_asm_11147b);
    if(bit_test(wram->wc821, 3)) {
    // asm_11147b:
        // NOP;
        // LD_A(0x1);
        data->a = 0x1;
        // RET;
        return;
    }
    // LD_A_addr(wc807);
    // OR_A_A;
    // IF_NZ goto asm_111436;
    if(wram->wc807 == 0x0) {
        // LD_HL(wc821);
        // SET_hl(1);
        bit_set(wram->wc821, 1);
        // LD_A(0x23);
        // LD_addr_A(wc80f);
        wram->wc80f = 0x23;
        // LD_A(0xff);
        // data->a = 0xff;
        // NOP;
        // RET;
        return;
    }

// asm_111436:
    // XOR_A_A;
    // LD_addr_A(wc86b);
    wram->wc86b = 0x0;
    // PUSH_HL;
    // LD_HL(wc829);
    // XOR_A_A;
    // LD_hli_A;
    wram->wc829 = 0x0;
    // LD_hli_A;
    wram->wc82a = 0x0;
    // LD_hli_A;
    wram->wc82b = 0x0;
    // LD_hl_A;
    wram->wc82c = 0x0;
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_TransferData);
    // LD_B(0x5);
    // CALL(aMobileSDK_CopyBytes);
    uint8_t* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_TransferData, 0x5);
    // POP_HL;
    // LD_A_hli;
    uint8_t count = *(hl++);
    // OR_A_A;
    // IF_Z goto asm_111485;
    // CP_A(0x81);
    // IF_NC goto asm_111485;
    if(count == 0x0 || count >= 0x81) {
    // asm_111485:
        // NOP;
        // CALL(aFunction110231);
        Function110231();
        // LD_A(0xff);
        data->a = 0xff;
        // RET;
        return;
    }
    // LD_C_A;
    // INC_A;
    // INC_A;
    // LD_de_A;
    // INC_DE;
    *(de++) = count + 2;
    // LD_A(0xff);
    // LD_de_A;
    // INC_DE;
    *(de++) = 0xff;
    // LD_A_C;
    // LD_de_A;
    // INC_DE;
    *(de++) = count;
    // LD_B_C;
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(de, hl, count);
    // LD_B_C;
    // INC_B;
    // INC_B;
    // CALL(aFunction111f63);
    Function111f63(de, count);
    // LD_HL(wc822);
    // SET_hl(7);
    bit_set(wram->wc822, 7);
    // LD_HL(wc821);
    // SET_hl(0);
    bit_set(wram->wc821, 0);
    // LD_A(0x0);
    data->a = 0x0;
    // NOP;
    // RET;
}

void Function11148c(void){
    LD_A_addr(wc822);
    BIT_A(4);
    JP_Z (mFunction110226);
    LD_A_addr(wc821);
    BIT_A(0);
    JP_NZ (mFunction110226);
    BIT_A(3);
    JP_Z (mFunction110226);
    LD_E_L;
    LD_D_H;
    LD_A_addr(wc992);
    OR_A_A;
    IF_NZ goto asm_111507;
    LD_A_addr(wc993);
    LD_C_A;
    LD_B(0);
    LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
    ADD_HL_BC;
    LD_A_hli;
    OR_A_A;
    IF_Z goto asm_1114bb;
    CP_A(0x81);
    IF_C goto asm_1114bd;


asm_1114bb:
    LD_A(0x80);


asm_1114bd:
    LD_B_A;
    INC_C;
    ADD_A_C;
    LD_addr_A(wc993);
    LD_A_addr(wc994);
    DEC_A;
    SUB_A_B;
    LD_C_A;
    LD_addr_A(wc994);
    LD_A_B;
    LD_de_A;
    INC_DE;
    CALL(aMobileSDK_CopyBytes);

asm_1114d2:
    XOR_A_A;
    OR_A_C;
    IF_NZ goto asm_1114dc;
    LD_HL(wc821);
    RES_hl(3);
    RET;


asm_1114dc:
    LD_A_hli;
    OR_A_A;
    IF_Z goto asm_1114e4;
    CP_A(0x81);
    IF_C goto asm_1114e6;


asm_1114e4:
    LD_A(0x80);


asm_1114e6:
    CP_A_C;
    RET_C ;
    LD_addr_A(wc991);
    DEC_C;
    LD_A_C;
    OR_A_A;
    IF_Z goto asm_111500;
    LD_addr_A(wc992);
    LD_B_A;
    LD_DE(wc880);
    CALL(aMobileSDK_CopyBytes);

asm_1114fa:
    LD_HL(wc821);
    RES_hl(3);
    RET;


asm_111500:
    LD_A(0xff);
    LD_addr_A(wc992);
    goto asm_1114fa;


asm_111507:
    CP_A(0xff);
    IF_NZ goto asm_11150c;
    XOR_A_A;


asm_11150c:
    LD_B_A;
    LD_A_addr(wc991);
    SUB_A_B;
    LD_C_A;
    LD_HL(wc880);
    LD_A_addr(wc991);
    LD_de_A;
    INC_DE;
    LD_A_B;
    OR_A_A;
    IF_Z goto asm_111521;
    CALL(aMobileSDK_CopyBytes);


asm_111521:
    LD_HL(wMobileSDK_ReceivePacketBuffer + 5);
    LD_B_C;
    CALL(aMobileSDK_CopyBytes);
    PUSH_HL;
    LD_A_C;
    INC_A;
    LD_addr_A(wc993);
    LD_B_A;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    SUB_A_B;
    LD_addr_A(wc994);
    LD_C_A;
    XOR_A_A;
    LD_HL(wc991);
    LD_hli_A;
    LD_hl_A;
    POP_HL;
    goto asm_1114d2;

    return Function111540();
}

void Function111540(void){
    NOP;

    return Function111541();
}

void Function111541(void){
    LD_HL(wc821);
    BIT_hl(0);
    JP_NZ (mFunction110226);
    LD_A_addr(wc86a);
    CP_A(0x5);
    JP_NC (mFunction110226);
    LD_addr_A(wc985);
    LD_A_E;
    LD_addr_A(wc86e);
    LD_A_D;
    LD_addr_A(wc86f);
    LD_A_addr(wc807);
    CP_A(0x2);
    IF_C goto asm_111582;
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_A(MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
    LD_HL(mMobilePacket_TelephoneStatus);
    CALL(aPacketSendEmptyBody);

asm_11156f:
    LD_A_addr(wMobileAPIIndex);
    CP_A(0x40);
    IF_NZ goto asm_11157a;
    LD_A(0x2c);
    goto asm_11157c;


asm_11157a:
    LD_A(0x1e);


asm_11157c:
    LD_addr_A(wc86a);
    JP(mFunction110432);


asm_111582:
    XOR_A_A;
    LDH_addr_A(rTAC);
    LD_A_addr(wc870);
    LD_C_A;
    CALL(aMobileAPI_SetTimer);
    CALL(aFunction1104b0);
    LD_A(0x1);
    LD_addr_A(wc86b);
    goto asm_11156f;

    return Function111596();
}

void Function111596(void){
    LD_HL(wc86a);
    LD_A_hl;
    CP_A(0x1);
    JP_Z (mFunction110226);
    CP_A(0x2a);
    JP_Z (mFunction110226);
    LD_A_addr(wc800);
    BIT_A(1);
    IF_NZ goto asm_1115af;
    LD_A(0x2a);
    JR(mFunction1115e4);


asm_1115af:
    LD_A_addr(wMobileSDK_SendCommandID);
    CP_A(0x92);
    IF_NZ goto asm_1115dd;
    LD_A(0x2a);
    LD_B(0x0);
    NOP;
    LD_hli_A;
    LD_hl_B;
    LD_HL(wc822);
    RES_hl(5);
    RES_hl(0);
    XOR_A_A;
    LD_addr_A(wc80b);
    LD_addr_A(wc800);
    LD_A(0x8);
    LD_addr_A(wc807);
    CALL(aResetReceivePacketBuffer);
    CALL(aFunction11164f);
    LD_HL(wc821);
    SET_hl(0);
    NOP;
    RET;


asm_1115dd:
    LD_A(0x2a);
    LD_hli_A;
    LD_A(0x1);
    LD_hl_A;
    RET;

}

void Function1115e4(void){
    NOP;
    PUSH_AF;
    LD_HL(wc821);
    SET_hl(0);
    LD_A(0x1);
    LD_addr_A(wc86b);
    LD_A_addr(wc86d);
    OR_A_A;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    IF_Z goto asm_111609;
    CP_A(0x9f);
    IF_Z goto asm_11160d;
    CP_A(0xa4);
    IF_Z goto asm_11160d;

asm_111601:
    CALL(aFunction112430);

asm_111604:
    POP_AF;
    LD_addr_A(wc86a);
    RET;


asm_111609:
    CP_A(0xa3);
    IF_Z goto asm_111601;


asm_11160d:
    NOP;
    goto asm_111604;

    return Function111610();
}

void Function111610(void){
    LD_HL(wc86a);
    LD_A_hl;
    DEC_A;
    JP_Z (mFunction110226);
    DEC_A;
    JP_Z (mFunction110226);
    LD_A_addr(wc800);
    OR_A_A;
    IF_NZ goto asm_111626;
    LD_A(0x28);
    JR(mFunction1115e4);


asm_111626:
    LD_A(0x28);
    LD_B(0x2);
    LD_hli_A;
    LD_hl_B;
    RET;

}

// MobileAPI1B
// ClearMobileSDKData
void Function11162d(mobile_api_data_s* data){
    (void)data;
    // LD_A_addr(wc86a);
    // CP_A(0x1);
    // JP_NZ (mFunction110226);
    if(wram->wc86a != 0x1)
        return Function110226();
    // XOR_A_A;
    // LD_HL(wMobileSDK_PacketBuffer);
    // LD_hli_A;
    wram->wMobileSDK_PacketBuffer[0] = 0x0;
    // LD_hl_A;
    wram->wMobileSDK_PacketBuffer[1] = 0x0;
    // CALL(aFunction111686);
    Function111686();
    // CALL(aResetReceivePacketBuffer);
    ResetReceivePacketBuffer();
    // LD_BC(0x0452);
// Clear mobile SDK data
    uint16_t bc = 0x0452;
    // LD_HL(wc800);
    uint8_t* hl = &wram->wc800;

    do {
    // asm_111647:
        // XOR_A_A;
        // LD_hli_A;
        *(hl++) = 0x0;
        // DEC_BC;
        // LD_A_C;
        // OR_A_B;
        // IF_NZ goto asm_111647;
    } while(--bc != 0);
    // RET;
}

void Function11164f(void){
    // LD_HL(wc815);
    // XOR_A_A;
    // LD_hli_A;
    wram->wc815 = 0x0;
    // LD_A_addr(wc81f);
    // LD_B_A;
    uint8_t b = wram->wc81f;
    // LD_A_addr(wMobileSDK_AdapterType); // Useless
    // LD_A_B;
    // SRL_A;
    // SRL_A;
    // ADD_A_B;
    // ADD_A_B;
    // LD_hl_A;
    wram->wc816 = (wram->wc816 & 0xff00) | ((b >> 2) + (b * 2));
    // RET;
}

// Mobile_AppendReceivedByte
void Function111664(uint8_t c){
    // LD_HL(wMobileSDK_ReceivedBytes);
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // LD_A_addr(wMobileSDK_SendCommandID);
    // CP_A(0xff);
    // IF_Z goto asm_111679;
    // LD_A_addr(wc822);
    // BIT_A(0);
    // IF_Z goto asm_11167c;
// asm_111679:
    // LD_HL(wMobileSDK_ReceivePacketBufferAlt);
    uint8_t* hl = (wram->wMobileSDK_SendCommandID == 0xff || bit_test(wram->wc822, 0))? wram->wMobileSDK_ReceivePacketBuffer: wram->wMobileSDK_ReceivePacketBufferAlt;

// asm_11167c:
    // ADD_HL_DE;
    // LD_hl_C;
    hl[wram->wMobileSDK_ReceivedBytes] = c;
    // INC_DE;
    // LD_HL(wMobileSDK_ReceivedBytes);
    // LD_A_E;
    // LD_hli_A;
    // LD_hl_D;
    wram->wMobileSDK_ReceivedBytes++;
    // RET;
}

void Function111686(void){
    // XOR_A_A;
    // LDH_addr_A(rTAC);
    gb_write(rTAC, 0x0);
    // LD_C(0xff);
    // LDH_A_c;
    // AND_A(0xf3);
    // LDH_c_A;
    gb_write(0xffff, gb_read(0xffff) & 0xf3); // ...why?
    // LD_A_addr(wMobileSDK_PacketBuffer + 1);
    // LD_addr_A(wc86a);
    wram->wc86a = wram->wMobileSDK_PacketBuffer[1];
    // LD_A_addr(wMobileSDK_PacketBuffer);
    // LD_C_A;
    // LD_HL(wc821);
    // LD_A_hl;
    // OR_A_C;
    // LD_hl_A;
    wram->wc821 |= wram->wMobileSDK_PacketBuffer[0];
    // RET;
}

void Function1116a0(void){
    LD_A(0x1);
    JR(mFunction1116a9);

}

void Function1116a4(void){
    SET_hl(1);
    LD_A_addr(wc86a);

    return Function1116a9();
}

void Function1116a9(void){
    LD_addr_A(wMobileSDK_PacketBuffer + 1);
    LD_HL(wc815);
    XOR_A_A;
    LD_hli_A;
    LD_A_addr(wc81f);
    RLA;
    LD_hl_A;
    LD_HL(wc821);
    LD_A_hl;
    LD_B_A;
    AND_A(0xd);
    LD_hl_A;
    LD_A(0x2);
    AND_A_B;
    LD_addr_A(wMobileSDK_PacketBuffer);
    RET;

}

void v_MobileReceive(void){
    LD_A_addr(wc800);
    RRCA;
    JP_NC (mFunction1118bc);
    RRCA;
    JP_C (mFunction1117e7);
    LD_HL(wc801);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    DEC_DE;
    LD_A_D;
    LD_hld_A;
    LD_A_E;
    LD_hl_A;
    CP_A(0x2);
    JP_NC (mFunction1118bc);
    LD_A_D;
    OR_A_A;
    JP_NZ (mFunction1118bc);
    LD_HL(wc808);
    ADD_HL_DE;
    LDH_A_addr(rSB);
    LD_hl_A;
    LD_A(0x8);
    CP_A_L;
    JP_NZ (mFunction1118bc);
    LD_A_addr(wMobileSDK_SendCommandID);
    CP_A(0xff);
    IF_Z goto asm_111716;
    LD_A(0xf2);
    CP_A_hl;
    JP_Z (mFunction111796);
    DEC_A;
    CP_A_hl;
    JP_Z (mFunction1117a0);
    DEC_A;
    CP_A_hl;
    JP_Z (mFunction1117a0);
    LD_A_addr(wc807);
    CP_A(0x1);
    IF_NZ goto asm_111716;
    LD_A_addr(wc806);
    OR_A_A;
    IF_Z goto asm_111778;

asm_111716:
    LD_A_addr(wMobileSDK_SendCommandID);
    CP_A(-1);
    IF_Z goto asm_111730;
    CP_A(MOBILE_COMMAND_ERROR | 0x80);
    IF_Z goto asm_111727;
    CP_A(MOBILE_COMMAND_TRANSFER_DATA_END | 0x80);
    IF_NZ goto asm_111727;
    LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);

asm_111727:
    CP_A_hl;
    JR_NZ (masm_11179a);
    LD_A_addr(wMobileSDK_AdapterType);
    OR_A_A;
    IF_Z goto asm_111730;

asm_111730:
    XOR_A_A;
    LD_addr_A(wc819);
    LD_A(0x3);
    LD_addr_A(wc800);
    XOR_A_A;
    LD_HL(wc80a);
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_HL(wc81f);
    LD_A_hli;
    LD_B_A;
    LD_A_hl;
    LD_HL(wc815);
    LD_hli_A;
    LD_A_B;
    LD_hli_A;
    LD_A_addr(wc822);
    BIT_A(0);
    IF_Z goto asm_111757;
    LD_A(0xb);
    goto asm_111774;

asm_111757:
    LD_A_addr(wMobileSDK_SendCommandID);
    CP_A(-1);
    IF_Z goto asm_11176e;
    CP_A(MOBILE_COMMAND_DIAL_TELEPHONE | 0x80);
    IF_Z goto asm_111772;
    CP_A(MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80);
    IF_Z goto asm_111772;
    CP_A(MOBILE_COMMAND_DNS_QUERY | 0x80);
    IF_Z goto asm_111772;
    LD_A(0x20);
    goto asm_111774;

asm_11176e:
    LD_A(0x3);
    goto asm_111774;

asm_111772:
    LD_A(0x60);

asm_111774:
    LD_hl_A;
    JP(mFunction1118bc);

asm_111778:
    XOR_A_A;
    LD_addr_A(wc800);
    return Function11177c();
}

void Function11177c(void){
    LD_HL(wc820);
    LD_A_hld;
    LD_E_A;
    LD_A_hl;
    DEC_A;
    LD_B(0x3);

asm_111785:
    OR_A_A;
    RRA;
    RR_E;
    DEC_B;
    IF_NZ goto asm_111785;
    OR_A_A;
    INC_A;
    LD_HL(wc816);
    LD_hld_A;
    LD_hl_E;
    JP(mFunction1118bc);

}

void Function111796(void){
    LD_B(0xa);
    JR(masm_1117a2);
}

void asm_11179a(void){
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    JP(mFunction1118bc);

}

void Function1117a0(void){
    LD_B(0x3);
    return asm_1117a2();
}

void asm_1117a2(void){
    LD_HL(wc822);
    SET_hl(3);
    LD_HL(wc815);
    LD_A_addr(wc820);
    LD_hli_A;
    LD_A_addr(wc81f);
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wc800);
    LD_HL(wc819);
    INC_hl;
    LD_A_B;
    CP_A_hl;
    JP_NC (mFunction1118bc);
    XOR_A_A;
    LD_HL(wc806);
    LD_hli_A;
    LD_addr_A(wc800);
    LD_A(0x6);
    LD_hl_A;
    LD_HL(wc821);
    SET_hl(1);
    LD_A(0x15);
    LD_addr_A(wc80f);
    LD_HL(wc810);
    LD_A_addr(wc808);
    AND_A(0xf);
    CP_A(0x2);
    IF_NZ goto asm_1117e1;
    INC_A;

asm_1117e1:
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    JP(mFunction1118bc);

}

void Function1117e7(void){
    LD_A_addr(wc80b);
    OR_A_A;
    IF_Z goto asm_1117f8;
    DEC_A;
    JP_Z (mFunction11186e);
    DEC_A;
    JP_Z (mFunction111884);
    JP(mFunction111892);

asm_1117f8:
    LD_HL(wc80a);
    LD_A_hl;
    OR_A_A;
    IF_NZ goto asm_111803;
    LD_B(0x99);
    goto asm_111805;

asm_111803:
    LD_B(0x66);

asm_111805:
    LDH_A_addr(rSB);
    CP_A_B;
    IF_Z goto asm_111840;
    CP_A(0xd2);
    IF_NZ goto asm_111817;
    XOR_A_A;
    LD_addr_A(wc9ae);

asm_111812:
    XOR_A_A;
    LD_hl_A;
    JP(mFunction1118bc);

asm_111817:
    LD_A_addr(wc9ae);
    INC_A;
    LD_addr_A(wc9ae);
    CP_A(0x14);
    IF_C goto asm_111812;
    LD_A(0x6);
    LD_addr_A(wc807);
    LD_A(0x10);
    LD_addr_A(wc80f);
    XOR_A_A;
    LD_addr_A(wc800);
    LD_HL(wc822);
    RES_hl(0);
    LD_HL(wc821);
    LD_A_hl;
    SET_A(1);
    AND_A(0xf);
    LD_hl_A;
    JR(mFunction1118bc);

asm_111840:
    INC_hl;
    LD_A(0x2);
    CP_A_hl;
    JR_NZ (mFunction1118bc);
    XOR_A_A;
    LD_hli_A;
    INC_hl;
    LD_HL(wMobileSDK_PacketChecksum);
    LD_B(0x3);

asm_11184e:
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_11184e;
    LD_A_addr(wc822);
    BIT_A(4);
    IF_Z goto asm_111864;
    LD_B_A;
    LD_A_addr(wc821);
    BIT_A(3);
    IF_NZ goto asm_111864;
    JP(mFunction11177c);

asm_111864:
    LD_A_addr(wc820);
    LD_hli_A;
    LD_A_addr(wc81f);
    LD_hl_A;
    JR(mFunction1118bc);

}

void Function11186e(void){
    CALL(aFunction1118c2);
    LD_A(0x4);
    CP_A_hl;
    JR_NZ (mFunction1118bc);
    XOR_A_A;
    LD_hli_A;
    LDH_A_addr(rSB);
    LD_addr_A(wc80c);
    INC_hl;
    OR_A_A;
    JR_NZ (mFunction1118bc);
    INC_hl;
    JR(mFunction1118bc);

}

void Function111884(void){
    CALL(aFunction1118c2);
    LD_A_addr(wc80c);
    CP_A_hl;
    JR_NZ (mFunction1118bc);
    XOR_A_A;
    LD_hli_A;
    INC_hl;
    JR(mFunction1118bc);

}

void Function111892(void){
    // LDH_A_addr(rSB);
    // LD_C_A;
    uint8_t c = gb_read(rSB);
    // CALL(aFunction111664);
    Function111664(c);
    // LD_HL(wc80a);
    // INC_hl;
    // LD_A(0x2);
    // CP_A_hl;
    // IF_C goto asm_1118b4;
    if(++wram->wc80a < 0x2) {
        // LD_A_addr(wc80a);
        // ADD_A(0x11);
        // LD_E_A;
        uint8_t e = wram->wc802 + 0x11;
        // LD_D(0xc8);
        // LD_A_de;
        // CP_A_C;
        // JR_Z (mFunction1118bc);
        if((&wram->wc800)[e] == c)
            return Function1118bc();
        // LD_A(0x1);
        // LD_addr_A(wc814);
        wram->wc814 = 0x1;
        // JR(mFunction1118bc);
        return Function1118bc();
    }

// asm_1118b4:
    // LD_A(0x4);
    // CP_A_hl;
    // JR_NZ (mFunction1118bc);
    if(wram->wc80a != 0x4)
        return Function1118bc();
    // XOR_A_A;
    // LD_hli_A;
    wram->wc80a = 0x0;
    // INC_hl;
    wram->wc80b++;
    return Function1118bc();
}

void Function1118bc(void){
    // LD_HL(wc822);
    // RES_hl(1);
    bit_reset(wram->wc822, 1);
    // RET;
}

void Function1118c2(void){
    LDH_A_addr(rSB);
    LD_C_A;
    LD_B(0);
    LD_HL(wMobileSDK_PacketChecksum);
    LD_A_hli;
    LD_L_hl;
    LD_H_A;
    ADD_HL_BC;
    LD_A_H;
    LD_addr_A(wMobileSDK_PacketChecksum);
    LD_A_L;
    LD_addr_A(wMobileSDK_PacketChecksum + 1);
    CALL(aFunction111664);
    LD_HL(wc80a);
    INC_hl;
    RET;

}

void v_Timer(void){
    // LD_A_addr(wc80b);
    // CP_A(0x4);
    // CALL_Z (aFunction111b3c);
    if(wram->wc80b == 0x4)
        return Function111b3c();
    // CALL(aFunction11214e);
    Function11214e();
    // LD_HL(wc807);
    // LD_A_hli;
    // CP_A(0x2);
    // IF_C goto asm_111927;
    if(wram->wc807 >= 0x2) {
        // LD_A_hli;
        // LD_B_A;
        // LD_A_hl;
        // LD_C_A;
        uint16_t bc = wram->wc808;
        // AND_A_B;
        // CP_A(0xff);
        // IF_Z goto asm_1118fe;
        // LD_A_C;
        // OR_A_B;
        // IF_NZ goto asm_111927;
        if(bc == 0xffff || bc == 0x0) {
        // asm_1118fe:
            // LD_HL(wc807);
            // LD_A(0x6);
            // CP_A_hl;
            // JP_Z (mFunction111b3b);
            if(wram->wc807 == 0x6)
                return Function111b3b();
            // LD_hl_A;
            wram->wc807 = 0x6;
            // LD_A(0x10);
            // LD_addr_A(wc80f);
            wram->wc80f = 0x10;
            // XOR_A_A;
            // LD_addr_A(wc800);
            wram->wc800 = 0x0;
            // LD_HL(wc822);
            // RES_hl(0);
            bit_reset(wram->wc822, 0);
            // LD_HL(wc821);
            // LD_A_hl;
            // AND_A(0xf);
            // OR_A(0x2);
            // LD_hl_A;
            wram->wc821 = (wram->wc821 & 0xf) | 0x2;
            // LD_A(0x10);
            // LD_addr_A(wc80f);
            wram->wc80f = 0x10;
            // JP(mFunction111b3b);
            return Function111b3b();
        }
    }

// asm_111927:
    // LD_A_addr(wc800);
    // CP_A(0x1);
    // JP_Z (mFunction111b21);
    if(wram->wc800 == 0x1)
        return Function111b21();
    // CP_A(0x3);
    // JP_Z (mFunction111a2a);
    if(wram->wc800 == 0x3)
        return Function111a2a();
    // LD_A_addr(wc807);
    // CP_A(0x1);
    // JP_C (mFunction111b3b);
    // LD_HL(wc815);
    // DEC_hl;
    // JP_NZ (mFunction111b3b);
    if(wram->wc807 < 0x1 || --wram->wc815 == 0)
        return Function111b3b();
    // INC_HL;
    // DEC_hl;
    wram->wc816 = (wram->wc816 & 0xff00) | ((wram->wc816 - 1) & 0x00ff);
    // JP_NZ (mFunction111b3b);
    if((wram->wc816 & 0xff) != 0)
        return Function111b3b();
    // LD_HL(wc807);
    // LD_A_addr(wc822);
    uint8_t a = wram->wc822;
    // BIT_A(3);
    // JP_NZ (mFunction111a0b);
    if(bit_test(a, 3))
        return Function111a0b(wram->wc807);
    // BIT_A(4);
    // IF_NZ goto asm_11199c;
    if(!bit_test(a, 4)) {
        // LD_A_hl;
        a = wram->wc807;
        // CP_A(0x1);
        // JP_Z (mFunction1119f0);
        if(a == 0x1)
            return Function1119f0();
        // CP_A(0xa);
        // IF_Z goto asm_111984;
        if(a == 0xa) {
        // asm_111984:
            // XOR_A_A;
            // LD_hl_A;
            wram->wc807 = 0x0;
            // LD_HL(wc821);
            // RES_hl(0);
            bit_reset(wram->wc821, 0);
            // CALL(aFunction111686);
            Function111686();
            // JP(mFunction111b3b);
            return Function111b3b();
        }
        // CP_A(0x8);
        // IF_Z goto asm_11197d;
        if(a == 0x8) {
        // asm_11197d:
            // LD_A_addr(wc805);
            // LD_hl_A;
            wram->wc807 = wram->wc805;
            // JP(mFunction111b3b);
            return Function111b3b();
        }
        // LD_A_addr(wc86a);
        a = wram->wc86a;
        // CP_A(0x2a);
        // IF_Z goto asm_111991;
        if(a == 0x2a) {
        // asm_111991:
            // XOR_A_A;
            // LD_hl_A;
            wram->wc807 = 0x0;
            // LD_addr_A(wc821);
            wram->wc821 = 0x0;
            // CALL(aFunction111686);
            Function111686();
            // JP(mFunction111b3b);
            return Function111b3b();
        }
        // CP_A(0xd);
        // IF_NZ goto asm_111977;
        // LD_A_addr(wc86b);
        // CP_A(0x4);
        // IF_NC goto asm_11199c;
        if(a != 0xd || wram->wc86b < 0x4) {
        asm_111977:
            // CALL(aFunction111f97);
            Function111f97();
            // JP(mFunction111b3b);
            return Function111b3b();
        }
    }

// asm_11199c:
    // LD_B_A;
    // LD_hl_A;
    wram->wc807 = a;
    // OR_A_A;
    // JP_Z (mFunction111b3b);
    if(a == 0)
        return Function111b3b();
    // LD_A_addr(wc822);
    // BIT_A(7);
    // IF_NZ goto asm_1119be;
    if(!bit_test(wram->wc822, 7)) {
    asm_1119a9:
        // LD_A_addr(wc821);
        // BIT_A(3);
        // IF_NZ goto asm_111977;
        if(bit_test(wram->wc821, 3))
            goto asm_111977;
        // LD_DE(lengthof(MobilePacket_TransferData));
        // LD_HL(mMobilePacket_TransferData);
        // LD_A(0x95);
        // CALL(aFunction111f02);
        Function111f02(MobilePacket_TransferData, lengthof(MobilePacket_TransferData), 0x95);
        // JP(mFunction111b3b);
        return Function111b3b();
    }

// asm_1119be:
    // LD_A_addr(wc821);
    // BIT_A(3);
    // IF_NZ goto asm_1119dd;
    if(!bit_test(wram->wc821, 3)) {
        // LD_A_addr(wMobileSDK_PacketBuffer + 5);
        // ADD_A(0xa);
        // LD_E_A;
        // LD_D(0);
        // LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
        // LD_addr_A(wMobileSDK_SendCommandID);
        wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_TRANSFER_DATA | 0x80;
        // LD_HL(wMobileSDK_PacketBuffer);
        // LD_B(0x5);
        // CALL(aPacketSendBytes);
        PacketSendBytes(wram->wMobileSDK_PacketBuffer, wram->wMobileSDK_PacketBuffer[5] + 0xa, 0x5);
        // JP(mFunction111b3b);
        return Function111b3b();
    }

// asm_1119dd:
    // LD_HL(wc821);
    // SET_hl(1);
    bit_set(wram->wc821, 1);
    // RES_hl(0);
    bit_reset(wram->wc821, 0);
    // LD_HL(wc822);
    // RES_hl(7);
    bit_reset(wram->wc822, 7);
    // LD_A(0x21);
    // LD_addr_A(wc80f);
    wram->wc80f = 0x21;
    goto asm_1119a9;
}

// MobileSDK_BeginSession
void Function1119f0(void){
    // LD_A(MOBILE_COMMAND_BEGIN_SESSION | 0x80);
    // LD_addr_A(wMobileSDK_SendCommandID);
    // LD_addr_A(wc808);
    wram->wc808 = wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_BEGIN_SESSION | 0x80;
    // LD_B(0x5);
    // LD_DE(lengthof(MobilePacket_BeginSession));
    // LD_HL(mMobilePacket_BeginSession);
    // CALL(aPacketSendBytes);
    PacketSendBytes(MobilePacket_BeginSession, sizeof(MobilePacket_BeginSession), 0x5);
    // LD_A(0x1);
    // LD_addr_A(wc806);
    wram->wc806 = 0x1;
    // JP(mFunction111b3b);
    return Function111b3b();
}

void Function111a0b(uint8_t a){
    // LD_A_hl;
    // CP_A(0x6);
    // JP_Z (mFunction111b3b);
    if(a == 0x6)
        return Function111b3b();
    // LD_HL(wc822);
    // RES_hl(3);
    // RES_hl(0);
    wram->wc822 &= ~((1 << 3) | (1 << 0));
    // LD_HL(wc81a);
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_B(0x5);
    // CALL(aPacketSendBytes);
    PacketSendBytes(gMobileSendPacketPointer, gMobileSendPacketSize, 0x5);
    // JP(mFunction111b3b);
    return Function111b3b();
}

void Function111a2a(void){
    // LD_HL(wc80b);
    // LD_A_hld;
    // OR_A_A;
    // JR_Z (masm_111a47);
    if(wram->wc80b == 0)
        return asm_111a47();
    // CP_A(0x3);
    // JR_NZ (masm_111a40);
    if(wram->wc80b != 0x3)
        return asm_111a40();
    // LD_A_hl;
    // CP_A(0x2);
    // JP_Z (mFunction111ab9);
    if(wram->wc80a == 0x2)
        return Function111ab9();
    // CP_A(0x3);
    // JP_Z (mFunction111abd);
    if(wram->wc80a == 0x3)
        return Function111abd();
    return asm_111a40();
}

// Mobile_WriteSerialByte0x4bAndSend
void asm_111a40(void){
    // LD_A(0x4b);
    return Function111a42(0x4b);
}

// Mobile_WriteSerialByteAndSend
void Function111a42(uint8_t a){
    // LDH_addr_A(rSB);
    gb_write(rSB, a);
    // JP(mFunction111b2e);
    return Function111b2e();
}

void asm_111a47(void){
    // LD_HL(wc815);
    // DEC_hl;
    // JR_NZ (masm_111a40);
    // INC_HL;
    // DEC_hl;
    // JR_NZ (masm_111a40);
    if(--wram->wc815 != 0x0 || ((--wram->wc816) & 0xff) != 0x0)
        return asm_111a40();
    // INC_HL;
    // DEC_hl;
    // IF_Z goto asm_111a63;
    if(wram->wc816 != 0) {
        // LD_HL(wc81f);
        // LD_A_hli;
        // LD_D_A;
        uint8_t d = wram->wc81f;
        // LD_A_hl;
        // LD_HL(wc815);
        // LD_hli_A;
        wram->wc815 = wram->wc820;
        // LD_A_D;
        // LD_hli_A;
        wram->wc816 = (wram->wc816 & 0xff00) | d;
        // JR(masm_111a40);
        return asm_111a40();
    }

// asm_111a63:
    // NOP;
    // LD_A_addr(wc86a);
    // CP_A(0x2a);
    // IF_Z goto asm_111aa8;
    if(wram->wc86a != 0x2a) {
        // LD_HL(wc9b2);
        // INC_hl;
        // LD_A_hl;
        // CP_A(0x1);
        // IF_Z goto asm_111a91;
        if(++wram->wc9b2 == 0x1) {
            // LD_HL(wc822);
            // RES_hl(5);
            // RES_hl(0);
            wram->wc822 &= ~((1 << 5) | (1 << 0));
            // LD_HL(wc821);
            // RES_hl(4);
            bit_reset(wram->wc821, 4);
            // LD_A(0x0);
            // LD_addr_A(wc805);
            wram->wc805 = 0x0;
            // LD_A(0x29);
            // LD_addr_A(wc86a);
            wram->wc86a = 0x29;
            // LD_A(0x1);
            // LD_addr_A(wc806);
            wram->wc806 = 0x1;
            // goto asm_111aa8;
        }
        else {
        // asm_111a91:
            // LD_A(0x29);
            // LD_addr_A(wc86a);
            wram->wc86a = 0x29;
            // XOR_A_A;
            // LD_addr_A(wc806);
            wram->wc806 = 0x0;
            // LD_addr_A(wc86b);
            wram->wc86b = 0x0;
            // LD_addr_A(wc80b);
            wram->wc80b = 0x0;
            // LD_addr_A(wc800);
            wram->wc800 = 0x0;
            // LD_A(0x8);
            // LD_addr_A(wc807);
            wram->wc807 = 0x8;
        }
    }

// asm_111aa8:
    // CALL(aResetReceivePacketBuffer);
    ResetReceivePacketBuffer();
    // CALL(aFunction11164f);
    Function11164f();
    // LD_HL(wc822);
    // RES_hl(5);
    // RES_hl(0);
    wram->wc822 &= ~((1 << 0) | (1 << 5));
    // NOP;
    // JP(mFunction111b3b);
    return Function111b3b();
}

// Mobile_WriteSerialByte0x80AndSend
void Function111ab9(void){
    // LD_A(0x80);
    // JR(mFunction111a42);
    return Function111a42(0x80);
}

void Function111abd(void){
    // LD_A_addr(wc814);
    // OR_A_A;
    // IF_NZ goto asm_111acb;
    if(wram->wc814 == 0x0) {
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
        // XOR_A(0x80);
        // JP(mFunction111a42);
        return Function111a42(wram->wMobileSDK_ReceivePacketBuffer[0] ^ 0x80);
    }

// asm_111acb:
    // LD_HL(wc819);
    // INC_hl;
    // LD_A(0x3);
    // CP_A_hl;
    // IF_Z goto asm_111afe;
    if(++wram->wc819 == 0x3) {
    // asm_111afe:
        // LD_HL(wc806);
        // XOR_A_A;
        // LD_hli_A;
        wram->wc806 = 0x0;
        // LD_addr_A(wc800);
        wram->wc800 = 0x0;
        // LD_A(0x6);
        // LD_hl_A;
        wram->wc807 = 0x6;
        // LD_HL(wc821);
        // SET_hl(1);
        bit_set(wram->wc821, 1);
        // LD_A(0x15);
        // LD_addr_A(wc80f);
        wram->wc80f = 0x15;
        // LD_A(0x2);
        // LD_addr_A(wc810);
        wram->wc810 = 0x2;
        // XOR_A_A;
        // LD_addr_A(wc811);
        wram->wc811 = 0x0;
    }
    else {
        // CALL(aResetReceivePacketBuffer);
        ResetReceivePacketBuffer();
        // LD_A(0x3);
        // LD_addr_A(wc800);
        wram->wc800 = 0x3;
        // XOR_A_A;
        // LD_HL(wc80a);
        // LD_hli_A;
        wram->wc80a = 0x0;
        // LD_hli_A;
        wram->wc80b = 0x0;
        // LD_hl_A;
        wram->wc80c = 0x0;
        // LD_HL(wc815);
        // LD_A_addr(wc820);
        // LD_hli_A;
        wram->wc815 = wram->wc820;
        // LD_A_addr(wc81f);
        // LD_hli_A;
        // LD_A_addr(wc822);
        // BIT_A(0);
        // IF_Z goto asm_111af9;
        // LD_A(0xb);
        // goto asm_111afb;

    // asm_111af9:
        // LD_A(0x20);

    // asm_111afb:
        // LD_hli_A;
        wram->wc816 = (wram->wc81f) | (((!bit_test(wram->wc822, 0))? 0x20: 0xb) << 8);
        // goto asm_111b1c;
    }

// asm_111b1c:
    // LD_A(0xf1);
    // JP(mFunction111a42);
    return Function111a42(0xf1);
}

// Mobile_WritePacketByte
void Function111b21(void){
    // LD_HL(wc803);
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    // LD_A_de;
    // LDH_addr_A(rSB);
    gb_write(rSB, *gMobilePacketPointer);
    // INC_DE;
    // LD_A_D;
    // LD_hld_A;
    // LD_hl_E;
    gMobilePacketPointer++;

    return Function111b2e();
}

// Mobile_SendWrittenPacketByte
void Function111b2e(void){
    // LD_HL(wc822);
    // SET_hl(1);
    bit_set(wram->wc822, 1);
    // LD_A((0 << rSC_ON) | (1 << rSC_CGB) | (1 << rSC_CLOCK));
    // LDH_addr_A(rSC);
    gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CGB) | (1 << rSC_CLOCK));
    // LD_A((1 << rSC_ON) | (1 << rSC_CGB) | (1 << rSC_CLOCK));
    // LDH_addr_A(rSC);
    gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CGB) | (1 << rSC_CLOCK));

    return Function111b3b();
}

// Stubbed function?
void Function111b3b(void){
    // RET;
}

void Function111b3c(void){
    // XOR_A_A;
    // LD_addr_A(wc819);
    wram->wc819 = 0x0;
    // LD_addr_A(wc80b);
    wram->wc80b = 0x0;
    // LD_HL(wc9b1);
    // LD_hli_A;
    wram->wc9b1 = 0x0;
    // LD_hl_A;
    wram->wc9b2 = 0x0;
    // LD_addr_A(wc800);
    wram->wc800 = 0x0;
    // LD_HL(wc822);
    // RES_hl(5);
    bit_reset(wram->wc822, 5);
    // BIT_hl(0);
    // IF_Z goto asm_111b59;
    // LD_A_addr(wMobileSDK_ReceivePacketBufferAlt);
    // goto asm_111b5c;

// asm_111b59:
    // LD_A_addr(wMobileSDK_ReceivePacketBuffer);

// asm_111b5c:
    uint8_t b = (bit_test(wram->wc822, 0))? wram->wMobileSDK_ReceivePacketBufferAlt[0]: wram->wMobileSDK_ReceivePacketBuffer[0];
    // CP_A(MOBILE_COMMAND_TRANSFER_DATA_END | 0x80);
    // IF_NZ goto asm_111b62;
    if(b == (MOBILE_COMMAND_TRANSFER_DATA_END | 0x80)) {
        // LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
        b = (MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    }

// asm_111b62:
    // LD_B_A;
    // LD_HL(mFunction111e28);
    // PUSH_HL;
    // CP_A(MOBILE_COMMAND_ERROR | 0x80);
    // JP_Z (mGetErrorCode);
    if(b == (MOBILE_COMMAND_ERROR | 0x80)) {
        GetErrorCode();
    }
    else {
        switch(wram->wMobileSDK_SendCommandID) {
            // LD_A_addr(wMobileSDK_SendCommandID);
            // CP_A(-1);
            // JP_Z (mFunction111ef8);
            case 0xff:
                Function111ef8();
                break;
            // CP_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
            // JP_Z (mFunction111c17);
            case MOBILE_COMMAND_TRANSFER_DATA | 0x80:
                Function111c17();
                break;
            // CP_A(MOBILE_COMMAND_DNS_QUERY | 0x80);
            // JP_Z (mFunction111d23);
            case MOBILE_COMMAND_DNS_QUERY | 0x80:
                Function111d23();
                break;
            // CP_A(MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80);
            // IF_Z goto asm_111bbe;
            // CP_A(MOBILE_COMMAND_CLOSE_TCP_CONNECTION | 0x80);
            // IF_Z goto asm_111bbe;
            case MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80:
            case MOBILE_COMMAND_CLOSE_TCP_CONNECTION | 0x80:
            // asm_111bbe:
                // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 4);
                // LD_addr_A(wc86c);
                wram->wc86c = wram->wMobileSDK_ReceivePacketBuffer[4];
                // LD_A(0x4);
                // LD_addr_A(wc807);
                wram->wc807 = 0x4;
                // RET;
                break;
            // CP_A(MOBILE_COMMAND_HANG_UP_TELEPHONE | 0x80);
            // IF_Z goto asm_111be0;
            case MOBILE_COMMAND_HANG_UP_TELEPHONE | 0x80:
            // asm_111be0:
                // LD_A(0x2);
                // LD_addr_A(wc807);
                wram->wc807 = 0x2;
                // LD_HL(wc822);
                // RES_hl(4);
                bit_reset(wram->wc822, 4);
                // LD_HL(wc821);
                // RES_hl(4);
                bit_reset(wram->wc821, 4);
                // RET;
                break;
            // CP_A(MOBILE_COMMAND_READ_CONFIGURATION_DATA | 0x80);
            // IF_Z goto asm_111bf0;
            case MOBILE_COMMAND_READ_CONFIGURATION_DATA | 0x80:
            // asm_111bf0:
                // LD_HL(wc829);
                // LD_A_hli;
                // LD_D_hl;
                // LD_E_A;
                // LD_HL(wMobileSDK_ReceivePacketBuffer + 3);  // packet size
                // LD_A_hli;
                // DEC_A;
                // LD_B_A;
                // INC_HL;
                // CALL(aMobileSDK_CopyBytes);
                MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wMobileSDK_ReceivePacketBuffer + 4, wram->wMobileSDK_ReceivePacketBuffer[3] - 1);
                // LD_A(0x2);
                // LD_addr_A(wc807);
                wram->wc807 = 0x2;
                // RET;
                break;
            // CP_A(MOBILE_COMMAND_WRITE_CONFIGURATION_DATA | 0x80);
            // JP_Z (mFunction111c06);
            case MOBILE_COMMAND_WRITE_CONFIGURATION_DATA | 0x80:
                Function111c06();
                break;
            // CP_A(MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
            // JP_Z (mFunction111d70);
            case MOBILE_COMMAND_TELEPHONE_STATUS | 0x80:
                // Function111d70();
                break;
            // CP_A(MOBILE_COMMAND_ISP_LOGIN | 0x80);
            // IF_Z goto asm_111bd0;
            case MOBILE_COMMAND_ISP_LOGIN | 0x80:
            // asm_111bd0:
                // LD_A(0x4);
                // LD_addr_A(wc807);
                // LD_DE(wc823);
                // LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
                // LD_B(0x4);
                // JP(mMobileSDK_CopyBytes);
                MobileSDK_CopyBytes(wram->wc823, wram->wMobileSDK_ReceivePacketBuffer + 4, 0x4);
                break;
            // CP_A(MOBILE_COMMAND_ISP_LOGOUT | 0x80);
            // IF_Z goto asm_111bca;
            case MOBILE_COMMAND_ISP_LOGOUT | 0x80:
            // asm_111bca:
                // LD_A(0x3);
                // LD_addr_A(wc807);
                wram->wc807 = 0x3;
                // RET;
                break;
            // CP_A(MOBILE_COMMAND_BEGIN_SESSION | 0x80);
            // JP_Z (mParseResponse_BeginSession);
            case MOBILE_COMMAND_BEGIN_SESSION | 0x80:
                ParseResponse_BeginSession();
                break;
            // CP_A(MOBILE_COMMAND_WAIT_FOR_TELEPHONE_CALL | 0x80);
            // JP_Z (mFunction111d65);
            // CP_A(MOBILE_COMMAND_DIAL_TELEPHONE | 0x80);
            // JP_Z (mFunction111d65);
            case MOBILE_COMMAND_WAIT_FOR_TELEPHONE_CALL | 0x80:
            case MOBILE_COMMAND_DIAL_TELEPHONE | 0x80:
                Function111d65();
                break;
            default:
                // LD_HL(wc822);
                // RES_hl(0);
                bit_reset(wram->wc822, 0);
                // LD_A(0xa);
                // LD_addr_A(wc807);
                wram->wc807 = 0xa;
                // XOR_A_A;
                // LD_addr_A(wc800);
                wram->wc800 = 0x0;
                // RET;
                break;
        }
    }
    Function111e28();

}

void Function111c06(void){
    // LD_DE(wc872);
    // LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
    // LD_B(0x2);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(&wram->wc872, wram->wMobileSDK_ReceivePacketBuffer + 4, 0x2);
    // LD_A(0x2);
    // LD_addr_A(wc807);
    wram->wc807 = 0x2;
    // RET;
}

void Function111c17(void){
    // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    // CP_A(MOBILE_COMMAND_TRANSFER_DATA_END | 0x80);
    // JP_Z (mFunction111d07);
    if(wram->wMobileSDK_ReceivePacketBuffer[0] == (MOBILE_COMMAND_TRANSFER_DATA_END | 0x80))
        return Function111d07();
    // LD_A_addr(wc86f);
    // LD_B_A;
    // LD_A_addr(wc86e);
    // OR_A_B;
    // JP_Z (mFunction111d07);
    if((wram->wc86f | wram->wc86e) == 0)
        return Function111d07();
    // LD_HL(wc82b);
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    // DEC_A;
    // JP_Z (mFunction111d07);
    if(wram->wMobileSDK_ReceivePacketBuffer[3] - 1 == 0)
        return Function111d07();
    // LD_C_A;
    // LD_A_addr(wc822);
    // BIT_A(4);
    // JP_Z (mFunction111cc2);
    if(!bit_test(wram->wc822, 4))
        return Function111cc2();
    LD_A_addr(wc992);
    OR_A_A;
    IF_NZ goto asm_111c89;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 5);
    OR_A_A;
    IF_Z goto asm_111c50;
    CP_A(0x81);
    IF_C goto asm_111c52;

asm_111c50:
    LD_A(0x80);

asm_111c52:
    LD_B_A;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    DEC_A;
    DEC_A;
    CP_A_B;
    IF_C goto asm_111c6e;

asm_111c5b:
    LD_HL(wc821);
    SET_hl(3);
    LD_HL(wc993);
    LD_A(0x1);
    LD_hli_A;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    DEC_A;
    LD_hl_A;
    JP(mFunction111d07);

asm_111c6e:
    LD_HL(wc992);
    OR_A_A;
    IF_Z goto asm_111c83;
    LD_hld_A;
    LD_hl_B;
    LD_B_A;
    LD_HL(wMobileSDK_ReceivePacketBuffer + 6);
    LD_DE(wc880);
    CALL(aMobileSDK_CopyBytes);
    JP(mFunction111d07);

asm_111c83:
    LD_A(0xff);
    LD_hld_A;
    LD_hl_B;
    JR(mFunction111d07);

asm_111c89:
    CP_A(0xff);
    IF_NZ goto asm_111c9d;
    LD_HL(wc991);
    LD_A_hli;
    LD_B_A;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    DEC_A;
    CP_A_B;
    IF_NC goto asm_111c5b;
    IF_Z goto asm_111c5b;
    XOR_A_A;
    LD_hl_A;

asm_111c9d:
    LD_HL(wc991);
    LD_A_hli;
    SUB_A_hl;
    LD_B_A;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    DEC_A;
    CP_A_B;
    IF_NC goto asm_111c5b;
    IF_Z goto asm_111c5b;
    LD_B_A;
    LD_L_hl;
    LD_H(0x0);
    ADD_A_L;
    LD_addr_A(wc992);
    LD_DE(wc880);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(wMobileSDK_ReceivePacketBuffer + 5);
    CALL(aMobileSDK_CopyBytes);
    JR(mFunction111d07);

}

void Function111cc2(void){
    XOR_A_A;
    CP_A_D;
    IF_NZ goto asm_111cda;
    LD_A_C;
    CP_A_E;
    IF_C goto asm_111cda;
    IF_Z goto asm_111cda;
    LD_A_addr(wc821);
    SET_A(2);
    LD_addr_A(wc821);
    LD_A_C;
    SUB_A_E;
    LD_C_E;
    LD_E_A;
    goto asm_111ce1;

asm_111cda:
    LD_A_E;
    SUB_A_C;
    LD_E_A;
    LD_A_D;
    SBC_A(0x0);
    LD_D_A;

asm_111ce1:
    LD_A_D;
    LD_hld_A;
    LD_hl_E;
    LD_A_addr(wc829);
    LD_E_A;
    LD_A_addr(wc82a);
    LD_D_A;
    LD_HL(wMobileSDK_ReceivePacketBuffer + 5);
    LD_A_C;
    OR_A_A;
    JR_Z (mFunction111d07);
    LD_B_A;
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc829);
    LD_A_E;
    LD_hli_A;
    LD_hl_D;
    LD_DE(0x3);
    ADD_HL_DE;
    LD_A_hl;
    ADD_A_C;
    LD_hli_A;
    JR_NC (mFunction111d07);
    INC_hl;

    return Function111d07();
}

void Function111d07(void){
    // LD_A_addr(wc822);
    // BIT_A(4);
    // IF_Z goto asm_111d1c;
    // BIT_A(7);
    // IF_Z goto asm_111d1c;
    if(bit_test(wram->wc822, 4) && bit_test(wram->wc822, 7)) {
        // LD_HL(wc822);
        // RES_hl(7);
        bit_reset(wram->wc822, 7);
        // LD_HL(wc821);
        // RES_hl(0);
        bit_reset(wram->wc821, 0);
    }

// asm_111d1c:
    // LD_A_addr(wc805);
    // LD_addr_A(wc807);
    wram->wc807 = wram->wc805;
    // RET;
}

// Mobile_CopyReceivedPacketHeader
void Function111d23(void){
    // LD_A_addr(wc829);
    // LD_E_A;
    // LD_A_addr(wc82a);
    // LD_D_A;
    // LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
    // LD_B(0x4);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wMobileSDK_ReceivePacketBuffer + 4, 0x4);
    // LD_A(0x4);
    // LD_addr_A(wc807);
    wram->wc807 = 0x4;
    // RET;
}

void ParseResponse_BeginSession(void){
    // LD_DE(wMobileSDK_ReceivePacketBuffer + 3);
    uint8_t* de = wram->wMobileSDK_ReceivePacketBuffer + 3;
    // LD_HL(mMobilePacket_BeginSession + 5);
    const uint8_t* hl = MobilePacket_BeginSession + 5;
    // LD_B(1 + sizeof("NINTENDO") - 1);
    uint8_t b = 1 + sizeof("NINTENDO") - 1;

    do {
    // check_loop:
        // LD_A_de;
        // INC_DE;
        uint8_t a = *(de++);
        // CP_A_hl;
        // IF_NZ goto check_done;
        if(a != *hl)
            break;
        // INC_HL;
        // DEC_B;
        // IF_NZ goto check_loop;
    } while(hl++, --b != 0);

// check_done:
    // LD_A_B;
    // OR_A_A;
    // IF_NZ goto done;
    if(b == 0) {
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 14);  // device type
        // CP_A(0x80);
        // IF_C goto fail;
        // CP_A(0x90);
        // IF_NC goto fail;
        if(wram->wMobileSDK_ReceivePacketBuffer[14] < 0x80 || wram->wMobileSDK_ReceivePacketBuffer[14] >= 0x90)
            wram->wMobileSDK_AdapterType = 0x0;
        else
            wram->wMobileSDK_AdapterType = wram->wMobileSDK_ReceivePacketBuffer[14];
    }
    else {
        wram->wMobileSDK_AdapterType = b;
    }

// done:
    // LD_addr_A(wMobileSDK_AdapterType);
    // LD_A(0x2);
    // LD_addr_A(wc807);
    wram->wc807 = 0x2;
    // RET;

// fail:
    // XOR_A_A;
    // goto done;
}

void Function111d65(void){
    // LD_A(0x3);
    // LD_addr_A(wc807);
    wram->wc807 = 0x3;
    // LD_HL(wc821);
    // SET_hl(4);
    bit_set(wram->wc821, 4);
    // RET;
}

void Function111d70(void){
    LD_HL(wc822);
    BIT_hl(0);
    IF_Z goto asm_111dc0;
    LD_A_addr(wc805);
    LD_addr_A(wc807);
    LD_A_addr(wMobileSDK_ReceivePacketBufferAlt + 4);
    LD_B_A;
    CALL(aFunction111dd9);
    CALL(aFunction111e15);
    RES_hl(0);
    LD_A_B;
    CP_A(0x7);
    IF_Z goto asm_111da9;
    OR_A_A;
    RET_NZ ;
    LD_HL(wc821);
    RES_hl(4);
    SET_hl(1);
    LD_A_addr(wc822);
    BIT_A(4);
    IF_NZ goto asm_111dbb;
    LD_A(0x23);
    LD_addr_A(wc80f);
    LD_A(0x6);
    LD_addr_A(wc807);
    RET;

asm_111da9:
    LD_HL(wc821);
    RES_hl(4);
    SET_hl(1);
    LD_A(0x11);
    LD_addr_A(wc80f);
    LD_A(0x6);
    LD_addr_A(wc807);
    RET;

asm_111dbb:
    XOR_A_A;
    LD_addr_A(wc807);
    RET;

asm_111dc0:
    LD_HL(wc86e);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 4);
    LD_B_A;
    CALL(aFunction111dd9);
    CALL(aFunction111e15);
    LD_A_B;
    LD_hl_A;
    LD_A_addr(wc805);
    LD_addr_A(wc807);
    RET;

}

void Function111dd9(void){
    CP_A(0xff);
    IF_Z goto asm_111de7;
    OR_A_A;
    RET_Z ;
    CP_A(0x4);
    IF_Z goto asm_111dea;
    CP_A(0x5);
    IF_Z goto asm_111e12;

asm_111de7:
    LD_B(0x7);
    RET;

asm_111dea:
    LD_B(0x5);
    LD_A_addr(wc822);
    BIT_A(0);
    IF_Z goto asm_111df8;
    LD_A_addr(wc86a);
    goto asm_111dfb;

asm_111df8:
    LD_A_addr(wc985);

asm_111dfb:
    CP_A(0x4);
    RET_Z ;
    CP_A(0x1c);
    RET_Z ;
    CP_A(0x1a);
    RET_Z ;
    DEC_B;
    CP_A(0x3);
    RET_Z ;
    LD_B(0x1);
    LD_A_addr(wc822);
    BIT_A(4);
    RET_Z ;
    INC_B;
    RET;

asm_111e12:
    LD_B(0x3);
    RET;

}

void Function111e15(void){
    LD_A_B;
    AND_A(0x7);
    RRCA;
    RRCA;
    RRCA;
    PUSH_HL;
    LD_L_A;
    LD_A_addr(wc821);
    AND_A(0x1f);
    OR_A_L;
    LD_addr_A(wc821);
    POP_HL;
    RET;

}

void Function111e28(void){
    // JP(mResetReceivePacketBuffer);
    return ResetReceivePacketBuffer();
}

//  Converts an error packet into a BCD error code
void GetErrorCode(void){
    // LD_A_addr(wMobileSDK_SendCommandID);
    // CP_A(-1);
    // JP_Z (mFunction111ef8);
    if(wram->wMobileSDK_SendCommandID == 0xff)
        return Function111ef8();
    // LD_A_addr(wc86a);
    // CP_A(0xd);
    // IF_Z goto asm_111e48;
    // CP_A(0x2a);
    // IF_Z goto asm_111e48;
    if(wram->wc86a != 0xd && wram->wc86a != 0x2a) {
        // LD_A(0x6);
        // LD_addr_A(wc807);
        wram->wc807 = 0x6;
        // LD_HL(wc821);
        // SET_hl(1);
        bit_set(wram->wc821, 1);
    }

// asm_111e48:
    // LD_A_addr(wc822);
    // BIT_A(0);
    // IF_Z goto asm_111e54;
    // LD_HL(wMobileSDK_ReceivePacketBufferAlt + 4);
    // goto asm_111e57;

// asm_111e54:
    // LD_HL(wMobileSDK_ReceivePacketBuffer + 4);

// asm_111e57:
    uint8_t* hl = (bit_test(wram->wc822, 0))? wram->wMobileSDK_ReceivePacketBufferAlt + 4: wram->wMobileSDK_ReceivePacketBuffer + 4;
    // LD_A_hli;
    uint8_t cmd = *(hl++);
    // LD_addr_A(wc80e);
    wram->wc80e = cmd;
    switch(cmd) {
    // CP_A(MOBILE_COMMAND_BEGIN_SESSION);
    // IF_Z goto adapter_not_plugged_in;
    case MOBILE_COMMAND_BEGIN_SESSION:
    // adapter_not_plugged_in:
        // LD_A(0x10);
        // goto store_error_code;
        wram->wc80f = 0x10;
        return;
    // CP_A(MOBILE_COMMAND_DIAL_TELEPHONE);
    // IF_Z goto dial_telephone;
    case MOBILE_COMMAND_DIAL_TELEPHONE:
    case MOBILE_COMMAND_ISP_LOGOUT:
    // dial_telephone:
        // LD_A_hl;
        // OR_A(0x0);
        // IF_Z goto asm_111e9d;
        if(*hl == 0x0) {
        // asm_111e9d:
            // LD_A(0x12);
            // goto store_error_code;
            wram->wc80f = 0x12;
        }
        // CP_A(0x2);
        // IF_Z goto asm_111e99;
        else if(*hl == 0x2) {
        // asm_111e99:
            // LD_A(0x17);
            // goto store_error_code;
            wram->wc80f = 0x17;
        }
        else {
            // LD_A(0x13);
            // goto store_error_code;
            wram->wc80f = 0x13;
        }
        return;
    // CP_A(MOBILE_COMMAND_HANG_UP_TELEPHONE);
    // IF_Z goto hang_up_logout;
    case MOBILE_COMMAND_HANG_UP_TELEPHONE:
    // hang_up_logout:
        // LD_HL(wc821);
        // RES_hl(1);
        bit_reset(wram->wc821, 1);
        // RES_hl(4);
        bit_reset(wram->wc821, 4);
        // LD_A(0x2);
        // LD_addr_A(wc807);
        wram->wc807 = 0x2;
        // RET;
        return;
    // CP_A(MOBILE_COMMAND_TRANSFER_DATA);
    // IF_Z goto transfer_data;
    case MOBILE_COMMAND_TRANSFER_DATA: {
    // transfer_data:
        // LD_A_hl;
        uint8_t a = *hl;
        // CP_A(0x1);
        // IF_NZ goto asm_111ed3;
        // LD_A_addr(wc822);
        // BIT_A(4);
        // IF_Z goto asm_111ed3;
        if(a == 0x1 && bit_test(wram->wc822, 4)) {
            // RES_A(4);
            // LD_addr_A(wc822);
            bit_reset(wram->wc822, 4);
            // LD_HL(wc821);
            // LD_A_hl;
            // AND_A(0xf);
            // OR_A(0x2);
            // LD_hl_A;
            wram->wc821 = (wram->wc821 & 0xf) | 0x2;
            // LD_A(0x23);
            // LD_addr_A(wc80f);
            wram->wc80f = 0x23;
            // LD_A(0x6);
            // LD_addr_A(wc807);
            wram->wc807 = 0x6;
            // RET;
            return;
        }

    // asm_111ed3:
        // LD_HL(wc822);
        // RES_hl(5);
        bit_reset(wram->wc822, 5);
        // LD_A(0x24);
        // goto store_error_code;
        wram->wc80f = 0x24;
    } return;
    // CP_A(MOBILE_COMMAND_READ_CONFIGURATION_DATA);
    // IF_Z goto read_configuration_data;
    case MOBILE_COMMAND_READ_CONFIGURATION_DATA:
    // read_configuration_data:
        // LD_A(0x14);
        // goto store_error_code;
        wram->wc80f = 0x14;
        return;
    // CP_A(MOBILE_COMMAND_ISP_LOGIN);
    // IF_Z goto isp_login;
    case MOBILE_COMMAND_ISP_LOGIN:
    // isp_login:
        // LD_A(0x22);
        // goto store_error_code;
        wram->wc80f = 0x22;
        return;
    // CP_A(MOBILE_COMMAND_ISP_LOGOUT);
    // IF_Z goto hang_up_logout;
    // CP_A(MOBILE_COMMAND_CLOSE_TCP_CONNECTION);
    // IF_Z goto close_tcp_connection;
    case MOBILE_COMMAND_CLOSE_TCP_CONNECTION:
    // close_tcp_connection:
        // LD_HL(wc821);
        // RES_hl(1);
        bit_reset(wram->wc821, 1);
        // LD_A(0x3);
        // LD_addr_A(wc807);
        wram->wc807 = 0x3;
        // RET;
        return;
    // CP_A(MOBILE_COMMAND_OPEN_TCP_CONNECTION);
    // IF_Z goto open_tcp_connection;
    case MOBILE_COMMAND_OPEN_TCP_CONNECTION:
    // open_tcp_connection:
        // LD_HL(wc821);
        // RES_hl(1);
        bit_reset(wram->wc821, 1);
        fallthrough;
    // CP_A(MOBILE_COMMAND_DNS_QUERY);
    // IF_Z goto dns_query;
    case MOBILE_COMMAND_DNS_QUERY:
    // dns_query:
        // LD_A(0x24);
        // goto store_error_code;
        wram->wc80f = 0x24;
        return;
    default:
        // LD_A_hl;
        wram->wc80f = *hl;
        return;
    }

// store_error_code:
    // LD_addr_A(wc80f);
    // RET;
}

void Function111ef8(void){
    // LD_A_addr(wc805);
    // LD_addr_A(wc807);
    wram->wc807 = wram->wc805;
    // RET;
}

bool PacketSendEmptyBody(const uint8_t* bytes, uint8_t id){
    // LD_DE(10);
    return Function111f02(bytes, 10, id);
}

bool Function111f02(const uint8_t* bytes, uint16_t size, uint8_t id){
    // LD_addr_A(wMobileSDK_SendCommandID);
    wram->wMobileSDK_SendCommandID = id;
    // LD_B(0x5);

    return PacketSendBytes(bytes, size, 0x5);
}

//  hl = bytes
//  de = size
//  b = ?
bool PacketSendBytes(const uint8_t* bytes, uint16_t size, uint8_t b){
    // CALL(aFunction1100b4);
    // RET_C ;
    if(Function1100b4())
        return true;
    // LD_A_addr(wc800);
    // CP_A(0x0);
    // IF_Z goto asm_111f17;
    if(wram->wc800 != 0x0) {
        // CALL(aFunction110226);
        Function110226();
        // SCF;
        // RET;
        return true;
    }

    do {
    // asm_111f17:
        DelayFrame();
        // LDH_A_addr(rSC);
        // AND_A(1 << rSC_ON);
        // IF_NZ goto asm_111f17;
    } while((gb_read(rSC) & (1 << rSC_ON)) != 0);
    // NOP;
    // LD_A_addr(wMobileSDK_SendCommandID);
    // CP_A(0xff);
    // IF_Z goto asm_111f35;
    if(wram->wMobileSDK_SendCommandID != 0xff) {
        // LD_A_L;
        // LD_addr_A(wc81c);
        // LD_A_H;
        // LD_addr_A(wc81d);
        gMobileSendPacketPointer = bytes;
        // LD_A_E;
        // LD_addr_A(wc81a);
        // LD_A_D;
        // LD_addr_A(wc81b);
        gMobileSendPacketSize = size;
    }

// asm_111f35:
    // LD_A_E;
    // LD_addr_A(wc801);
    // LD_A_D;
    // LD_addr_A(wc802);
    gMobilePacketSize = size;
    // LD_A_L;
    // LD_addr_A(wc803);
    // LD_A_H;
    // LD_addr_A(wc804);
    gMobilePacketPointer = bytes;
    // LD_HL(wc807);
    // LD_A_hl;
    // CP_A_B;
    // IF_Z goto asm_111f4f;
    if(wram->wc807 != b) {
        // LD_addr_A(wc805);
        wram->wc805 = wram->wc807;
    }

// asm_111f4f:
    // LD_A_B;
    // LD_addr_A(wc807);
    wram->wc807 = b;
    // XOR_A_A;
    // LD_addr_A(wc806);
    wram->wc806 = 0x0;
    // LD_A(0x1);
    // LD_addr_A(wc800);
    wram->wc800 = 0x1;
    // LD_HL(wc822);
    // SET_hl(5);
    bit_set(wram->wc822, 5);
    // NOP;
    // RET;
    return false;
}

uint16_t Function111f63(uint8_t* de, uint8_t b){
    // PUSH_DE;
    // LD_HL(0);
    uint16_t hl = 0;
    // LD_C_B;
    uint8_t c = b;
    // XOR_A_A;
    // CP_A_B;
    // IF_Z goto asm_111f71;
    while(b != 0) {
    // asm_111f6c:
        // CALL(aFunction111f8d);
        Function111f8d(&de, &hl, &b);
        // IF_NZ goto asm_111f6c;
    }

// asm_111f71:
    // LD_B(0x4);
    b = 0x4;

    do {
    // asm_111f73:
        // CALL(aFunction111f8d);
        Function111f8d(&de, &hl, &b);
        // IF_NZ goto asm_111f73;
    } while(b != 0);
    // LD_E_L;
    // LD_D_H;
    // LD_HL(0x000a);
    // ADD_HL_BC;
    // LD_C_L;
    // LD_B_H;
    uint16_t bc = 0x000a + c;
    // POP_HL;
    // LD_A_D;
    // LD_hli_A;
    *(de++) = HIGH(hl);
    // LD_A_E;
    // LD_hli_A;
    *(de++) = LOW(hl);
    // LD_A(0x80);
    // LD_hli_A;
    (*de++) = 0x80;
    // XOR_A_A;
    // LD_hl_A;
    *de = 0x0;
    // LD_E_C;
    // LD_D_B;
    // RET;
    return bc;
}

void Function111f8d(uint8_t** de, uint16_t* hl, uint8_t* b){
    // DEC_DE;
    (*de)--;
    // LD_A_de;
    uint8_t a = **de;
    // ADD_A_L;
    // LD_L_A;
    // LD_A(0x0);
    // ADC_A_H;
    // LD_H_A;
    *hl += a;
    // DEC_B;
    (*b)--;
    // RET;
}

bool Function111f97(void){
    // LD_HL(wc822);
    // BIT_hl(0);
    // RET_NZ ;
    if(bit_test(wram->wc822, 0))
        return false;
    // LD_A_addr(wc807);
    // CP_A(0x2);
    // IF_C goto asm_111fcb;
    // CP_A(0x5);
    // IF_Z goto asm_111fcb;
    if(wram->wc807 < 0x2 || wram->wc807 == 0x5)
        return true;
    // CP_A(0x6);
    // IF_NZ goto asm_111fcd;
    if(wram->wc807 == 0x6) {
        // LD_A_addr(wc80f);
        uint8_t a = wram->wc80f;
        // CP_A(0x22);
        // IF_Z goto asm_111fcb;
        // CP_A(0x23);
        // IF_Z goto asm_111fcb;
        // CP_A(0x26);
        // IF_Z goto asm_111fcb;
        if(a == 0x22 || a == 0x23 || a == 0x26)
            return true;
        // SWAP_A;
        // AND_A(0xf);
        a = (a >> 4) & 0xf;
        // CP_A(0x1);
        // IF_Z goto asm_111fcb;
        // CP_A(0x0);
        // IF_Z goto asm_111fcb;
        // CP_A(0x8);
        // IF_NZ goto asm_111fcd;
        if(a == 0x1 || a == 0x0 || a == 0x8) {
        // asm_111fcb:
            // SCF;
            // RET;
            return true;
        }
    }

// asm_111fcd:
    // LD_B(0x5);
    // LD_HL(wMobileSDK_SendCommandID);
    // LD_A_hl;
    // CP_A(-1);
    // IF_Z goto asm_111fe9;
    if(wram->wMobileSDK_SendCommandID == 0xff) {
    // asm_111fe9:
        // LD_HL(mMobilePacket_BeginSession);
        // LD_DE(lengthof(MobilePacket_BeginSession));
        // JP(mPacketSendBytes);
        return PacketSendBytes(MobilePacket_BeginSession, lengthof(MobilePacket_BeginSession), 0x5);
    }
    // LD_A(MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
    // LD_hl_A;
    wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_TELEPHONE_STATUS | 0x80;
    // LD_HL(mMobilePacket_TelephoneStatus);
    // LD_DE(lengthof(MobilePacket_TelephoneStatus));
    // CALL(aPacketSendBytes);
    PacketSendBytes(MobilePacket_TelephoneStatus, lengthof(MobilePacket_TelephoneStatus), 0x5);
    // LD_HL(wc822);
    // SET_hl(0);
    bit_set(wram->wc822, 0);
    // RET;
    return false;
    //ds ['14']

}

// Mobile_TimerValues?
const uint8_t Unknown_112089[] = {
    (uint8_t)-20, 0x14, 0xc9,
    (uint8_t)-28, 0x0f, 0x0e,
    (uint8_t)-32, 0x0c, 0x53,
    (uint8_t)-60, 0x07, 0x94,
    (uint8_t)-80, 0x05, 0xee,
    (uint8_t)-20, 0x10, 0xb4,
    (uint8_t)-28, 0x0c, 0xdd,
};

// Mail Strings

const char Unknown_11209e[] = "HELO ";              //db ['"HELO "', '0'];
const char Unknown_1120a4[] = "MAIL FROM:<";        //db ['"MAIL FROM:<"', '0'];
const char Unknown_1120b0[] = "RCPT TO:<";          //db ['"RCPT TO:<"', '0'];
const char Unknown_1120ba[] = "DATA\r\n";           //db ['"DATA\\r\\n"', '0'];
const char Unknown_1120c1[] = "QUIT\r\n";           //db ['"QUIT\\r\\n"', '0'];
const char Unknown_1120c8[] = "USER ";              //db ['"USER "', '0'];
const char Unknown_1120ce[] = "PASS ";              //db ['"PASS "', '0'];
const char Unknown_1120d4[] = "STAT\r\n";           //db ['"STAT\\r\\n"', '0'];
const char Unknown_1120db[] = "LIST 00000\r\n";     //db ['"LIST 00000\\r\\n"', '0'];
const char Unknown_1120e8[] = "RETR 00000\r\n";     //db ['"RETR 00000\\r\\n"', '0'];
const char Unknown_1120f5[] = "DELE 00000\r\n";     //db ['"DELE 00000\\r\\n"', '0'];
const char Unknown_112102[] = "TOP 00000 0\r\n";    //db ['"TOP 00000 0\\r\\n"', '0'];
const char Unknown_112110[] = "GET ";               //db ['"GET "', '0'];
const char Unknown_112115[] = " HTTP/1.0\r\n";      //db ['" HTTP/1.0\\r\\n"', '0'];
const char Unknown_112121[] = "User-Agent: CGB-";   //db ['"User-Agent: CGB-"', '0'];
const char Unknown_112132[] = "\r\n\r\n";           //db ['"\\r\\n\\r\\n"', '0'];
const char Unknown_112137[] = "POST ";              //db ['"POST "', '0'];
const char Unknown_11213d[] = "Content-Length: ";   //db ['"Content-Length: "', '0'];

void Function11214e(void){
    // LD_A_addr(wc822);
    // BIT_A(5);
    // RET_NZ ;
    if(bit_test(wram->wc822, 5))
        return;
    // LD_A_addr(wc86a);
    // CP_A(0xa);
    // RET_C ;
    if(wram->wc86a < 0xa)
        return;
    // LD_C_A;
    uint8_t c = wram->wc86a;
    // CP_A(0xd);
    // IF_Z goto asm_112187;
    if(c == 0xd) {
    // asm_112187:
        // LD_C_A;
        // LD_A_addr(wc86b);
        // CP_A(0x1);
        // IF_NZ goto asm_11216f;
        if(wram->wc86b != 0x1)
            goto asm_11216f;
        // LD_HL(wc821);
        // RES_hl(1);
        bit_reset(wram->wc821, 1);
        // goto asm_112175;
    }
    // CP_A(0xf);
    // IF_Z goto asm_112196;
    else if(c == 0xf) {
    // asm_112196:
        // LD_C_A;
        // LD_A_addr(wc80f);
        // CP_A(0x24);
        // IF_NZ goto asm_11216f;
        // LD_A_addr(wc86b);
        // CP_A(0x1);
        // IF_NZ goto asm_11216f;
        if(wram->wc80f != 0x24 || wram->wc86b != 0x1)
            goto asm_11216f;
        // LD_HL(wc821);
        // RES_hl(1);
        bit_reset(wram->wc821, 1);
        // goto asm_112175;
    }
    // CP_A(0x29);
    // IF_Z goto asm_112175;
    // CP_A(0x2a);
    // IF_Z goto asm_112175;
    // CP_A(0x28);
    // IF_Z goto asm_112175;
    else if(c == 0x29 || c == 0x2a || c == 0x28) {

    }
    else {
    asm_11216f:
        // LD_A_addr(wc807);
        // CP_A(0x6);
        // RET_Z ;
        if(wram->wc807 == 0x6)
            return;
    }

// asm_112175:
    // LD_B(0x0);
    // SLA_C;
    // LD_HL(mJumptable_1121ac - 2 * 0xa);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // PUSH_HL;
    // LD_HL(wc86b);
    // INC_hl;
    // LD_A_hl;
    // RET;
    return Jumptable_1121ac[(c << 1) - 0xa](&wram->wc86c, wram->wc86b);
}

const Jumptable_1121ac_t Jumptable_1121ac[] = {
    //dw ['Function1121f6'];
    //dw ['Function112271'];
    //dw ['Function112373'];
    //dw ['Function1123b6'];
    //dw ['Function1123e1'];
    //dw ['Function112451'];
    //dw ['Function112715'];
    //dw ['Function11273a'];
    //dw ['Function11299c'];
    //dw ['Function112d33'];
    //dw ['Function112d33'];
    //dw ['Function112840'];
    //dw ['Function1128db'];
    //dw ['Function112969'];
    //dw ['Function112a56'];
    //dw ['Function112b71'];
    //dw ['Function112bec'];
    //dw ['Function112bbb'];
    //dw ['Function112bec'];
    //dw ['Function112b71'];
    //dw ['Function1134cb'];
    //dw ['Function112d33'];
    //dw ['Function112d33'];
    //dw ['Function112d33'];
    //dw ['Function112d33'];
    //dw ['Function112d33'];
    //dw ['Function112d33'];
    //dw ['Function113519'];
    //dw ['Function113519'];
    //dw ['Function113519'];
    //dw ['Function113e42'];
    //dw ['Function113ef2'];
    //dw ['Function113f2d'];
    //dw ['Function1121f6'];
    //dw ['Function1134cb'];
    //dw ['Function113672'];
    //dw ['Function113626'];
};

void Function1121f6(void){
    DEC_A;
    IF_Z goto asm_1121fe;
    DEC_A;
    IF_Z goto asm_112210;
    DEC_hl;
    RET;


asm_1121fe:
    LD_A_addr(wMobileSDK_AdapterType);
    OR_A_A;
    IF_Z goto asm_112206;
    JR(mFunction112269);


asm_112206:
    LD_A(0x10);
    CALL(aFunction11225d);
    RES_hl(0);
    SET_hl(1);
    RET;


asm_112210:
    LD_HL(wc86e);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wMobileSDK_AdapterType);
    CP_A(0x88);
    IF_C goto asm_112249;
    SUB_A(0x88);
    LD_hl_A;

// There aren't more than four adapters
    CP_A(0x4);
    IF_C goto asm_112226;
    LD_A(0x3);

asm_112226:

// The green adapter was scrapped, so the red adapter is the third
    CP_A(0x3);
    IF_NZ goto asm_11222b;
    DEC_A;

asm_11222b:

    LD_B_A;
    LD_A(0x4);
    SUB_A_B;
    LD_D_A;
    RLCA;
    ADD_A_D;
    LD_C_A;
    XOR_A_A;
    CP_A_B;
    IF_Z goto asm_11223a;
    LD_A(0x3);
    XOR_A_B;


asm_11223a:
    LD_HL(wc871);
    LD_hld_A;
    LD_hl_C;
    LD_A_addr(wc86a);
    CP_A(0xa);
    JR_NZ (mFunction112251);
    JP(mFunction1116a0);


asm_112249:
    LD_A(0x10);
    CALL(aFunction11225d);
    JP(mFunction1116a4);

}

void Function112251(void){
    // XOR_A_A;
    // LD_addr_A(wc821);
    wram->wc821 = 0x0;
    // LD_addr_A(wc807);
    wram->wc807 = 0x0;
    // INC_A;
    // LD_addr_A(wc86a);
    wram->wc86a = 0x1;
    // RET;
}

void Function11225d(void){
    LD_addr_A(wc80f);
    LD_A(0x5);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    RET;

}

// Mobile_SendEndSession
bool Function112269(void){
    // LD_A(MOBILE_COMMAND_END_SESSION | 0x80);
    // LD_HL(mMobilePacket_EndSession);
    // JP(mPacketSendEmptyBody);
    return PacketSendEmptyBody(MobilePacket_EndSession, MOBILE_COMMAND_END_SESSION | 0x80);
}

void Function112271(void){
    DEC_A;
    IF_Z goto asm_11228c;
    DEC_A;
    IF_Z goto asm_112292;
    DEC_A;
    IF_Z goto asm_1122a1;
    DEC_A;
    JP_Z (mFunction112271_asm_112309);
    DEC_A;
    JP_Z (mFunction112271_asm_112326);
    DEC_A;
    JP_Z (mFunction112271_asm_112335);
    DEC_A;
    JP_Z (mFunction112271_asm_112342);
    DEC_hl;
    RET;


asm_11228c:
    LD_HL(mMobilePacket_ReadConfigurationDataPart1);
    JP(mFunction11236b);


asm_112292:
    LD_HL(wc829);
    LD_A(0xe0);
    LD_hli_A;
    LD_A(0xc8);
    LD_hli_A;
    LD_HL(mMobilePacket_ReadConfigurationDataPart2);
    JP(mFunction11236b);


asm_1122a1:
    LD_HL(wc880);
    LD_A_hli;
    CP_A(0x4d);
    IF_NZ goto asm_1122f5;
    LD_A_hld;
    CP_A(0x41);
    IF_NZ goto asm_1122f5;
    LD_B(0xbe);
    LD_DE(0);

asm_1122b3:
    LD_A_hli;
    ADD_A_E;
    LD_E_A;
    LD_A(0x0);
    ADC_A_D;
    LD_D_A;
    DEC_B;
    IF_NZ goto asm_1122b3;
    LD_A_hli;
    CP_A_D;
    IF_NZ goto asm_1122fc;
    LD_A_hl;
    CP_A_E;
    IF_NZ goto asm_1122fc;
    LD_HL(wc884);
    LD_DE(wc836);
    LD_B(0x8);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc8ca);
    LD_B(0x2c);
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wMobileSDK_PacketBuffer + 50);
    LD_C_A;
    SUB_A(0x8);
    LD_E_A;
    LD_D(0);
    LD_HL(wMobileSDK_PacketBuffer + 51);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(wc836);
    LD_B(0x8);
    CALL(aMobileSDK_CopyBytes);
    LD_B_C;
    CALL(aFunction111f63);
    JR(mFunction11235a);


asm_1122f5:
    LD_A(0x25);
    LD_addr_A(wc872);
    goto asm_112301;


asm_1122fc:
    LD_A(0x14);
    LD_addr_A(wc872);


asm_112301:
    LD_A(0x6);
    LD_addr_A(wc86b);
    JP(mFunction112269);


asm_112309:
    LD_A_addr(wc821);
    AND_A(0xe0);
    IF_NZ goto asm_112314;
    LD_B(0x92);
    JR(mFunction11234b);


asm_112314:
    CP_A(0xe0);
    LD_A(0x11);
    IF_Z goto asm_11231b;
    INC_A;


asm_11231b:
    LD_addr_A(wc872);
    LD_A(0x6);
    LD_addr_A(wc86b);
    JP(mFunction112269);


asm_112326:
    LD_D_A;
    LD_A_addr(wMobileSDK_PacketBuffer + 50);
    ADD_A(0xa);
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 45);
    LD_A(0xa1);
    JP(mFunction111f02);


asm_112335:
    LD_A(0x2);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    RES_hl(0);
    SET_hl(5);
    RET;


asm_112342:
    LD_A_addr(wc872);
    CALL(aFunction11225d);
    JP(mFunction1116a4);

}

void Function11234b(void){
    LD_A_addr(wMobileSDK_PacketBuffer + 5);
    ADD_A(0xa);
    LD_E_A;
    LD_D(0);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_A_B;
    JP(mFunction111f02);

}

void Function11235a(void){
    LD_HL(wc86e);
    LD_A(0x80);
    LD_hli_A;
    LD_A(0xc8);
    LD_hl_A;
    LD_A(MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
    LD_HL(mMobilePacket_TelephoneStatus);
    JP(mPacketSendEmptyBody);

}

void Function11236b(void){
    LD_A(0x99);
    LD_DE(0x000c);
    JP(mFunction111f02);

}

void Function112373(void){
    DEC_A;
    JR_Z (mFunction11235a);
    DEC_A;
    IF_Z goto asm_112381;
    DEC_A;
    IF_Z goto asm_11239b;
    DEC_A;
    IF_Z goto asm_1123ad;
    DEC_hl;
    RET;


asm_112381:
    LD_A_addr(wc821);
    AND_A(0xe0);
    IF_NZ goto asm_11238c;
    LD_B(0x92);
    JR(mFunction11234b);


asm_11238c:
    CP_A(0xe0);
    LD_A(0x11);
    IF_Z goto asm_112393;
    INC_A;


asm_112393:
    LD_A(0x3);
    LD_addr_A(wc86b);
    JP(mFunction112269);


asm_11239b:
    LD_HL(wc822);
    SET_hl(4);
    LD_A(0x2);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    RES_hl(0);
    SET_hl(6);
    RET;


asm_1123ad:
    LD_A_addr(wc872);
    CALL(aFunction11225d);
    JP(mFunction1116a4);

}

void Function1123b6(void){
    DEC_A;
    IF_Z goto asm_1123be;
    DEC_A;
    IF_Z goto asm_1123c6;
    RET;


asm_1123bd:
    DEC_hl;


asm_1123be:
    LD_A(MOBILE_COMMAND_WAIT_FOR_TELEPHONE_CALL | 0x80);
    LD_HL(mMobilePacket_WaitForTelephoneCall);
    JP(mPacketSendEmptyBody);


asm_1123c6:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0xee);
    IF_Z goto asm_1123bd;
    LD_HL(wc822);
    SET_hl(4);
    LD_A(0x2);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    RES_hl(0);
    SET_hl(6);
    SET_hl(5);
    RET;

}

void Function1123e1(void){
    DEC_A;
    IF_Z goto asm_1123f2;
    DEC_A;
    IF_Z goto asm_11240a;
    DEC_A;
    IF_Z goto asm_112416;
    DEC_A;
    IF_Z goto asm_11241e;
    DEC_A;
    IF_Z goto asm_112421;
    DEC_hl;
    RET;


asm_1123f2:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    IF_Z goto asm_112408;
    CALL(aFunction1127e1);
    IF_Z goto asm_112408;
    LD_HL(wc86b);
    DEC_hl;
    LD_HL(wMobileSDK_PacketBuffer + 32);
    JP(mFunction1127c5);


asm_112408:
    JR(mFunction112430);


asm_11240a:
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_A(MOBILE_COMMAND_ISP_LOGOUT | 0x80);
    LD_HL(mMobilePacket_ISPLogout);
    JP(mPacketSendEmptyBody);


asm_112416:
    LD_A(MOBILE_COMMAND_HANG_UP_TELEPHONE | 0x80);
    LD_HL(mMobilePacket_HangUpTelephone);
    JP(mPacketSendEmptyBody);


asm_11241e:
    JP(mFunction112269);


asm_112421:
    LD_HL(wc822);
    RES_hl(4);
    LD_HL(wc821);
    LD_A_hl;
    AND_A(0xf);
    LD_hl_A;
    JP(mFunction1116a0);

}

void Function112430(void){
    LD_A(0x3);
    LD_addr_A(wc807);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_CloseTCPConnection);
    LD_B(lengthof(MobilePacket_CloseTCPConnection));
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    INC_B;
    CALL(aFunction111f63);
    LD_A(0xa4);
    LD_HL(wMobileSDK_PacketBuffer);
    JP(mFunction111f02);

}

void Function112451(void){
    DEC_A;
    IF_Z goto asm_112458;
    DEC_A;
    IF_Z goto asm_112496;
    RET;


asm_112458:
    LD_B(0x6);
    LD_DE(wMobileSDK_PacketBuffer + 92);
    CALL(aFunction111f63);
    LD_A_addr(wc86e);
    INC_A;
    CP_A(0x3);
    IF_NZ goto asm_11248b;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 128);
    OR_A_A;
    IF_Z goto asm_11248b;
    LD_HL(wc995);
    LD_A_hli;
    CP_A(0x99);
    IF_NZ goto asm_112480;
    LD_A_hli;
    CP_A(0x66);
    IF_NZ goto asm_112480;
    LD_A_hli;
    CP_A(0x23);
    IF_Z goto asm_11248b;


asm_112480:
    LD_HL(wMobileSDK_PacketBuffer + 80);
    LD_DE(wc995);
    LD_B(0x10);
    CALL(aMobileSDK_CopyBytes);


asm_11248b:
    LD_A(0xa3);
    LD_DE(0x0010);
    LD_HL(wMobileSDK_PacketBuffer + 80);
    JP(mFunction111f02);


asm_112496:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0xa3);
    IF_Z goto asm_1124ce;
    LD_A_addr(wc822);
    BIT_A(3);
    IF_Z goto asm_1124ab;
    DEC_hl;
    LD_A(0x3);
    LD_addr_A(wc807);
    RET;


asm_1124ab:
    LD_A_addr(wc9af);
    CP_A(0x5);
    IF_C goto asm_1124b8;
    LD_HL(wc821);
    SET_hl(1);
    RET;


asm_1124b8:
    DEC_hl;
    LD_HL(wc9af);
    INC_hl;
    LD_HL(wc822);
    SET_hl(3);
    LD_HL(wc815);
    LD_A_addr(wc820);
    LD_hli_A;
    LD_A_addr(wc81f);
    LD_hl_A;
    RET;


asm_1124ce:
    XOR_A_A;
    LD_addr_A(wc9af);
    LD_A_addr(wc86e);
    INC_A;
    LD_addr_A(wc86d);
    DEC_A;
    JP_Z (mFunction11261c);
    DEC_A;
    JP_Z (mFunction112654);
    DEC_A;
    JP_Z (mFunction112597);
    DEC_A;
    JP_Z (mFunction112566);
    CALL(aFunction1125c7);
    PUSH_DE;
    LD_DE(wc880);
    LD_HL(wc827);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_A(0x1);
    LD_addr_A(wc86e);
    LD_A(0xfa);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    POP_DE;
    LD_A(0x1);
    LD_addr_A(wc994);
    CALL(aFunction11269b);
    LD_A(0x5);
    LD_addr_A(wc86b);
    CALL(aFunction112534);
    LD_A_addr(wc9a5);
    OR_A_A;
    IF_Z goto asm_112521;
    LD_A(0x1);


asm_112521:
    ADD_A(0x23);
    LD_addr_A(wc86a);
    LD_A_addr(wc98a);
    CP_A(0x2);
    IF_NZ goto asm_112531;
    XOR_A_A;
    LD_addr_A(wc9a5);


asm_112531:
    JP(mFunction1125bf);

}

void Function112534(void){
    LD_B(0xfa);
    LD_HL(wc880);
    XOR_A_A;

asm_11253a:
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_11253a;
    LD_A_addr(wc876);
    LD_addr_A(wc87c);
    LD_A_addr(wc877);
    LD_addr_A(wc87d);
    LD_A_addr(wc87a);
    LD_addr_A(wc87e);
    LD_A_addr(wc87b);
    LD_addr_A(wc87f);
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 17);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(0x95);
    LD_HL(wMobileSDK_PacketBuffer + 12);
    JP(mFunction111f02);

}

void Function112566(void){
    CALL(aFunction1125c7);
    LD_A_addr(wMobileSDK_PacketBuffer + 19);
    AND_A(0x1);
    OR_A_A;
    IF_NZ goto asm_11257d;
    LD_A_addr(wc98a);
    CP_A(0x2);
    IF_NZ goto asm_11257d;
    LD_A(0x1);
    LD_addr_A(wc994);


asm_11257d:
    CALL(aFunction11269b);
    LD_A(0x5);
    LD_addr_A(wc86b);
    CALL(aFunction112534);
    LD_A_addr(wc9a5);
    OR_A_A;
    IF_Z goto asm_112590;
    LD_A(0x1);


asm_112590:
    ADD_A(0x21);
    LD_addr_A(wc86a);
    JR(mFunction1125bf);

}

void Function112597(void){
    CALL(aFunction1125c7);
    CALL(aFunction11269b);
    LD_A(0x5);
    LD_addr_A(wc86b);
    CALL(aFunction112534);
    LD_A_addr(wc98f);
    LD_B_A;
    LD_A_addr(wc994);
    AND_A(0x1);
    ADD_A(0x13);
    BIT_B(0);
    IF_Z goto asm_1125bc;
    SUB_A(0x13);
    ADD_A(0x1f);
    DEC_B;
    SLA_B;
    ADD_A_B;


asm_1125bc:
    LD_addr_A(wc86a);

    return Function1125bf();
}

void Function1125bf(void){
    LD_HL(wc821);
    SET_hl(0);
    RES_hl(2);
    RET;

}

void Function1125c7(void){
    LD_HL(wc872);
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_E_A;
    LD_D_hl;
    LD_A_addr(wc994);
    AND_A(0x1);
    XOR_A(0x1);
    LD_addr_A(wc86b);
    LD_HL(wc827);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    INC_DE;
    INC_DE;
    LD_A(0x80);
    LD_hli_A;
    LD_A(0xc8);
    LD_hli_A;
    DEC_BC;
    DEC_BC;
    LD_A(0xfa);
    LD_hli_A;
    LD_A(0x0);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_B(0x1);
    CALL(aFunction111f63);
    LD_DE(wMobileSDK_PacketBuffer + 12);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x5);
    CALL(aMobileSDK_CopyBytes);
    INC_DE;
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    RET;

}

void Function11261c(void){
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_A_addr(wc86c);
    LD_addr_A(wMobileSDK_PacketBuffer + 118);
    LD_DE(wMobileSDK_PacketBuffer + 102);
    LD_de_A;
    INC_DE;
    LD_B(0x1);
    CALL(aFunction111f63);
    CALL(aFunction112724);
    LD_A_addr(wMobileSDK_PacketBuffer + 117);
    LD_B_A;
    LD_DE(wMobileSDK_PacketBuffer + 118);
    ADD_A_E;
    LD_E_A;
    LD_A(0x0);
    ADC_A_D;
    LD_D_A;
    CALL(aFunction111f63);
    LD_HL(wMobileSDK_PacketBuffer + 96);
    CALL(aFunction1127c5);
    LD_A(0x11);
    LD_addr_A(wc86a);

    return Function11264e();
}

void Function11264e(void){
    LD_HL(wc821);
    SET_hl(0);
    RET;

}

void Function112654(void){
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_A_addr(wc86c);
    LD_addr_A(wMobileSDK_PacketBuffer + 102);
    LD_addr_A(wMobileSDK_PacketBuffer + 166);
    LD_DE(wMobileSDK_PacketBuffer + 134);
    LD_de_A;
    INC_DE;
    LD_B(0x1);
    CALL(aFunction111f63);
    CALL(aFunction112724);
    LD_A_addr(wMobileSDK_PacketBuffer + 165);
    LD_B_A;
    LD_DE(wMobileSDK_PacketBuffer + 166);
    ADD_A_E;
    LD_E_A;
    LD_A(0x0);
    ADC_A_D;
    LD_D_A;
    CALL(aFunction111f63);
    LD_A_addr(wMobileSDK_PacketBuffer + 101);
    LD_B_A;
    LD_DE(wMobileSDK_PacketBuffer + 102);
    ADD_A_E;
    LD_E_A;
    LD_A(0x0);
    ADC_A_D;
    LD_D_A;
    CALL(aFunction111f63);
    LD_HL(wMobileSDK_PacketBuffer + 128);
    CALL(aFunction1127c5);
    LD_A(0x12);
    LD_addr_A(wc86a);
    JR(mFunction11264e);

}

void Function11269b(void){
    LD_BC(0x0001);
    LD_HL(mUnknown_112110);
    LD_A_addr(wc994);
    OR_A_A;
    CALL_NZ (aFunction1126ac);
    CALL(aMobileSDK_CopyString);
    RET;

}

void Function1126ac(void){
    LD_HL(mUnknown_112137);
    RET;

}

void Function1126b0(void){
    LD_HL(mUnknown_112115);
    JP(mMobileSDK_CopyString);

}

void Function1126b6(void){
    LD_HL(mUnknown_112121);
    CALL(aMobileSDK_CopyString);
    LD_HL(0x013f);
    LD_B(0x4);
    CALL(aMobileSDK_CopyBytes);
    LD_A(0x2d);
    LD_de_A;
    INC_DE;
    LD_A_addr(0x014c);
    AND_A(0xf0);
    SWAP_A;
    OR_A(0x30);
    LD_de_A;
    INC_DE;
    LD_A_addr(0x014c);
    AND_A(0xf);
    OR_A(0x30);
    LD_de_A;
    INC_DE;
    LD_A(0x7);
    ADD_A_C;
    LD_C_A;
    LD_HL(mUnknown_112132);
    JP(mMobileSDK_CopyString);

}

void Function1126e6(void){
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_HL(mUnknown_11213d);
    CALL(aMobileSDK_CopyString);
    LD_HL(wc9a5);
    LD_B(0x5);

asm_1126f5:
    LD_A_hl;
    CP_A(0x30);
    IF_NZ goto asm_112701;
    INC_HL;
    DEC_B;
    LD_A(0x1);
    CP_A_B;
    IF_NZ goto asm_1126f5;


asm_112701:
    PUSH_BC;
    CALL(aMobileSDK_CopyBytes);
    LD_A(0xd);
    LD_de_A;
    INC_DE;
    LD_A(0xa);
    LD_de_A;
    INC_DE;
    POP_BC;
    LD_A_B;
    ADD_A(0x2);
    ADD_A_C;
    LD_C_A;
    OR_A_C;
    RET;

}

void Function112715(void){
    XOR_A_A;
    LD_addr_A(wc86c);
    LD_A(0x2);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    RES_hl(0);
    RET;

}

void Function112724(void){
    LD_A(0xff);
    LD_addr_A(wc86e);

    return Function112729();
}

void Function112729(void){
    PUSH_HL;
    LD_HL(wc82c);
    XOR_A_A;
    LD_hld_A;
    LD_A(0xff);
    LD_hld_A;
    LD_A(0xc8);
    LD_hld_A;
    LD_A(0x80);
    LD_hl_A;
    POP_HL;
    RET;

}

void Function11273a(void){
    DEC_A;
    IF_Z goto asm_112752;
    DEC_A;
    IF_Z goto asm_11278f;
    DEC_A;
    IF_Z goto asm_112744;
    RET;


asm_112744:
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_A(0x30);
    CALL(aFunction11225d);
    SET_hl(1);
    RES_hl(0);
    RET;


asm_112752:
    CALL(aFunction1127e1);
    IF_NZ goto asm_11277a;
    LD_HL(wc880);
    CALL(aFunction112b11);
    LD_A(0x2);
    CP_A_D;
    IF_NZ goto asm_1127b7;
    LD_A(0x20);
    CP_A_E;
    IF_NZ goto asm_1127b7;
    CALL(aFunction112724);
    LD_A_addr(wMobileSDK_PacketBuffer + 117);
    ADD_A(0xa);
    LD_E_A;
    LD_D(0);
    LD_A(0x95);
    LD_HL(wMobileSDK_PacketBuffer + 112);
    JP(mFunction111f02);


asm_11277a:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    JR_Z (mFunction1127cd);
    LD_HL(wc86b);
    DEC_hl;
    XOR_A_A;
    LD_addr_A(wMobileSDK_ReceivePacketBuffer + 3);
    LD_HL(wMobileSDK_PacketBuffer + 96);
    JP(mFunction1127c5);


asm_11278f:
    CALL(aFunction1127e1);
    IF_NZ goto asm_11277a;
    LD_HL(wc880);
    CALL(aFunction112b11);
    LD_A(0x2);
    CP_A_D;
    IF_NZ goto asm_1127b7;
    LD_A(0x50);
    CP_A_E;
    IF_NZ goto asm_1127b7;
    LD_A(0x3);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    LD_A_hl;
    AND_A(0xd6);
    OR_A(0x80);
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wc98a);
    RET;


asm_1127b7:
    LD_HL(wc810);
    LD_A_E;
    LD_hli_A;
    LD_hl_D;
    LD_A(0x2);
    LD_addr_A(wc86b);
    JP(mFunction112430);

}

void Function1127c5(void){
    LD_DE(0x000b);
    LD_A(0x95);
    JP(mFunction111f02);

}

void Function1127cd(void){
    LD_HL(wc810);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_A(0x30);
    CALL(aFunction11225d);
    SET_hl(1);
    RES_hl(0);
    RET;

}

void Function1127e1(void){
    CALL(aFunction112807);
    LD_HL(wc832);

    return Function1127e7();
}

void Function1127e7(void){
    LD_A_hli;
    CP_A(0xd);
    RET_NZ ;
    LD_A_hl;
    CP_A(0xa);
    RET_NZ ;
    LD_A(0x20);
    LD_hl_A;
    RET;

}

void Function1127f3(void){
    CALL(aFunction112807);
    LD_HL(wc82f);
    LD_A_hli;
    CP_A(0xd);
    RET_NZ ;
    LD_A_hli;
    CP_A(0xa);
    RET_NZ ;
    LD_A_hli;
    CP_A(0x2e);
    RET_NZ ;
    JR(mFunction1127e7);

}

void Function112807(void){
    PUSH_BC;
    PUSH_DE;
    LD_HL(wMobileSDK_ReceivePacketBuffer + 3);
    LD_A_hl;
    DEC_A;
    IF_Z goto asm_11282d;
    LD_C_A;
    CP_A(0x5);
    IF_NC goto asm_112830;
    LD_A(0x5);
    SUB_A_C;
    LD_B_A;
    LD_E_C;
    LD_D(0x0);
    LD_HL(wc82f);
    ADD_HL_DE;
    LD_DE(wc82f);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wMobileSDK_ReceivePacketBuffer + 5);
    LD_B_C;

asm_11282a:
    CALL(aMobileSDK_CopyBytes);


asm_11282d:
    POP_DE;
    POP_BC;
    RET;


asm_112830:
    SUB_A(0x5);
    LD_C_A;
    LD_B(0);
    LD_HL(wMobileSDK_ReceivePacketBuffer + 5);
    ADD_HL_BC;
    LD_B(0x5);
    LD_DE(wc82f);
    goto asm_11282a;

    return Function112840();
}

void Function112840(void){
    DEC_A;
    IF_Z goto asm_112844;
    RET;


asm_112844:
    CALL(aFunction1127e1);
    IF_NZ goto asm_1128ab;
    LD_HL(wc880);
    LD_A_hli;
    CP_A(0x32);
    JR_NZ (mFunction1128bd);
    LD_A_hli;
    CP_A(0x35);
    JR_NZ (mFunction1128bd);
    CALL(aFunction112724);
    LD_HL(wc87c);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hl;
    OR_A_A;
    IF_Z goto asm_11289d;
    PUSH_HL;
    LD_HL(wc86b);
    DEC_hl;
    LD_BC(0x0001);
    LD_DE(wMobileSDK_PacketBuffer + 19);
    LD_HL(mUnknown_1120b0);
    CALL(aMobileSDK_CopyString);
    POP_HL;
    LD_A(0x80);
    CALL(aMobileSDK_CopyStringLen);
    LD_A(0x3e);
    LD_de_A;
    INC_DE;
    INC_C;
    LD_A_L;
    LD_addr_A(wc87c);
    LD_A_H;
    LD_addr_A(wc87d);
    CALL(aFunction11295e);
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 17);
    LD_B_C;
    CALL(aFunction111f63);
    LD_HL(wMobileSDK_PacketBuffer + 12);
    LD_D(0x0);
    LD_E_C;
    LD_A(0x95);
    JP(mFunction111f02);


asm_11289d:
    LD_A(0x3);
    LD_addr_A(wc86a);
    CALL(aFunction1128d3);
    LD_A(0x1);
    LD_addr_A(wc98a);
    RET;


asm_1128ab:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    JP_Z (mFunction1127cd);
    LD_HL(wc86b);
    DEC_hl;
    LD_HL(wMobileSDK_PacketBuffer);
    JP(mFunction1127c5);

}

void Function1128bd(void){
    LD_HL(wc880);
    CALL(aFunction112b11);
    LD_HL(wc810);
    LD_A_E;
    LD_hli_A;
    LD_hl_D;
    LD_A(0x30);
    CALL(aFunction11225d);
    SET_hl(1);
    RES_hl(0);
    RET;

}

void Function1128d3(void){
    LD_HL(wc821);
    RES_hl(0);
    RES_hl(2);
    RET;

}

void Function1128db(void){
    DEC_A;
    IF_Z goto asm_112947;
    DEC_A;
    IF_Z goto asm_1128e5;
    DEC_A;
    IF_Z goto asm_112913;
    RET;


asm_1128e5:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    JP_Z (mFunction1127cd);
    CALL(aFunction113482);
    LD_A_addr(wc86f);
    OR_A_A;
    IF_NZ goto asm_112901;
    LD_A(0x3);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    RES_hl(0);
    RET;


asm_112901:
    CALL(aFunction112724);
    LD_DE(wMobileSDK_PacketBuffer + 5);
    LD_A(0x1);
    LD_de_A;
    INC_DE;
    INC_DE;
    LD_B(0x1);
    CALL(aFunction111f63);
    goto asm_112941;


asm_112913:
    CALL(aFunction1127e1);
    IF_NZ goto asm_11293d;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    JP_Z (mFunction1127cd);
    LD_HL(wc880);
    CALL(aFunction112b11);
    LD_A_D;
    CP_A(0x2);
    IF_NZ goto asm_11295b;
    LD_A_E;
    CP_A(0x50);
    IF_NZ goto asm_11295b;
    LD_A(0x3);
    LD_addr_A(wc86a);
    CALL(aFunction1128d3);
    XOR_A_A;
    LD_addr_A(wc98a);
    RET;


asm_11293d:
    LD_HL(wc86b);
    DEC_hl;


asm_112941:
    LD_HL(wMobileSDK_PacketBuffer);
    JP(mFunction1127c5);


asm_112947:
    CALL(aFunction1127e1);
    IF_NZ goto asm_11293d;
    LD_HL(wc880);
    CALL(aFunction112b11);
    LD_A_D;
    CP_A(0x3);
    IF_NZ goto asm_11295b;
    LD_A_E;
    CP_A(0x54);
    RET_Z ;


asm_11295b:
    JP(mFunction1128bd);

}

void Function11295e(void){
    LD_A(0xd);
    LD_de_A;
    INC_DE;
    INC_C;
    LD_A(0xa);
    LD_de_A;
    INC_DE;
    INC_C;
    RET;

}

void Function112969(void){
    DEC_A;
    IF_Z goto asm_112970;
    DEC_A;
    IF_Z goto asm_112989;
    RET;


asm_112970:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    IF_Z goto asm_112986;
    CALL(aFunction1127e1);
    IF_Z goto asm_112986;
    LD_HL(wc86b);
    DEC_hl;
    LD_HL(wMobileSDK_PacketBuffer + 32);
    JP(mFunction1127c5);


asm_112986:
    JP(mFunction112430);


asm_112989:
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_A(0x2);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    RES_hl(0);
    RES_hl(7);
    SET_hl(5);
    RET;

}

void Function11299c(void){
    DEC_A;
    IF_Z goto asm_1129aa;
    DEC_A;
    IF_Z goto asm_1129c9;
    DEC_A;
    IF_Z goto asm_1129e7;
    DEC_A;
    JP_Z (mFunction11299c_asm_112a1d);
    RET;


asm_1129aa:
    CALL(aFunction1127e1);
    IF_NZ goto asm_1129fe;
    LD_A_addr(wc880);
    CP_A(0x2b);
    IF_NZ goto asm_112a0f;
    CALL(aFunction112724);
    LD_A_addr(wMobileSDK_PacketBuffer + 101);
    ADD_A(0xa);
    LD_E_A;
    LD_D(0);
    LD_A(0x95);
    LD_HL(wMobileSDK_PacketBuffer + 96);
    JP(mFunction111f02);


asm_1129c9:
    LD_D_A;
    CALL(aFunction1127e1);
    IF_NZ goto asm_1129fe;
    LD_A_addr(wc880);
    CP_A(0x2b);
    IF_NZ goto asm_112a0f;
    CALL(aFunction112724);
    LD_A_addr(wMobileSDK_PacketBuffer + 165);
    ADD_A(0xa);
    LD_E_A;
    LD_A(0x95);
    LD_HL(wMobileSDK_PacketBuffer + 160);
    JP(mFunction111f02);


asm_1129e7:
    CALL(aFunction1127e1);
    IF_NZ goto asm_1129fe;
    LD_A_addr(wc880);
    CP_A(0x2b);
    IF_NZ goto asm_112a0f;
    LD_A(0x4);
    LD_addr_A(wc86a);
    CALL(aFunction1128d3);
    SET_hl(7);
    RET;


asm_1129fe:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    JR_Z (mFunction112a42);
    LD_HL(wc86b);
    DEC_hl;
    LD_HL(wMobileSDK_PacketBuffer + 128);
    JP(mFunction1127c5);


asm_112a0f:
    LD_A_addr(wc86b);
    LD_addr_A(wMobileSDK_PacketBuffer + 32);
    LD_A(0x3);
    LD_addr_A(wc86b);
    JP(mFunction112430);


asm_112a1d:
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_DE(0x0002);
    LD_A_addr(wMobileSDK_PacketBuffer + 32);
    CP_A(0x1);
    IF_Z goto asm_112a2c;
    INC_DE;

asm_112a2c:

    return Function112a2c();
}

void Function112a2c(void){
    LD_HL(wc821);
    SET_hl(1);
    RES_hl(0);
    LD_HL(wc80f);
    LD_A(0x31);
    LD_hli_A;
    LD_A_E;
    LD_hli_A;
    LD_hl_D;
    LD_A(0x5);
    LD_addr_A(wc86a);
    RET;

}

void Function112a42(void){
    LD_HL(wc810);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_A(0x31);
    CALL(aFunction11225d);
    SET_hl(1);
    RES_hl(0);
    RET;

}

void Function112a56(void){
    DEC_A;
    IF_Z goto asm_112a5a;
    RET;


asm_112a5a:
    CALL(aFunction1127e1);
    IF_NZ goto asm_112a95;
    LD_HL(wc880);
    LD_A_hli;
    CP_A(0x2b);
    IF_NZ goto asm_112aa6;

asm_112a67:
    LD_A_hli;
    CP_A(0x20);
    IF_NZ goto asm_112a67;
    CALL(aFunction112aac);
    LD_A_addr(wc86e);
    LD_C_A;
    LD_A_addr(wc86f);
    LD_B_A;
    LD_A_E;
    LD_bc_A;
    INC_BC;
    LD_A_D;
    LD_bc_A;
    CALL(aFunction112aac);
    LD_HL(wc86e);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    INC_HL;
    INC_HL;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_A_C;
    LD_hli_A;
    LD_A(0x4);
    LD_addr_A(wc86a);
    JP(mFunction1128d3);


asm_112a95:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    JR_Z (mFunction112a42);
    LD_HL(wc86b);
    DEC_hl;
    LD_HL(wMobileSDK_PacketBuffer + 128);
    JP(mFunction1127c5);


asm_112aa6:
    LD_DE(0x0005);
    JP(mFunction112a2c);

}

void Function112aac(void){
    LD_A_addr(wc872);
    PUSH_AF;
    LD_A_addr(wc873);
    PUSH_AF;
    LD_A_addr(wc874);
    PUSH_AF;
    LD_BC(0);
    LD_DE(0);

asm_112abe:
    LD_A_hli;
    CP_A(0xd);
    IF_Z goto asm_112b04;
    CP_A(0x20);
    IF_Z goto asm_112b04;
    AND_A(0xf);
    LD_B_A;
    SLA_E;
    RL_D;
    RL_C;
    LD_A_E;
    LD_addr_A(wc872);
    LD_A_D;
    LD_addr_A(wc873);
    LD_A_C;
    LD_addr_A(wc874);
    SLA_E;
    RL_D;
    RL_C;
    SLA_E;
    RL_D;
    RL_C;
    LD_A_addr(wc872);
    ADD_A_E;
    LD_E_A;
    LD_A_addr(wc873);
    ADC_A_D;
    LD_D_A;
    LD_A_addr(wc874);
    ADC_A_C;
    LD_C_A;
    LD_A_B;
    ADD_A_E;
    LD_E_A;
    LD_A(0x0);
    ADC_A_D;
    LD_D_A;
    LD_A(0x0);
    ADC_A_C;
    LD_C_A;
    goto asm_112abe;


asm_112b04:
    POP_AF;
    LD_addr_A(wc874);
    POP_AF;
    LD_addr_A(wc873);
    POP_AF;
    LD_addr_A(wc872);
    RET;

}

void Function112b11(void){
    LD_A_addr(wc872);
    PUSH_AF;
    LD_A_addr(wc873);
    PUSH_AF;
    LD_A_addr(wc874);
    PUSH_AF;
    LD_BC(0x0300);
    LD_DE(wc872);
    CALL(aFunction112b60);
    CALL_NC (aFunction112b60);
    CALL_NC (aFunction112b60);
    DEC_HL;

asm_112b2d:
    LD_A_hli;
    CP_A(0xd);
    IF_Z goto asm_112b36;
    CP_A(0x20);
    IF_NZ goto asm_112b2d;


asm_112b36:
    PUSH_HL;
    LD_HL(wc872);
    LD_DE(0);
    LD_A_B;
    OR_A_A;
    IF_Z goto asm_112b49;
    DEC_A;
    IF_Z goto asm_112b4b;
    DEC_A;
    IF_Z goto asm_112b4f;
    goto asm_112b52;


asm_112b49:
    LD_A_hli;
    LD_D_A;


asm_112b4b:
    LD_A_hli;
    SWAP_A;
    LD_E_A;


asm_112b4f:
    LD_A_hli;
    OR_A_E;
    LD_E_A;


asm_112b52:
    POP_HL;
    POP_AF;
    LD_addr_A(wc874);
    POP_AF;
    LD_addr_A(wc873);
    POP_AF;
    LD_addr_A(wc872);
    RET;

}

void Function112b60(void){
    LD_A_hli;
    CP_A(0x30);
    IF_C goto asm_112b6f;
    CP_A(0x3a);
    IF_NC goto asm_112b6f;
    AND_A(0xf);
    LD_de_A;
    INC_DE;
    DEC_B;
    RET;


asm_112b6f:
    SCF;
    RET;

}

void Function112b71(void){
    DEC_A;
    IF_Z goto asm_112b75;
    RET;


asm_112b75:
    CALL(aFunction1127e1);
    IF_NZ goto asm_112ba3;
    LD_HL(wc880);
    LD_A_hli;
    CP_A(0x2b);
    IF_NZ goto asm_112bb5;

asm_112b82:
    LD_A_hli;
    CP_A(0x20);
    IF_NZ goto asm_112b82;

asm_112b87:
    LD_A_hli;
    CP_A(0x20);
    IF_NZ goto asm_112b87;
    CALL(aFunction112aac);
    LD_HL(wc86e);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_A_C;
    LD_hli_A;
    LD_A(0x4);
    LD_addr_A(wc86a);
    JP(mFunction1128d3);


asm_112ba3:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    JP_Z (mFunction112a42);
    LD_HL(wc86b);
    DEC_hl;
    LD_HL(wMobileSDK_PacketBuffer + 128);
    JP(mFunction1127c5);


asm_112bb5:
    LD_DE(0x0004);
    JP(mFunction112a2c);

}

void Function112bbb(void){
    DEC_A;
    IF_Z goto asm_112bbf;
    RET;


asm_112bbf:
    CALL(aFunction1127e1);
    IF_NZ goto asm_112bd4;
    LD_HL(wc880);
    LD_A_hli;
    CP_A(0x2b);
    IF_NZ goto asm_112be6;
    LD_A(0x4);
    LD_addr_A(wc86a);
    JP(mFunction1128d3);


asm_112bd4:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    JP_Z (mFunction112a42);
    LD_HL(wc86b);
    DEC_hl;
    LD_HL(wMobileSDK_PacketBuffer + 128);
    JP(mFunction1127c5);


asm_112be6:
    LD_DE(0x0004);
    JP(mFunction112a2c);

}

void Function112bec(void){
    DEC_A;
    IF_Z goto asm_112bf7;
    DEC_A;
    JP_Z (mFunction112bec_asm_112cdb);
    DEC_A;
    RET_NZ ;
    DEC_hl;
    RET;


asm_112bf7:
    LD_A_addr(wc880);
    CP_A(0x2d);
    IF_NZ goto asm_112c03;
    CALL(aFunction1127e1);
    IF_Z goto asm_112c0b;


asm_112c03:
    LD_A_addr(wc821);
    BIT_A(2);
    JP_Z (mFunction112bec_asm_112cef);


asm_112c0b:
    LD_HL(wc86b);
    INC_hl;
    LD_HL(wc880);
    LD_A_hli;
    CP_A(0x2b);
    JP_NZ (mFunction112d20);
    LD_B(0x7f);

asm_112c1a:
    LD_A_hli;
    DEC_B;
    CP_A(0xa);
    IF_NZ goto asm_112c1a;
    PUSH_HL;
    LD_HL(wc98f);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_B;
    LD_addr_A(wc82d);
    LD_A_hli;
    LD_H_hl;
    SUB_A_B;
    LD_L_A;
    LD_A_H;
    SBC_A(0x0);
    LD_H_A;
    IF_NC goto asm_112c56;
    CP_A(0xff);
    IF_NZ goto asm_112c56;
    LD_HL(wc991);
    LD_A_hli;
    LD_C_A;
    INC_HL;
    LD_A_B;
    SUB_A_C;
    LD_hli_A;
    LD_A_addr(wc82b);
    LD_hl_A;
    LD_HL(wc827);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_C;
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    POP_HL;
    LD_B_C;
    JP(mMobileSDK_CopyBytes);


asm_112c56:
    LD_addr_A(wc993);
    LD_A_addr(wc82b);
    LD_C_A;
    LD_addr_A(wc994);
    PUSH_HL;
    LD_A_L;
    SUB_A_C;
    LD_L_A;
    LD_A_H;
    SBC_A(0x0);
    LD_H_A;
    IF_NC goto asm_112c9f;
    CP_A(0xff);
    IF_NZ goto asm_112c9f;
    LD_A_C;
    LD_addr_A(wMobileSDK_ReceivePacketBuffer + 1);
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    SUB_A_C;
    POP_HL;
    LD_C_L;
    POP_HL;
    PUSH_AF;
    CALL(aMobileSDK_CopyBytes);
    POP_AF;
    PUSH_DE;
    LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    POP_DE;
    LD_B_C;
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 1);
    SUB_A_C;
    LD_addr_A(wc994);
    LD_HL(wc827);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wc991);
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    RET;


asm_112c9f:
    LD_addr_A(wc994);
    LD_A_L;
    LD_addr_A(wc82b);
    LD_A_H;
    LD_addr_A(wc82c);
    POP_HL;
    POP_HL;
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    SUB_A_C;
    PUSH_DE;
    LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    POP_DE;
    LD_B_C;
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc82d);
    ADD_A_C;
    LD_addr_A(wc82d);
    LD_A_addr(wc82e);
    ADC_A(0);
    LD_addr_A(wc82e);
    LD_HL(wc829);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;
    LD_HL(wc821);
    RES_hl(2);


asm_112cdb:
    LD_A_addr(wc821);
    BIT_A(2);
    IF_Z goto asm_112cea;
    LD_A(0x2);
    LD_addr_A(wc86b);
    JP(mFunction112bec_asm_112d09);


asm_112cea:
    CALL(aFunction1127f3);
    IF_Z goto asm_112d01;


asm_112cef:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    JP_Z (mFunction112a42);
    LD_HL(wc86b);
    DEC_hl;
    LD_HL(wMobileSDK_PacketBuffer + 128);
    JP(mFunction1127c5);


asm_112d01:
    LD_A(0x4);
    LD_addr_A(wc86a);
    CALL(aFunction1128d3);


asm_112d09:
    LD_A_addr(wc86e);
    LD_L_A;
    LD_A_addr(wc86f);
    OR_A_L;
    RET_Z ;
    LD_HL(wc827);
    LD_A_hli;
    LD_E_A;
    LD_D_hl;
    LD_HL(wc82d);
    LD_B(0x2);
    JP(mMobileSDK_CopyBytes);

}

void Function112d20(void){
    LD_A_addr(wc86a);
    CP_A(0x1a);
    IF_NZ goto asm_112d2d;
    LD_DE(0x0004);
    JP(mFunction112a2c);


asm_112d2d:
    LD_DE(0x0004);
    JP(mFunction112a2c);

}

void Function112d33(void){
    DEC_A;
    IF_Z goto asm_112d87;
    DEC_A;
    IF_Z goto asm_112d9f;
    DEC_A;
    JP_Z (mFunction112d33_asm_112e46);
    DEC_A;
    IF_Z goto asm_112d4d;
    DEC_A;
    JP_Z (mFunction113317);
    DEC_A;
    JP_Z (mFunction113386);
    DEC_A;
    JP(mFunction112d33_asm_112e46);


asm_112d4c:
//   //  unreferenced
    RET;


asm_112d4d:
    LD_A_addr(wc86a);
    CP_A(0x23);
    IF_Z goto asm_112d6d;
    CP_A(0x1f);
    IF_Z goto asm_112d60;
    CP_A(0x20);
    IF_Z goto asm_112d6d;
    CP_A(0x22);
    IF_NZ goto asm_112d82;


asm_112d60:
    LD_HL(wc98b);
    LD_A_hli;
    CP_A(0x1);
    IF_NZ goto asm_112d82;
    LD_A_hl;
    CP_A(0x4);
    IF_NZ goto asm_112d82;


asm_112d6d:
    LD_HL(wc86e);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    LD_HL(wc82b);
    LD_hli_A;
    LD_hl_A;
    LD_HL(wc821);
    RES_hl(2);
    LD_HL(wc86b);
    DEC_hl;
    DEC_hl;


asm_112d82:
    LD_HL(wc86b);
    DEC_hl;
    RET;


asm_112d87:
    CALL(aFunction113482);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_B(0x1);
    CALL(aFunction111f63);


asm_112d9f:
    LD_A_addr(wc821);
    BIT_A(2);
    IF_Z goto asm_112dab;
    LD_A(0x3);
    LD_hl_A;
    goto asm_112dc1;


asm_112dab:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(MOBILE_COMMAND_TRANSFER_DATA_END | 0x80);
    IF_Z goto asm_112dc1;
    LD_HL(wc86b);
    DEC_hl;
    LD_DE(0x000b);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_B(0x5);
    JP(mPacketSendBytes);


asm_112dc1:
    LD_A_addr(wc989);
    CP_A(0x2);
    IF_NC goto asm_112df2;
    CALL(aFunction112f61);
    BIT_A(2);
    RET_NZ ;
    CP_A(0x3);
    IF_Z goto asm_112e38;
    CP_A(0x1);
    IF_NZ goto asm_112df2;
    LD_A_addr(wc86a);
    CP_A(0x1f);
    IF_Z goto asm_112de1;
    CP_A(0x20);
    IF_NZ goto asm_112df2;


asm_112de1:
    LD_HL(wc98b);
    LD_A_hli;
    CP_A(0x1);
    IF_NZ goto asm_112df2;
    LD_A(0x4);
    CP_A_hl;
    IF_NZ goto asm_112df2;
    XOR_A_A;
    LD_addr_A(wc990);


asm_112df2:
    LD_A_addr(wc86e);
    LD_L_A;
    LD_A_addr(wc86f);
    OR_A_L;
    RET_Z ;
    LD_A_addr(wc86a);
    CP_A(0x13);
    IF_Z goto asm_112e21;
    CP_A(0x14);
    IF_Z goto asm_112e21;
    CP_A(0x20);
    RET_Z ;
    CP_A(0x22);
    RET_Z ;
    CP_A(0x23);
    RET_Z ;
    CP_A(0x1f);
    IF_NZ goto asm_112e21;
    LD_HL(wc98b);
    LD_A_hli;
    CP_A(0x0);
    RET_NZ ;
    LD_A(0x2);
    CP_A_hl;
    RET_NZ ;
    LD_A_addr(wc86a);


asm_112e21:
    CP_A(0x24);
    IF_NZ goto asm_112e2a;
    LD_HL(wc878);
    goto asm_112e2d;


asm_112e2a:
    LD_HL(wc827);


asm_112e2d:
    LD_A_hli;
    LD_E_A;
    LD_D_hl;
    LD_HL(wc82d);
    LD_B(0x2);
    JP(mMobileSDK_CopyBytes);


asm_112e38:
    LD_HL(wc821);
    SET_hl(1);
    RES_hl(0);
    LD_DE(wc98b);
    LD_A(0x24);
    goto asm_112e95;


asm_112e46:
    LD_A_addr(wc86a);
    CP_A(0x1f);
    IF_Z goto asm_112ea6;
    CP_A(0x20);
    IF_Z goto asm_112ea6;
    LD_A_addr(wc98a);
    CP_A(0x1);
    IF_Z goto asm_112e65;
    LD_A_addr(wc86a);
    CP_A(0x21);
    JP_Z (mFunction112d33_asm_112eea);
    CP_A(0x22);
    JP_Z (mFunction112d33_asm_112eea);


asm_112e65:
    LD_A_addr(wc990);
    OR_A_A;
    JP_Z (mFunction112d33_asm_112f3d);

asm_112e6c:
    LD_HL(wc98c);
    LD_A_hld;
    CP_A(0x3);
    IF_NZ goto asm_112e7f;
    LD_A_hl;
    OR_A_A;
    IF_Z goto asm_112e7f;
    CP_A(0x3);
    IF_NC goto asm_112e7f;
    CALL(aFunction1133fe);


asm_112e7f:
    LD_HL(wc821);
    SET_hl(1);
    RES_hl(0);
    LD_DE(wc98b);
    LD_A_addr(wc990);
    CP_A(0x1);
    LD_A(0x32);
    IF_Z goto asm_112e95;
    INC_DE;
    INC_DE;
    INC_A;


asm_112e95:
    LD_addr_A(wc80f);
    LD_HL(wc810);
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_A_de;
    LD_hl_A;
    LD_A(0x5);
    LD_addr_A(wc86a);
    RET;


asm_112ea6:
    LD_HL(wc98b);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CP_A(0x0);
    IF_NZ goto asm_112ec1;
    LD_A(0x2);
    CP_A_H;
    IF_NZ goto asm_112ec1;
    LD_A_addr(wc98d);
    LD_B_A;
    LD_A_addr(wc98e);
    OR_A_B;
    IF_NZ goto asm_112e6c;
    goto asm_112f3d;


asm_112ec1:
    LD_A(0x1);
    CP_A_L;
    IF_NZ goto asm_112e6c;
    LD_A(0x4);
    CP_A_H;
    IF_NZ goto asm_112e6c;
    LD_A_addr(wc9a5);
    OR_A_A;
    IF_NZ goto asm_112efb;
    LD_A_addr(wc86e);
    LD_L_A;
    LD_A_addr(wc86f);
    OR_A_L;
    IF_NZ goto asm_112efb;
    LD_A(0x2);
    LD_addr_A(wc86a);
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_HL(wc821);
    RES_hl(0);
    RET;


asm_112eea:
    LD_HL(wc98b);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CP_A(0x0);
    JP_NZ (mFunction112d33_asm_112e6c);
    LD_A(0x2);
    CP_A_H;
    JP_NZ (mFunction112d33_asm_112e6c);


asm_112efb:
    LD_A_addr(wc98d);
    LD_B_A;
    LD_A_addr(wc98e);
    CP_A_B;
    JP_NZ (mFunction112d33_asm_112e6c);
    OR_A_A;
    IF_Z goto asm_112f13;
    CP_A(0x1);
    JP_NZ (mFunction112d33_asm_112e6c);
    LD_A(0x1);
    LD_addr_A(wc993);


asm_112f13:
    LD_A_addr(wc86b);
    CP_A(0x7);
    IF_Z goto asm_112f3d;
    LD_HL(wc98f);
    INC_hl;
    LD_A(0xf);
    LD_addr_A(wc86a);
    LD_A(0x1);
    LD_addr_A(wc86b);
    LD_A_addr(wc86d);
    LD_addr_A(wc86e);
    XOR_A_A;
    LD_addr_A(wc989);
    LD_A(0xa3);
    LD_DE(0x0010);
    LD_HL(wc995);
    JP(mFunction111f02);


asm_112f3d:
    LD_A_addr(wc993);
    CP_A(0x1);
    IF_NZ goto asm_112f52;
    LD_A(0x2);
    LD_addr_A(wc990);
    LD_HL(wc98d);
    DEC_A;
    LD_hli_A;
    LD_hl_A;
    JP(mFunction112d33_asm_112e7f);


asm_112f52:
    LD_A(0x2);
    LD_addr_A(wc86a);
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_HL(wc821);
    RES_hl(0);
    RET;

}

void Function112f61(void){
    LD_HL(wc989);
    LD_A_hl;
    OR_A_A;
    IF_NZ goto asm_112f8a;
    INC_hl;
    LD_HL(wc880);
    LD_DE(0x0008);
    ADD_HL_DE;

asm_112f70:
    LD_A_hli;
    CP_A(0x20);
    IF_Z goto asm_112f70;
    DEC_HL;
    LD_D(0x0);
    CP_A(0x32);
    IF_Z goto asm_112f7d;
    INC_D;


asm_112f7d:
    LD_A_D;
    LD_addr_A(wc990);
    CALL(aFunction112b11);
    LD_HL(wc98b);
    LD_A_E;
    LD_hli_A;
    LD_hl_D;


asm_112f8a:
    LD_HL(wc880);
    LD_A_addr(wc82d);
    LD_B_A;
    OR_A_A;
    IF_NZ goto asm_112fa1;
    LD_HL(wc98b);
    LD_A(0x0);
    LD_hli_A;
    LD_hl_A;
    LD_A(0x1);
    LD_addr_A(wc990);
    RET;


asm_112fa1:
    CALL(aFunction112fd5);
    CALL(aFunction113008);
    CALL(aFunction113026);
    CALL(aFunction113054);
    CALL(aFunction113167);
    CALL(aFunction113180);
    CALL(aFunction113268);
    IF_C goto asm_112fc9;
    LD_A(0xd);
    CP_A_hl;
    IF_Z goto asm_112fc2;
    LD_A(0xa);
    CP_A_hl;
    IF_NZ goto asm_112fa1;


asm_112fc2:
    LD_HL(wc990);
    RES_hl(2);
    goto asm_112fce;


asm_112fc9:
    LD_HL(wc990);
    SET_hl(2);


asm_112fce:
    CALL(aFunction11306b);
    LD_A_addr(wc990);
    RET;

}

void Function112fd5(void){
    LD_DE(mUnknown_113001);
    PUSH_HL;
    CALL(aFunction113281);
    IF_NC goto asm_112fe0;
    POP_HL;
    RET;


asm_112fe0:
    POP_DE;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_B(0x0);

asm_112fe6:
    INC_B;
    LD_A_hli;
    CP_A(0xa);
    IF_NZ goto asm_112fe6;
    POP_HL;
    LD_C_B;
    LD_A_addr(wc833);
    LD_E_A;
    LD_A_addr(wc834);
    LD_D_A;
    OR_A_E;
    IF_Z goto asm_112ffe;
    CALL(aMobileSDK_CopyBytes);
    XOR_A_A;
    LD_de_A;


asm_112ffe:
    POP_HL;
    POP_BC;
    RET;

}

void Unknown_113001(void){
    //db ['"date: "', '0'];

    return Function113008();
}

void Function113008(void){
    LD_DE(mUnknown_1132a6);
    PUSH_HL;
    CALL(aFunction113273);
    IF_NC goto asm_113013;
    POP_HL;
    RET;


asm_113013:
    CALL(aFunction112b11);
    LD_HL(wc98d);
    LD_A_E;
    LD_hli_A;
    LD_hl_D;
    POP_HL;
    LD_A_D;
    OR_A_E;
    RET_Z ;
    LD_A(0x2);
    LD_addr_A(wc990);
    RET;

}

void Function113026(void){
    LD_DE(mUnknown_1132b2);
    PUSH_HL;
    CALL(aFunction113273);
    IF_NC goto asm_113031;
    POP_HL;
    RET;


asm_113031:
    POP_HL;
    PUSH_BC;
    PUSH_HL;
    PUSH_HL;
    LD_B(0x0);

asm_113037:
    INC_B;
    LD_A_hli;
    CP_A(0xa);
    IF_NZ goto asm_113037;
    POP_HL;
    LD_C_B;
    LD_DE(wMobileSDK_PacketBuffer + 18);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wMobileSDK_PacketBuffer + 18);
    LD_DE(wc9b5);
    LD_B_C;
    CALL(aMobileSDK_CopyBytes);
    XOR_A_A;
    LD_de_A;
    POP_HL;
    POP_BC;
    RET;

}

void Function113054(void){
    LD_DE(mUnknown_1132bf);
    PUSH_HL;
    CALL(aFunction113273);
    IF_NC goto asm_11305f;
    POP_HL;
    RET;


asm_11305f:
    PUSH_BC;
    LD_DE(wc9b5);
    LD_B(0x30);
    CALL(aFunction1136c1);
    POP_BC;
    POP_HL;
    RET;

}

void Function11306b(void){
    LD_HL(wc880);
    LD_A_addr(wc82d);
    LD_B_A;

    return Function113072();
}

void Function113072(void){
    CALL(aFunction113268);
    JP_NC (mFunction113089);
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    JP_NZ (mFunction1131a9);
    PUSH_HL;
    LD_HL(wc990);
    RES_hl(2);
    POP_HL;
    JR(mFunction113095);

}

void Function113089(void){
    LD_A_hl;
    CP_A(0xd);
    IF_Z goto asm_113094;
    CP_A(0xa);
    JR_Z (mFunction113095);
    JR(mFunction113072);


asm_113094:
    INC_HL;

    return Function113095();
}

void Function113095(void){
    INC_HL;
    PUSH_BC;
    LD_A_addr(wc872);
    LD_B_A;
    LD_A_addr(wc873);
    OR_A_B;
    POP_BC;
    IF_Z goto asm_1130b3;
    LD_A_addr(wc86a);
    CP_A(0x23);
    IF_Z goto asm_1130b3;
    CP_A(0x20);
    IF_Z goto asm_1130b3;
    CP_A(0x22);
    IF_Z goto asm_1130b3;
    goto asm_1130d6;


asm_1130b3:
    XOR_A_A;
    LD_HL(wc86e);
    LD_hli_A;
    LD_hl_A;
    LD_HL(wc821);
    RES_hl(2);
    LD_A_addr(wc86a);
    CP_A(0x13);
    IF_Z goto asm_1130c8;
    CP_A(0x14);
    RET_NZ ;


asm_1130c8:
    LD_A(0x6);
    LD_addr_A(wc86b);
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    RET_Z ;
    JP(mFunction112430);


asm_1130d6:
    LD_A_addr(wc82b);
    LD_C_A;
    DEC_B;
    DEC_B;
    LD_A_B;
    LD_addr_A(wc82d);
    IF_Z goto asm_11310d;
    LD_A_addr(wc873);
    LD_D_A;
    LD_A_addr(wc872);
    LD_E_A;
    DEC_DE;
    DEC_DE;
    XOR_A_A;
    OR_A_D;
    IF_NZ goto asm_1130f5;
    LD_A_E;
    CP_A_B;
    JP_C (mFunction113206);


asm_1130f5:
    LD_A_E;
    SUB_A_B;
    LD_addr_A(wc82b);
    LD_A_D;
    SBC_A(0x0);
    LD_addr_A(wc82c);
    LD_A_addr(wc874);
    LD_E_A;
    LD_A_addr(wc875);
    LD_D_A;
    INC_DE;
    INC_DE;
    CALL(aMobileSDK_CopyBytes);


asm_11310d:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    CP_A(0x9f);
    IF_Z goto asm_113150;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    OR_A_A;
    IF_Z goto asm_113150;
    LD_L_C;
    SUB_A_C;
    LD_C_A;
    LD_A_L;
    LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
    ADD_HL_BC;
    LD_B_A;
    PUSH_DE;
    LD_A_addr(wc82b);
    LD_E_A;
    LD_A_addr(wc82c);
    LD_D_A;
    XOR_A_A;
    OR_A_D;
    IF_NZ goto asm_113135;
    LD_A_E;
    CP_A_B;
    JP_C (mFunction113245);


asm_113135:
    POP_DE;
    PUSH_HL;
    LD_HL(wc82d);
    LD_A_hl;
    ADD_A_B;
    LD_hli_A;
    LD_A_hl;
    ADC_A(0);
    LD_hl_A;
    LD_C_B;
    POP_HL;
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc82b);
    LD_A_hl;
    SUB_A_C;
    LD_hli_A;
    LD_A_hl;
    SBC_A(0x0);
    LD_hl_A;


asm_113150:
    LD_HL(wc829);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;
    LD_HL(wc821);
    RES_hl(2);
    LD_A(0x1);
    LD_addr_A(wc86b);
    LD_A(0x2);
    LD_addr_A(wc989);
    RET;

}

void Function113167(void){
    LD_DE(mUnknown_1132ff);
    PUSH_HL;
    CALL(aFunction113273);
    IF_NC goto asm_113172;
    POP_HL;
    RET;


asm_113172:
    POP_DE;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_B(0x0);

asm_113178:
    INC_B;
    LD_A_hli;
    CP_A(0xa);
    IF_NZ goto asm_113178;
    JR(mFunction113197);

}

void Function113180(void){
    LD_DE(mUnknown_11330c);
    PUSH_HL;
    CALL(aFunction113273);
    IF_NC goto asm_11318b;
    POP_HL;
    RET;


asm_11318b:
    POP_DE;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_B(0x0);

asm_113191:
    INC_B;
    LD_A_hli;
    CP_A(0xa);
    IF_NZ goto asm_113191;

    return Function113197();
}

void Function113197(void){
    POP_HL;
    LD_C_B;
    LD_DE(wMobileSDK_PacketBuffer + 16);
    LD_A_B;
    LD_de_A;
    INC_DE;
    DEC_B;
    DEC_B;
    CALL(aMobileSDK_CopyBytes);
    XOR_A_A;
    LD_de_A;
    POP_HL;
    POP_BC;
    RET;

}

void Function1131a9(void){
    LD_HL(wc979);
    LD_DE(wc880);
    LD_B(0x0);
    LD_C_B;
    LD_A_hl;
    CP_A(0xa);
    IF_Z goto asm_1131c4;

asm_1131b7:
    LD_A_hld;
    INC_B;
    CP_A(0xa);
    IF_NZ goto asm_1131b7;
    INC_HL;
    INC_HL;
    DEC_B;
    LD_C_B;
    CALL(aMobileSDK_CopyBytes);


asm_1131c4:
    LD_A_addr(wc82b);
    LD_B_A;
    ADD_A_C;
    LD_C_A;
    PUSH_BC;
    LD_A(0xff);
    SUB_A_B;
    LD_C_A;
    LD_B(0);
    LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
    ADD_HL_BC;
    POP_BC;
    CALL(aMobileSDK_CopyBytes);
    LD_A_C;
    LD_addr_A(wc82d);
    LD_A(0xfa);
    SUB_A_C;
    LD_addr_A(wc82b);
    LD_HL(wc829);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;
    LD_L_E;
    LD_H_D;
    LD_DE(wc97a);

asm_1131ef:
    XOR_A_A;
    LD_hli_A;
    LD_A_L;
    CP_A_E;
    IF_NZ goto asm_1131ef;
    LD_A_D;
    CP_A_H;
    IF_NZ goto asm_1131ef;
    LD_HL(wc821);
    RES_hl(2);
    LD_HL(wc86b);
    DEC_hl;
    DEC_hl;
    LD_A(0x4);
    RET;

}

void Function113206(void){
    LD_A_B;
    SUB_A_E;
    LD_addr_A(wc991);
    LD_A_addr(wc821);
    BIT_A(2);
    LD_A_C;
    IF_NZ goto asm_113214;
    XOR_A_A;


asm_113214:
    LD_addr_A(wc992);
    LD_B_E;
    LD_C_E;
    LD_A_addr(wc874);
    LD_E_A;
    LD_A_addr(wc875);
    LD_D_A;
    INC_DE;
    INC_DE;
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc991);
    LD_addr_A(wc993);
    LD_B_A;
    LD_DE(wc880);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc82d);
    LD_A_C;
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    LD_HL(wc821);
    SET_hl(2);
    LD_A(0x3);
    LD_addr_A(wc86b);
    RET;

}

void Function113245(void){
    LD_A_B;
    SUB_A_E;
    LD_addr_A(wc992);
    LD_addr_A(wc82b);
    LD_B_E;
    LD_C_E;
    POP_DE;
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc82d);
    LD_A_C;
    ADD_A_hl;
    LD_hli_A;
    LD_A(0x0);
    ADC_A_hl;
    LD_hl_A;
    LD_HL(wc821);
    SET_hl(2);
    LD_A(0x3);
    LD_addr_A(wc86b);
    RET;

}

void Function113268(void){

asm_113268:
    DEC_B;
    LD_A_hli;
    CP_A(0xa);
    RET_Z ;
    XOR_A_A;
    OR_A_B;
    IF_NZ goto asm_113268;
    SCF;
    RET;

}

void Function113273(void){
    LD_C(0x0);

asm_113275:
    LD_A_de;
    INC_DE;
    OR_A_A;
    RET_Z ;
    XOR_A_hl;
    INC_HL;
    OR_A_C;
    LD_C_A;
    IF_Z goto asm_113275;
    SCF;
    RET;

}

void Function113281(void){
    LD_C(0x0);
    PUSH_HL;
    LD_L_E;
    LD_H_D;
    POP_DE;

asm_113287:
    LD_A_de;
    INC_DE;
    CALL(aFunction11329d);
    XOR_A_hl;
    INC_HL;
    OR_A_C;
    LD_C_A;
    XOR_A_A;
    CP_A_hl;
    IF_Z goto asm_113298;
    CP_A_C;
    IF_Z goto asm_113287;
    SCF;


asm_113298:
    PUSH_HL;
    LD_L_E;
    LD_H_D;
    POP_DE;
    RET;

}

void Function11329d(void){
    CP_A(0x41);
    RET_C ;
    CP_A(0x5b);
    RET_NC ;
    OR_A(0x20);
    RET;

}

void Unknown_1132a6(void){
    //db ['"Gb-Status: "', '0'];
    return Unknown_1132b2();
}

void Unknown_1132b2(void){
    //db ['"Gb-Auth-ID: "', '0'];
    return Unknown_1132bf();
}

void Unknown_1132bf(void){
    //db ['"WWW-Authenticate: GB00 name="', '0x22', '0'];
    return Unknown_1132dd();
}

void Unknown_1132dd(void){
    //db ['"Content-Type: application/x-cgb"', '0xd', '"\\n"', '0'];
    return Unknown_1132ff();
}

void Unknown_1132ff(void){
    //db ['"URI-header: "', '0'];
    return Unknown_11330c();
}

void Unknown_11330c(void){
    //db ['"Location: "', '0'];

    return Function113317();
}

void Function113317(void){
    LD_A(0x1);
    LD_addr_A(wc86b);
    LD_DE(wMobileSDK_PacketBuffer + 18);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    CALL(aFunction1126b0);
    LD_HL(mUnknown_1132dd);
    LD_A_addr(wc9a5);
    OR_A_A;
    CALL_NZ (aMobileSDK_CopyString);
    LD_A_addr(wc86a);
    CP_A(0x22);
    IF_NZ goto asm_113344;
    LD_A_addr(wc98a);
    CP_A(0x2);
    IF_NZ goto asm_113351;
    goto asm_113348;


asm_113344:
    CP_A(0x24);
    IF_NZ goto asm_113351;


asm_113348:
    LD_A_addr(wc9a5);
    OR_A_A;
    IF_Z goto asm_11336a;
    CALL(aFunction1133de);


asm_113351:
    LD_HL(wc9b5);
    CALL(aMobileSDK_CopyString);
    CALL(aFunction1126b6);
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 17);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(0x95);
    LD_HL(wMobileSDK_PacketBuffer + 12);
    JP(mFunction111f02);


asm_11336a:
    LD_HL(mUnknown_113372);
    CALL(aMobileSDK_CopyString);
    goto asm_113351;

    return Unknown_113372();
}

void Unknown_113372(void){
    //db ['"Content-Length: 0"', '0xd', '"\\n"', '0'];

    return Function113386();
}

void Function113386(void){
    CALL(aFunction113482);
    LD_A(0x1);
    LD_addr_A(wc86b);
    LD_DE(wMobileSDK_PacketBuffer);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_B(0x1);
    CALL(aFunction111f63);
    LD_DE(wMobileSDK_PacketBuffer + 12);
    LD_HL(mMobilePacket_TransferData);
    LD_B(0x6);
    CALL(aMobileSDK_CopyBytes);
    LD_A_addr(wc86d);
    CP_A(0x3);
    JP_NZ (mFunction113317);
    LD_DE(wMobileSDK_PacketBuffer + 18);
    LD_A_addr(wc86c);
    LD_de_A;
    INC_DE;
    LD_BC(0x0001);
    CALL(aFunction1126b0);
    LD_A_addr(wc994);
    OR_A_A;
    CALL_NZ (aFunction1133de);
    CALL(aFunction1126b6);
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 17);
    LD_B_C;
    CALL(aFunction111f63);
    LD_A(0x95);
    LD_HL(wMobileSDK_PacketBuffer + 12);
    JP(mFunction111f02);

}

void Function1133de(void){
    CALL(aFunction1126e6);
    XOR_A_A;
    LD_addr_A(wc86b);
    LD_A_addr(wc9aa);
    LD_addr_A(wc87c);
    LD_A_addr(wc9ab);
    LD_addr_A(wc87d);
    LD_A_addr(wc9ac);
    LD_addr_A(wc87e);
    LD_A_addr(wc9ad);
    LD_addr_A(wc87f);
    RET;

}

void Function1133fe(void){
    LD_HL(wMobileSDK_PacketBuffer + 17);
    LD_A_hli;
    CP_A(0x68);
    IF_NZ goto asm_113432;
    LD_A_hli;
    CP_A(0x74);
    IF_NZ goto asm_113432;
    LD_A_hli;
    CP_A(0x74);
    IF_NZ goto asm_113432;
    LD_A_hli;
    CP_A(0x70);
    IF_NZ goto asm_113432;
    LD_A_hli;
    CP_A(0x3a);
    IF_NZ goto asm_113432;
    LD_A_hli;
    CP_A(0x2f);
    IF_NZ goto asm_113432;
    LD_A_hli;
    CP_A(0x2f);
    IF_NZ goto asm_113432;
    LD_HL(wMobileSDK_PacketBuffer + 16);
    LD_DE(wc880);
    LD_A_hli;
    LD_B_A;
    CALL(aMobileSDK_CopyBytes);
    XOR_A_A;
    LD_de_A;
    RET;


asm_113432:
    LD_A_addr(wMobileSDK_PacketBuffer + 17);
    CP_A(0x2f);
    IF_Z goto asm_113460;
    LD_DE(wc880);
    LD_HL(wc9b5);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    INC_HL;
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aMobileSDK_CopyString);
    LD_L_E;
    LD_H_D;

asm_11344c:
    LD_A_hld;
    CP_A(0x2f);
    IF_NZ goto asm_11344c;
    INC_HL;
    INC_HL;
    LD_E_L;
    LD_D_H;

asm_113455:
    LD_HL(wMobileSDK_PacketBuffer + 16);
    LD_A_hli;
    LD_B_A;
    CALL(aMobileSDK_CopyBytes);
    XOR_A_A;
    LD_de_A;
    RET;


asm_113460:
    LD_DE(wc880);
    LD_HL(wc9b5);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    INC_HL;
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hl;
    CP_A(0x2f);
    IF_Z goto asm_113478;
    LD_B(0x7);
    CALL(aMobileSDK_CopyBytes);


asm_113478:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    CP_A(0x2f);
    IF_NZ goto asm_113478;
    DEC_DE;
    goto asm_113455;

    return Function113482();
}

void Function113482(void){
    LD_HL(wc87f);
    LD_A_hld;
    LD_B_A;
    LD_A_hld;
    LD_C_A;
    LD_A_B;
    OR_A_C;
    RET_Z ;
    POP_HL;
    LD_HL(rSC);
    ADD_HL_BC;
    IF_C goto asm_113496;
    XOR_A_A;
    LD_L_A;
    LD_H_A;


asm_113496:
    LD_E_L;
    LD_D_H;
    LD_HL(wc87f);
    LD_A_D;
    LD_hld_A;
    LD_A_E;
    LD_hld_A;
    IF_NC goto asm_1134a3;
    LD_C(0xfe);


asm_1134a3:
    LD_A_hld;
    LD_L_hl;
    LD_H_A;
    LD_A_C;
    INC_A;
    LD_addr_A(wMobileSDK_PacketBuffer + 5);
    LD_DE(wMobileSDK_PacketBuffer + 7);
    LD_B_C;
    CALL(aMobileSDK_CopyBytes);
    LD_A_L;
    LD_addr_A(wc87c);
    LD_A_H;
    LD_addr_A(wc87d);
    LD_B_C;
    INC_B;
    CALL(aFunction111f63);
    LD_HL(wc86b);
    DEC_hl;
    LD_HL(wMobileSDK_PacketBuffer);
    LD_A(0x95);
    JP(mFunction111f02);

}

void Function1134cb(void){
    DEC_A;
    IF_Z goto asm_1134d9;
    DEC_A;
    IF_Z goto asm_1134f4;
    DEC_A;
    IF_Z goto asm_1134fc;
    DEC_A;
    IF_Z goto asm_11350e;
    DEC_hl;
    RET;


asm_1134d9:
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 4);
    CP_A(0x0);
    IF_Z goto asm_1134f0;
    CP_A(0xff);
    IF_Z goto asm_1134f0;
    LD_A_addr(wc985);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    RES_hl(0);
    RET;


asm_1134f0:
    INC_hl;
    INC_hl;
    goto asm_1134fc;


asm_1134f4:
    LD_A(MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
    LD_HL(mMobilePacket_TelephoneStatus);
    JP(mPacketSendEmptyBody);


asm_1134fc:
    LD_HL(wc86e);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer + 6);
    CP_A(0xf0);
    IF_C goto asm_11350b;
    SET_hl(7);


asm_11350b:
    JP(mFunction112269);


asm_11350e:
    LD_A_addr(wc86a);
    CP_A(0x1e);
    JP_NZ (mFunction112251);
    JP(mFunction1116a0);

}

void Function113519(void){
    DEC_A;
    IF_Z goto asm_113527;
    DEC_A;
    IF_Z goto asm_11352d;
    DEC_A;
    IF_Z goto asm_11353c;
    DEC_A;
    IF_Z goto asm_11353f;
    DEC_hl;
    RET;


asm_113527:
    LD_HL(mMobilePacket_ReadConfigurationDataPart1);
    JP(mFunction11236b);


asm_11352d:
    LD_HL(wc829);
    LD_A(0xe0);
    LD_hli_A;
    LD_A(0xc8);
    LD_hli_A;
    LD_HL(mMobilePacket_ReadConfigurationDataPart2);
    JP(mFunction11236b);


asm_11353c:
    JP(mFunction112269);


asm_11353f:
    LD_HL(wc880);
    LD_A_hli;
    CP_A(0x4d);
    IF_NZ goto asm_113586;
    LD_A_hld;
    CP_A(0x41);
    IF_NZ goto asm_113586;
    LD_B(0xbe);
    LD_DE(0);

asm_113551:
    LD_A_hli;
    ADD_A_E;
    LD_E_A;
    LD_A(0x0);
    ADC_A_D;
    LD_D_A;
    DEC_B;
    IF_NZ goto asm_113551;
    LD_A_hli;
    CP_A_D;
    IF_NZ goto asm_11358a;
    LD_A_hl;
    CP_A_E;
    IF_NZ goto asm_11358a;
    LD_A_addr(wc86e);
    LD_E_A;
    LD_A_addr(wc86f);
    LD_D_A;
    LD_HL(mFunction113519_asm_11357e);
    PUSH_HL;
    LD_A_addr(wc86a);
    CP_A(0x25);
    JR_Z (mFunction1135ba);
    CP_A(0x26);
    JR_Z (mFunction11359d);
    CP_A(0x27);
    JR_Z (mFunction1135ad);

asm_11357e:
    LD_A(0x1);
    LD_addr_A(wc835);
    JP(mFunction1116a0);


asm_113586:
    LD_A(0x25);
    goto asm_11358c;


asm_11358a:
    LD_A(0x14);


asm_11358c:
    CALL(aFunction11225d);
    JP(mFunction1116a4);

}

void Function113592(void){
    PUSH_DE;
    LD_L_E;
    LD_H_D;
    XOR_A_A;
    LD_hl_A;
    INC_DE;
    CALL(aMobileSDK_CopyBytes);
    POP_DE;
    RET;

}

void Function11359d(void){
    LD_B(0x20);
    CALL(aFunction113592);
    LD_A(0x21);
    LD_HL(wc88c);
    CALL(aMobileSDK_CopyStringLen);
    XOR_A_A;
    LD_de_A;
    RET;

}

void Function1135ad(void){
    LD_B(0x1e);
    CALL(aFunction113592);
    LD_A(0x1f);
    LD_HL(wc8ac);
    JP(mMobileSDK_CopyStringLen);

}

void Function1135ba(void){
    LD_B(0x65);
    CALL(aFunction113592);
    LD_HL(wc8f6);
    CALL(aFunction1135eb);
    LD_A(0x11);
    LD_HL(wc8fe);
    CALL(aMobileSDK_CopyStringLen);
    INC_DE;
    LD_HL(wc90e);
    CALL(aFunction1135eb);
    LD_A(0x11);
    LD_HL(wc916);
    CALL(aMobileSDK_CopyStringLen);
    INC_DE;
    LD_HL(wc926);
    CALL(aFunction1135eb);
    LD_A(0x11);
    LD_HL(wc92e);
    JP(mMobileSDK_CopyStringLen);

}

void Function1135eb(void){
    LD_B(0x8);

asm_1135ed:
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    CP_A(0xf);
    IF_Z goto asm_11361c;
    OR_A(0x30);
    CP_A(0x3a);
    CALL_Z (aFunction113620);
    CP_A(0x3b);
    CALL_Z (aFunction113623);
    LD_de_A;
    INC_DE;
    LD_A_hli;
    AND_A(0xf);
    CP_A(0xf);
    IF_Z goto asm_11361c;
    OR_A(0x30);
    CP_A(0x3a);
    CALL_Z (aFunction113620);
    CP_A(0x3b);
    CALL_Z (aFunction113623);
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto asm_1135ed;


asm_11361c:
    XOR_A_A;
    LD_de_A;
    INC_DE;
    RET;

}

void Function113620(void){
    LD_A(0x23);
    RET;

}

void Function113623(void){
    LD_A(0x2a);
    RET;

}

void Function113626(void){
    DEC_A;
    IF_Z goto asm_113634;
    DEC_A;
    IF_Z goto asm_113639;
    DEC_A;
    IF_Z goto asm_11366c;
    DEC_A;
    IF_Z goto asm_11366f;
    DEC_hl;
    RET;


asm_113634:
    LD_B(0x9a);
    JP(mFunction11234b);


asm_113639:
    LD_A_addr(wc882);
    OR_A_A;
    IF_NZ goto asm_113642;
    INC_hl;
    goto asm_11366c;


asm_113642:
    LD_DE(wMobileSDK_PacketBuffer + 5);
    LD_C_A;
    INC_A;
    LD_de_A;
    INC_DE;
    LD_A(0x80);
    LD_de_A;
    INC_DE;
    LD_HL(wc880);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_B_C;
    CALL(aMobileSDK_CopyBytes);
    LD_B_C;
    INC_B;
    CALL(aFunction111f63);
    LD_A_addr(wMobileSDK_PacketBuffer + 5);
    ADD_A(0xa);
    LD_E_A;
    LD_D(0);
    LD_A(0x9a);
    LD_HL(wMobileSDK_PacketBuffer);
    JP(mFunction111f02);


asm_11366c:
    JP(mFunction112269);


asm_11366f:
    JP(mFunction1116a0);

}

void Function113672(void){
    DEC_A;
    IF_Z goto asm_113680;
    DEC_A;
    IF_Z goto asm_113686;
    DEC_A;
    IF_Z goto asm_1136bb;
    DEC_A;
    IF_Z goto asm_1136be;
    DEC_hl;
    RET;


asm_113680:
    LD_HL(wMobileSDK_PacketBuffer);
    JP(mFunction11236b);


asm_113686:
    LD_A_addr(wc882);
    OR_A_A;
    IF_Z goto asm_113693;
    CP_A(0x81);
    IF_NC goto asm_113693;
    INC_hl;
    goto asm_1136bb;


asm_113693:
    LD_HL(wMobileSDK_PacketBuffer + 7);
    SUB_A(0x80);
    LD_hld_A;
    LD_A(0x80);
    LD_hl_A;
    LD_DE(wMobileSDK_PacketBuffer + 8);
    LD_B(0x2);
    CALL(aFunction111f63);
    LD_HL(wc880);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(0x0080);
    ADD_HL_DE;
    LD_E_H;
    LD_A_L;
    LD_HL(wc829);
    LD_hli_A;
    LD_hl_E;
    LD_HL(wMobileSDK_PacketBuffer);
    JP(mFunction11236b);


asm_1136bb:
    JP(mFunction112269);


asm_1136be:
    JP(mFunction1116a0);

}

void Function1136c1(void){
    XOR_A_A;
    LD_addr_A(wMobileSDK_PacketBuffer + 225);
    LD_A_L;
    LD_addr_A(wMobileSDK_PacketBuffer + 192);
    LD_A_H;
    LD_addr_A(wMobileSDK_PacketBuffer + 193);
    LD_HL(wMobileSDK_PacketBuffer + 194);
    LD_A_E;
    LD_hli_A;
    LD_A_D;
    LD_hli_A;
    LD_A_B;
    LD_hli_A;
    LD_HL(wMobileSDK_PacketBuffer + 192);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wMobileSDK_PacketBuffer + 32);
    LD_B(0x30);
    LD_C_B;
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wc97f);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

asm_1136eb:
    LD_A_hli;
    OR_A_A;
    IF_NZ goto asm_1136eb;
    CALL(aMobileSDK_CopyString);
    LD_A(0x37);
    CP_A_C;
    INC_A;
    IF_NC goto asm_1136ff;
    LD_A(0x2);
    LD_addr_A(wMobileSDK_PacketBuffer + 225);
    LD_A(0x78);


asm_1136ff:
    SUB_A_C;
    LD_B_A;
    LD_A(0x80);
    LD_de_A;
    INC_DE;
    XOR_A_A;

asm_113706:
    DEC_B;
    IF_Z goto asm_11370d;
    LD_de_A;
    INC_DE;
    goto asm_113706;


asm_11370d:
    OR_A_A;
    SLA_C;
    RL_B;
    SLA_C;
    RL_B;
    SLA_C;
    RL_B;
    LD_A_C;
    LD_de_A;
    INC_DE;
    LD_A_B;
    LD_de_A;
    INC_DE;
    LD_L_E;
    LD_H_D;
    LD_B(0x6);
    XOR_A_A;

asm_113725:
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_113725;
    LD_DE(wMobileSDK_PacketBuffer + 160);
    LD_HL(mUnknown_113b7e);
    LD_B(0x10);
    CALL(aMobileSDK_CopyBytes);


asm_113734:
    LD_HL(wMobileSDK_PacketBuffer + 197);
    LD_A(LOW(aMD5_K_Table));
    LD_hli_A;
    LD_A(HIGH(aMD5_K_Table));
    LD_hl_A;
    LD_HL(wMobileSDK_PacketBuffer + 199);
    LD_A(LOW(aUnknown_113a70));
    LD_hli_A;
    LD_A(HIGH(aUnknown_113a70));
    LD_hl_A;
    LD_HL(wMobileSDK_PacketBuffer + 160);
    LD_DE(wMobileSDK_PacketBuffer + 209);
    LD_B(0x10);
    CALL(aMobileSDK_CopyBytes);


asm_113751:
    LD_HL(wMobileSDK_PacketBuffer + 199);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hli;
    LD_C_A;
    PUSH_HL;
    CALL(aFunction113909);
    LD_HL(wMobileSDK_PacketBuffer + 176);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a32);
    POP_HL;
    LD_A_hli;
    LD_D_hl;
    INC_HL;
    LD_E_A;
    PUSH_HL;
    LD_A_addr(wMobileSDK_PacketBuffer + 225);
    BIT_A(0);
    IF_Z goto asm_11377c;
    LD_HL(0x0040);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;


asm_11377c:
    LD_HL(wMobileSDK_PacketBuffer + 32);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a32);
    LD_HL(wMobileSDK_PacketBuffer + 197);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a32);
    POP_HL;
    LD_A_hli;
    LD_B_A;
    LD_A_L;
    LD_addr_A(wMobileSDK_PacketBuffer + 199);
    LD_A_H;
    LD_addr_A(wMobileSDK_PacketBuffer + 200);
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a40);
    LD_HL(wMobileSDK_PacketBuffer + 178);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a32);
    LD_HL(wMobileSDK_PacketBuffer + 176);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    LD_B(0x4);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wMobileSDK_PacketBuffer + 197);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }
    LD_A_H;
    LD_addr_A(wMobileSDK_PacketBuffer + 198);
    LD_A_L;
    LD_addr_A(wMobileSDK_PacketBuffer + 197);
    CP_A(0x8e);  // LOW(MD5_K_Table + $100) ???
    JP_NZ (mFunction1136c1_asm_113751);
    LD_DE(wMobileSDK_PacketBuffer + 209);
    LD_HL(wMobileSDK_PacketBuffer + 160);
    CALL(aFunction113a32);
    LD_DE(wMobileSDK_PacketBuffer + 213);
    CALL(aFunction113a32);
    LD_DE(wMobileSDK_PacketBuffer + 217);
    CALL(aFunction113a32);
    LD_DE(wMobileSDK_PacketBuffer + 221);
    CALL(aFunction113a32);
    LD_HL(wMobileSDK_PacketBuffer + 225);
    BIT_hl(1);
    IF_Z goto asm_1137fc;
    DEC_hl;
    JP(mFunction1136c1_asm_113734);


asm_1137fc:
    LD_HL(wMobileSDK_PacketBuffer + 32);
    LD_DE(wMobileSDK_PacketBuffer + 80);
    LD_BC(0x0030);
    CALL(aFunction113d66);
    LD_HL(wMobileSDK_PacketBuffer + 194);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(mUnknown_113a55);
    CALL(aMobileSDK_CopyString);
    LD_HL(wMobileSDK_PacketBuffer + 80);
    LD_BC(0x0020);
    CALL(aFunction113c8e);
    LD_A_L;
    LD_addr_A(wMobileSDK_PacketBuffer + 194);
    LD_A_H;
    LD_addr_A(wMobileSDK_PacketBuffer + 195);
    LD_B(0x12);
    LD_HL(wMobileSDK_PacketBuffer + 80);
    LD_DE(wMobileSDK_PacketBuffer + 32);

asm_11382d:
    LD_A(0x40);
    AND_A_hl;
    RLCA;
    LD_C_A;
    LD_A_hli;
    BIT_A(4);
    IF_Z goto asm_113839;
    SET_C(6);


asm_113839:
    BIT_A(2);
    IF_Z goto asm_11383f;
    SET_C(5);


asm_11383f:
    BIT_A(0);
    IF_Z goto asm_113845;
    SET_C(4);


asm_113845:
    LD_A_hli;
    BIT_A(6);
    IF_Z goto asm_11384c;
    SET_C(3);


asm_11384c:
    BIT_A(4);
    IF_Z goto asm_113852;
    SET_C(2);


asm_113852:
    BIT_A(2);
    IF_Z goto asm_113858;
    SET_C(1);


asm_113858:
    BIT_A(0);
    IF_Z goto asm_11385e;
    SET_C(0);


asm_11385e:
    LD_A_C;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto asm_11382d;
    LD_B(0x12);
    LD_HL(wMobileSDK_PacketBuffer + 115);
    LD_DE(wMobileSDK_PacketBuffer + 67);

asm_11386c:
    LD_A(0x2);
    AND_A_hl;
    RRCA;
    LD_C_A;
    LD_A_hld;
    BIT_A(3);
    IF_Z goto asm_113878;
    SET_C(1);


asm_113878:
    BIT_A(5);
    IF_Z goto asm_11387e;
    SET_C(2);


asm_11387e:
    BIT_A(7);
    IF_Z goto asm_113884;
    SET_C(3);


asm_113884:
    LD_A_hld;
    BIT_A(1);
    IF_Z goto asm_11388b;
    SET_C(4);


asm_11388b:
    BIT_A(3);
    IF_Z goto asm_113891;
    SET_C(5);


asm_113891:
    BIT_A(5);
    IF_Z goto asm_113897;
    SET_C(6);


asm_113897:
    BIT_A(7);
    IF_Z goto asm_11389d;
    SET_C(7);


asm_11389d:
    LD_A_C;
    LD_de_A;
    DEC_DE;
    DEC_B;
    IF_NZ goto asm_11386c;
    LD_B(0x10);
    LD_DE(wMobileSDK_PacketBuffer + 80);
    LD_HL(wMobileSDK_PacketBuffer + 160);
    CALL(aMobileSDK_CopyBytes);
    LD_BC(0x0010);
    LD_HL(wc97f);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aMobileSDK_CopyString);
    LD_A(0x24);
    SUB_A_C;
    LD_B_A;
    LD_L_E;
    LD_H_D;
    LD_A(0xff);

asm_1138c2:
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_1138c2;
    XOR_A_A;
    LD_hl_A;
    LD_B(0x24);
    LD_HL(wMobileSDK_PacketBuffer + 32);
    LD_DE(wMobileSDK_PacketBuffer + 80);

asm_1138d0:
    LD_A_de;
    INC_DE;
    XOR_A_hl;
    LD_C(0x0);
    BIT_A(0);
    IF_Z goto asm_1138db;
    SET_C(3);


asm_1138db:
    BIT_A(3);
    IF_Z goto asm_1138e1;
    SET_C(6);


asm_1138e1:
    BIT_A(6);
    IF_Z goto asm_1138e7;
    SET_C(0);


asm_1138e7:
    AND_A(0xb6);
    OR_A_C;
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_1138d0;
    LD_HL(wMobileSDK_PacketBuffer + 194);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 32);
    LD_BC(0x0024);
    CALL(aFunction113c8e);
    LD_A(0x22);
    LD_hli_A;
    LD_A(0xd);
    LD_hli_A;
    LD_A(0xa);
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    RET;

}

void Function113909(void){
    CALL(aFunction11391e);
    LD_A_C;
    AND_A(0xf0);
    SWAP_A;
    OR_A_A;
    JR_Z (mFunction11392f);
    DEC_A;
    JR_Z (mFunction113973);
    DEC_A;
    JP_Z (mFunction1139b7);
    JP(mFunction1139de);

}

void Function11391e(void){
    AND_A(0xf);
    LD_E_A;
    LD_D(0);
    LD_HL(mUnknown_113b70);
    ADD_HL_DE;
    LD_DE(wMobileSDK_PacketBuffer + 176);
    LD_B(0x8);
    JP(mMobileSDK_CopyBytes);

}

void Function11392f(void){
    LD_HL(wMobileSDK_PacketBuffer + 178);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wMobileSDK_PacketBuffer + 184);
    LD_B(0x4);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wMobileSDK_PacketBuffer + 180);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a0b);
    LD_HL(wMobileSDK_PacketBuffer + 178);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wMobileSDK_PacketBuffer + 188);
    LD_B(0x4);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wMobileSDK_PacketBuffer + 188);
    CALL(aFunction113a1f);
    LD_HL(wMobileSDK_PacketBuffer + 182);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 188);
    CALL(aFunction113a0b);
    LD_HL(wMobileSDK_PacketBuffer + 184);
    LD_DE(wMobileSDK_PacketBuffer + 188);
    CALL(aFunction113a15);
    RET;

}

void Function113973(void){
    LD_HL(wMobileSDK_PacketBuffer + 178);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wMobileSDK_PacketBuffer + 184);
    LD_B(0x4);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wMobileSDK_PacketBuffer + 182);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a0b);
    LD_HL(wMobileSDK_PacketBuffer + 182);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wMobileSDK_PacketBuffer + 188);
    LD_B(0x4);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wMobileSDK_PacketBuffer + 188);
    CALL(aFunction113a1f);
    LD_HL(wMobileSDK_PacketBuffer + 180);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 188);
    CALL(aFunction113a0b);
    LD_HL(wMobileSDK_PacketBuffer + 184);
    LD_DE(wMobileSDK_PacketBuffer + 188);
    CALL(aFunction113a15);
    RET;

}

void Function1139b7(void){
    LD_HL(wMobileSDK_PacketBuffer + 178);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wMobileSDK_PacketBuffer + 184);
    LD_B(0x4);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wMobileSDK_PacketBuffer + 180);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a28);
    LD_HL(wMobileSDK_PacketBuffer + 182);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a28);
    RET;

}

void Function1139de(void){
    LD_HL(wMobileSDK_PacketBuffer + 182);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wMobileSDK_PacketBuffer + 184);
    LD_B(0x4);
    CALL(aMobileSDK_CopyBytes);
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a1f);
    LD_HL(wMobileSDK_PacketBuffer + 178);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a15);
    LD_HL(wMobileSDK_PacketBuffer + 180);
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    LD_HL(wMobileSDK_PacketBuffer + 184);
    CALL(aFunction113a28);
    RET;

}

void Function113a0b(void){
    LD_B(0x4);

asm_113a0d:
    LD_A_de;
    INC_DE;
    AND_A_hl;
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_113a0d;
    RET;

}

void Function113a15(void){
    LD_B(0x4);

asm_113a17:
    LD_A_de;
    INC_DE;
    OR_A_hl;
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_113a17;
    RET;

}

void Function113a1f(void){
    LD_B(0x4);

asm_113a21:
    LD_A_hl;
    CPL;
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_113a21;
    RET;

}

void Function113a28(void){
    LD_B(0x4);

asm_113a2a:
    LD_A_de;
    INC_DE;
    XOR_A_hl;
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_113a2a;
    RET;

}

void Function113a32(void){
    LD_A_de;
    INC_DE;
    ADD_A_hl;
    LD_hli_A;
    LD_B(0x3);

asm_113a38:
    LD_A_de;
    INC_DE;
    ADC_A_hl;
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_113a38;
    RET;

}

void Function113a40(void){

asm_113a40:
    OR_A_A;
    PUSH_HL;
    LD_A_hli;
    RLA;
    LD_A_hl;
    RLA;
    LD_hli_A;
    LD_A_hl;
    RLA;
    LD_hli_A;
    LD_A_hl;
    RLA;
    LD_hl_A;
    POP_HL;
    LD_A_hl;
    RLA;
    LD_hl_A;
    DEC_B;
    IF_NZ goto asm_113a40;
    RET;

}

void Unknown_113a55(void){
    //db ['"Authorization: GB00 name="', '0x22', '0'];

    return Unknown_113a70();
}

void Unknown_113a70(void){
    //db ['0x00', '0x00', '0x00', '0x07', '0x06', '0x04', '0x00', '0x0c', '0x04', '0x08', '0x00', '0x11', '0x02', '0x0c', '0x00', '0x16'];
    //db ['0x00', '0x10', '0x00', '0x07', '0x06', '0x14', '0x00', '0x0c', '0x04', '0x18', '0x00', '0x11', '0x02', '0x1c', '0x00', '0x16'];
    //db ['0x00', '0x20', '0x00', '0x07', '0x06', '0x24', '0x00', '0x0c', '0x04', '0x28', '0x00', '0x11', '0x02', '0x2c', '0x00', '0x16'];
    //db ['0x00', '0x30', '0x00', '0x07', '0x06', '0x34', '0x00', '0x0c', '0x04', '0x38', '0x00', '0x11', '0x02', '0x3c', '0x00', '0x16'];
    //db ['0x10', '0x04', '0x00', '0x05', '0x16', '0x18', '0x00', '0x09', '0x14', '0x2c', '0x00', '0x0e', '0x12', '0x00', '0x00', '0x14'];
    //db ['0x10', '0x14', '0x00', '0x05', '0x16', '0x28', '0x00', '0x09', '0x14', '0x3c', '0x00', '0x0e', '0x12', '0x10', '0x00', '0x14'];
    //db ['0x10', '0x24', '0x00', '0x05', '0x16', '0x38', '0x00', '0x09', '0x14', '0x0c', '0x00', '0x0e', '0x12', '0x20', '0x00', '0x14'];
    //db ['0x10', '0x34', '0x00', '0x05', '0x16', '0x08', '0x00', '0x09', '0x14', '0x1c', '0x00', '0x0e', '0x12', '0x30', '0x00', '0x14'];
    //db ['0x20', '0x14', '0x00', '0x04', '0x26', '0x20', '0x00', '0x0b', '0x24', '0x2c', '0x00', '0x10', '0x22', '0x38', '0x00', '0x17'];
    //db ['0x20', '0x04', '0x00', '0x04', '0x26', '0x10', '0x00', '0x0b', '0x24', '0x1c', '0x00', '0x10', '0x22', '0x28', '0x00', '0x17'];
    //db ['0x20', '0x34', '0x00', '0x04', '0x26', '0x00', '0x00', '0x0b', '0x24', '0x0c', '0x00', '0x10', '0x22', '0x18', '0x00', '0x17'];
    //db ['0x20', '0x24', '0x00', '0x04', '0x26', '0x30', '0x00', '0x0b', '0x24', '0x3c', '0x00', '0x10', '0x22', '0x08', '0x00', '0x17'];
    //db ['0x30', '0x00', '0x00', '0x06', '0x36', '0x1c', '0x00', '0x0a', '0x34', '0x38', '0x00', '0x0f', '0x32', '0x14', '0x00', '0x15'];
    //db ['0x30', '0x30', '0x00', '0x06', '0x36', '0x0c', '0x00', '0x0a', '0x34', '0x28', '0x00', '0x0f', '0x32', '0x04', '0x00', '0x15'];
    //db ['0x30', '0x20', '0x00', '0x06', '0x36', '0x3c', '0x00', '0x0a', '0x34', '0x18', '0x00', '0x0f', '0x32', '0x34', '0x00', '0x15'];
    //db ['0x30', '0x10', '0x00', '0x06', '0x36', '0x2c', '0x00', '0x0a', '0x34', '0x08', '0x00', '0x0f', '0x32', '0x24', '0x00', '0x15'];

    return Unknown_113b70();
}

void Unknown_113b70(void){
    //dw ['wMobileSDK_PacketBuffer + 160'];
    //dw ['wMobileSDK_PacketBuffer + 164'];
    //dw ['wMobileSDK_PacketBuffer + 168'];
    //dw ['wMobileSDK_PacketBuffer + 172'];
    //dw ['wMobileSDK_PacketBuffer + 160'];
    //dw ['wMobileSDK_PacketBuffer + 164'];
    //dw ['wMobileSDK_PacketBuffer + 168'];

    return Unknown_113b7e();
}

void Unknown_113b7e(void){
    //db ['0x01', '0x23', '0x45', '0x67', '0x89', '0xab', '0xcd', '0xef'];
    //db ['0xfe', '0xdc', '0xba', '0x98', '0x76', '0x54', '0x32', '0x10'];

    return MD5_K_Table();
}

void MD5_K_Table(void){
    //dl ['0xd76aa478', '0xe8c7b756', '0x242070db', '0xc1bdceee']
    //dl ['0xf57c0faf', '0x4787c62a', '0xa8304613', '0xfd469501']
    //dl ['0x698098d8', '0x8b44f7af', '0xffff5bb1', '0x895cd7be']
    //dl ['0x6b901122', '0xfd987193', '0xa679438e', '0x49b40821']
    //dl ['0xf61e2562', '0xc040b340', '0x265e5a51', '0xe9b6c7aa']
    //dl ['0xd62f105d', '0x02441453', '0xd8a1e681', '0xe7d3fbc8']
    //dl ['0x21e1cde6', '0xc33707d6', '0xf4d50d87', '0x455a14ed']
    //dl ['0xa9e3e905', '0xfcefa3f8', '0x676f02d9', '0x8d2a4c8a']
    //dl ['0xfffa3942', '0x8771f681', '0x6d9d6122', '0xfde5380c']
    //dl ['0xa4beea44', '0x4bdecfa9', '0xf6bb4b60', '0xbebfbc70']
    //dl ['0x289b7ec6', '0xeaa127fa', '0xd4ef3085', '0x04881d05']
    //dl ['0xd9d4d039', '0xe6db99e5', '0x1fa27cf8', '0xc4ac5665']
    //dl ['0xf4292244', '0x432aff97', '0xab9423a7', '0xfc93a039']
    //dl ['0x655b59c3', '0x8f0ccc92', '0xffeff47d', '0x85845dd1']
    //dl ['0x6fa87e4f', '0xfe2ce6e0', '0xa3014314', '0x4e0811a1']
    //dl ['0xf7537e82', '0xbd3af235', '0x2ad7d2bb', '0xeb86d391']

    return Function113c8e();
}

void Function113c8e(void){
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 201);
    LD_A_B;
    LD_addr_A(wMobileSDK_PacketBuffer + 202);
    LD_C_E;
    LD_B_D;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;
    XOR_A_A;
    LD_addr_A(wMobileSDK_PacketBuffer + 207);


asm_113ca0:
    LD_B(0x3);
    PUSH_HL;
    LD_HL(wMobileSDK_PacketBuffer + 203);

asm_113ca6:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_113ca6;
    LD_A_addr(wMobileSDK_PacketBuffer + 201);
    LD_C_A;
    LD_A_addr(wMobileSDK_PacketBuffer + 202);
    LD_B_A;
    XOR_A_A;
    OR_A_B;
    IF_NZ goto asm_113ccf;
    LD_A(0x2);
    CP_A_C;
    IF_C goto asm_113ccf;
    PUSH_HL;
    DEC_HL;
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 207);

asm_113cc3:
    XOR_A_A;
    LD_hld_A;
    INC_C;
    LD_A(0x3);
    CP_A_C;
    IF_NZ goto asm_113cc3;
    POP_HL;
    LD_BC(0x0003);


asm_113ccf:
    DEC_BC;
    DEC_BC;
    DEC_BC;
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 201);
    LD_A_B;
    LD_addr_A(wMobileSDK_PacketBuffer + 202);
    PUSH_DE;
    DEC_HL;
    LD_C_hl;
    DEC_HL;
    LD_B_hl;
    DEC_HL;
    LD_A_hl;
    LD_D_A;
    SRL_A;
    SRL_A;
    LD_hli_A;
    LD_A(0x3);
    AND_A_D;
    LD_D_A;
    LD_A(0xf0);
    AND_A_B;
    OR_A_D;
    SWAP_A;
    LD_hli_A;
    LD_A(0xf);
    AND_A_B;
    LD_D_A;
    LD_A_C;
    AND_A(0xc0);
    OR_A_D;
    RLCA;
    RLCA;
    LD_hli_A;
    LD_A(0x3f);
    AND_A_C;
    LD_hld_A;
    DEC_HL;
    DEC_HL;
    POP_DE;
    LD_B_H;
    LD_C_L;
    POP_HL;
    LD_A_bc;
    INC_BC;
    CALL(aFunction113d47);
    LD_hli_A;
    LD_A_bc;
    INC_BC;
    CALL(aFunction113d47);
    LD_hli_A;
    LD_A_bc;
    INC_BC;
    CALL(aFunction113d47);
    LD_hli_A;
    LD_A_bc;
    INC_BC;
    CALL(aFunction113d47);
    LD_hli_A;
    LD_A_addr(wMobileSDK_PacketBuffer + 201);
    CP_A(0x0);
    JP_NZ (mFunction113c8e_asm_113ca0);
    LD_A_addr(wMobileSDK_PacketBuffer + 202);
    CP_A(0x0);
    JP_NZ (mFunction113c8e_asm_113ca0);
    LD_A_addr(wMobileSDK_PacketBuffer + 207);
    CP_A(0x0);
    IF_Z goto asm_113d43;
    PUSH_HL;
    DEC_HL;
    LD_B_A;

asm_113d39:
    LD_A(0x3d);
    LD_hld_A;
    INC_B;
    LD_A(0x3);
    CP_A_B;
    IF_NZ goto asm_113d39;
    POP_HL;


asm_113d43:
    LD_A(0x0);
    LD_hl_A;
    RET;

}

void Function113d47(void){
    CP_A(0x1a);
    IF_C goto asm_113d5a;
    CP_A(0x34);
    IF_C goto asm_113d5d;
    CP_A(0x3e);
    IF_C goto asm_113d60;
    CP_A(0x3e);
    IF_Z goto asm_113d63;
    LD_A(0x2f);
    RET;


asm_113d5a:
    ADD_A(0x41);
    RET;


asm_113d5d:
    ADD_A(0x47);
    RET;


asm_113d60:
    SUB_A(0x4);
    RET;


asm_113d63:
    LD_A(0x2b);
    RET;

}

void Function113d66(void){
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 201);
    LD_A_B;
    LD_addr_A(wMobileSDK_PacketBuffer + 202);
    LD_C_E;
    LD_B_D;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;

asm_113d74:
    LD_A_addr(wMobileSDK_PacketBuffer + 202);
    OR_A_A;
    IF_NZ goto asm_113d82;
    LD_A_addr(wMobileSDK_PacketBuffer + 201);
    CP_A(0x4);
    JP_C (mFunction113d66_asm_113e26);


asm_113d82:
    LD_B(0x4);
    PUSH_HL;
    LD_HL(wMobileSDK_PacketBuffer + 203);

asm_113d88:
    LD_A_de;
    INC_DE;
    CALL(aFunction113d66_Function113dfa);
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_113d88;
    LD_A_addr(wMobileSDK_PacketBuffer + 201);
    LD_C_A;
    LD_A_addr(wMobileSDK_PacketBuffer + 202);
    LD_B_A;
    for(int rept = 0; rept < 4; rept++){
    DEC_BC;
    }
    LD_A_B;
    OR_A_C;
    IF_Z goto asm_113dae;

asm_113da1:
    LD_A_de;
    CP_A(0xd);
    IF_Z goto asm_113daa;
    CP_A(0xa);
    IF_NZ goto asm_113dae;


asm_113daa:
    INC_DE;
    DEC_BC;
    goto asm_113da1;


asm_113dae:
    LD_A_C;
    LD_addr_A(wMobileSDK_PacketBuffer + 201);
    LD_A_B;
    LD_addr_A(wMobileSDK_PacketBuffer + 202);
    PUSH_DE;
    DEC_HL;
    LD_D_hl;
    DEC_HL;
    LD_C_hl;
    DEC_HL;
    LD_B_hl;
    DEC_HL;
    LD_A_hl;
    SLA_B;
    SLA_B;
    SLA_B;
    RLA;
    SLA_B;
    RLA;
    LD_hli_A;
    LD_hl_B;
    INC_HL;
    RRC_C;
    RRC_C;
    LD_hl_C;
    DEC_HL;
    LD_A(0xf);
    AND_A_C;
    OR_A_hl;
    LD_hli_A;
    LD_A_hli;
    AND_A(0xc0);
    OR_A_hl;
    DEC_HL;
    LD_hld_A;
    DEC_HL;
    POP_DE;
    LD_B_H;
    LD_C_L;
    POP_HL;
    LD_A_bc;
    LD_hli_A;
    INC_BC;
    LD_A_bc;
    LD_hli_A;
    INC_BC;
    LD_A_bc;
    LD_hli_A;
    LD_A_addr(wMobileSDK_PacketBuffer + 201);
    OR_A_A;
    IF_NZ goto asm_113d74;
    LD_A_addr(wMobileSDK_PacketBuffer + 202);
    OR_A_A;
    JP_NZ (mFunction113d66_asm_113d74);
    XOR_A_A;
    LD_hl_A;
    RET;


Function113dfa:
    CP_A(0x2b);
    IF_C goto asm_113e24;
    IF_Z goto asm_113e31;
    CP_A(0x2f);
    IF_C goto asm_113e24;
    IF_Z goto asm_113e34;
    CP_A(0x30);
    IF_C goto asm_113e24;
    CP_A(0x3a);
    IF_C goto asm_113e37;
    CP_A(0x3d);
    IF_C goto asm_113e24;
    IF_Z goto asm_113e3a;
    CP_A(0x41);
    IF_C goto asm_113e24;
    CP_A(0x5b);
    IF_C goto asm_113e3c;
    CP_A(0x61);
    IF_C goto asm_113e24;
    CP_A(0x7b);
    IF_C goto asm_113e3f;


asm_113e24:
    POP_HL;
    POP_HL;

asm_113e26:
    LD_HL(wc821);
    SET_hl(1);
    LD_A(0x20);
    LD_addr_A(wc80f);
    RET;


asm_113e31:
    LD_A(0x3e);
    RET;


asm_113e34:
    LD_A(0x3f);
    RET;


asm_113e37:
    ADD_A(0x4);
    RET;


asm_113e3a:
    XOR_A_A;
    RET;


asm_113e3c:
    SUB_A(0x41);
    RET;


asm_113e3f:
    SUB_A(0x47);
    RET;

}

void Function113e42(void){
    DEC_A;
    IF_Z goto asm_113e4f;
    DEC_A;
    IF_Z goto asm_113e85;
    DEC_A;
    IF_Z goto asm_113ea8;
    DEC_A;
    IF_Z goto asm_113eb0;
    RET;


asm_113e4f:
    LD_A_addr(wc807);
    CP_A(0x8);
    IF_NZ goto asm_113e58;

asm_113e56:
    DEC_hl;
    RET;


asm_113e58:
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_A(0x2);
    LD_addr_A(wc86a);
    LD_HL(wc821);
    LD_A_hl;
    AND_A(0x10);
    SET_A(5);
    LD_hl_A;
    JP(mFunction113eb8);


asm_113e6d:
    LD_A_addr(wc86d);
    OR_A_A;
    LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    IF_Z goto asm_113e81;
    CP_A(0x9f);
    IF_Z goto asm_113e85;
    CP_A(0xa4);
    IF_Z goto asm_113e85;

asm_113e7e:
    JP(mFunction112430);


asm_113e81:
    CP_A(0xa3);
    IF_Z goto asm_113e7e;


asm_113e85:
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_A(0x2);
    LD_addr_A(wc86a);
    LD_A(0x3);
    LD_addr_A(wc807);
    LD_HL(wc821);
    LD_A_hl;
    AND_A(0x10);
    SET_A(5);
    LD_hl_A;
    LD_HL(wc822);
    BIT_hl(0);
    CALL_Z (aFunction111f97);
    RET;


asm_113ea8:
    LD_A_addr(wc807);
    CP_A(0x8);
    IF_Z goto asm_113e56;
    RET;


asm_113eb0:
    LD_A(0x1);
    LD_addr_A(wc86b);
    JP(mFunction113e42_asm_113e6d);

    return Function113eb8();
}

void Function113eb8(void){
    LD_A(0xff);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_HL(wc822);
    RES_hl(5);
    RES_hl(0);
    JP(mFunction111f97);

}

void Function113ec7(void){
//  //  unreferenced
    LD_HL(wc822);
    LD_A_hl;
    PUSH_AF;
    RES_hl(3);
    RES_hl(0);
    LD_HL(wc81a);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    INC_HL;
    INC_HL;
    LD_A_hld;
    DEC_HL;
    XOR_A(0x80);
    LD_addr_A(wMobileSDK_SendCommandID);
    LD_B(0x5);
    CALL(aPacketSendBytes);
    POP_AF;
    BIT_A(0);
    RET_Z ;
    LD_HL(wc822);
    SET_hl(0);
    RET;

}

void Function113ef2(void){
    DEC_A;
    IF_Z goto asm_113efa;
    DEC_A;
    IF_Z goto asm_113f03;
    DEC_hl;
    RET;


asm_113efa:
    LD_A_addr(wc807);
    CP_A(0x8);
    JR_NZ (mFunction113eb8);
    DEC_hl;
    RET;


asm_113f03:
    LD_A(0x26);
    CALL(aFunction11225d);
    LD_A(0x2a);
    LD_addr_A(wc86a);
    LD_HL(wc820);
    LD_A_hld;
    LD_H_hl;
    LD_L_A;
    LD_E_L;
    LD_D_H;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(wc815);
    LD_E_A;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wc800);
    LD_HL(wMobileSDK_PacketBuffer);
    LD_A(0x2);
    LD_hli_A;
    DEC_A;
    LD_hl_A;
    RET;

}

void Function113f2d(void){
    DEC_A;
    IF_Z goto asm_113f35;
    DEC_A;
    IF_Z goto asm_113f4f;
    DEC_hl;
    RET;


asm_113f35:
    LD_A_addr(wc807);
    CP_A(0x8);
    IF_NZ goto asm_113f3e;
    DEC_hl;
    RET;


asm_113f3e:
    XOR_A_A;
    LD_addr_A(wMobileSDK_ReceivePacketBuffer);
    LD_addr_A(wMobileSDK_ReceivePacketBufferAlt);
    LD_A_addr(wMobileSDK_SendCommandID);
    CP_A(0x91);
    IF_Z goto asm_113f4f;
    JP(mFunction113eb8);


asm_113f4f:
    XOR_A_A;
    LD_addr_A(wc86d);
    LD_HL(wc821);
    SET_hl(0);
    LD_HL(wc822);
    XOR_A_A;
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wc80b);
    XOR_A_A;
    LD_addr_A(wMobileSDK_PacketBuffer);
    LD_HL(wc820);
    LD_A_hld;
    LD_H_hl;
    LD_L_A;
    LD_E_L;
    LD_D_H;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_HL(wc815);
    LD_E_A;
    LD_hli_A;
    LD_A_D;
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wc800);
    LD_HL(wMobileSDK_PacketBuffer);
    XOR_A_A;
    LD_hli_A;
    INC_A;
    LD_hl_A;
    RET;

}

#include "../../constants.h"
#include "main.h"
#include "../../home/compare.h"
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

#define MOBILE_PACKET_MAGIC_BYTES 0x99, 0x66
#define MOBILE_PACKET_IDLE_BYTE 0x4b

enum {
    HTTP_METHOD_GET = 0x0,
    HTTP_METHOD_POST = 0x1,
};

const uint8_t MobilePacket_Idle[] = {
    MOBILE_PACKET_IDLE_BYTE
};

const uint8_t MobilePacket_BeginSession[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_BEGIN_SESSION, 0x00, 0x00, 0x08, 
    'N', 'I', 'N', 'T', 'E', 'N', 'D', 'O', // "NINTENDO", 
    0x02, 0x77, 0x80, 0x00
};

const uint8_t MobilePacket_EndSession[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_END_SESSION, 0x00, 0x00, 0x00, 0x00, 0x11, 0x80, 0x00
};

const uint8_t MobilePacket_DialTelephone[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_DIAL_TELEPHONE, 0x00, 0x00, 0x00
};

const uint8_t MobilePacket_HangUpTelephone[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_HANG_UP_TELEPHONE, 0x00, 0x00, 0x00, 0x00, 0x13, 0x80, 0x00
};

const uint8_t MobilePacket_TelephoneStatus[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_TELEPHONE_STATUS, 0x00, 0x00, 0x00, 0x00, 0x17, 0x80, 0x00
};

const uint8_t MobilePacket_ISPLogin[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_ISP_LOGIN, 0x00, 0x00
};

const uint8_t MobilePacket_ISPLogout[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_ISP_LOGOUT, 0x00, 0x00, 0x00, 0x00, 0x22, 0x80, 0x00
};

const uint8_t MobilePacket_ReadConfigurationDataPart1[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_READ_CONFIGURATION_DATA, 0x00, 0x00, 0x02, 0x00, 0x60, 0x00, 0x7b, 0x80, 0x00
};

const uint8_t MobilePacket_ReadConfigurationDataPart2[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_READ_CONFIGURATION_DATA, 0x00, 0x00, 0x02, 0x60, 0x60, 0x00, 0xdb, 0x80, 0x00
};

const uint8_t MobilePacket_WriteConfigurationData[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_WRITE_CONFIGURATION_DATA, 0x00, 0x00
};

const uint8_t MobilePacket_DNSQuery[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_DNS_QUERY, 0x00, 0x00
};

const uint8_t MobilePacket_WaitForTelephoneCall[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_WAIT_FOR_TELEPHONE_CALL, 0x00, 0x00, 0x00, 0x00, 0x14, 0x80, 0x00
};

const uint8_t MobilePacket_TransferData[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_TRANSFER_DATA, 0x00, 0x00, 0x01, 0xff, 0x01, 0x15, 0x80, 0x00
};

const uint8_t MobilePacket_OpenTCPConnection[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_OPEN_TCP_CONNECTION, 0x00, 0x00, 0x06
};

const uint8_t MobilePacket_CloseTCPConnection[] = {
    MOBILE_PACKET_MAGIC_BYTES, MOBILE_COMMAND_CLOSE_TCP_CONNECTION, 0x00, 0x00, 0x01
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
uint8_t* gMobile_wc827;
uint8_t* gMobile_wc833_wc834;
uint8_t* gMobile_wc86e_wc86f;
uint8_t* gMobile_wc874_wc875;
uint8_t* gMobile_wc876;
uint8_t* gMobile_wc878;
uint8_t* gMobile_wc87c_wc87d;
uint8_t* gMobile_wc9aa_wc9ab;
uint8_t* gMobile_wc9b5;
uint8_t* gMobile_wc97f_wc980;
uint8_t* gMobile_wc98f;

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
    return de_;
}

//  Copy bytes from hl to de until a 0 is encountered.
//  Include the 0 in the copy, and count the number of
//  nonzero bytes copied.  Keep the de pointer at the
//  copied zero.
char* MobileSDK_CopyString(char* de, const char* hl, uint16_t* bc){
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
        (*bc)++;
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
        char ch = *(hl++);
        // LD_de_A;
        *de = ch;
        // OR_A_A;
        // IF_Z goto done;
        if(ch == '\0')
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
        [MOBILEAPI_05] = Function1104c6,
        [MOBILEAPI_06] = Function110578,
        [MOBILEAPI_07] = Function110582,
        [MOBILEAPI_08] = Function11058c,
        [MOBILEAPI_09] = Function1105dd,
        // [MOBILEAPI_0A] = Function1106ef,
        // [MOBILEAPI_0B] = Function110757,
        // [MOBILEAPI_0C] = Function1107ff,
        // [MOBILEAPI_0D] = Function110899,
        // [MOBILEAPI_0E] = Function1108a3,
        // [MOBILEAPI_0F] = Function110905,
        // [MOBILEAPI_10] = Function1109a4,
        // [MOBILEAPI_11] = Function1109f9,
        [MOBILEAPI_12] = Function110a5b,
        [MOBILEAPI_13] = Function110c3c,
        [MOBILEAPI_14] = Function110c9e,
        [MOBILEAPI_15] = Function110ddd,
        [MOBILEAPI_16] = Function1111fe,
        [MOBILEAPI_17] = Function1113fe,
        [MOBILEAPI_SETTIMER] = MobileAPI_SetTimer,
        [MOBILEAPI_19] = Function111541,
        // [MOBILEAPI_1A] = Function111596,
        [MOBILEAPI_1B] = Function11162d,
        // [MOBILEAPI_1C] = Function11032c,
        // [MOBILEAPI_1D] = Function11148c,
        // [MOBILEAPI_1E] = Function111610,
        // [MOBILEAPI_1F] = Function1103ac,
        [MOBILEAPI_20] = Function110235,
        [MOBILEAPI_21] = Function111540,
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
    printf("Mobile API %02X\n", wram->wMobileAPIIndex);
    // CALL_NZ (aFunction1100b4);
    if(wram->wMobileAPIIndex != MOBILEAPI_01)
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

void finish_gb_cycle(void);

bool Function1100b4(void){
    // PUSH_BC;
    uint8_t b, c;

    do {
    // loop:
        finish_gb_cycle();
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
    hl += LOW(data->bc);
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
    // LD_HL(wc821);
    // BIT_hl(1);
    // IF_NZ goto asm_110120;
    if(!bit_test(wram->wc821, 1)) {
        // XOR_A_A;
        data->a = 0x0;
        // LD_L_A;
        data->l = 0x0;
        // LD_H_A;
        data->h = 0x0;
        // RET;
        return;
    }

// asm_110120:
    // RES_hl(1);
    bit_reset(wram->wc821, 1);
    // LD_A_addr(wc80f);
    // LD_E_A;
    uint8_t e = wram->wc80f;
    switch(e) {
        // CP_A(0x22);
        // IF_Z goto asm_11016a;
        // CP_A(0x23);
        // IF_Z goto asm_11016a;
        // CP_A(0x25);
        // IF_Z goto asm_11016a;
        // CP_A(0x26);
        // IF_Z goto asm_11018e;
        case 0x26:
        // asm_11018e:
            // LD_A_addr(wc821);
            // BIT_A(4);
            // LD_A(0x1);
            // IF_Z goto asm_11016a;
            if(!bit_test(wram->wc821, 4))
                break;
            // LD_A(0x2);
            // LD_addr_A(wc86a);
            wram->wc86a = 0x2;
            // LD_A_addr(wc805);
            // LD_addr_A(wc807);
            wram->wc807 = wram->wc805;
            goto asm_110158;
        // CP_A(0x30);
        // JP_Z (mFunction110115_asm_1101f8);
        case 0x30:
        // asm_1101f8:
            // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
            // CP_A(0xa4);
            // IF_Z goto asm_1101a4;
            if(wram->wMobileSDK_ReceivePacketBuffer[0] != 0xa4) {
                // LD_A(0x3);
                // LD_addr_A(wc86a);
                wram->wc86a = 0x3;
                // LD_HL(wc810);
                // LD_A_hli;
                // LD_H_hl;
                data->h = wram->wc811;
                // LD_L_A;
                data->l = wram->wc810;
                // JP(mFunction110115_asm_11015b);
                goto asm_11015b;
            }
            // goto asm_1101a4;
            fallthrough;
        // CP_A(0x24);
        // IF_Z goto asm_1101a4;
        case 0x24:
        case 0x32:
        case 0x33:
        asm_1101a4:
            // RES_hl(0);
            bit_reset(wram->wc821, 0);
            // LD_HL(wc822);
            // RES_hl(5);
            bit_reset(wram->wc822, 5);
            // LD_HL(wc821);
            // RES_hl(7);
            // RES_hl(6);
            wram->wc821 &= ~((1 << 7) | (1 << 6));
            // SET_hl(5);
            bit_set(wram->wc821, 5);
            // XOR_A_A;
            // LD_addr_A(wc86d);
            wram->wc86d = 0x0;
            // LD_addr_A(wc9af);
            wram->wc9af = 0x0;
            // LD_A(0x2);
            // LD_addr_A(wc86a);
            wram->wc86a = 0x2;
            // LD_A(0x4);
            // LD_addr_A(wc807);
            wram->wc807 = 0x4;
            // LD_A_E;
            // CP_A(0x32);
            // IF_Z goto asm_1101d7;
            // CP_A(0x33);
            // IF_Z goto asm_1101d7;
            // CP_A(0x30);
            // IF_Z goto asm_1101d7;
            // CP_A(0x31);
            // JP_NZ (mFunction110115_asm_110158);
            if(e != 0x32 && e != 0x33 && e != 0x30 && e != 0x31)
                goto asm_110158;
            goto asm_1101d7;
        // CP_A(0x31);
        // JP_Z (mFunction110115_asm_11020d);
        case 0x31:
        // asm_11020d:
            // LD_A_addr(wc810);
            // CP_A(0x2);
            // IF_Z goto asm_1101a4;
            // CP_A(0x3);
            // IF_Z goto asm_1101a4;
            if(wram->wc810 == 0x2 || wram->wc810 == 0x3)
                goto asm_1101a4;
            // LD_A(0x4);
            // LD_addr_A(wc86a);
            wram->wc86a = 0x4;
            // LD_HL(wc810);
            // LD_A_hli;
            // LD_H_hl;
            data->h = wram->wc811;
            // LD_L_A;
            data->l = wram->wc811;
            // JP(mFunction110115_asm_11015b);
            goto asm_11015b;
        // CP_A(0x32);
        // IF_Z goto asm_1101a4;
        // CP_A(0x33);
        // IF_Z goto asm_1101a4;
        default: {
            // SWAP_A;
            // AND_A(0xf);
            uint8_t a = (e >> 4) & 0xf;
            // CP_A(0x1);
            // IF_Z goto asm_11016a;
            if(a != 0x1) {
                // CP_A(0x0);
                // IF_Z goto asm_11015d;
                if(a != 0x0) {
                asm_110158:
                    // LD_HL(0);
                    data->h = 0x0;
                    data->l = 0x0;

                asm_11015b:
                    // LD_A_E;
                    data->a = e;
                    // RET;
                    return;
                }
                else {
                // asm_11015d:
                    // LD_A_E;
                    // ADD_A(0x15);
                    // LD_E_A;
                    e += 0x15;
                    // XOR_A_A;
                    // LD_HL(wc810);
                    // LD_hli_A;
                    wram->wc810 = 0x0;
                    // LD_hl_A;
                    wram->wc811 = 0x0;
                    // LD_HL(wc821);
                }
            }
        } fallthrough;
        case 0x22:
        case 0x23:
        case 0x25:
            // goto asm_11016a;
            break;
    }


asm_11016a:
    // XOR_A_A;
    // LD_addr_A(wc86d);
    wram->wc86d = 0x0;
    // LD_hl_A;
    wram->wc821 = 0x0;
    // LD_addr_A(wc807);
    wram->wc807 = 0x0;
    // INC_A;
    // LD_addr_A(wc86a);
    wram->wc86a = 0x1;
    // LD_HL(wc822);
    // RES_hl(0);
    bit_reset(wram->wc822, 0);
    // RES_hl(5);
    bit_reset(wram->wc822, 5);
    // LD_HL(wMobileSDK_PacketBuffer);
    // XOR_A_A;
    // LD_hli_A;
    wram->wMobileSDK_PacketBuffer[0] = 0x0;
    // INC_A;
    // LD_hl_A;
    wram->wMobileSDK_PacketBuffer[1] = 0x1;
    // CALL(aFunction111686);
    Function111686();
    // LD_A(0x15);
    // CP_A_E;
    // IF_NZ goto asm_110158;
    if(e != 0x15)
        goto asm_110158;
    // goto asm_1101d7;

asm_1101d7:
    // LD_HL(wc810);
    // LD_A_hli;
    // LD_H_hl;
    data->h = wram->wc811;
    // LD_L_A;
    data->l = wram->wc810;
    // LD_A(0x32);
    // CP_A_E;
    // JP_NZ (mFunction110115_asm_11015b);
    // LD_A(0x3);
    // CP_A_H;
    // JP_NZ (mFunction110115_asm_11015b);
    // DEC_A;
    // CP_A_L;
    // IF_Z goto asm_1101f2;
    // DEC_A;
    // CP_A_L;
    // JP_NZ (mFunction110115_asm_11015b);
    if(e != 0x32 || data->h != 0x3 || (data->l != 0x2 && data->l != 0x1))
        goto asm_11015b;

// asm_1101f2:
    // LD_BC(wc880);
    data->bc = wc880;
    // JP(mFunction110115_asm_11015b);
    goto asm_11015b;
}

// Mobile_SetWC80Fto33AndSetWC821Bit1
void Function110226(void){
    // LD_A(0x21);

    return Function110228(0x21);
}

// Mobile_SetWC80FtoAAndSetWC821Bit1
void Function110228(uint8_t a){
    // LD_addr_A(wc80f);
    wram->wc80f = a;
    // LD_HL(wc821);
    // SET_hl(1);
    bit_set(wram->wc821, 1);
    // RET;
}

// Mobile_SetWC80Fto32AndSetWC821Bit1
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
    gMobile_wc86e_wc86f = data->de;
    wram->wc86e = (gMobile_wc86e_wc86f == NULL)? 0x0: 0x1;
    wram->wc86f = (gMobile_wc86e_wc86f == NULL)? 0x0: 0x1;
    // XOR_A_A;
    // LD_addr_A(wc819);
    wram->wc819 = 0x0;
    // LD_C(0xc);
    data->bc = (data->bc & 0xff00) | 0xc;
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
    // LD_A(0xc8);
    // LD_hl_A;
    gMobileReceiveBuffer_Destination = (uint8_t*)wram->wc872_digit_buffer;
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

// MobileAPI_1C
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

bool Function11039a(char** hl, uint8_t c){
    // LD_B(0x0);
    uint8_t b = 0x0;

    do {
    // asm_11039c:
        // INC_B;
        // IF_Z goto asm_1103a3;
        if(++b == 0)
            break;
        // LD_A_hli;
        // OR_A_A;
        // IF_NZ goto asm_11039c;
    } while(*((*hl)++) != 0x0);

// asm_1103a3:
    // LD_A_B;
    // CP_A_C;
    // IF_NC goto asm_1103aa;
    if(b < c) {
        // CP_A(0x2);
        // RET;
        return b < 0x2;
    }

// asm_1103aa:
    // SCF;
    // RET;
    return true;
}

// MobileAPI03
void Function1103ac(mobile_api_data_s* data){
    // LD_A_addr(wc821);
    // BIT_A(0);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc86a);
    // CP_A(0x1);
    // JP_NZ (mFunction110226);
    if(bit_test(wram->wc821, 0) || wram->wc86a != 0x1)
        return Function110226();
    // PUSH_HL;
    char* hl = data->hl;
    printf("MOBILE API \"%s\"\n", hl);
    // LD_C(0x15);
    // CALL(aFunction11039a);
    // IF_C goto asm_1103d2;
    // LD_C(0x22);
    // CALL(aFunction11039a);
    // IF_C goto asm_1103d2;
    // LD_C(0x12);
    // CALL(aFunction11039a);
    // IF_NC goto asm_1103d6;
    if(Function11039a(&hl, 0x15) 
    || Function11039a(&hl, 0x22)
    /* Function11039a(&hl, 0x12) */) {
    // asm_1103d2:
        // POP_HL;
        // JP(mFunction110231);
        return Function110231();
    }

// asm_1103d6:
    hl = data->hl;
    // XOR_A_A;
    // LDH_addr_A(rTAC);
    gb_write(rTAC, 0x0);
    // LD_addr_A(wc86d);
    wram->wc86d = 0x0;
    // LD_addr_A(wc97a);
    wram->wc97a[0] = 0x0;
    // LD_A_addr(wc870);
    // LD_C_A;
    data->bc = (data->bc & 0xff00) | wram->wc870;
    // CALL(aMobileAPI_SetTimer);
    MobileAPI_SetTimer(data);
    // LD_HL(wc829);
    // LD_A(0x80);
    // LD_hli_A;
    // LD_A(0xc8);
    // LD_hl_A;
    gMobileReceiveBuffer_Destination = (uint8_t*)wram->wc880_str;
    // CALL(aFunction110485);
    uint8_t b;
    // PUSH_HL;
    char* str = Function110485(hl, &b);
    hl += b;
    // LD_B_A;
    // CALL(aFunction111f63);
    Function111f63(str, b);
    // LD_B(lengthof(MobilePacket_ISPLogin));
    // LD_HL(mMobilePacket_ISPLogin);
    // LD_DE(wMobileSDK_PacketBuffer + 45);
    // CALL(aMobileSDK_CopyBytes);
    char* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 45, MobilePacket_ISPLogin, sizeof(MobilePacket_ISPLogin));
    // INC_DE;
    // INC_DE;
    de += 2;
    // POP_HL;
    // LD_BC(0);
    uint16_t bc = 0;
    // CALL(aMobileSDK_CopyString);
    de = MobileSDK_CopyString(de, hl, &bc);
    hl += bc;
    // LD_A_C;
    // LD_addr_A(wMobileSDK_PacketBuffer + 51);
    wram->wMobileSDK_PacketBuffer[51] = LOW(bc);
    // LD_addr_A(wc86b);
    wram->wc86b = LOW(bc);
    // PUSH_DE;
    char* de2 = de + 1;
    // INC_DE;
    // LD_BC(0);
    bc = 0;
    // LD_A(0x20);
    // CALL(aMobileSDK_CopyStringLen);
    hl = MobileSDK_CopyStringLen(de2, hl, &bc, 0x20);
    // LD_L_E;
    // LD_H_D;
    // POP_DE;
    // LD_A_C;
    // LD_de_A;
    *de = LOW(bc);
    // LD_A_addr(wc86b);
    // ADD_A_C;
    // ADD_A(0xa);
    // LD_addr_A(wMobileSDK_PacketBuffer + 50);
    wram->wMobileSDK_PacketBuffer[50] = wram->wc86b + LOW(bc) + 0xa;
    // CALL(aFunction1104b0);
    Function1104b0();
    // LD_A(0xb);
    // LD_addr_A(wc86a);
    wram->wc86a = 0xb;

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
    // LD_A_addr(wc821);
    // BIT_A(0);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc86a);
    // CP_A(0x1);
    // JP_NZ (mFunction110226);
    if(bit_test(wram->wc821, 0) || wram->wc86a != 0x1)
        return Function110226();
    // PUSH_HL;
    const char* number = data->hl;
    // LD_C(0x15);
    // CALL(aFunction11039a);
    // IF_NC goto asm_110454;
    if(Function11039a((char**)&data->hl, 0x15)) {
        // POP_HL;
        // JP(mFunction110231);
        return Function110231();
    }

// asm_110454:
    // XOR_A_A;
    // LDH_addr_A(rTAC);
    gb_write(rTAC, 0x0);
    // LD_addr_A(wc97a);
    wram->wc97a[0] = 0x0;
    // LD_A_addr(wc870);
    // LD_C_A;
    data->bc = wram->wc870;
    // CALL(aMobileAPI_SetTimer);
    MobileAPI_SetTimer(data);
    // LD_HL(wc98f);
    // LD_A(0x81);
    // LD_hli_A;
    // LD_A(0xc8);
    // LD_hli_A;
    gMobile_wc98f = &wram->wc881;
    // XOR_A_A;
    // LD_hli_A;
    wram->wc991 = 0x0;
    // LD_hli_A;
    wram->wc992 = 0x0;
    // LD_hli_A;
    wram->wc993 = 0x0;
    // LD_hl_A;
    wram->wc994 = HTTP_METHOD_GET;
    // LD_A(0xff);
    // LD_addr_A(wc86e);
    wram->wc86e = 0xff;
    // CALL(aFunction110485);
    uint8_t a;
    char* de = Function110485(number, &a);
    // LD_B_A;
    // CALL(aFunction111f63);
    Function111f63(de, a);
    // CALL(aFunction1104b0);
    Function1104b0();
    // LD_A(0xc);
    // LD_addr_A(wc86a);
    wram->wc86a = 0xc;
    // JR(mFunction110432);
    Function110432();

}

// Mobile_DialPhoneNumber
char* Function110485(const char* hl, uint8_t* a){
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_DialTelephone);
    // LD_B(lengthof(MobilePacket_DialTelephone));
    // CALL(aMobileSDK_CopyBytes);
    char* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_DialTelephone, sizeof(MobilePacket_DialTelephone));
    // POP_BC;
    // POP_HL;
    // PUSH_BC;
    // LD_A_addr(wMobileSDK_AdapterType);
    // CP_A(0x8c);
    // IF_C goto asm_11049e;
    // LD_A(0x3);
    // goto asm_1104a1;

// asm_11049e:
    // LD_A_addr(wc871);

// asm_1104a1:
    // LD_de_A;
    // INC_DE;
    *(de++) = (wram->wMobileSDK_AdapterType < 0x8c)? wram->wc871: 0x3;
    // LD_BC(0x0001);
    uint16_t bc = 0x0001;
    // LD_A(MOBILE_PHONE_NUMBER_LENGTH);
    // CALL(aMobileSDK_CopyStringLen);
    de = MobileSDK_CopyStringLen(de, hl, &bc, MOBILE_PHONE_NUMBER_LENGTH);
    // LD_A_C;
    // LD_addr_A(wMobileSDK_PacketBuffer + 5);
    wram->wMobileSDK_PacketBuffer[5] = LOW(bc);
    *a = LOW(bc);
    // RET;
    return de;
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

// MobileAPI_05
void Function1104c6(mobile_api_data_s *data){
    (void)data;
    // LD_A_addr(wc821);
    // BIT_A(0);
    // JP_NZ (mFunction110226);
    if(bit_test(wram->wc821, 0))
        return Function110226();
    // LD_A_addr(wc86a);
    // CP_A(0x4);
    // IF_Z goto asm_110526;
    // CP_A(0x3);
    // IF_Z goto asm_110526;
    if(wram->wc86a != 0x4 && wram->wc86a != 0x3) {
        // CP_A(0x2);
        // JP_NZ (mFunction110226);
        if(wram->wc86a != 0x2)
            return Function110226();
        // LD_HL(wc822);
        // BIT_hl(4);
        // IF_NZ goto asm_110507;
        if(!bit_test(wram->wc822, 4)) {
            // LD_A(0x2);
            // LD_addr_A(wc86b);
            wram->wc86b = 0x2;
            // LD_A(MOBILE_COMMAND_ISP_LOGOUT | 0x80);
            // LD_addr_A(wMobileSDK_SendCommandID);
            wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_ISP_LOGOUT | 0x80;
            // LD_DE(lengthof(MobilePacket_ISPLogout));
            // LD_HL(mMobilePacket_ISPLogout);
            // LD_B(0x5);
            // CALL(aPacketSendBytes);
            PacketSendBytes(MobilePacket_ISPLogout, lengthof(MobilePacket_ISPLogout), 0x5);
        }
        else {
        // asm_110507:
            // LD_A_addr(wc807);
            // OR_A_A;
            // IF_NZ goto asm_11051f;
            if(wram->wc807 == 0) {
                // LD_A(0x1);
                // LD_addr_A(wc86a);
                wram->wc86a = 0x1;
                // LD_HL(wc822);
                // RES_hl(4);
                bit_reset(wram->wc822, 4);
                // LD_HL(wc821);
                // LD_A_hl;
                // AND_A(0x17);
                // LD_hl_A;
                wram->wc821 &= 0x17;
                // RET;
                return;
            }

        // asm_11051f:
            // LD_A(0x2);
            // LD_addr_A(wc86b);
            wram->wc86b = 0x2;
            // goto asm_1104fa;
        }

    // asm_1104fa:
        // LD_A(0xe);
        // LD_addr_A(wc86a);
        wram->wc86a = 0xe;
        // LD_HL(wc821);
        // SET_hl(0);
        bit_set(wram->wc821, 0);
        // RES_hl(3);
        bit_reset(wram->wc821, 3);
        // RET;
        return;
    }

// asm_110526:
    // CALL(aFunction112724);
    Function112724();
    // XOR_A_A;
    // LD_addr_A(wc86b);
    wram->wc86b = 0x0;
    // LD_DE(wMobileSDK_PacketBuffer + 32);
    // LD_HL(mMobilePacket_TransferData);
    // LD_B(0x6);
    // CALL(aMobileSDK_CopyBytes);
    uint8_t* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 32, MobilePacket_TransferData, 0x6);
    // LD_A_addr(wc86c);
    // LD_de_A;
    // INC_DE;
    *(de++) = wram->wc86c;
    // LD_B(0x1);
    // CALL(aFunction111f63);
    Function111f63(de, 0x1);
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_TransferData);
    // LD_B(0x5);
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_TransferData, 0x6);
    // LD_A(0x7);
    // LD_de_A;
    // INC_DE;
    *(de++) = 0x7;
    // LD_A_addr(wc86c);
    // LD_de_A;
    // INC_DE;
    *(de++) = wram->wc86c;
    // LD_BC(0x0001);
    uint16_t bc = 0x0001;
    // LD_HL(mUnknown_1120c1);
    // CALL(aMobileSDK_CopyString);
    de = (uint8_t*)MobileSDK_CopyString((char*)de, Unknown_1120c1, &bc);
    // LD_B_C;
    // CALL(aFunction111f63);
    Function111f63(de, bc & 0xff);
    // LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    // LD_addr_A(wMobileSDK_SendCommandID);
    wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_TRANSFER_DATA | 0x80;
    // LD_HL(wMobileSDK_PacketBuffer);
    // LD_B(0x5);
    // CALL(aPacketSendBytes);
    PacketSendBytes(wram->wMobileSDK_PacketBuffer, bc, 0x5);
    // LD_A(0xe);
    // LD_addr_A(wc86a);
    wram->wc86a = 0xe;
    // JP(mFunction110432);
    Function110432();
}

// MobileAPI_06
void Function110578(mobile_api_data_s* data){
    // LD_B(0x25);
    // CALL(aFunction110596);
    uint8_t a = Function110596(data, 0x25);
    // OR_A_A;
    // JP_NZ (mFunction1135ba);
    if(a != 0) {
        data->de = Function1135ba(data->de);
    }
    // RET;
}

// MobileAPI_07
void Function110582(mobile_api_data_s* data){
    // LD_B(0x26);
    // CALL(aFunction110596);
    uint8_t a = Function110596(data, 0x26);
    // OR_A_A;
    // JP_NZ (mFunction11359d);
    if(a != 0) {
        data->de = Function11359d(data->de, &(uint16_t){0x0});
    }
    // RET;
}

// MobileAPI_08
void Function11058c(mobile_api_data_s* data){
    // LD_B(0x27);
    // CALL(aFunction110596);
    uint8_t a = Function110596(data, 0x26);
    // OR_A_A;
    // JP_NZ (mFunction1135ad);
    if(a != 0) {
        data->de = Function11359d(data->de, &(uint16_t){0x0});
    }
    // RET;
}

uint8_t Function110596(mobile_api_data_s* data, uint8_t b){
    // LD_A_addr(wc821);
    // BIT_A(0);
    // IF_NZ goto asm_1105d9;
    // LD_A_addr(wc86a);
    // CP_A(0x1);
    // IF_NZ goto asm_1105d9;
    if(bit_test(wram->wc821, 0) || wram->wc86a != 0x1) {
    // asm_1105d9:
        // POP_HL;
        // JP(mFunction110226);
        Function110226();
        return 0x21;
    }
    // LD_A_addr(wc835);
    // OR_A_A;
    // RET_NZ ;
    if(wram->wc835 != 0)
        return wram->wc835;
    // LD_A_B;
    // LD_addr_A(wcb36);
    wram->wcb36 = b;
    // XOR_A_A;
    // LDH_addr_A(rTAC);
    gb_write(rTAC, 0x0);
    // LD_A_E;
    // LD_addr_A(wc86e);
    // LD_A_D;
    // LD_addr_A(wc86f);
    gMobile_wc86e_wc86f = data->de;
    wram->wc86e = (gMobile_wc86e_wc86f == NULL)? 0x0: 0x1;
    wram->wc86f = (gMobile_wc86e_wc86f == NULL)? 0x0: 0x1;
    // XOR_A_A;
    // LD_addr_A(wc819);
    wram->wc819 = 0x0;
    // LD_A_addr(wc870);
    // LD_C_A;
    data->bc = (b << 8) | wram->wc870;
    // CALL(aMobileAPI_SetTimer);
    MobileAPI_SetTimer(data);
    // LD_HL(wc829);
    // LD_A(0x80);
    // LD_hli_A;
    // LD_A(0xc8);
    // LD_hl_A;
    gMobileReceiveBuffer_Destination = &wram->wc880;
    // CALL(aFunction1104b0);
    Function1104b0();
    // LD_A_addr(wcb36);
    // LD_addr_A(wc86a);
    wram->wc86a = wram->wcb36;
    // XOR_A_A;
    data->a = 0x0;
    // JP(mFunction110432);
    Function110432();
    return 0x0;
}

// MobileAPI_09
void Function1105dd(mobile_api_data_s* data){
    // LD_A_addr(wc821);
    // BIT_A(0);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc86a);
    // CP_A(0x1);
    // JP_NZ (mFunction110226);
    if(bit_test(wram->wc821, 0) || wram->wc86a != 0x1)
        return Function110226();
    // XOR_A_A;
    // LDH_addr_A(rTAC);
    gb_write(rTAC, 0x0);
    // LD_A_addr(wc870);
    // LD_C_A;
    data->bc = wram->wc870;
    // CALL(aMobileAPI_SetTimer);
    MobileAPI_SetTimer(data);
    // LD_HL(wc98f);
    // LD_A(0x81);
    // LD_hli_A;
    // LD_A(0xc8);
    // LD_hli_A;
    gMobile_wc98f = &wram->wc881;
    // XOR_A_A;
    // LD_hli_A;
    wram->wc990 = 0x0;
    // LD_hli_A;
    wram->wc991 = 0x0;
    // LD_hli_A;
    wram->wc992 = 0x0;
    // LD_hl_A;
    wram->wc993 = 0x0;
    // LD_A(0xff);
    // LD_addr_A(wc86e);
    wram->wc86e = 0xff;
    // CALL(aFunction1104b0);
    Function1104b0();
    // LD_A(0xd);
    // LD_addr_A(wc86a);
    wram->wc86a = 0xd;
    // JP(mFunction110432);
    return Function110432();
}

void Function110615(uint8_t a){
    // LD_B(0x15);
    uint8_t b = 0x15;
    // LD_addr_A(wc86e);
    wram->wc86e = a;
    uint8_t* hl;
    // OR_A_A;
    // IF_Z goto asm_110625;
    if(a == 0) {
    // asm_110625:
        // LD_A(0x19);
        a = 0x19;
        // LD_HL(wc83e);
        hl = wram->wc83e;
        // goto asm_110631;
    }
    // DEC_A;
    // IF_Z goto asm_11062c;
    else if(a == 1) {
    // asm_11062c:
        // LD_A(0x6e);
        a = 0x6e;
        // LD_HL(wc852);
        hl = wram->wc852;
    }
    // DEC_A;
    // JP_Z (mFunction110615_asm_1106c1);
    else if(a == 2) {
    // asm_1106c1:
        // LD_B(0x50);
        b = 0x50;
        // LD_HL(wc876);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // LD_DE(0x0007);
        // ADD_HL_DE;
        uint8_t* hl2 = gMobile_wc876 + 0x0007;
        hl = hl2;
        // LD_DE(wc8ff);
        uint8_t* de = wram->wc8ff;

        do {
        // asm_1106d0:
            // LD_A_hli;
            uint8_t a = *(hl++);
            // LD_de_A;
            *de = a;
            // CP_A(0x2f);
            // IF_Z goto asm_1106da;
            if(a == '/')
                break;
            // INC_DE;
            de++;
            // DEC_B;
            // IF_NZ goto asm_1106d0;
        } while(--b != 0);

    // asm_1106da:
        // XOR_A_A;
        // LD_de_A;
        *de = 0x0;
        // DEC_HL;
        // LD_A_L;
        // LD_addr_A(wc876);
        // LD_A_H;
        // LD_addr_A(wc877);
        gMobile_wc876 = --hl;
        // LD_HL(wc8ff);
        hl = wram->wc8ff;
        // LD_A(0x50);
        a = 0x50;
        // LD_B(0x40);
        b = 0x40;
        // JP(mFunction110615_asm_110631);
        printf("DNS Query: %s %s\n", (const char*)wram->wc8ff, (const char*)hl2);
    }
    else {
        // RET;
        return;
    }


// asm_110631:
    // PUSH_HL;
    // PUSH_BC;
    // LD_addr_A(wMobileSDK_PacketBuffer + 91);
    wram->wMobileSDK_PacketBuffer[91] = a;
    // LD_HL(wc829);
    // LD_A(0x9d);
    // LD_hli_A;
    // LD_A(0xcb);
    // LD_hl_A;
    gMobileReceiveBuffer_Destination = wram->wMobileSDK_PacketBuffer + (0xcb9d - 0xcb47);
    // XOR_A_A;
    // LD_addr_A(wMobileSDK_PacketBuffer + 90);
    wram->wMobileSDK_PacketBuffer[90] = 0x0;
    // LD_addr_A(wc86b);
    wram->wc86b = 0x0;
    // LD_addr_A(wc9af);
    wram->wc9af = 0x0;
    // LD_DE(wMobileSDK_PacketBuffer + 80);
    // LD_HL(mMobilePacket_OpenTCPConnection);
    // LD_B(lengthof(MobilePacket_OpenTCPConnection));
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 80, MobilePacket_OpenTCPConnection, lengthof(MobilePacket_OpenTCPConnection));
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_DNSQuery);
    // LD_B(lengthof(MobilePacket_DNSQuery));
    // CALL(aMobileSDK_CopyBytes);
    char* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_DNSQuery, lengthof(MobilePacket_DNSQuery));
    // POP_BC;
    // POP_HL;
    // PUSH_DE;
    char* de2 = de;
    // INC_DE;
    de2++;
    // LD_A_B;
    // LD_BC(0);
    uint16_t bc = 0;
    // CALL(aMobileSDK_CopyStringLen);
    de2 = MobileSDK_CopyStringLen(de2, (const char*)hl, &bc, b);
    // LD_A_C;
    // POP_HL;
    // LD_hl_A;
    *de = LOW(bc);
    // LD_B_C;
    // CALL(aFunction111f63);
    bc = Function111f63(de2, LOW(bc));
    // LD_A_addr(wc86e);
    // CP_A(0x2);
    // IF_NZ goto asm_1106ac;
    // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 128);
    // OR_A_A;
    // IF_Z goto asm_1106ac;
    // LD_HL(wc995);
    // LD_A_hli;
    // CP_A(0x99);
    // IF_NZ goto asm_1106ac;
    // LD_A_hli;
    // CP_A(0x66);
    // IF_NZ goto asm_1106ac;
    // LD_A_hli;
    // CP_A(0x23);
    // IF_NZ goto asm_1106ac;
    if(wram->wc86e == 0x2
    && wram->wMobileSDK_ReceivePacketBuffer[128] != 0
    && wram->wc995[0] == 0x99
    && wram->wc995[1] == 0x66
    && wram->wc995[2] == 0x23) {
        // LD_A(0x2);
        // LD_addr_A(wc86e);
        wram->wc86e = 0x2;
        // DEC_A;
        // LD_addr_A(wc86b);
        wram->wc86b = 0x1;
        // LD_A(0xa3);
        // LD_DE(0x0010);
        // LD_HL(wc995);
        // CALL(aFunction111f02);
        Function111f02(wram->wc995, 0x0010, MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80);
        // LD_A(0xf);
        // LD_addr_A(wc86a);
        wram->wc86a = 0xf;
        // JP(mFunction110432);
        return Function110432();
    }

// asm_1106ac:
    // LD_HL(wMobileSDK_PacketBuffer);
    // LD_A(MOBILE_COMMAND_DNS_QUERY | 0x80);
    // LD_addr_A(wMobileSDK_SendCommandID);
    wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_DNS_QUERY | 0x80;
    // LD_B(0x5);
    // CALL(aPacketSendBytes);
    PacketSendBytes(wram->wMobileSDK_PacketBuffer, bc, 0x5);
    // LD_A(0xf);
    // LD_addr_A(wc86a);
    wram->wc86a = 0xf;
    // JP(mFunction110432);
    return Function110432();
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

// MobileAPI_12
void Function110a5b(mobile_api_data_s* data){
    // LD_A_addr(wc821);
    // BIT_A(2);
    // IF_Z goto asm_110a6d;
    if(bit_test(wram->wc821, 2)) {
        // LD_A_addr(wc86a);
        // CP_A(0x1a);
        // JP_NZ (mFunction110226);
        // JP(mFunction110af4);
        if(wram->wc86a == 0x1a)
            return Function110af4(data);
        return Function110226();
    }

// asm_110a6d:
    // BIT_A(0);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc86a);
    // CP_A(0x4);
    // JP_NZ (mFunction110226);
    if(bit_test(wram->wc821, 0) || wram->wc86a != 0x4)
        return Function110226();
    // LD_A_L;
    // OR_A_H;
    // JP_Z (mFunction110231);
    if(data->hl == NULL)
        return Function110231();
    // LD_A_L;
    // LD_addr_A(wc86e);
    // LD_A_H;
    // LD_addr_A(wc86f);
    gMobile_wc86e_wc86f = data->hl;
    wram->wc86e = (gMobile_wc86e_wc86f == NULL)? 0x0: 0x1;
    wram->wc86f = (gMobile_wc86e_wc86f == NULL)? 0x0: 0x1;
    // LD_HL(wc827);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobile_wc827 = data->de;
    // INC_DE;
    // INC_DE;
    data->de += 2;
    // DEC_BC;
    // DEC_BC;
    data->bc -= 2;
    // LD_HL(wc98f);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobile_wc98f = data->de;
    // LD_A_C;
    // LD_hli_A;
    wram->wc991 = LOW(data->bc);
    // LD_A_B;
    // LD_hl_A;
    wram->wc992 = HIGH(data->bc);
    // LD_HL(wc829);
    // LD_A(0x80);
    // LD_hli_A;
    // LD_A(0xc8);
    // LD_hli_A;
    gMobileReceiveBuffer_Destination = &wram->wc880;
    // LD_A(0x80);
    // LD_hli_A;
    wram->wc82b = 0x80;
    // XOR_A_A;
    // LD_hli_A;
    wram->wc82c = 0x0;
    // XOR_A_A;
    // LD_hli_A;
    wram->wc82d = 0x0;
    // LD_hli_A;
    wram->wc82e = 0x0;
    // XOR_A_A;
    // LD_addr_A(wc86b);
    wram->wc86b = 0x0;
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_TransferData);
    // LD_B(0x5);
    // CALL(aMobileSDK_CopyBytes);
    char* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_TransferData, 0x5);
    // LD_A(0xd);
    // LD_de_A;
    // INC_DE;
    *(de++) = '\r';
    // LD_A_addr(wc86c);
    // LD_de_A;
    *(de++) = wram->wc86c;
    // INC_DE;
    // LD_BC(0x0001);
    uint16_t bc = 0x0001;
    // LD_HL(mUnknown_1120e8);
    // CALL(aMobileSDK_CopyString);
    MobileSDK_CopyString(de, Unknown_1120e8, &bc);
    // LD_DE(wMobileSDK_PacketBuffer + 12);
    // LD_HL(wc86e);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint16_t hl = gMobile_wc86e_wc86f[0] | (gMobile_wc86e_wc86f[1] << 8);
    // CALL(aFunction110d37);
    de = Function110d37(de, hl);
    // LD_B_C;
    // CALL(aFunction111f63);
    uint16_t size = Function111f63(de, LOW(bc));
    // LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    // LD_addr_A(wMobileSDK_SendCommandID);
    wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_TRANSFER_DATA | 0x80;
    // LD_HL(wMobileSDK_PacketBuffer);
    // LD_B(0x5);
    // CALL(aPacketSendBytes);
    PacketSendBytes(wram->wMobileSDK_PacketBuffer, size, 0x5);
    // LD_A(0x1a);
    // LD_addr_A(wc86a);
    wram->wc86a = 0x1a;
    // JP(mFunction110432);
    Function110432();
}

void Function110af4(mobile_api_data_s* data){
    // LD_HL(wc827);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobile_wc827 = data->de;
    // INC_DE;
    // INC_DE;
    data->de += 2;
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobileReceiveBuffer_Destination = data->de;
    // LD_E_hl;
    uint8_t e = wram->wc82b;
    // LD_A_B;
    // OR_A_C;
    // LD_addr_A(wc86e);
    // LD_addr_A(wc86f);
    // IF_Z goto asm_110b5c;
    if(data->bc != 0) {
        // DEC_BC;
        // DEC_BC;
        data->bc -= 2;
        // LD_A_addr(wc993);
        // OR_A_A;
        // JP_NZ (mFunction110af4_asm_110bd5);
        if(wram->wc993 != 0) {
        // asm_110bd5:
            // LD_E_A;
            // XOR_A_A;
            // CP_A_B;
            // IF_NZ goto asm_110c05;
            // LD_A_E;
            // CP_A_C;
            // IF_C goto asm_110c05;
            if(data->bc <= e) {
                // LD_B_C;
                // LD_HL(wc993);
                // LD_A_hl;
                // SUB_A_C;
                // LD_hl_A;
                wram->wc993 -= LOW(data->bc);
                // LD_A(0x80);
                // SUB_A_E;
                // LD_E_A;
                // LD_D(0);
                // LD_HL(wc880);
                // ADD_HL_DE;
                // LD_A_addr(wc829);
                // LD_E_A;
                // LD_A_addr(wc82a);
                // LD_D_A;
                // CALL(aMobileSDK_CopyBytes);
                data->de = MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wc880_str + (0x80 - e), LOW(data->bc));
                // LD_HL(wc827);
                // LD_A_hli;
                // LD_H_hl;
                // LD_L_A;
                // LD_A_C;
                // LD_hli_A;
                gMobile_wc827[0] = LOW(data->bc);
                // XOR_A_A;
                // LD_hl_A;
                gMobile_wc827[1] = 0x0;
                // RET;
                return;
            }

        // asm_110c05:
            // PUSH_HL;
            // PUSH_BC;
            // LD_A_addr(wc993);
            // LD_B_A;
            // LD_A(0x80);
            // SUB_A_E;
            // LD_E_A;
            // LD_D(0);
            // LD_HL(wc880);
            // ADD_HL_DE;
            // LD_A_addr(wc829);
            // LD_E_A;
            // LD_A_addr(wc82a);
            // LD_D_A;
            // CALL(aMobileSDK_CopyBytes);
            // LD_A_E;
            // LD_addr_A(wc829);
            // LD_A_D;
            // LD_addr_A(wc82a);
            gMobileReceiveBuffer_Destination = MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wc880_str + (0x80 - e), wram->wc993);
            // POP_BC;
            // LD_A_addr(wc993);
            // LD_E_A;
            // LD_A_C;
            // SUB_A_E;
            // LD_C_A;
            // LD_A_B;
            // SBC_A(0x0);
            // LD_B_A;
            data->bc -= wram->wc993;
            // LD_A_addr(wc994);
            // LD_E_A;
            e = wram->wc994;
            // POP_HL;
            // JP(mFunction110af4_asm_110b1c);
        }
        // LD_A_addr(wc994);
        // OR_A_A;
        // IF_Z goto asm_110b1c;
        else if(wram->wc994 != HTTP_METHOD_GET) {
            // LD_E_A;
            e = wram->wc994;
        }

    // asm_110b1c:
        // XOR_A_A;
        // LD_addr_A(wc994);
        wram->wc994 = HTTP_METHOD_GET;
        // CP_A_B;
        // IF_NZ goto asm_110b5c;
        // LD_A_E;
        // CP_A_C;
        // IF_C goto asm_110b5c;
        if(data->bc <= e) {
            // PUSH_BC;
            uint16_t bc = data->bc;
            uint8_t c = data->bc;
            // SUB_A_C;
            // LD_hl_A;
            wram->wc82b = e - c;
            // LD_B_C;
            // LD_HL(wc82d);
            // LD_A_addr(wc993);
            // ADD_A_C;
            // LD_hli_A;
            wram->wc82d = wram->wc993 + c;
            uint8_t carry = (wram->wc993 + c > 0xff)? 1: 0;
            // LD_A_B;
            // ADC_A(0);
            // LD_hl_A;
            wram->wc82e = c + carry;
            // XOR_A_A;
            // LD_addr_A(wc993);
            wram->wc993 = 0x0;
            // LD_HL(wMobileSDK_ReceivePacketBuffer + 3);
            // LD_A_hli;
            // INC_HL;
            // SUB_A_E;
            // DEC_A;
            // LD_E_A;
            // LD_D(0);
            // ADD_HL_DE;
            // LD_A_addr(wc829);
            // LD_E_A;
            // LD_A_addr(wc82a);
            // LD_D_A;
            // CALL(aMobileSDK_CopyBytes);
            data->de = MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wMobileSDK_ReceivePacketBuffer + 5 + (wram->wMobileSDK_ReceivePacketBuffer[3] - e - 1), c);
            // POP_BC;
            // LD_HL(wc827);
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            uint8_t* hl = gMobile_wc827;
            // LD_A_C;
            // LD_hli_A;
            *(hl++) = LOW(bc);
            // LD_hl_B;
            *(hl++) = HIGH(bc);
            // RET;
            return;
        }
    }

// asm_110b5c:
    // LD_A_C;
    // SUB_A_E;
    // LD_C_A;
    // LD_A_B;
    // SBC_A(0x0);
    // LD_B_A;
    data->bc -= e;
    // LD_A_C;
    // LD_hli_A;
    wram->wc82b = LOW(data->bc);
    // LD_hl_B;
    wram->wc82e = HIGH(data->bc);
    // LD_HL(wc82d);
    // LD_A_addr(wc993);
    // ADD_A_E;
    // LD_hli_A;
    // LD_A(0);
    // ADC_A(0);
    // LD_hl_A;
    uint16_t c82d = wram->wc82d | (wram->wc82e << 8);
    c82d += e;
    wram->wc82d = LOW(c82d);
    wram->wc82e = HIGH(c82d);
    // XOR_A_A;
    // LD_addr_A(wc993);
    wram->wc993 = 0x0;
    // LD_A_addr(wc86e);
    // OR_A_A;
    // IF_Z goto asm_110b9b;
    if(wram->wc86e != 0) {
        // LD_B_E;
        // LD_HL(wMobileSDK_ReceivePacketBuffer + 3);
        // LD_A_hli;
        // INC_HL;
        // SUB_A_E;
        // DEC_A;
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // LD_A_addr(wc829);
        // LD_E_A;
        // LD_A_addr(wc82a);
        // LD_D_A;
        // CALL(aMobileSDK_CopyBytes);
        data->de = MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wMobileSDK_ReceivePacketBuffer + 5 + (wram->wMobileSDK_ReceivePacketBuffer[3] - e - 1), e);
        // LD_HL(wc829);
        // LD_A_E;
        // LD_hli_A;
        // LD_A_D;
        // LD_hl_A;
        gMobileReceiveBuffer_Destination = data->de;
    }

// asm_110b9b:
    // CALL(aFunction1127f3);
    // IF_Z goto asm_110bbb;
    if(!Function1127f3()) {
        // NOP;
        // LD_HL(wc821);
        // RES_hl(2);
        bit_reset(wram->wc821, 2);
        // LD_A(0x1);
        // LD_addr_A(wc86b);
        // LD_DE(0x000b);
        // LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
        // LD_addr_A(wMobileSDK_SendCommandID);
        wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_TRANSFER_DATA | 0x80;
        // LD_HL(wMobileSDK_PacketBuffer + 128);
        // LD_B(0x5);
        // JP(mPacketSendBytes);
        PacketSendBytes(wram->wMobileSDK_PacketBuffer + 128, 0x000b, 0x5);
        return;
    }

// asm_110bbb:
    // LD_A(0x4);
    // LD_addr_A(wc86a);
    wram->wc86a = 0x4;
    // LD_HL(wc821);
    // RES_hl(0);
    // RES_hl(2);
    wram->wc821 &= ~((1 << 0) | (1 << 2));
    // LD_HL(wc827);
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    // LD_HL(wc82d);
    // LD_B(0x2);
    // JP(mMobileSDK_CopyBytes);
    data->de = MobileSDK_CopyBytes(gMobile_wc827, &wram->wc82d, 0x2);
    return;
}

// MobileAPI_13
void Function110c3c(mobile_api_data_s* data){
    // LD_A_addr(wc821);
    // BIT_A(0);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc86a);
    // CP_A(0x4);
    // JP_NZ (mFunction110226);
    if(bit_test(wram->wc821, 0) || wram->wc86a != 0x4)
        return Function110226();
    // LD_A_L;
    // OR_A_H;
    // JP_Z (mFunction110231);
    if(data->hl == NULL)
        return Function110231();
    // LD_A_L;
    // LD_addr_A(wc86e);
    // LD_A_H;
    // LD_addr_A(wc86f);
    gMobile_wc86e_wc86f = data->hl;
    wram->wc86e = (gMobile_wc86e_wc86f == NULL)? 0x0: 0x1;
    wram->wc86f = (gMobile_wc86e_wc86f == NULL)? 0x0: 0x1;
    // CALL(aFunction112729);
    Function112729();
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_TransferData);
    // LD_B(0x5);
    // CALL(aMobileSDK_CopyBytes);
    char* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_TransferData, 0x5);
    // LD_A(0xd);
    // LD_de_A;
    // INC_DE;
    *(de++) = '\r';
    // LD_A_addr(wc86c);
    // LD_de_A;
    // INC_DE;
    *(de++) = wram->wc86c;
    // LD_BC(0x0001);
    uint16_t bc = 0x0001;
    // LD_HL(mUnknown_1120f5);
    // CALL(aMobileSDK_CopyString);
    MobileSDK_CopyString(de, Unknown_1120f5, &bc);
    // LD_DE(wMobileSDK_PacketBuffer + 12);
    // LD_HL(wc86e);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aFunction110d37);
    de = Function110d37((char*)wram->wMobileSDK_PacketBuffer + 12, gMobile_wc86e_wc86f[0] | (gMobile_wc86e_wc86f[1] << 8));
    // LD_B_C;
    // CALL(aFunction111f63);
    uint16_t size = Function111f63(de, LOW(bc));
    // LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    // LD_addr_A(wMobileSDK_SendCommandID);
    wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_TRANSFER_DATA | 0x80;
    // LD_HL(wMobileSDK_PacketBuffer);
    // LD_B(0x5);
    // CALL(aPacketSendBytes);
    PacketSendBytes(wram->wMobileSDK_PacketBuffer, size, 0x5);
    // LD_A(0x1b);
    // LD_addr_A(wc86a);
    wram->wc86a = 0x1b;
    // JP(mFunction110432);
    return Function110432();
}

// MobileAPI_14
void Function110c9e(mobile_api_data_s* data){
    // LD_A_addr(wc821);
    // BIT_A(2);
    // IF_Z goto asm_110cb0;
    if(bit_test(wram->wc821, 2)) {
        // LD_A_addr(wc86a);
        // CP_A(0x1c);
        // JP_NZ (mFunction110226);
        if(wram->wc86a != 0x1c)
            return Function110226();
        // JP(mFunction110af4);
        return Function110af4(data);
    }

// asm_110cb0:
    // BIT_A(0);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc86a);
    // CP_A(0x4);
    // JP_NZ (mFunction110226);
    if(bit_test(wram->wc821, 0) || wram->wc86a != 0x4)
        return Function110226();
    // LD_A_L;
    // OR_A_H;
    // JP_Z (mFunction110231);
    if(data->hl == NULL)
        return Function110231();
    // LD_A_L;
    // LD_addr_A(wc86e);
    // LD_A_H;
    // LD_addr_A(wc86f);
    gMobile_wc86e_wc86f = data->hl;
    // LD_HL(wc827);
    char* de = data->de;
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobile_wc827 = (uint8_t*)de;
    // INC_DE;
    // INC_DE;
    de += 2;
    // DEC_BC;
    // DEC_BC;
    data->bc -= 2;
    // LD_HL(wc98f);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobile_wc98f = (uint8_t*)de;
    // LD_A_C;
    // LD_hli_A;
    wram->wc990 = LOW(data->bc);
    // LD_A_B;
    // LD_hl_A;
    wram->wc991 = HIGH(data->bc);
    // LD_HL(wc829);
    // LD_A(0x80);
    // LD_hli_A;
    // LD_A(0xc8);
    // LD_hli_A;
    gMobileReceiveBuffer_Destination = &wram->wc880;
    // LD_A(0x80);
    // LD_hli_A;
    wram->wc82b = 0x80;
    // XOR_A_A;
    // LD_hli_A;
    wram->wc82c = 0x0;
    // XOR_A_A;
    // LD_hli_A;
    wram->wc82d = 0x0;
    // LD_hli_A;
    wram->wc82e = 0x0;
    // XOR_A_A;
    // LD_addr_A(wc86b);
    wram->wc86b = 0x0;
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_TransferData);
    // LD_B(0x5);
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_TransferData, 0x5);
    // LD_A(0xe);
    // LD_de_A;
    // INC_DE;
    *(de++) = 0xe;
    // LD_A_addr(wc86c);
    // LD_de_A;
    // INC_DE;
    *(de++) = wram->wc86c;
    // LD_BC(0x0001);
    uint16_t bc = 0x0001;
    // LD_HL(mUnknown_112102);
    // CALL(aMobileSDK_CopyString);
    de = MobileSDK_CopyString(de, Unknown_112102, &bc);
    // LD_DE(wMobileSDK_PacketBuffer + 11);
    // LD_HL(wc86e);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aFunction110d37);
    de = Function110d37((char*)wram->wMobileSDK_PacketBuffer + 11, (gMobile_wc86e_wc86f[0] | (gMobile_wc86e_wc86f[1] << 8)));
    // LD_B_C;
    // CALL(aFunction111f63);
    Function111f63(de, LOW(bc));
    // LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    // LD_addr_A(wMobileSDK_SendCommandID);
    wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_TRANSFER_DATA | 0x80;
    // LD_HL(wMobileSDK_PacketBuffer);
    // LD_B(0x5);
    // CALL(aPacketSendBytes);
    PacketSendBytes(wram->wMobileSDK_PacketBuffer, LOW(bc), 0x5);
    // LD_A(0x1c);
    // LD_addr_A(wc86a);
    wram->wc86a = 0x1c;
    // JP(mFunction110432);
    return Function110432();
}

// PrintNumber?
char* Function110d37(char* de, uint16_t hl){
    // PUSH_BC;
    // PUSH_DE;
    char* start = de;
    // LD_B(0);
    char b = 0;

// check_under_10k:
    // LD_A(HIGH(10000));
    // CP_A_H;
    // IF_C goto subtract_10k;
    // IF_NZ goto done_10k;
    // LD_A(LOW(10000));
    // CP_A_L;
    // IF_Z goto subtract_10k;
    // IF_NC goto done_10k;

    while(hl >= 10000) {
    // subtract_10k:
        // INC_B;
        b++;
        // LD_A_B;
        // LD_BC(-10000);
        // ADD_HL_BC;
        hl -= 10000;
        // LD_B_A;
        // goto check_under_10k;
    }


// done_10k:
    // LD_A(0x30);
    // OR_A_B;
    // LD_de_A;
    // INC_DE;
    *(de++) = '0' + b;
    // LD_B(0);
    b = 0;

// check_under_1k:
    // LD_A(HIGH(1000));
    // CP_A_H;
    // IF_C goto subtract_1k;
    // IF_NZ goto done_1k;
    // LD_A(LOW(1000));
    // CP_A_L;
    // IF_Z goto subtract_1k;
    // IF_NC goto done_1k;

    while(hl >= 1000) {
    // subtract_1k:
        // INC_B;
        b++;
        // LD_A_B;
        // LD_BC(-1000);
        // ADD_HL_BC;
        hl -= 1000;
        // LD_B_A;
        // goto check_under_1k;
    }

// done_1k:
    // LD_A(0x30);
    // OR_A_B;
    // LD_de_A;
    // INC_DE;
    *(de++) = '0' + b;
    // LD_B(0);
    b = 0;

// check_under_100:
    // LD_A(HIGH(100));
    // CP_A_H;
    // IF_NZ goto subtract_100;
    // LD_A(LOW(100));
    // CP_A_L;
    // IF_Z goto subtract_100;
    // IF_NC goto check_under_10;

    while(hl >= 100) {
    // subtract_100:
        // INC_B;
        b++;
        // LD_A_B;
        // LD_BC(-100);
        // ADD_HL_BC;
        hl -= 100;
        // LD_B_A;
        // goto check_under_100;
    }

// check_under_10:
    // LD_A(0x30);
    // OR_A_B;
    // LD_de_A;
    *(de++) = '0' + b;
    // INC_DE;
    // LD_B(0x0);
    b = 0;
    // LD_A_L;

    while(hl >= 10) {
    // subtract_10:
        // CP_A(10);
        // IF_C goto done_10;
        // SUB_A(10);
        hl -= 10;
        // INC_B;
        b++;
        // goto subtract_10;
    }

// done_10:
    // LD_L_A;
    // LD_A(0x30);
    // OR_A_B;
    // LD_de_A;
    // INC_DE;
    *(de++) = '0' + b;
    // LD_A(0x30);
    // OR_A_L;
    // LD_de_A;
    *de = '0' + LOW(hl);
    // POP_DE;
    de = start;
    // LD_L_E;
    // LD_H_D;
    // LD_B(0x5);
    b = 0x5;

    do {
    // find_first_digit:
        // LD_A_hl;
        // CP_A(0x30);
        // IF_NZ goto found_first_digit;
        if(*start != '0') {
        // found_first_digit:
            // LD_A(0x5);
            // CP_A_B;
            // IF_Z goto done;
            if(b == 0x5)
                break;
            // SUB_A_B;
            // LD_C_A;
            // LD_A_addr(wMobileSDK_PacketBuffer + 5);
            // SUB_A_C;
            // LD_C_A;
            // LD_addr_A(wMobileSDK_PacketBuffer + 5);
            wram->wMobileSDK_PacketBuffer[5] -= 0x5 - b;
            // PUSH_HL;
            char* hl2 = start;
            // LD_B(0x1);
            b = 0x1;

            char a;
            do {
            // penultimate_loop:
                // INC_B;
                // LD_A_hli;
                a = *(hl2++);
                // CP_A(0xd);
                // IF_NZ goto penultimate_loop;
            } while(a != '\r');
            // POP_HL;
            // CALL(aMobileSDK_CopyBytes);
            de = MobileSDK_CopyBytes(de, start, b);
            // POP_HL;
            // RET;
            return de;
        }
        // INC_HL;
        start++;
        // DEC_B;
        // IF_NZ goto find_first_digit;
    } while(--b != 0);
    // goto done;

// done:
    // POP_BC;

    char a;
    do {
    // last_loop:
        // LD_A_de;
        // INC_DE;
        a = *(de++);
        // CP_A(0xa);
        // IF_NZ goto last_loop;
    } while(a != '\n');
    // RET;
    return de;
}

// MobileAPI_15
void Function110ddd(mobile_api_data_s* data){
    // LD_A_addr(wc821);
    // BIT_A(2);
    // LD_A_addr(wc86a);
    // IF_Z goto asm_110e00;
    if(bit_test(wram->wc821, 2)) {
        // CP_A(0x13);
        // JP_Z (mFunction111044);
        // CP_A(0x1f);
        // JP_Z (mFunction111044);
        // CP_A(0x21);
        // JP_Z (mFunction111044);
        if(wram->wc86a == 0x13 || wram->wc86a == 0x1f || wram->wc86a == 0x21)
            return Function111044(data);
        // JP(mFunction110226);
        return Function110226();

    // asm_110df9:
        // POP_HL;

    // asm_110dfa:
        // POP_HL;
        // POP_HL;
        // POP_HL;

    asm_110dfd:
        // JP(mFunction110231);
        return Function110231();
    }

asm_110e00:
    // CP_A(0x2);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc821);
    // BIT_A(0);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc86d);
    // OR_A_A;
    // JP_NZ (mFunction110226);
    if(wram->wc86a != 0x2 || bit_test(wram->wc821, 0) || wram->wc86d != 0)
        return Function110226();
    // LD_A_L;
    // LD_addr_A(wc9b5);
    // LD_A_H;
    // LD_addr_A(wc9b6);
    gMobile_wc9b5 = data->hl;
    // XOR_A_A;
    // LD_addr_A(wc989);
    wram->wc989 = 0x0;
    // LD_addr_A(wc9a5);
    wram->wc9a5[0] = 0x0;
    // LD_addr_A(wc98a);
    wram->wc98a = 0x0;
    // LD_addr_A(wc993);
    wram->wc993 = 0x0;
    // LD_A_hli;
    // LD_addr_A(wc833);
    // LD_A_hli;
    // LD_addr_A(wc834);
    gMobile_wc833_wc834 = GBToRAMAddr((gMobile_wc9b5[0] | (gMobile_wc9b5[1] << 8)));
    uint16_t addr = (gMobile_wc9b5[2] | (gMobile_wc9b5[3] << 8));
    char* hl = GBToRAMAddr(addr);
    // INC_HL;
    // INC_HL;
    // LD_A_L;
    // LD_addr_A(wc97f);
    // LD_A_H;
    // LD_addr_A(wc980);
    gMobile_wc97f_wc980 = (uint8_t*)gMobile_wc9b5 + 4;
    // DEC_HL;
    // DEC_HL;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A(0x80);
    // CP_A_L;
    // IF_NZ goto asm_110e4a;
    // LD_A(0xc8);
    // CP_A_H;
    // IF_Z goto asm_110dfd;
    if(addr == 0xc880)
        goto asm_110dfd;
// asm_110e4a:
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // PUSH_HL;
    char* hl2 = hl;
    // LD_B(sizeof(URIPrefix));
    uint8_t b = sizeof(URIPrefix) - 1;
    // LD_DE(mURIPrefix);
    const char* de = URIPrefix;

    do {
    // asm_110e53:
        // LD_A_de;
        // INC_DE;
        // CP_A_hl;
        // IF_NZ goto asm_110df9;
        if(*de != *hl2)
            goto asm_110dfd;
        // INC_HL;
        hl2++, de++;
        // DEC_B;
        // IF_NZ goto asm_110e53;
    } while(--b != 0);
    // PUSH_HL;
    char* hl3 = hl2;
    // LD_B(lengthof(HTTPUploadURL));
    b = lengthof(HTTPUploadURL);
    // LD_C(0x0);
    uint8_t c = 0x0;
    // LD_DE(mHTTPUploadURL);
    de = HTTPUploadURL;

    do {
    // asm_110e64:
        // LD_A_de;
        // INC_DE;
        // CP_A_hl;
        // IF_NZ goto asm_110e70;
        if(*de != *hl3)
            goto asm_110e70;
        // INC_HL;
        de++, hl3++;
        // DEC_B;
        // IF_NZ goto asm_110e64;
    } while(--b != 0);
    // POP_HL;
    // goto asm_110df9;
    goto asm_110dfd;

asm_110e70:
    // POP_HL;
    // PUSH_HL;
    hl3 = hl2;
    // LD_B(lengthof(HTTPRankingURL));
    b = sizeof(HTTPRankingURL) - 1;
    // LD_C(0x0);
    c = 0x0;
    // LD_DE(mHTTPRankingURL);
    de = HTTPRankingURL;

    do {
    // asm_110e79:
        // LD_A_de;
        // INC_DE;
        // CP_A_hl;
        // IF_NZ goto asm_110e86;
        if(*de != *hl3)
            goto asm_110e86;
        // INC_HL;
        hl3++, de++;
        // DEC_B;
        // IF_NZ goto asm_110e79;
    } while(--b != 0);
    // POP_HL;
    // JP(mFunction110ddd_asm_110df9);
    goto asm_110dfd;

asm_110e86:
    // POP_HL;
    // PUSH_HL;
    hl3 = hl2;
    // LD_B(sizeof(HTTPUtilityURL));
    b = sizeof(HTTPUtilityURL) - 1;
    // LD_C(0x0);
    c = 0x0;
    // LD_DE(mHTTPUtilityURL);
    de = HTTPUtilityURL;

    do {
    // asm_110e8f:
        // LD_A_de;
        // INC_DE;
        // CP_A_hl;
        // IF_NZ goto asm_110ea2;
        if(*de != *hl3) {
        // asm_110ea2:
            // POP_HL;
            hl3 = hl2;
            // LD_B(sizeof(HTTPDownloadURL));
            b = sizeof(HTTPDownloadURL) - 1;
            // LD_C(0x0);
            c = 0x0;
            // LD_DE(mHTTPDownloadURL);
            de = HTTPDownloadURL;

            do {
            // asm_110eaa:
                // LD_A_de;
                // INC_DE;
                // CP_A_hl;
                // IF_NZ goto asm_110ecb;
                if(*de != *hl3)
                    goto asm_110ecb;
                // INC_HL;
                hl3++, de++;
                // DEC_B;
                // IF_NZ goto asm_110eaa;
            } while(--b != 0);
            goto asm_110eb3;
        }
        // INC_HL;
        hl3++, de++;
        // DEC_B;
        // IF_NZ goto asm_110e8f;
    } while(--b != 0);
    // POP_HL;
    hl3 = hl2;
    // LD_A(0x1);
    // LD_addr_A(wc98a);
    wram->wc98a = 0x1;
    // LD_C(0x1);
    c = 0x1;
    // goto asm_110eb3;

asm_110eb3:
    // LD_HL(wc97f);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    char* hl4 = (char*)gMobile_wc97f_wc980;
    // LD_C(0x12);
    // CALL(aFunction11039a);
    // JP_C (mFunction110ddd_asm_110df9);
    if(Function11039a(&hl4, 0x12))
        goto asm_110dfd;
    // LD_C(0x12);
    // CALL(aFunction11039a);
    // JP_C (mFunction110ddd_asm_110df9);
    if(Function11039a(&hl4, 0x12))
        goto asm_110dfd;
    // LD_C(0x1);
    c = 0x1;

asm_110ecb:
    // LD_A_C;
    // LD_addr_A(wc98f);
    wram->wc98f = c;
    // LD_addr_A(wMobileSDK_ReceivePacketBuffer + 128);
    wram->wMobileSDK_ReceivePacketBuffer[128] = c;
    // POP_HL;
    // CALL(aFunction1111d7);
    uint16_t bc = Function1111d7(hl2);
    // LD_A_B;
    // CP_A(0x4);
    // IF_C goto asm_110ee3;
    // JP_NZ (mFunction110ddd_asm_110dfa);
    // XOR_A_A;
    // OR_A_C;
    // JP_NZ (mFunction110ddd_asm_110dfa);
    if(bc >= 0x400)
        goto asm_110dfd;

asm_110ee3:
    // LD_HL(wc98b);
    // XOR_A_A;
    // LD_hli_A;
    wram->wc98b = 0x0;
    // LD_hli_A;
    wram->wc98c = 0x0;
    // LD_hli_A;
    wram->wc98d = 0x0;
    // LD_hl_A;
    wram->wc98e = 0x0;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // LD_A_L;
    // LD_addr_A(wc876);
    // LD_A_H;
    // LD_addr_A(wc877);
    gMobile_wc876 = (uint8_t*)hl;
    // LD_HL(wc872);
    // LD_A_C;
    // LD_hli_A;
    wram->wc872 = LOW(data->bc);
    // LD_A_B;
    // LD_hli_A;
    wram->wc873 = HIGH(data->bc);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobile_wc874_wc875 = data->de;
    // INC_HL;
    // INC_HL;
    hl += 2;
    // XOR_A_A;
    // LD_addr_A(wc994);
    wram->wc994 = HTTP_METHOD_GET;

    return Function110f07();
}

void Function110f07(void){
    // LD_HL(wc833);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl = gMobile_wc833_wc834;
    // OR_A_H;
    // IF_Z goto asm_110f12;
    if(hl != NULL) {
        // XOR_A_A;
        // LD_hl_A;
        *hl = 0;
    }

// asm_110f12:
    // LD_HL(wc991);
    // XOR_A_A;
    // LD_hli_A;
    wram->wc991 = 0x0;
    // LD_hl_A;
    wram->wc992 = 0x0;
    // LD_HL(wc866);
    // LD_A_hli;
    // OR_A_hl;
    // INC_HL;
    // OR_A_hl;
    // INC_HL;
    // OR_A_hl;
    // IF_NZ goto asm_110f28;
    if((wram->wc866[0] | wram->wc866[1] | wram->wc866[2] | wram->wc866[3]) == 0) {
        // LD_A(0x2);
        // JP(mFunction110615);
        return Function110615(0x2);
    }

// asm_110f28:
    // LD_A(0x2);
    // LD_addr_A(wc86e);
    wram->wc86e = 0x2;
    // LD_A(0x1f);
    // LD_addr_A(wMobileSDK_PacketBuffer + 10);
    wram->wMobileSDK_PacketBuffer[10] = 0x1f;
    // LD_A(0x90);
    // LD_addr_A(wMobileSDK_PacketBuffer + 11);
    wram->wMobileSDK_PacketBuffer[11] = 0x90;
    // LD_A(0x1);
    // LD_addr_A(wc86b);
    wram->wc86b = 0x1;
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_OpenTCPConnection);
    // LD_B(0x6);
    // CALL(aMobileSDK_CopyBytes);
    uint8_t* de3 = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_OpenTCPConnection, sizeof(MobilePacket_OpenTCPConnection));
    // LD_HL(wc866);
    // LD_B(0x4);
    // CALL(aMobileSDK_CopyBytes);
    de3 = MobileSDK_CopyBytes(de3, wram->wc866, 0x4);
    // INC_DE;
    // INC_DE;
    // LD_B(0x6);
    // CALL(aFunction111f63);
    Function111f63(de3 + 2, 0x6);
    // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 128);
    // OR_A_A;
    // IF_Z goto asm_110f95;
    if(wram->wMobileSDK_ReceivePacketBuffer[128] != 0) {
        // LD_HL(wc995);
        // LD_A_hli;
        // CP_A(0x99);
        // IF_NZ goto asm_110f8a;
        // LD_A_hli;
        // CP_A(0x66);
        // IF_NZ goto asm_110f8a;
        // LD_A_hli;
        // CP_A(0x23);
        // IF_NZ goto asm_110f8a;
        if(wram->wc995[0] == 0x99
        && wram->wc995[1] == 0x66
        && wram->wc995[2] == MOBILE_COMMAND_OPEN_TCP_CONNECTION) {
            // LD_A(0x2);
            // LD_addr_A(wc86e);
            wram->wc86e = 0x2;
            // DEC_A;
            // LD_addr_A(wc86b);
            wram->wc86b = 0x1;
            // LD_A(0xa3);
            // LD_DE(0x0010);
            // LD_HL(wc995);
            // CALL(aFunction111f02);
            Function111f02(wram->wc995, 0x0010, MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80);
            // LD_A(0xf);
            // LD_addr_A(wc86a);
            wram->wc86a = 0xf;
            // JP(mFunction110432);
            return Function110432();
        }
        else {
        // asm_110f8a:
            // LD_HL(wMobileSDK_PacketBuffer);
            // LD_DE(wc995);
            // LD_B(0x10);
            // CALL(aMobileSDK_CopyBytes);
            MobileSDK_CopyBytes(wram->wc995, wram->wMobileSDK_PacketBuffer, 0x10);
        }
    }

// asm_110f95:
    // LD_DE(0x0010);
    // LD_HL(wMobileSDK_PacketBuffer);
    // LD_A(MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80);
    // LD_addr_A(wMobileSDK_SendCommandID);
    wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80;
    // LD_B(0x5);
    // CALL(aPacketSendBytes);
    PacketSendBytes(wram->wMobileSDK_PacketBuffer, 0x0010, 0x5);
    // LD_A(0xf);
    // LD_addr_A(wc86a);
    wram->wc86a = 0xf;
    // JP(mFunction110432);
    return Function110432();
}

void Function111044(mobile_api_data_s* data){
    uint8_t* de = data->de;
    // LD_HL(wc827);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobile_wc827 = de;
    // INC_DE;
    // INC_DE;
    de += 2;
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobileReceiveBuffer_Destination = de;
    // LD_E_hl;
    uint8_t e = wram->wc82b;
    // LD_A_B;
    // OR_A_C;
    uint8_t b_or_c = HIGH(data->bc) | LOW(data->bc);
    // LD_addr_A(wc86e);
    // LD_addr_A(wc86f);
    wram->wc86f = wram->wc86e = b_or_c;
    // DEC_BC;
    // DEC_BC;
    data->bc -= 2;
    // JP_Z (mFunction1111ca);
    if(b_or_c == 0)
        return Function1111ca();
    // LD_A_addr(wc991);
    // OR_A_A;
    // CALL_NZ (aFunction11115f);
    if(wram->wc991 != 0)
        e = Function11115f(&data->bc, wram->wc991);
    // XOR_A_A;
    // CP_A_E;
    // JP_Z (mFunction111044_asm_1110eb);
    if(e != 0) {
        // XOR_A_A;
        // CP_A_B;
        // IF_NZ goto asm_1110ac;
        // LD_A_E;
        // CP_A_C;
        // IF_C goto asm_1110ac;
        if(data->bc <= e) {
            // PUSH_BC;
            // SUB_A_C;
            // LD_hl_A;
            wram->wc82b = e - data->bc;
            // LD_B_C;
            // LD_HL(wc82d);
            // LD_A_C;
            // LD_hli_A;
            wram->wc82d = LOW(data->bc);
            // XOR_A_A;
            // LD_hl_A;
            wram->wc82e = 0x0;
            // LD_HL(wMobileSDK_ReceivePacketBuffer + 3);
            // LD_A_hli;
            // INC_HL;
            // SUB_A_E;
            // DEC_A;
            // LD_E_A;
            // LD_D(0);
            // ADD_HL_DE;
            // LD_A_addr(wc829);
            // LD_E_A;
            // LD_A_addr(wc82a);
            // LD_D_A;
            // CALL(aMobileSDK_CopyBytes);
            MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wMobileSDK_ReceivePacketBuffer + 5 + (wram->wMobileSDK_ReceivePacketBuffer[3] - e - 1), LOW(data->bc));
            // POP_BC;
            // LD_A_addr(wc991);
            // LD_L_A;
            // LD_H(0);
            // ADD_HL_BC;
            // LD_C_L;
            // LD_B_H;
            data->bc += wram->wc991;
            // XOR_A_A;
            // LD_addr_A(wc991);
            wram->wc991 = 0x0;
            // LD_HL(wc827);
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // LD_A_C;
            // LD_hli_A;
            gMobile_wc827[0] = LOW(data->bc);
            // LD_hl_B;
            gMobile_wc827[1] = HIGH(data->bc);
            // RET;
            return;
        }

    // asm_1110ac:
        // LD_A_C;
        // SUB_A_E;
        // LD_C_A;
        // LD_A_B;
        // SBC_A(0x0);
        // LD_B_A;
        data->bc -= e;
        // LD_A_C;
        // LD_hli_A;
        wram->wc82b = LOW(data->bc);
        // LD_hl_B;
        wram->wc82c = HIGH(data->bc);
        // LD_HL(wc82d);
        // LD_A_addr(wc991);
        // ADD_A_E;
        // LD_hli_A;
        wram->wc82d = LOW(wram->wc991 + e);
        // LD_A(0);
        // ADC_A(0);
        // LD_hl_A;
        wram->wc82e = HIGH(wram->wc991 + e);
        // XOR_A_A;
        // LD_addr_A(wc991);
        wram->wc991 = 0x0;
        // LD_A_addr(wc86e);
        // OR_A_A;
        // IF_Z goto asm_1110eb;
        if(wram->wc86e != 0x0) {
            // LD_B_E;
            // LD_HL(wMobileSDK_ReceivePacketBuffer + 3);
            // LD_A_hli;
            // INC_HL;
            // SUB_A_E;
            // DEC_A;
            // LD_E_A;
            // LD_D(0);
            // ADD_HL_DE;
            // LD_A_addr(wc829);
            // LD_E_A;
            // LD_A_addr(wc82a);
            // LD_D_A;
            // CALL(aMobileSDK_CopyBytes);
            gMobileReceiveBuffer_Destination = MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wMobileSDK_ReceivePacketBuffer + 5 + (wram->wMobileSDK_ReceivePacketBuffer[3] - e - 1), e);
            // LD_HL(wc829);
            // LD_A_E;
            // LD_hli_A;
            // LD_A_D;
            // LD_hl_A;
        }
    }

// asm_1110eb:
    // NOP;
    // LD_A(0x2);
    // LD_addr_A(wc989);
    wram->wc989 = 0x2;
    // LD_HL(wc821);
    // RES_hl(2);
    bit_reset(wram->wc821, 2);
    // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    // CP_A(0x9f);
    // IF_Z goto asm_111144;
    if(wram->wMobileSDK_ReceivePacketBuffer[0] == 0x9f) {
    // asm_111144:
        // RES_hl(0);
        bit_reset(wram->wc821, 0);
        // LD_HL(wc827);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // LD_A_addr(wc82d);
        // LD_hli_A;
        gMobile_wc827[0] = wram->wc82d;
        // LD_A_addr(wc82e);
        // LD_hl_A;
        gMobile_wc827[1] = wram->wc82e;
        // LD_A(0x2);
        // LD_addr_A(wc86a);
        wram->wc86a = 0x2;
        // XOR_A_A;
        // LD_addr_A(wc86d);
        wram->wc86d = 0x0;
        // NOP;
        // RET;
        return;
    }
    // LD_DE(0x000b);
    // LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    // LD_addr_A(wMobileSDK_SendCommandID);
    wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_TRANSFER_DATA | 0x80;
    // LD_HL(wMobileSDK_PacketBuffer);
    // LD_B(0x5);
    // CALL(aPacketSendBytes);
    PacketSendBytes(wram->wMobileSDK_PacketBuffer, 0x000b, 0x5);
    // LD_A(0x1);
    // LD_addr_A(wc86b);
    wram->wc86b = 0x1;
    // RET;
    return;

// Orphaned code?
    // LD_HL(wc827);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wc82d);
    // LD_hli_A;
    // LD_A_addr(wc82e);
    // LD_hl_A;
    // LD_HL(wc98f);
    // INC_hl;
    // LD_A(0xf);
    // LD_addr_A(wc86a);
    // LD_A(0x1);
    // LD_addr_A(wc86b);
    // LD_A_addr(wc86d);
    // LD_addr_A(wc86e);
    // XOR_A_A;
    // LD_addr_A(wc989);
    // LD_A(0xa3);
    // LD_DE(0x0010);
    // LD_HL(wc995);
    // JP(mFunction111f02);
}

uint8_t Function11115f(uint16_t* bc, uint8_t a){
    // LD_E_A;
    uint8_t e = a;
    // XOR_A_A;
    // CP_A_B;
    // IF_NZ goto asm_111168;
    // LD_A_C;
    // CP_A_E;
    // IF_C goto asm_1111a2;
    if(*bc >= e) {
    // asm_111168:
        // PUSH_HL;
        // PUSH_BC;
        // LD_B_E;
        // LD_C_E;
        // LD_A_addr(wc993);
        // SUB_A_E;
        // LD_E_A;
        // LD_D(0);
        // LD_HL(wc880);
        // ADD_HL_DE;
        // LD_A_addr(wc829);
        // LD_E_A;
        // LD_A_addr(wc82a);
        // LD_D_A;
        // CALL(aMobileSDK_CopyBytes);
        // LD_HL(wc829);
        // LD_A_E;
        // LD_hli_A;
        // LD_A_D;
        // LD_hl_A;
        gMobileReceiveBuffer_Destination = MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wc880_str + (wram->wc993 - e), e);
        // LD_E_C;
        // LD_A_C;
        // LD_HL(wc82d);
        // LD_hli_A;
        wram->wc82d = e;
        // XOR_A_A;
        // LD_hl_A;
        wram->wc82e = 0x0;
        // POP_BC;
        // LD_A_C;
        // SUB_A_E;
        // LD_C_A;
        // LD_A_B;
        // SBC_A(0x0);
        // LD_B_A;
        *bc -= e;
        // LD_A_addr(wc992);
        // LD_addr_A(wc82b);
        wram->wc82b = wram->wc992;
        // LD_E_A;
        e = wram->wc992;
        // POP_HL;
        // RET;
        return e;
    }
    else {
    // asm_1111a2:
        // LD_A_E;
        // SUB_A_C;
        // LD_addr_A(wc991);
        wram->wc991 = e - *bc;
        // LD_A_addr(wc993);
        // SUB_A_E;
        // LD_E_A;
        // LD_D(0);
        // LD_HL(wc880);
        // ADD_HL_DE;
        // LD_A_addr(wc829);
        // LD_E_A;
        // LD_A_addr(wc82a);
        // LD_D_A;
        // LD_B_C;
        // CALL(aMobileSDK_CopyBytes);
        MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wc880_str + (wram->wc993 - e), *bc);
        // LD_HL(wc827);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // LD_A_C;
        // LD_hli_A;
        gMobile_wc827[0] = LOW(*bc);
        // XOR_A_A;
        // LD_hl_A;
        gMobile_wc827[1] = 0x0;
        // POP_AF;
        // RET;
        return e;
    }
}

void Function1111ca(void){
    // LD_HL(wc821);
    // RES_hl(2);
    bit_reset(wram->wc821, 2);
    // LD_A(0x6);
    // LD_addr_A(wc86b);
    wram->wc86b = 0x6;
    // JP(mFunction112430);
    Function112430();
}

uint16_t Function1111d7(const char* hl){
    // PUSH_HL;
    // LD_HL(wc866);
    // LD_A_hli;
    // OR_A_hl;
    // INC_HL;
    // OR_A_hl;
    // INC_HL;
    // OR_A_hl;
    // POP_HL;
    // IF_NZ goto asm_1111ee;
    if(wram->wc866[0] == 0
    && wram->wc866[1] == 0
    && wram->wc866[2] == 0
    && wram->wc866[3] == 0) {
        // LD_DE(0x0007);
        // ADD_HL_DE;
        hl += 0x0007;

        uint8_t a;
        do {
        // asm_1111e8:
            // LD_A_hli;
            a = *(hl++);
            // CP_A(0x2f);
            // IF_NZ goto asm_1111e8;
        } while(a != '/');
        // DEC_HL;
        hl--;
    }

// asm_1111ee:
    // LD_BC(-1);
    uint16_t bc = -1;
    uint8_t a;

    do {
    // asm_1111f1:
        // LD_A_hli;
        a = *(hl++);
        // INC_BC;
        bc++;
        // OR_A_A;
        // IF_NZ goto asm_1111f1;
    } while(a != 0);
    // LD_HL(wc87a);
    // LD_A_C;
    // LD_hli_A;
    wram->wc87a = LOW(bc);
    // LD_A_B;
    // LD_hl_A;
    wram->wc87b = HIGH(bc);
    // RET;
    return bc;
}

// MobileAPI_16
void Function1111fe(mobile_api_data_s* data){
    // LD_A_addr(wc821);
    // BIT_A(2);
    // LD_A_addr(wc86a);
    // JP_NZ (mFunction1113ea);
    if(bit_test(wram->wc821, 2))
        return Function1113ea(data, wram->wc86a);
    // CP_A(0x2);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc821);
    // BIT_A(0);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc86d);
    // OR_A_A;
    // JP_NZ (mFunction110226);
    if(wram->wc86a != 0x2 || bit_test(wram->wc821, 0) || wram->wc86d != 0)
        return Function110226();
    // XOR_A_A;
    // LD_addr_A(wc989);
    wram->wc989 = 0;
    // LD_addr_A(wc98a);
    wram->wc98a = 0;
    // LD_addr_A(wc993);
    wram->wc993 = 0;
    // PUSH_HL;
    char* hl = data->hl;
    // PUSH_DE;
    // PUSH_BC;
    // PUSH_HL;
    char* hl2 = hl;
    // for(int rept = 0; rept < 4; rept++){
    // INC_HL;
    // }
    hl2 += 4;
    // LD_A_hli;
    // LD_addr_A(wc833);
    // LD_A_hli;
    // LD_addr_A(wc834);
    gMobile_wc833_wc834 = GBToRAMAddr(hl2[0] | (hl2[1] << 8));
    hl2 += 2;
    // INC_HL;
    // INC_HL;
    hl2 += 2;
    // LD_A_L;
    // LD_addr_A(wc97f);
    // LD_A_H;
    // LD_addr_A(wc980);
    gMobile_wc97f_wc980 = (uint8_t*)hl2;
    // DEC_HL;
    // DEC_HL;
    hl2 -= 2;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    hl2 = GBToRAMAddr(hl2[0] | (hl2[1] << 8));
    // LD_A(0x80);
    // CP_A_L;
    // IF_NZ goto asm_111251;
    // LD_A(0xc8);
    // CP_A_H;
    // JP_Z (mFunction1113f7);
    if(hl2 == wram->wc880_str)
        return Function1113f7();

// asm_111251:
    // LD_B(lengthof(URIPrefix));
    uint8_t b = lengthof(URIPrefix) - 1;
    // LD_DE(mURIPrefix);
    const char* de2 = URIPrefix;

    do {
    // asm_111256:
        // LD_A_de;
        // INC_DE;
        char ch = *(de2++);
        // CP_A_hl;
        // JP_NZ (mFunction1113f7);
        if(ch != *hl2)
            return Function1113f7();
        // INC_HL;
        hl2++;
        // DEC_B;
        // IF_NZ goto asm_111256;
    } while(--b != 0);
    // PUSH_HL;
    char* hl3 = hl2;
    // LD_B(lengthof(HTTPDownloadURL));
    b = lengthof(HTTPDownloadURL) - 1;
    // LD_C(0x0);
    uint8_t c = 0x0;
    // LD_DE(mHTTPDownloadURL);
    de2 = HTTPDownloadURL;

    do {
    // asm_111268:
        // LD_A_de;
        // INC_DE;
        char ch = *(de2++);
        // CP_A_hl;
        // IF_NZ goto asm_111275;
        if(ch != *hl3)
            goto asm_111275;
        // INC_HL;
        hl3++;
        // DEC_B;
        // IF_NZ goto asm_111268;
    } while(--b != 0);
    // POP_HL;
    // JP(mFunction1113f7);
    return Function1113f7();

asm_111275:
    // POP_HL;
    // PUSH_HL;
    hl3 = hl2;
    // LD_B(lengthof(HTTPRankingURL));
    b = lengthof(HTTPRankingURL) - 1;
    // LD_C(0x0);
    c = 0x0;
    // LD_DE(mHTTPRankingURL);
    de2 = HTTPRankingURL;

    do {
    // asm_11127e:
        // LD_A_de;
        // INC_DE;
        char ch = *(de2++);
        // CP_A_hl;
        // IF_NZ goto asm_11128f;
        if(ch != *hl3) {
        // asm_11128f:
            // POP_HL;
            // LD_B(lengthof(HTTPUploadURL));
            b = lengthof(HTTPUploadURL) - 1;
            // LD_C(0x0);
            c = 0x0;
            // LD_DE(mHTTPUploadURL);
            de2 = HTTPUploadURL;

            do {
            // asm_111297:
                // LD_A_de;
                // INC_DE;
                char ch = *(de2++);
                // CP_A_hl;
                // IF_NZ goto asm_1112cc;
                if(ch != *hl2)
                    goto asm_1112cc;
                // INC_HL;
                hl2++;
                // DEC_B;
                // IF_NZ goto asm_111297;
            } while(--b != 0);
            goto asm_1112a0;
        }
        // INC_HL;
        hl3++;
        // DEC_B;
        // IF_NZ goto asm_11127e;
    } while(--b != 0);
    // LD_A(0x2);
    // LD_addr_A(wc98a);
    wram->wc98a = 0x2;
    // POP_HL;
    // goto asm_1112a0;

asm_1112a0:
    do {
        // LD_A_hli;
        // OR_A_A;
        // IF_NZ goto asm_1112a0;
    } while(*(hl2++) != 0);

    do {
    // asm_1112a4:
        // LD_A_hld;
        // CP_A(0x2f);
        // IF_NZ goto asm_1112a4;
    } while(*(hl2--) != '/');
    // INC_HL;
    // INC_HL;
    hl2 += 2;
    // LD_A_hl;
    // CP_A(0x30);
    // IF_C goto asm_1112cc;
    // CP_A(0x3a);
    // IF_NC goto asm_1112cc;
    if(hl2[0] >= '0' && hl2[0] <= '9') {
        // LD_HL(wc97f);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        hl2 = (char*)gMobile_wc97f_wc980;
        // LD_C(0x12);
        // CALL(aFunction11039a);
        // JP_C (mFunction1113f7);
        if(Function11039a(&hl2, 0x12))
            return Function1113f7();
        // LD_C(0x12);
        // CALL(aFunction11039a);
        // JP_C (mFunction1113f7);
        if(Function11039a(&hl2, 0x12))
            return Function1113f7();
        // LD_C(0x1);
        c = 0x1;
    }

asm_1112cc:
    // LD_A_C;
    // LD_addr_A(wc98f);
    wram->wc98f = c;
    // LD_addr_A(wMobileSDK_ReceivePacketBuffer + 128);
    wram->wMobileSDK_ReceivePacketBuffer[128] = c;
    // POP_HL;
    // LD_DE(0x0006);
    // ADD_HL_DE;
    hl += 0x0006;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    hl2 = GBToRAMAddr(hl[0] | (hl[1] << 8));
    // CALL(aFunction1111d7);
    uint16_t bc2 = Function1111d7(hl2);
    // LD_A_B;
    // CP_A(0x4);
    // IF_C goto asm_1112eb;
    // JP_NZ (mFunction1113f8);
    // XOR_A_A;
    // OR_A_C;
    // JP_NZ (mFunction1113f8);
    if(bc2 > 0x400)
        return Function1113f8();

// asm_1112eb:
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // LD_A_L;
    // LD_addr_A(wc876);
    // LD_A_H;
    // LD_addr_A(wc877);
    gMobile_wc876 = data->hl;
    // LD_HL(wc872);
    // LD_A_C;
    // LD_hli_A;
    wram->wc872 = LOW(data->bc);
    // LD_A_B;
    // LD_hli_A;
    wram->wc873 = HIGH(data->bc);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobile_wc874_wc875 = data->de;
    // INC_HL;
    // INC_HL;
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hl_A;
    gMobile_wc878 = data->de;
    // CALL(aFunction111335);
    Function111335();
    // LD_HL(wc876);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl4 = gMobile_wc876;
    // LD_A_hli;
    // LD_addr_A(wc9aa);
    // LD_A_hli;
    // LD_addr_A(wc9ab);
    gMobile_wc9aa_wc9ab = GBToRAMAddr(hl4[0] | (hl4[1] << 8));
    // LD_A_hli;
    // LD_addr_A(wc9ac);
    wram->wc9ac = hl4[2];
    // LD_A_hli;
    // LD_addr_A(wc9ad);
    wram->wc9ad = hl4[3];
    // INC_HL;
    // INC_HL;
    // LD_A_hli;
    // LD_addr_A(wc876);
    // LD_A_hl;
    // LD_addr_A(wc877);
    gMobile_wc876 = GBToRAMAddr(hl4[6] | (hl4[7] << 8));
    // LD_A_addr(wc98f);
    // XOR_A(0x1);
    // LD_addr_A(wc994);
    wram->wc994 = wram->wc98f ^ 0x1;
    // JP(mFunction110f07);
    return Function110f07();
}

void Function111335(void){
    // LD_HL(wc876);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl2 = gMobile_wc876;
    // INC_HL;
    // INC_HL;
    hl2 += 2;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint16_t hl = hl2[0] | (hl2[1] << 8);
    // XOR_A_A;
    uint8_t a = 0;
    // LD_addr_A(wc8c9);
    wram->wc8c9 = a;

    while(hl > 30000) {
    // asm_111344:
        // LD_DE(0x8ad0);
        // ADD_HL_DE;
        // IF_NC goto asm_11134e;
        hl -= 30000;
        // ADD_A(0x3);
        a += 0x3;
        // goto asm_111344;
    }

// asm_11134e:
    // LD_DE(0x7530);
    // ADD_HL_DE;

    while(hl > 10000) {
    // asm_111352:
        // LD_DE(0xd8f0);
        // ADD_HL_DE;
        // IF_NC goto asm_11135b;
        hl -= 10000;
        // INC_A;
        a++;
        // goto asm_111352;
    }

// asm_11135b:
    // LD_DE(0x2710);
    // ADD_HL_DE;
    // LD_addr_A(wc8c6);
    wram->wc8c6 = a;
    // XOR_A_A;
    a = 0;

    while(hl >= 3000) {
    // asm_111363:
        // LD_DE(0xf448);
        // ADD_HL_DE;
        hl -= 3000;
        // IF_NC goto asm_11136d;
        // ADD_A(0x30);
        a += 0x30;
        // goto asm_111363;
    }

// asm_11136d:
    // LD_DE(0x0bb8);
    // ADD_HL_DE;

    while(hl >= 1000) {
    // asm_111371:
        // LD_DE(0xfc18);
        // ADD_HL_DE;
        // IF_NC goto asm_11137b;
        hl -= 1000;
        // ADD_A(0x10);
        a += 0x10;
        // goto asm_111371;
    }

// asm_11137b:
    // LD_DE(0x03e8);
    // ADD_HL_DE;

    while(hl >= 300) {
    // asm_11137f:
        // LD_DE(0xfed4);
        // ADD_HL_DE;
        // IF_NC goto asm_111389;
        hl -= 300;
        // ADD_A(0x3);
        a += 0x3;
        // goto asm_11137f;
    }

// asm_111389:
    // LD_DE(0x012c);
    // ADD_HL_DE;

    while(hl >= 100) {
    // asm_11138d:
        // LD_DE(0xff9c);
        // ADD_HL_DE;
        // IF_NC goto asm_111396;
        hl -= 100;
        // INC_A;
        a++;
        // goto asm_11138d;
    }

// asm_111396:
    // LD_DE(0x0064);
    // ADD_HL_DE;
    // LD_addr_A(wc8c7);
    wram->wc8c7 = a;
    // XOR_A_A;
    a = 0;

    while(hl >= 30) {
    // asm_11139e:
        // LD_DE(0xffe2);
        // ADD_HL_DE;
        // IF_NC goto asm_1113a8;
        hl -= 30;
        // ADD_A(0x30);
        a += 0x30;
        // goto asm_11139e;
    }

// asm_1113a8:
    // LD_DE(0x001e);
    // ADD_HL_DE;

    while(hl >= 10) {
    // asm_1113ac:
        // LD_DE(0xfff6);
        // ADD_HL_DE;
        hl -= 10;
        // IF_NC goto asm_1113b6;
        // ADD_A(0x10);
        a += 0x10;
        // goto asm_1113ac;
    }

// asm_1113b6:
    // LD_DE(0x000a);
    // ADD_HL_DE;
    // ADD_A_L;
    // LD_addr_A(wc8c8);
    wram->wc8c8 = LOW(hl) + a;
    // LD_DE(wc9a5);
    uint8_t* de = wram->wc9a5;
    // LD_HL(wc8c6);
    hl2 = &wram->wc8c6;
    // LD_A_hli;
    // OR_A(0x30);
    // LD_de_A;
    // INC_DE;
    *(de++) = *(hl2++) | 0x30;
    // LD_A_hl;
    a = *(hl2++);
    // SWAP_A;
    // AND_A(0xf);
    // OR_A(0x30);
    // LD_de_A;
    // INC_DE;
    *(de++) = ((a >> 4) & 0xf) | 0x30;
    // LD_A_hli;
    // AND_A(0xf);
    // OR_A(0x30);
    // LD_de_A;
    // INC_DE;
    *(de++) = (a & 0xf) | 0x30;
    // LD_A_hl;
    a = *(hl2++);
    // SWAP_A;
    // AND_A(0xf);
    // OR_A(0x30);
    // LD_de_A;
    // INC_DE;
    *(de++) = ((a >> 4) & 0xf) | 0x30;
    // LD_A_hl;
    // AND_A(0xf);
    // OR_A(0x30);
    // LD_de_A;
    // INC_DE;
    *(de++) = (a & 0xf) | 0x30;
    // RET;

}

void Function1113ea(mobile_api_data_s* data, uint8_t a){
    // CP_A(0x14);
    // JP_Z (mFunction111044);
    // CP_A(0x24);
    // JP_Z (mFunction111044);
    if(a == 0x14 || a == 0x24)
        return Function111044(data);
    // JP(mFunction110226);
    return Function110226();
}

void Function1113f7(void){
    // POP_HL;

    return Function1113f8();
}

void Function1113f8(void){
    // POP_HL;
    // POP_HL;
    // POP_HL;
    // JP(mFunction110231);
    Function110231();
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
        data->a = 0xff;
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
    // LD_hli_A;
    gMobileReceiveBuffer_Destination = NULL;
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
}

// MobileAPI_21
void Function111540(mobile_api_data_s *data){
    // NOP;

    return Function111541(data);
}

// MobileAPI_19
void Function111541(mobile_api_data_s *data){
    // LD_HL(wc821);
    // BIT_hl(0);
    // JP_NZ (mFunction110226);
    // LD_A_addr(wc86a);
    // CP_A(0x5);
    // JP_NC (mFunction110226);
    if(bit_test(wram->wc821, 0) || wram->wc86a >= 0x5)
        return Function110226();
    // LD_addr_A(wc985);
    wram->wc985 = wram->wc86a;
    // LD_A_E;
    // LD_addr_A(wc86e);
    // LD_A_D;
    // LD_addr_A(wc86f);
    gMobile_wc86e_wc86f = data->de;
    // LD_A_addr(wc807);
    // CP_A(0x2);
    // IF_C goto asm_111582;
    if(wram->wc807 >= 0x2) {
        // XOR_A_A;
        // LD_addr_A(wc86b);
        wram->wc86b = 0x0;
        // LD_A(MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
        // LD_HL(mMobilePacket_TelephoneStatus);
        // CALL(aPacketSendEmptyBody);
        PacketSendEmptyBody(MobilePacket_TelephoneStatus, MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
    }
    else {
    // asm_111582:
        // XOR_A_A;
        // LDH_addr_A(rTAC);
        gb_write(rTAC, 0x0);
        // LD_A_addr(wc870);
        // LD_C_A;
        data->bc = wram->wc870;
        // CALL(aMobileAPI_SetTimer);
        MobileAPI_SetTimer(data);
        // CALL(aFunction1104b0);
        Function1104b0();
        // LD_A(0x1);
        // LD_addr_A(wc86b);
        wram->wc86b = 0x1;
        // goto asm_11156f;
    }

// asm_11156f:
    // LD_A_addr(wMobileAPIIndex);
    // CP_A(0x40);
    // IF_NZ goto asm_11157a;
    // LD_A(0x2c);
    // goto asm_11157c;

// asm_11157a:
    // LD_A(0x1e);

// asm_11157c:
    // LD_addr_A(wc86a);
    wram->wc86a = (wram->wMobileAPIIndex == 0x40)? 0x2c: 0x1e;
    // JP(mFunction110432);
    return Function110432();
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
    wram->wc816 = ((b >> 2) + (b * 2));
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
    uint8_t* hl = (wram->wMobileSDK_SendCommandID == 0xff || bit_test(wram->wc822, 0))? wram->wMobileSDK_ReceivePacketBufferAlt: wram->wMobileSDK_ReceivePacketBuffer;

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
    // LD_A(0x1);
    // JR(mFunction1116a9);
    return Function1116a9(0x1);
}

void Function1116a4(uint8_t* hl){
    // SET_hl(1);
    bit_set(*hl, 1);
    // LD_A_addr(wc86a);

    return Function1116a9(wram->wc86a);
}

void Function1116a9(uint8_t a){
    // LD_addr_A(wMobileSDK_PacketBuffer + 1);
    wram->wMobileSDK_PacketBuffer[1] = a;
    // LD_HL(wc815);
    // XOR_A_A;
    // LD_hli_A;
    wram->wc815 = 0x0;
    // LD_A_addr(wc81f);
    // RLA;
    // LD_hl_A;
    wram->wc816 = wram->wc81f << 1;
    // LD_HL(wc821);
    // LD_A_hl;
    // LD_B_A;
    uint8_t b = wram->wc821;
    // AND_A(0xd);
    // LD_hl_A;
    wram->wc821 = b & 0xd;
    // LD_A(0x2);
    // AND_A_B;
    // LD_addr_A(wMobileSDK_PacketBuffer);
    wram->wMobileSDK_PacketBuffer[0] = b & 0x2;
    // RET;
}

void v_MobileReceive(void){
    // LD_A_addr(wc800);
    uint8_t a = wram->wc800;
    // RRCA;
    // JP_NC (mFunction1118bc);
    if(!(a & 1))
        return Function1118bc();
    // RRCA;
    // JP_C (mFunction1117e7);
    if(a & 2)
        return Function1117e7();
    // LD_HL(wc801);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // DEC_DE;
    uint16_t de = --gMobilePacketSize;
    // LD_A_D;
    // LD_hld_A;
    // LD_A_E;
    // LD_hl_A;
    // CP_A(0x2);
    // JP_NC (mFunction1118bc);
    // LD_A_D;
    // OR_A_A;
    // JP_NZ (mFunction1118bc);
    if(de >= 0x2)
        return Function1118bc();
    // LD_HL(wc808);
    // ADD_HL_DE;
    // LDH_A_addr(rSB);
    uint8_t* hl = wram->wc808_arr + de;
    // LD_hl_A;
    *hl = gb_read(rSB);
    // LD_A(0x8);
    // CP_A_L;
    // JP_NZ (mFunction1118bc);
    if(de != 0x0)
        return Function1118bc();
    // LD_A_addr(wMobileSDK_SendCommandID);
    // CP_A(0xff);
    // IF_Z goto asm_111716;
    if(wram->wMobileSDK_SendCommandID != 0xff) {
        // LD_A(0xf2);
        // CP_A_hl;
        // JP_Z (mFunction111796);
        if(*hl == 0xf2)
            return Function111796();
        // DEC_A;
        // CP_A_hl;
        // JP_Z (mFunction1117a0);
        if(*hl == 0xf1)
            return Function1117a0();
        // DEC_A;
        // CP_A_hl;
        // JP_Z (mFunction1117a0);
        if(*hl == 0xf0)
            return Function1117a0();
        // LD_A_addr(wc807);
        // CP_A(0x1);
        // IF_NZ goto asm_111716;
        // LD_A_addr(wc806);
        // OR_A_A;
        // IF_Z goto asm_111778;
        if(wram->wc807 == 0x1 && wram->wc806 == 0) {
        // asm_111778:
            // XOR_A_A;
            // LD_addr_A(wc800);
            wram->wc800 = 0x0;
            return Function11177c();
        }
    }

// asm_111716:
    // LD_A_addr(wMobileSDK_SendCommandID);
    // CP_A(-1);
    // IF_Z goto asm_111730;
    if(wram->wMobileSDK_SendCommandID != 0xff) {
        a = wram->wMobileSDK_SendCommandID;
        // CP_A(MOBILE_COMMAND_ERROR | 0x80);
        // IF_Z goto asm_111727;
        // CP_A(MOBILE_COMMAND_TRANSFER_DATA_END | 0x80);
        // IF_NZ goto asm_111727;
        if(a != (MOBILE_COMMAND_ERROR | 0x80)
        && a == (MOBILE_COMMAND_TRANSFER_DATA_END | 0x80)) {
            // LD_A(MOBILE_COMMAND_TRANSFER_DATA | 0x80);
            a = MOBILE_COMMAND_TRANSFER_DATA | 0x80;
        }

    // asm_111727:
        // CP_A_hl;
        // JR_NZ (masm_11179a);
        if(a != *hl)
            return asm_11179a(hl);
        // LD_A_addr(wMobileSDK_AdapterType);
        // OR_A_A;
        // IF_Z goto asm_111730; // Pointless jump
    }

// asm_111730:
    // XOR_A_A;
    // LD_addr_A(wc819);
    wram->wc819 = 0x0;
    // LD_A(0x3);
    // LD_addr_A(wc800);
    wram->wc800 = 0x3;
    // XOR_A_A;
    // LD_HL(wc80a);
    // LD_hli_A;
    wram->wc80a = 0x0;
    // LD_hli_A;
    wram->wc80b = 0x0;
    // LD_hli_A;
    wram->wc80c_arr[0] = 0x0;
    // LD_HL(wc81f);
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hl;
    // LD_HL(wc815);
    // LD_hli_A;
    wram->wc815 = wram->wc820;
    // LD_A_B;
    // LD_hli_A;
    wram->wc816 = wram->wc81f;
    // LD_A_addr(wc822);
    // BIT_A(0);
    // IF_Z goto asm_111757;
    if(bit_test(wram->wc822, 0)) {
        // LD_A(0xb);
        a = 0xb;
        // goto asm_111774;
    }

// asm_111757:
    // LD_A_addr(wMobileSDK_SendCommandID);
    // CP_A(-1);
    // IF_Z goto asm_11176e;
    else if(wram->wMobileSDK_SendCommandID == 0xff) {
    // asm_11176e:
        // LD_A(0x3);
        a = 0x3;
        // goto asm_111774;
    }
    // CP_A(MOBILE_COMMAND_DIAL_TELEPHONE | 0x80);
    // IF_Z goto asm_111772;
    // CP_A(MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80);
    // IF_Z goto asm_111772;
    // CP_A(MOBILE_COMMAND_DNS_QUERY | 0x80);
    // IF_Z goto asm_111772;
    else if(wram->wMobileSDK_SendCommandID == (MOBILE_COMMAND_DIAL_TELEPHONE | 0x80)
        ||  wram->wMobileSDK_SendCommandID == (MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80)
        ||  wram->wMobileSDK_SendCommandID == (MOBILE_COMMAND_DNS_QUERY | 0x80)) {
    // asm_111772:
        // LD_A(0x60);
        a = 0x60;
    }
    else {
        // LD_A(0x20);
        a = 0x20;
        // goto asm_111774;
    }

// asm_111774:
    // LD_hl_A;
    wram->wc817 = a;
    // JP(mFunction1118bc);
    return Function1118bc();
}

void Function11177c(void){
    // LD_HL(wc820);
    // LD_A_hld;
    // LD_E_A;
    // LD_A_hl;
    // DEC_A;
    uint16_t de = ((wram->wc81f - 1) << 8) | wram->wc820;
    printf("Timer set: %d\n", de);
    // LD_B(0x3);

    // do {
    // // asm_111785:
    //     // OR_A_A;
    //     // RRA;
    //     // RR_E;
    //     de = (de >> 1) | (de << 15);
    //     // DEC_B;
    //     // IF_NZ goto asm_111785;
    // } while(--b != 0);
    // de = (de >> 3) | (de << (16 - 3));
    // OR_A_A;
    // INC_A;
    de = (de + 0x100);
    // printf("Timer set: %d, %d\n", ((de >> 8) | (de << 8)) & 0xffff, de);
    // LD_HL(wc816);
    // LD_hld_A;
    wram->wc816 = HIGH(de);
    // LD_hl_E;
    wram->wc815 = LOW(de);
    // JP(mFunction1118bc);
    return Function1118bc();
}

void Function111796(void){
    // LD_B(0xa);
    // JR(masm_1117a2);
    return asm_1117a2(0xa);
}

void asm_11179a(uint8_t* hl){
    // XOR_A_A;
    // LD_hli_A;
    hl[0] = 0x0;
    // LD_hl_A;
    hl[1] = 0x0;
    // JP(mFunction1118bc);
    return Function1118bc();
}

void Function1117a0(void){
    // LD_B(0x3);
    return asm_1117a2(0x3);
}

void asm_1117a2(uint8_t b){
    // LD_HL(wc822);
    // SET_hl(3);
    bit_set(wram->wc822, 3);
    // LD_HL(wc815);
    // LD_A_addr(wc820);
    // LD_hli_A;
    wram->wc815 = wram->wc820;
    // LD_A_addr(wc81f);
    // LD_hl_A;
    wram->wc816 = wram->wc81f;
    // XOR_A_A;
    // LD_addr_A(wc800);
    wram->wc800 = 0x0;
    // LD_HL(wc819);
    // INC_hl;
    // LD_A_B;
    // CP_A_hl;
    // JP_NC (mFunction1118bc);
    if(b >= ++wram->wc819)
        return Function1118bc();
    // XOR_A_A;
    // LD_HL(wc806);
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
    // LD_HL(wc810);
    // LD_A_addr(wc808);
    // AND_A(0xf);
    uint8_t a = wram->wc808 & 0xf;
    // CP_A(0x2);
    // IF_NZ goto asm_1117e1;
    if(a == 0x2) {
        // INC_A;
        ++a;
    }

// asm_1117e1:
    // LD_hli_A;
    wram->wc810 = a;
    // XOR_A_A;
    // LD_hl_A;
    wram->wc811 = 0x0;
    // JP(mFunction1118bc);
    return Function1118bc();
}

void Function1117e7(void){
    // LD_A_addr(wc80b);
    // OR_A_A;
    // IF_Z goto asm_1117f8;
    if(wram->wc80b != 0x0) {
        // DEC_A;
        // JP_Z (mFunction11186e);
        if(wram->wc80b == 0x1)
            return Function11186e();
        // DEC_A;
        // JP_Z (mFunction111884);
        if(wram->wc80b == 0x2)
            return Function111884();
        // JP(mFunction111892);
        return Function111892();
    }

// asm_1117f8:
    // LD_HL(wc80a);
    // LD_A_hl;
    // OR_A_A;
    // IF_NZ goto asm_111803;
    // LD_B(0x99);
    // goto asm_111805;

// asm_111803:
    // LD_B(0x66);

// asm_111805:
    uint8_t b = (wram->wc80a != 0x0)? 0x66: 0x99;
    // LDH_A_addr(rSB);
    uint8_t a = gb_read(rSB);
    // CP_A_B;
    // IF_Z goto asm_111840;
    if(a != b) {
        // CP_A(0xd2);
        // IF_NZ goto asm_111817;
        if(a == 0xd2) {
            // XOR_A_A;
            // LD_addr_A(wc9ae);
            wram->wc9ae = 0x0;

        asm_111812:
            // XOR_A_A;
            // LD_hl_A;
            wram->wc80a = 0x0;
            // JP(mFunction1118bc);
            return Function1118bc();
        }

    // asm_111817:
        // LD_A_addr(wc9ae);
        // INC_A;
        // LD_addr_A(wc9ae);
        a = ++wram->wc9ae;
        // CP_A(0x14);
        // IF_C goto asm_111812;
        if(a < 0x14)
            goto asm_111812;
        // LD_A(0x6);
        // LD_addr_A(wc807);
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
        // SET_A(1);
        // AND_A(0xf);
        // LD_hl_A;
        wram->wc821 = (wram->wc821 | (1 << 1)) & 0xf;
        // JR(mFunction1118bc);
        return Function1118bc();
    }

// asm_111840:
    // INC_hl;
    ++wram->wc80a;
    // LD_A(0x2);
    // CP_A_hl;
    // JR_NZ (mFunction1118bc);
    if(wram->wc80a != 0x2)
        return Function1118bc();
    // XOR_A_A;
    // LD_hli_A;
    wram->wc80a = 0x0;
    // INC_hl;
    wram->wc80b++;
    // LD_HL(wMobileSDK_PacketChecksum);
    // LD_B(0x3);

// asm_11184e:
    // LD_hli_A;
    // DEC_B;
    // IF_NZ goto asm_11184e;
    wram->wMobileSDK_PacketChecksum = 0x0;
    wram->wc814 = 0x0;
    // LD_A_addr(wc822);
    // BIT_A(4);
    // IF_Z goto asm_111864;
    // LD_B_A;
    // LD_A_addr(wc821);
    // BIT_A(3);
    // IF_NZ goto asm_111864;
    if(bit_test(wram->wc822, 4) && !bit_test(wram->wc821, 3)) {
        // JP(mFunction11177c);
        return Function11177c();
    }

// asm_111864:
    // LD_A_addr(wc820);
    // LD_hli_A;
    wram->wc815 = wram->wc820;
    // LD_A_addr(wc81f);
    // LD_hl_A;
    wram->wc816 = wram->wc81f;
    // JR(mFunction1118bc);
    return Function1118bc();
}

void Function11186e(void){
    // CALL(aFunction1118c2);
    Function1118c2();
    // LD_A(0x4);
    // CP_A_hl;
    // JR_NZ (mFunction1118bc);
    if(wram->wc80a != 0x4)
        return Function1118bc();
    // XOR_A_A;
    // LD_hli_A;
    wram->wc80a = 0x0;
    // LDH_A_addr(rSB);
    // LD_addr_A(wc80c);
    wram->wc80c_arr[0] = gb_read(rSB);
    // INC_hl;
    ++wram->wc80b;
    // OR_A_A;
    // JR_NZ (mFunction1118bc);
    if(wram->wc80c_arr[0] != 0x0)
        return Function1118bc();
    // INC_hl;
    ++wram->wc80c_arr[0];
    // JR(mFunction1118bc);
    Function1118bc();
}

void Function111884(void){
    // CALL(aFunction1118c2);
    Function1118c2();
    // LD_A_addr(wc80c);
    // CP_A_hl;
    // JR_NZ (mFunction1118bc);
    if(wram->wc80a != wram->wc80c_arr[0])
        return Function1118bc();
    // XOR_A_A;
    // LD_hli_A;
    wram->wc80a = 0x0;
    // INC_hl;
    wram->wc80b++;
    // JR(mFunction1118bc);
    return Function1118bc();
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
    if(++wram->wc80a <= 0x2) {
        // LD_A_addr(wc80a);
        // ADD_A(0x11);
        // LD_E_A;
        uint8_t e = wram->wc80a;
        // LD_D(0xc8);
        // LD_A_de;
        // CP_A_C;
        // JR_Z (mFunction1118bc);
        if((&wram->wc811)[e] == c)
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

// Mobile_ResetwC822Bit1
void Function1118bc(void){
    // LD_HL(wc822);
    // RES_hl(1);
    bit_reset(wram->wc822, 1);
    // RET;
}

// Mobile_AppendReceivedByteAndUpdateChecksum
void Function1118c2(void){
    // LDH_A_addr(rSB);
    // LD_C_A;
    uint8_t c = gb_read(rSB);
    // LD_B(0);
    // LD_HL(wMobileSDK_PacketChecksum);
    // LD_A_hli;
    // LD_L_hl;
    // LD_H_A;
    // ADD_HL_BC;
    // LD_A_H;
    // LD_addr_A(wMobileSDK_PacketChecksum);
    // LD_A_L;
    // LD_addr_A(wMobileSDK_PacketChecksum + 1);
    wram->wMobileSDK_PacketChecksum += c;
    // CALL(aFunction111664);
    Function111664(c);
    // LD_HL(wc80a);
    // INC_hl;
    wram->wc80a++;
    // RET;
}

void v_Timer(void){
    // LD_A_addr(wc80b);
    // CP_A(0x4);
    // CALL_Z (aFunction111b3c);
    if(wram->wc80b == 0x4)
        Function111b3c();
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
    // printf("Timer left: %d\n", (wram->wc816 << 8) | wram->wc815);
    // INC_HL;
    // DEC_hl;
    // JP_NZ (mFunction111b3b);
    if(wram->wc807 < 0x1 || --wram->wc815 != 0 || --wram->wc816 != 0)
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
        else if(a == 0xa) {
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
        else if(a == 0x8) {
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
        Function111f02(MobilePacket_TransferData, lengthof(MobilePacket_TransferData), MOBILE_COMMAND_TRANSFER_DATA | 0x80);
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
    wram->wc808_arr[0] = wram->wMobileSDK_SendCommandID = MOBILE_COMMAND_BEGIN_SESSION | 0x80;
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
    if(--wram->wc815 != 0x0 || (--wram->wc816) != 0x0)
        return asm_111a40();
    // INC_HL;
    // DEC_hl;
    // IF_Z goto asm_111a63;
    if(--wram->wc817 != 0) {
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
        wram->wc816 = d;
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
    if(wram->wc814 != 0x0) {
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
                MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wMobileSDK_ReceivePacketBuffer + 5, wram->wMobileSDK_ReceivePacketBuffer[3] - 1);
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
                Function111d70();
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
    if(gMobile_wc86e_wc86f == NULL || (wram->wc86e | wram->wc86f) == 0)
        return Function111d07();
    // LD_HL(wc82b);
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    uint16_t de = (wram->wc82b) | (wram->wc82c << 8);
    // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    // DEC_A;
    // JP_Z (mFunction111d07);
    if(wram->wMobileSDK_ReceivePacketBuffer[3] - 1 == 0)
        return Function111d07();
    // LD_C_A;
    uint8_t c = wram->wMobileSDK_ReceivePacketBuffer[3] - 1;
    // LD_A_addr(wc822);
    // BIT_A(4);
    // JP_Z (mFunction111cc2);
    if(!bit_test(wram->wc822, 4))
        return Function111cc2(&wram->wc82b, de, c);
    // LD_A_addr(wc992);
    // OR_A_A;
    // IF_NZ goto asm_111c89;
    if(wram->wc992 == 0x0) {
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 5);
        // OR_A_A;
        // IF_Z goto asm_111c50;
        // CP_A(0x81);
        // IF_C goto asm_111c52;
    // asm_111c50:
        // LD_A(0x80);

    // asm_111c52:
        // LD_B_A;
        uint8_t b = (wram->wMobileSDK_ReceivePacketBuffer[5] == 0 || wram->wMobileSDK_ReceivePacketBuffer[5] >= 0x81)? 0x80: wram->wMobileSDK_ReceivePacketBuffer[5];
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
        // DEC_A;
        // DEC_A;
        uint8_t a = wram->wMobileSDK_ReceivePacketBuffer[3] - 2;
        // CP_A_B;
        // IF_C goto asm_111c6e;
        if(a >= b) {
        asm_111c5b:
            // LD_HL(wc821);
            // SET_hl(3);
            bit_set(wram->wc821, 3);
            // LD_HL(wc993);
            // LD_A(0x1);
            // LD_hli_A;
            wram->wc993 = 0x1;
            // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
            // DEC_A;
            // LD_hl_A;
            wram->wc994 = wram->wMobileSDK_ReceivePacketBuffer[3] - 1;
            // JP(mFunction111d07);
            return Function111d07();
        }

    // asm_111c6e:
        // LD_HL(wc992);
        // OR_A_A;
        // IF_Z goto asm_111c83;
        if(a != 0) {
            // LD_hld_A;
            wram->wc992 = a;
            // LD_hl_B;
            wram->wc991 = b;
            // LD_B_A;
            // LD_HL(wMobileSDK_ReceivePacketBuffer + 6);
            // LD_DE(wc880);
            // CALL(aMobileSDK_CopyBytes);
            MobileSDK_CopyBytes(&wram->wc880, wram->wMobileSDK_ReceivePacketBuffer + 6, a);
            // JP(mFunction111d07);
            return Function111d07();
        }
        else {
        // asm_111c83:
            // LD_A(0xff);
            // LD_hld_A;
            wram->wc992 = 0xff;
            // LD_hl_B;
            wram->wc991 = b;
            // JR(mFunction111d07);
            return Function111d07();
        }
    }
    else {
    // asm_111c89:
        // CP_A(0xff);
        // IF_NZ goto asm_111c9d;
        if(wram->wc992 == 0xff) {
            // LD_HL(wc991);
            // LD_A_hli;
            // LD_B_A;
            uint8_t b = wram->wc991;
            // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
            // DEC_A;
            // CP_A_B;
            // IF_NC goto asm_111c5b;
            // IF_Z goto asm_111c5b;
            if(wram->wMobileSDK_ReceivePacketBuffer[3] - 1 >= b)
                goto asm_111c5b;
            // XOR_A_A;
            // LD_hl_A;
            wram->wc992 = 0x0;
        }

    // asm_111c9d:
        // LD_HL(wc991);
        // LD_A_hli;
        // SUB_A_hl;
        // LD_B_A;
        uint8_t b = wram->wc991 - wram->wc992;
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
        // DEC_A;
        // CP_A_B;
        // IF_NC goto asm_111c5b;
        // IF_Z goto asm_111c5b;
        if(wram->wMobileSDK_ReceivePacketBuffer[3] - 1 >= b)
            goto asm_111c5b;
        // LD_B_A;
        b = wram->wMobileSDK_ReceivePacketBuffer[3] - 1;
        // LD_L_hl;
        // LD_H(0x0);
        uint8_t l = wram->wc992;
        // ADD_A_L;
        // LD_addr_A(wc992);
        wram->wc992 = l + b;
        // LD_DE(wc880);
        // ADD_HL_DE;
        // LD_E_L;
        // LD_D_H;
        // LD_HL(wMobileSDK_ReceivePacketBuffer + 5);
        // CALL(aMobileSDK_CopyBytes);
        MobileSDK_CopyBytes((&wram->wc880) + l, wram->wMobileSDK_ReceivePacketBuffer + 5, b);
        // JR(mFunction111d07);
        return Function111d07();
    }

}

void Function111cc2(uint8_t* hl, uint16_t de, uint8_t c){
    // XOR_A_A;
    // CP_A_D;
    // IF_NZ goto asm_111cda;
    // LD_A_C;
    // CP_A_E;
    // IF_C goto asm_111cda;
    // IF_Z goto asm_111cda;
    if(c > de) {
        // LD_A_addr(wc821);
        // SET_A(2);
        // LD_addr_A(wc821);
        bit_set(wram->wc821, 2);
        // LD_A_C;
        uint8_t temp = LOW(de);
        // SUB_A_E;
        de = (c - de);
        // LD_C_E;
        c = temp;
        // LD_E_A;
        // goto asm_111ce1;
    }
    else {
    // asm_111cda:
        // LD_A_E;
        // SUB_A_C;
        // LD_E_A;
        // LD_A_D;
        // SBC_A(0x0);
        // LD_D_A;
        de -= c;
    }

// asm_111ce1:
    // LD_A_D;
    // LD_hld_A;
    hl[1] = HIGH(de);
    // LD_hl_E;
    hl[0] = LOW(de);
    // LD_A_addr(wc829);
    // LD_E_A;
    // LD_A_addr(wc82a);
    // LD_D_A;
    // LD_HL(wMobileSDK_ReceivePacketBuffer + 5);
    // LD_A_C;
    // OR_A_A;
    // JR_Z (mFunction111d07);
    if(c != 0) {
        // LD_B_A;
        // CALL(aMobileSDK_CopyBytes);
        // LD_HL(wc829);
        // LD_A_E;
        // LD_hli_A;
        // LD_hl_D;
        gMobileReceiveBuffer_Destination = MobileSDK_CopyBytes(gMobileReceiveBuffer_Destination, wram->wMobileSDK_ReceivePacketBuffer + 5, c);
        // LD_DE(0x3);
        // ADD_HL_DE;
        uint16_t de3 = wram->wc82d | (wram->wc82e << 8);
        // LD_A_hl;
        // ADD_A_C;
        // LD_hli_A;
        de3 += c;
        wram->wc82d = LOW(de3);
        wram->wc82e = HIGH(de3);
        // JR_NC (mFunction111d07);
        // INC_hl;
    }

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
    printf("Adapter type = %d\n", wram->wMobileSDK_AdapterType);
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

// MobileCommand_TelephoneStatus
void Function111d70(void){
    // LD_HL(wc822);
    // BIT_hl(0);
    // IF_Z goto asm_111dc0;
    if(bit_test(wram->wc822, 0)) {
        // LD_A_addr(wc805);
        // LD_addr_A(wc807);
        wram->wc807 = wram->wc805;
        // LD_A_addr(wMobileSDK_ReceivePacketBufferAlt + 4);
        // LD_B_A;
        // CALL(aFunction111dd9);
        uint8_t b = Function111dd9(wram->wMobileSDK_ReceivePacketBufferAlt[4], wram->wMobileSDK_ReceivePacketBufferAlt[4]);
        // CALL(aFunction111e15);
        Function111e15(b);
        // RES_hl(0);
        bit_reset(wram->wc822, 0);
        // LD_A_B;
        // CP_A(0x7);
        // IF_Z goto asm_111da9;
        if(b == 0x7) {
        // asm_111da9:
            // LD_HL(wc821);
            // RES_hl(4);
            bit_reset(wram->wc821, 4);
            // SET_hl(1);
            bit_set(wram->wc821, 1);
            // LD_A(0x11);
            // LD_addr_A(wc80f);
            wram->wc80f = 0x11;
            // LD_A(0x6);
            // LD_addr_A(wc807);
            wram->wc807 = 0x6;
            // RET;
            return;
        }
        // OR_A_A;
        // RET_NZ ;
        else if(b != 0)
            return;
        // LD_HL(wc821);
        // RES_hl(4);
        bit_reset(wram->wc821, 4);
        // SET_hl(1);
        bit_set(wram->wc821, 1);
        // LD_A_addr(wc822);
        // BIT_A(4);
        // IF_NZ goto asm_111dbb;
        if(bit_test(wram->wc822, 4)) {
        // asm_111dbb:
            // XOR_A_A;
            // LD_addr_A(wc807);
            wram->wc807 = 0x0;
            // RET;
            return;
        }
        else {
            // LD_A(0x23);
            // LD_addr_A(wc80f);
            wram->wc80f = 0x23;
            // LD_A(0x6);
            // LD_addr_A(wc807);
            wram->wc807 = 0x6;
            // RET;
            return;
        }
    }
    else {
    // asm_111dc0:
        // LD_HL(wc86e);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 4);
        // LD_B_A;
        // CALL(aFunction111dd9);
        uint8_t b = Function111dd9(wram->wMobileSDK_ReceivePacketBuffer[4], wram->wMobileSDK_ReceivePacketBuffer[4]);
        // CALL(aFunction111e15);
        Function111e15(b);
        // LD_A_B;
        // LD_hl_A;
        *gMobile_wc86e_wc86f = b;
        // LD_A_addr(wc805);
        // LD_addr_A(wc807);
        wram->wc807 = wram->wc805;
        // RET;
    }
}

uint8_t Function111dd9(uint8_t a, uint8_t b){
    // CP_A(0xff);
    // IF_Z goto asm_111de7;
    if(a != 0xff) {
        // OR_A_A;
        // RET_Z ;
        if(a == 0x0)
            return b;
        // CP_A(0x4);
        // IF_Z goto asm_111dea;
        else if(a == 0x4) {
        // asm_111dea:
            // LD_B(0x5);
            // LD_A_addr(wc822);
            // BIT_A(0);
            // IF_Z goto asm_111df8;
            // LD_A_addr(wc86a);
            // goto asm_111dfb;

        // asm_111df8:
            // LD_A_addr(wc985);

        // asm_111dfb:
            a = (!bit_test(wram->wc822, 0))? wram->wc985: wram->wc86a;
            // CP_A(0x4);
            // RET_Z ;
            // CP_A(0x1c);
            // RET_Z ;
            // CP_A(0x1a);
            // RET_Z ;
            if(a == 0x4 || a == 0x1c || a == 0x1a)
                return 0x5;
            // DEC_B;
            // CP_A(0x3);
            // RET_Z ;
            if(a == 0x3)
                return 0x4;
            // LD_B(0x1);
            // LD_A_addr(wc822);
            // BIT_A(4);
            // RET_Z ;
            if(!bit_test(wram->wc822, 4))
                return 0x1;
            // INC_B;
            // RET;
            return 0x2;
        }
        // CP_A(0x5);
        // IF_Z goto asm_111e12;
        else if(a == 0x5) {
        // asm_111e12:
            // LD_B(0x3);
            // RET;
            return 0x3;
        }
    }

// asm_111de7:
    // LD_B(0x7);
    // RET;
    return 0x7;

}

void Function111e15(uint8_t b){
    // LD_A_B;
    // AND_A(0x7);
    // RRCA;
    // RRCA;
    // RRCA;
    // PUSH_HL;
    // LD_L_A;
    // LD_A_addr(wc821);
    // AND_A(0x1f);
    // OR_A_L;
    // LD_addr_A(wc821);
    wram->wc821 = (wram->wc821 & 0x1f) | ((b & 0x7) << 5);
    // POP_HL;
    // RET;
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

// MobileSDK_SendCommandPacket
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

    // do {
    // // asm_111f17:
    //     finish_gb_cycle();
    //     // LDH_A_addr(rSC);
    //     // AND_A(1 << rSC_ON);
    //     // IF_NZ goto asm_111f17;
    // } while((gb_read(rSC) & (1 << rSC_ON)) != 0);
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

// Calculates the checksum of b bytes backwards starting at de.
// Stores the calculated checksum at de and de + 1 and the
// footer at de + 2 and de + 3.
// Returns the total size of the data plus the checksum and footer.
uint16_t Function111f63(void* de_, uint8_t b){
    // PUSH_DE;
    uint8_t* de = de_;
    uint8_t* de2 = de_;
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
    *(de2++) = HIGH(hl);
    // LD_A_E;
    // LD_hli_A;
    *(de2++) = LOW(hl);
    // LD_A(0x80);
    // LD_hli_A;
    *(de2++) = 0x80;
    // XOR_A_A;
    // LD_hl_A;
    *de2 = 0x0;
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
    printf("Jumptable_1121ac[%d](hl, %d)\n", c - 0xa, wram->wc86b + 1);
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
    return Jumptable_1121ac[c - 0xa](&wram->wc86b, ++wram->wc86b);
}

static void Jumptable_1121ac_Dummy(uint8_t* hl, uint8_t a) {
    (void)hl, (void)a;
}

const Jumptable_1121ac_t Jumptable_1121ac[] = {
    Function1121f6,
    Function112271, //dw ['Function112271'];
    Function112373, //dw ['Function112373'];
    Function1123b6, //dw ['Function1123b6'];
    Function1123e1, //dw ['Function1123e1'];
    Function112451, //dw ['Function112451'];
    Function112715, //dw ['Function112715'];
    Jumptable_1121ac_Dummy, //dw ['Function11273a'];
    Jumptable_1121ac_Dummy, //dw ['Function11299c'];
    Function112d33, //dw ['Function112d33'];
    Function112d33, //dw ['Function112d33'];
    Jumptable_1121ac_Dummy, //dw ['Function112840'];
    Jumptable_1121ac_Dummy, //dw ['Function1128db'];
    Jumptable_1121ac_Dummy, //dw ['Function112969'];
    Jumptable_1121ac_Dummy, //dw ['Function112a56'];
    Jumptable_1121ac_Dummy, //dw ['Function112b71'];
    Function112bec, //dw ['Function112bec'];
    Function112bbb, //dw ['Function112bbb'];
    Function112bec, //dw ['Function112bec'];
    Jumptable_1121ac_Dummy, //dw ['Function112b71'];
    Function1134cb, //dw ['Function1134cb'];
    Function112d33, //dw ['Function112d33'];
    Function112d33, //dw ['Function112d33'];
    Function112d33, //dw ['Function112d33'];
    Function112d33, //dw ['Function112d33'];
    Function112d33, //dw ['Function112d33'];
    Function112d33, //dw ['Function112d33'];
    Function113519, //dw ['Function113519'];
    Function113519, //dw ['Function113519'];
    Function113519, //dw ['Function113519'];
    Jumptable_1121ac_Dummy, //dw ['Function113e42'];
    Jumptable_1121ac_Dummy, //dw ['Function113ef2'];
    Jumptable_1121ac_Dummy, //dw ['Function113f2d'];
    Function1121f6, //dw ['Function1121f6'];
    Function1134cb, //dw ['Function1134cb'];
    Jumptable_1121ac_Dummy, //dw ['Function113672'];
    Function113626, //dw ['Function113626'];
};

void Function1121f6(uint8_t* hl, uint8_t a){
    // DEC_A;
    // IF_Z goto asm_1121fe;
    if(a == 1) {
    // asm_1121fe:
        // LD_A_addr(wMobileSDK_AdapterType);
        // OR_A_A;
        // IF_Z goto asm_112206;
        if(wram->wMobileSDK_AdapterType == 0) {
        // asm_112206:
            // LD_A(0x10);
            // CALL(aFunction11225d);
            uint8_t* hl2 = Function11225d(0x10);
            // RES_hl(0);
            bit_reset(*hl2, 0);
            // SET_hl(1);
            bit_set(*hl2, 1);
            // RET;
            return;
        }
        // JR(mFunction112269);
        Function112269();
        return;
    }
    // DEC_A;
    // IF_Z goto asm_112210;
    else if(a == 2) {
    // asm_112210:
        // LD_HL(wc86e);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        uint8_t* hl2 = gMobile_wc86e_wc86f;
        // LD_A_addr(wMobileSDK_AdapterType);
        // CP_A(0x88);
        // IF_C goto asm_112249;
        if(wram->wMobileSDK_AdapterType >= 0x88) {
            // SUB_A(0x88);
            uint8_t a2 = wram->wMobileSDK_AdapterType - 0x88;
            // LD_hl_A;
            *hl2 = a2;

        // There aren't more than four adapters
            // CP_A(0x4);
            // IF_C goto asm_112226;
            if(a2 >= 0x4) {
                // LD_A(0x3);
                a2 = 0x3;
            }

        // asm_112226:
        // The green adapter was scrapped, so the red adapter is the third
            // CP_A(0x3);
            // IF_NZ goto asm_11222b;
            // DEC_A;
            if(a2 == 0x3)
                --a2;

        // asm_11222b:
            // LD_B_A;
            uint8_t b = a2;
            // LD_A(0x4);
            // SUB_A_B;
            // LD_D_A;
            uint8_t d = 0x4 - b;
            // RLCA;
            // ADD_A_D;
            // LD_C_A;
            uint8_t c = ((d << 1) | (d >> 7)) + d;
            // XOR_A_A;
            // CP_A_B;
            // IF_Z goto asm_11223a;
            if(b != 0) {
                // LD_A(0x3);
                // XOR_A_B;
                b = 0x3 ^ b;
            }

        // asm_11223a:
            // LD_HL(wc871);
            // LD_hld_A;
            wram->wc871 = b;
            // LD_hl_C;
            wram->wc870 = c;
            // LD_A_addr(wc86a);
            // CP_A(0xa);
            // JR_NZ (mFunction112251);
            if(wram->wc86a != 0xa)
                return Function112251();
            // JP(mFunction1116a0);
            return Function1116a0();
        }

    // asm_112249:
        // LD_A(0x10);
        // CALL(aFunction11225d);
        uint8_t* hl3 = Function11225d(0x10);
        // JP(mFunction1116a4);
        return Function1116a4(hl3);
    }
    // DEC_hl;
    (*hl)--;
    // RET;
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

uint8_t* Function11225d(uint8_t a){
    // LD_addr_A(wc80f);
    wram->wc80f = a;
    // LD_A(0x5);
    // LD_addr_A(wc86a);
    wram->wc86a = 0x5;
    // LD_HL(wc821);
    // RET;
    return &wram->wc821;
}

// Mobile_SendEndSession
bool Function112269(void){
    // LD_A(MOBILE_COMMAND_END_SESSION | 0x80);
    // LD_HL(mMobilePacket_EndSession);
    // JP(mPacketSendEmptyBody);
    return PacketSendEmptyBody(MobilePacket_EndSession, MOBILE_COMMAND_END_SESSION | 0x80);
}

void Function112271(uint8_t* hl, uint8_t a){
    // DEC_A;
    // IF_Z goto asm_11228c;
    if(a == 0x1) {
    // asm_11228c:
        // LD_HL(mMobilePacket_ReadConfigurationDataPart1);
        // JP(mFunction11236b);
        Function11236b(MobilePacket_ReadConfigurationDataPart1);
        return;
    }
    // DEC_A;
    // IF_Z goto asm_112292;
    else if(a == 0x2) {
    // asm_112292:
        // LD_HL(wc829);
        // LD_A(0xe0);
        // LD_hli_A;
        // LD_A(0xc8);
        // LD_hli_A;
        gMobileReceiveBuffer_Destination = (uint8_t*)wram->wc880_str + 0x60;
        // LD_HL(mMobilePacket_ReadConfigurationDataPart2);
        // JP(mFunction11236b);
        Function11236b(MobilePacket_ReadConfigurationDataPart2);
        return;
    }
    // DEC_A;
    // IF_Z goto asm_1122a1;
    else if(a == 0x3) {
    // asm_1122a1:
        // LD_HL(wc880);
        // LD_A_hli;
        // CP_A(0x4d);
        // IF_NZ goto asm_1122f5;
        // LD_A_hld;
        // CP_A(0x41);
        // IF_NZ goto asm_1122f5;
        if(wram->wc880 == 0x4d && wram->wc881 == 0x41) {
            uint8_t* hl2 = (uint8_t*)wram->wc880_str;
            // LD_B(0xbe);
            uint8_t b = 0xbe;
            // LD_DE(0);
            uint16_t de = 0;

            do {
            // asm_1122b3:
                // LD_A_hli;
                // ADD_A_E;
                // LD_E_A;
                // LD_A(0x0);
                // ADC_A_D;
                // LD_D_A;
                de += *(hl2++);
                // DEC_B;
                // IF_NZ goto asm_1122b3;
            } while(--b != 0);
            // LD_A_hli;
            // CP_A_D;
            // IF_NZ goto asm_1122fc;
            uint16_t de2 = (hl2[0] << 8) | hl2[1];
            // LD_A_hl;
            // CP_A_E;
            // IF_NZ goto asm_1122fc;
            if(de == de2) {
                // LD_HL(wc884);
                // LD_DE(wc836);
                // LD_B(0x8);
                // CALL(aMobileSDK_CopyBytes);
                MobileSDK_CopyBytes(wram->wc836, wram->wc884, 8);
                // LD_HL(wc8ca);
                // LD_B(0x2c);
                // CALL(aMobileSDK_CopyBytes);
                MobileSDK_CopyBytes(wram->wc83e, wram->wc8ca, 0x2c);
                // LD_A_addr(wMobileSDK_PacketBuffer + 50);
                // LD_C_A;
                uint8_t c = wram->wMobileSDK_PacketBuffer[50];
                // SUB_A(0x8);
                // LD_E_A;
                // LD_D(0);
                // LD_HL(wMobileSDK_PacketBuffer + 51);
                // ADD_HL_DE;
                // LD_E_L;
                // LD_D_H;
                // LD_HL(wc836);
                // LD_B(0x8);
                // CALL(aMobileSDK_CopyBytes);
                uint8_t* dest = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 51 + (c - 0x8), wram->wc836, 0x8);
                // LD_B_C;
                // CALL(aFunction111f63);
                Function111f63(dest, c);
                // JR(mFunction11235a);
                Function11235a();
                return;
            }
        
        // asm_1122fc:
            // LD_A(0x14);
            // LD_addr_A(wc872);
            wram->wc872 = 0x14;
        }
        else {
        // asm_1122f5:
            // LD_A(0x25);
            // LD_addr_A(wc872);
            // goto asm_112301;
            wram->wc872 = 0x25;
        }

    // asm_112301:
        // LD_A(0x6);
        // LD_addr_A(wc86b);
        wram->wc86b = 0x6;
        // JP(mFunction112269);
        Function112269();
        return;
    }
    // DEC_A;
    // JP_Z (mFunction112271_asm_112309);
    else if(a == 0x4) {
    // asm_112309:
        // LD_A_addr(wc821);
        // AND_A(0xe0);
        // IF_NZ goto asm_112314;
        if((wram->wc821 & 0xe0) == 0x0) {
            // LD_B(0x92);
            // JR(mFunction11234b);
            Function11234b(MOBILE_COMMAND_DIAL_TELEPHONE | 0x80);
            return;
        }

    // asm_112314:
        // CP_A(0xe0);
        // LD_A(0x11);
        // IF_Z goto asm_11231b;
        // INC_A;

    // asm_11231b:
        // LD_addr_A(wc872);
        wram->wc872 = ((wram->wc821 & 0xe0) == 0xe0)? 0x11: 0x12;
        // LD_A(0x6);
        // LD_addr_A(wc86b);
        wram->wc86b = 0x6;
        // JP(mFunction112269);
        Function112269();
        return;
    }
    // DEC_A;
    // JP_Z (mFunction112271_asm_112326);
    else if(a == 0x5) {
    // asm_112326:
        // LD_D_A;
        // LD_A_addr(wMobileSDK_PacketBuffer + 50);
        // ADD_A(0xa);
        // LD_E_A;
        uint16_t de = (wram->wMobileSDK_PacketBuffer[50] + 0xa);
        // LD_HL(wMobileSDK_PacketBuffer + 45);
        // LD_A(0xa1);
        // JP(mFunction111f02);
        Function111f02(wram->wMobileSDK_PacketBuffer + 45, de, MOBILE_COMMAND_ISP_LOGIN | 0x80);
        return;
    }
    // DEC_A;
    // JP_Z (mFunction112271_asm_112335);
    else if(a == 0x6) {
    // asm_112335:
        // LD_A(0x2);
        // LD_addr_A(wc86a);
        wram->wc86a = 0x2;
        // LD_HL(wc821);
        // RES_hl(0);
        bit_reset(wram->wc821, 0);
        // SET_hl(5);
        bit_set(wram->wc821, 5);
        // RET;
        return;
    }
    // DEC_A;
    // JP_Z (mFunction112271_asm_112342);
    else if(a == 0x7) {
    // asm_112342:
        // LD_A_addr(wc872);
        // CALL(aFunction11225d);
        // JP(mFunction1116a4);
        Function1116a4(Function11225d(wram->wc872));
        return;
    }
    else {
        // DEC_hl;
        (*hl)--;
        // RET;
    }
}

// MobileSDK_SendPacketCommandDynamic
void Function11234b(uint8_t b){
    // LD_A_addr(wMobileSDK_PacketBuffer + 5);
    // ADD_A(0xa);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wMobileSDK_PacketBuffer);
    // LD_A_B;
    // JP(mFunction111f02);
    Function111f02(wram->wMobileSDK_PacketBuffer, wram->wMobileSDK_PacketBuffer[5] + 0xa, b);
}

void Function11235a(void){
    // LD_HL(wc86e);
    // LD_A(0x80);
    // LD_hli_A;
    // LD_A(0xc8);
    // LD_hl_A;
    gMobile_wc86e_wc86f = (uint8_t*)wram->wc880_str;
    // LD_A(MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
    // LD_HL(mMobilePacket_TelephoneStatus);
    // JP(mPacketSendEmptyBody);
    PacketSendEmptyBody(MobilePacket_TelephoneStatus, MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
}

// MobileSDK_ReadConfigurationData
bool Function11236b(const uint8_t* hl){
    // LD_A(0x99);
    // LD_DE(0x000c);
    // JP(mFunction111f02);
    return Function111f02(hl, 0x000c, MOBILE_COMMAND_READ_CONFIGURATION_DATA | 0x80);
}

void Function112373(uint8_t* hl, uint8_t a){
    // DEC_A;
    // JR_Z (mFunction11235a);
    if(a == 0x1)
        return Function11235a();
    // DEC_A;
    // IF_Z goto asm_112381;
    else if(a == 0x2) {
    // asm_112381:
        // LD_A_addr(wc821);
        // AND_A(0xe0);
        // IF_NZ goto asm_11238c;
        if((wram->wc821 & 0xe0) == 0x0) {
            // LD_B(0x92);
            // JR(mFunction11234b);
            return Function11234b(0x92);
        }

    // asm_11238c:
        // CP_A(0xe0);
        // LD_A(0x11);
        // IF_Z goto asm_112393; // Useless branch
        // INC_A;

    // asm_112393:
        // LD_A(0x3);
        // LD_addr_A(wc86b);
        wram->wc86b = 0x3;
        // JP(mFunction112269);
        Function112269();
        return;
    }
    // DEC_A;
    // IF_Z goto asm_11239b;
    else if(a == 0x3) {
    // asm_11239b:
        // LD_HL(wc822);
        // SET_hl(4);
        bit_set(wram->wc822, 4);
        // LD_A(0x2);
        // LD_addr_A(wc86a);
        wram->wc86a = 0x2;
        // LD_HL(wc821);
        // RES_hl(0);
        bit_reset(wram->wc821, 0);
        // SET_hl(6);
        bit_set(wram->wc821, 6);
        // RET;
        return;
    }
    // DEC_A;
    // IF_Z goto asm_1123ad;
    else if(a == 0x4) {
    // asm_1123ad:
        // LD_A_addr(wc872);
        // CALL(aFunction11225d);
        // JP(mFunction1116a4);
        Function1116a4(Function11225d(wram->wc872));
        return;
    }
    else {
        // DEC_hl;
        (*hl)--;
        // RET;
    }
}

void Function1123b6(uint8_t* hl, uint8_t a){
    // DEC_A;
    // IF_Z goto asm_1123be;
    if(a == 0x1) {
    asm_1123be:
        // LD_A(MOBILE_COMMAND_WAIT_FOR_TELEPHONE_CALL | 0x80);
        // LD_HL(mMobilePacket_WaitForTelephoneCall);
        // JP(mPacketSendEmptyBody);
        PacketSendEmptyBody(MobilePacket_WaitForTelephoneCall, MOBILE_COMMAND_WAIT_FOR_TELEPHONE_CALL | 0x80);
        return;
    }
    // DEC_A;
    // IF_Z goto asm_1123c6;
    else if(a == 0x2) {
    // asm_1123c6:
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
        // CP_A(0xee);
        // IF_Z goto asm_1123bd;
        if(wram->wMobileSDK_ReceivePacketBuffer[0] == 0xee) {
        // asm_1123bd:
            // DEC_hl;
            (*hl)--;
            goto asm_1123be;
        }
        // LD_HL(wc822);
        // SET_hl(4);
        bit_set(wram->wc822, 4);
        // LD_A(0x2);
        // LD_addr_A(wc86a);
        wram->wc86a = 0x2;
        // LD_HL(wc821);
        // RES_hl(0);
        bit_reset(wram->wc821, 0);
        // SET_hl(6);
        // SET_hl(5);
        wram->wc821 |= (1 << 6) | (1 << 5);
        // RET;
        return;
    }
    // RET;
}

void Function1123e1(uint8_t* hl, uint8_t a){
    // DEC_A;
    // IF_Z goto asm_1123f2;
    if(a == 0x1) {
    // asm_1123f2:
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
        // CP_A(0x9f);
        // IF_Z goto asm_112408;
        // CALL(aFunction1127e1);
        // IF_Z goto asm_112408;
        if(wram->wMobileSDK_ReceivePacketBuffer[0] != 0x9f && !Function1127e1()) {
            // LD_HL(wc86b);
            // DEC_hl;
            --wram->wc86b;
            // LD_HL(wMobileSDK_PacketBuffer + 32);
            // JP(mFunction1127c5);
            return Function1127c5(wram->wMobileSDK_PacketBuffer + 32);
        }

    // asm_112408:
        // JR(mFunction112430);
        return Function112430();
    }
    // DEC_A;
    // IF_Z goto asm_11240a;
    else if(a == 0x2) {
    // asm_11240a:
        // XOR_A_A;
        // LD_addr_A(wc86d);
        wram->wc86d = 0x0;
        // LD_A(MOBILE_COMMAND_ISP_LOGOUT | 0x80);
        // LD_HL(mMobilePacket_ISPLogout);
        // JP(mPacketSendEmptyBody);
        PacketSendEmptyBody(MobilePacket_ISPLogout, MOBILE_COMMAND_ISP_LOGOUT | 0x80);
        return;
    }
    // DEC_A;
    // IF_Z goto asm_112416;
    else if(a == 0x3) {
    // asm_112416:
        // LD_A(MOBILE_COMMAND_HANG_UP_TELEPHONE | 0x80);
        // LD_HL(mMobilePacket_HangUpTelephone);
        // JP(mPacketSendEmptyBody);
        PacketSendEmptyBody(MobilePacket_HangUpTelephone, MOBILE_COMMAND_HANG_UP_TELEPHONE | 0x80);
        return;
    }
    // DEC_A;
    // IF_Z goto asm_11241e;
    else if(a == 0x4) {
    // asm_11241e:
        // JP(mFunction112269);
        Function112269();
        return;
    }
    // DEC_A;
    // IF_Z goto asm_112421;
    else if(a == 0x5) {
    // asm_112421:
        // LD_HL(wc822);
        // RES_hl(4);
        bit_reset(wram->wc822, 4);
        // LD_HL(wc821);
        // LD_A_hl;
        // AND_A(0xf);
        // LD_hl_A;
        wram->wc821 = (wram->wc821 & 0xf);
        // JP(mFunction1116a0);
        return Function1116a0();
    }
    // DEC_hl;
    (*hl)--;
    // RET;
}

// MobileSDK_CloseTCPConnection
void Function112430(void){
    // LD_A(0x3);
    // LD_addr_A(wc807);
    wram->wc807 = 0x3;
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_CloseTCPConnection);
    // LD_B(lengthof(MobilePacket_CloseTCPConnection));
    // CALL(aMobileSDK_CopyBytes);
    uint8_t* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_CloseTCPConnection, sizeof(MobilePacket_CloseTCPConnection));
    // LD_A_addr(wc86c);
    // LD_de_A;
    *de = wram->wc86c;
    // INC_DE;
    de++;
    // INC_B; // b = 1?
    // CALL(aFunction111f63);
    uint16_t size = Function111f63(de, 0x1);
    // LD_A(0xa4);
    // LD_HL(wMobileSDK_PacketBuffer);
    // JP(mFunction111f02);
    Function111f02(wram->wMobileSDK_PacketBuffer, size, MOBILE_COMMAND_CLOSE_TCP_CONNECTION | 0x80);
}

void Function112451(uint8_t* hl, uint8_t a){
    (void)hl;
    // DEC_A;
    // IF_Z goto asm_112458;
    if(a == 0x1) {
    // asm_112458:
        // LD_B(0x6);
        // LD_DE(wMobileSDK_PacketBuffer + 92);
        // CALL(aFunction111f63);
        Function111f63(wram->wMobileSDK_PacketBuffer + 92, 6);
        // LD_A_addr(wc86e);
        // INC_A;
        // CP_A(0x3);
        // IF_NZ goto asm_11248b;
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 128);
        // OR_A_A;
        // IF_Z goto asm_11248b;
        // LD_HL(wc995);
        // LD_A_hli;
        // CP_A(0x99);
        // IF_NZ goto asm_112480;
        // LD_A_hli;
        // CP_A(0x66);
        // IF_NZ goto asm_112480;
        // LD_A_hli;
        // CP_A(0x23);
        // IF_Z goto asm_11248b;
        if(wram->wc86e + 1 == 0x3 && wram->wMobileSDK_ReceivePacketBuffer[128] != 0
        && (wram->wc995[0] != 0x99 || wram->wc995[1] != 0x66 || wram->wc995[2] != MOBILE_COMMAND_OPEN_TCP_CONNECTION)) {
        // asm_112480:
            // LD_HL(wMobileSDK_PacketBuffer + 80);
            // LD_DE(wc995);
            // LD_B(0x10);
            // CALL(aMobileSDK_CopyBytes);
            MobileSDK_CopyBytes(wram->wc995, wram->wMobileSDK_PacketBuffer + 80, 0x10);
        }

    // asm_11248b:
        printf("TCP %u.%u.%u.%u:%u\n", wram->wMobileSDK_PacketBuffer[86], wram->wMobileSDK_PacketBuffer[87],
            wram->wMobileSDK_PacketBuffer[88], wram->wMobileSDK_PacketBuffer[89],
            (wram->wMobileSDK_PacketBuffer[90] << 8) | wram->wMobileSDK_PacketBuffer[91]);
        // LD_A(0xa3);
        // LD_DE(0x0010);
        // LD_HL(wMobileSDK_PacketBuffer + 80);
        // JP(mFunction111f02);
        Function111f02(wram->wMobileSDK_PacketBuffer + 80, 0x0010, MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80);
        return;
    }
    // DEC_A;
    // IF_Z goto asm_112496;
    else if(a == 0x2) {
    // asm_112496:
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
        // CP_A(0xa3);
        // IF_Z goto asm_1124ce;
        if(wram->wMobileSDK_ReceivePacketBuffer[0] != (MOBILE_COMMAND_OPEN_TCP_CONNECTION | 0x80)) {
            // LD_A_addr(wc822);
            // BIT_A(3);
            // IF_Z goto asm_1124ab;
            if(bit_test(wram->wc822, 3)) {
                // DEC_hl;
                (*hl)--;
                // LD_A(0x3);
                // LD_addr_A(wc807);
                wram->wc807 = 0x3;
                // RET;
                return;
            }
        // asm_1124ab:
            // LD_A_addr(wc9af);
            // CP_A(0x5);
            // IF_C goto asm_1124b8;
            else if((wram->wc9af & 0xff) >= 0x5) {
                // LD_HL(wc821);
                // SET_hl(1);
                bit_set(wram->wc821, 1);
                // RET;
                return;
            }
            else {
            // asm_1124b8:
                // DEC_hl;
                (*hl)--;
                // LD_HL(wc9af);
                // INC_hl;
                wram->wc9af = (wram->wc9af & 0xff00) | ((wram->wc9af + 1) & 0xff);
                // LD_HL(wc822);
                // SET_hl(3);
                bit_set(wram->wc822, 3);
                // LD_HL(wc815);
                // LD_A_addr(wc820);
                // LD_hli_A;
                wram->wc815 = wram->wc820;
                // LD_A_addr(wc81f);
                // LD_hl_A;
                wram->wc816 = wram->wc81f;
                // RET;
                return;
            }
        }

    // asm_1124ce:
        // XOR_A_A;
        // LD_addr_A(wc9af);
        wram->wc9af = (wram->wc9af & 0xff00);
        // LD_A_addr(wc86e);
        // INC_A;
        // LD_addr_A(wc86d);
        wram->wc86d = wram->wc86e + 1;
        // DEC_A;
        // JP_Z (mFunction11261c);
        if(wram->wc86d == 1)
            return Function11261c();
        // DEC_A;
        // JP_Z (mFunction112654);
        if(wram->wc86d == 2)
            return Function112654();
        // DEC_A;
        // JP_Z (mFunction112597);
        if(wram->wc86d == 3)
            return Function112597();
        // DEC_A;
        // JP_Z (mFunction112566);
        if(wram->wc86d == 4)
            return Function112566();
        // CALL(aFunction1125c7);
        char* de = Function1125c7();
        // PUSH_DE;
        // LD_DE(wc880);
        // LD_HL(wc827);
        // LD_A_E;
        // LD_hli_A;
        // LD_A_D;
        // LD_hli_A;
        gMobile_wc827 = &wram->wc880;
        // LD_A_E;
        // LD_hli_A;
        // LD_A_D;
        // LD_hli_A;
        gMobileReceiveBuffer_Destination = &wram->wc880;
        // LD_A(0x1);
        // LD_addr_A(wc86e);
        wram->wc86e = 0x1;
        // LD_A(0xfa);
        // LD_hli_A;
        wram->wc82b = 0xfa;
        // XOR_A_A;
        // LD_hli_A;
        wram->wc82c = 0x0;
        // XOR_A_A;
        // LD_hli_A;
        wram->wc82d = 0x0;
        // LD_hli_A;
        wram->wc82e = 0x0;
        // POP_DE;
        // LD_A(0x1);
        // LD_addr_A(wc994);
        wram->wc994 = HTTP_METHOD_POST;
        // CALL(aFunction11269b);
        uint16_t bc = 0;
        de = Function11269b(de, &bc);
        // LD_A(0x5);
        // LD_addr_A(wc86b);
        wram->wc86b = 0x5;
        // CALL(aFunction112534);
        Function112534(de, LOW(bc));
        // LD_A_addr(wc9a5);
        // OR_A_A;
        // IF_Z goto asm_112521;
        // LD_A(0x1);


    // asm_112521:
        // ADD_A(0x23);
        // LD_addr_A(wc86a);
        wram->wc86a = ((wram->wc9a5[0] == 0)? 0: 1) + 0x23;
        // LD_A_addr(wc98a);
        // CP_A(0x2);
        // IF_NZ goto asm_112531;
        if(wram->wc98a == 0x2) {
            // XOR_A_A;
            // LD_addr_A(wc9a5);
            wram->wc9a5[0] = 0;
        }

    // asm_112531:
        // JP(mFunction1125bf);
        return Function1125bf();
    }
    // RET;
}

void Function112534(char* de, uint8_t c){
    // LD_B(0xfa);
    // LD_HL(wc880);
    uint8_t* hl = &wram->wc880;
    // XOR_A_A;

    for(uint8_t i = 0; i < 0xfa; ++i) {
    // asm_11253a:
        // LD_hli_A;
        hl[i] = 0;
        // DEC_B;
        // IF_NZ goto asm_11253a;
    }
    // LD_A_addr(wc876);
    // LD_addr_A(wc87c);
    // LD_A_addr(wc877);
    // LD_addr_A(wc87d);
    gMobile_wc87c_wc87d = gMobile_wc876;
    // LD_A_addr(wc87a);
    // LD_addr_A(wc87e);
    wram->wc87e = wram->wc87a;
    // LD_A_addr(wc87b);
    // LD_addr_A(wc87f);
    wram->wc87f = wram->wc87b;
    // LD_A_C;
    // LD_addr_A(wMobileSDK_PacketBuffer + 17);
    wram->wMobileSDK_PacketBuffer[17] = c;
    // LD_B_C;
    // CALL(aFunction111f63);
    uint16_t size = Function111f63(de, c);
    // LD_A(0x95);
    // LD_HL(wMobileSDK_PacketBuffer + 12);
    // JP(mFunction111f02);
    Function111f02(wram->wMobileSDK_PacketBuffer + 12, size, MOBILE_COMMAND_TRANSFER_DATA | 0x80);
}

void Function112566(void){
    // CALL(aFunction1125c7);
    char* de = Function1125c7();
    // LD_A_addr(wMobileSDK_PacketBuffer + 19);
    // AND_A(0x1);
    // OR_A_A;
    // IF_NZ goto asm_11257d;
    // LD_A_addr(wc98a);
    // CP_A(0x2);
    // IF_NZ goto asm_11257d;
    if((wram->wMobileSDK_PacketBuffer[19] & 0x1) == 0 && wram->wc98a == 0x2) {
        // LD_A(0x1);
        // LD_addr_A(wc994);
        wram->wc994 = HTTP_METHOD_POST;
    }

// asm_11257d:
    // CALL(aFunction11269b);
    uint16_t bc = 0;
    de = Function11269b(de, &bc);
    // LD_A(0x5);
    // LD_addr_A(wc86b);
    wram->wc86b = 0x5;
    // CALL(aFunction112534);
    Function112534(de, LOW(bc));
    // LD_A_addr(wc9a5);
    // OR_A_A;
    // IF_Z goto asm_112590;
    // LD_A(0x1);


// asm_112590:
    // ADD_A(0x21);
    // LD_addr_A(wc86a);
    wram->wc86a = 0x21 + ((wram->wc9a5[0] == 0)? 0: 1);
    // JR(mFunction1125bf);
    return Function1125bf();
}

void Function112597(void){
    uint16_t bc;
    // CALL(aFunction1125c7);
    char* de = Function1125c7();
    // CALL(aFunction11269b);
    de = Function11269b(de, &bc);
    // LD_A(0x5);
    // LD_addr_A(wc86b);
    wram->wc86b = 0x5;
    // CALL(aFunction112534);
    Function112534(de, LOW(bc));
    // LD_A_addr(wc98f);
    // LD_B_A;
    if(!bit_test(wram->wc98f, 0)) {
        // LD_A_addr(wc994);
        // AND_A(0x1);
        // ADD_A(0x13);
        wram->wc86a = (wram->wc994 & 1) + 0x13;
        // BIT_B(0);
        // IF_Z goto asm_1125bc;
    }
    else {
        // SUB_A(0x13);
        // ADD_A(0x1f);
        // DEC_B;
        // SLA_B;
        // ADD_A_B;
        wram->wc86a = ((wram->wc994 & 1) + 0x1f) + ((wram->wc98f - 1) << 1);
    }

// asm_1125bc:
    // LD_addr_A(wc86a);
    printf("wc86a=%d, wc86b=%d, wc98f=%d\n", wram->wc86a, wram->wc86b, wram->wc98f);

    return Function1125bf();
}

void Function1125bf(void){
    // LD_HL(wc821);
    // SET_hl(0);
    bit_set(wram->wc821, 0);
    // RES_hl(2);
    bit_reset(wram->wc821, 2);
    // RET;
}

char* Function1125c7(void){
    // LD_HL(wc872);
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    // LD_A_addr(wc994);
    // AND_A(0x1);
    // XOR_A(0x1);
    // LD_addr_A(wc86b);
    wram->wc86b = (wram->wc994 & 1) ^ 1;
    // LD_HL(wc827);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    gMobile_wc827 = gMobile_wc874_wc875;
    // INC_DE;
    // INC_DE;
    // LD_A(0x80);
    // LD_hli_A;
    // LD_A(0xc8);
    // LD_hli_A;
    gMobileReceiveBuffer_Destination = &wram->wc880;
    // DEC_BC;
    // DEC_BC;
    // LD_A(0xfa);
    // LD_hli_A;
    wram->wc82b = 0xfa;
    // LD_A(0x0);
    // LD_hli_A;
    wram->wc82c = 0x0;
    // XOR_A_A;
    // LD_hli_A;
    wram->wc82d = 0x0;
    // LD_hli_A;
    wram->wc82e = 0x0;
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_TransferData);
    // LD_B(0x6);
    // CALL(aMobileSDK_CopyBytes);
    char* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_TransferData, 0x6);
    // LD_A_addr(wc86c);
    // LD_de_A;
    // INC_DE;
    *(de++) = wram->wc86c;
    // LD_B(0x1);
    // CALL(aFunction111f63);
    Function111f63(de, 0x1);
    // LD_DE(wMobileSDK_PacketBuffer + 12);
    // LD_HL(mMobilePacket_TransferData);
    // LD_B(0x5);
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 12, MobilePacket_TransferData, 0x5);
    // INC_DE;
    de++;
    // LD_A_addr(wc86c);
    // LD_de_A;
    *de = wram->wc86c;
    // INC_DE;
    // RET;
    return ++de;
}

void Function11261c(void){
    // XOR_A_A;
    // LD_addr_A(wc86b);
    wram->wc86b = 0x0;
    // LD_A_addr(wc86c);
    // LD_addr_A(wMobileSDK_PacketBuffer + 118);
    wram->wMobileSDK_PacketBuffer[118] = wram->wc86c;
    // LD_DE(wMobileSDK_PacketBuffer + 102);
    uint8_t* de = wram->wMobileSDK_PacketBuffer + 102;
    // LD_de_A;
    // INC_DE;
    *(de++) = wram->wc86c;
    // LD_B(0x1);
    // CALL(aFunction111f63);
    Function111f63(de, 0x1);
    // CALL(aFunction112724);
    Function112724();
    // LD_A_addr(wMobileSDK_PacketBuffer + 117);
    // LD_B_A;
    uint8_t b = wram->wMobileSDK_PacketBuffer[117];
    // LD_DE(wMobileSDK_PacketBuffer + 118);
    // ADD_A_E;
    // LD_E_A;
    // LD_A(0x0);
    // ADC_A_D;
    // LD_D_A;
    // CALL(aFunction111f63);
    Function111f63(wram->wMobileSDK_PacketBuffer + 118 + b, b);
    // LD_HL(wMobileSDK_PacketBuffer + 96);
    // CALL(aFunction1127c5);
    Function1127c5(wram->wMobileSDK_PacketBuffer + 96);
    // LD_A(0x11);
    // LD_addr_A(wc86a);
    wram->wc86a = 0x11;

    return Function11264e();
}

// SetWc821Bit0
void Function11264e(void){
    // LD_HL(wc821);
    // SET_hl(0);
    bit_set(wram->wc821, 0);
    // RET;
}

void Function112654(void){
    // XOR_A_A;
    // LD_addr_A(wc86b);
    wram->wc86b = 0x0;
    // LD_A_addr(wc86c);
    uint8_t a = wram->wc86c;
    // LD_addr_A(wMobileSDK_PacketBuffer + 102);
    wram->wMobileSDK_PacketBuffer[102] = a;
    // LD_addr_A(wMobileSDK_PacketBuffer + 166);
    wram->wMobileSDK_PacketBuffer[166] = a;
    // LD_DE(wMobileSDK_PacketBuffer + 134);
    // LD_de_A;
    // INC_DE;
    wram->wMobileSDK_PacketBuffer[134] = a;
    // LD_B(0x1);
    // CALL(aFunction111f63);
    Function111f63(wram->wMobileSDK_PacketBuffer + 135, 0x1);
    // CALL(aFunction112724);
    Function112724();
    // LD_A_addr(wMobileSDK_PacketBuffer + 165);
    // LD_B_A;
    uint8_t b = wram->wMobileSDK_PacketBuffer[165];
    // LD_DE(wMobileSDK_PacketBuffer + 166);
    // ADD_A_E;
    // LD_E_A;
    // LD_A(0x0);
    // ADC_A_D;
    // LD_D_A;
    // CALL(aFunction111f63);
    Function111f63(wram->wMobileSDK_PacketBuffer + 166 + b, b);
    // LD_A_addr(wMobileSDK_PacketBuffer + 101);
    // LD_B_A;
    b = wram->wMobileSDK_PacketBuffer[101];
    // LD_DE(wMobileSDK_PacketBuffer + 102);
    // ADD_A_E;
    // LD_E_A;
    // LD_A(0x0);
    // ADC_A_D;
    // LD_D_A;
    // CALL(aFunction111f63);
    Function111f63(wram->wMobileSDK_PacketBuffer + 102 + b, b);
    // LD_HL(wMobileSDK_PacketBuffer + 128);
    // CALL(aFunction1127c5);
    Function1127c5(wram->wMobileSDK_PacketBuffer + 128);
    // LD_A(0x12);
    // LD_addr_A(wc86a);
    wram->wc86a = 0x12;
    // JR(mFunction11264e);
    return Function11264e();

}

// MobileSDK_CopyGETOrPOSTString
char* Function11269b(char* de, uint16_t* bc){
    // LD_BC(0x0001);
    *bc = 0x0001;
    // LD_HL(mUnknown_112110);
    // LD_A_addr(wc994);
    // OR_A_A;
    // CALL_NZ (aFunction1126ac);
    const char* hl = (wram->wc994 == HTTP_METHOD_GET)? Unknown_112110: Unknown_112137;
    // CALL(aMobileSDK_CopyString);
    // RET;
    return MobileSDK_CopyString(de, hl, bc);
}

// GetPOSTString? // Useless?
const char* Function1126ac(void){
    // LD_HL(mUnknown_112137);
    // RET;
    return Unknown_112137;
}

// MobileSDK_CopyHTTPVersionString
char* Function1126b0(char* de, uint16_t* bc){
    // LD_HL(mUnknown_112115);
    // JP(mMobileSDK_CopyString);
    return MobileSDK_CopyString(de, Unknown_112115, bc);
}

#if defined(_CRYSTAL_JP)
const char CrystalManufactureCode[] = { 'B', 'X', 'T', 'J' };
#else
const char CrystalManufactureCode[] = { 'B', 'X', 'T', 'E' };
#endif
static_assert(sizeof(CrystalManufactureCode) == 0x4, "");
const uint8_t CrystalVersion = 0x00;

// MobileSDK_CopyUserAgentString
char* Function1126b6(char* de, uint16_t* bc){
    // LD_HL(mUnknown_112121);
    // CALL(aMobileSDK_CopyString);
    de = MobileSDK_CopyString(de, Unknown_112121, bc);
    // LD_HL(0x013f);
    // LD_B(0x4);
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(de, CrystalManufactureCode, sizeof(CrystalManufactureCode));
    // LD_A(0x2d);
    // LD_de_A;
    // INC_DE;
    *(de++) = '-';
    // LD_A_addr(0x014c);
    // AND_A(0xf0);
    // SWAP_A;
    // OR_A(0x30);
    // LD_de_A;
    // INC_DE;
    *(de++) = (CrystalVersion >> 4) + '0';
    // LD_A_addr(0x014c);
    // AND_A(0xf);
    // OR_A(0x30);
    // LD_de_A;
    // INC_DE;
    *(de++) = (CrystalVersion & 0xf) + '0';
    // LD_A(0x7);
    // ADD_A_C;
    // LD_C_A;
    *bc += 0x7;
    // LD_HL(mUnknown_112132);
    // JP(mMobileSDK_CopyString);
    return MobileSDK_CopyString(de, Unknown_112132, bc);
}

// MobileSDK_CopyPOSTHeaderContentLength?
char* Function1126e6(char* de, uint16_t* bc){
    // XOR_A_A;
    // LD_addr_A(wc86b);
    wram->wc86b = 0x0;
    // LD_HL(mUnknown_11213d);
    // CALL(aMobileSDK_CopyString);
    de = MobileSDK_CopyString(de, Unknown_11213d, bc);
    // LD_HL(wc9a5);
    uint8_t* hl = wram->wc9a5;
    // LD_B(0x5);
    uint8_t b = sizeof(wram->wc9a5);

    do {
    // asm_1126f5:
        // LD_A_hl;
        // CP_A(0x30);
        // IF_NZ goto asm_112701;
        if(*hl != '0')
            break;
        // INC_HL;
        hl++;
        // DEC_B;
        // LD_A(0x1);
        // CP_A_B;
        // IF_NZ goto asm_1126f5;
    } while(--b != 0x1);

// asm_112701:
    // PUSH_BC;
    uint8_t c = (*bc & 0xff);
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(de, hl, b);
    // LD_A(0xd);
    // LD_de_A;
    *(de++) = '\r';
    // INC_DE;
    // LD_A(0xa);
    // LD_de_A;
    *(de++) = '\n';
    // INC_DE;
    // POP_BC;
    // LD_A_B;
    // ADD_A(0x2);
    // ADD_A_C;
    // LD_C_A;
    c = c + b + 0x2;
    // OR_A_C;
    *bc = (*bc & 0xff00) | c;
    // RET;
    return de;
}

void Function112715(uint8_t* hl, uint8_t a){
    (void)hl, (void)a;
    // XOR_A_A;
    // LD_addr_A(wc86c);
    wram->wc86c = 0x0;
    // LD_A(0x2);
    // LD_addr_A(wc86a);
    wram->wc86a = 0x2;
    // LD_HL(wc821);
    // RES_hl(0);
    bit_reset(wram->wc821, 0);
    // RET;
}

void Function112724(void){
    // LD_A(0xff);
    // LD_addr_A(wc86e);
    wram->wc86e = 0xff;

    return Function112729();
}

void Function112729(void){
    // PUSH_HL;
    // LD_HL(wc82c);
    // XOR_A_A;
    // LD_hld_A;
    wram->wc82c = 0x0;
    // LD_A(0xff);
    // LD_hld_A;
    wram->wc82b = 0xff;
    // LD_A(0xc8);
    // LD_hld_A;
    // LD_A(0x80);
    // LD_hl_A;
    gMobileReceiveBuffer_Destination = &wram->wc880;
    // POP_HL;
    // RET;
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

// MobileSDK_Transfer11Bytes
void Function1127c5(const uint8_t *bytes){
    // LD_DE(0x000b);
    // LD_A(0x95);
    // JP(mFunction111f02);
    Function111f02(bytes, 0x000b, MOBILE_COMMAND_TRANSFER_DATA | 0x80);
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

bool Function1127e1(void){
    // CALL(aFunction112807);
    Function112807();
    // LD_HL(wc832);

    return Function1127e7((char*)&wram->wc832);
}

bool Function1127e7(char* hl){
    // LD_A_hli;
    // CP_A(0xd);
    // RET_NZ ;
    if(hl[0] != '\r')
        return false;
    // LD_A_hl;
    // CP_A(0xa);
    // RET_NZ ;
    if(hl[1] != '\n')
        return false;
    // LD_A(0x20);
    // LD_hl_A;
    hl[1] = ' ';
    // RET;
    return true;
}

bool Function1127f3(void){
    // CALL(aFunction112807);
    Function112807();
    // LD_HL(wc82f);
    char* hl = (char*)wram->wc82f;
    // LD_A_hli;
    // CP_A(0xd);
    // RET_NZ ;
    if(hl[0] != '\r')
        return false;
    // LD_A_hli;
    // CP_A(0xa);
    // RET_NZ ;
    if(hl[1] != '\n')
        return false;
    // LD_A_hli;
    // CP_A(0x2e);
    // RET_NZ ;
    if(hl[2] != '.')
        return false;
    // JR(mFunction1127e7);
    return Function1127e7(hl + 3);
}

void Function112807(void){
    // PUSH_BC;
    // PUSH_DE;
    // LD_HL(wMobileSDK_ReceivePacketBuffer + 3);
    // LD_A_hl;
    uint8_t a = wram->wMobileSDK_ReceivePacketBuffer[3] - 1;
    // DEC_A;
    // IF_Z goto asm_11282d;
    if(a == 0)
        return;
    // LD_C_A;
    // CP_A(0x5);
    // IF_NC goto asm_112830;
    if(a >= 0x5) {
    // asm_112830:
        // SUB_A(0x5);
        // LD_C_A;
        // LD_B(0);
        // LD_HL(wMobileSDK_ReceivePacketBuffer + 5);
        // ADD_HL_BC;
        // LD_B(0x5);
        // LD_DE(wc82f);
        // goto asm_11282a;
        MobileSDK_CopyBytes(wram->wc82f, wram->wMobileSDK_ReceivePacketBuffer + 5 + (a - 0x5), 0x5);
        return;
    }
    // LD_A(0x5);
    // SUB_A_C;
    // LD_B_A;
    // LD_E_C;
    // LD_D(0x0);
    // LD_HL(wc82f);
    // ADD_HL_DE;
    // LD_DE(wc82f);
    // CALL(aMobileSDK_CopyBytes);
    uint8_t* de = MobileSDK_CopyBytes(wram->wc82f, wram->wc82f + a, 0x5 - a);
    // LD_HL(wMobileSDK_ReceivePacketBuffer + 5);
    // LD_B_C;

// asm_11282a:
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(de, wram->wMobileSDK_ReceivePacketBuffer + 5, a);

// asm_11282d:
    // POP_DE;
    // POP_BC;
    // RET;
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
    // LD_HL(wc821);
    // RES_hl(0);
    // RES_hl(2);
    wram->wc821 &= ~((1 << 2) | (1 << 0));
    // RET;
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
    // LD_DE(0x0002);
    // LD_A_addr(wMobileSDK_PacketBuffer + 32);
    // CP_A(0x1);
    // IF_Z goto asm_112a2c;
    // INC_DE;

// asm_112a2c:

    return Function112a2c((wram->wMobileSDK_PacketBuffer[32] == 0x1)? 0x0002: 0x0003);
}

void Function112a2c(uint16_t de){
    // LD_HL(wc821);
    // SET_hl(1);
    bit_set(wram->wc821, 1);
    // RES_hl(0);
    bit_reset(wram->wc821, 0);
    // LD_HL(wc80f);
    // LD_A(0x31);
    // LD_hli_A;
    wram->wc80f = 0x31;
    // LD_A_E;
    // LD_hli_A;
    wram->wc810 = LOW(de);
    // LD_hl_D;
    wram->wc811 = HIGH(de);
    // LD_A(0x5);
    // LD_addr_A(wc86a);
    wram->wc86a = 0x5;
    // RET;
}

void Function112a42(void){
    // LD_HL(wc810);
    // XOR_A_A;
    // LD_hli_A;
    wram->wc810 = 0x0;
    // LD_hl_A;
    wram->wc811 = 0x0;
    // XOR_A_A;
    // LD_addr_A(wc86d);
    wram->wc86d = 0x0;
    // LD_A(0x31);
    // CALL(aFunction11225d);
    uint8_t* hl = Function11225d(0x31);
    // SET_hl(1);
    bit_set(*hl, 1);
    // RES_hl(0);
    bit_reset(*hl, 0);
    // RET;
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

// MobileSDK_ParseNumber
uint16_t Function112b11(const char* hl){
    // LD_A_addr(wc872);
    // PUSH_AF;
    uint8_t c872 = wram->wc872;
    // LD_A_addr(wc873);
    // PUSH_AF;
    uint8_t c873 = wram->wc873;
    // LD_A_addr(wc874);
    // PUSH_AF;
    uint8_t c874 = wram->wc874;
    // LD_BC(0x0300);
    uint8_t b = 0x03;
    // LD_DE(wc872);
    char* de = wram->wc872_digit_buffer;
    // CALL(aFunction112b60);
    u8_flag_s res = Function112b60(&de, &hl, &b);
    // CALL_NC (aFunction112b60);
    if(!res.flag) res = Function112b60(&de, &hl, &b);
    // CALL_NC (aFunction112b60);
    if(!res.flag) res = Function112b60(&de, &hl, &b);
    // DEC_HL;
    --hl;
    char a;

    do {
    // asm_112b2d:
        // LD_A_hli;
        a = *(hl++);
        // CP_A(0xd);
        // IF_Z goto asm_112b36;
        // CP_A(0x20);
        // IF_NZ goto asm_112b2d;
    } while(a != '\r' && a != ' ');

// asm_112b36:
    // PUSH_HL;
    // LD_HL(wc872);
    hl = wram->wc872_digit_buffer;
    // LD_DE(0);
    union Register de2 = {.reg = 0x0};
    // LD_A_B;
    // OR_A_A;
    // IF_Z goto asm_112b49;
    // DEC_A;
    // IF_Z goto asm_112b4b;
    // DEC_A;
    // IF_Z goto asm_112b4f;
    // goto asm_112b52;
    switch(b) {
    case 0:
    // asm_112b49:
        // LD_A_hli;
        // LD_D_A;
        de2.hi = *(hl++);
        fallthrough;

    case 1:
    // asm_112b4b:
        // LD_A_hli;
        a = *(hl++);
        // SWAP_A;
        // LD_E_A;
        de2.lo = (a << 4) | (a >> 4);
        fallthrough;

    case 2:
    // asm_112b4f:
        // LD_A_hli;
        // OR_A_E;
        // LD_E_A;
        de2.lo |= *(hl++);
        fallthrough;

    default:
    // asm_112b52:
        // POP_HL;
        // POP_AF;
        // LD_addr_A(wc874);
        wram->wc874 = c874;
        // POP_AF;
        // LD_addr_A(wc873);
        wram->wc873 = c873;
        // POP_AF;
        // LD_addr_A(wc872);
        wram->wc872 = c872;
        // RET;
        return de2.reg;
    }
}

// TryParseDigit?
u8_flag_s Function112b60(char** de, const char** hl, uint8_t* b){
    // LD_A_hli;
    uint8_t a = (uint8_t)*((*hl)++);
    // CP_A(0x30);
    // IF_C goto asm_112b6f;
    // CP_A(0x3a);
    // IF_NC goto asm_112b6f;
    if(a >= '0' || a <= '9') {
        // AND_A(0xf);
        // LD_de_A;
        **de = a & 0xf;
        // INC_DE;
        (*de)++;
        // DEC_B;
        (*b)--;
        // RET;
        return u8_flag(*b, *b == 0xff);
    }
    return u8_flag(0, true);

// asm_112b6f:
    // SCF;
    // RET;
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

void Function112bbb(uint8_t* hl, uint8_t a){
    (void)hl;
    // DEC_A;
    // IF_Z goto asm_112bbf;
    if(a == 0x1) {
    // asm_112bbf:
        // CALL(aFunction1127e1);
        // IF_NZ goto asm_112bd4;
        if(Function1127e1()) {
            // LD_HL(wc880);
            // LD_A_hli;
            // CP_A(0x2b);
            // IF_NZ goto asm_112be6;
            if(wram->wc880_str[0] != 0x2b) {
            // asm_112be6:
                // LD_DE(0x0004);
                // JP(mFunction112a2c);
                return Function112a2c(0x0004);
            }
            // LD_A(0x4);
            // LD_addr_A(wc86a);
            wram->wc86a = 0x4;
            // JP(mFunction1128d3);
            Function1128d3();
            return;
        }

    // asm_112bd4:
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
        // CP_A(0x9f);
        // JP_Z (mFunction112a42);
        if(wram->wMobileSDK_ReceivePacketBuffer[0x0] == 0x9f)
            return Function112a42();
        // LD_HL(wc86b);
        // DEC_hl;
        wram->wc86b--;
        // LD_HL(wMobileSDK_PacketBuffer + 128);
        // JP(mFunction1127c5);
        return Function1127c5(wram->wMobileSDK_PacketBuffer + 128);
    }
    // RET;
}

void Function112bec(uint8_t* hl, uint8_t a){
    // DEC_A;
    // IF_Z goto asm_112bf7;
    if(a == 0x1) {
    // asm_112bf7:
        // LD_A_addr(wc880);
        // CP_A(0x2d);
        // IF_NZ goto asm_112c03;
        if(wram->wc880_str[0] == '-') {
            // CALL(aFunction1127e1);
            // IF_Z goto asm_112c0b;
            if(Function1127e1())
                goto asm_112c0b;
        }

    // asm_112c03:
        // LD_A_addr(wc821);
        // BIT_A(2);
        // JP_Z (mFunction112bec_asm_112cef);
        if(!bit_test(wram->wc821, 2))
            goto asm_112cef;

    asm_112c0b:
        // LD_HL(wc86b);
        // INC_hl;
        wram->wc86b++;
        // LD_HL(wc880);
        // LD_A_hli;
        // CP_A(0x2b);
        // JP_NZ (mFunction112d20);
        if(wram->wc880_str[0] == '+')
            return Function112d20();
        // LD_B(0x7f);
        uint8_t b = 0x7f;
        char* str = wram->wc880_str + 1;
        char a;

        do {
        // asm_112c1a:
            // LD_A_hli;
            a = *(str++);
            // DEC_B;
            --b;
            // CP_A(0xa);
            // IF_NZ goto asm_112c1a;
        } while(a != '\n');
        // PUSH_HL;
        // LD_HL(wc98f);
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint8_t* de = gMobile_wc98f;
        // LD_A_B;
        // LD_addr_A(wc82d);
        wram->wc82d = b;
        // LD_A_hli;
        // LD_H_hl;
        uint16_t hl2 = wram->wc991 | (wram->wc992 << 8);
        // SUB_A_B;
        // LD_L_A;
        // LD_A_H;
        // SBC_A(0x0);
        // LD_H_A;
        // IF_NC goto asm_112c56;
        // CP_A(0xff);
        // IF_NZ goto asm_112c56;
        if(hl2 < b) {
            // LD_HL(wc991);
            // LD_A_hli;
            // LD_C_A;
            uint8_t c = wram->wc991;
            // INC_HL;
            // LD_A_B;
            // SUB_A_C;
            // LD_hli_A;
            wram->wc991 = (b - c);
            wram->wc992 = 0xff;
            // LD_A_addr(wc82b);
            // LD_hl_A;
            wram->wc993 = wram->wc82b;
            // LD_HL(wc827);
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // LD_A_C;
            // LD_hli_A;
            gMobile_wc827[0] = c;
            // XOR_A_A;
            // LD_hl_A;
            gMobile_wc827[1] = 0x0;
            // POP_HL;
            // LD_B_C;
            // JP(mMobileSDK_CopyBytes);
            MobileSDK_CopyBytes(de, str, c);
            return;
        }

    // asm_112c56:
        // LD_addr_A(wc993);
        wram->wc993 = HIGH((hl2 - b));
        // LD_A_addr(wc82b);
        // LD_C_A;
        uint8_t c = wram->wc82b;
        // LD_addr_A(wc994);
        wram->wc994 = c;
        hl2 -= b;
        // PUSH_HL;
        // LD_A_L;
        // SUB_A_C;
        // LD_L_A;
        // LD_A_H;
        // SBC_A(0x0);
        // LD_H_A;
        // IF_NC goto asm_112c9f;
        // CP_A(0xff);
        // IF_NZ goto asm_112c9f;
        if(hl2 < c) {
            // LD_A_C;
            // LD_addr_A(wMobileSDK_ReceivePacketBuffer + 1);
            wram->wMobileSDK_ReceivePacketBuffer[1] = c;
            // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
            // SUB_A_C;
            uint8_t sub = wram->wMobileSDK_ReceivePacketBuffer[3] - c;
            // POP_HL;
            // LD_C_L;
            c = LOW(hl2);
            // POP_HL;
            // PUSH_AF;
            // CALL(aMobileSDK_CopyBytes);
            de = MobileSDK_CopyBytes(de, hl, b);
            // POP_AF;
            // PUSH_DE;
            // LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
            // LD_E_A;
            // LD_D(0);
            // ADD_HL_DE;
            // POP_DE;
            // LD_B_C;
            // CALL(aMobileSDK_CopyBytes);
            de = MobileSDK_CopyBytes(de, wram->wMobileSDK_ReceivePacketBuffer + 4 + sub, c);
            // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 1);
            // SUB_A_C;
            // LD_addr_A(wc994);
            wram->wc994 = wram->wMobileSDK_ReceivePacketBuffer[1] - c;
            // LD_HL(wc827);
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // LD_A_addr(wc991);
            // LD_hli_A;
            gMobile_wc827[0] = wram->wc991;
            // XOR_A_A;
            // LD_hl_A;
            gMobile_wc827[1] = 0x0;
            // RET;
            return;
        }

    // asm_112c9f:
        // LD_addr_A(wc994);
        wram->wc994 = HIGH((hl2 - c));
        hl2 -= c;
        // LD_A_L;
        // LD_addr_A(wc82b);
        wram->wc82b = LOW(hl2);
        // LD_A_H;
        // LD_addr_A(wc82c);
        wram->wc82c = HIGH(hl2);
        // POP_HL;
        // POP_HL;
        // CALL(aMobileSDK_CopyBytes);
        de = MobileSDK_CopyBytes(de, hl, b);
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
        // SUB_A_C;
        uint8_t sub = wram->wMobileSDK_ReceivePacketBuffer[3] - c;
        // PUSH_DE;
        // LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // POP_DE;
        // LD_B_C;
        // CALL(aMobileSDK_CopyBytes);
        de = MobileSDK_CopyBytes(de, wram->wMobileSDK_ReceivePacketBuffer + 4 + sub, c);
        uint16_t de3 = wram->wc82d | (wram->wc82e << 8);
        // LD_A_addr(wc82d);
        // ADD_A_C;
        de3 += c;
        // LD_addr_A(wc82d);
        wram->wc82d = LOW(de3);
        // LD_A_addr(wc82e);
        // ADC_A(0);
        // LD_addr_A(wc82e);
        wram->wc82e = HIGH(de3);
        // LD_HL(wc829);
        // LD_A_E;
        // LD_hli_A;
        // LD_A_D;
        // LD_hl_A;
        gMobileReceiveBuffer_Destination = de;
        // LD_HL(wc821);
        // RES_hl(2);
        bit_reset(wram->wc821, 2);
        goto asm_112cdb;
    }
    // DEC_A;
    // JP_Z (mFunction112bec_asm_112cdb);
    else if(a == 0x2) {
    asm_112cdb:
        // LD_A_addr(wc821);
        // BIT_A(2);
        // IF_Z goto asm_112cea;
        if(bit_test(wram->wc821, 2)) {
            // LD_A(0x2);
            // LD_addr_A(wc86b);
            wram->wc86b = 0x2;
            // JP(mFunction112bec_asm_112d09);
        }
        else {
        // asm_112cea:
            // CALL(aFunction1127f3);
            // IF_Z goto asm_112d01;
            if(!Function1127f3()) {
            asm_112cef:
                // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
                // CP_A(0x9f);
                // JP_Z (mFunction112a42);
                if(wram->wMobileSDK_ReceivePacketBuffer[0] == 0x9f)
                    return Function112a42();
                // LD_HL(wc86b);
                // DEC_hl;
                wram->wc86b--;
                // LD_HL(wMobileSDK_PacketBuffer + 128);
                // JP(mFunction1127c5);
                return Function1127c5(wram->wMobileSDK_PacketBuffer + 128);
            }
            else {
            // asm_112d01:
                // LD_A(0x4);
                // LD_addr_A(wc86a);
                wram->wc86a = 0x4;
                // CALL(aFunction1128d3);
                return Function1128d3();
            }
        }

    // asm_112d09:
        // LD_A_addr(wc86e);
        // LD_L_A;
        // LD_A_addr(wc86f);
        // OR_A_L;
        // RET_Z ;
        if(gMobile_wc86e_wc86f == NULL && (wram->wc86e | wram->wc86f) == 0)
            return;
        // LD_HL(wc827);
        // LD_A_hli;
        // LD_E_A;
        // LD_D_hl;
        // LD_HL(wc82d);
        // LD_B(0x2);
        // JP(mMobileSDK_CopyBytes);
        MobileSDK_CopyBytes(gMobile_wc827, &wram->wc82d, 0x2);
        return;
    }
    // DEC_A;
    // RET_NZ ;
    else if(a == 0x3) {
        // DEC_hl;
        (*hl)--;
        // RET;
        return;
    }
}

void Function112d20(void){
    // LD_A_addr(wc86a);
    // CP_A(0x1a);
    // IF_NZ goto asm_112d2d;
    if(wram->wc86a == 0x1a) { // Useless 
        // LD_DE(0x0004);
        // JP(mFunction112a2c);
        return Function112a2c(0x0004);
    }
    else {
    // asm_112d2d:
        // LD_DE(0x0004);
        // JP(mFunction112a2c);
        return Function112a2c(0x0004);
    }
}

void Function112d33(uint8_t* hl, uint8_t a){
    // DEC_A;
    // IF_Z goto asm_112d87;
    if(a == 0x1) {
    // asm_112d87:
        // CALL(aFunction113482);
        if(Function113482())
            return;
        // LD_DE(wMobileSDK_PacketBuffer);
        // LD_HL(mMobilePacket_TransferData);
        // LD_B(0x6);
        // CALL(aMobileSDK_CopyBytes);
        uint8_t* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_TransferData, 0x6);
        // LD_A_addr(wc86c);
        // LD_de_A;
        *de = wram->wc86c;
        // INC_DE;
        // LD_B(0x1);
        // CALL(aFunction111f63);
        Function111f63(de + 1, 0x1);
        goto asm_112d9f;
    }
    // DEC_A;
    // IF_Z goto asm_112d9f;
    if(a == 0x2) {
    asm_112d9f:
        // LD_A_addr(wc821);
        // BIT_A(2);
        // IF_Z goto asm_112dab;
        if(!bit_test(wram->wc821, 2)) {
        // asm_112dab:
            // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
            // CP_A(MOBILE_COMMAND_TRANSFER_DATA_END | 0x80);
            // IF_Z goto asm_112dc1;
            if(wram->wMobileSDK_ReceivePacketBuffer[0] != (MOBILE_COMMAND_TRANSFER_DATA_END | 0x80)) {
                // LD_HL(wc86b);
                // DEC_hl;
                wram->wc86b--;
                // LD_DE(0x000b);
                // LD_HL(wMobileSDK_PacketBuffer);
                // LD_B(0x5);
                // JP(mPacketSendBytes);
                PacketSendBytes(wram->wMobileSDK_PacketBuffer, 0x000b, 0x5);
                return;
            }
        }
        else {
            // LD_A(0x3);
            // LD_hl_A;
            *hl = 0x3;
            // goto asm_112dc1;
        }

    // asm_112dc1:
        // LD_A_addr(wc989);
        // CP_A(0x2);
        // IF_NC goto asm_112df2;
        if(wram->wc989 >= 0x2)
            goto asm_112df2;
        // CALL(aFunction112f61);
        a = Function112f61();
        // BIT_A(2);
        // RET_NZ ;
        if(bit_test(a, 2))
            return;
        // CP_A(0x3);
        // IF_Z goto asm_112e38;
        if(a == 0x3) {
        // asm_112e38:
            // LD_HL(wc821);
            // SET_hl(1);
            bit_set(wram->wc821, 1);
            // RES_hl(0);
            bit_reset(wram->wc821, 0);
            // LD_DE(wc98b);
            uint8_t* de = &wram->wc98b;
            // LD_A(0x24);
            a = 0x24;
            goto asm_112e95;


        asm_112e46:
            // LD_A_addr(wc86a);
            // CP_A(0x1f);
            // IF_Z goto asm_112ea6;
            // CP_A(0x20);
            // IF_Z goto asm_112ea6;
            if(wram->wc86a != 0x1f && wram->wc86a != 0x20) {
                // LD_A_addr(wc98a);
                // CP_A(0x1);
                // IF_Z goto asm_112e65;
                if(wram->wc98a != 0x1) {
                    // LD_A_addr(wc86a);
                    // CP_A(0x21);
                    // JP_Z (mFunction112d33_asm_112eea);
                    // CP_A(0x22);
                    // JP_Z (mFunction112d33_asm_112eea);
                    if(wram->wc86a == 0x21 || wram->wc86a == 0x22)
                        goto asm_112eea;
                }

            // asm_112e65:
                // LD_A_addr(wc990);
                // OR_A_A;
                // JP_Z (mFunction112d33_asm_112f3d);
                if(wram->wc990 == 0x0)
                    goto asm_112f3d;

            asm_112e6c:
                // LD_HL(wc98c);
                // LD_A_hld;
                // CP_A(0x3);
                // IF_NZ goto asm_112e7f;
                // LD_A_hl;
                // OR_A_A;
                // IF_Z goto asm_112e7f;
                // CP_A(0x3);
                // IF_NC goto asm_112e7f;
                if(wram->wc98c == 0x3 && wram->wc98b != 0 && wram->wc98b < 0x3) {
                    // CALL(aFunction1133fe);
                    Function1133fe();
                }

            asm_112e7f:
                // LD_HL(wc821);
                // SET_hl(1);
                bit_set(wram->wc821, 1);
                // RES_hl(0);
                bit_reset(wram->wc821, 0);
                // LD_DE(wc98b);
                // LD_A_addr(wc990);
                // CP_A(0x1);
                // LD_A(0x32);
                // IF_Z goto asm_112e95;
                // INC_DE;
                // INC_DE;
                de = (wram->wc990 == 0x1)? &wram->wc98b: &wram->wc98b + 2;
                // INC_A;
                a = (wram->wc990 == 0x1)? 0x32: 0x33;

            asm_112e95:
                // LD_addr_A(wc80f);
                wram->wc80f = a;
                // LD_HL(wc810);
                // LD_A_de;
                // INC_DE;
                // LD_hli_A;
                wram->wc810 = *(de++);
                // LD_A_de;
                // LD_hl_A;
                wram->wc811 = *(de++);
                // LD_A(0x5);
                // LD_addr_A(wc86a);
                wram->wc86a = 0x5;
                // RET;
                return;
            }

        asm_112ea6:
            // LD_HL(wc98b);
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // CP_A(0x0);
            // IF_NZ goto asm_112ec1;
            // LD_A(0x2);
            // CP_A_H;
            // IF_NZ goto asm_112ec1;
            if(wram->wc98b == 0x0 && wram->wc98c == 0x2) {
                // LD_A_addr(wc98d);
                // LD_B_A;
                // LD_A_addr(wc98e);
                // OR_A_B;
                // IF_NZ goto asm_112e6c;
                if((wram->wc98e | wram->wc98d) != 0)
                    goto asm_112e6c;
                goto asm_112f3d;
            }

        // asm_112ec1:
            // LD_A(0x1);
            // CP_A_L;
            // IF_NZ goto asm_112e6c;
            // LD_A(0x4);
            // CP_A_H;
            // IF_NZ goto asm_112e6c;
            if(wram->wc98b != 0x1 || wram->wc98c != 0x4)
                goto asm_112e6c;
            // LD_A_addr(wc9a5);
            // OR_A_A;
            // IF_NZ goto asm_112efb;
            // LD_A_addr(wc86e);
            // LD_L_A;
            // LD_A_addr(wc86f);
            // OR_A_L;
            // IF_NZ goto asm_112efb;
            if(wram->wc9a5[0] != 0x0 || (gMobile_wc86e_wc86f != NULL || (wram->wc86e | wram->wc86f) != 0))
                goto asm_112efb;
            // LD_A(0x2);
            // LD_addr_A(wc86a);
            wram->wc86a = 0x2;
            // XOR_A_A;
            // LD_addr_A(wc86d);
            wram->wc86d = 0x0;
            // LD_HL(wc821);
            // RES_hl(0);
            bit_reset(wram->wc821, 0);
            // RET;
            return;

        asm_112eea:
            // LD_HL(wc98b);
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // CP_A(0x0);
            // JP_NZ (mFunction112d33_asm_112e6c);
            // LD_A(0x2);
            // CP_A_H;
            // JP_NZ (mFunction112d33_asm_112e6c);
            if(wram->wc98b != 0x0 || wram->wc98c != 0x2)
                goto asm_112e6c;

        asm_112efb:
            // LD_A_addr(wc98d);
            // LD_B_A;
            // LD_A_addr(wc98e);
            // CP_A_B;
            // JP_NZ (mFunction112d33_asm_112e6c);
            if(wram->wc98d != wram->wc98e)
                goto asm_112e6c;
            // OR_A_A;
            // IF_Z goto asm_112f13;
            if(wram->wc98e != 0) {
                // CP_A(0x1);
                // JP_NZ (mFunction112d33_asm_112e6c);
                if(wram->wc98e != 0x1)
                    goto asm_112e6c;
                // LD_A(0x1);
                // LD_addr_A(wc993);
                wram->wc993 = 0x1;
            }

        // asm_112f13:
            // LD_A_addr(wc86b);
            // CP_A(0x7);
            // IF_Z goto asm_112f3d;
            if(wram->wc86b != 0x7) {
                // LD_HL(wc98f);
                // INC_hl;
                wram->wc98f++;
                // LD_A(0xf);
                // LD_addr_A(wc86a);
                wram->wc86a = 0xf;
                // LD_A(0x1);
                // LD_addr_A(wc86b);
                wram->wc86b = 0x1;
                // LD_A_addr(wc86d);
                // LD_addr_A(wc86e);
                wram->wc86e = wram->wc86d;
                // XOR_A_A;
                // LD_addr_A(wc989);
                wram->wc989 = 0x0;
                // LD_A(0xa3);
                // LD_DE(0x0010);
                // LD_HL(wc995);
                // JP(mFunction111f02);
                Function111f02(wram->wc995, sizeof(wram->wc995), 0xa3);
                return;
            }

        asm_112f3d:
            // LD_A_addr(wc993);
            // CP_A(0x1);
            // IF_NZ goto asm_112f52;
            if(wram->wc993 != 0x1) {
            // asm_112f52:
                // LD_A(0x2);
                // LD_addr_A(wc86a);
                wram->wc86a = 0x2;
                // XOR_A_A;
                // LD_addr_A(wc86d);
                wram->wc86d = 0x0;
                // LD_HL(wc821);
                // RES_hl(0);
                bit_reset(wram->wc821, 0);
                // RET;
                return;
            }
            // LD_A(0x2);
            // LD_addr_A(wc990);
            wram->wc990 = 0x2;
            // LD_HL(wc98d);
            // DEC_A;
            // LD_hli_A;
            wram->wc98d = 0x1;
            // LD_hl_A;
            wram->wc98c = 0x1;
            // JP(mFunction112d33_asm_112e7f);
            goto asm_112e7f;
        }
        // CP_A(0x1);
        // IF_NZ goto asm_112df2;
        if(a != 0x1)
            goto asm_112df2;
        // LD_A_addr(wc86a);
        // CP_A(0x1f);
        // IF_Z goto asm_112de1;
        // CP_A(0x20);
        // IF_NZ goto asm_112df2;
        if(wram->wc86a == 0x1f || wram->wc86a == 0x20) {
        // asm_112de1:
            // LD_HL(wc98b);
            // LD_A_hli;
            // CP_A(0x1);
            // IF_NZ goto asm_112df2;
            // LD_A(0x4);
            // CP_A_hl;
            // IF_NZ goto asm_112df2;
            if(wram->wc98b == 0x1 && wram->wc98c == 0x4) {
                // XOR_A_A;
                // LD_addr_A(wc990);
                wram->wc990 = 0x0;
            }
        }

    asm_112df2:
        // LD_A_addr(wc86e);
        // LD_L_A;
        // LD_A_addr(wc86f);
        // OR_A_L;
        // RET_Z ;
        if(gMobile_wc86e_wc86f == NULL && (wram->wc86e | wram->wc86f) == 0)
            return;
        // LD_A_addr(wc86a);
        a = wram->wc86a;
        // CP_A(0x13);
        // IF_Z goto asm_112e21;
        // CP_A(0x14);
        // IF_Z goto asm_112e21;
        if(a != 0x13 && a != 0x14) {
            // CP_A(0x20);
            // RET_Z ;
            // CP_A(0x22);
            // RET_Z ;
            // CP_A(0x23);
            // RET_Z ;
            if(a == 0x20 || a == 0x22 || a == 0x23)
                return;
            // CP_A(0x1f);
            // IF_NZ goto asm_112e21;
            if(a == 0x1f) {
                // LD_HL(wc98b);
                // LD_A_hli;
                // CP_A(0x0);
                // RET_NZ ;
                // LD_A(0x2);
                // CP_A_hl;
                // RET_NZ ;
                if(wram->wc98b != 0x0 || wram->wc98c != 0x2)
                    return;
                // LD_A_addr(wc86a);
                a = wram->wc86a;
            }
        }

    // asm_112e21:
        // CP_A(0x24);
        // IF_NZ goto asm_112e2a;
        // LD_HL(wc878);
        // goto asm_112e2d;

    // asm_112e2a:
        // LD_HL(wc827);

    // asm_112e2d:
        // LD_A_hli;
        // LD_E_A;
        // LD_D_hl;
        uint8_t* de = (a == 0x24)? gMobile_wc878: gMobile_wc827;
        // LD_HL(wc82d);
        // LD_B(0x2);
        // JP(mMobileSDK_CopyBytes);
        MobileSDK_CopyBytes(de, &wram->wc82d, 0x2);
        return;
    }
    // DEC_A;
    // JP_Z (mFunction112d33_asm_112e46);
    // DEC_A;
    // IF_Z goto asm_112d4d;
    if(a == 0x4) {
    // asm_112d4d:
        // LD_A_addr(wc86a);
        // CP_A(0x23);
        // IF_Z goto asm_112d6d;
        // CP_A(0x1f);
        // IF_Z goto asm_112d60;
        // CP_A(0x20);
        // IF_Z goto asm_112d6d;
        // CP_A(0x22);
        // IF_NZ goto asm_112d82;
        if(wram->wc86a == 0x23 || wram->wc86a == 0x1f || wram->wc86a == 0x20 || wram->wc86a == 0x22) {
            if(wram->wc86a == 0x1f || wram->wc86a == 0x22) {
            // asm_112d60:
                // LD_HL(wc98b);
                // LD_A_hli;
                // CP_A(0x1);
                // IF_NZ goto asm_112d82;
                // LD_A_hl;
                // CP_A(0x4);
                // IF_NZ goto asm_112d82;
                if(wram->wc98b == 0x1 && wram->wc98c == 0x4)
                    goto asm_112d6d;
            }
            else {
            asm_112d6d:
                // LD_HL(wc86e);
                // XOR_A_A;
                // LD_hli_A;
                // LD_hl_A;
                gMobile_wc86e_wc86f = NULL;
                wram->wc86e = 0;
                wram->wc86f = 0;
                // LD_HL(wc82b);
                // LD_hli_A;
                wram->wc82b = 0x0;
                // LD_hl_A;
                wram->wc82c = 0x0;
                // LD_HL(wc821);
                // RES_hl(2);
                bit_reset(wram->wc821, 2);
                // LD_HL(wc86b);
                // DEC_hl;
                // DEC_hl;
                wram->wc86b -= 2;
            }
        }

    // asm_112d82:
        // LD_HL(wc86b);
        // DEC_hl;
        wram->wc86b--;
        // RET;
        return;
    }
    // DEC_A;
    // JP_Z (mFunction113317);
    if(a == 0x5)
        return Function113317();
    // DEC_A;
    // JP_Z (mFunction113386);
    if(a == 0x6)
        return Function113386();
    // DEC_A;
    // JP(mFunction112d33_asm_112e46);
    goto asm_112e46;

// asm_112d4c:
//   //  unreferenced
    // RET;
}

// Mobile_ParseHTTPResponseHeader
uint8_t Function112f61(void){
    // LD_HL(wc989);
    // LD_A_hl;
    // OR_A_A;
    // IF_NZ goto asm_112f8a;
    if(wram->wc989 == 0) {
        // INC_hl;
        wram->wc989++;
        // LD_HL(wc880);
        // LD_DE(0x0008);
        // ADD_HL_DE;
        const char* hl = (const char*)wram->wc884 + 0x4; // Grab response code string.

        char a = 0;
        do {
        // asm_112f70:
            // LD_A_hli;
            a = *(hl++);
            // CP_A(0x20);
            // IF_Z goto asm_112f70;
        } while(a == ' ');
        // DEC_HL;
        hl--;
        // LD_D(0x0);
        // CP_A(0x32);
        // IF_Z goto asm_112f7d;
        // INC_D;

    // asm_112f7d:
        uint8_t d = (a == '2')? 0x0: 0x1; // Checks for 2XX response code.
        // LD_A_D;
        // LD_addr_A(wc990);
        wram->wc990 = d;
        // CALL(aFunction112b11);
        uint16_t de = Function112b11(hl);
        // LD_HL(wc98b);
        // LD_A_E;
        // LD_hli_A;
        wram->wc98b = LOW(de);
        // LD_hl_D;
        wram->wc98c = HIGH(de);
    }

// asm_112f8a:
    // LD_HL(wc880);
    char* hl = wram->wc880_str;
    // LD_A_addr(wc82d);
    // LD_B_A;
    uint8_t b = wram->wc82d;
    // OR_A_A;
    // IF_NZ goto asm_112fa1;
    if(b == 0) {
        // LD_HL(wc98b);
        // LD_A(0x0);
        // LD_hli_A;
        wram->wc98b = 0x0;
        // LD_hl_A;
        wram->wc98c = 0x0;
        // LD_A(0x1);
        // LD_addr_A(wc990);
        wram->wc990 = 0x1;
        // RET;
        return 0x1;
    }

    bool do_set = false;
    uint8_t* de = NULL;

// parse the response header
    do {
    // asm_112fa1:
        // CALL(aFunction112fd5);
        hl = Function112fd5(hl); // date
        // CALL(aFunction113008);
        hl = Function113008(hl); // Gb-Status
        // CALL(aFunction113026);
        hl = Function113026(hl); // Gb-Auth-ID
        // CALL(aFunction113054);
        hl = Function113054(hl); // WWW-Authenticate
        // CALL(aFunction113167);
        hl = Function113167(hl); // URI-header
        // CALL(aFunction113180);
        hl = Function113180(hl); // Location
        de = (uint8_t*)hl;
        // CALL(aFunction113268);
        u8_flag_s res = Function113268(&hl, &b); // consume line?
        // IF_C goto asm_112fc9;
        if(!res.flag) {
        // asm_112fc9:
            // LD_HL(wc990);
            // SET_hl(2);
            do_set = true;
            break;
        }
        // LD_A(0xd);
        // CP_A_hl;
        // IF_Z goto asm_112fc2;
        if(*hl == '\r')
            break;
        // LD_A(0xa);
        // CP_A_hl;
        // IF_NZ goto asm_112fa1;
    } while(*hl != '\n');

// asm_112fc2:
    // LD_HL(wc990);
    // RES_hl(2);
    // goto asm_112fce;
    if(do_set) {
        bit_set(wram->wc990, 2);
    } else {
        bit_reset(wram->wc990, 2);
    }

// asm_112fce:
    // CALL(aFunction11306b);
    Function11306b(de);
    // LD_A_addr(wc990);
    // RET;
    return wram->wc990;
}

// MobileSDK_ParseHTTPResponseHeaderDate
char* Function112fd5(char* hl){
    // LD_DE(mUnknown_113001);
    // PUSH_HL;
    char* hl2 = hl;
    // CALL(aFunction113281);
    // IF_NC goto asm_112fe0;
    // POP_HL;
    // RET;
    if(!Function113281(&hl2, Unknown_113001)) {
    // asm_112fe0:
        // POP_DE;
        hl = hl2;
        // PUSH_BC;
        // PUSH_DE;
        // PUSH_HL;
        // LD_B(0x0);
        uint8_t b = 0x0;
        char a;

        do {
        // asm_112fe6:
            // INC_B;
            b++;
            // LD_A_hli;
            a = *(hl2++);
            // CP_A(0xa);
            // IF_NZ goto asm_112fe6;
        } while(a != '\n');
        // POP_HL;
        // LD_C_B;
        // LD_A_addr(wc833);
        // LD_E_A;
        // LD_A_addr(wc834);
        // LD_D_A;
        // OR_A_E;
        // IF_Z goto asm_112ffe;
        if(gMobile_wc833_wc834 != NULL) {
            // CALL(aMobileSDK_CopyBytes);
            char* end = MobileSDK_CopyBytes(gMobile_wc833_wc834, hl, b);
            // XOR_A_A;
            // LD_de_A;
            *end = '\0';
        }

    // asm_112ffe:
        // POP_HL;
        // POP_BC;
        // RET;
    }
    return hl;
}

const char Unknown_113001[] = "date: "; // ['"date: "', '0'];

// MobileSDK_ParseGBStatusField
char* Function113008(char* hl){
    // LD_DE(mUnknown_1132a6);
    // PUSH_HL;
    char* hl2 = hl;
    // CALL(aFunction113273);
    // IF_NC goto asm_113013;
    // POP_HL;
    // RET;
    if(!Function113273(&hl2, Unknown_1132a6)) {
    // asm_113013:
        // CALL(aFunction112b11);
        uint16_t de = Function112b11(hl2);
        // LD_HL(wc98d);
        // LD_A_E;
        // LD_hli_A;
        wram->wc98d = LOW(de);
        // LD_hl_D;
        wram->wc98e = HIGH(de);
        // POP_HL;
        // LD_A_D;
        // OR_A_E;
        // RET_Z ;
        if(de == 0)
            return hl;
        // LD_A(0x2);
        // LD_addr_A(wc990);
        wram->wc990 = 0x2;
        // RET;
    }
    return hl;
}

// MobileSDK_ParseHTTPResponseHeaderGBAuth
char* Function113026(char* hl){
    // LD_DE(mUnknown_1132b2);
    // PUSH_HL;
    char* hl2 = hl;
    // CALL(aFunction113273);
    // IF_NC goto asm_113031;
    // POP_HL;
    // RET;
    if(!Function113273(&hl2, Unknown_1132b2)) {
    // asm_113031:
        // POP_HL;
        char* de = hl;
        hl2 = hl;
        // PUSH_BC;
        // PUSH_HL;
        // PUSH_HL;
        // LD_B(0x0);
        uint8_t b = 0x0;
        char a;

        do {
        // asm_113037:
            // INC_B;
            b++;
            // LD_A_hli;
            a = *(hl2++);
            // CP_A(0xa);
            // IF_NZ goto asm_113037;
        } while(a != '\n');
        // POP_HL;
        // LD_C_B;
        // LD_DE(wMobileSDK_PacketBuffer + 18);
        // CALL(aMobileSDK_CopyBytes);
        de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 18, hl, b);
        // LD_HL(wMobileSDK_PacketBuffer + 18);
        // LD_DE(wc9b5);
        // LD_B_C;
        // CALL(aMobileSDK_CopyBytes);
        de = MobileSDK_CopyBytes(&wram->wc9b5, wram->wMobileSDK_PacketBuffer + 18, b);
        // XOR_A_A;
        // LD_de_A;
        *de = 0;
        // POP_HL;
        // POP_BC;
        // RET;
    }
    return hl;
}

// MobileSDK_ParseHTTPResponseHeaderWWWAuth
char* Function113054(char* hl){
    // LD_DE(mUnknown_1132bf);
    // PUSH_HL;
    char* hl2 = hl;
    // CALL(aFunction113273);
    // IF_NC goto asm_11305f;
    // POP_HL;
    // RET;
    if(!Function113273(&hl2, Unknown_1132bf)) {
    // asm_11305f:
        // PUSH_BC;
        // LD_DE(wc9b5);
        // LD_B(0x30);
        // CALL(aFunction1136c1);
        Function1136c1(hl2, &wram->wc9b5, 0x30);
        printf("Challenge=%s\nResponse:%s\n", hl2, &wram->wc9b5);
        // POP_BC;
        // POP_HL;
        // RET;
    }
    return hl;
}

void Function11306b(uint8_t* de){
    // LD_HL(wc880);
    // LD_A_addr(wc82d);
    // LD_B_A;

    return Function113072(wram->wc880_str, de, wram->wc82d);
}

void Function113072(char* hl, uint8_t* de, uint8_t b){
    while(1) {
        // CALL(aFunction113268);
        u8_flag_s res = Function113268(&hl, &b);
        // JP_NC (mFunction113089);
        if(res.flag) { // Inlined
            // LD_A_hl;
            // CP_A(0xd);
            // IF_Z goto asm_113094;
            if(*hl != '\r') {
                // CP_A(0xa);
                // JR_Z (mFunction113095);
                if(*hl == '\n')
                    return Function113095(hl, de, res.a);
                // JR(mFunction113072);
                continue;
            }

        // asm_113094:
            // INC_HL;
            hl++;

            return Function113095(hl, de, res.a);
        }
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
        // CP_A(0x9f);
        // JP_NZ (mFunction1131a9);
        if(wram->wMobileSDK_ReceivePacketBuffer[0] != 0x9f)
            return Function1131a9();
        // PUSH_HL;
        // LD_HL(wc990);
        // RES_hl(2);
        bit_reset(wram->wc990, 2);
        // POP_HL;
        // JR(mFunction113095);
        return Function113095(hl, de, res.a);
    }
}

// void Function113089(char* hl){
//     // LD_A_hl;
//     // CP_A(0xd);
//     // IF_Z goto asm_113094;
//     if(*hl != '\r') {
//         // CP_A(0xa);
//         // JR_Z (mFunction113095);
//         if(*hl == '\n')
//             return Function113095(hl);
//         // JR(mFunction113072);
//         return Function113072(hl);
//     }

// // asm_113094:
//     // INC_HL;
//     hl++;

//     return Function113095(hl, bc);
// }

void Function113095(char* hl, uint8_t* de, uint8_t b){
    // INC_HL;
    hl++;
    // PUSH_BC;
    // LD_A_addr(wc872);
    // LD_B_A;
    // LD_A_addr(wc873);
    // OR_A_B;
    // POP_BC;
    // IF_Z goto asm_1130b3;
    // LD_A_addr(wc86a);
    // CP_A(0x23);
    // IF_Z goto asm_1130b3;
    // CP_A(0x20);
    // IF_Z goto asm_1130b3;
    // CP_A(0x22);
    // IF_Z goto asm_1130b3;
    // goto asm_1130d6;
    if((wram->wc872 | wram->wc873) == 0
    || wram->wc86a == 0x23
    || wram->wc86a == 0x20) {
    // asm_1130b3:
        // XOR_A_A;
        // LD_HL(wc86e);
        // LD_hli_A;
        // LD_hl_A;
        gMobile_wc86e_wc86f = NULL;
        wram->wc86e = 0;
        wram->wc86f = 0;
        // LD_HL(wc821);
        // RES_hl(2);
        bit_reset(wram->wc821, 2);
        // LD_A_addr(wc86a);
        // CP_A(0x13);
        // IF_Z goto asm_1130c8;
        // CP_A(0x14);
        // RET_NZ ;
        if(wram->wc86a != 0x13 && wram->wc86a != 0x14)
            return;

    // asm_1130c8:
        // LD_A(0x6);
        // LD_addr_A(wc86b);
        wram->wc86b = 0x6;
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
        // CP_A(0x9f);
        // RET_Z ;
        if(wram->wMobileSDK_ReceivePacketBuffer[0] == (0x80 | MOBILE_COMMAND_TRANSFER_DATA_END))
            return;
        // JP(mFunction112430);
        return Function112430();
    }

// asm_1130d6:
    // LD_A_addr(wc82b);
    // LD_C_A;
    uint8_t c = wram->wc82b;
    // DEC_B;
    // DEC_B;
    b -= 2;
    // LD_A_B;
    // LD_addr_A(wc82d);
    wram->wc82d = b;
    // IF_Z goto asm_11310d;
    if(b != 0) {
        // LD_A_addr(wc873);
        // LD_D_A;
        // LD_A_addr(wc872);
        // LD_E_A;
        uint16_t de2 = (wram->wc873 << 8) | wram->wc872;
        // DEC_DE;
        // DEC_DE;
        de2 -= 2;
        // XOR_A_A;
        // OR_A_D;
        // IF_NZ goto asm_1130f5;
        // LD_A_E;
        // CP_A_B;
        // JP_C (mFunction113206);
        if(de2 < b)
            return Function113206(hl, b, c, LOW(de2));

    // asm_1130f5:
        // LD_A_E;
        // SUB_A_B;
        de2 -= b;
        // LD_addr_A(wc82b);
        wram->wc82b = LOW(de2);
        // LD_A_D;
        // SBC_A(0x0);
        // LD_addr_A(wc82c);
        wram->wc82c = HIGH(de2);
        // LD_A_addr(wc874);
        // LD_E_A;
        // LD_A_addr(wc875);
        // LD_D_A;
        // INC_DE;
        // INC_DE;
        de = gMobile_wc874_wc875 + 2;
        // CALL(aMobileSDK_CopyBytes);
        de = MobileSDK_CopyBytes(de, hl, b);
        hl += b;
    }

// asm_11310d:
    // LD_A_addr(wMobileSDK_ReceivePacketBuffer);
    // CP_A(0x9f);
    // IF_Z goto asm_113150;
    // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 3);
    // OR_A_A;
    // IF_Z goto asm_113150;
    if(wram->wMobileSDK_ReceivePacketBuffer[0] != (0x80 | MOBILE_COMMAND_TRANSFER_DATA_END) 
    && wram->wMobileSDK_ReceivePacketBuffer[3] != 0) {
        // LD_L_C;
        uint8_t l = c;
        // SUB_A_C;
        // LD_C_A;
        c = wram->wMobileSDK_ReceivePacketBuffer[3] - c;
        // LD_A_L;
        // LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
        // ADD_HL_BC;
        uint8_t* hl2 = wram->wMobileSDK_ReceivePacketBuffer + 4 + c;
        // LD_B_A;
        b = l;
        // PUSH_DE;
        // LD_A_addr(wc82b);
        // LD_E_A;
        // LD_A_addr(wc82c);
        // LD_D_A;
        uint16_t de2 = wram->wc82b | (wram->wc82c << 8);
        // XOR_A_A;
        // OR_A_D;
        // IF_NZ goto asm_113135;
        // LD_A_E;
        // CP_A_B;
        // JP_C (mFunction113245);
        if(de2 < b)
            return Function113245(de, hl2, b, LOW(de2));

    // asm_113135:
        // POP_DE;
        // PUSH_HL;
        // LD_HL(wc82d);
        uint16_t hl3 = wram->wc82d | (wram->wc82e << 8);
        // LD_A_hl;
        // ADD_A_B;
        // LD_hli_A;
        hl3 += b;
        // LD_A_hl;
        // ADC_A(0);
        // LD_hl_A;
        wram->wc82d = LOW(hl3);
        wram->wc82e = HIGH(hl3);
        // LD_C_B;
        // POP_HL;
        // CALL(aMobileSDK_CopyBytes);
        de = MobileSDK_CopyBytes(de, hl2, b);
        // LD_HL(wc82b);
        hl3 = wram->wc82b | (wram->wc82c << 8);
        // LD_A_hl;
        // SUB_A_C;
        hl3 -= b;
        // LD_hli_A;
        // LD_A_hl;
        // SBC_A(0x0);
        // LD_hl_A;
        wram->wc82b = LOW(hl3);
        wram->wc82c = HIGH(hl3);
    }

// asm_113150:
    // LD_HL(wc829);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hl_A;
    gMobileReceiveBuffer_Destination = de;
    // LD_HL(wc821);
    // RES_hl(2);
    bit_reset(wram->wc821, 2);
    // LD_A(0x1);
    // LD_addr_A(wc86b);
    wram->wc86b = 0x1;
    // LD_A(0x2);
    // LD_addr_A(wc989);
    wram->wc989 = 0x2;
    // RET;
}

// MobileSDK_ParseHTTPResponseHeaderURIHeader
char* Function113167(char* hl){
    // LD_DE(mUnknown_1132ff);
    // PUSH_HL;
    char* hl2 = hl;
    // CALL(aFunction113273);
    // IF_NC goto asm_113172;
    // POP_HL;
    // RET;
    if(!Function113273(&hl2, Unknown_1132ff)) {
    // asm_113172:
        // POP_DE;
        char* de = hl;
        // PUSH_BC;
        // PUSH_DE;
        // PUSH_HL;
        hl = hl2;
        // LD_B(0x0);
        uint8_t b = 0x0;
        char a;

        do {
        // asm_113178:
            // INC_B;
            b++;
            // LD_A_hli;
            a = *(hl2++);
            // CP_A(0xa);
            // IF_NZ goto asm_113178;
        } while(a != '\n');
        // JR(mFunction113197);
        Function113197(hl, b);
        hl = de;
    }
    return hl;
}

// MobileSDK_ParseHTTPResponseHeaderLocation
char* Function113180(char* hl){
    // LD_DE(mUnknown_11330c);
    // PUSH_HL;
    char* hl2 = hl;
    // CALL(aFunction113273);
    // IF_NC goto asm_11318b;
    // POP_HL;
    // RET;
    if(!Function113273(&hl2, Unknown_11330c)) {
    // asm_11318b:
        // POP_DE;
        char* de = hl;
        // PUSH_BC;
        // PUSH_DE;
        // PUSH_HL;
        hl = hl2;
        // LD_B(0x0);
        uint8_t b = 0x0;
        char a;

        do {
        // asm_113191:
            // INC_B;
            b++;
            // LD_A_hli;
            a = *(hl2++);
            // CP_A(0xa);
            // IF_NZ goto asm_113191;
        } while(a != 0xa);
        Function113197(hl, b);
        hl = de;
    }
    return hl;
}

void Function113197(char* hl, uint8_t b){
    // POP_HL;
    // LD_C_B;
    // LD_DE(wMobileSDK_PacketBuffer + 16);
    // LD_A_B;
    // LD_de_A;
    wram->wMobileSDK_PacketBuffer[16] = b;
    // INC_DE;
    // DEC_B;
    // DEC_B;
    // CALL(aMobileSDK_CopyBytes);
    uint8_t* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 17, hl, b - 2);
    // XOR_A_A;
    // LD_de_A;
    *de = 0x0;
    // POP_HL;
    // POP_BC;
    // RET;
}

void Function1131a9(void){
    // LD_HL(wc979);
    const char* hl = (const char*)&wram->wc979;
    // LD_DE(wc880);
    char* de = wram->wc880_str;
    // LD_B(0x0);
    uint8_t b = 0x0;
    // LD_C_B;
    uint8_t c = 0x0;
    char a;
    // LD_A_hl;
    // CP_A(0xa);
    // IF_Z goto asm_1131c4;
    if(*hl != '\n') {
        do {
        // asm_1131b7:
            // LD_A_hld;
            a = *(hl--);
            // INC_B;
            b++;
            // CP_A(0xa);
            // IF_NZ goto asm_1131b7;
        } while(a != '\n');
        // INC_HL;
        // INC_HL;
        hl += 2;
        // DEC_B;
        // LD_C_B;
        c = --b;
        // CALL(aMobileSDK_CopyBytes);
        de = MobileSDK_CopyBytes(de, hl, b);
    }

// asm_1131c4:
    // LD_A_addr(wc82b);
    // LD_B_A;
    b = wram->wc82b;
    // ADD_A_C;
    // LD_C_A;
    c += b;
    // PUSH_BC;
    // LD_A(0xff);
    // SUB_A_B;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wMobileSDK_ReceivePacketBuffer + 4);
    // ADD_HL_BC;
    // POP_BC;
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(de, wram->wMobileSDK_ReceivePacketBuffer + 4 + (0xff - b), b);
    // LD_A_C;
    // LD_addr_A(wc82d);
    wram->wc82d = c;
    // LD_A(0xfa);
    // SUB_A_C;
    // LD_addr_A(wc82b);
    wram->wc82b = 0xfa - c;
    // LD_HL(wc829);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hl_A;
    gMobileReceiveBuffer_Destination = (uint8_t*)de;
    // LD_L_E;
    // LD_H_D;
    // LD_DE(wc97a);

    do {
    // asm_1131ef:
        // XOR_A_A;
        // LD_hli_A;
        *(de++) = 0x0;
        // LD_A_L;
        // CP_A_E;
        // IF_NZ goto asm_1131ef;
        // LD_A_D;
        // CP_A_H;
        // IF_NZ goto asm_1131ef;
    } while(de != (char*)wram->wc97a);
    // LD_HL(wc821);
    // RES_hl(2);
    bit_reset(wram->wc821, 2);
    // LD_HL(wc86b);
    // DEC_hl;
    // DEC_hl;
    wram->wc86b -= 2;
    // LD_A(0x4);
    // RET;
    // return 0x4;
}

void Function113206(const char* hl, uint8_t b, uint8_t c, uint8_t e){
    // LD_A_B;
    // SUB_A_E;
    // LD_addr_A(wc991);
    wram->wc991 = b - e;
    // LD_A_addr(wc821);
    // BIT_A(2);
    // LD_A_C;
    // IF_NZ goto asm_113214;
    // XOR_A_A;

// asm_113214:
    // LD_addr_A(wc992);
    wram->wc992 = (bit_test(wram->wc821, 2))? c: 0;
    // LD_B_E;
    b = e;
    // LD_C_E;
    c = e;
    // LD_A_addr(wc874);
    // LD_E_A;
    // LD_A_addr(wc875);
    // LD_D_A;
    // INC_DE;
    // INC_DE;
    uint8_t* de = gMobile_wc874_wc875 + 2;
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(de, hl, b);
    hl += b;
    // LD_A_addr(wc991);
    // LD_addr_A(wc993);
    wram->wc993 = wram->wc991;
    // LD_B_A;
    // LD_DE(wc880);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wc880_str, hl, wram->wc991);
    // LD_HL(wc82d);
    // LD_A_C;
    // LD_hli_A;
    wram->wc82d = c;
    // XOR_A_A;
    // LD_hl_A;
    wram->wc82e = 0x0;
    // LD_HL(wc821);
    // SET_hl(2);
    bit_set(wram->wc821, 2);
    // LD_A(0x3);
    // LD_addr_A(wc86b);
    wram->wc86b = 0x3;
    // RET;
}

void Function113245(uint8_t* de, const uint8_t* hl, uint8_t b, uint8_t e){
    // LD_A_B;
    // SUB_A_E;
    // LD_addr_A(wc992);
    // LD_addr_A(wc82b);
    wram->wc82b = wram->wc992 = b - e;
    // LD_B_E;
    b = e;
    // LD_C_E;
    uint8_t c = e;
    // POP_DE;
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(de, hl, b);
    // LD_HL(wc82d);
    uint16_t hl2 = wram->wc82d | (wram->wc82e << 8);
    // LD_A_C;
    // ADD_A_hl;
    hl2 += c;
    // LD_hli_A;
    wram->wc82d = LOW(hl2);
    // LD_A(0x0);
    // ADC_A_hl;
    // LD_hl_A;
    wram->wc82e = HIGH(hl2);
    // LD_HL(wc821);
    // SET_hl(2);
    bit_set(wram->wc821, 2);
    // LD_A(0x3);
    // LD_addr_A(wc86b);
    wram->wc86b = 0x3;
    // RET;
}

// ContainsNewLineCharacter?
u8_flag_s Function113268(char** hl, uint8_t* b){
    do {
    // asm_113268:
        // DEC_B;
        --(*b);
        // LD_A_hli;
        char a = *((*hl)++);
        // CP_A(0xa);
        // RET_Z ;
        if(a == '\n')
            return u8_flag(*b, true);
        // XOR_A_A;
        // OR_A_B;
        // IF_NZ goto asm_113268;
    } while(*b != 0);
    // SCF;
    // RET;
    return u8_flag(*b, false);
}

// StringCompare?
bool Function113273(char** hl, const char* de){
    // LD_C(0x0);
    uint8_t c = 0x0;
    char a;

    do {
    // asm_113275:
        // LD_A_de;
        // INC_DE;
        a = *(de++);
        // OR_A_A;
        // RET_Z ;
        if(a == 0)
            return false;
        // XOR_A_hl;
        // INC_HL;
        a ^= *((*hl)++);
        // OR_A_C;
        c |= a;
        // LD_C_A;
        // IF_Z goto asm_113275;
    } while(c == 0);
    // SCF;
    // RET;
    return true;
}

// CaseInsensitiveStringCompare?
bool Function113281(char** hl, const char* de){
    // LD_C(0x0);
    uint8_t c = 0x0;
    // PUSH_HL;
    // LD_L_E;
    // LD_H_D;
    // POP_DE;
    bool result = true;
    char a;

    do {
    // asm_113287:
        // LD_A_de;
        // INC_DE;
        a = *((*hl)++);
        // CALL(aFunction11329d);
        // XOR_A_hl;
        a = Function11329d(a) ^ *de;
        // INC_HL;
        de++;
        // OR_A_C;
        // LD_C_A;
        c |= a;
        // XOR_A_A;
        // CP_A_hl;
        // IF_Z goto asm_113298;
        if(*de == 0) {
            result = false;
            break;
        }
        // CP_A_C;
        // IF_Z goto asm_113287;
    } while(a == c);
    // SCF;

// asm_113298:
    // PUSH_HL;
    // LD_L_E;
    // LD_H_D;
    // POP_DE;
    // RET;
    return result;
}

// ToLower?
uint8_t Function11329d(uint8_t a){
    // CP_A(0x41);
    // RET_C ;
    // CP_A(0x5b);
    // RET_NC ;
    if(a < 0x41 || a >= 0x5b)
        return a;
    // OR_A(0x20);
    // RET;
    return a | 0x20;
}

const char Unknown_1132a6[] = "Gb-Status: "; //db ['"Gb-Status: "', '0'];
const char Unknown_1132b2[] = "Gb-Auth-ID: "; //db ['"Gb-Auth-ID: "', '0'];
const char Unknown_1132bf[] = "WWW-Authenticate: GB00 name=\""; //db ['"WWW-Authenticate: GB00 name="', '0x22', '0'];
const char Unknown_1132dd[] = "Content-Type: application/x-cgb\r\n"; //db ['"Content-Type: application/x-cgb"', '0xd', '"\\n"', '0'];
const char Unknown_1132ff[] = "URI-header: "; // ['"URI-header: "', '0'];
const char Unknown_11330c[] = "Location: "; //db ['"Location: "', '0'];

// MobileSDK_CopyHTTPRequestPacket
void Function113317(void){
    // LD_A(0x1);
    // LD_addr_A(wc86b);
    wram->wc86b = 0x1;
    // LD_DE(wMobileSDK_PacketBuffer + 18);
    char* de = (char*)wram->wMobileSDK_PacketBuffer + 18;
    // LD_A_addr(wc86c);
    // LD_de_A;
    // INC_DE;
    *(de++) = wram->wc86c;
    // LD_BC(0x0001);
    uint16_t bc = 0x0001;
    // CALL(aFunction1126b0);
    de = Function1126b0(de, &bc);
    // LD_HL(mUnknown_1132dd);
    // LD_A_addr(wc9a5);
    // OR_A_A;
    // CALL_NZ (aMobileSDK_CopyString);
    if(wram->wc9a5[0] != 0) {
        de = MobileSDK_CopyString(de, Unknown_1132dd, &bc);
    }
    // LD_A_addr(wc86a);
    // CP_A(0x22);
    // IF_NZ goto asm_113344;
    if(wram->wc86a == 0x22) {
        // LD_A_addr(wc98a);
        // CP_A(0x2);
        // IF_NZ goto asm_113351;
        if(wram->wc98a != 0x2)
            goto asm_113351;
        // goto asm_113348;
    }
    else {
    // asm_113344:
        // CP_A(0x24);
        // IF_NZ goto asm_113351;
        if(wram->wc86a != 0x24)
            goto asm_113351;
    }

// asm_113348:
    // LD_A_addr(wc9a5);
    // OR_A_A;
    // IF_Z goto asm_11336a;
    if(wram->wc9a5[0] == 0) {
    // asm_11336a:
        // LD_HL(mUnknown_113372);
        // CALL(aMobileSDK_CopyString);
        de = MobileSDK_CopyString(de, Unknown_113372, &bc);
        // goto asm_113351;
    }
    else {
        // CALL(aFunction1133de);
        de = Function1133de(de, &bc);
    }

asm_113351:
    // LD_HL(wc9b5);
    // CALL(aMobileSDK_CopyString);
    de = MobileSDK_CopyString(de, (char*)&wram->wc9b5, &bc);
    // CALL(aFunction1126b6);
    de = Function1126b6(de, &bc);
    // LD_A_C;
    // LD_addr_A(wMobileSDK_PacketBuffer + 17);
    wram->wMobileSDK_PacketBuffer[17] = (bc & 0xff);
    // LD_B_C;
    // CALL(aFunction111f63);
    bc = Function111f63(de, bc & 0xff);
    // LD_A(0x95);
    // LD_HL(wMobileSDK_PacketBuffer + 12);
    // JP(mFunction111f02);
    Function111f02(wram->wMobileSDK_PacketBuffer + 12, bc, MOBILE_COMMAND_TRANSFER_DATA | 0x80);
}

const char Unknown_113372[] = "Content-Length: 0\r\n"; //db ['"Content-Length: 0"', '0xd', '"\\n"', '0'];

void Function113386(void){
    // CALL(aFunction113482);
    if(Function113482())
        return;
    // LD_A(0x1);
    // LD_addr_A(wc86b);
    wram->wc86b = 0x1;
    // LD_DE(wMobileSDK_PacketBuffer);
    // LD_HL(mMobilePacket_TransferData);
    // LD_B(0x6);
    // CALL(aMobileSDK_CopyBytes);
    char* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer, MobilePacket_TransferData, 0x6);
    // LD_A_addr(wc86c);
    // LD_de_A;
    *de = wram->wc86c;
    // INC_DE;
    de++;
    // LD_B(0x1);
    // CALL(aFunction111f63);
    Function111f63(de, 0x1);
    // LD_DE(wMobileSDK_PacketBuffer + 12);
    // LD_HL(mMobilePacket_TransferData);
    // LD_B(0x6);
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 12, MobilePacket_TransferData, 0x6);
    // LD_A_addr(wc86d);
    // CP_A(0x3);
    // JP_NZ (mFunction113317);
    if(wram->wc86d != 0x3)
        return Function113317();
    // LD_DE(wMobileSDK_PacketBuffer + 18);
    de = (char*)wram->wMobileSDK_PacketBuffer + 18;
    // LD_A_addr(wc86c);
    // LD_de_A;
    // INC_DE;
    *(de++) = wram->wc86c;
    // LD_BC(0x0001);
    uint16_t bc = 0x0001;
    // CALL(aFunction1126b0);
    de = Function1126b0(de, &bc);
    // LD_A_addr(wc994);
    // OR_A_A;
    // CALL_NZ (aFunction1133de);
    if(wram->wc994 != HTTP_METHOD_GET)
        de = Function1133de(de, &bc);
    // CALL(aFunction1126b6);
    de = Function1126b6(de, &bc);
    // LD_A_C;
    // LD_addr_A(wMobileSDK_PacketBuffer + 17);
    wram->wMobileSDK_PacketBuffer[17] = bc & 0xff;
    // LD_B_C;
    // CALL(aFunction111f63);
    bc = Function111f63(de, bc & 0xff);
    // LD_A(0x95);
    // LD_HL(wMobileSDK_PacketBuffer + 12);
    // JP(mFunction111f02);
    Function111f02(wram->wMobileSDK_PacketBuffer + 12, bc, MOBILE_COMMAND_TRANSFER_DATA | 0x80);
}

// MobileSDK_CopyPOSTHeader?
char* Function1133de(char* de, uint16_t* bc){
    // CALL(aFunction1126e6);
    de = Function1126e6(de, bc);
    // XOR_A_A;
    // LD_addr_A(wc86b);
    wram->wc86b = 0x0;
    // LD_A_addr(wc9aa);
    // LD_addr_A(wc87c);
    // LD_A_addr(wc9ab);
    // LD_addr_A(wc87d);
    gMobile_wc87c_wc87d = gMobile_wc9aa_wc9ab;
    // LD_A_addr(wc9ac);
    // LD_addr_A(wc87e);
    wram->wc87e = wram->wc9ac;
    // LD_A_addr(wc9ad);
    // LD_addr_A(wc87f);
    wram->wc87f = wram->wc9ad;
    // RET;
    return de;
}

// TODO: Finish converting this function.
void Function1133fe(void){
    // LD_HL(wMobileSDK_PacketBuffer + 17);
    // LD_A_hli;
    // CP_A(0x68);
    // IF_NZ goto asm_113432;
    // LD_A_hli;
    // CP_A(0x74);
    // IF_NZ goto asm_113432;
    // LD_A_hli;
    // CP_A(0x74);
    // IF_NZ goto asm_113432;
    // LD_A_hli;
    // CP_A(0x70);
    // IF_NZ goto asm_113432;
    // LD_A_hli;
    // CP_A(0x3a);
    // IF_NZ goto asm_113432;
    // LD_A_hli;
    // CP_A(0x2f);
    // IF_NZ goto asm_113432;
    // LD_A_hli;
    // CP_A(0x2f);
    // IF_NZ goto asm_113432;
    if(CompareBytes(wram->wMobileSDK_PacketBuffer + 17, "http://", sizeof("http://") - 1) == 0) {
        // LD_HL(wMobileSDK_PacketBuffer + 16);
        // LD_DE(wc880);
        // LD_A_hli;
        // LD_B_A;
        // CALL(aMobileSDK_CopyBytes);
        char* de = MobileSDK_CopyBytes(wram->wc880_str, wram->wMobileSDK_PacketBuffer + 17, wram->wMobileSDK_PacketBuffer[16]);
        // XOR_A_A;
        // LD_de_A;
        *de = 0x0;
        // RET;
        return;
    }

// asm_113432:
    char* de;
    // LD_A_addr(wMobileSDK_PacketBuffer + 17);
    // CP_A(0x2f);
    // IF_Z goto asm_113460;
    if(wram->wMobileSDK_PacketBuffer[17] != '/') {
        // LD_DE(wc880);
        de = wram->wc880_str;
        // LD_HL(wc9b5);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // INC_HL;
        // INC_HL;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        char* hl = GBToRAMAddr(gMobile_wc9b5[2] | (gMobile_wc9b5[3] << 8));
        // CALL(aMobileSDK_CopyString);
        // LD_L_E;
        // LD_H_D;
        uint16_t bc = 0;
        hl = MobileSDK_CopyString(de, hl, &bc);

        do {
        // asm_11344c:
            // LD_A_hld;
            // CP_A(0x2f);
            // IF_NZ goto asm_11344c;
        } while(*(hl--) != '/');
        // INC_HL;
        // INC_HL;
        // LD_E_L;
        // LD_D_H;
        de = hl + 2;
    }
    else {
    // asm_113460:
        // LD_DE(wc880);
        de = wram->wc880_str;
        // LD_HL(wc9b5);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // INC_HL;
        // INC_HL;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        char* hl = GBToRAMAddr(gMobile_wc9b5[2] | (gMobile_wc9b5[3] << 8));
        // LD_A_hl;
        // CP_A(0x2f);
        // IF_Z goto asm_113478;
        if(*hl != '/') {
            // LD_B(0x7);
            // CALL(aMobileSDK_CopyBytes);
            MobileSDK_CopyBytes(de, hl, 0x7);
            de += 7;
            hl += 7;
        }

        char ch;
        do {
        // asm_113478:
            // LD_A_hli;
            ch = *(hl++);
            // LD_de_A;
            // INC_DE;
            *(de++) = ch;
            // CP_A(0x2f);
            // IF_NZ goto asm_113478;
        } while(ch != '/');
        // DEC_DE;
        de--;
        // goto asm_113455;
    }

// asm_113455:
    // LD_HL(wMobileSDK_PacketBuffer + 16);
    // LD_A_hli;
    // LD_B_A;
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(de, wram->wMobileSDK_PacketBuffer + 17, wram->wMobileSDK_PacketBuffer[16]);
    // XOR_A_A;
    // LD_de_A;
    *de = 0;
    // RET;
}

// Mobile_CopyHTTPRequestURL
bool Function113482(void){
    // LD_HL(wc87f);
    // LD_A_hld;
    // LD_B_A;
    // LD_A_hld;
    // LD_C_A;
    uint16_t bc = (wram->wc87f << 8) | wram->wc87e;
    // LD_A_B;
    // OR_A_C;
    // RET_Z ;
    if(bc == 0)
        return false;
    // POP_HL;
    // LD_HL(rSC);
    // ADD_HL_BC;
    // IF_C goto asm_113496;
    bool carry = ((bc + rSC) & 0xffff0000) != 0;
    // XOR_A_A;
    // LD_L_A;
    // LD_H_A;

// asm_113496:
    // LD_E_L;
    // LD_D_H;
    uint16_t de = carry? bc + rSC: 0x0;
    // LD_HL(wc87f);
    // LD_A_D;
    // LD_hld_A;
    wram->wc87f = HIGH(de);
    // LD_A_E;
    // LD_hld_A;
    wram->wc87e = LOW(de);
    // IF_NC goto asm_1134a3;
    // LD_C(0xfe);

// asm_1134a3:
    uint8_t c = (carry)? 0xfe: LOW(bc);
    // LD_A_hld;
    // LD_L_hl;
    // LD_H_A;
    // LD_A_C;
    // INC_A;
    // LD_addr_A(wMobileSDK_PacketBuffer + 5);
    wram->wMobileSDK_PacketBuffer[5] = c + 1;
    // LD_DE(wMobileSDK_PacketBuffer + 7);
    // LD_B_C;
    // CALL(aMobileSDK_CopyBytes);
    uint8_t* de2 = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 7, gMobile_wc87c_wc87d, c);
    // LD_A_L;
    // LD_addr_A(wc87c);
    // LD_A_H;
    // LD_addr_A(wc87d);
    gMobile_wc87c_wc87d += c;
    // LD_B_C;
    // INC_B;
    // CALL(aFunction111f63);
    uint16_t size = Function111f63(de2, c + 1);
    // LD_HL(wc86b);
    // DEC_hl;
    wram->wc86b--;
    // LD_HL(wMobileSDK_PacketBuffer);
    // LD_A(0x95);
    // JP(mFunction111f02);
    Function111f02(wram->wMobileSDK_PacketBuffer, size, MOBILE_COMMAND_TRANSFER_DATA | 0x80);
    return true;
}

void Function1134cb(uint8_t* hl, uint8_t a){
    // DEC_A;
    // IF_Z goto asm_1134d9;
    if(a == 0x1) {
    // asm_1134d9:
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 4);
        // CP_A(0x0);
        // IF_Z goto asm_1134f0;
        // CP_A(0xff);
        // IF_Z goto asm_1134f0;
        if(wram->wMobileSDK_ReceivePacketBuffer[4] == 0x0 || wram->wMobileSDK_ReceivePacketBuffer[4] == 0xff) {
        // asm_1134f0:
            // INC_hl;
            // INC_hl;
            (*hl) += 2;
            goto asm_1134fc;
        }
        // LD_A_addr(wc985);
        // LD_addr_A(wc86a);
        wram->wc86a = wram->wc985;
        // LD_HL(wc821);
        // RES_hl(0);
        bit_reset(wram->wc821, 0);
        // RET;
        return;
    }
    // DEC_A;
    // IF_Z goto asm_1134f4;
    else if(a == 0x2) {
    // asm_1134f4:
        // LD_A(MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
        // LD_HL(mMobilePacket_TelephoneStatus);
        // JP(mPacketSendEmptyBody);
        PacketSendEmptyBody(MobilePacket_TelephoneStatus, MOBILE_COMMAND_TELEPHONE_STATUS | 0x80);
        return;
    }
    // DEC_A;
    // IF_Z goto asm_1134fc;
    else if(a == 0x3) {
    asm_1134fc:
        // LD_HL(wc86e);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        uint8_t* hl2 = gMobile_wc86e_wc86f;
        // LD_A_addr(wMobileSDK_ReceivePacketBuffer + 6);
        // CP_A(0xf0);
        // IF_C goto asm_11350b;
        if(wram->wMobileSDK_ReceivePacketBuffer[6] >= 0xf0) {
            // SET_hl(7);
            bit_set(*hl2, 7);
        }

    // asm_11350b:
        // JP(mFunction112269);
        Function112269();
        return;
    }
    // DEC_A;
    // IF_Z goto asm_11350e;
    else if(a == 0x4) {
    // asm_11350e:
        // LD_A_addr(wc86a);
        // CP_A(0x1e);
        // JP_NZ (mFunction112251);
        if(wram->wc86a != 0x1e)
            return Function112251();
        // JP(mFunction1116a0);
        return Function1116a0();
    }
    else {
        // DEC_hl;
        (*hl)--;
        // RET;
    }
}

void Function113519(uint8_t* hl, uint8_t a){
    // DEC_A;
    // IF_Z goto asm_113527;
    if(a == 0x1) {
    // asm_113527:
        // LD_HL(mMobilePacket_ReadConfigurationDataPart1);
        // JP(mFunction11236b);
        Function11236b(MobilePacket_ReadConfigurationDataPart1);
        return;
    }
    // DEC_A;
    // IF_Z goto asm_11352d;
    else if(a == 0x2) {
    // asm_11352d:
        // LD_HL(wc829);
        // LD_A(0xe0);
        // LD_hli_A;
        // LD_A(0xc8);
        // LD_hli_A;
        gMobileReceiveBuffer_Destination = wram->wc8ca + 0x16;
        // LD_HL(mMobilePacket_ReadConfigurationDataPart2);
        // JP(mFunction11236b);
        Function11236b(MobilePacket_ReadConfigurationDataPart2);
        return;
    }
    // DEC_A;
    // IF_Z goto asm_11353c;
    else if(a == 0x3) {
    // asm_11353c:
        // JP(mFunction112269);
        Function112269();
        return;
    }
    // DEC_A;
    // IF_Z goto asm_11353f;
    else if(a == 0x4) {
    // asm_11353f:
        // LD_HL(wc880);
        // LD_A_hli;
        // CP_A(0x4d);
        // IF_NZ goto asm_113586;
        // LD_A_hld;
        // CP_A(0x41);
        // IF_NZ goto asm_113586;
        if(wram->wc880_str[0] == 'M' && wram->wc880_str[1] == 'A') {
            // LD_B(0xbe);
            uint8_t b = 0xbe;
            // LD_DE(0);
            uint16_t de = 0;
            uint8_t* str = (uint8_t*)wram->wc880_str;

            do {
            // asm_113551:
                // LD_A_hli;
                // ADD_A_E;
                // LD_E_A;
                // LD_A(0x0);
                // ADC_A_D;
                // LD_D_A;
                de += *(str++);
                // DEC_B;
                // IF_NZ goto asm_113551;
            } while(--b != 0);
            // LD_A_hli;
            // CP_A_D;
            // IF_NZ goto asm_11358a;
            // LD_A_hl;
            // CP_A_E;
            // IF_NZ goto asm_11358a;
            if(HIGH(de) == str[0] && LOW(de) == str[1]) {
                // LD_A_addr(wc86e);
                // LD_E_A;
                // LD_A_addr(wc86f);
                // LD_D_A;
                char* de2 = (char*)gMobile_wc86e_wc86f;
                uint16_t bc;
                // LD_HL(mFunction113519_asm_11357e);
                // PUSH_HL;
                // LD_A_addr(wc86a);
                // CP_A(0x25);
                // JR_Z (mFunction1135ba);
                if(wram->wc86a == 0x25)
                    de2 = Function1135ba(de2);
                // CP_A(0x26);
                // JR_Z (mFunction11359d);
                else if(wram->wc86a == 0x26)
                    de2 = Function11359d(de2, &bc);
                // CP_A(0x27);
                // JR_Z (mFunction1135ad);
                else if(wram->wc86a == 0x27)
                    de2 = Function1135ad(de2, &bc);

            // asm_11357e:
                // LD_A(0x1);
                // LD_addr_A(wc835);
                wram->wc835 = 0x1;
                // JP(mFunction1116a0);
                Function1116a0();
                return;
            }
            else {
            // asm_11358a:
                // LD_A(0x14);
                a = 0x14;
            }
        }
        else {
        // asm_113586:
            // LD_A(0x25);
            a = 0x25;
            // goto asm_11358c;
        }

    // asm_11358c:
        // CALL(aFunction11225d);
        // JP(mFunction1116a4);
        Function1116a4(Function11225d(a));
        return;
    }
    else {
        // DEC_hl;
        (*hl)--;
        // RET;
    }
}

// ClearString?
void Function113592(char* de, uint8_t b){
    // PUSH_DE;
    // LD_L_E;
    // LD_H_D;
    // XOR_A_A;
    // LD_hl_A;
    *de = 0x0;
    // INC_DE;
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(de + 1, de, b);
    // POP_DE;
    // RET;
}

char* Function11359d(char* de, uint16_t* bc){
    // LD_B(0x20);
    // CALL(aFunction113592);
    Function113592(de, 0x20);
    // LD_A(0x21);
    // LD_HL(wc88c);
    // CALL(aMobileSDK_CopyStringLen);
    de = MobileSDK_CopyStringLen(de, (const char*)wram->wc88c, bc, 0x21);
    // XOR_A_A;
    // LD_de_A;
    *de = 0x0;
    // RET;
    return de;
}

char* Function1135ad(char* de, uint16_t* bc){
    // LD_B(0x1e);
    // CALL(aFunction113592);
    Function113592(de, 0x20);
    // LD_A(0x1f);
    // LD_HL(wc8ac);
    // JP(mMobileSDK_CopyStringLen);
    return MobileSDK_CopyStringLen(de, (const char*)wram->wc8ac, bc, 0x1f);
}

char* Function1135ba(char* de){
    // LD_B(0x65);
    // CALL(aFunction113592);
    Function113592(de, 0x65);
    char* de2 = de;
    // LD_HL(wc8f6);
    // CALL(aFunction1135eb);
    de = Function1135eb(de, wram->wc8f6);
    uint16_t bc = 0;
    // LD_A(0x11);
    // LD_HL(wc8fe);
    // CALL(aMobileSDK_CopyStringLen);
    de = MobileSDK_CopyStringLen(de, (const char*)&wram->wc8fe, &bc, 0x11);
    // INC_DE;
    de++;
    // LD_HL(wc90e);
    // CALL(aFunction1135eb);
    de = Function1135eb(de, wram->wc90e);
    // LD_A(0x11);
    // LD_HL(wc916);
    // CALL(aMobileSDK_CopyStringLen);
    de = MobileSDK_CopyStringLen(de, (const char*)wram->wc916, &bc, 0x11);
    // INC_DE;
    de++;
    // LD_HL(wc926);
    // CALL(aFunction1135eb);
    de = Function1135eb(de, wram->wc926);
    printf("Copying \"%s\"\n", de2);
    // LD_A(0x11);
    // LD_HL(wc92e);
    // JP(mMobileSDK_CopyStringLen);
    return MobileSDK_CopyStringLen(de, (const char*)wram->wc92e, &bc, 0x11);
}

// ExpandNumberString?
char* Function1135eb(char* de, const uint8_t* hl){
    // LD_B(0x8);
    uint8_t b = 0x8;

    do {
    // asm_1135ed:
        // LD_A_hl;
        // SWAP_A;
        // AND_A(0xf);
        char c = (*hl >> 4) & 0xf;
        // CP_A(0xf);
        // IF_Z goto asm_11361c;
        if(c == 0xf)
            break;
        // OR_A(0x30);
        c |= 0x30;
        // CP_A(0x3a);
        // CALL_Z (aFunction113620);
        if(c == 0x3a)
            c = Function113620();
        // CP_A(0x3b);
        // CALL_Z (aFunction113623);
        if(c == 0x3b)
            c = Function113623();
        // LD_de_A;
        // INC_DE;
        *(de++) = c;
        // LD_A_hli;
        // AND_A(0xf);
        c = *hl & 0xf;
        hl++;
        // CP_A(0xf);
        // IF_Z goto asm_11361c;
        if(c == 0xf)
            break;
        // OR_A(0x30);
        c |= 0x30;
        // CP_A(0x3a);
        // CALL_Z (aFunction113620);
        if(c == 0x3a)
            c = Function113620();
        // CP_A(0x3b);
        // CALL_Z (aFunction113623);
        if(c == 0x3b)
            c = Function113623();
        // LD_de_A;
        // INC_DE;
        *(de++) = c;
        // DEC_B;
        // IF_NZ goto asm_1135ed;
    } while(--b != 0);

// asm_11361c:
    // XOR_A_A;
    // LD_de_A;
    // INC_DE;
    *(de++) = '\0';
    // RET;
    return de;
}

char Function113620(void){
    // LD_A(0x23);
    // RET;
    return '#';
}

char Function113623(void){
    // LD_A(0x2a);
    // RET;
    return '*';
}

void Function113626(uint8_t* hl, uint8_t a){
    // DEC_A;
    // IF_Z goto asm_113634;
    if(a == 0x1) {
    // asm_113634:
        // LD_B(0x9a);
        // JP(mFunction11234b);
        return Function11234b(0x9a);
    }
    // DEC_A;
    // IF_Z goto asm_113639;
    else if(a == 0x2) {
    // asm_113639:
        // LD_A_addr(wc882);
        // OR_A_A;
        // IF_NZ goto asm_113642;
        if(wram->wc882 == 0x0) {
            // INC_hl;
            (*hl)++;
            goto asm_11366c;
        }
    // asm_113642:
        // LD_DE(wMobileSDK_PacketBuffer + 5);
        // LD_C_A;
        // INC_A;
        // LD_de_A;
        wram->wMobileSDK_PacketBuffer[5] = a + 1;
        // INC_DE;
        // LD_A(0x80);
        // LD_de_A;
        wram->wMobileSDK_PacketBuffer[6] = 0x80;
        // INC_DE;
        // LD_HL(wc880);
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // LD_B_C;
        // CALL(aMobileSDK_CopyBytes);
        uint8_t* de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 7, GBToRAMAddr(wram->wc880 | (wram->wc881 << 8)), a); // TODO: Replace wc880 pointer with real pointer.
        // LD_B_C;
        // INC_B;
        // CALL(aFunction111f63);
        Function111f63(de, a + 1);
        // LD_A_addr(wMobileSDK_PacketBuffer + 5);
        // ADD_A(0xa);
        // LD_E_A;
        // LD_D(0);
        // LD_A(0x9a);
        // LD_HL(wMobileSDK_PacketBuffer);
        // JP(mFunction111f02);
        Function111f02(wram->wMobileSDK_PacketBuffer, wram->wMobileSDK_PacketBuffer[5] + 0xa, MOBILE_COMMAND_WRITE_CONFIGURATION_DATA | 0x80);
        return;
    }
    // DEC_A;
    // IF_Z goto asm_11366c;
    else if(a == 0x3) {
    asm_11366c:
        // JP(mFunction112269);
        Function112269();
        return;
    }
    // DEC_A;
    // IF_Z goto asm_11366f;
    else if(a == 0x4) {
    // asm_11366f:
        // JP(mFunction1116a0);
        return Function1116a0();
    }
    else {
        // DEC_hl;
        (*hl)--;
        // RET;
    }
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

void Function1136c1(char* hl, uint8_t* de, uint8_t b){
    // XOR_A_A;
    // LD_addr_A(wMobileSDK_PacketBuffer + 225);
    wram->wMobileSDK_PacketBuffer[225] = 0;
    // LD_A_L;
    // LD_addr_A(wMobileSDK_PacketBuffer + 192);
    // LD_A_H;
    // LD_addr_A(wMobileSDK_PacketBuffer + 193);
    // LD_HL(wMobileSDK_PacketBuffer + 194);
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hli_A;
    uint8_t* de_saved = de;
    // LD_A_B;
    // LD_hli_A;
    wram->wMobileSDK_PacketBuffer[196] = b;
    // LD_HL(wMobileSDK_PacketBuffer + 192);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(wMobileSDK_PacketBuffer + 32);
    // LD_B(0x30);
    // LD_C_B;
    // CALL(aMobileSDK_CopyBytes);
    de = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 32, hl, 0x30);
    // LD_HL(wc97f);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl2 = gMobile_wc97f_wc980;

    do {
    // asm_1136eb:
        // LD_A_hli;
        // OR_A_A;
        // IF_NZ goto asm_1136eb;
    } while(*(hl2++) != 0);
    // CALL(aMobileSDK_CopyString);
    uint16_t bc = 0x30;
    char* de_str = MobileSDK_CopyString((char*)de, (char*)hl2, &bc);
    // LD_A(0x37);
    // CP_A_C;
    uint8_t a = 0x38;
    // INC_A;
    // IF_NC goto asm_1136ff;
    if(0x37 < LOW(bc)) {
        // LD_A(0x2);
        // LD_addr_A(wMobileSDK_PacketBuffer + 225);
        wram->wMobileSDK_PacketBuffer[225] = 0x2;
        // LD_A(0x78);
        a = 0x78;
    }

// asm_1136ff:
    // SUB_A_C;
    // LD_B_A;
    b = a - LOW(bc);
    // LD_A(0x80);
    // LD_de_A;
    // INC_DE;
    *(de_str++) = 0x80;
    // XOR_A_A;

    while(--b != 0) {
    // asm_113706:
        // DEC_B;
        // IF_Z goto asm_11370d;
        // LD_de_A;
        // INC_DE;
        *(de_str++) = 0;
        // goto asm_113706;
    }

// asm_11370d:
    bc = LOW(bc);
    // OR_A_A;
    // SLA_C;
    // RL_B;
    // SLA_C;
    // RL_B;
    // SLA_C;
    // RL_B;
    bc <<= 3;
    // LD_A_C;
    // LD_de_A;
    // INC_DE;
    *(de_str++) = LOW(bc);
    // LD_A_B;
    // LD_de_A;
    // INC_DE;
    *(de_str++) = HIGH(bc);
    // LD_L_E;
    // LD_H_D;
    // LD_B(0x6);
    b = 0x6;
    // XOR_A_A;

    do {
    // asm_113725:
        // LD_hli_A;
        *(de_str++) = 0;
        // DEC_B;
        // IF_NZ goto asm_113725;
    } while(--b != 0);
    // LD_DE(wMobileSDK_PacketBuffer + 160);
    // LD_HL(mUnknown_113b7e);
    // LD_B(0x10);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 160, Unknown_113b7e, 0x10);

    while(1) {
    // asm_113734:
        // LD_HL(wMobileSDK_PacketBuffer + 197);
        // LD_A(LOW(aMD5_K_Table));
        // LD_hli_A;
        // LD_A(HIGH(aMD5_K_Table));
        // LD_hl_A;
        const uint32_t* table = MD5_K_Table;
        // LD_HL(wMobileSDK_PacketBuffer + 199);
        // LD_A(LOW(aUnknown_113a70));
        // LD_hli_A;
        // LD_A(HIGH(aUnknown_113a70));
        // LD_hl_A;
        const uint8_t* table2 = Unknown_113a70;
        // LD_HL(wMobileSDK_PacketBuffer + 160);
        // LD_DE(wMobileSDK_PacketBuffer + 209);
        // LD_B(0x10);
        // CALL(aMobileSDK_CopyBytes);
        MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 209, wram->wMobileSDK_PacketBuffer + 160, 0x10);

        do {
        // asm_113751:
            // LD_HL(wMobileSDK_PacketBuffer + 199);
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            const uint8_t* hl = table2;
            // LD_A_hli;
            // LD_C_A;
            uint8_t c = *(hl++);
            // PUSH_HL;
            // CALL(aFunction113909);
            Function113909(c, c);
            // LD_HL(wMobileSDK_PacketBuffer + 176);
            // LD_A_hli;
            // LD_D_hl;
            // LD_E_A;
            uint8_t* de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[176] | (wram->wMobileSDK_PacketBuffer[177] << 8));
            // LD_HL(wMobileSDK_PacketBuffer + 184);
            // CALL(aFunction113a32);
            Function113a32(wram->wMobileSDK_PacketBuffer + 184, de);
            // POP_HL;
            // LD_A_hli;
            // LD_D_hl;
            // INC_HL;
            // LD_E_A;
            // PUSH_HL;
            uint16_t de2 = hl[0] | (hl[1] << 8);
            hl += 2;
            // LD_A_addr(wMobileSDK_PacketBuffer + 225);
            // BIT_A(0);
            // IF_Z goto asm_11377c;
            if(bit_test(wram->wMobileSDK_PacketBuffer[225], 0)) {
                // LD_HL(0x0040);
                // ADD_HL_DE;
                // LD_E_L;
                // LD_D_H;
                de2 += 0x0040;
            }

        // asm_11377c:
            // LD_HL(wMobileSDK_PacketBuffer + 32);
            // ADD_HL_DE;
            // LD_E_L;
            // LD_D_H;
            // LD_HL(wMobileSDK_PacketBuffer + 184);
            // CALL(aFunction113a32);
            Function113a32(wram->wMobileSDK_PacketBuffer + 184, wram->wMobileSDK_PacketBuffer + 32 + de2);
            // LD_HL(wMobileSDK_PacketBuffer + 197);
            // LD_A_hli;
            // LD_D_hl;
            // LD_E_A;
            // LD_HL(wMobileSDK_PacketBuffer + 184);
            // CALL(aFunction113a32);
            Function113a32(wram->wMobileSDK_PacketBuffer + 184, (const uint8_t*)table);
            // POP_HL;
            // LD_A_hli;
            // LD_B_A;
            uint8_t b = *(hl++);
            // LD_A_L;
            // LD_addr_A(wMobileSDK_PacketBuffer + 199);
            // LD_A_H;
            // LD_addr_A(wMobileSDK_PacketBuffer + 200);
            table2 = hl;
            // LD_HL(wMobileSDK_PacketBuffer + 184);
            // CALL(aFunction113a40);
            Function113a40((uint32_t*)(wram->wMobileSDK_PacketBuffer + 184), b);
            // LD_HL(wMobileSDK_PacketBuffer + 178);
            // LD_A_hli;
            // LD_D_hl;
            // LD_E_A;
            de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[178] | (wram->wMobileSDK_PacketBuffer[179] << 8));
            // LD_HL(wMobileSDK_PacketBuffer + 184);
            // CALL(aFunction113a32);
            Function113a32(wram->wMobileSDK_PacketBuffer + 184, de);
            // LD_HL(wMobileSDK_PacketBuffer + 176);
            // LD_A_hli;
            // LD_D_hl;
            // LD_E_A;
            de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[176] | (wram->wMobileSDK_PacketBuffer[177] << 8));
            // LD_HL(wMobileSDK_PacketBuffer + 184);
            // LD_B(0x4);
            // CALL(aMobileSDK_CopyBytes);
            MobileSDK_CopyBytes(de, wram->wMobileSDK_PacketBuffer + 184, 0x4);
            // LD_HL(wMobileSDK_PacketBuffer + 197);
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // for(int rept = 0; rept < 4; rept++){
            // INC_HL;
            // }
            table++;
            // LD_A_H;
            // LD_addr_A(wMobileSDK_PacketBuffer + 198);
            // LD_A_L;
            // LD_addr_A(wMobileSDK_PacketBuffer + 197);
            // CP_A(0x8e);  // LOW(MD5_K_Table + $100) ???
            // JP_NZ (mFunction1136c1_asm_113751);
        } while(table - MD5_K_Table != 0x100 / 4);
        // LD_DE(wMobileSDK_PacketBuffer + 209);
        // LD_HL(wMobileSDK_PacketBuffer + 160);
        // CALL(aFunction113a32);
        Function113a32(wram->wMobileSDK_PacketBuffer + 160, wram->wMobileSDK_PacketBuffer + 209);
        // LD_DE(wMobileSDK_PacketBuffer + 213);
        // CALL(aFunction113a32);
        Function113a32(wram->wMobileSDK_PacketBuffer + 164, wram->wMobileSDK_PacketBuffer + 213);
        // LD_DE(wMobileSDK_PacketBuffer + 217);
        // CALL(aFunction113a32);
        Function113a32(wram->wMobileSDK_PacketBuffer + 168, wram->wMobileSDK_PacketBuffer + 217);
        // LD_DE(wMobileSDK_PacketBuffer + 221);
        // CALL(aFunction113a32);
        Function113a32(wram->wMobileSDK_PacketBuffer + 172, wram->wMobileSDK_PacketBuffer + 221);
        // LD_HL(wMobileSDK_PacketBuffer + 225);
        // BIT_hl(1);
        // IF_Z goto asm_1137fc;
        if(!bit_test(wram->wMobileSDK_PacketBuffer[225], 1))
            break;
        // DEC_hl;
        wram->wMobileSDK_PacketBuffer[225]--;
        // JP(mFunction1136c1_asm_113734);
    }

// asm_1137fc:
    // LD_HL(wMobileSDK_PacketBuffer + 32);
    // LD_DE(wMobileSDK_PacketBuffer + 80);
    // LD_BC(0x0030);
    // CALL(aFunction113d66);
    Function113d66(wram->wMobileSDK_PacketBuffer + 80, wram->wMobileSDK_PacketBuffer + 32, 0x0030);
    // LD_HL(wMobileSDK_PacketBuffer + 194);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    de_str = (char*)de_saved;
    // LD_HL(mUnknown_113a55);
    // CALL(aMobileSDK_CopyString);
    de_str = MobileSDK_CopyString(de_str, Unknown_113a55, &bc); // Copy "Authorization: GB00 name="
    // LD_HL(wMobileSDK_PacketBuffer + 80);
    // LD_BC(0x0020);
    // CALL(aFunction113c8e);
    de_saved = Function113c8e((uint8_t*)de_str, wram->wMobileSDK_PacketBuffer + 80, 0x0020);
    // LD_A_L;
    // LD_addr_A(wMobileSDK_PacketBuffer + 194);
    // LD_A_H;
    // LD_addr_A(wMobileSDK_PacketBuffer + 195);
    // LD_B(0x12);
    b = 0x12;
    // LD_HL(wMobileSDK_PacketBuffer + 80);
    hl2 = wram->wMobileSDK_PacketBuffer + 80;
    // LD_DE(wMobileSDK_PacketBuffer + 32);
    uint8_t* de2 = wram->wMobileSDK_PacketBuffer + 32;

    do {
    // asm_11382d:
        // LD_A(0x40);
        // AND_A_hl;
        // RLCA;
        // LD_C_A;
        uint8_t c = ((*hl2 & 0x40) << 1);
        // LD_A_hli;
        uint8_t a = *(hl2++);
        // BIT_A(4);
        // IF_Z goto asm_113839;
        if(bit_test(a, 4)) {
            // SET_C(6);
            bit_set(c, 6);
        }

    // asm_113839:
        // BIT_A(2);
        // IF_Z goto asm_11383f;
        if(bit_test(a, 2)) {
            // SET_C(5);
            bit_set(c, 5);
        }

    // asm_11383f:
        // BIT_A(0);
        // IF_Z goto asm_113845;
        if(bit_test(a, 0)) {
            // SET_C(4);
            bit_set(c, 4);
        }

    // asm_113845:
        // LD_A_hli;
        a = *(hl2++);
        // BIT_A(6);
        // IF_Z goto asm_11384c;
        if(bit_test(a, 6)) {
            // SET_C(3);
            bit_set(c, 3);
        }

    // asm_11384c:
        // BIT_A(4);
        // IF_Z goto asm_113852;
        if(bit_test(a, 4)) {
            // SET_C(2);
            bit_set(c, 2);
        }

    // asm_113852:
        // BIT_A(2);
        // IF_Z goto asm_113858;
        if(bit_test(a, 2)) {
            // SET_C(1);
            bit_set(c, 1);
        }

    // asm_113858:
        // BIT_A(0);
        // IF_Z goto asm_11385e;
        if(bit_test(a, 0)) {
            // SET_C(0);
            bit_set(c, 0);
        }

    // asm_11385e:
        // LD_A_C;
        // LD_de_A;
        // INC_DE;
        *(de2++) = c;
        // DEC_B;
        // IF_NZ goto asm_11382d;
    } while(--b != 0);
    // LD_B(0x12);
    b = 0x12;
    // LD_HL(wMobileSDK_PacketBuffer + 115);
    hl2 = wram->wMobileSDK_PacketBuffer + 115;
    // LD_DE(wMobileSDK_PacketBuffer + 67);
    de2 = wram->wMobileSDK_PacketBuffer + 67;

    do {
    // asm_11386c:
        // LD_A(0x2);
        // AND_A_hl;
        // RRCA;
        // LD_C_A;
        uint8_t c = ((*hl2 & 0x2) >> 1);
        // LD_A_hld;
        uint8_t a = *(hl2--);
        // BIT_A(3);
        // IF_Z goto asm_113878;
        if(bit_test(a, 3)) {
            // SET_C(1);
            bit_set(c, 1);
        }

    // asm_113878:
        // BIT_A(5);
        // IF_Z goto asm_11387e;
        if(bit_test(a, 5)) {
            // SET_C(2);
            bit_set(c, 2);
        }

    // asm_11387e:
        // BIT_A(7);
        // IF_Z goto asm_113884;
        if(bit_test(a, 7)) {
            // SET_C(3);
            bit_set(c, 3);
        }

    // asm_113884:
        // LD_A_hld;
        a = *(hl2--);
        // BIT_A(1);
        // IF_Z goto asm_11388b;
        if(bit_test(a, 1)) {
            // SET_C(4);
            bit_set(c, 4);
        }

    // asm_11388b:
        // BIT_A(3);
        // IF_Z goto asm_113891;
        if(bit_test(a, 3)) {
            // SET_C(5);
            bit_set(c, 5);
        }

    // asm_113891:
        // BIT_A(5);
        // IF_Z goto asm_113897;
        if(bit_test(a, 5)) {
            // SET_C(6);
            bit_set(c, 6);
        }

    // asm_113897:
        // BIT_A(7);
        // IF_Z goto asm_11389d;
        if(bit_test(a, 7)) {
            // SET_C(7);
            bit_set(c, 7);
        }

    // asm_11389d:
        // LD_A_C;
        // LD_de_A;
        // DEC_DE;
        *(de2--) = c;
        // DEC_B;
        // IF_NZ goto asm_11386c;
    } while(--b != 0);
    // LD_B(0x10);
    // LD_DE(wMobileSDK_PacketBuffer + 80);
    // LD_HL(wMobileSDK_PacketBuffer + 160);
    // CALL(aMobileSDK_CopyBytes);
    de2 = MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 80, wram->wMobileSDK_PacketBuffer + 160, 0x10);
    // LD_BC(0x0010);
    bc = 0x10;
    // LD_HL(wc97f);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aMobileSDK_CopyString);
    de2 = (uint8_t*)MobileSDK_CopyString((char*)de2, (char*)gMobile_wc97f_wc980, &bc);
    // LD_A(0x24);
    // SUB_A_C;
    // LD_B_A;
    b = 0x24 - LOW(bc);
    // LD_L_E;
    // LD_H_D;
    hl2 = de2;
    // LD_A(0xff);

    do {
    // asm_1138c2:
        // LD_hli_A;
        *(de2++) = 0xff;
        // DEC_B;
        // IF_NZ goto asm_1138c2;
    } while(--b != 0);
    // XOR_A_A;
    // LD_hl_A;
    *de2 = 0;
    // LD_B(0x24);
    b = 0x24;
    // LD_HL(wMobileSDK_PacketBuffer + 32);
    hl2 = wram->wMobileSDK_PacketBuffer + 32;
    // LD_DE(wMobileSDK_PacketBuffer + 80);
    de2 = wram->wMobileSDK_PacketBuffer + 80;

    do {
    // asm_1138d0:
        // LD_A_de;
        // INC_DE;
        // XOR_A_hl;
        uint8_t a = *de2 ^ *hl2;
        // LD_C(0x0);
        uint8_t c = 0x0;
        // BIT_A(0);
        // IF_Z goto asm_1138db;
        if(bit_test(a, 0)) {
            // SET_C(3);
            bit_set(c, 3);
        }

    // asm_1138db:
        // BIT_A(3);
        // IF_Z goto asm_1138e1;
        if(bit_test(a, 3)) {
            // SET_C(6);
            bit_set(c, 6);
        }

    // asm_1138e1:
        // BIT_A(6);
        // IF_Z goto asm_1138e7;
        if(bit_test(a, 6)) {
            // SET_C(0);
            bit_set(c, 0);
        }

    // asm_1138e7:
        // AND_A(0xb6);
        // OR_A_C;
        // LD_hli_A;
        *hl2 = (a & 0xb6) | c;
        hl2++, de2++;
        // DEC_B;
        // IF_NZ goto asm_1138d0;
    } while(--b != 0);
    // LD_HL(wMobileSDK_PacketBuffer + 194);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // LD_HL(wMobileSDK_PacketBuffer + 32);
    // LD_BC(0x0024);
    // CALL(aFunction113c8e);
    hl2 = Function113c8e(de_saved, wram->wMobileSDK_PacketBuffer + 32, 0x0024);
    // LD_A(0x22);
    // LD_hli_A;
    *(hl2++) = '"';
    // LD_A(0xd);
    // LD_hli_A;
    *(hl2++) = '\r';
    // LD_A(0xa);
    // LD_hli_A;
    *(hl2++) = '\n';
    // XOR_A_A;
    // LD_hl_A;
    *hl2 = 0;
    // RET;
}

void Function113909(uint8_t a, uint8_t c){
    // CALL(aFunction11391e);
    Function11391e(a);
    // LD_A_C;
    // AND_A(0xf0);
    // SWAP_A;
    a = (c >> 4) & 0xf;
    switch(a) {
        // OR_A_A;
        // JR_Z (mFunction11392f);
        case 0: 
            return Function11392f();
        // DEC_A;
        // JR_Z (mFunction113973);
        case 1: 
            return Function113973();
        // DEC_A;
        // JP_Z (mFunction1139b7);
        case 2: 
            return Function1139b7();
        // JP(mFunction1139de);
        default: 
            return Function1139de();
    }
}

void Function11391e(uint8_t a){
    // AND_A(0xf);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mUnknown_113b70);
    // ADD_HL_DE;
    // LD_DE(wMobileSDK_PacketBuffer + 176);
    // LD_B(0x8);
    // JP(mMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 176, &Unknown_113b70[(a & 0xf) / 2], 0x8);
}

void Function11392f(void){
    // LD_HL(wMobileSDK_PacketBuffer + 178);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[178] | (wram->wMobileSDK_PacketBuffer[179] << 8));
    // LD_DE(wMobileSDK_PacketBuffer + 184);
    // LD_B(0x4);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 184, hl, 0x4);
    // LD_HL(wMobileSDK_PacketBuffer + 180);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    uint8_t* de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[180] | (wram->wMobileSDK_PacketBuffer[181] << 8));
    // LD_HL(wMobileSDK_PacketBuffer + 184);
    // CALL(aFunction113a0b);
    Function113a0b(wram->wMobileSDK_PacketBuffer + 184, de);
    // LD_HL(wMobileSDK_PacketBuffer + 178);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    hl = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[178] | (wram->wMobileSDK_PacketBuffer[179] << 8));
    // LD_DE(wMobileSDK_PacketBuffer + 188);
    // LD_B(0x4);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 188, hl, 0x4);
    // LD_HL(wMobileSDK_PacketBuffer + 188);
    // CALL(aFunction113a1f);
    Function113a1f(wram->wMobileSDK_PacketBuffer + 188);
    // LD_HL(wMobileSDK_PacketBuffer + 182);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[182] | (wram->wMobileSDK_PacketBuffer[183] << 8));
    // LD_HL(wMobileSDK_PacketBuffer + 188);
    // CALL(aFunction113a0b);
    Function113a0b(wram->wMobileSDK_PacketBuffer + 188, de);
    // LD_HL(wMobileSDK_PacketBuffer + 184);
    // LD_DE(wMobileSDK_PacketBuffer + 188);
    // CALL(aFunction113a15);
    Function113a15(wram->wMobileSDK_PacketBuffer + 184, wram->wMobileSDK_PacketBuffer + 188);
    // RET;
}

void Function113973(void){
    // LD_HL(wMobileSDK_PacketBuffer + 178);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[178] | (wram->wMobileSDK_PacketBuffer[179] << 8));
    // LD_DE(wMobileSDK_PacketBuffer + 184);
    // LD_B(0x4);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 184, hl, 0x4);
    // LD_HL(wMobileSDK_PacketBuffer + 182);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    uint8_t* de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[182] | (wram->wMobileSDK_PacketBuffer[183] << 8));
    // LD_HL(wMobileSDK_PacketBuffer + 184);
    // CALL(aFunction113a0b);
    Function113a0b(wram->wMobileSDK_PacketBuffer + 184, de);
    // LD_HL(wMobileSDK_PacketBuffer + 182);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    hl = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[182] | (wram->wMobileSDK_PacketBuffer[183] << 8));
    // LD_DE(wMobileSDK_PacketBuffer + 188);
    // LD_B(0x4);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 188, hl, 0x4);
    // LD_HL(wMobileSDK_PacketBuffer + 188);
    // CALL(aFunction113a1f);
    Function113a1f(wram->wMobileSDK_PacketBuffer + 188);
    // LD_HL(wMobileSDK_PacketBuffer + 180);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[180] | (wram->wMobileSDK_PacketBuffer[181] << 8));
    // LD_HL(wMobileSDK_PacketBuffer + 188);
    // CALL(aFunction113a0b);
    Function113a0b(wram->wMobileSDK_PacketBuffer + 188, de);
    // LD_HL(wMobileSDK_PacketBuffer + 184);
    // LD_DE(wMobileSDK_PacketBuffer + 188);
    // CALL(aFunction113a15);
    Function113a15(wram->wMobileSDK_PacketBuffer + 184, wram->wMobileSDK_PacketBuffer + 188);
    // RET;
}

void Function1139b7(void){
    // LD_HL(wMobileSDK_PacketBuffer + 178);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[178] | (wram->wMobileSDK_PacketBuffer[179] << 8));
    // LD_DE(wMobileSDK_PacketBuffer + 184);
    // LD_B(0x4);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 184, hl, 0x4);
    // LD_HL(wMobileSDK_PacketBuffer + 180);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    uint8_t* de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[180] | (wram->wMobileSDK_PacketBuffer[181] << 8));
    // LD_HL(wMobileSDK_PacketBuffer + 184);
    // CALL(aFunction113a28);
    Function113a28(wram->wMobileSDK_PacketBuffer + 184, de);
    // LD_HL(wMobileSDK_PacketBuffer + 182);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[182] | (wram->wMobileSDK_PacketBuffer[183] << 8));
    // LD_HL(wMobileSDK_PacketBuffer + 184);
    // CALL(aFunction113a28);
    Function113a28(wram->wMobileSDK_PacketBuffer + 184, de);
    // RET;
}

void Function1139de(void){
    // LD_HL(wMobileSDK_PacketBuffer + 182);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    uint8_t* hl = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[182] | (wram->wMobileSDK_PacketBuffer[183] << 8));
    // LD_DE(wMobileSDK_PacketBuffer + 184);
    // LD_B(0x4);
    // CALL(aMobileSDK_CopyBytes);
    MobileSDK_CopyBytes(wram->wMobileSDK_PacketBuffer + 184, hl, 0x4);
    // LD_HL(wMobileSDK_PacketBuffer + 184);
    // CALL(aFunction113a1f);
    Function113a1f(wram->wMobileSDK_PacketBuffer + 184);
    // LD_HL(wMobileSDK_PacketBuffer + 178);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    uint8_t* de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[178] | (wram->wMobileSDK_PacketBuffer[179] << 8));
    // LD_HL(wMobileSDK_PacketBuffer + 184);
    // CALL(aFunction113a15);
    Function113a15(wram->wMobileSDK_PacketBuffer + 184, de);
    // LD_HL(wMobileSDK_PacketBuffer + 180);
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    de = wram->wMobileSDK_PacketBuffer + (wram->wMobileSDK_PacketBuffer[180] | (wram->wMobileSDK_PacketBuffer[181] << 8));
    // LD_HL(wMobileSDK_PacketBuffer + 184);
    // CALL(aFunction113a28);
    Function113a28(wram->wMobileSDK_PacketBuffer + 184, de);
    // RET;
}

void Function113a0b(uint8_t* hl, const uint8_t* de){
    // LD_B(0x4);
    uint8_t b = 0x4;

    do {
    // asm_113a0d:
        // LD_A_de;
        // INC_DE;
        // AND_A_hl;
        // LD_hli_A;
        *(hl++) &= *(de++);
        // DEC_B;
        // IF_NZ goto asm_113a0d;
    } while(--b != 0);
    // RET;
}

void Function113a15(uint8_t* hl, const uint8_t* de){
    // LD_B(0x4);
    uint8_t b = 0x4;

    do {
    // asm_113a17:
        // LD_A_de;
        // INC_DE;
        // OR_A_hl;
        // LD_hli_A;
        *(hl++) |= *(de++);
        // DEC_B;
        // IF_NZ goto asm_113a17;
    } while(--b != 0);
    // RET;
}

void Function113a1f(uint8_t* hl){
    // LD_B(0x4);
    uint8_t b = 0x4;

    do {
    // asm_113a21:
        // LD_A_hl;
        // CPL;
        // LD_hli_A;
        *hl = (*hl ^ 0xff);
        hl++;
        // DEC_B;
        // IF_NZ goto asm_113a21;
    } while(--b != 0);
    // RET;
}

void Function113a28(uint8_t* hl, const uint8_t* de){
    // LD_B(0x4);
    uint8_t b = 0x4;

    do {
    // asm_113a2a:
        // LD_A_de;
        // INC_DE;
        // XOR_A_hl;
        // LD_hli_A;
        *(hl++) ^= *(de++);
        // DEC_B;
        // IF_NZ goto asm_113a2a;
    } while(--b != 0);
    // RET;
}

void Function113a32(uint8_t* hl, const uint8_t* de){
    uint8_t cy = 0;
    // LD_A_de;
    // INC_DE;
    // ADD_A_hl;
    // LD_hli_A;
    // LD_B(0x3);

    for(uint8_t b = 0x4; b != 0; --b) {
    // asm_113a38:
        // LD_A_de;
        // INC_DE;
        // ADC_A_hl;
        // LD_hli_A;
        *hl = AddCarry8(*hl, *de, cy, &cy);
        hl++, de++;
        // DEC_B;
        // IF_NZ goto asm_113a38;
    }
    // RET;
}

void Function113a40(uint32_t* hl, uint8_t b){
    do {
    // asm_113a40:
        // OR_A_A;
        // PUSH_HL;
        // LD_A_hli;
        // RLA;
        // LD_A_hl;
        // RLA;
        // LD_hli_A;
        // LD_A_hl;
        // RLA;
        // LD_hli_A;
        // LD_A_hl;
        // RLA;
        // LD_hl_A;
        // POP_HL;
        // LD_A_hl;
        // RLA;
        // LD_hl_A;
        // DEC_B;
        *hl = (*hl << 1) | (*hl >> 31);
        // IF_NZ goto asm_113a40;
    } while(--b != 0);
    // RET;
}

const char Unknown_113a55[] = "Authorization: GB00 name=\""; //db ['"Authorization: GB00 name="', '0x22', '0'];

const uint8_t Unknown_113a70[] = {
    0x00, 0x00, 0x00, 0x07, 0x06, 0x04, 0x00, 0x0c, 0x04, 0x08, 0x00, 0x11, 0x02, 0x0c, 0x00, 0x16,
    0x00, 0x10, 0x00, 0x07, 0x06, 0x14, 0x00, 0x0c, 0x04, 0x18, 0x00, 0x11, 0x02, 0x1c, 0x00, 0x16,
    0x00, 0x20, 0x00, 0x07, 0x06, 0x24, 0x00, 0x0c, 0x04, 0x28, 0x00, 0x11, 0x02, 0x2c, 0x00, 0x16,
    0x00, 0x30, 0x00, 0x07, 0x06, 0x34, 0x00, 0x0c, 0x04, 0x38, 0x00, 0x11, 0x02, 0x3c, 0x00, 0x16,
    0x10, 0x04, 0x00, 0x05, 0x16, 0x18, 0x00, 0x09, 0x14, 0x2c, 0x00, 0x0e, 0x12, 0x00, 0x00, 0x14,
    0x10, 0x14, 0x00, 0x05, 0x16, 0x28, 0x00, 0x09, 0x14, 0x3c, 0x00, 0x0e, 0x12, 0x10, 0x00, 0x14,
    0x10, 0x24, 0x00, 0x05, 0x16, 0x38, 0x00, 0x09, 0x14, 0x0c, 0x00, 0x0e, 0x12, 0x20, 0x00, 0x14,
    0x10, 0x34, 0x00, 0x05, 0x16, 0x08, 0x00, 0x09, 0x14, 0x1c, 0x00, 0x0e, 0x12, 0x30, 0x00, 0x14,
    0x20, 0x14, 0x00, 0x04, 0x26, 0x20, 0x00, 0x0b, 0x24, 0x2c, 0x00, 0x10, 0x22, 0x38, 0x00, 0x17,
    0x20, 0x04, 0x00, 0x04, 0x26, 0x10, 0x00, 0x0b, 0x24, 0x1c, 0x00, 0x10, 0x22, 0x28, 0x00, 0x17,
    0x20, 0x34, 0x00, 0x04, 0x26, 0x00, 0x00, 0x0b, 0x24, 0x0c, 0x00, 0x10, 0x22, 0x18, 0x00, 0x17,
    0x20, 0x24, 0x00, 0x04, 0x26, 0x30, 0x00, 0x0b, 0x24, 0x3c, 0x00, 0x10, 0x22, 0x08, 0x00, 0x17,
    0x30, 0x00, 0x00, 0x06, 0x36, 0x1c, 0x00, 0x0a, 0x34, 0x38, 0x00, 0x0f, 0x32, 0x14, 0x00, 0x15,
    0x30, 0x30, 0x00, 0x06, 0x36, 0x0c, 0x00, 0x0a, 0x34, 0x28, 0x00, 0x0f, 0x32, 0x04, 0x00, 0x15,
    0x30, 0x20, 0x00, 0x06, 0x36, 0x3c, 0x00, 0x0a, 0x34, 0x18, 0x00, 0x0f, 0x32, 0x34, 0x00, 0x15,
    0x30, 0x10, 0x00, 0x06, 0x36, 0x2c, 0x00, 0x0a, 0x34, 0x08, 0x00, 0x0f, 0x32, 0x24, 0x00, 0x15,
};

const uint16_t Unknown_113b70[] =  {
    160, // wMobileSDK_PacketBuffer + 160
    164, // wMobileSDK_PacketBuffer + 164
    168, // wMobileSDK_PacketBuffer + 168
    172, // wMobileSDK_PacketBuffer + 172
    160, // wMobileSDK_PacketBuffer + 160
    164, // wMobileSDK_PacketBuffer + 164
    168, // wMobileSDK_PacketBuffer + 168
};

const uint8_t Unknown_113b7e[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10,
};

const uint32_t MD5_K_Table[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

uint8_t* Function113c8e(uint8_t* de, const uint8_t* hl, uint16_t bc){
    // LD_A_C;
    // LD_addr_A(wMobileSDK_PacketBuffer + 201);
    // LD_A_B;
    // LD_addr_A(wMobileSDK_PacketBuffer + 202);
    // LD_C_E;
    // LD_B_D;
    // LD_E_L;
    // LD_D_H;
    const uint8_t* de2 = hl;
    // LD_L_C;
    // LD_H_B;
    uint8_t* hl2 = de;
    // XOR_A_A;
    // LD_addr_A(wMobileSDK_PacketBuffer + 207);
    wram->wMobileSDK_PacketBuffer[207] = 0;

    do {
    // asm_113ca0:
        // LD_B(0x3);
        uint8_t b = 0x3;
        // PUSH_HL;
        // LD_HL(wMobileSDK_PacketBuffer + 203);
        uint8_t* hl3 = wram->wMobileSDK_PacketBuffer + 203;

        do {
        // asm_113ca6:
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            *(hl3++) = *(de2++);
            // DEC_B;
            // IF_NZ goto asm_113ca6;
        } while(--b != 0);
        // LD_A_addr(wMobileSDK_PacketBuffer + 201);
        // LD_C_A;
        // LD_A_addr(wMobileSDK_PacketBuffer + 202);
        // LD_B_A;
        // XOR_A_A;
        // OR_A_B;
        // IF_NZ goto asm_113ccf;
        // LD_A(0x2);
        // CP_A_C;
        // IF_C goto asm_113ccf;
        if(bc <= 0x2) {
            // PUSH_HL;
            // DEC_HL;
            uint8_t* hl4 = hl3 - 1;
            // LD_A_C;
            // LD_addr_A(wMobileSDK_PacketBuffer + 207);
            wram->wMobileSDK_PacketBuffer[207] = LOW(bc);
            uint8_t c = LOW(bc);

            do {
            // asm_113cc3:
                // XOR_A_A;
                // LD_hld_A;
                *(hl4--) = 0;
                // INC_C;
                c++;
                // LD_A(0x3);
                // CP_A_C;
                // IF_NZ goto asm_113cc3;
            } while(c != 0x3);
            // POP_HL;
            // LD_BC(0x0003);
            bc = 0x3;
        }

    // asm_113ccf:
        // DEC_BC;
        // DEC_BC;
        // DEC_BC;
        bc -= 3;
        // LD_A_C;
        // LD_addr_A(wMobileSDK_PacketBuffer + 201);
        // LD_A_B;
        // LD_addr_A(wMobileSDK_PacketBuffer + 202);
        // PUSH_DE;
        // DEC_HL;
        --hl3;
        // LD_C_hl;
        uint8_t c = *hl3;
        // DEC_HL;
        --hl3;
        // LD_B_hl;
        b = *hl3;
        // DEC_HL;
        --hl3;
        // LD_A_hl;
        // LD_D_A;
        uint8_t d = *hl3;
        // SRL_A;
        // SRL_A;
        // LD_hli_A;
        *(hl3++) = d >> 2;
        // LD_A(0x3);
        // AND_A_D;
        // LD_D_A;
        // LD_A(0xf0);
        // AND_A_B;
        // OR_A_D;
        uint8_t a = (d & 0x3) | (b & 0xf0);
        // SWAP_A;
        // LD_hli_A;
        *(hl3++) = (a << 4) | (a >> 4);
        // LD_A(0xf);
        // AND_A_B;
        // LD_D_A;
        // LD_A_C;
        // AND_A(0xc0);
        // OR_A_D;
        a = (b & 0xf) | (c & 0xc0);
        // RLCA;
        // RLCA;
        // LD_hli_A;
        *(hl3++) = (a << 2) | (a >> 6);
        // LD_A(0x3f);
        // AND_A_C;
        // LD_hld_A;
        *(hl3--) = c & 0x3f;
        // DEC_HL;
        // DEC_HL;
        hl3 -= 2;
        // POP_DE;
        // LD_B_H;
        // LD_C_L;
        uint8_t* bc2 = hl3;
        // POP_HL;
        // LD_A_bc;
        // INC_BC;
        // CALL(aFunction113d47);
        // LD_hli_A;
        *(hl2++) = Function113d47(*(bc2++));
        // LD_A_bc;
        // INC_BC;
        // CALL(aFunction113d47);
        // LD_hli_A;
        *(hl2++) = Function113d47(*(bc2++));
        // LD_A_bc;
        // INC_BC;
        // CALL(aFunction113d47);
        // LD_hli_A;
        *(hl2++) = Function113d47(*(bc2++));
        // LD_A_bc;
        // INC_BC;
        // CALL(aFunction113d47);
        // LD_hli_A;
        *(hl2++) = Function113d47(*(bc2++));
        // LD_A_addr(wMobileSDK_PacketBuffer + 201);
        // CP_A(0x0);
        // JP_NZ (mFunction113c8e_asm_113ca0);
        // LD_A_addr(wMobileSDK_PacketBuffer + 202);
        // CP_A(0x0);
        // JP_NZ (mFunction113c8e_asm_113ca0);
    } while(bc != 0);
    // LD_A_addr(wMobileSDK_PacketBuffer + 207);
    // CP_A(0x0);
    // IF_Z goto asm_113d43;
    if(wram->wMobileSDK_PacketBuffer[207] != 0) {
        // PUSH_HL;
        // DEC_HL;
        uint8_t* hl3 = hl2 - 1;
        // LD_B_A;
        uint8_t b = wram->wMobileSDK_PacketBuffer[207];

        do {
        // asm_113d39:
            // LD_A(0x3d);
            // LD_hld_A;
            *(hl3--) = 0x3d;
            // INC_B;
            // LD_A(0x3);
            // CP_A_B;
            // IF_NZ goto asm_113d39;
        } while(++b != 0x3);
        // POP_HL;
    }

// asm_113d43:
    // LD_A(0x0);
    // LD_hl_A;
    *hl2 = 0;
    // RET;
    return hl2;
}

uint8_t Function113d47(uint8_t a){
    // CP_A(0x1a);
    // IF_C goto asm_113d5a;
    if(a < 0x1a)
        return a + 0x41;
    // CP_A(0x34);
    // IF_C goto asm_113d5d;
    if(a < 0x34)
        return a + 0x47;
    // CP_A(0x3e);
    // IF_C goto asm_113d60;
    if(a < 0x3e)
        return a - 0x4;
    // CP_A(0x3e);
    // IF_Z goto asm_113d63;
    if(a == 0x3e)
        return 0x2b;
    // LD_A(0x2f);
    // RET;
    return 0x2f;

// asm_113d5a:
    // ADD_A(0x41);
    // RET;

// asm_113d5d:
    // ADD_A(0x47);
    // RET;

// asm_113d60:
    // SUB_A(0x4);
    // RET;

// asm_113d63:
    // LD_A(0x2b);
    // RET;
}

static u8_flag_s asm_113e26(void) {
    // LD_HL(wc821);
    // SET_hl(1);
    bit_set(wram->wc821, 1);
    // LD_A(0x20);
    // LD_addr_A(wc80f);
    wram->wc80f = 0x20;
    // RET;
    return u8_flag(0x20, true);
}

u8_flag_s Function113dfa(uint8_t a){
    // CP_A(0x2b);
    // IF_C goto asm_113e24;
    if(a < 0x2b)
        return asm_113e26();
    // IF_Z goto asm_113e31;
    if(a == 0x2b)
        return u8_flag(0x3e, false);
    // CP_A(0x2f);
    // IF_C goto asm_113e24;
    if(a < 0x2f)
        return asm_113e26();
    // IF_Z goto asm_113e34;
    if(a == 0x2f)
        return u8_flag(0x3f, false);
    // CP_A(0x30);
    // IF_C goto asm_113e24;
    if(a < 0x30)
        return asm_113e26();
    // CP_A(0x3a);
    // IF_C goto asm_113e37;
    if(a < 0x3a) // 0-9
        return u8_flag(a + 0x4, false);
    // CP_A(0x3d);
    // IF_C goto asm_113e24;
    if(a < 0x3d)
        return asm_113e26();
    // IF_Z goto asm_113e3a;
    if(a == 0x3d)
        return u8_flag(0x0, false);
    // CP_A(0x41);
    // IF_C goto asm_113e24;
    if(a < 0x41)
        return asm_113e26();
    // CP_A(0x5b);
    // IF_C goto asm_113e3c;
    if(a < 0x5b) // A-Z
        return u8_flag(a - 0x41, false);
    // CP_A(0x61);
    // IF_C goto asm_113e24;
    if(a < 0x61)
        return asm_113e26();
    // CP_A(0x7b);
    // IF_C goto asm_113e3f;
    if(a < 0x7b) // a-z
        return u8_flag(a - 0x47, false);

    return asm_113e26();


// asm_113e24:
    // POP_HL;
    // POP_HL;

// asm_113e26:
    // LD_HL(wc821);
    // SET_hl(1);
    // LD_A(0x20);
    // LD_addr_A(wc80f);
    // RET;

// asm_113e31:
    // LD_A(0x3e);
    // RET;

// asm_113e34:
    // LD_A(0x3f);
    // RET;

// asm_113e37:
    // ADD_A(0x4);
    // RET;

// asm_113e3a:
    // XOR_A_A;
    // RET;

// asm_113e3c:
    // SUB_A(0x41);
    // RET;

// asm_113e3f:
    // SUB_A(0x47);
    // RET;
}

void Function113d66(uint8_t* de, const uint8_t* hl, uint16_t bc){
    // LD_A_C;
    // LD_addr_A(wMobileSDK_PacketBuffer + 201);
    // LD_A_B;
    // LD_addr_A(wMobileSDK_PacketBuffer + 202);
    // LD_C_E;
    // LD_B_D;
    // LD_E_L;
    // LD_D_H;
    const uint8_t* de2 = hl;
    // LD_L_C;
    // LD_H_B;
    uint8_t* hl2 = de;

    do {
    // asm_113d74:
        // LD_A_addr(wMobileSDK_PacketBuffer + 202);
        // OR_A_A;
        // IF_NZ goto asm_113d82;
        // LD_A_addr(wMobileSDK_PacketBuffer + 201);
        // CP_A(0x4);
        // JP_C (mFunction113d66_asm_113e26);
        if(bc < 0x4) {
            asm_113e26();
            return;
        }

    // asm_113d82:
        // LD_B(0x4);
        uint8_t b = 0x4;
        // PUSH_HL;
        // LD_HL(wMobileSDK_PacketBuffer + 203);
        uint8_t* hl3 = wram->wMobileSDK_PacketBuffer + 203;

        do {
        // asm_113d88:
            // LD_A_de;
            // INC_DE;
            // CALL(aFunction113d66_Function113dfa);
            u8_flag_s res = Function113dfa(*(de2++));
            if(res.flag)
                return;
            // LD_hli_A;
            *(hl3++) = res.a;
            // DEC_B;
            // IF_NZ goto asm_113d88;
        } while(--b != 0);
        // LD_A_addr(wMobileSDK_PacketBuffer + 201);
        // LD_C_A;
        // LD_A_addr(wMobileSDK_PacketBuffer + 202);
        // LD_B_A;
        // for(int rept = 0; rept < 4; rept++){
        // DEC_BC;
        // }
        bc -= 4;
        // LD_A_B;
        // OR_A_C;
        // IF_Z goto asm_113dae;
        if(bc != 0) {
            while(*de2 == '\r' || *de2 == '\n') {
            // asm_113da1:
                // LD_A_de;
                // CP_A(0xd);
                // IF_Z goto asm_113daa;
                // CP_A(0xa);
                // IF_NZ goto asm_113dae;
            // asm_113daa:
                // INC_DE;
                de2++;
                // DEC_BC;
                --bc;
                // goto asm_113da1;
            }
        }

    // asm_113dae:
        // LD_A_C;
        // LD_addr_A(wMobileSDK_PacketBuffer + 201);
        // LD_A_B;
        // LD_addr_A(wMobileSDK_PacketBuffer + 202);
        // PUSH_DE;
        // DEC_HL;
        --hl3;
        // LD_D_hl;
        // uint8_t d = *hl3;
        // DEC_HL;
        --hl3;
        // LD_C_hl;
        uint8_t c = *hl3;
        // DEC_HL;
        --hl3;
        // LD_B_hl;
        b = *hl3;
        // DEC_HL;
        --hl3;
        // LD_A_hl;
        uint8_t a = *hl3;
        // SLA_B;
        // SLA_B;
        // SLA_B;
        // RLA;
        // SLA_B;
        // RLA;
        uint16_t ab = ((a << 8) | LOW(b << 2)) << 2;
        // LD_hli_A;
        *(hl3++) = HIGH(ab);
        // LD_hl_B;
        // INC_HL;
        *(hl3++) = LOW(ab);
        // RRC_C;
        // RRC_C;
        c = (c << 6) | (c >> 2);
        // LD_hl_C;
        *hl3 = c;
        // DEC_HL;
        --hl3;
        // LD_A(0xf);
        // AND_A_C;
        // OR_A_hl;
        // LD_hli_A;
        *hl3 |= (0xf & c);
        hl3++;
        // LD_A_hli;
        a = *(hl3++);
        // AND_A(0xc0);
        // OR_A_hl;
        a = (a & 0xc0) | *hl3;
        // DEC_HL;
        --hl3;
        // LD_hld_A;
        *(hl3--) = a;
        // DEC_HL;
        --hl3;
        // POP_DE;
        // LD_B_H;
        // LD_C_L;
        uint8_t* bc2 = hl3;
        // POP_HL;
        // LD_A_bc;
        // LD_hli_A;
        // INC_BC;
        *(hl2++) = *(bc2++);
        // LD_A_bc;
        // LD_hli_A;
        // INC_BC;
        *(hl2++) = *(bc2++);
        // LD_A_bc;
        // LD_hli_A;
        *(hl2++) = *bc2;
        // LD_A_addr(wMobileSDK_PacketBuffer + 201);
        // OR_A_A;
        // IF_NZ goto asm_113d74;
        // LD_A_addr(wMobileSDK_PacketBuffer + 202);
        // OR_A_A;
        // JP_NZ (mFunction113d66_asm_113d74);
    } while(bc != 0);
    // XOR_A_A;
    // LD_hl_A;
    *hl2 = 0;
    // RET;
    return;
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

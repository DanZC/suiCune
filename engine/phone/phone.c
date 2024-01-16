#include "../../constants.h"
#include "phone.h"
#include "phonering_copytilemapatonce.h"
#include "../../home/map.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/array.h"
#include "../../home/gfx.h"
#include "../../home/delay.h"
#include "../../home/text.h"
#include "../../home/random.h"
#include "../../home/math.h"
#include "../../home/map_objects.h"
#include "../overworld/scripting.h"
#include "../overworld/time.h"
#include "../overworld/landmarks.h"
#include "../events/checktime.h"
#include "../battle/read_trainer_attributes.h"
#include "../battle/read_trainer_party.h"
#include "../../util/scripting.h"
#include "../../data/text/common.h"
#include "../../data/phone/non_trainer_names.h"
#include "../../data/phone/phone_contacts.h"
#include "../../data/phone/special_calls.h"
#include "../../data/phone/permanent_numbers.h"

struct PhoneContact gCallerContact;
Script_fn_t gPhoneCaller;

void AddPhoneNumber(void){
    CALL(av_CheckCellNum);
    IF_C goto cant_add;
    CALL(aPhone_FindOpenSlot);
    IF_NC goto cant_add;
    LD_hl_C;
    XOR_A_A;
    RET;


cant_add:
    SCF;
    RET;

}

bool AddPhoneNumber_Conv(uint8_t c){
    // CALL(av_CheckCellNum);
    uint16_t hl = v_CheckCellNum_Conv(c);

    // IF_C goto cant_add;
    if(hl != 0)
    {
        return false;
    }

    // CALL(aPhone_FindOpenSlot);
    // IF_NC goto cant_add;
    hl = Phone_FindOpenSlot_Conv(c);
    if(hl == 0)
    {
        return false;
    }

    // LD_hl_C;
    gb_write(hl, c);
    
    // XOR_A_A;
    // RET;
    return true;
}

bool AddPhoneNumber_Conv2(uint8_t c){
    // CALL(av_CheckCellNum);
    uint8_t* hl = v_CheckCellNum_Conv2(c);

    // IF_C goto cant_add;
    if(hl != NULL) {
        return false;
    }

    // CALL(aPhone_FindOpenSlot);
    // IF_NC goto cant_add;
    hl = Phone_FindOpenSlot_Conv2(c);
    if(hl == NULL) {
        return false;
    }

    // LD_hl_C;
    *hl = c;
    
    // XOR_A_A;
    // RET;
    return true;
}

void DelCellNum(void){
    CALL(av_CheckCellNum);
    IF_NC goto not_in_list;
    XOR_A_A;
    LD_hl_A;
    RET;


not_in_list:
    SCF;
    RET;

}

bool DelCellNum_Conv(uint8_t c){
    // CALL(av_CheckCellNum);
    // IF_NC goto not_in_list;
    uint16_t hl = v_CheckCellNum_Conv(c);
    if(hl == 0)
    {
        return false;
    }

    // XOR_A_A;
    // LD_hl_A;
    gb_write(hl, 0);

    // RET;
    return true;
}

// Returns true (nc) if the number was successfully deleted.
bool DelCellNum_Conv2(uint8_t c){
    // CALL(av_CheckCellNum);
    // IF_NC goto not_in_list;
    uint8_t* hl = v_CheckCellNum_Conv2(c);
    if(hl == NULL) {
        return false;
    }

    // XOR_A_A;
    // LD_hl_A;
    *hl = 0;

    // RET;
    return true;
}

void CheckCellNum(void){
    JP(mv_CheckCellNum);  // useless

}

void v_CheckCellNum(void){
    LD_HL(wPhoneList);
    LD_B(CONTACT_LIST_SIZE);

loop:
    LD_A_hli;
    CP_A_C;
    IF_Z goto got_it;
    DEC_B;
    IF_NZ goto loop;
    XOR_A_A;
    RET;


got_it:
    DEC_HL;
    SCF;
    RET;

}

uint16_t v_CheckCellNum_Conv(uint8_t c){
    // LD_HL(wPhoneList);
    // LD_B(CONTACT_LIST_SIZE);
    uint16_t hl = wPhoneList;
    uint8_t b = CONTACT_LIST_SIZE;

    do {
        // LD_A_hli;
        uint8_t a = gb_read(hl++);

        // CP_A_C;
        // IF_Z goto got_it;
        if(a == c)
        {
            return hl - 1;
        }
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    return 0;
}

uint8_t* v_CheckCellNum_Conv2(uint8_t c){
    // LD_HL(wPhoneList);
    uint8_t* hl = wram->wPhoneList;
    // LD_B(CONTACT_LIST_SIZE);
    for(uint8_t b = 0; b < CONTACT_LIST_SIZE; ++b) {
    // loop:
        // LD_A_hli;
        // CP_A_C;
        // IF_Z goto got_it;
    // got_it:
        // DEC_HL;
        // SCF;
        // RET;
        if(hl[b] == c)
            return hl + b;
        // DEC_B;
        // IF_NZ goto loop;
    }
    // XOR_A_A;
    // RET;
    return NULL;
}

void Phone_FindOpenSlot(void){
    CALL(aGetRemainingSpaceInPhoneList);
    LD_B_A;
    LD_HL(wPhoneList);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto FoundOpenSpace;
    DEC_B;
    IF_NZ goto loop;
    XOR_A_A;
    RET;


FoundOpenSpace:
    DEC_HL;
    SCF;
    RET;

}

uint16_t Phone_FindOpenSlot_Conv(uint8_t c){
    // CALL(aGetRemainingSpaceInPhoneList);
    // LD_B_A;
    uint8_t b = GetRemainingSpaceInPhoneList_Conv(c);
    
    // LD_HL(wPhoneList);
    uint16_t hl = wPhoneList;

    do {
        // LD_A_hli;
        uint8_t a = gb_read(hl++);
        // AND_A_A;
        // IF_Z goto FoundOpenSpace;
        if(a == 0)
        {
            hl--;
            return hl;
        }
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    return 0;
}

uint8_t* Phone_FindOpenSlot_Conv2(uint8_t c){
    // CALL(aGetRemainingSpaceInPhoneList);
    // LD_B_A;
    uint8_t b = GetRemainingSpaceInPhoneList_Conv(c);
    
    // LD_HL(wPhoneList);
    uint8_t* hl = wram->wPhoneList;

    for(uint8_t i = 0; i < b; ++i) {
        // LD_A_hli;
        uint8_t a = hl[i];
        // AND_A_A;
        // IF_Z goto FoundOpenSpace;
        if(a == 0) {
            return hl + i;
        }
        // DEC_B;
        // IF_NZ goto loop;
    }
    return NULL;
}

void GetRemainingSpaceInPhoneList(void){
    XOR_A_A;
    LD_addr_A(wRegisteredPhoneNumbers);
    LD_HL(mPermanentNumbers);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done;
    CP_A_C;
    IF_Z goto continue_;

    PUSH_BC;
    PUSH_HL;
    LD_C_A;
    CALL(av_CheckCellNum);
    IF_C goto permanent;
    LD_HL(wRegisteredPhoneNumbers);
    INC_hl;

permanent:
    POP_HL;
    POP_BC;


continue_:
    goto loop;


done:
    LD_A(CONTACT_LIST_SIZE);
    LD_HL(wRegisteredPhoneNumbers);
    SUB_A_hl;
    RET;

// INCLUDE "data/phone/permanent_numbers.asm"

    return BrokenPlaceFarString();
}

uint8_t GetRemainingSpaceInPhoneList_Conv(uint8_t c){
    // XOR_A_A;
    // LD_addr_A(wRegisteredPhoneNumbers);
    wram->wRegisteredPhoneNumbers = 0;

    // LD_HL(mPermanentNumbers);
    uint16_t hl = mPermanentNumbers;

    while(1)
    {
        // LD_A_hli;
        uint8_t a = gb_read(hl++);

        // CP_A(-1);
        // IF_Z goto done;
        if(a == 0xff) 
            break;

        // CP_A_C;
        // IF_Z goto continue_;
        if(a == c)
            continue;

        // PUSH_BC;
        // PUSH_HL;
        // LD_C_A;
        // CALL(av_CheckCellNum);
        // IF_C goto permanent;
        if(v_CheckCellNum_Conv(c) == 0)
        {
            // LD_HL(wRegisteredPhoneNumbers);
            // INC_hl;
            gb_write(wRegisteredPhoneNumbers, gb_read(wRegisteredPhoneNumbers) + 1);
        }
    }

    // LD_A(CONTACT_LIST_SIZE);
    // LD_HL(wRegisteredPhoneNumbers);
    uint8_t t = gb_read(wRegisteredPhoneNumbers);

    // SUB_A_hl;
    uint8_t ret = (CONTACT_LIST_SIZE - t);
    return ret;
}

uint8_t GetRemainingSpaceInPhoneList_Conv2(uint8_t c){
    // XOR_A_A;
    // LD_addr_A(wRegisteredPhoneNumbers);
    wram->wRegisteredPhoneNumbers = 0;

    // LD_HL(mPermanentNumbers);
    const uint8_t* hl = PermanentNumbers;

    for(uint8_t i = 0; ; i++)
    {
        // LD_A_hli;
        uint8_t a = hl[i];

        // CP_A(-1);
        // IF_Z goto done;
        if(a == 0xff) 
            break;

        // CP_A_C;
        // IF_Z goto continue_;
        if(a == c)
            continue;

        // PUSH_BC;
        // PUSH_HL;
        // LD_C_A;
        // CALL(av_CheckCellNum);
        // IF_C goto permanent;
        if(v_CheckCellNum_Conv2(c) != NULL) {
            // LD_HL(wRegisteredPhoneNumbers);
            // INC_hl;
            wram->wRegisteredPhoneNumbers++;
        }
    }

    // LD_A(CONTACT_LIST_SIZE);
    // LD_HL(wRegisteredPhoneNumbers);

    // SUB_A_hl;
    uint8_t ret = (CONTACT_LIST_SIZE - wram->wRegisteredPhoneNumbers);
    return ret;
}

void BrokenPlaceFarString(void){
//  This routine is not in bank 0 and will fail or crash if called.
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A_B;
    RST(aBankswitch);

    CALL(aPlaceString);

    POP_AF;
    RST(aBankswitch);
    RET;

}

void CheckPhoneCall(void){
//  Check if the phone is ringing in the overworld.

    CALL(aCheckStandingOnEntrance);
    IF_Z goto no_call;

    CALL(aCheckPhoneCall_timecheck);
    NOP;
    IF_NC goto no_call;

// 50% chance for a call
    CALL(aRandom);
    LD_B_A;
    AND_A(0b01111111);
    CP_A_B;
    IF_NZ goto no_call;

    CALL(aGetMapPhoneService);
    AND_A_A;
    IF_NZ goto no_call;

    CALL(aGetAvailableCallers);
    CALL(aChooseRandomCaller);
    IF_NC goto no_call;

    LD_E_A;
    CALL(aLoadCallerScript);
    LD_A(BANK(aScript_ReceivePhoneCall));
    LD_HL(mScript_ReceivePhoneCall);
    CALL(aCallScript);
    SCF;
    RET;


no_call:
    XOR_A_A;
    RET;


timecheck:
    FARCALL(aCheckReceiveCallTimer);
    RET;

}

static bool CheckPhoneCall_timecheck(void) {
    // FARCALL(aCheckReceiveCallTimer);
    // RET;
    return CheckReceiveCallTimer_Conv();
}

//  Check if the phone is ringing in the overworld.
u8_flag_s CheckPhoneCall_Conv(void){
    // CALL(aCheckStandingOnEntrance);
    // IF_Z goto no_call;
    if(CheckStandingOnEntrance_Conv())
        return u8_flag(0, false);

    // CALL(aCheckPhoneCall_timecheck);
    // NOP;
    // IF_NC goto no_call;
    if(!CheckPhoneCall_timecheck())
        return u8_flag(0, false);

// 50% chance for a call
    // CALL(aRandom);
    // LD_B_A;
    // AND_A(0b01111111);
    // CP_A_B;
    // IF_NZ goto no_call;
    if(Random_Conv() & 0b10000000)
        return u8_flag(0, false);

    // CALL(aGetMapPhoneService);
    // AND_A_A;
    // IF_NZ goto no_call;
    if(GetMapPhoneService_Conv() != 0)
        return u8_flag(0, false);

    // CALL(aGetAvailableCallers);
    GetAvailableCallers_Conv();
    // CALL(aChooseRandomCaller);
    // IF_NC goto no_call;
    u8_flag_s res = ChooseRandomCaller_Conv();
    if(!res.flag)
        return u8_flag(0, false);

    // LD_E_A;
    // CALL(aLoadCallerScript);
    LoadCallerScript_Conv(res.a);
    // LD_A(BANK(aScript_ReceivePhoneCall));
    // LD_HL(mScript_ReceivePhoneCall);
    // CALL(aCallScript);
    uint8_t a = CallScript_Conv2(Script_ReceivePhoneCall);
    // SCF;
    // RET;
    return u8_flag(a, true);

// no_call:
    // XOR_A_A;
    // RET;
}

void CheckPhoneContactTimeOfDay(void){
    PUSH_HL;
    PUSH_BC;
    PUSH_DE;
    PUSH_AF;

    FARCALL(aCheckTime);
    POP_AF;
    AND_A(ANYTIME);
    AND_A_C;

    POP_DE;
    POP_BC;
    POP_HL;
    RET;

}

bool CheckPhoneContactTimeOfDay_Conv(uint8_t a){
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_AF;

    // FARCALL(aCheckTime);
    uint8_t curTime = CheckTime_Conv().a;
    // POP_AF;
    // AND_A(ANYTIME);
    // AND_A_C;

    // POP_DE;
    // POP_BC;
    // POP_HL;
    // RET;
    return ((a & (ANYTIME)) & curTime) != 0;
}

void ChooseRandomCaller(void){
//  If no one is available to call, don't return anything.
    LD_A_addr(wNumAvailableCallers);
    AND_A_A;
    IF_Z goto NothingToSample;

//  Store the number of available callers in c.
    LD_C_A;
//  Sample a random number between 0 and 31.
    CALL(aRandom);
    LDH_A_addr(hRandomAdd);
    SWAP_A;
    AND_A(0x1f);
//  Compute that number modulo the number of available callers.
    CALL(aSimpleDivide);
//  Return the caller ID you just sampled.
    LD_C_A;
    LD_B(0);
    LD_HL(wAvailableCallers);
    ADD_HL_BC;
    LD_A_hl;
    SCF;
    RET;


NothingToSample:
    XOR_A_A;
    RET;

}

u8_flag_s ChooseRandomCaller_Conv(void){
//  If no one is available to call, don't return anything.
    // LD_A_addr(wNumAvailableCallers);
    // AND_A_A;
    // IF_Z goto NothingToSample;
    if(wram->wNumAvailableCallers == 0)
        return u8_flag(0, false);

//  Store the number of available callers in c.
    // LD_C_A;
    uint8_t c = wram->wNumAvailableCallers;
//  Sample a random number between 0 and 31.
    // CALL(aRandom);
    Random_Conv();
    // LDH_A_addr(hRandomAdd);
    // SWAP_A;
    // AND_A(0x1f);
    uint8_t a = ((hram->hRandomAdd >> 4) | (hram->hRandomAdd << 4)) & 0x1f;
//  Compute that number modulo the number of available callers.
    // CALL(aSimpleDivide);
    uint8_t rem = SimpleDivide_Conv(a, c).rem;
//  Return the caller ID you just sampled.
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wAvailableCallers);
    // ADD_HL_BC;
    // LD_A_hl;
    // SCF;
    // RET;
    return u8_flag(wram->wAvailableCallers[rem], true);

// NothingToSample:
    // XOR_A_A;
    // RET;
}

void GetAvailableCallers(void){
    FARCALL(aCheckTime);
    LD_A_C;
    LD_addr_A(wCheckedTime);
    LD_HL(wNumAvailableCallers);
    LD_BC(CONTACT_LIST_SIZE + 1);
    XOR_A_A;
    CALL(aByteFill);
    LD_DE(wPhoneList);
    LD_A(CONTACT_LIST_SIZE);


loop:
    LD_addr_A(wPhoneListIndex);
    LD_A_de;
    AND_A_A;
    IF_Z goto not_good_for_call;
    LD_HL(mPhoneContacts + PHONE_CONTACT_SCRIPT2_TIME);
    LD_BC(PHONE_CONTACT_SIZE);
    CALL(aAddNTimes);
    LD_A_addr(wCheckedTime);
    AND_A_hl;
    IF_Z goto not_good_for_call;
    LD_BC(PHONE_CONTACT_MAP_GROUP - PHONE_CONTACT_SCRIPT2_TIME);
    ADD_HL_BC;
    LD_A_addr(wMapGroup);
    CP_A_hl;
    IF_NZ goto different_map;
    INC_HL;
    LD_A_addr(wMapNumber);
    CP_A_hl;
    IF_Z goto not_good_for_call;

different_map:
    LD_A_addr(wNumAvailableCallers);
    LD_C_A;
    LD_B(0);
    INC_A;
    LD_addr_A(wNumAvailableCallers);
    LD_HL(wAvailableCallers);
    ADD_HL_BC;
    LD_A_de;
    LD_hl_A;

not_good_for_call:
    INC_DE;
    LD_A_addr(wPhoneListIndex);
    DEC_A;
    IF_NZ goto loop;
    RET;

}

void GetAvailableCallers_Conv(void){
    // FARCALL(aCheckTime);
    u8_flag_s time = CheckTime_Conv();
    // LD_A_C;
    // LD_addr_A(wCheckedTime);
    wram->wCheckedTime = time.a;
    // LD_HL(wNumAvailableCallers);
    // LD_BC(CONTACT_LIST_SIZE + 1);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(&wram->wNumAvailableCallers, CONTACT_LIST_SIZE + 1, 0);
    // LD_DE(wPhoneList);
    uint8_t* de = wram->wPhoneList;
    // LD_A(CONTACT_LIST_SIZE);
    for(uint8_t a = 0; a < CONTACT_LIST_SIZE; ++a) {
    // loop:
        // LD_addr_A(wPhoneListIndex);
        // LD_A_de;
        uint8_t i = de[a];
        // AND_A_A;
        // IF_Z goto not_good_for_call;
        if(i == 0)
            continue;
        // LD_HL(mPhoneContacts + PHONE_CONTACT_SCRIPT2_TIME);
        const struct PhoneContact* const hl = &PhoneContacts[i];
        // LD_BC(PHONE_CONTACT_SIZE);
        // CALL(aAddNTimes);
        // LD_A_addr(wCheckedTime);
        // AND_A_hl;
        // IF_Z goto not_good_for_call;
        if(!(hl->callerTime & time.a))
            continue;
        // LD_BC(PHONE_CONTACT_MAP_GROUP - PHONE_CONTACT_SCRIPT2_TIME);
        // ADD_HL_BC;
        // LD_A_addr(wMapGroup);
        // CP_A_hl;
        // IF_NZ goto different_map;
        // INC_HL;
        // LD_A_addr(wMapNumber);
        // CP_A_hl;
        // IF_Z goto not_good_for_call;
        if(hl->mapGroup == wram->wMapGroup || hl->mapNumber == wram->wMapNumber)
            continue;

    // different_map:
        // LD_A_addr(wNumAvailableCallers);
        // LD_C_A;
        // LD_B(0);
        // INC_A;
        // LD_addr_A(wNumAvailableCallers);
        uint8_t j = wram->wNumAvailableCallers++;
        // LD_HL(wAvailableCallers);
        // ADD_HL_BC;
        // LD_A_de;
        // LD_hl_A;
        wram->wAvailableCallers[j] = i;

    // not_good_for_call:
        // INC_DE;
        // LD_A_addr(wPhoneListIndex);
        // DEC_A;
        // IF_NZ goto loop;
    }
    // RET;
}

void CheckSpecialPhoneCall(void){
    LD_A_addr(wSpecialPhoneCallID);
    AND_A_A;
    IF_Z goto NoPhoneCall;

    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(mSpecialPhoneCallList);
    LD_A(SPECIALCALL_SIZE);
    CALL(aAddNTimes);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(av_hl_);
    IF_NC goto NoPhoneCall;

    CALL(aCheckSpecialPhoneCall_DoSpecialPhoneCall);
    INC_HL;
    INC_HL;
    LD_A_hli;
    LD_E_A;
    PUSH_HL;
    CALL(aLoadCallerScript);
    POP_HL;
    LD_DE(wCallerContact + PHONE_CONTACT_SCRIPT2_BANK);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    LD_A(BANK(aCheckSpecialPhoneCall_script));
    LD_HL(mCheckSpecialPhoneCall_script);
    CALL(aCallScript);
    SCF;
    RET;

NoPhoneCall:
    XOR_A_A;
    RET;


script:
    //pause ['30']
    //sjump ['Script_ReceivePhoneCall']


DoSpecialPhoneCall:
    LD_A_addr(wSpecialPhoneCallID);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(mSpecialPhoneCallList);
    LD_A(SPECIALCALL_SIZE);
    CALL(aAddNTimes);
    RET;

}

static bool CheckSpecialPhoneCall_script(script_s* s) {
// script:
    SCRIPT_BEGIN
    pause(30)
    sjump(Script_ReceivePhoneCall)
    SCRIPT_END
}

bool CheckSpecialPhoneCall_Conv(void){
    // LD_A_addr(wSpecialPhoneCallID);
    // AND_A_A;
    // IF_Z goto NoPhoneCall;
    if(wram->wSpecialPhoneCallID == 0)
        return false;

    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mSpecialPhoneCallList);
    // LD_A(SPECIALCALL_SIZE);
    // CALL(aAddNTimes);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct SpecialCall* spec = SpecialPhoneCallList + (wram->wSpecialPhoneCallID - 1);
    // CALL(av_hl_);
    // IF_NC goto NoPhoneCall;
    if(!spec->condition())
        return false;

    // CALL(aCheckSpecialPhoneCall_DoSpecialPhoneCall);
    // INC_HL;
    // INC_HL;
    // LD_A_hli;
    // LD_E_A;
    // PUSH_HL;
    // CALL(aLoadCallerScript);
    LoadCallerScript_Conv(spec->contact);
    // POP_HL;
    // LD_DE(wCallerContact + PHONE_CONTACT_SCRIPT2_BANK);
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    gCallerContact.callerScript = spec->script;
    // LD_A(BANK(aCheckSpecialPhoneCall_script));
    // LD_HL(mCheckSpecialPhoneCall_script);
    // CALL(aCallScript);
    CallScript_Conv2(CheckSpecialPhoneCall_script);
    // SCF;
    // RET;
    return true;

// NoPhoneCall:
    // XOR_A_A;
    // RET;


// DoSpecialPhoneCall:
    // LD_A_addr(wSpecialPhoneCallID);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mSpecialPhoneCallList);
    // LD_A(SPECIALCALL_SIZE);
    // CALL(aAddNTimes);
    // RET;
}

void SpecialCallOnlyWhenOutside(void){
    LD_A_addr(wEnvironment);
    CP_A(TOWN);
    IF_Z goto outside;
    CP_A(ROUTE);
    IF_Z goto outside;
    XOR_A_A;
    RET;


outside:
    SCF;
    RET;

}

bool SpecialCallOnlyWhenOutside_Conv(void){
    // LD_A_addr(wEnvironment);
    uint8_t a = wram->wEnvironment;
    // CP_A(TOWN);
    // IF_Z goto outside;
    // CP_A(ROUTE);
    // IF_Z goto outside;
    if(a == TOWN || a == ROUTE) {
    // outside:
        // SCF;
        // RET;
        return true;
    }
    // XOR_A_A;
    // RET;
    return false;
}

void SpecialCallWhereverYouAre(void){
    SCF;
    RET;

}

bool SpecialCallWhereverYouAre_Conv(void){
    return true;
}

void MakePhoneCallFromPokegear(void){
// Don't do the call if you're in a link communication
    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto OutOfArea;
// If you're in an area without phone service, don't do the call
    CALL(aGetMapPhoneService);
    AND_A_A;
    IF_NZ goto OutOfArea;
// If the person can't take a call at that time, don't do the call
    LD_A_B;
    LD_addr_A(wCurCaller);
    LD_HL(mPhoneContacts);
    LD_BC(PHONE_CONTACT_SIZE);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_HL(PHONE_CONTACT_SCRIPT1_TIME);
    ADD_HL_DE;
    LD_A_hl;
    CALL(aCheckPhoneContactTimeOfDay);
    IF_Z goto OutOfArea;
// If we're in the same map as the person we're calling,
// use the "Just talk to that person" script.
    LD_HL(PHONE_CONTACT_MAP_GROUP);
    ADD_HL_DE;
    LD_A_addr(wMapGroup);
    CP_A_hl;
    IF_NZ goto GetPhoneScript;
    LD_HL(PHONE_CONTACT_MAP_NUMBER);
    ADD_HL_DE;
    LD_A_addr(wMapNumber);
    CP_A_hl;
    IF_NZ goto GetPhoneScript;
    LD_B(BANK(aPhoneScript_JustTalkToThem));
    LD_HL(mPhoneScript_JustTalkToThem);
    goto DoPhoneCall;


GetPhoneScript:
    LD_HL(PHONE_CONTACT_SCRIPT1_BANK);
    ADD_HL_DE;
    LD_B_hl;
    LD_HL(PHONE_CONTACT_SCRIPT1_ADDR);
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    goto DoPhoneCall;


OutOfArea:
    LD_B(BANK(aLoadOutOfAreaScript));
    LD_DE(mLoadOutOfAreaScript);
    CALL(aExecuteCallbackScript);
    RET;


DoPhoneCall:
    LD_A_B;
    LD_addr_A(wPhoneScriptBank);
    LD_A_L;
    LD_addr_A(wPhoneCaller);
    LD_A_H;
    LD_addr_A(wPhoneCaller + 1);
    LD_B(BANK(aLoadPhoneScriptBank));
    LD_DE(mLoadPhoneScriptBank);
    CALL(aExecuteCallbackScript);
    RET;

}

void MakePhoneCallFromPokegear_Conv(uint8_t caller){
// Don't do the call if you're in a link communication
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto OutOfArea;
    if(wram->wLinkMode != 0 || GetMapPhoneService_Conv() != 0) {
    OutOfArea:
        // LD_B(BANK(aLoadOutOfAreaScript));
        // LD_DE(mLoadOutOfAreaScript);
        // CALL(aExecuteCallbackScript);
        ExecuteCallbackScript_Conv(LoadOutOfAreaScript);
        // RET;
        return;
    }

// If you're in an area without phone service, don't do the call
    // CALL(aGetMapPhoneService);
    // AND_A_A;
    // IF_NZ goto OutOfArea;
// If the person can't take a call at that time, don't do the call
    // LD_A_B;
    // LD_addr_A(wCurCaller);
    wram->wCurCaller = caller;
    // LD_HL(mPhoneContacts);
    // LD_BC(PHONE_CONTACT_SIZE);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(PHONE_CONTACT_SCRIPT1_TIME);
    // ADD_HL_DE;
    // LD_A_hl;
    const struct PhoneContact* contact_struct = PhoneContacts + caller;
    // CALL(aCheckPhoneContactTimeOfDay);
    // IF_Z goto OutOfArea;
    if(!CheckPhoneContactTimeOfDay_Conv(contact_struct->calleeTime))
        goto OutOfArea;
// If we're in the same map as the person we're calling,
// use the "Just talk to that person" script.
    // LD_HL(PHONE_CONTACT_MAP_GROUP);
    // ADD_HL_DE;
    // LD_A_addr(wMapGroup);
    // CP_A_hl;
    // IF_NZ goto GetPhoneScript;
    // LD_HL(PHONE_CONTACT_MAP_NUMBER);
    // ADD_HL_DE;
    // LD_A_addr(wMapNumber);
    // CP_A_hl;
    // IF_NZ goto GetPhoneScript;
    Script_fn_t script;
    if(contact_struct->mapGroup == wram->wMapGroup && contact_struct->mapNumber == wram->wMapNumber) {
        // LD_B(BANK(aPhoneScript_JustTalkToThem));
        // LD_HL(mPhoneScript_JustTalkToThem);
        script = PhoneScript_JustTalkToThem;
        // goto DoPhoneCall;
    }
    else {
    // GetPhoneScript:
        // LD_HL(PHONE_CONTACT_SCRIPT1_BANK);
        // ADD_HL_DE;
        // LD_B_hl;
        // LD_HL(PHONE_CONTACT_SCRIPT1_ADDR);
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // goto DoPhoneCall;
        script = contact_struct->calleeScript;
    }

// DoPhoneCall:
    // LD_A_B;
    // LD_addr_A(wPhoneScriptBank);
    // LD_A_L;
    // LD_addr_A(wPhoneCaller);
    // LD_A_H;
    // LD_addr_A(wPhoneCaller + 1);
    gPhoneCaller = script;
    // LD_B(BANK(aLoadPhoneScriptBank));
    // LD_DE(mLoadPhoneScriptBank);
    // CALL(aExecuteCallbackScript);
    ExecuteCallbackScript_Conv(LoadPhoneScriptBank);
    // RET;

}

bool LoadPhoneScriptBank(script_s* s){
    SCRIPT_BEGIN
    scall(gPhoneCaller)
    s_endcallback
    SCRIPT_END
}

bool LoadOutOfAreaScript(script_s* s){
    SCRIPT_BEGIN
    scall(PhoneOutOfAreaScript)
    s_endcallback
    SCRIPT_END
}

void LoadCallerScript(void){
    NOP;
    NOP;
    LD_A_E;
    LD_addr_A(wCurCaller);
    AND_A_A;
    IF_NZ goto actualcaller;
    LD_A(BANK(aWrongNumber));
    LD_HL(mWrongNumber);
    goto proceed;


actualcaller:
    LD_HL(mPhoneContacts);
    LD_BC(PHONE_CONTACT_SIZE);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A(BANK(aPhoneContacts));

proceed:
    LD_DE(wCallerContact);
    LD_BC(PHONE_CONTACT_SIZE);
    CALL(aFarCopyBytes);
    RET;

}

void LoadCallerScript_Conv(uint8_t caller){
    // NOP;
    // NOP;
    // LD_A_E;
    // LD_addr_A(wCurCaller);
    wram->wCurCaller = caller;
    // AND_A_A;
    // IF_NZ goto actualcaller;
    if(caller == 0) {
        // LD_A(BANK(aWrongNumber));
        // LD_HL(mWrongNumber);
        // goto proceed;
        CopyBytes_Conv2(&gCallerContact, &WrongNumber, sizeof(gCallerContact));
    }
    else {


    // actualcaller:
    //     LD_HL(mPhoneContacts);
    //     LD_BC(PHONE_CONTACT_SIZE);
    //     LD_A_E;
    //     CALL(aAddNTimes);
    //     LD_A(BANK(aPhoneContacts));
        // uint16_t phone_struct = AddNTimes_Conv(PHONE_CONTACT_SIZE, mPhoneContacts, caller);
        // FarCopyBytes_Conv(wCallerContact, BANK(aPhoneContacts), phone_struct, PHONE_CONTACT_SIZE);
        CopyBytes_Conv2(&gCallerContact, &PhoneContacts[caller], sizeof(gCallerContact));
    }
}

const struct TextCmd PhoneWrongNumberText[] = {
    text_far(v_PhoneWrongNumberText)
    text_end
};

bool WrongNumber_script(script_s* s) {
    SCRIPT_BEGIN
    writetext(PhoneWrongNumberText)
    s_end
    SCRIPT_END
}

const struct PhoneContact WrongNumber = {
    .trainerClass = TRAINER_NONE,
    .trainerId = PHONE_00,

    .callerScript = WrongNumber_script,
    .calleeScript = WrongNumber_script,
    //db ['TRAINER_NONE', 'PHONE_00'];
    //dba ['.script']

// script:
    //writetext ['.PhoneWrongNumberText']
    //end ['?']

// PhoneWrongNumberText:
    //text_far ['_PhoneWrongNumberText']
    //text_end ['?']
};

// void Script_ReceivePhoneCall(void){
//     //refreshscreen ['?']
//     //callasm ['RingTwice_StartCall']
//     //memcall ['wCallerContact + PHONE_CONTACT_SCRIPT2_BANK']
//     //waitbutton ['?']
//     //callasm ['HangUp']
//     //closetext ['?']
//     //callasm ['InitCallReceiveDelay']
//     //end ['?']

//     return Script_SpecialBillCall();
// }

bool Script_ReceivePhoneCall(script_s* s) {
    SCRIPT_BEGIN
    refreshscreen
    RingTwice_StartCall();
    scall(gCallerContact.calleeScript);
    waitbutton
    HangUp();
    closetext
    InitCallReceiveDelay();
    SCRIPT_END
}

bool Script_SpecialBillCall(script_s* s) {
    SCRIPT_BEGIN
    Script_SpecialBillCall_LoadBillScript();
    sjump(Script_ReceivePhoneCall);
    SCRIPT_END
}

void Script_SpecialBillCall_LoadBillScript(void) {
    return LoadCallerScript_Conv(PHONE_BILL);
}

// void Script_SpecialElmCall(void){
//  //  unreferenced
    //callasm ['.LoadElmScript']
    //pause ['30']
    //sjump ['Script_ReceivePhoneCall']


// LoadElmScript:
//     LD_E(PHONE_ELM);
//     JP(mLoadCallerScript);

// }

bool Script_SpecialElmCall(script_s* s) {
    SCRIPT_BEGIN
    Script_SpecialElmCall_LoadElmScript();
    pause(30);
    sjump(Script_ReceivePhoneCall);
    SCRIPT_END
}

void Script_SpecialElmCall_LoadElmScript(void) {
    return LoadCallerScript_Conv(PHONE_ELM);
}

static void RingTwice_StartCall_CallerTextboxWithName(void) {
    // LD_A_addr(wCurCaller);
    // LD_B_A;
    // CALL(aPhone_TextboxWithName);
    // RET;
    return Phone_TextboxWithName_Conv(wram->wCurCaller);
}

static void RingTwice_StartCall_Ring(void) {
    // CALL(aPhone_StartRinging);
    Phone_StartRinging();
    // CALL(aPhone_Wait20Frames);
    Phone_Wait20Frames();
    // CALL(aRingTwice_StartCall_CallerTextboxWithName);
    RingTwice_StartCall_CallerTextboxWithName();
    // CALL(aPhone_Wait20Frames);
    Phone_Wait20Frames();
    // CALL(aPhone_CallerTextbox);
    Phone_CallerTextbox_Conv();
    // CALL(aPhone_Wait20Frames);
    Phone_Wait20Frames();
    // CALL(aRingTwice_StartCall_CallerTextboxWithName);
    RingTwice_StartCall_CallerTextboxWithName();
    // RET;
}

void RingTwice_StartCall(void){
    // CALL(aRingTwice_StartCall_Ring);
    RingTwice_StartCall_Ring();
    // CALL(aRingTwice_StartCall_Ring);
    RingTwice_StartCall_Ring();
    // FARCALL(aStubbedTrainerRankings_PhoneCalls);
    // RET;
}

void PhoneCall(void){
    LD_A_B;
    LD_addr_A(wPhoneScriptBank);
    LD_A_E;
    LD_addr_A(wPhoneCaller);
    LD_A_D;
    LD_addr_A(wPhoneCaller + 1);
    CALL(aPhoneCall_Ring);
    CALL(aPhoneCall_Ring);
    FARCALL(aStubbedTrainerRankings_PhoneCalls);
    RET;


Ring:
    CALL(aPhone_StartRinging);
    CALL(aPhone_Wait20Frames);
    CALL(aPhoneCall_CallerTextboxWithName);
    CALL(aPhone_Wait20Frames);
    CALL(aPhone_CallerTextbox);
    CALL(aPhone_Wait20Frames);
    CALL(aPhoneCall_CallerTextboxWithName);
    RET;


CallerTextboxWithName:
    CALL(aPhone_CallerTextbox);
    hlcoord(1, 2, wTilemap);
    LD_hl(0x62);
    INC_HL;
    INC_HL;
    LD_A_addr(wPhoneScriptBank);
    LD_B_A;
    LD_A_addr(wPhoneCaller);
    LD_E_A;
    LD_A_addr(wPhoneCaller + 1);
    LD_D_A;
    CALL(aBrokenPlaceFarString);
    RET;

}

static void PhoneCall_CallerTextboxWithName(void) {
    // CALL(aPhone_CallerTextbox);
    Phone_CallerTextbox_Conv();
    // hlcoord(1, 2, wTilemap);
    // LD_hl(0x62);
    *coord(1, 2, wram->wTilemap) = 0x62;
    // INC_HL;
    // INC_HL;
    // LD_A_addr(wPhoneScriptBank);
    // LD_B_A;
    // LD_A_addr(wPhoneCaller);
    // LD_E_A;
    // LD_A_addr(wPhoneCaller + 1);
    // LD_D_A;
    // CALL(aBrokenPlaceFarString);
    // Replaced Broken function with this.
    PlaceStringSimple(U82C("?@"), coord(3, 2, wram->wTilemap));
    // RET;
}

static void PhoneCall_Ring(void) {
    // CALL(aPhone_StartRinging);
    Phone_StartRinging();
    // CALL(aPhone_Wait20Frames);
    Phone_Wait20Frames();
    // CALL(aPhoneCall_CallerTextboxWithName);
    PhoneCall_CallerTextboxWithName();
    // CALL(aPhone_Wait20Frames);
    Phone_Wait20Frames();
    // CALL(aPhone_CallerTextbox);
    Phone_CallerTextbox_Conv();
    // CALL(aPhone_Wait20Frames);
    Phone_Wait20Frames();
    // CALL(aPhoneCall_CallerTextboxWithName);
    PhoneCall_CallerTextboxWithName();
    // RET;
}

// This function is unused and broken in the original game.
void PhoneCall_Conv(Script_fn_t de){
    // LD_A_B;
    // LD_addr_A(wPhoneScriptBank);
    // LD_A_E;
    // LD_addr_A(wPhoneCaller);
    // LD_A_D;
    // LD_addr_A(wPhoneCaller + 1);
    gPhoneCaller = de;
    // CALL(aPhoneCall_Ring);
    PhoneCall_Ring();
    // CALL(aPhoneCall_Ring);
    PhoneCall_Ring();
    // FARCALL(aStubbedTrainerRankings_PhoneCalls);
    // RET;
}

void Phone_NoSignal(void){
    // LD_DE(SFX_NO_SIGNAL);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_NO_SIGNAL);
    // JR(mPhone_CallEnd);
    return Phone_CallEnd();

}

void HangUp(void){
    // CALL(aHangUp_Beep);
    HangUp_Beep();
    // CALL(aHangUp_Wait20Frames);
    HangUp_Wait20Frames();
    return Phone_CallEnd();
}

void Phone_CallEnd(void){
    // CALL(aHangUp_BoopOn);
    HangUp_BoopOn();
    // CALL(aHangUp_Wait20Frames);
    HangUp_Wait20Frames();
    // CALL(aHangUp_BoopOff);
    HangUp_BoopOff();
    // CALL(aHangUp_Wait20Frames);
    HangUp_Wait20Frames();
    // CALL(aHangUp_BoopOn);
    HangUp_BoopOn();
    // CALL(aHangUp_Wait20Frames);
    HangUp_Wait20Frames();
    // CALL(aHangUp_BoopOff);
    HangUp_BoopOff();
    // CALL(aHangUp_Wait20Frames);
    HangUp_Wait20Frames();
    // CALL(aHangUp_BoopOn);
    HangUp_BoopOn();
    // CALL(aHangUp_Wait20Frames);
    HangUp_Wait20Frames();
    // CALL(aHangUp_BoopOff);
    HangUp_BoopOff();
    // CALL(aHangUp_Wait20Frames);
    HangUp_Wait20Frames();
    // RET;
}

void HangUp_ShutDown(void){
//  //  unreferenced
    LD_DE(SFX_SHUT_DOWN_PC);
    CALL(aPlaySFX);
    RET;

}

void HangUp_Beep(void){
    // LD_HL(mPhoneClickText);
    // CALL(aPrintText);
    PrintText_Conv2(PhoneClickText);
    // LD_DE(SFX_HANG_UP);
    // CALL(aPlaySFX);
    // RET;
    return PlaySFX_Conv(SFX_HANG_UP);
}

const struct TextCmd PhoneClickText[] = {
    text_far(v_PhoneClickText)
    text_end
};

void HangUp_BoopOn(void){
    // LD_HL(mPhoneEllipseText);
    // CALL(aPrintText);
    // RET;
    return PrintText_Conv2(PhoneEllipseText);
}

const struct TextCmd PhoneEllipseText[] = {
    text_far(v_PhoneEllipseText)
    text_end
};

void HangUp_BoopOff(void){
    // CALL(aSpeechTextbox);
    // RET;
    return SpeechTextbox_Conv2();
}

void Phone_StartRinging(void){
    // CALL(aWaitSFX);
    WaitSFX_Conv();
    // LD_DE(SFX_CALL);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_CALL);
    // CALL(aPhone_CallerTextbox);
    Phone_CallerTextbox_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // FARCALL(aPhoneRing_CopyTilemapAtOnce);
    PhoneRing_CopyTilemapAtOnce_Conv();
    // RET;
}

void HangUp_Wait20Frames(void){
    // JR(mPhone_Wait20Frames);
    return Phone_Wait20Frames();
}

void Phone_Wait20Frames(void){
    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames_Conv(20);
    // FARCALL(aPhoneRing_CopyTilemapAtOnce);
    PhoneRing_CopyTilemapAtOnce_Conv();
    // RET;
}

void Phone_TextboxWithName(void){
    PUSH_BC;
    CALL(aPhone_CallerTextbox);
    hlcoord(1, 1, wTilemap);
    LD_hl(0x62);
    INC_HL;
    INC_HL;
    LD_D_H;
    LD_E_L;
    POP_BC;
    CALL(aGetCallerClassAndName);
    RET;

}

void Phone_TextboxWithName_Conv(uint8_t caller){
    // PUSH_BC;
    // CALL(aPhone_CallerTextbox);
    Phone_CallerTextbox_Conv();
    // hlcoord(1, 1, wTilemap);
    // LD_hl(0x62);
    *coord(1, 1, wram->wTilemap) = 0x62;
    // INC_HL;
    // INC_HL;
    // LD_D_H;
    // LD_E_L;
    uint8_t* de = coord(1, 1, wram->wTilemap) + 2;
    // POP_BC;
    // CALL(aGetCallerClassAndName);
    GetCallerClassAndName_Conv(de, caller);
    // RET;

}

void Phone_CallerTextbox(void){
    hlcoord(0, 0, wTilemap);
    LD_B(2);
    LD_C(SCREEN_WIDTH - 2);
    CALL(aTextbox);
    RET;

}

void Phone_CallerTextbox_Conv(void){
    // hlcoord(0, 0, wTilemap);
    // LD_B(2);
    // LD_C(SCREEN_WIDTH - 2);
    // CALL(aTextbox);
    // RET;
    return Textbox_Conv2(coord(0, 0, wram->wTilemap), 2, SCREEN_WIDTH - 2);
}

void GetCallerClassAndName(void){
    LD_H_D;
    LD_L_E;
    LD_A_B;
    CALL(aGetCallerTrainerClass);
    CALL(aGetCallerName);
    RET;

}

void GetCallerClassAndName_Conv(uint8_t* de, uint8_t b){
    // LD_H_D;
    // LD_L_E;
    // LD_A_B;
    // CALL(aGetCallerTrainerClass);
    struct TrainerId tid = GetCallerTrainerClass_Conv(b);
    // CALL(aGetCallerName);
    // RET;
    return GetCallerName_Conv(de, tid);
}

void CheckCanDeletePhoneNumber(void){
    LD_A_C;
    CALL(aGetCallerTrainerClass);
    LD_A_C;
// and a
    RET_NZ ;
    LD_A_B;
    CP_A(PHONECONTACT_MOM);
    RET_Z ;
    CP_A(PHONECONTACT_ELM);
    RET_Z ;
    LD_C(0x1);
    RET;

}

bool CheckCanDeletePhoneNumber_Conv(uint8_t c){
    // LD_A_C;
    // CALL(aGetCallerTrainerClass);
    struct TrainerId tid = GetCallerTrainerClass_Conv(c);
    // LD_A_C;
// and a
    // RET_NZ ;
    if(tid.trainerClass != 0)
        return true;
    // LD_A_B;
    // CP_A(PHONECONTACT_MOM);
    // RET_Z ;
    // CP_A(PHONECONTACT_ELM);
    // RET_Z ;
    if(tid.trainerId == PHONECONTACT_MOM || tid.trainerId == PHONECONTACT_ELM)
        return false;
    // LD_C(0x1);
    // RET;
    return true;
}

void GetCallerTrainerClass(void){
    PUSH_HL;
    LD_HL(mPhoneContacts + PHONE_CONTACT_TRAINER_CLASS);
    LD_BC(PHONE_CONTACT_SIZE);
    CALL(aAddNTimes);
    LD_A_hli;
    LD_B_hl;
    LD_C_A;
    POP_HL;
    RET;

}

struct TrainerId GetCallerTrainerClass_Conv(uint8_t caller){
    // PUSH_HL;
    // LD_HL(mPhoneContacts + PHONE_CONTACT_TRAINER_CLASS);
    // LD_BC(PHONE_CONTACT_SIZE);
    // CALL(aAddNTimes);
    // LD_A_hli;
    // LD_B_hl;
    // LD_C_A;
    // POP_HL;
    // RET;
    return (struct TrainerId){.trainerClass=PhoneContacts[caller].trainerClass, .trainerId=PhoneContacts[caller].trainerId};
}

void GetCallerName(void){
    LD_A_C;
    AND_A_A;
    IF_Z goto NotTrainer;

    CALL(aPhone_GetTrainerName);
    PUSH_HL;
    PUSH_BC;
    CALL(aPlaceString);
    LD_A(0x9c);
    LD_bc_A;
    POP_BC;
    POP_HL;
    LD_DE(SCREEN_WIDTH + 3);
    ADD_HL_DE;
    CALL(aPhone_GetTrainerClassName);
    CALL(aPlaceString);
    RET;


NotTrainer:
    PUSH_HL;
    LD_C_B;
    LD_B(0);
    LD_HL(mNonTrainerCallerNames);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_E_A;
    LD_D_hl;
    POP_HL;
    CALL(aPlaceString);
    RET;

// INCLUDE "data/phone/non_trainer_names.asm"

    return Phone_GetTrainerName();
}

void GetCallerName_Conv(uint8_t* hl, struct TrainerId c){
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto NotTrainer;
    if(c.trainerClass == TRAINER_NONE) {
    // NotTrainer:
        // PUSH_HL;
        // LD_C_B;
        // LD_B(0);
        // LD_HL(mNonTrainerCallerNames);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_E_A;
        // LD_D_hl;
        // POP_HL;
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(NonTrainerCallerNames[c.trainerId]), hl);
        // RET;
        return;
    }

    // CALL(aPhone_GetTrainerName);
    uint8_t* name = GetTrainerName_Conv(c.trainerId, c.trainerClass);
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aPlaceString);
    struct TextPrintState state = {.de = name, .hl = hl};
    PlaceString_Conv(&state, hl);
    // LD_A(0x9c);
    // LD_bc_A;
    *state.bc = 0x9c;
    // POP_BC;
    // POP_HL;
    // LD_DE(SCREEN_WIDTH + 3);
    // ADD_HL_DE;
    hl += SCREEN_WIDTH + 3;
    // CALL(aPhone_GetTrainerClassName);
    // CALL(aPlaceString);
    PlaceStringSimple(GetTrainerClassName_Conv(c.trainerClass), hl);
    // RET;
}

void Phone_GetTrainerName(void){
    PUSH_HL;
    PUSH_BC;
    FARCALL(aGetTrainerName);
    POP_BC;
    POP_HL;
    RET;

}

void Phone_GetTrainerClassName(void){
    PUSH_HL;
    PUSH_BC;
    FARCALL(aGetTrainerClassName);
    POP_BC;
    POP_HL;
    RET;

}

void GetCallerLocation(void){
    LD_A_addr(wCurCaller);
    CALL(aGetCallerTrainerClass);
    LD_D_C;
    LD_E_B;
    PUSH_DE;
    LD_A_addr(wCurCaller);
    LD_HL(mPhoneContacts + PHONE_CONTACT_MAP_GROUP);
    LD_BC(PHONE_CONTACT_SIZE);
    CALL(aAddNTimes);
    LD_B_hl;
    INC_HL;
    LD_C_hl;
    PUSH_BC;
    CALL(aGetWorldMapLocation);
    LD_E_A;
    FARCALL(aGetLandmarkName);
    POP_BC;
    POP_DE;
    RET;

// INCLUDE "data/phone/phone_contacts.asm"

// INCLUDE "data/phone/special_calls.asm"

}

struct CallerLocation GetCallerLocation_Conv(void){
    // LD_A_addr(wCurCaller);
    // CALL(aGetCallerTrainerClass);
    struct TrainerId tr = GetCallerTrainerClass_Conv(wram->wCurCaller);
    // LD_D_C;
    // LD_E_B;
    // PUSH_DE;
    // LD_A_addr(wCurCaller);
    // LD_HL(mPhoneContacts + PHONE_CONTACT_MAP_GROUP);
    // LD_BC(PHONE_CONTACT_SIZE);
    // CALL(aAddNTimes);
    // LD_B_hl;
    uint8_t mgroup = PhoneContacts[wram->wCurCaller].mapGroup;
    // INC_HL;
    // LD_C_hl;
    uint8_t mnum = PhoneContacts[wram->wCurCaller].mapNumber;
    // PUSH_BC;
    // CALL(aGetWorldMapLocation);
    uint8_t landmark = GetWorldMapLocation_Conv2(mgroup, mnum);
    // LD_E_A;
    // FARCALL(aGetLandmarkName);
    GetLandmarkName_Conv(landmark);
    // POP_BC;
    // POP_DE;
    // RET;
    return (struct CallerLocation) {.tclass = tr.trainerClass, .tid = tr.trainerId, .mgroup = mgroup, .mnum = mnum};

// INCLUDE "data/phone/phone_contacts.asm"

// INCLUDE "data/phone/special_calls.asm"

}

bool PhoneOutOfAreaScript(script_s* s){
    SCRIPT_BEGIN
    writetext(PhoneOutOfAreaText);
    s_end
    SCRIPT_END
}

const struct TextCmd PhoneOutOfAreaText[] = {
    text_far(v_PhoneOutOfAreaText)
    text_end
};

bool PhoneScript_JustTalkToThem(script_s* s){
    SCRIPT_BEGIN
    writetext(PhoneJustTalkToThemText);
    s_end
    SCRIPT_END
}

const struct TextCmd PhoneJustTalkToThemText[] = {
    text_far(v_PhoneJustTalkToThemText)
    text_end
};

bool PhoneThankYouTextScript(script_s* s){
//  //  unreferenced
    SCRIPT_BEGIN
    writetext(PhoneThankYouText)
    SCRIPT_END
}

const struct TextCmd PhoneThankYouText[] = {
    text_far(v_PhoneThankYouText)
    text_end
};


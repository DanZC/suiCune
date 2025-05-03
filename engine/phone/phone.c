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
#include "../../mobile/mobile_41.h"
#include "../../util/scripting.h"
#include "../../data/text/common.h"
#include "../../data/phone/non_trainer_names.h"
#include "../../data/phone/phone_contacts.h"
#include "../../data/phone/special_calls.h"
#include "../../data/phone/permanent_numbers.h"

struct PhoneContact gCallerContact;
Script_fn_t gPhoneCaller;

bool AddPhoneNumber(uint8_t c){
    // CALL(av_CheckCellNum);
    uint8_t* hl = CheckCellNum(c);

    // IF_C goto cant_add;
    if(hl != NULL) {
        return false;
    }

    // CALL(aPhone_FindOpenSlot);
    // IF_NC goto cant_add;
    hl = Phone_FindOpenSlot(c);
    if(hl == NULL) {
        return false;
    }

    // LD_hl_C;
    *hl = c;
    
    // XOR_A_A;
    // RET;
    return true;
}

// Returns true (nc) if the number was successfully deleted.
bool DelCellNum(uint8_t c){
    // CALL(av_CheckCellNum);
    // IF_NC goto not_in_list;
    uint8_t* hl = CheckCellNum(c);
    if(hl == NULL) {
        return false;
    }

    // XOR_A_A;
    // LD_hl_A;
    *hl = 0;

    // RET;
    return true;
}

uint8_t* CheckCellNum(uint8_t c){
    // LD_HL(wPhoneList);
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
        if(wram->wPhoneList[b] == c)
            return wram->wPhoneList + b;
        // DEC_B;
        // IF_NZ goto loop;
    }
    // XOR_A_A;
    // RET;
    return NULL;
}

uint8_t* Phone_FindOpenSlot(uint8_t c){
    // CALL(aGetRemainingSpaceInPhoneList);
    // LD_B_A;
    uint8_t b = GetRemainingSpaceInPhoneList(c);
    
    // LD_HL(wPhoneList);

    for(uint8_t i = 0; i < b; ++i) {
        // LD_A_hli;
        uint8_t a = wram->wPhoneList[i];
        // AND_A_A;
        // IF_Z goto FoundOpenSpace;
        if(a == 0) {
            return wram->wPhoneList + i;
        }
        // DEC_B;
        // IF_NZ goto loop;
    }
    return NULL;
}

uint8_t GetRemainingSpaceInPhoneList(uint8_t c){
    // XOR_A_A;
    // LD_addr_A(wRegisteredPhoneNumbers);
    wram->wRegisteredPhoneNumbers = 0;

    // LD_HL(mPermanentNumbers);

    for(uint8_t i = 0; ; i++)
    {
        // LD_A_hli;
        uint8_t a = PermanentNumbers[i];

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
        if(CheckCellNum(c) != NULL) {
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

static bool CheckPhoneCall_timecheck(void) {
    // FARCALL(aCheckReceiveCallTimer);
    // RET;
    return CheckReceiveCallTimer();
}

//  Check if the phone is ringing in the overworld.
u8_flag_s CheckPhoneCall(void){
    // CALL(aCheckStandingOnEntrance);
    // IF_Z goto no_call;
    if(CheckStandingOnEntrance())
        return u8_flag(0, false);

    // CALL(aCheckPhoneCall_timecheck);
    // NOP;
    // IF_NC goto no_call;
    if(!CheckPhoneCall_timecheck())
        return u8_flag(0, false);

// 50% chance for a call
    // CALL(aRandom);
    // LD_B_A;
    uint8_t b = Random();
    // AND_A(0b01111111);
    // CP_A_B;
    // IF_NZ goto no_call;
    if((b & 0b01111111) != b)
        return u8_flag(0, false);

    // CALL(aGetMapPhoneService);
    // AND_A_A;
    // IF_NZ goto no_call;
    if(GetMapPhoneService() != 0)
        return u8_flag(0, false);

    // CALL(aGetAvailableCallers);
    GetAvailableCallers();
    // CALL(aChooseRandomCaller);
    // IF_NC goto no_call;
    u8_flag_s res = ChooseRandomCaller();
    if(!res.flag)
        return u8_flag(0, false);

    // LD_E_A;
    // CALL(aLoadCallerScript);
    LoadCallerScript(res.a);
    // LD_A(BANK(aScript_ReceivePhoneCall));
    // LD_HL(mScript_ReceivePhoneCall);
    // CALL(aCallScript);
    uint8_t a = CallScript(Script_ReceivePhoneCall);
    // SCF;
    // RET;
    return u8_flag(a, true);

// no_call:
    // XOR_A_A;
    // RET;
}

static bool CheckPhoneContactTimeOfDay(uint8_t a){
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_AF;

    // FARCALL(aCheckTime);
    uint8_t curTime = CheckTime().a;
    // POP_AF;
    // AND_A(ANYTIME);
    // AND_A_C;

    // POP_DE;
    // POP_BC;
    // POP_HL;
    // RET;
    return ((a & (ANYTIME)) & curTime) != 0;
}

u8_flag_s ChooseRandomCaller(void){
//  If no one is available to call, don't return anything.
    // LD_A_addr(wNumAvailableCallers);
    // AND_A_A;
    // IF_Z goto NothingToSample;
    if(wram->wNumAvailableCallers == 0)
        return u8_flag(0, false);

//  Store the number of available callers in c.
    // LD_C_A;
//  Sample a random number between 0 and 31.
    // CALL(aRandom);
    Random();
    // LDH_A_addr(hRandomAdd);
    // SWAP_A;
    // AND_A(0x1f);
    uint8_t a = ((hram->hRandomAdd >> 4) | (hram->hRandomAdd << 4)) & 0x1f;
//  Compute that number modulo the number of available callers.
    // CALL(aSimpleDivide);
    uint8_t rem = a % wram->wNumAvailableCallers;
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
    // FARCALL(aCheckTime);
    u8_flag_s time = CheckTime();
    // LD_A_C;
    // LD_addr_A(wCheckedTime);
    wram->wCheckedTime = time.a;
    // LD_HL(wNumAvailableCallers);
    // LD_BC(CONTACT_LIST_SIZE + 1);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(&wram->wNumAvailableCallers, CONTACT_LIST_SIZE + 1, 0);
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

static bool CheckSpecialPhoneCall_script(script_s* s) {
// script:
    SCRIPT_BEGIN
    pause(30)
    sjump(Script_ReceivePhoneCall)
    SCRIPT_END
}

bool CheckSpecialPhoneCall(void){
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
    const struct SpecialCall* spec = SpecialPhoneCallList + (wram->wSpecialPhoneCallID);
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
    LoadCallerScript(spec->contact);
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
    CallScript(CheckSpecialPhoneCall_script);
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

bool SpecialCallOnlyWhenOutside(void){
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

bool SpecialCallWhereverYouAre(void){
    return true;
}

void MakePhoneCallFromPokegear(uint8_t caller){
// Don't do the call if you're in a link communication
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto OutOfArea;
    if(wram->wLinkMode != LINK_NULL || GetMapPhoneService() != 0) {
    OutOfArea:
        // LD_B(BANK(aLoadOutOfAreaScript));
        // LD_DE(mLoadOutOfAreaScript);
        // CALL(aExecuteCallbackScript);
        ExecuteCallbackScript(LoadOutOfAreaScript);
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
    if(!CheckPhoneContactTimeOfDay(contact_struct->calleeTime))
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
    ExecuteCallbackScript(LoadPhoneScriptBank);
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

void LoadCallerScript(uint8_t caller){
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
        CopyBytes(&gCallerContact, &WrongNumber, sizeof(gCallerContact));
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
        CopyBytes(&gCallerContact, &PhoneContacts[caller], sizeof(gCallerContact));
    }
}

const txt_cmd_s PhoneWrongNumberText[] = {
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
    scall(gCallerContact.callerScript);
    waitbutton
    HangUp();
    closetext
    InitCallReceiveDelay();
    s_end
    SCRIPT_END
}

bool Script_SpecialBillCall(script_s* s) {
    SCRIPT_BEGIN
    Script_SpecialBillCall_LoadBillScript();
    sjump(Script_ReceivePhoneCall);
    SCRIPT_END
}

void Script_SpecialBillCall_LoadBillScript(void) {
    return LoadCallerScript(PHONE_BILL);
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
    return LoadCallerScript(PHONE_ELM);
}

static void RingTwice_StartCall_CallerTextboxWithName(void) {
    // LD_A_addr(wCurCaller);
    // LD_B_A;
    // CALL(aPhone_TextboxWithName);
    // RET;
    return Phone_TextboxWithName(wram->wCurCaller);
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
    Phone_CallerTextbox();
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
    StubbedTrainerRankings_PhoneCalls();
    // RET;
}

static void PhoneCall_CallerTextboxWithName(void) {
    // CALL(aPhone_CallerTextbox);
    Phone_CallerTextbox();
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
    Phone_CallerTextbox();
    // CALL(aPhone_Wait20Frames);
    Phone_Wait20Frames();
    // CALL(aPhoneCall_CallerTextboxWithName);
    PhoneCall_CallerTextboxWithName();
    // RET;
}

// This function is unused and broken in the original game.
void PhoneCall(Script_fn_t de){
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
    StubbedTrainerRankings_PhoneCalls();
    // RET;
}

void Phone_NoSignal(void){
    // LD_DE(SFX_NO_SIGNAL);
    // CALL(aPlaySFX);
    PlaySFX(SFX_NO_SIGNAL);
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
    PrintText(PhoneClickText);
    // LD_DE(SFX_HANG_UP);
    // CALL(aPlaySFX);
    // RET;
    return PlaySFX(SFX_HANG_UP);
}

const txt_cmd_s PhoneClickText[] = {
    text_far(v_PhoneClickText)
    text_end
};

void HangUp_BoopOn(void){
    // LD_HL(mPhoneEllipseText);
    // CALL(aPrintText);
    // RET;
    return PrintText(PhoneEllipseText);
}

const txt_cmd_s PhoneEllipseText[] = {
    text_far(v_PhoneEllipseText)
    text_end
};

void HangUp_BoopOff(void){
    // CALL(aSpeechTextbox);
    // RET;
    return SpeechTextbox();
}

void Phone_StartRinging(void){
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_DE(SFX_CALL);
    // CALL(aPlaySFX);
    PlaySFX(SFX_CALL);
    // CALL(aPhone_CallerTextbox);
    Phone_CallerTextbox();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // FARCALL(aPhoneRing_CopyTilemapAtOnce);
    PhoneRing_CopyTilemapAtOnce();
    // RET;
}

void HangUp_Wait20Frames(void){
    // JR(mPhone_Wait20Frames);
    return Phone_Wait20Frames();
}

void Phone_Wait20Frames(void){
    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames(20);
    // FARCALL(aPhoneRing_CopyTilemapAtOnce);
    PhoneRing_CopyTilemapAtOnce();
    // RET;
}

void Phone_TextboxWithName(uint8_t caller){
    // PUSH_BC;
    // CALL(aPhone_CallerTextbox);
    Phone_CallerTextbox();
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
    GetCallerClassAndName(de, caller);
    // RET;

}

void Phone_CallerTextbox(void){
    // hlcoord(0, 0, wTilemap);
    // LD_B(2);
    // LD_C(SCREEN_WIDTH - 2);
    // CALL(aTextbox);
    // RET;
    return Textbox(coord(0, 0, wram->wTilemap), 2, SCREEN_WIDTH - 2);
}

void GetCallerClassAndName(uint8_t* de, uint8_t b){
    // LD_H_D;
    // LD_L_E;
    // LD_A_B;
    // CALL(aGetCallerTrainerClass);
    struct TrainerId tid = GetCallerTrainerClass(b);
    // CALL(aGetCallerName);
    // RET;
    return GetCallerName(de, tid);
}

bool CheckCanDeletePhoneNumber(uint8_t c){
    // LD_A_C;
    // CALL(aGetCallerTrainerClass);
    struct TrainerId tid = GetCallerTrainerClass(c);
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

struct TrainerId GetCallerTrainerClass(uint8_t caller){
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

void GetCallerName(uint8_t* hl, struct TrainerId c){
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
    uint8_t* name = GetTrainerName(c.trainerId, c.trainerClass);
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aPlaceString);
    struct TextPrintState state = {.de = name, .hl = hl};
    PlaceString(&state, hl);
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
    PlaceStringSimple(GetTrainerClassName(c.trainerClass), hl);
    // RET;
}

// void Phone_GetTrainerName(void){
//     PUSH_HL;
//     PUSH_BC;
//     FARCALL(aGetTrainerName);
//     POP_BC;
//     POP_HL;
//     RET;

// }

// void Phone_GetTrainerClassName(void){
//     PUSH_HL;
//     PUSH_BC;
//     FARCALL(aGetTrainerClassName);
//     POP_BC;
//     POP_HL;
//     RET;

// }

struct CallerLocation GetCallerLocation(void){
    // LD_A_addr(wCurCaller);
    // CALL(aGetCallerTrainerClass);
    struct TrainerId tr = GetCallerTrainerClass(wram->wCurCaller);
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
    uint8_t landmark = GetWorldMapLocation(mgroup, mnum);
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

const txt_cmd_s PhoneOutOfAreaText[] = {
    text_far(v_PhoneOutOfAreaText)
    text_end
};

bool PhoneScript_JustTalkToThem(script_s* s){
    SCRIPT_BEGIN
    writetext(PhoneJustTalkToThemText);
    s_end
    SCRIPT_END
}

const txt_cmd_s PhoneJustTalkToThemText[] = {
    text_far(v_PhoneJustTalkToThemText)
    text_end
};

bool PhoneThankYouTextScript(script_s* s){
//  //  unreferenced
    SCRIPT_BEGIN
    writetext(PhoneThankYouText)
    SCRIPT_END
}

const txt_cmd_s PhoneThankYouText[] = {
    text_far(v_PhoneThankYouText)
    text_end
};


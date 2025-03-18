#include "../constants.h"
#include "predef.h"

#define add_predef(name) a##name

const uint32_t PredefPointers[] = {
    add_predef(LearnMove),
    add_predef(DummyPredef1),
    add_predef(HealParty),  // this is both a special and a predef
    add_predef(SmallFarFlagAction),
    add_predef(ComputeHPBarPixels),
    add_predef(FillPP),
    add_predef(TryAddMonToParty),
    add_predef(AddTempmonToParty),
    add_predef(SendGetMonIntoFromBox),
    add_predef(SendMonIntoBox),
    add_predef(GiveEgg),
    add_predef(AnimateHPBar),
    add_predef(CalcMonStats),
    add_predef(CalcMonStatC),
    add_predef(CanLearnTMHMMove),
    add_predef(GetTMHMMove),
    add_predef(LinkTextboxAtHL),
    add_predef(PrintMoveDescription),
    add_predef(UpdatePlayerHUD),
    add_predef(PlaceGraphic),
    add_predef(CheckPlayerPartyForFitMon),
    add_predef(UpdateEnemyHUD),
    add_predef(StartBattle),
    add_predef(FillInExpBar),
    add_predef(GetBattleMonBackpic),
    add_predef(GetEnemyMonFrontpic),
    add_predef(LearnLevelMoves),
    add_predef(FillMoves),
    add_predef(EvolveAfterBattle),
    add_predef(TradeAnimationPlayer2),
    add_predef(TradeAnimation),
    add_predef(CopyMonToTempMon),
    add_predef(ListMoves),
    add_predef(PlaceNonFaintStatus),
    add_predef(Unused_PlaceEnemyHPLevel),
    add_predef(ListMovePP),
    add_predef(GetGender),
    add_predef(StatsScreenInit),
    add_predef(DrawPlayerHP),
    add_predef(DrawEnemyHP),
    add_predef(PrintTempMonStats),
    add_predef(GetTypeName),
    add_predef(PrintMoveType),
    add_predef(PrintType),
    add_predef(PrintMonTypes),
    add_predef(GetUnownLetter),
    add_predef(LoadPoisonBGPals),
    add_predef(DummyPredef2F),
    add_predef(InitSGBBorder),
    add_predef(LoadSGBLayout),
    add_predef(Pokedex_GetArea),
    add_predef(Unused_CheckShininess),
    add_predef(DoBattleTransition),
    add_predef(DummyPredef35),
    add_predef(DummyPredef36),
    add_predef(PlayBattleAnim),
    add_predef(DummyPredef38),
    add_predef(DummyPredef39),
    add_predef(DummyPredef3A),
    add_predef(PartyMonItemName),
    add_predef(GetMonFrontpic),
    add_predef(GetMonBackpic),
    add_predef(GetAnimatedFrontpic),
    add_predef(GetTrainerPic),
    add_predef(DecompressGet2bpp),
    add_predef(CheckTypeMatchup),
    add_predef(ConvertMon_1to2),
    add_predef(NewPokedexEntry),
    add_predef(Unused_AnimateMon_Slow_Normal),
    add_predef(PlaceStatusString),
    add_predef(LoadMonAnimation),
    add_predef(AnimateFrontpic),
    add_predef(Unused_HOF_AnimateAlignedFrontpic),
    add_predef(HOF_AnimateFrontpic),
};

void Predef(void) {
        //  Call predefined function a.
    //  Preserves bc, de, hl and f.
    uint8_t predefId = REG_A;
    LD_addr_A(wPredefID);  // ld [wPredefID], a
    LDH_A_addr(hROMBank);  // ldh a, [hROMBank]
    PUSH_AF;               // push af

    //  Save hl for later (back in Predef)
    LD_A_H;                    // ld a, h
    LD_addr_A(wPredefHL);      // ld [wPredefHL], a
    LD_A_L;                    // ld a, l
    LD_addr_A(wPredefHL + 1);  // ld [wPredefHL + 1], a
    REG_HL = (PredefPointers[predefId] & 0x3FFF) | 0x4000;
    LD_A_L;                                // ld a, [hli]
    LD_addr_A(wPredefAddress + 1);         // ld [wPredefAddress + 1], a
    LD_A_H;                                // ld a, [hli]
    LD_addr_A(wPredefAddress);             // ld [wPredefAddress], a
    LD_A(BANK(PredefPointers[predefId]));  // ld a, [hl]

    //  Switch to the new function's bank
    Bankswitch(REG_A);

    //  Get hl back
    LD_A_addr(wPredefHL);        // ld a, [wPredefHL]
    LD_H_A;                      // ld h, a
    LD_A_addr(wPredefHL + 1);    // ld a, [wPredefHL + 1]
    LD_L_A;                      // ld l, a
    SET_PC(aPredef_Return - 3);  // -3 for call
    CALL((PredefPointers[predefId] & 0x3FFF) | 0x4000);
    Predef_Return();
}

void Predef_Return(void) {
        //  Clean up after the Predef call
    LD_A_H;                    // ld a, h
    LD_addr_A(wPredefHL);      // ld [wPredefHL], a
    LD_A_L;                    // ld a, l
    LD_addr_A(wPredefHL + 1);  // ld [wPredefHL + 1], a

    POP_HL;  // pop hl
    LD_A_H;  // ld a, h
    Bankswitch(REG_A);

    LD_A_addr(wPredefHL);      // ld a, [wPredefHL]
    LD_H_A;                    // ld h, a
    LD_A_addr(wPredefHL + 1);  // ld a, [wPredefHL + 1]
    LD_L_A;                    // ld l, a
    RET;                       // ret
}

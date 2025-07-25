#include "../../constants.h"
#include "save.h"
#include "intro_menu.h"
#include "savemenu_copytilemapatonce.h"
#include "../../home/text.h"
#include "../../home/delay.h"
#include "../../home/audio.h"
#include "../../home/sram.h"
#include "../../home/copy.h"
#include "../../home/map.h"
#include "../../home/map_objects.h"
#include "../../home/menu.h"
#include "../../home/time.h"
#include "../rtc/rtc.h"
#include "../link/mystery_gift.h"
#include "../pokemon/mail.h"
#include "../../mobile/mobile_41.h"
#include "../../data/default_options.h"
#include "../../data/text/common.h"
#include "../../util/serialize.h"

struct BoxAddress {
    uint32_t address;
    uint32_t addressEnd;
};

// #define box_address(_start, _end) {((sizeof(struct {static_assert(MBANK(_start) == MBANK(_end), ""); int dummy;})) * 0) + _start, _end}
// Previous definition was too problematic for many compilers.
#define box_address(_start, _end) {_start, _end}

static const struct BoxAddress BoxAddresses[] = {
    //table_width ['5', 'BoxAddresses']
    box_address(asBox1,     asBox1End),
    box_address(asBox2,     asBox2End),
    box_address(asBox3,     asBox3End),
    box_address(asBox4,     asBox4End),
    box_address(asBox5,     asBox5End),
    box_address(asBox6,     asBox6End),
    box_address(asBox7,     asBox7End),
    box_address(asBox8,     asBox8End),
    box_address(asBox9,     asBox9End),
    box_address(asBox10,    asBox10End),
    box_address(asBox11,    asBox11End),
    box_address(asBox12,    asBox12End),
    box_address(asBox13,    asBox13End),
    box_address(asBox14,    asBox14End),
};
static_assert(lengthof(BoxAddresses) == NUM_BOXES, "");

bool SaveMenu(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // FARCALL(aDisplaySaveInfoOnSave);
    DisplaySaveInfoOnSave();
    // CALL(aSpeechTextbox);
    SpeechTextbox();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // FARCALL(aSaveMenu_CopyTilemapAtOnce);
    SaveMenu_CopyTilemapAtOnce();
    // LD_HL(mWouldYouLikeToSaveTheGameText);
    // CALL(aSaveTheGame_yesorno);
    // IF_NZ goto refused;
    if(SaveTheGame_yesorno(WouldYouLikeToSaveTheGameText)) {
        // CALL(aAskOverwriteSaveFile);
        // IF_C goto refused;
        if(AskOverwriteSaveFile()) {
            // CALL(aPauseGameLogic);
            PauseGameLogic();
            // CALL(av_SavingDontTurnOffThePower);
            v_SavingDontTurnOffThePower();
            // CALL(aResumeGameLogic);
            ResumeGameLogic();
            // CALL(aExitMenu);
            ExitMenu();
            // AND_A_A;
            // RET;
            return true;
        }
    }

// refused:
    // CALL(aExitMenu);
    ExitMenu();
    // CALL(aGSReloadPalettes);
    // FARCALL(aSaveMenu_CopyTilemapAtOnce);
    SaveMenu_CopyTilemapAtOnce();
    // SCF;
    // RET;
    return false;
}

void SaveAfterLinkTrade(void){
    // CALL(aPauseGameLogic);
    PauseGameLogic();
    // FARCALL(aStageRTCTimeForSave);
    StageRTCTimeForSave();
    // FARCALL(aBackupMysteryGift);
    BackupMysteryGift();
    // CALL(aSavePokemonData);
    SavePokemonData();
    // CALL(aSaveChecksum);
    SaveChecksum();
    // CALL(aSaveBackupPokemonData);
    SaveBackupPokemonData();
    // CALL(aSaveBackupChecksum);
    SaveBackupChecksum();
    // FARCALL(aBackupPartyMonMail);
    BackupPartyMonMail();
    // FARCALL(aSaveRTC);
    SaveRTC();
    // CALL(aResumeGameLogic);
    ResumeGameLogic();
    // RET;
}

void ChangeBoxSaveGame(uint8_t box){
    // PUSH_DE;
    // LD_HL(mChangeBoxSaveText);
    // CALL(aMenuTextbox);
    MenuTextbox(ChangeBoxSaveText);
    // CALL(aYesNoBox);
    bool yes = YesNoBox();
    // CALL(aExitMenu);
    ExitMenu();
    // IF_C goto refused;
    // CALL(aAskOverwriteSaveFile);
    // IF_C goto refused;
    if(yes && AskOverwriteSaveFile()) {
        // CALL(aPauseGameLogic);
        PauseGameLogic();
        // CALL(aSavingDontTurnOffThePower);
        SavingDontTurnOffThePower();
        // CALL(aSaveBox);
        SaveBox();
        // POP_DE;
        // LD_A_E;
        // LD_addr_A(wCurBox);
        gPlayer.curBox = box;
        // CALL(aLoadBox);
        LoadBox();
        // CALL(aSavedTheGame);
        SavedTheGame();
        // CALL(aResumeGameLogic);
        ResumeGameLogic();
        // AND_A_A;
        // RET;
        return;
    }

// refused:
    // POP_DE;
    // RET;
}

// Asks to save the game.
// Returns true if saved, false if refused.
bool Link_SaveGame(void){
    // CALL(aAskOverwriteSaveFile);
    // IF_C goto refused;
    if(AskOverwriteSaveFile()) {
        // CALL(aPauseGameLogic);
        PauseGameLogic();
        // CALL(av_SavingDontTurnOffThePower);
        v_SavingDontTurnOffThePower();
        // CALL(aResumeGameLogic);
        ResumeGameLogic();
        // AND_A_A;
        return true;
    }

// refused:
    // RET;
    return false;
}

void MoveMonWOMail_SaveGame(uint8_t e){
    // CALL(aPauseGameLogic);
    PauseGameLogic();
    // PUSH_DE;
    // CALL(aSaveBox);
    SaveBox();
    // POP_DE;
    // LD_A_E;
    // LD_addr_A(wCurBox);
    gPlayer.curBox = e;
    // CALL(aLoadBox);
    LoadBox();
    // CALL(aResumeGameLogic);
    ResumeGameLogic();
    // RET;
}

void MoveMonWOMail_InsertMon_SaveGame(uint8_t e){
    // CALL(aPauseGameLogic);
    PauseGameLogic();
    // PUSH_DE;
    // CALL(aSaveBox);
    SaveBox();
    // POP_DE;
    // LD_A_E;
    // LD_addr_A(wCurBox);
    gPlayer.curBox = e;
    // LD_A(TRUE);
    // LD_addr_A(wSaveFileExists);
    gOptions.saveFileExists = TRUE;
    // FARCALL(aStageRTCTimeForSave);
    StageRTCTimeForSave();
    // FARCALL(aBackupMysteryGift);
    BackupMysteryGift();
    // CALL(aValidateSave);
    ValidateSave();
    // CALL(aSaveOptions);
    SaveOptions();
    // CALL(aSavePlayerData);
    SavePlayerData();
    // CALL(aSavePokemonData);
    SavePokemonData();
    // CALL(aSaveChecksum);
    SaveChecksum();
    // CALL(aValidateBackupSave);
    ValidateBackupSave();
    // CALL(aSaveBackupOptions);
    SaveBackupOptions();
    // CALL(aSaveBackupPlayerData);
    SaveBackupPlayerData();
    // CALL(aSaveBackupPokemonData);
    SaveBackupPokemonData();
    // CALL(aSaveBackupChecksum);
    SaveBackupChecksum();
    // FARCALL(aBackupPartyMonMail);
    BackupPartyMonMail();
    // FARCALL(aBackupMobileEventIndex);
    BackupMobileEventIndex();
    // FARCALL(aSaveRTC);
    SaveRTC();
    // CALL(aLoadBox);
    LoadBox();
    // CALL(aResumeGameLogic);
    ResumeGameLogic();
    // LD_DE(SFX_SAVE);
    // CALL(aPlaySFX);
    PlaySFX(SFX_SAVE);
    // LD_C(24);
    // CALL(aDelayFrames);
    DelayFrames(24);
    // RET;
}

bool StartMoveMonWOMail_SaveGame(void){
    // LD_HL(mMoveMonWOMailSaveText);
    // CALL(aMenuTextbox);
    MenuTextbox(MoveMonWOMailSaveText);
    // CALL(aYesNoBox);
    bool yes = YesNoBox();
    // CALL(aExitMenu);
    ExitMenu();
    // IF_C goto refused;
    // CALL(aAskOverwriteSaveFile);
    // IF_C goto refused;
    if(yes && AskOverwriteSaveFile()) {
        // CALL(aPauseGameLogic);
        PauseGameLogic();
        // CALL(av_SavingDontTurnOffThePower);
        v_SavingDontTurnOffThePower();
        // CALL(aResumeGameLogic);
        ResumeGameLogic();
        // AND_A_A;
        // RET;
        return true;
    }

// refused:
    // SCF;
    // RET;
    return false;
}

void PauseGameLogic(void){
    // LD_A(TRUE);
    // LD_addr_A(wGameLogicPaused);
    wram->wGameLogicPaused = TRUE;
    // RET;
}

void ResumeGameLogic(void){
    // XOR_A_A;  // FALSE
    // LD_addr_A(wGameLogicPaused);
    wram->wGameLogicPaused = FALSE;
    // RET;
}

void AddHallOfFameEntry(void){
    // LD_A(BANK(sHallOfFame));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asHallOfFame));
    // LD_HL(sHallOfFame + HOF_LENGTH * (NUM_HOF_TEAMS - 1) - 1);
    uint16_t hl = sHallOfFame + HOF_LENGTH * (NUM_HOF_TEAMS - 1) - 1;
    // LD_DE(sHallOfFame + HOF_LENGTH * NUM_HOF_TEAMS - 1);
    uint16_t de = sHallOfFame + HOF_LENGTH * NUM_HOF_TEAMS - 1;
    // LD_BC(HOF_LENGTH * (NUM_HOF_TEAMS - 1));
    uint16_t bc = HOF_LENGTH * (NUM_HOF_TEAMS - 1);

    do {
    // loop:
        // LD_A_hld;
        // LD_de_A;
        // DEC_DE;
        gb_write(de--, gb_read(hl--));
        // DEC_BC;
        // LD_A_C;
        // OR_A_B;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // LD_HL(wHallOfFamePokemonList);
    // LD_DE(sHallOfFame);
    // LD_BC(wHallOfFamePokemonListEnd - wHallOfFamePokemonList + 1);
    // CALL(aCopyBytes);
    CopyBytes_GB(sHallOfFame, wHallOfFamePokemonList, wHallOfFamePokemonListEnd - wHallOfFamePokemonList + 1);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void SaveGameData(void){
    // CALL(av_SaveGameData);
    v_SaveGameData();
    // RET;
}

bool AskOverwriteSaveFile(void){
    // LD_A_addr(wSaveFileExists);
    // AND_A_A;
    // IF_Z goto erase;
    if(gOptions.saveFileExists) {
        // CALL(aCompareLoadedAndSavedPlayerID);
        // IF_Z goto yoursavefile;
        if(CompareLoadedAndSavedPlayerID()) {
        // yoursavefile:
            // LD_HL(mAlreadyASaveFileText);
            // CALL(aSaveTheGame_yesorno);
            if(!SaveTheGame_yesorno(AlreadyASaveFileText))
            // IF_NZ goto refused;
                return false;
            // goto ok;
            return true;
        }
        // LD_HL(mAnotherSaveFileText);
        // CALL(aSaveTheGame_yesorno);
        // IF_NZ goto refused;
        if(!SaveTheGame_yesorno(AnotherSaveFileText))
            return false;
        // goto erase;
    }

// erase:
    // CALL(aErasePreviousSave);
    ErasePreviousSave();

// ok:
    // AND_A_A;
    // RET;
    return true;

// refused:
    // SCF;
    // RET;
}

bool SaveTheGame_yesorno(const txt_cmd_s* hl){
    // LD_B(BANK(aWouldYouLikeToSaveTheGameText));
    // CALL(aMapTextbox);
    MapTextbox(hl);
    // CALL(aLoadMenuTextbox);
    LoadMenuTextbox();
    // LD_BC((0 << 8) | 7);
    // CALL(aPlaceYesNoBox);
    v_YesNoBox(0, 7);
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // CALL(aCloseWindow);
    CloseWindow();
    // PUSH_AF;
    // CALL(aGSReloadPalettes);
    // POP_AF;
    // AND_A_A;
    // RET;
    return wram->wMenuCursorY == 1;
}

bool CompareLoadedAndSavedPlayerID(void){
    // LD_A(BANK(sPlayerData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asPlayerData));
    // LD_HL(sPlayerData + (wPlayerID - wPlayerData));
    // LD_A_hli;
    // LD_C_hl;
    // LD_B_A;
    // uint16_t bc = (gb_read(sPlayerData + (wPlayerID - wPlayerData)))
    //     | (gb_read(sPlayerData + (wPlayerID - wPlayerData) + 1) << 8);
    struct PlayerData pd;
    Deserialize_PlayerData(&pd, (const uint8_t *)GBToRAMAddr(sPlayerData));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A_addr(wPlayerID);
    // CP_A_B;
    // RET_NZ ;
    // LD_A_addr(wPlayerID + 1);
    // CP_A_C;
    // RET;
    return gPlayer.playerID == pd.playerID;
}

void v_SavingDontTurnOffThePower(void){
    // CALL(aSavingDontTurnOffThePower);
    SavingDontTurnOffThePower();
    return SavedTheGame();
}

void SavedTheGame(void){
    // CALL(av_SaveGameData);
    v_SaveGameData();
// wait 32 frames
    // LD_C(32);
    // CALL(aDelayFrames);
    // DelayFrames(32);
// copy the original text speed setting to the stack
    // LD_A_addr(wOptions);
    // PUSH_AF;
    uint8_t options = gOptions.options;
// set text speed to medium
    // LD_A(TEXT_DELAY_MED);
    // LD_addr_A(wOptions);
    gOptions.options = TEXT_DELAY_FAST;
// <PLAYER> saved the game!
    // LD_HL(mSavedTheGameText);
    // CALL(aPrintText);
    PrintText(SavedTheGameText);
// restore the original text speed setting
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
    // LD_DE(SFX_SAVE);
    // CALL(aWaitPlaySFX);
    WaitPlaySFX(SFX_SAVE);
    // CALL(aWaitSFX);
    WaitSFX();
// wait 30 frames
    // LD_C(30);
    // CALL(aDelayFrames);
    DelayFrames(30);
    // RET;
}

void v_SaveGameData(void){
    // LD_A(TRUE);
    // LD_addr_A(wSaveFileExists);
    gOptions.saveFileExists = TRUE;
    // FARCALL(aStageRTCTimeForSave);
    StageRTCTimeForSave();
    // FARCALL(aBackupMysteryGift);
    BackupMysteryGift();
    // CALL(aValidateSave);
    ValidateSave();
    // CALL(aSaveOptions);
    SaveOptions();
    // CALL(aSavePlayerData);
    SavePlayerData();
    // CALL(aSavePokemonData);
    SavePokemonData();
    // CALL(aSaveBox);
    SaveBox();
    // CALL(aSaveChecksum);
    SaveChecksum();
    // CALL(aValidateBackupSave);
    ValidateBackupSave();
    // CALL(aSaveBackupOptions);
    SaveBackupOptions();
    // CALL(aSaveBackupPlayerData);
    SaveBackupPlayerData();
    // CALL(aSaveBackupPokemonData);
    SaveBackupPokemonData();
    // CALL(aSaveBackupChecksum);
    SaveBackupChecksum();
    // CALL(aUpdateStackTop);
    UpdateStackTop();
    // FARCALL(aBackupPartyMonMail);
    BackupPartyMonMail();
    // FARCALL(aBackupMobileEventIndex);
    BackupMobileEventIndex();
    // FARCALL(aSaveRTC);
    SaveRTC();
    // LD_A(BANK(sBattleTowerChallengeState));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBattleTowerChallengeState));
    // LD_A_addr(sBattleTowerChallengeState);
    uint8_t a = gb_read(sBattleTowerChallengeState);
    // CP_A(BATTLETOWER_RECEIVED_REWARD);
    // IF_NZ goto ok;
    if(a == BATTLETOWER_RECEIVED_REWARD) {
        // XOR_A_A;
        // LD_addr_A(sBattleTowerChallengeState);
        gb_write(sBattleTowerChallengeState, 0);
    }

// ok:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void UpdateStackTop(void){
//  sStackTop appears to be unused.
//  It could have been used to debug stack overflow during saving.
    // CALL(aFindStackTop);
    // LD_A(BANK(sStackTop));
    // CALL(aOpenSRAM);
    // LD_A_addr(sStackTop + 0);
    // LD_E_A;
    // LD_A_addr(sStackTop + 1);
    // LD_D_A;
    // OR_A_E;
    // IF_Z goto update;
    // LD_A_E;
    // SUB_A_L;
    // LD_A_D;
    // SBC_A_H;
    // IF_C goto done;


// update:
    // LD_A_L;
    // LD_addr_A(sStackTop + 0);
    // LD_A_H;
    // LD_addr_A(sStackTop + 1);


// done:
    // CALL(aCloseSRAM);
    // RET;

}

uint8_t* FindStackTop(void){
//  Find the furthest point that sp has traversed to.
//  This is distinct from the current value of sp.
    // LD_HL(wStackBottom);
    uint8_t* hl = wram->wStackBottom;

    do {
    // loop:
        // LD_A_hl;
        // OR_A_A;
        // RET_NZ ;
        if(*hl != 0)
            return hl;
        // INC_HL;
        // goto loop;
        hl++;
    } while(1);
}

void SavingDontTurnOffThePower(void){
// Prevent joypad interrupts
    // XOR_A_A;
    // LDH_addr_A(hJoypadReleased);
    hram.hJoypadReleased = 0;
    // LDH_addr_A(hJoypadPressed);
    hram.hJoypadPressed = 0;
    // LDH_addr_A(hJoypadSum);
    hram.hJoypadSum = 0;
    // LDH_addr_A(hJoypadDown);
    hram.hJoypadDown = 0;
// Save the text speed setting to the stack
    // LD_A_addr(wOptions);
    // PUSH_AF;
    uint8_t options = gOptions.options;
// Set the text speed to medium
    // LD_A(TEXT_DELAY_MED);
    // LD_addr_A(wOptions);
    // gOptions.options = TEXT_DELAY_FAST;
// SAVING... DON'T TURN OFF THE POWER.
    // LD_HL(mSavingDontTurnOffThePowerText);
    // CALL(aPrintText);
    // PrintText(SavingDontTurnOffThePowerText);
// Restore the text speed setting
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
// Wait for 16 frames
    // LD_C(16);
    // CALL(aDelayFrames);
    // DelayFrames(16);
    // RET;
}

void ErasePreviousSave(void){
    // CALL(aEraseBoxes);
    EraseBoxes();
    // CALL(aEraseHallOfFame);
    EraseHallOfFame();
    // CALL(aEraseLinkBattleStats);
    EraseLinkBattleStats();
    // CALL(aEraseMysteryGift);
    EraseMysteryGift();
    // CALL(aSaveData);
    SaveData();
    // CALL(aEraseBattleTowerStatus);
    EraseBattleTowerStatus();
    // LD_A(BANK(sStackTop));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asStackTop));
    // XOR_A_A;
    // LD_addr_A(sStackTop + 0);
    // LD_addr_A(sStackTop + 1);
    gb_write16(sStackTop, 0);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A(0x1);
    // LD_addr_A(wSavedAtLeastOnce);
    gPlayer.savedAtLeastOnce = 0x1;
    // RET;
}

void EraseLinkBattleStats(void){
    // LD_A(BANK(sLinkBattleStats));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asLinkBattleStats));
    // LD_HL(sLinkBattleStats);
    // LD_BC(sLinkBattleStatsEnd - sLinkBattleStats);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_GB(sLinkBattleStats, sLinkBattleStatsEnd - sLinkBattleStats, 0);
    // JP(mCloseSRAM);
    CloseSRAM();
}

void EraseMysteryGift(void){
    // LD_A(BANK(sBackupMysteryGiftItem));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBackupMysteryGiftItem));
    // LD_HL(sBackupMysteryGiftItem);
    // LD_BC(sBackupMysteryGiftItemEnd - sBackupMysteryGiftItem);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_GB(sBackupMysteryGiftItem, sBackupMysteryGiftItemEnd - sBackupMysteryGiftItem, 0);
    // JP(mCloseSRAM);
    CloseSRAM();
}

void EraseHallOfFame(void){
    // LD_A(BANK(sHallOfFame));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asHallOfFame));
    // LD_HL(sHallOfFame);
    // LD_BC(sHallOfFameEnd - sHallOfFame);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_GB(sHallOfFame, sHallOfFameEnd - sHallOfFame, 0);
    // JP(mCloseSRAM);
    return CloseSRAM();
}

void Function14d18(void){
//  //  unreferenced
    LD_A(BANK(s4_a007));  // MBC30 bank used by JP Crystal// inaccessible by MBC3
    CALL(aOpenSRAM);
    LD_HL(mFunction14d18_Data);
    LD_DE(s4_a007);
    LD_BC(4 * 12);
    CALL(aCopyBytes);
    JP(mCloseSRAM);


Data:
    //db ['0x0d', '0x02', '0x00', '0x05', '0x00', '0x00', '0x22', '0x02', '0x01', '0x05', '0x00', '0x00'];
    //db ['0x03', '0x04', '0x05', '0x08', '0x03', '0x05', '0x0e', '0x06', '0x03', '0x02', '0x00', '0x00'];
    //db ['0x39', '0x07', '0x07', '0x04', '0x00', '0x05', '0x04', '0x07', '0x01', '0x05', '0x00', '0x00'];
    //db ['0x0f', '0x05', '0x14', '0x07', '0x05', '0x05', '0x11', '0x0c', '0x0c', '0x06', '0x06', '0x04'];

    return EraseBattleTowerStatus();
}

void EraseBattleTowerStatus(void){
    // LD_A(BANK(sBattleTowerChallengeState));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBattleTowerChallengeState));
    // XOR_A_A;
    // LD_addr_A(sBattleTowerChallengeState);
    gb_write(sBattleTowerChallengeState, 0);
    // JP(mCloseSRAM);
    CloseSRAM();
}

void SaveData(void){
    // CALL(av_SaveData);
    v_SaveData();
    // RET;
}

void Function14d6c(void){
//  //  unreferenced
    LD_A(BANK(s4_a60b));  // MBC30 bank used by JP Crystal// inaccessible by MBC3
    CALL(aOpenSRAM);
    LD_A_addr(s4_a60b);  // address of MBC30 bank
    LD_B(0x0);
    AND_A_A;
    IF_Z goto ok;
    LD_B(0x2);


ok:
    LD_A_B;
    LD_addr_A(s4_a60b);  // address of MBC30 bank
    CALL(aCloseSRAM);
    RET;

}

void Function14d83(void){
//  //  unreferenced
    LD_A(BANK(s4_a60c));  // aka BANK(s4_a60d) // MBC30 bank used by JP Crystal// inaccessible by MBC3
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_addr_A(s4_a60c);  // address of MBC30 bank
    LD_addr_A(s4_a60d);  // address of MBC30 bank
    CALL(aCloseSRAM);
    RET;

}

void Function14d93(void){
//  //  unreferenced
    LD_A(BANK(s7_a000));  // MBC30 bank used by JP Crystal// inaccessible by MBC3
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_addr_A(s7_a000);  // address of MBC30 bank
    CALL(aCloseSRAM);
    RET;

}

void HallOfFame_InitSaveIfNeeded(void){
    // LD_A_addr(wSavedAtLeastOnce);
    // AND_A_A;
    // RET_NZ ;
    if(gPlayer.savedAtLeastOnce)
        return;
    // CALL(aErasePreviousSave);
    ErasePreviousSave();
    // RET;
}

void ValidateSave(void){
    // LD_A(BANK(sCheckValue1));  // aka BANK(sCheckValue2)
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asCheckValue1));
    // LD_A(SAVE_CHECK_VALUE_1);
    // LD_addr_A(sCheckValue1);
    gb_write(sCheckValue1, SAVE_CHECK_VALUE_1);
    // LD_A(SAVE_CHECK_VALUE_2);
    // LD_addr_A(sCheckValue2);
    gb_write(sCheckValue2, SAVE_CHECK_VALUE_2);
    // JP(mCloseSRAM);
    return CloseSRAM();
}

void SaveOptions(void){
    // LD_A(BANK(sOptions));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asOptions));
    // LD_HL(wOptions);
    // LD_DE(sOptions);
    // LD_BC(wOptionsEnd - wOptions);
    // CALL(aCopyBytes);
    Serialize_OptionsData((uint8_t*)GBToRAMAddr(sOptions), &gOptions);
    // LD_A_addr(wOptions);
    // AND_A(~(1 << NO_TEXT_SCROLL));
    // LD_addr_A(sOptions);
    gb_write(sOptions, gOptions.options & ~(1 << NO_TEXT_SCROLL));
    // JP(mCloseSRAM);
    CloseSRAM();
}

void SavePlayerData(void){
    // LD_A(BANK(sPlayerData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asPlayerData));
    // LD_HL(wPlayerData);
    // LD_DE(sPlayerData);
    // LD_BC(wPlayerDataEnd - wPlayerData);
    // CALL(aCopyBytes);
    uint8_t* dest = GBToRAMAddr(sPlayerData);
    Serialize_PlayerData(dest, &gPlayer);
    // LD_HL(wCurMapData);
    // LD_DE(sCurMapData);
    // LD_BC(wCurMapDataEnd - wCurMapData);
    // CALL(aCopyBytes);
    dest = GBToRAMAddr(sCurMapData);
    Serialize_CurMapData(dest, &gCurMapData);
    // JP(mCloseSRAM);
    CloseSRAM();
}

void SavePokemonData(void){
    // LD_A(BANK(sPokemonData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asPokemonData));
    // LD_HL(wPokemonData);
    // LD_DE(sPokemonData);
    // LD_BC(wPokemonDataEnd - wPokemonData);
    // CALL(aCopyBytes);
    Serialize_PokemonData((uint8_t*)GBToRAMAddr(sPokemonData), &gPokemon);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void SaveBox(void){
    // CALL(aGetBoxAddress);
    uint32_t de = GetBoxAddress();
    // CALL(aSaveBoxAddress);
    SaveBoxAddress(de);
    // RET;
}

void SaveChecksum(void){
    // LD_HL(sGameData);
    // LD_BC(sGameDataEnd - sGameData);
    // LD_A(BANK(sGameData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asGameData));
    // CALL(aChecksum);
    uint16_t checksum = Checksum(GBToRAMAddr(sGameData), sGameDataEnd - sGameData);
    // LD_A_E;
    // LD_addr_A(sChecksum + 0);
    // LD_A_D;
    // LD_addr_A(sChecksum + 1);
    gb_write16(sChecksum, checksum);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void ValidateBackupSave(void){
    // LD_A(BANK(sBackupCheckValue1));  // aka BANK(sBackupCheckValue2)
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBackupCheckValue1));
    // LD_A(SAVE_CHECK_VALUE_1);
    // LD_addr_A(sBackupCheckValue1);
    gb_write(sBackupCheckValue1, SAVE_CHECK_VALUE_1);
    // LD_A(SAVE_CHECK_VALUE_2);
    // LD_addr_A(sBackupCheckValue2);
    gb_write(sBackupCheckValue2, SAVE_CHECK_VALUE_2);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void SaveBackupOptions(void){
    // LD_A(BANK(sBackupOptions));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBackupOptions));
    // LD_HL(wOptions);
    // LD_DE(sBackupOptions);
    // LD_BC(wOptionsEnd - wOptions);
    // CALL(aCopyBytes);
    Serialize_OptionsData((uint8_t*)GBToRAMAddr(sBackupOptions), &gOptions);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void SaveBackupPlayerData(void){
    // LD_A(BANK(sBackupPlayerData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBackupPlayerData));
    // LD_HL(wPlayerData);
    // LD_DE(sBackupPlayerData);
    // LD_BC(wPlayerDataEnd - wPlayerData);
    // CALL(aCopyBytes);
    uint8_t* dest = GBToRAMAddr(sBackupPlayerData);
    Serialize_PlayerData(dest, &gPlayer);
    // LD_HL(wCurMapData);
    // LD_DE(sBackupCurMapData);
    // LD_BC(wCurMapDataEnd - wCurMapData);
    // CALL(aCopyBytes);
    dest = GBToRAMAddr(sBackupCurMapData);
    Serialize_CurMapData(dest, &gCurMapData);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void SaveBackupPokemonData(void){
    // LD_A(BANK(sBackupPokemonData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBackupPokemonData));
    // LD_HL(wPokemonData);
    // LD_DE(sBackupPokemonData);
    // LD_BC(wPokemonDataEnd - wPokemonData);
    // CALL(aCopyBytes);
    CopyBytes_GB(sBackupPokemonData, wPokemonData, wPokemonDataEnd - wPokemonData);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void SaveBackupChecksum(void){
    // LD_HL(sBackupGameData);
    // LD_BC(sBackupGameDataEnd - sBackupGameData);
    // LD_A(BANK(sBackupGameData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBackupGameData));
    // CALL(aChecksum);
    uint16_t checksum = Checksum(GBToRAMAddr(sBackupGameData), sBackupGameDataEnd - sBackupGameData);
    // LD_A_E;
    // LD_addr_A(sBackupChecksum + 0);
    // LD_A_D;
    // LD_addr_A(sBackupChecksum + 1);
    gb_write16(sBackupChecksum, checksum);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

// Tries to load the save file.
// Returns true on success, false on corruption.
bool TryLoadSaveFile(void){
    // CALL(aVerifyChecksum);
    // IF_NZ goto backup;
    if(VerifyChecksum()) {
        // CALL(aLoadPlayerData);
        LoadPlayerData();
        // CALL(aLoadPokemonData);
        LoadPokemonData();
        // CALL(aLoadBox);
        LoadBox();
        // FARCALL(aRestorePartyMonMail);
        RestorePartyMonMail();
        // FARCALL(aRestoreMobileEventIndex);
        RestoreMobileEventIndex();
        // FARCALL(aRestoreMysteryGift);
        RestoreMysteryGift();
        // CALL(aValidateBackupSave);
        ValidateBackupSave();
        // CALL(aSaveBackupOptions);
        SaveBackupOptions();
        // CALL(aSaveBackupPlayerData);
        SaveBackupPlayerData();
        // CALL(aSaveBackupPokemonData);
        SaveBackupPokemonData();
        // CALL(aSaveBackupChecksum);
        SaveBackupChecksum();
        // AND_A_A;
        // RET;
        return true;
    }

// backup:
    // CALL(aVerifyBackupChecksum);
    // IF_NZ goto corrupt;
    if(VerifyBackupChecksum()) {
        // CALL(aLoadBackupPlayerData);
        LoadBackupPlayerData();
        // CALL(aLoadBackupPokemonData);
        LoadBackupPokemonData();
        // CALL(aLoadBox);
        LoadBox();
        // FARCALL(aRestorePartyMonMail);
        RestorePartyMonMail();
        // FARCALL(aRestoreMobileEventIndex);
        RestoreMobileEventIndex();
        // FARCALL(aRestoreMysteryGift);
        RestoreMysteryGift();
        // CALL(aValidateSave);
        ValidateSave();
        // CALL(aSaveOptions);
        SaveOptions();
        // CALL(aSavePlayerData);
        SavePlayerData();
        // CALL(aSavePokemonData);
        SavePokemonData();
        // CALL(aSaveChecksum);
        SaveChecksum();
        // AND_A_A;
        // RET;
        return true;
    }

// corrupt:
    // LD_A_addr(wOptions);
    // PUSH_AF;
    uint8_t options = gOptions.options;
    // SET_A(NO_TEXT_SCROLL);
    // LD_addr_A(wOptions);
    bit_set(gOptions.options, NO_TEXT_SCROLL);
    // LD_HL(mSaveFileCorruptedText);
    // CALL(aPrintText);
    PrintText(SaveFileCorruptedText);
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
    // SCF;
    // RET;
    return false;
}

void TryLoadSaveData(void){
    PEEK("");
    struct PlayerData pd;
    // XOR_A_A;  // FALSE
    // LD_addr_A(wSaveFileExists);
    gOptions.saveFileExists = FALSE;
    // CALL(aCheckPrimarySaveFile);
    CheckPrimarySaveFile();
    // LD_A_addr(wSaveFileExists);
    // AND_A_A;
    // IF_Z goto backup;
    if(gOptions.saveFileExists) {
        // LD_A(BANK(sPlayerData));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asPlayerData));
        Deserialize_PlayerData(&pd, (const uint8_t *)GBToRAMAddr(sPlayerData));
        // LD_HL(sPlayerData + wStartDay - wPlayerData);
        // LD_DE(wStartDay);
        // LD_BC(8);
        // CALL(aCopyBytes);
        // CopyBytes_GB(wStartDay, sPlayerData + wStartDay - wPlayerData, 8);
        CopyBytes(&gPlayer.startDay, &pd.startDay, 8);
        // LD_HL(sPlayerData + wStatusFlags - wPlayerData);
        // LD_DE(wStatusFlags);
        // LD_A_hl;
        // LD_de_A;
        gPlayer.statusFlags = pd.statusFlags;
        // CALL(aCloseSRAM);
        CloseSRAM();
        // RET;
        return;
    }

// backup:
    // CALL(aCheckBackupSaveFile);
    CheckBackupSaveFile();
    // LD_A_addr(wSaveFileExists);
    // AND_A_A;
    // IF_Z goto corrupt;
    if(gOptions.saveFileExists) {
        // LD_A(BANK(sBackupPlayerData));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asBackupPlayerData));
        Deserialize_PlayerData(&pd, (const uint8_t *)GBToRAMAddr(sBackupPlayerData));
        // LD_HL(sBackupPlayerData + wStartDay - wPlayerData);
        // LD_DE(wStartDay);
        // LD_BC(8);
        // CALL(aCopyBytes);
        // CopyBytes_GB(wStartDay, sBackupPlayerData + wStartDay - wPlayerData, 8);
        CopyBytes(&gPlayer.startDay, &pd.startDay, 8);
        // LD_HL(sBackupPlayerData + wStatusFlags - wPlayerData);
        // LD_DE(wStatusFlags);
        // LD_A_hl;
        // LD_de_A;
        gPlayer.statusFlags = pd.statusFlags;
        // CALL(aCloseSRAM);
        CloseSRAM();
        // RET;
        return;
    }

// corrupt:
    // LD_HL(mDefaultOptions);
    // LD_DE(wOptions);
    // LD_BC(wOptionsEnd - wOptions);
    // CALL(aCopyBytes);
    CopyBytes(&gOptions.options, &DefaultOptions, sizeof(gOptions));
    // CALL(aClearClock);
    ClearClock();
    // RET;

// INCLUDE "data/default_options.asm"
}

void CheckPrimarySaveFile(void){
    // LD_A(BANK(sCheckValue1));  // aka BANK(sCheckValue2)
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asCheckValue1));
    // LD_A_addr(sCheckValue1);
    // CP_A(SAVE_CHECK_VALUE_1);
    // IF_NZ goto nope;
    // LD_A_addr(sCheckValue2);
    // CP_A(SAVE_CHECK_VALUE_2);
    // IF_NZ goto nope;
    if(gb_read(sCheckValue1) == SAVE_CHECK_VALUE_1
    && gb_read(sCheckValue2) == SAVE_CHECK_VALUE_2) {
        // LD_HL(sOptions);
        // LD_DE(wOptions);
        // LD_BC(wOptionsEnd - wOptions);
        // CALL(aCopyBytes);
        Deserialize_OptionsData(&gOptions, (const uint8_t*)GBToRAMAddr(sOptions));
        // CALL(aCloseSRAM);
        // LD_A(TRUE);
        // LD_addr_A(wSaveFileExists);
        gOptions.saveFileExists = TRUE;
    }


// nope:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void CheckBackupSaveFile(void){
    // LD_A(BANK(sBackupCheckValue1));  // aka BANK(sBackupCheckValue2)
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBackupCheckValue1));
    // LD_A_addr(sBackupCheckValue1);
    // CP_A(SAVE_CHECK_VALUE_1);
    // IF_NZ goto nope;
    // LD_A_addr(sBackupCheckValue2);
    // CP_A(SAVE_CHECK_VALUE_2);
    // IF_NZ goto nope;
    if(gb_read(sBackupCheckValue1) == SAVE_CHECK_VALUE_1
    && gb_read(sBackupCheckValue2) == SAVE_CHECK_VALUE_2) {
        // LD_HL(sBackupOptions);
        // LD_DE(wOptions);
        // LD_BC(wOptionsEnd - wOptions);
        // CALL(aCopyBytes);
        Deserialize_OptionsData(&gOptions, (const uint8_t*)GBToRAMAddr(sBackupOptions));
        // LD_A(0x2);
        // LD_addr_A(wSaveFileExists);
        gOptions.saveFileExists = 0x2;
    }

// nope:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void LoadPlayerData(void){
    // LD_A(BANK(sPlayerData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asPlayerData));
    // LD_HL(sPlayerData);
    // LD_DE(wPlayerData);
    // LD_BC(wPlayerDataEnd - wPlayerData);
    // CALL(aCopyBytes);
    const uint8_t* src = GBToRAMAddr(sPlayerData);
    Deserialize_PlayerData(&gPlayer, src);
    // LD_HL(sCurMapData);
    // LD_DE(wCurMapData);
    // LD_BC(wCurMapDataEnd - wCurMapData);
    // CALL(aCopyBytes);
    src = GBToRAMAddr(sCurMapData);
    Deserialize_CurMapData(&gCurMapData, src);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A(BANK(sBattleTowerChallengeState));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBattleTowerChallengeState));
    // LD_A_addr(sBattleTowerChallengeState);
    // CP_A(BATTLETOWER_RECEIVED_REWARD);
    // IF_NZ goto not_4;
    if(gb_read(sBattleTowerChallengeState) == BATTLETOWER_RECEIVED_REWARD) {
        // LD_A(BATTLETOWER_WON_CHALLENGE);
        // LD_addr_A(sBattleTowerChallengeState);
        gb_write(sBattleTowerChallengeState, BATTLETOWER_WON_CHALLENGE);
    }
// not_4:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void LoadPokemonData(void){
    // LD_A(BANK(sPokemonData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asPokemonData));
    // LD_HL(sPokemonData);
    // LD_DE(wPokemonData);
    // LD_BC(wPokemonDataEnd - wPokemonData);
    // CALL(aCopyBytes);
    Deserialize_PokemonData(&gPokemon, (const uint8_t*)GBToRAMAddr(sPokemonData));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void LoadBox(void){
    // CALL(aGetBoxAddress);
    uint32_t address = GetBoxAddress();
    // CALL(aLoadBoxAddress);
    LoadBoxAddress(address);
    // RET;
}

bool VerifyChecksum(void){
    // LD_HL(sGameData);
    // LD_BC(sGameDataEnd - sGameData);
    // LD_A(BANK(sGameData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asGameData));
    // CALL(aChecksum);
    uint16_t checksum = Checksum(GBToRAMAddr(sGameData), sGameDataEnd - sGameData);
    // LD_A_addr(sChecksum + 0);
    // CP_A_E;
    // IF_NZ goto fail;
    // LD_A_addr(sChecksum + 1);
    // CP_A_D;
    bool success = gb_read16(sChecksum) == checksum;

// fail:
    // PUSH_AF;
    // CALL(aCloseSRAM);
    CloseSRAM();
    // POP_AF;
    // RET;
    return success;
}

void LoadBackupPlayerData(void){
    // LD_A(BANK(sBackupPlayerData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBackupPlayerData));
    // LD_HL(sBackupPlayerData);
    // LD_DE(wPlayerData);
    // LD_BC(wPlayerDataEnd - wPlayerData);
    // CALL(aCopyBytes);
    const uint8_t* src = GBToRAMAddr(sBackupPlayerData);
    Deserialize_PlayerData(&gPlayer, src);
    // LD_HL(sBackupCurMapData);
    // LD_DE(wCurMapData);
    // LD_BC(wCurMapDataEnd - wCurMapData);
    // CALL(aCopyBytes);
    src = GBToRAMAddr(sBackupCurMapData);
    Deserialize_CurMapData(&gCurMapData, src);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;

}

void LoadBackupPokemonData(void){
    // LD_A(BANK(sBackupPokemonData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBackupPokemonData));
    // LD_HL(sBackupPokemonData);
    // LD_DE(wPokemonData);
    // LD_BC(wPokemonDataEnd - wPokemonData);
    // CALL(aCopyBytes);
    Deserialize_PokemonData(&gPokemon, (const uint8_t*)GBToRAMAddr(sBackupPokemonData));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;

}

bool VerifyBackupChecksum(void){
    // LD_HL(sBackupGameData);
    // LD_BC(sBackupGameDataEnd - sBackupGameData);
    // LD_A(BANK(sBackupGameData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBackupGameData));
    // CALL(aChecksum);
    uint16_t checksum = Checksum(GBToRAMAddr(sBackupGameData), sBackupGameDataEnd - sBackupGameData);
    // LD_A_addr(sBackupChecksum + 0);
    // CP_A_E;
    // IF_NZ goto fail;
    // LD_A_addr(sBackupChecksum + 1);
    // CP_A_D;
    bool success = gb_read16(sBackupChecksum) == checksum;

// fail:
    // PUSH_AF;
    // CALL(aCloseSRAM);
    CloseSRAM();
    // POP_AF;
    // RET;
    return success;
}

void v_SaveData(void){
// This is called within two scenarios:
//   a) ErasePreviousSave (the process of erasing the save from a previous game file)
//   b) unused mobile functionality
// It is not part of a regular save.

    // LD_A(BANK(sCrystalData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asCrystalData));
    // LD_HL(wCrystalData);
    // LD_DE(sCrystalData);
    // LD_BC(wCrystalDataEnd - wCrystalData);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(sCrystalData), &gCrystal, wCrystalDataEnd - wCrystalData);
    CloseSRAM();

// This block originally had some mobile functionality, but since we're still in
// BANK(sCrystalData), it instead overwrites the sixteen wEventFlags starting at 1:s4_a60e with
// garbage from wd479. This isn't an issue, since ErasePreviousSave is followed by a regular
// save that unwrites the garbage.

    // LD_HL(wd479);
    // LD_A_hli;
    // LD_addr_A(s4_a60e + 0);
    // LD_A_hli;
    // LD_addr_A(s4_a60e + 1);
    // ld a, BANK(s4_a60e)
    // call OpenSRAM
    OpenSRAM(MBANK(as4_a60e));
    // ld hl, wd479
    // ld a, [hli]
    // ld [s4_a60e + 0], a
    // ld a, [hli]
    // ld [s4_a60e + 1], a
    CopyBytes(GBToRAMAddr(s4_a60e), wram->wd479, 2);

    // JP(mCloseSRAM);
    CloseSRAM();
}

void v_LoadData(void){
    // LD_A(BANK(sCrystalData));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asCrystalData));
    // LD_HL(sCrystalData);
    // LD_DE(wCrystalData);
    // LD_BC(wCrystalDataEnd - wCrystalData);
    // CALL(aCopyBytes);
    CopyBytes(&gCrystal, GBToRAMAddr(sCrystalData), sizeof(gCrystal));

// This block originally had some mobile functionality to mirror _SaveData above, but instead it
// (harmlessly) writes the aforementioned wEventFlags to the unused wd479.

    // LD_HL(wd479);
    // LD_A_addr(s4_a60e + 0);
    // LD_hli_A;
    // LD_A_addr(s4_a60e + 1);
    // LD_hli_A;
    // call CloseSRAM
    CloseSRAM();
    // ld a, BANK(s4_a60e)
    // call OpenSRAM
    OpenSRAM(MBANK(as4_a60e));
    // ld hl, wd479
    // ld a, [s4_a60e + 0]
    // ld [hli], a
    // ld a, [s4_a60e + 1]
    // ld [hli], a
    CopyBytes(wram->wd479, GBToRAMAddr(s4_a60e), 2);

    // JP(mCloseSRAM);
    CloseSRAM();
}

uint32_t GetBoxAddress(void){
    // LD_A_addr(wCurBox);
    // CP_A(NUM_BOXES);
    // IF_C goto ok;
    if(gPlayer.curBox >= NUM_BOXES) {
        // XOR_A_A;
        // LD_addr_A(wCurBox);
        gPlayer.curBox = 0;
    }

// ok:
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mBoxAddresses);
    // for(int rept = 0; rept < 5; rept++){
    // ADD_HL_DE;
    // }
    struct BoxAddress ba = BoxAddresses[gPlayer.curBox];
    // LD_A_hli;
    // PUSH_AF;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // POP_AF;
    // RET;
    return ba.address;
}

void SaveBoxAddress(uint32_t de){
//  Save box via wBoxPartialData.
//  We do this in three steps because the size of wBoxPartialData is less than
//  the size of sBox.
    // PUSH_HL;
//  Load the first part of the active box.
    // PUSH_AF;
    // PUSH_DE;
    // LD_A(BANK(sBox));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBox));
    // LD_HL(sBox);
    // LD_DE(wBoxPartialData);
    // LD_BC((wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCopyBytes);
    CopyBytes_GB(wBoxPartialData, sBox, (wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // POP_DE;
    // POP_AF;
//  Save it to the target box.
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(de));
    // LD_HL(wBoxPartialData);
    // LD_BC((wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCopyBytes);
    CopyBytes_GB(de & 0xffff, wBoxPartialData, (wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCloseSRAM);
    CloseSRAM();

//  Load the second part of the active box.
    // LD_A(BANK(sBox));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBox));
    // LD_HL(sBox + (wBoxPartialDataEnd - wBoxPartialData));
    // LD_DE(wBoxPartialData);
    // LD_BC((wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCopyBytes);
    CopyBytes_GB(wBoxPartialData, sBox + (wBoxPartialDataEnd - wBoxPartialData), (wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // POP_DE;
    // POP_AF;

    // LD_HL((wBoxPartialDataEnd - wBoxPartialData));
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    de += (wBoxPartialDataEnd - wBoxPartialData);
//  Save it to the next part of the target box.
    // PUSH_AF;
    // PUSH_DE;
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(de));
    // LD_HL(wBoxPartialData);
    // LD_BC((wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCopyBytes);
    CopyBytes_GB(de & 0xffff, wBoxPartialData, (wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCloseSRAM);
    CloseSRAM();

//  Load the third and final part of the active box.
    // LD_A(BANK(sBox));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBox));
    // LD_HL(sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2);
    // LD_DE(wBoxPartialData);
    // LD_BC(sBoxEnd - (sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2));  // $8e
    // CALL(aCopyBytes);
    CopyBytes_GB(wBoxPartialData, sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2, sBoxEnd - (sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // POP_DE;
    // POP_AF;

    // LD_HL((wBoxPartialDataEnd - wBoxPartialData));
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    de += (wBoxPartialDataEnd - wBoxPartialData);
//  Save it to the final part of the target box.
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(de));
    // LD_HL(wBoxPartialData);
    // LD_BC(sBoxEnd - (sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2));  // $8e
    // CALL(aCopyBytes);
    CopyBytes_GB(de & 0xffff, wBoxPartialData, sBoxEnd - (sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2));
    // CALL(aCloseSRAM);
    CloseSRAM();

    // POP_HL;
    // RET;
}

void LoadBoxAddress(uint32_t de){
//  Load box via wBoxPartialData.
//  We do this in three steps because the size of wBoxPartialData is less than
//  the size of sBox.
    // PUSH_HL;
    // LD_L_E;
    // LD_H_D;
//  Load part 1
    // PUSH_AF;
    // PUSH_HL;
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(de));
    // LD_DE(wBoxPartialData);
    // LD_BC((wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCopyBytes);
    CopyBytes_GB(wBoxPartialData, de & 0xffff, (wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A(BANK(sBox));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBox));
    // LD_HL(wBoxPartialData);
    // LD_DE(sBox);
    // LD_BC((wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCopyBytes);
    CopyBytes_GB(sBox, wBoxPartialData, (wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // POP_HL;
    // POP_AF;

    // LD_DE((wBoxPartialDataEnd - wBoxPartialData));
    // ADD_HL_DE;
    de += (wBoxPartialDataEnd - wBoxPartialData);
//  Load part 2
    // PUSH_AF;
    // PUSH_HL;
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(de));
    // LD_DE(wBoxPartialData);
    // LD_BC((wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCopyBytes);
    CopyBytes_GB(wBoxPartialData, de & 0xffff, (wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A(BANK(sBox));
    // CALL(aOpenSRAM);
    // LD_HL(wBoxPartialData);
    // LD_DE(sBox + (wBoxPartialDataEnd - wBoxPartialData));
    // LD_BC((wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCopyBytes);
    CopyBytes_GB(sBox + (wBoxPartialDataEnd - wBoxPartialData), wBoxPartialData, (wBoxPartialDataEnd - wBoxPartialData));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // POP_HL;
    // POP_AF;
//  Load part 3
    // LD_DE((wBoxPartialDataEnd - wBoxPartialData));
    // ADD_HL_DE;
    de += (wBoxPartialDataEnd - wBoxPartialData);
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(de));
    // LD_DE(wBoxPartialData);
    // LD_BC(sBoxEnd - (sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2));  // $8e
    // CALL(aCopyBytes);
    CopyBytes_GB(wBoxPartialData, de & 0xffff, sBoxEnd - (sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_A(BANK(sBox));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBox));
    // LD_HL(wBoxPartialData);
    // LD_DE(sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2);
    // LD_BC(sBoxEnd - (sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2));  // $8e
    // CALL(aCopyBytes);
    CopyBytes_GB(sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2, wBoxPartialData, sBoxEnd - (sBox + (wBoxPartialDataEnd - wBoxPartialData) * 2));
    // CALL(aCloseSRAM);
    CloseSRAM();

    // POP_HL;
    // RET;
}

void EraseBoxes(void){
    // LD_HL(mBoxAddresses);
    const struct BoxAddress* hl = BoxAddresses;
    // LD_C(NUM_BOXES);

    for(uint32_t i = 0; i < NUM_BOXES; ++i) {
    // next:
        // PUSH_BC;
        // LD_A_hli;
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(hl[i].address));
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint16_t de = hl[i].address & 0x3fff;
        // XOR_A_A;
        // LD_de_A;
        // INC_DE;
        gb_write(de++, 0);
        // LD_A(-1);
        // LD_de_A;
        // INC_DE;
        gb_write(de++, 0xff);
        // LD_BC(sBoxEnd - (sBox + 2));

        for(uint16_t bc = sBoxEnd - (sBox + 2); bc > 0; --bc) {
        // clear:
            // XOR_A_A;
            // LD_de_A;
            // INC_DE;
            gb_write(de++, 0);
            // DEC_BC;
            // LD_A_B;
            // OR_A_C;
            // IF_NZ goto clear;
        }
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint16_t de2 = hl[i].addressEnd & 0x3fff;
        // LD_A(-1);
        // LD_de_A;
        // INC_DE;
        gb_write(de2++, 0xff);
        // XOR_A_A;
        // LD_de_A;
        gb_write(de2, 0);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // POP_BC;
        // DEC_C;
        // IF_NZ goto next;
    }
    // RET;

// box_address: MACRO
//     assert BANK(\1) == BANK(\2)
//     db BANK(\1)
//     dw \1, \2
// ENDM

}

uint16_t Checksum(uint8_t* hl, uint16_t bc){
    // LD_DE(0);
    uint16_t de = 0;

    do {
    // loop:
        // LD_A_hli;
        // ADD_A_E;
        // LD_E_A;
        // LD_A(0);
        // ADC_A_D;
        // LD_D_A;
        de += *(hl++);
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // RET;
    return de;
}

const txt_cmd_s WouldYouLikeToSaveTheGameText[] = {
    text_far(v_WouldYouLikeToSaveTheGameText)
    text_end
};

const txt_cmd_s SavingDontTurnOffThePowerText[] = {
    text_far(v_SavingDontTurnOffThePowerText)
    text_end
};

const txt_cmd_s SavedTheGameText[] = {
    text_far(v_SavedTheGameText)
    text_end
};

const txt_cmd_s AlreadyASaveFileText[] = {
    text_far(v_AlreadyASaveFileText)
    text_end
};

const txt_cmd_s AnotherSaveFileText[] = {
    text_far(v_AnotherSaveFileText)
    text_end
};

const txt_cmd_s SaveFileCorruptedText[] = {
    text_far(v_SaveFileCorruptedText)
    text_end
};

const txt_cmd_s ChangeBoxSaveText[] = {
    text_far(v_ChangeBoxSaveText)
    text_end
};

const txt_cmd_s MoveMonWOMailSaveText[] = {
    text_far(v_MoveMonWOMailSaveText)
    text_end
};

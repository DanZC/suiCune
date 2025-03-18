#include "../../constants.h"
#include "../../util/scripting.h"
#include "fruit_trees.h"
#include "../../data/items/fruit_trees.h"
#include "../../data/text/common.h"
#include "../../home/copy.h"
#include "../../home/flag.h"
#include "../../mobile/mobile_41.h"

bool FruitTreeScript(script_s* s){
    SCRIPT_BEGIN
    GetCurTreeFruit();
    opentext
    readmem(wram_ptr(wCurFruit))
    getitemname(STRING_BUFFER_3, USE_SCRIPT_VAR)
    writetext(FruitBearingTreeText)
    promptbutton
    TryResetFruitTrees();
    CheckFruitTree();
    iffalse(fruit)
    writetext(NothingHereText)
    waitbutton
    goto end;


fruit:
    writetext(HeyItsFruitText)
    readmem(wram_ptr(wCurFruit))
    giveitem(ITEM_FROM_MEM, 1)
    iffalse(packisfull)
    promptbutton
    writetext(ObtainedFruitText)
    PickedFruitTree();
    specialsound
    itemnotify
    goto end;


packisfull:
    promptbutton
    writetext(FruitPackIsFullText)
    waitbutton

end:
    closetext
    s_end
    SCRIPT_END
}

void GetCurTreeFruit(void){
    // LD_A_addr(wCurFruitTree);
    // DEC_A;
    // CALL(aGetFruitTreeItem);
    // LD_addr_A(wCurFruit);
    // RET;
    wram->wCurFruit = GetFruitTreeItem_Conv(wram->wCurFruitTree);
}

void TryResetFruitTrees(void){
    // LD_HL(wDailyFlags1);
    // BIT_hl(DAILYFLAGS1_ALL_FRUIT_TREES_F);
    // RET_NZ ;
    // JP(mResetFruitTrees);
    if(bit_test(wram->wDailyFlags1, DAILYFLAGS1_ALL_FRUIT_TREES_F))
        return;
    return ResetFruitTrees();
}

void CheckFruitTree(void){
    // LD_B(CHECK_FLAG);
    // CALL(aGetFruitTreeFlag);
    // LD_A_C;
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = GetFruitTreeFlag_Conv(CHECK_FLAG, wram->wCurFruitTree);
}

void PickedFruitTree(void){
    // FARCALL(aStubbedTrainerRankings_FruitPicked);
    StubbedTrainerRankings_FruitPicked();
    // LD_B(1);
    // JP(mGetFruitTreeFlag);
    GetFruitTreeFlag_Conv(SET_FLAG, wram->wCurFruitTree);
}

void ResetFruitTrees(void){
    // XOR_A_A;
    // LD_HL(wFruitTreeFlags);
    // LD_hli_A;
    // LD_hli_A;
    // LD_hli_A;
    // LD_hl_A;
    ByteFill(wram->wFruitTreeFlags, sizeof(wram->wFruitTreeFlags), 0);
    // LD_HL(wDailyFlags1);
    // SET_hl(DAILYFLAGS1_ALL_FRUIT_TREES_F);
    bit_set(wram->wDailyFlags1, DAILYFLAGS1_ALL_FRUIT_TREES_F);
    // RET;
}

void GetFruitTreeFlag(void){
    // PUSH_HL;
    // PUSH_DE;
    // LD_A_addr(wCurFruitTree);
    // DEC_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wFruitTreeFlags);
    // CALL(aFlagAction);
    // POP_DE;
    // POP_HL;
    // RET;
}

uint8_t GetFruitTreeFlag_Conv(uint8_t b, uint8_t tree){
    // PUSH_HL;
    // PUSH_DE;
    // LD_A_addr(wCurFruitTree);
    // DEC_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wFruitTreeFlags);
    // CALL(aFlagAction);
    // POP_DE;
    // POP_HL;
    // RET;
    return FlagAction_Conv2(wram->wFruitTreeFlags, tree - 1, b);
}

void GetFruitTreeItem(void){
    // PUSH_HL;
    // PUSH_DE;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mFruitTreeItems);
    // ADD_HL_DE;
    // LD_A_hl;
    // POP_DE;
    // POP_HL;
    // RET;

// INCLUDE "data/items/fruit_trees.asm"

}

item_t GetFruitTreeItem_Conv(uint8_t a){
    // PUSH_HL;
    // PUSH_DE;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mFruitTreeItems);
    // ADD_HL_DE;
    // LD_A_hl;
    // POP_DE;
    // POP_HL;
    // RET;

// INCLUDE "data/items/fruit_trees.asm"
    return FruitTreeItems[a];
}

const txt_cmd_s FruitBearingTreeText[] = {
    text_far(v_FruitBearingTreeText)
    text_end
};

const txt_cmd_s HeyItsFruitText[] = {
    text_far(v_HeyItsFruitText)
    text_end
};

const txt_cmd_s ObtainedFruitText[] = {
    text_far(v_ObtainedFruitText)
    text_end
};

const txt_cmd_s FruitPackIsFullText[] = {
    text_far(v_FruitPackIsFullText)
    text_end
};

const txt_cmd_s NothingHereText[] = {
    text_far(v_NothingHereText)
    text_end
};

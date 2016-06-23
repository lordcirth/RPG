#include "fight.h"
#include "player.h"
#include "monsters.h"
#include "interface.h"
#include "skills.h"
#include <iostream>
#include <sstream>

using namespace std;

Skill * getValidSkillChoice(skillPtrList skillPtrs) {
    char ch;
    Skill *playerChosenSkill;

    do {
        ch = getPlayerKeyFight();
        playerChosenSkill = getSkillByHotkey(skillPtrs, ch);
    } while (playerChosenSkill == nullptr);

    return playerChosenSkill;
}


//Self or enemy target skill?
bool Fight::autoTargetSkill(Creature &player, Creature &enemy, Skill *playerChosenSkill) {
    skillReturnType attempt;

        if (playerChosenSkill->getTargetType() == TYPE_SELF) {
            attempt = playerChosenSkill->Use(player);
        } else if (playerChosenSkill->getTargetType() == TYPE_ENEMY) {
            attempt = playerChosenSkill->Use(player, enemy);
        }

        if (attempt == SKILL_SUCCESS ) {
                msgBuffer.addMessage(msgSkillUse(playerChosenSkill->getName()));
                return true;
        } else {
                msgBuffer.addMessage(msgSkillFails(playerChosenSkill,attempt));
                return false;
        }


}

Fight::Fight(PlayerCharacter &pl, Monster &e) {
    player = pl;
    enemy = e;
}

fightResults Fight::start() {

    Skill *playerChosenSkill;
    bool skillSuccess;
    initInterface();

    while ( !player.isDead() && !enemy.isDead()) { //Main fight loop
    //4 phases:

        //Phase 1: Run player buffs/debuffs
        player.clearBuffTurnMultipliers();
        runPreBuffs(player);
        runPostBuffs(player);
        if (player.isDead()) break;

        //Phase 2: Player turn
        updatePoints(player,enemy);

        printAllBuffs(player.buffs, enemy.buffs);
        printMessageBuffer(msgBuffer.getBuffer());
        showMenu(player);

        do {
            //Get key, loop until valid
            playerChosenSkill = getValidSkillChoice(player.skillPtrs);
            //Self or enemy target skill?
            skillSuccess = autoTargetSkill(player, enemy, playerChosenSkill);

        } while (skillSuccess == false); //Don't advance turn until player uses a Skill

        if (enemy.isDead()) break;
        checkExpiry(player.buffs);

        //Phase 3: Run enemy buffs/debuffs
        enemy.clearBuffTurnMultipliers();
        runPreBuffs(enemy);
        runPostBuffs(enemy);
        if (enemy.isDead()) break;
        //Phase 4: Enemy turn
        enemy.doTurn(player);
        //if (player.isDead()) break;
        checkExpiry(enemy.buffs);
    }

    fightResults results = {false, 0, 0};



    if (player.isDead()) {
        results = {false, 0, 0};

    } else if (enemy.isDead()) {
        results = {true, 0, enemy.getXP()};
    }
    return results;
}

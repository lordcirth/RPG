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
        ch = getPlayerKey();
        playerChosenSkill = getSkillByHotkey(skillPtrs, ch);
    } while (playerChosenSkill == nullptr);

    return playerChosenSkill;
}


//Self or enemy target skill?
bool autoTargetSkill(Creature &player, Creature &enemy, Skill *playerChosenSkill) {
    skillReturnType attempt;

        if (playerChosenSkill->getTargetType() == TYPE_SELF) {
            attempt = playerChosenSkill->Use(player);
        } else if (playerChosenSkill->getTargetType() == TYPE_ENEMY) {
            attempt = playerChosenSkill->Use(player, enemy);
        }

        if (attempt == SKILL_SUCCESS ) {
                printSkillUse(playerChosenSkill->getName());
                return true;
        } else {
                printSkillFails(playerChosenSkill,attempt);
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
    //initSkillMenu(player);

    while ( !player.isDead() && !enemy.isDead()) { //Main fight loop
    //4 phases:

        //Phase 1: Run player buffs/debuffs
        runBuffs(player);
        if (player.isDead()) break;

        //Phase 2: Player turn
        displayPoints(0,0, player);
        displayPoints(0,64, enemy);

        printAllBuffs(player.buffs, enemy.buffs);

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
        runBuffs(enemy);
        if (enemy.isDead()) break;
        //Phase 4: Enemy turn
        enemy.doTurn(player);
        //if (player.isDead()) break;
        checkExpiry(enemy.buffs);
    }

    fightResults results = {false, 0, 0};

    cleanUpInterface();
    if (player.isDead()) {
        cout << "You lose!";
        results = {false, 0, 0};
    } else if (enemy.isDead()) {
        cout << "You win!";
        results = {true, 0, enemy.getXP()};
    }
    return results;
}

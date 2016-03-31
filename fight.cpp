#include "fight.h"
#include "player.h"
#include "monsters.h"
#include "interface.h"
#include "skills.h"
#include <iostream>
#include <sstream>

using namespace std;

Fight::Fight(PlayerCharacter &pl, Monster &e) {
    player = pl;
    enemy = e;
}

fightResults Fight::start() {
    char ch;
    Skill *playerChosenSkill;
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
        showMenu(player);

        //Get key, loop until valid
        do {
            ch = getPlayerKey();
            playerChosenSkill = getSkillByHotkey(player.skillPtrs, ch);
        } while (playerChosenSkill == nullptr);

        //Self or enemy target skill?
        if (playerChosenSkill->getTargetType() == TYPE_SELF) {
            playerChosenSkill->Use(player);
            printSkillUse(playerChosenSkill->getName());

        } else if (playerChosenSkill->getTargetType() == TYPE_ENEMY) {
            playerChosenSkill->Use(player, enemy);
            printSkillUse(playerChosenSkill->getName(),enemy.getName());
        };

        if (enemy.isDead()) break;
        //Phase 3: Run enemy buffs/debuffs
        runBuffs(enemy);
        if (enemy.isDead()) break;
        //Phase 4: Enemy turn
        enemy.attack(player);
        //if (player.isDead()) break;
    }


    fightResults results = {false, 0, 0};

    cleanUpInterface();
    if (player.isDead()) {
        //cout << "You lose!";
        results = {false, 0, 0};
    } else if (enemy.isDead()) {
        //cout << "You win!";
        results = {true, 0, enemy.getXP()};
    }
    return results;
}

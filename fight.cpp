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
    while ( !player.isDead() && !enemy.isDead()) {
        displayPoints(0,0, player);
        displayPoints(0,66, enemy);


        //Player turn
        showMenu(player);
        do {
            ch = getPlayerKey();
            playerChosenSkill = getSkillByHotkey(player.skillPtrs, ch);
        } while (playerChosenSkill == nullptr);
        playerChosenSkill->Use(player);
        printSkillUse(playerChosenSkill->getName());


        //Enemy turn
        enemy.attack(player);
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

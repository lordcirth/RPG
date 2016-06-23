#pragma once
//Manage "fights" - ie encounters, turns, win/loss, etc.
#include "player.h"
#include "monsters.h"
#include "interface.h"

struct fightResults {
    bool won;
    int gold = 0;
    int XP;
};

class Fight {
private:
    PlayerCharacter player;
    Monster enemy;
    bool autoTargetSkill(Creature &player, Creature &enemy, Skill *playerChosenSkill);
public:
    Fight(PlayerCharacter &player, Monster &enemy);
    fightResults start(); //Run the whole fight to its end, return results
    MessageBuffer buffer;
};

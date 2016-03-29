#pragma once
//Manage "fights" - ie encounters, their turns, win/loss, etc.
#include "player.h"
#include "monsters.h"

struct fightResults {
    bool won;
    int gold = 0;
    int XP;
};

class Fight {
private:
    PlayerCharacter player;
    Monster enemy;

public:
    Fight(PlayerCharacter &player, Monster &enemy);
    fightResults start(); //Run the whole fight to its end, return results
};

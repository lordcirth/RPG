#pragma once
//Manage "fights" - ie encounters, their turns, win/loss, etc.
#include "player.h"
#include "monsters.h"

class Fight
{
private:
PlayerCharacter player;
Monster enemy;

public:
    Fight(PlayerCharacter &player, Monster &enemy);
    void start(); //Run the whole fight to its end
};

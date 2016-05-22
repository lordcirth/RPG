#pragma once
#include "skills.h"

class Monster : public Creature {
private:
    int killXP;
public:
    int getXP();

    Monster();
    Monster(CreaturePoints points, Stats stats, skillPtrList skills, int XP);

    void doTurn(Creature &player); //Default Monster AI

};

//=============================
// Define specific Monsters
//=============================

class Wolf : public Monster {
public:
    Wolf(); //Use this for generic "wolf"

    //Custom wolf with name and/or injured.  Don't make it more than 15 HP.
    Wolf(std::string name, int startingHP);
};

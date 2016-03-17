#pragma once
#include "creature.h"

class Monster : public Creature {
private:
    int killXP;
    int attackDamage;
public:
    int getXP();
    void attack(Creature &target);

    Monster(); //Only for other classes
    Monster(CreaturePoints points, int XP);
    Monster(CreaturePoints points, int dmg, int XP);

};


//=============================
// Define specific Monsters
//=============================

class Wolf : public Monster {
public:
    Wolf();
    Wolf(int startingHP);
    Wolf(std::string name);
};

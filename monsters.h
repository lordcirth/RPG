#include "player.h"
#ifndef MONSTERS_H
#define MONSTERS_H

class Creature
{
    CreaturePoints pointValues;
public:
    void healAll();
    void damage(int hpDmg, int spDmg, int mpDmg);
    Creature();
    Creature(CreaturePoints points);

};


class Monster : public Creature
{

public:
    Monster(CreaturePoints points);
};
#endif

#include "monsters.h"
#include <iostream>

int Monster::getXP()
{
    return killXP;
}

void Monster::attack(Creature &target)
{
    target.damage(attackDamage,0,0);
}

//Default, only for other classes
Monster::Monster()
    : Creature()
{

}

Monster::Monster(CreaturePoints points, int XP)
    : Creature(points)
{
    killXP = XP;

}

Monster::Monster(CreaturePoints points, int dmg, int XP)
    : Creature(points)
{
    killXP = XP;
    attackDamage = dmg;
}

Wolf::Wolf()
    : Monster(
{
    15,0,0,15,0,0
},5)
{
}


Wolf::Wolf(int startingHP)
    : Monster(
{
    15,0,0,startingHP,0,0
},5)
{
}

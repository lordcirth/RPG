#include "monsters.h"
#include <algorithm> //min

using namespace std;
Creature::Creature(CreaturePoints points)
{
    stats = {0,0,0,0,0,0};
    pointValues = points;

}

void Creature::damage(int hpDmg, int spDmg, int mpDmg)
{
    pointValues.HP = min(pointValues.HP - hpDmg, pointValues.maxHP);
    pointValues.SP = min(pointValues.SP - spDmg, pointValues.maxSP);
    pointValues.MP = min(pointValues.MP - mpDmg, pointValues.maxMP);
}

Monster::Monster(CreaturePoints points)
    : Creature(points)
{

}

//
//wolf

#include "creature.h"
#include <algorithm> //min
#include <iostream>


using namespace std;

CreatureStats Creature::getStats()
{
    return stats;
}

void Creature::setStats(CreatureStats newStats)
{
    stats = newStats;
}

CreaturePoints Creature::getPointValues()
{
    return pointValues;
}


void Creature::setPointValues(CreaturePoints points)
{
    pointValues = points;
}



Creature::Creature(CreatureStats startingStats)
{
    stats = startingStats;
    pointValues = {0,0,0,0,0,0};

}

Creature::Creature(CreaturePoints points)
{
    stats = {0,0,0,0,0,0};
    pointValues = points;

}


void Creature::healAll()
{
    CreaturePoints points = getPointValues();
    points.HP = points.maxHP;
    points.SP = points.maxSP;
    points.MP = points.maxMP;
    setPointValues(points);
}

void Creature::damage(int hpDmg, int spDmg, int mpDmg)
{
    cout << "Damage: " << hpDmg << endl;
    pointValues.HP = min(pointValues.HP - hpDmg, pointValues.maxHP);
    pointValues.SP = min(pointValues.SP - spDmg, pointValues.maxSP);
    pointValues.MP = min(pointValues.MP - mpDmg, pointValues.maxMP);
}

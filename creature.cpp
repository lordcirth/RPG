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
    //calcAttributes(); //New maxHP, etc
}

CreaturePoints Creature::getPointValues()
{
    return pointValues;
}

void Creature::setPointValues(CreaturePoints points)
{
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

std::string Creature::getName()
{
    return name;
}

void Creature::damage(int hpDmg, int spDmg, int mpDmg)
{
    pointValues.HP = min(pointValues.HP - hpDmg, pointValues.maxHP);
    pointValues.SP = min(pointValues.SP - spDmg, pointValues.maxSP);
    pointValues.MP = min(pointValues.MP - mpDmg, pointValues.maxMP);
}

bool Creature::isDead()
{
    if (pointValues.HP <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Constructors
Creature::Creature()
{
}
Creature::Creature(CreatureStats startingStats)
{
    name = "Unnamed Creature";
    stats = startingStats;
    //Calculated from stats by subclass
    pointValues = {0,0,0,0,0,0};
}

Creature::Creature(CreaturePoints points)
{
    stats = {0,0,0,0,0,0};
    pointValues = points;
}

Creature::Creature(CreatureStats startingStats, std::string cName)
{
    name = cName;
    stats = startingStats;
    pointValues = {0,0,0,0,0,0};
}

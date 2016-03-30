#include "creature.h"
#include <algorithm> //min
#include <iostream>


using namespace std;

CreatureStats Creature::getStats() {
    return stats;
}

void Creature::setStats(CreatureStats newStats) {
    stats = newStats;
    //calcAttributes(); //New maxHP, etc
}

CreaturePoints Creature::getPointValues() {
    return pointValues;
}

void Creature::setPointValues(CreaturePoints points) {
    pointValues = points;
}

void Creature::healAll() {
    CreaturePoints points = getPointValues();
    points.HP = points.maxHP;
    points.SP = points.maxSP;
    points.MP = points.maxMP;
    setPointValues(points);
}

void Creature::setName(std::string newName) {
    name = newName;
}

std::string Creature::getName() {
    return name;
}


const  char * Creature::getName_c() {
    return name.c_str();
}

void Creature::damage(int hpDmg, int spDmg, int mpDmg) {
    CreaturePoints c = pointValues;
    //Limit to between 0 and max
    c.HP = max(0, min(c.HP - hpDmg, c.maxHP));
    c.SP = max(0, min(c.SP - spDmg, c.maxSP));
    c.MP = max(0, min(c.MP - mpDmg, c.maxMP));
    pointValues = c;
}

bool Creature::isDead() {
    if (pointValues.HP <= 0) {
        return true;
    } else {
        return false;
    }
}


//Constructors
Creature::Creature() {
}
Creature::Creature(CreatureStats startingStats) {
    name = "Unnamed Creature";
    stats = startingStats;
    //Calculated from stats by subclass
    pointValues = {0,0,0,0,0,0};
}

Creature::Creature(CreaturePoints points) {
    stats = {0,0,0,0,0,0};
    pointValues = points;
}

Creature::Creature(CreatureStats startingStats, std::string cName) {
    //cout << "starting Creature ctor";
    name = cName;
    stats = startingStats;
    pointValues = {0,0,0,0,0,0};
}

#include "creature.h"
#include <algorithm> //min
#include <iostream>


using namespace std;

Stats Creature::getStats() {
    return stats;
}

void Creature::setStats(Stats newStats) {
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

void Creature::damage(Points dmg) {
    CreaturePoints c = pointValues;
    //Limit to between 0 and max
    c.HP = max(0, min(c.HP - dmg.HP, c.maxHP));
    c.SP = max(0, min(c.SP - dmg.SP, c.maxSP));
    c.MP = max(0, min(c.MP - dmg.MP, c.maxMP));
    pointValues = c;
}

void Creature::heal(Points healing) {
    CreaturePoints c = pointValues;
    //Limit to between 0 and max
    c.HP = max(0, min(c.HP + healing.HP, c.maxHP));
    c.SP = max(0, min(c.SP + healing.SP, c.maxSP));
    c.MP = max(0, min(c.MP + healing.MP, c.maxMP));
    pointValues = c;
}

//void Creature::addBuff(Buff newBuff) {
//    buffs.push_back(*newBuff);
//};

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
//Creature::Creature(Stats startingStats) {
//    name = "Unnamed Creature";
//    stats = startingStats;
//    //Calculated from stats by subclass
//    pointValues = {0,0,0,0,0,0};
//}

Creature::Creature(CreaturePoints points) {
    stats = {0,0,0,0,0,0};
    pointValues = points;
}

Creature::Creature(Stats startingStats, std::string cName) {
    name = cName;
    stats = startingStats;
    pointValues = {0,0,0,0,0,0}; //Initialized by subclass, based on Stats
}

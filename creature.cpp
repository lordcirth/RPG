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

void Creature::rawDamage(Points dmg) { //Deal raw damage.  Should rarely be called directly.
    CreaturePoints c = pointValues;
    //Limit to between 0 and max
    c.HP = max(0, min(c.HP - dmg.HP, c.maxHP));
    c.SP = max(0, min(c.SP - dmg.SP, c.maxSP));
    c.MP = max(0, min(c.MP - dmg.MP, c.maxMP));
    pointValues = c;
}

void Creature::damage(Points dmg, skillDamageType damageType) {
    //Currently only HP is affected
    //If any multiplier is 0 (ie disarm), damage is 0.  "No change" is 1.
    dmg.HP *= turnBuffEffects.allDamageTaken;
    if (damageType == DMGTYPE_PHYSICAL) {
        dmg.HP *= turnBuffEffects.physicalDamageTaken;
    }
    if (damageType == DMGTYPE_MAGICAL) {
        dmg.HP *= turnBuffEffects.magicalDamageTaken;
    }

    rawDamage(dmg);
}

void Creature::heal(Points healing) {
    CreaturePoints c = pointValues;
    //Limit to between 0 and max
    c.HP = max(0, min(c.HP + healing.HP, c.maxHP));
    c.SP = max(0, min(c.SP + healing.SP, c.maxSP));
    c.MP = max(0, min(c.MP + healing.MP, c.maxMP));
    pointValues = c;
}

void Creature::takeCost(Points cost) {
    rawDamage(cost);
}

Points Creature::runDamageMultipliers (Points dmg,  skillDamageType damageType) {
    //Only HP is affected right now
    dmg.HP *= turnBuffEffects.allDamageOutput;
    if (damageType == DMGTYPE_PHYSICAL) {
        dmg.HP *= turnBuffEffects.physicalDamageOutput;
    }
    if (damageType == DMGTYPE_MAGICAL) {
        dmg.HP *= turnBuffEffects.magicalDamageOutput;
    }
    return dmg;
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

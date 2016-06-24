#include "creature.h"
#include <algorithm> //min
#include <iostream>


using namespace std;

//Calculate & set total attributes
void Creature::calcAttributes() {
    //All subject to change
    CreaturePoints points = getPointValues();
    Stats stats = getStats();

    points.maxHP = basePoints.HP + 2*stats["endurance"];
    points.maxSP = basePoints.SP + 1*stats["endurance"] + 1*stats["dexterity"];
    points.maxMP = basePoints.MP + 2*stats["stability"] + 1* stats["control"];

    setPointValues(points);
}

Stats allStats(int s) { //Generate stats all the same (0 for starting, 1 for player, etc)
Stats stats;

    //Physical
    stats.emplace("strength"  , s);
    stats.emplace("dexterity" , s);
    stats.emplace("endurance" , s);

    //Magical
    stats.emplace("power"     , s);
    stats.emplace("control"   , s);
    stats.emplace("stability" , s);
return stats;
};

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

Creature::Creature(Points basePoints, Stats startingStats, std::string cName) {
    name = cName;
    this->basePoints = basePoints;
    stats = startingStats;
    calcAttributes();
    healAll();
}


//Extra functions:


//Merge two sets of BuffTurnMultipliers
void Creature::mergeBuffTurnMultipliers (BuffTurnMultipliers changes) {

    //TODO: Move to std::map like Stats
    this->turnBuffEffects.allDamageOutput       *= changes.allDamageOutput;
    this->turnBuffEffects.magicalDamageOutput   *= changes.magicalDamageOutput;
    this->turnBuffEffects.physicalDamageOutput  *= changes.physicalDamageOutput;

    this->turnBuffEffects.allDamageTaken        *= changes.allDamageTaken;
    this->turnBuffEffects.magicalDamageTaken    *= changes.magicalDamageTaken;
    this->turnBuffEffects.physicalDamageTaken   *= changes.physicalDamageTaken;

}

void Creature::clearBuffTurnMultipliers() {
    BuffTurnMultipliers defaultMults;
    this->turnBuffEffects = defaultMults;
};

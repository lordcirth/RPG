#pragma once
#include <list>
#include <string>


class Skill;  //Forward declaration
class Buff;  //Forward declaration

//Used by Skills, Buffs, and Creatures so it needs to be here
enum skillDamageType {
    DMGTYPE_NONE, //Used mostly if it doesn't do damage, or special cases
    DMGTYPE_PHYSICAL,
    DMGTYPE_MAGICAL
};

struct Stats {
    //Physical
    int strength    = 0;
    int dexterity   = 0;
    int endurance   = 0;
    //Magical
    int power       = 0;
    int control     = 0;
    int stability   = 0;

};

struct Points {
    int HP;
    int SP;
    int MP;
};

struct CreaturePoints {
    int maxHP;
    int maxSP;
    int maxMP;

    int HP;
    int SP;
    int MP;
};

//Modifiers applied by (de)buffs on a given turn
//Default values are 1, no effect
struct BuffTurnMultipliers {
    float allDamageOutput         = 1;
    float physicalDamageOutput    = 1;
    float magicalDamageOutput     = 1;

    float allDamageTaken          = 1;
    float physicalDamageTaken     = 1;
    float magicalDamageTaken      = 1;

};


class Creature {
private:
    Stats stats;
    CreaturePoints pointValues;
    std::string name = "";

    void rawDamage(Points dmg); //Raw damage, no modifiers

public:
    std::list<Skill*> skillPtrs;
    std::list<Buff*> buffs;
    BuffTurnMultipliers turnBuffEffects;
    Stats getStats();
    void setStats(Stats);
    CreaturePoints getPointValues();
    void setPointValues(CreaturePoints);
    void setName(std::string);
    std::string getName();
    const char * getName_c();
    Points runDamageMultipliers (Points dmg,  skillDamageType damageType);

    void healAll();

    void damage(Points dmg, skillDamageType damageType);
    void heal(Points healing);
    //Like damage() but for skill costs, ignores amp/reduction etc
    void takeCost(Points cost);
    void mergeBuffTurnMultipliers (BuffTurnMultipliers changes);
    void clearBuffTurnMultipliers();

    bool isDead();

    Creature();
    Creature(Stats startingStats);
    Creature(CreaturePoints points);
    Creature(Stats startingStats, std::string cName);


};

//Merge two sets of BuffTurnMultipliers


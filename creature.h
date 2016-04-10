#pragma once
#include <list>
#include <string>

class Skill;  //Forward declaration
class Buff;  //Forward declaration

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
//Default values are no effect
struct TurnMultipliers {
    int allDamageOutput         = 1;
    int physicalDamageOutput    = 1;
    int magicalDamageOutput     = 1;

    int allDamageTaken          = 1;
    int physicalDamageTaken     = 1;
    int magicalDamageTaken      = 1;

};


class Creature {
private:
    Stats stats;
    CreaturePoints pointValues;
    std::string name = "";
    //Has to be pointers or subclasses get "sliced"

public:
    std::list<Skill*> skillPtrs;
    std::list<Buff*> buffs;
    TurnMultipliers turnBuffEffects;
    Stats getStats();
    void setStats(Stats);
    CreaturePoints getPointValues();
    void setPointValues(CreaturePoints);
    void setName(std::string);
    std::string getName();
    const char * getName_c();

    void healAll();
    void damage(Points dmg);
    void heal(Points healing);

    bool isDead();

    Creature();
    Creature(Stats startingStats);
    Creature(CreaturePoints points);
    Creature(Stats startingStats, std::string cName);

};


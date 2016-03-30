#pragma once
#include <list>
#include <string>

class Buff;  //Forward declaration

struct Stats {
    //Physical
    int strength;
    int dexterity;
    int endurance;
    //Magical
    int power;
    int control;
    int stability;

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


class Creature {
private:
    Stats stats;
    CreaturePoints pointValues;
    std::string name = "";
    //Has to be pointers or subclasses get "sliced"
    std::list<Buff*> buffs;

public:
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
    //void addBuff(Buff &newBuff);
    //void runBuffs();

    bool isDead();

    Creature();
    Creature(Stats startingStats);
    Creature(CreaturePoints points);
    Creature(Stats startingStats, std::string cName);

};


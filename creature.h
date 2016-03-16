#pragma once
#include <string>
struct CreatureStats
{
    //Physical
    int strength;
    int dexterity;
    int endurance;
    //Magical
    int power;
    int control;
    int stability;

};

struct CreaturePoints
{
    int maxHP;
    int maxSP;
    int maxMP;

    int HP;
    int SP;
    int MP;
};


class Creature
{
private:
    CreatureStats stats;
    CreaturePoints pointValues;
    std::string name = "";

public:
    CreatureStats getStats();
    void setStats(CreatureStats);
    CreaturePoints getPointValues();
    void setPointValues(CreaturePoints);
    void setName(std::string);
    std::string getName();

    void healAll();
    void damage(int hpDmg, int spDmg, int mpDmg);

    bool isDead();

    Creature();
    Creature(CreatureStats startingStats);
    Creature(CreaturePoints points);
    Creature(CreatureStats startingStats, std::string cName);

};


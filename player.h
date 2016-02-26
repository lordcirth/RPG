#include <string>
#ifndef PLAYER_H
#define PLAYER_H

struct CreatureStats
{
    //Physical
    int strength;
    int dexterity;
    int endurance;
    //Magical
    int power;
    int control;
    int capacity;

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
    CreaturePoints pointValues;
public:
    void healAll();
    void damage(int hpDmg, int spDmg, int mpDmg);
    Creature();
    Creature(CreaturePoints points);

};


class PlayerCharacter
{

private:
    //stats struct
    CreatureStats stats;
    CreaturePoints pointValues;

    //Stats add to these
    int baseHP; //Health
    int baseSP; //Stamina
    int baseMP; //Mana

public:
    CreatureStats getStats();
    void setStats(CreatureStats);
    CreaturePoints getPointValues();

    //Constructors
    PlayerCharacter(int bHP, int bSP, int bMP, CreatureStats bStats);
    PlayerCharacter();
    void calcAttributes();
    void healAll();
    void damage(int hpDmg, int spDmg, int mpDmg);


};

std::string displayStats(CreatureStats stats);
std::string displayPoints(CreaturePoints points);

#endif

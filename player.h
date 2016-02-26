#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "monsters.h"

#warning Starting player.h

//class Creature
//{
//    CreaturePoints pointValues;
//public:
//    void healAll();
//    void damage(int hpDmg, int spDmg, int mpDmg);
//    Creature();
//    Creature(CreaturePoints points);
//
//};


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
    #warning Declaring calcAttributes
    void calcAttributes();
    void healAll();
    void damage(int hpDmg, int spDmg, int mpDmg);
    //Constructors
    PlayerCharacter(int bHP, int bSP, int bMP, CreatureStats bStats);
    PlayerCharacter();



};

std::string displayStats(CreatureStats stats);
std::string displayPoints(CreaturePoints points);

#endif

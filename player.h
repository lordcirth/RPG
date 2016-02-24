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

class PlayerCharacter
{

private:
    //stats struct
    CreatureStats stats;

    //Stats add to these
    int baseHP; //Health
    int baseSP; //Stamina
    int baseMP; //Mana

    int maxHP;
    int maxSP;
    int maxMP;

    int HP;
    int SP;
    int MP;

public:
    CreatureStats getStats();
    void setStats(CreatureStats);

    //Constructors
    PlayerCharacter(int bHP, int bSP, int bMP, CreatureStats bStats);
    PlayerCharacter();
    void calcAttributes();

    //calcAttributes();

};

std::string displayStats(CreatureStats stats);


#endif

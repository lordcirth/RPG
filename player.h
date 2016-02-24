#include <string>
#ifndef PLAYER_H
#define PLAYER_H

struct CreatureStats
{

};

class PlayerCharacter
{

    private:
    //stats struct
    CreatureStats stats;

//Physical
//    int strength;
//    int dexterity;
//    int endurance;
//    //Magical
//    int power;
//    int control;
//    int capacity;
//
//    //Stats add to these
//    int baseHP; //Health
//    int baseSP; //Stamina
//    int baseMP; //Mana

    int[6] stats

    public:
    CreatureStats getStats();
    void setStats(CreatureStats);

    //Constructors
    PlayerCharacter(int bHP, int bSP, int bMP, CreatureStats bStats);
    PlayerCharacter();

    //calcAttributes();

};

std::string displayStats(CreatureStats stats);




#endif

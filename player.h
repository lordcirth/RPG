#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "monsters.h"

class PlayerCharacter : public Creature
{

private:
    //Stats add to these
    int baseHP; //Health
    int baseSP; //Stamina
    int baseMP; //Mana

public:

    void calcAttributes();

    //Constructors
    PlayerCharacter(int bHP, int bSP, int bMP, CreatureStats bStats);
    PlayerCharacter();



};

std::string displayStats(CreatureStats stats);
std::string displayPoints(CreaturePoints points);

#endif

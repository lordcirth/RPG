#include <iostream>
#include "player.h"

using namespace std;

CreatureStats PlayerCharacter::getStats()
{
    return stats;
};

void PlayerCharacter::setStats(CreatureStats newStats)
{
    stats = newStats;
};

//Calculate & set total attributes
void PlayerCharacter::calcAttributes()
{
    //All subject to change
    maxHP = baseHP + 2*stats.endurance;
    maxSP = baseSP + 1*stats.endurance + 1*stats.dexterity;
    maxMP = baseMP + 2*stats.capacity;
};


void PlayerCharacter::healAll()
{
    HP = maxHP;
    SP = maxSP;
    MP = maxMP;
}

//Apply damage & costs to player
void PlayerCharacter::damage(int hpDmg, int spDmg, int mpDmg)
{
    HP = HP - hpDmg;
    SP = SP - spDmg;
    MP = MP - mpDmg;
}

//Default Constructor
PlayerCharacter::PlayerCharacter()
{
    baseHP = 10;
    baseSP = 0;
    baseMP = 0;

    PlayerCharacter::setStats({1,1,1,1,1,1});
    calcAttributes();
    healAll();
};

//Custom Constructor
PlayerCharacter::PlayerCharacter(int bHP, int bSP, int bMP, CreatureStats bStats)
{
    baseHP = bHP;
    baseSP = bSP;
    baseMP = bMP;

    setStats(bStats);
    calcAttributes();
    healAll();

};

string displayStats(CreatureStats stats)
{
    string output =
        "  STR: " + to_string(stats.strength)  +
        "  DEX: " + to_string(stats.dexterity) +
        "  END: " + to_string(stats.endurance) +
        "\n"

        "  POW: " + to_string(stats.power)     +
        "  CNT: " + to_string(stats.control)   +
        "  CAP: " + to_string(stats.capacity);
    return output;
};

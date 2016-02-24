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

//Default Constructor
PlayerCharacter::PlayerCharacter()
{
    baseHP = 10;
    baseSP = 0;
    baseMP = 0;

    PlayerCharacter::setStats({1,1,1,1,1,1});

};

//Custom Constructor
PlayerCharacter::PlayerCharacter(int bHP, int bSP, int bMP, CreatureStats bStats)
{
    baseHP = bHP;
    baseSP = bSP;
    baseMP = bMP;

    setStats(bStats);

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

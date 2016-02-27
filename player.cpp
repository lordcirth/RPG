#include "player.h"
#include <iostream>
#include "monsters.h"
#include "skills.h"

using namespace std;

CreatureStats PlayerCharacter::getStats()
{
    return stats;
}

void PlayerCharacter::setStats(CreatureStats newStats)
{
    stats = newStats;
}

//Calculate & set total attributes
void PlayerCharacter::calcAttributes()
{
    //All subject to change
    pointValues.maxHP = baseHP + 2*stats.endurance;
    pointValues.maxSP = baseSP + 1*stats.endurance + 1*stats.dexterity;
    pointValues.maxMP = baseMP + 2*stats.capacity;
}


void PlayerCharacter::healAll()
{
    pointValues.HP = pointValues.maxHP;
    pointValues.SP = pointValues.maxSP;
    pointValues.MP = pointValues.maxMP;
}

//Apply damage & costs to player
//Can go negative, but not over maxHP
void PlayerCharacter::damage(int hpDmg, int spDmg, int mpDmg)
{
    pointValues.HP = min(pointValues.HP - hpDmg, pointValues.maxHP);
    pointValues.SP = min(pointValues.SP - spDmg, pointValues.maxSP);
    pointValues.MP = min(pointValues.MP - mpDmg, pointValues.maxMP);
}

CreaturePoints PlayerCharacter::getPointValues()
{
    return pointValues;
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
}

//Custom Constructor
PlayerCharacter::PlayerCharacter(int bHP, int bSP, int bMP, CreatureStats bStats)
{
    baseHP = bHP;
    baseSP = bSP;
    baseMP = bMP;

    setStats(bStats);
    calcAttributes();
    healAll();

}

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
}

string displayPoints(CreaturePoints points)
{
    string output =
        "  HP: " + to_string(points.HP) + " / " + to_string(points.maxHP) + "\n" +
        "  SP: " + to_string(points.SP) + " / " + to_string(points.maxSP) + "\n" +
        "  MP: " + to_string(points.MP) + " / " + to_string(points.maxMP) + "\n";
    return output;
}

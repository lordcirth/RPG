#include "player.h"
#include <iostream>
#include "monsters.h"
#include "skills.h"

using namespace std;


//Calculate & set total attributes
void PlayerCharacter::calcAttributes() {
    //All subject to change
    CreaturePoints points = getPointValues();
    CreatureStats stats = getStats();

    points.maxHP = baseHP + 2*stats.endurance;
    points.maxSP = baseSP + 1*stats.endurance + 1*stats.dexterity;
    points.maxMP = baseMP + 2*stats.stability + 1* stats.control;

    setPointValues(points);
}



//Default Constructor
PlayerCharacter::PlayerCharacter()
    : Creature(CreatureStats {1,1,1,1,1,1}, "Player") {
    baseHP = 10;
    baseSP = 0;
    baseMP = 0;

    skillPtrs = createSkillPtrList();

    setStats({1,1,1,1,1,1});
    calcAttributes();
    healAll();

}

PlayerCharacter::PlayerCharacter(std::string playerName)
    : Creature(CreatureStats {1,1,1,1,1,1}, playerName) {
    //cout << "starting player ctor";
    baseHP = 10;
    baseSP = 0;
    baseMP = 0;

    skillPtrs = createSkillPtrList();
    std::cout << "Player ctor:" << skillPtrs.front()->getName() << std::endl;

    setStats({1,1,1,1,1,1});
    calcAttributes();
    healAll();

    //skillList skills = createSkillStruct();
}

PlayerCharacter::PlayerCharacter(int bHP, int bSP, int bMP, CreatureStats bStats, std::string playerName)
    : Creature(bStats, playerName) {
    baseHP = bHP;
    baseSP = bSP;
    baseMP = bMP;

    calcAttributes();
    healAll();

//    skillList skills = createSkillStruct();
}

string displayStats(CreatureStats stats) {
    string output =
        "  STR: " + to_string(stats.strength)  +
        "  DEX: " + to_string(stats.dexterity) +
        "  END: " + to_string(stats.endurance) +
        "\n"

        "  POW: " + to_string(stats.power)     +
        "  CNT: " + to_string(stats.control)   +
        "  CAP: " + to_string(stats.stability);
    return output;
}

string displayPoints(CreaturePoints points) {
    string output =
        "  HP: " + to_string(points.HP) + " / " + to_string(points.maxHP) + "\n" +
        "  SP: " + to_string(points.SP) + " / " + to_string(points.maxSP) + "\n" +
        "  MP: " + to_string(points.MP) + " / " + to_string(points.maxMP) + "\n";
    return output;
}

void PlayerCharacter::levelUp() {
    level++;
    freeStatPoints++;
    freeSkillPoints++;
}

void PlayerCharacter::giveXP(int earnedXP) {
    XP += earnedXP;
    //XP is full
    if (XP > xpLevelMultiplier*baseXpPerLevel) {
        XP -= xpLevelMultiplier*baseXpPerLevel;
        levelUp();
    }
}

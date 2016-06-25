#include "player.h"
#include <iostream>
#include "monsters.h"
#include "skills.h"

using namespace std;






//Default Constructor
PlayerCharacter::PlayerCharacter() {
//    : Creature(allStats(1), {} "Player") {
//    basePoints.HP = 10;
//    basePoints.SP = 0;
//    basePoints.MP = 0;
//
//    skillPtrs = createSkillPtrList();
//
//    setStats({1,1,1,1,1,1});
//    calcAttributes();
//    healAll();
}

PlayerCharacter::PlayerCharacter(std::string playerName)
    : Creature({10,0,0}, allStats(1), playerName) {

    skillPtrs = createSkillPtrList();
}

// Not used right now, so no point updating it for every change.
//PlayerCharacter::PlayerCharacter(int bHP, int bSP, int bMP, Stats bStats, std::string playerName)
//    : Creature(bStats, playerName) {
//    basePoints.HP = bHP;
//    basePoints.SP = bSP;
//    basePoints.MP = bMP;
//
//    calcAttributes();
//    healAll();
//
////    skillList skills = createSkillStruct();
//}

//Destructor
//PlayerCharacter::~PlayerCharacter() {
//
//}


//string displayStats(Stats stats) {
//    string output =
//        "  STR: " + to_string(stats["strength"] )  +
//        "  DEX: " + to_string(stats["dexterity"]) +
//        "  END: " + to_string(stats["endurance"]) +
//        "\n"
//
//        "  POW: " + to_string(stats.power)     +
//        "  CNT: " + to_string(stats.control)   +
//        "  CAP: " + to_string(stats.stability);
//    return output;
//}

void PlayerCharacter::levelUp() {
    level++;
    freeStatPoints++;
    freeSkillPoints++;
}

void PlayerCharacter::giveXP(int earnedXP) {
    XP += earnedXP;

    //XP is full
    if (XP >= xpLevelMultiplier*level*baseXpPerLevel) {
        XP -= xpLevelMultiplier*level*baseXpPerLevel;
        levelUp();
    }
}

//Return both as pair, since they are often used together, and should never be out of sync
std::pair<int,int> PlayerCharacter::getXP() {
    //Total XP required, not remaining!
    int xpNextLevel = xpLevelMultiplier*level*baseXpPerLevel;
    std::pair<int,int> xpPair = std::make_pair(XP,xpNextLevel);
    return xpPair;
}

int PlayerCharacter::getFreeStatPoints() {
    return freeStatPoints;
}


int PlayerCharacter::getFreeSkillPoints() {
    return freeSkillPoints;
}

int PlayerCharacter::changeFreeStatPointsBy(int change) {
    freeStatPoints += change;
}

int PlayerCharacter::changeFreeSkillPointsBy(int change)  {
    freeSkillPoints += change;
}

int PlayerCharacter::getLevel() {
    return level;
}

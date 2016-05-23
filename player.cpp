#include "player.h"
#include <iostream>
#include "monsters.h"
#include "skills.h"

using namespace std;


//Calculate & set total attributes
void PlayerCharacter::calcAttributes() {
    //All subject to change
    CreaturePoints points = getPointValues();
    Stats stats = getStats();

    points.maxHP = basePoints.HP + 2*stats.endurance;
    points.maxSP = basePoints.SP + 1*stats.endurance + 1*stats.dexterity;
    points.maxMP = basePoints.MP + 2*stats.stability + 1* stats.control;

    setPointValues(points);
}



//Default Constructor
PlayerCharacter::PlayerCharacter()
    : Creature(Stats {1,1,1,1,1,1}, "Player") {
    basePoints.HP = 10;
    basePoints.SP = 0;
    basePoints.MP = 0;

    skillPtrs = createSkillPtrList();

    setStats({1,1,1,1,1,1});
    calcAttributes();
    healAll();

}

PlayerCharacter::PlayerCharacter(std::string playerName)
    : Creature(Stats {1,1,1,1,1,1}, playerName) {
    //cout << "starting player ctor";
    basePoints.HP = 10;
    basePoints.SP = 0;
    basePoints.MP = 0;

    skillPtrs = createSkillPtrList();

    setStats({1,1,1,1,1,1});
    calcAttributes();
    healAll();

    //skillList skills = createSkillStruct();
}

PlayerCharacter::PlayerCharacter(int bHP, int bSP, int bMP, Stats bStats, std::string playerName)
    : Creature(bStats, playerName) {
    basePoints.HP = bHP;
    basePoints.SP = bSP;
    basePoints.MP = bMP;

    calcAttributes();
    healAll();

//    skillList skills = createSkillStruct();
}

//Destructor
PlayerCharacter::~PlayerCharacter() {
    //cerr << "Player dcon called!" << endl;
//    list<Skill*>::const_iterator it = skillPtrs.begin();
//
//    while (it != this->skillPtrs.end()) {
//        delete (*it);  //Causes doublefree?  Why?
//    }
}

string displayStats(Stats stats) {
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

void PlayerCharacter::levelUp() {
    level++;
    freeStatPoints++;
    freeSkillPoints++;
}

void PlayerCharacter::giveXP(int earnedXP) {
    XP += earnedXP;

    //XP is full
    if (XP >= xpLevelMultiplier*level*baseXpPerLevel) {
        XP -= xpLevelMultiplier*baseXpPerLevel;
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

int PlayerCharacter::getLevel() {
    return level;
}

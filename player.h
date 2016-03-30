#pragma once

#include <string>
#include "monsters.h"
#include "skills.h"

//typedef std::map<std::string,Heal> healPtrMap;
class PlayerCharacter : public Creature {

private:
    //Stats add to these
    int baseHP; //Health
    int baseSP; //Stamina
    int baseMP; //Mana

    int level = 1;
    int XP = 0;

    int freeStatPoints = 0;
    int freeSkillPoints = 0;

    //XP Scaling
    int xpLevelMultiplier = 1;
    int baseXpPerLevel = 10;

    void levelUp();

public:

    skillPtrList skillPtrs;
//    skillSharedPtrList safeSkillList;

    void calcAttributes();
    void giveXP(int earnedXP);
    //Constructors
    PlayerCharacter(int bHP, int bSP, int bMP, Stats bStats);
    PlayerCharacter(int bHP, int bSP, int bMP, Stats bStats, std::string playerName);
    PlayerCharacter(std::string playerName);
    PlayerCharacter();

};

std::string displayStats(Stats stats);
//std::string displayPoints(CreaturePoints points);

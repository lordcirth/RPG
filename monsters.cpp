#include "monsters.h"
#include <iostream>

int Monster::getXP() {
    return killXP;
}


//Default, only for other classes
Monster::Monster()
    : Creature() {

}

Monster::Monster(Points basePoints, Stats stats, std::string name, skillPtrList skills, int XP)
    : Creature(basePoints, stats, name) {
    setStats(stats); //TODO fix Creature ctors
    killXP = XP;
    skillPtrs = skills;
}

void Monster::doTurn(Creature &player) { //Default Monster AI
    if (skillPtrs.size() >= 1) {
        skillPtrs.front()->Use(*this, player);
    } else {
        std::cerr << "no skills!" << std::endl;
    }
}

skillPtrList skills_default = createMonsterSkillList();

Points basePoints_wolf =  {8,0,0};
Stats wolf_stats() {
    Stats            stats_wolf = allStats(0);
    stats_wolf["strength"]      =  1;
    stats_wolf["dexterity"]     =  1;
    stats_wolf["endurance"]     =  2;
    return stats_wolf;
}


Wolf::Wolf()
    : Monster(basePoints_wolf, wolf_stats(), "Wolf", skills_default, 10) {

}

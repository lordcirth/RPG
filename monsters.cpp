#include "monsters.h"
#include <iostream>

int Monster::getXP() {
    return killXP;
}


//Default, only for other classes
Monster::Monster()
    : Creature() {

}

Monster::Monster(CreaturePoints points, Stats stats, skillPtrList skills, int XP)
    : Creature(points) {
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

CreaturePoints cpoints_wolf =  {15,0,0,15,0,0};
Stats          stats_wolf   =   {1,1,1,0,0,0};
Wolf::Wolf()
    : Monster(cpoints_wolf, stats_wolf, skills_default, 10) {
    setName("Wolf"); //Should probably be moved to Creature() at some point
}

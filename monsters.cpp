#include "monsters.h"
#include <iostream>

int Monster::getXP() {
    return killXP;
}

void Monster::attack(Creature &target) { //TODO replace with using Hit.Use()
    target.damage({attackDamage,0,0}, DMGTYPE_PHYSICAL);
}

//Default, only for other classes
Monster::Monster()
    : Creature() {

}

Monster::Monster(CreaturePoints points, int dmg, int XP)
    : Creature(points) {
    killXP = XP;
    attackDamage = dmg;
}

Wolf::Wolf()
    : Monster( {15,0,0,15,0,0},2,5) {
    setName("Wolf");
}


Wolf::Wolf(std::string mName, int startingHP)
    : Monster( {15,0,0,startingHP,0,0},2,5) {
    setName(mName);
}

//Wolf::Wolf()
//    : Monster({15,0,0,startingHP,0,0},2,5)
//{
//
//}
//

#include "buffs.h"

//============================
// Buff & subclasses
//============================

Buff::Buff() {};
Buff::Buff(std::string buffName, bool dispel, int dur) {
    name = buffName;
    canDispel = dispel;
    duration = dur;
    turnsLeft = duration;
}

void Buff::checkExpire() {
    if (turnsLeft <= 0) {
        //TODO Remove self
    }
}

DoT::DoT() {}

DoT::DoT(std::string buffName, bool dispel, int dur, Points dmg)
    : Buff(buffName, dispel, dur) {

}

void DoT::tick(Creature &c) {
    c.damage(tickDamage);
    turnsLeft -= 1;
    checkExpire();
}


//============================
// Specific buffs
//============================
//Moved to skills.cpp
//
//buff_FlameTouch::buff_FlameTouch()
//    : DoT ("Flame Touch burn", true, 3, 1,0,0) {
//}

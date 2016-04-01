#include "buffs.h"
#include <iostream>

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


std::string Buff::getName() {
    return name;
}

void Buff::apply(Creature &tgt) {
//TODO:  If already there, check stacking
    tgt.buffs.push_back(this);
}

bool Buff::isExpired() {
    if (turnsLeft <= 0) {
       return true;
    } else return false;
}

void dispel() {

}

void Buff::tick(Creature &c) {
    std::cerr << "Buff::tick called on: " << c.getName() << std::endl;
    turnsLeft -= 1;
    isExpired();
}

DoT::DoT() {}

DoT::DoT(std::string buffName, bool dispel, int dur, Points dmg)
    : Buff(buffName, dispel, dur) {
    tickDamage = dmg;
}

void DoT::tick(Creature &c) {
    c.damage(tickDamage);
    turnsLeft -= 1;
}

Buff* DoT::Clone() {
    return new DoT(*this);
}

void runBuffs(Creature &c) {
    //Save buffs to remove after running them
    //Can't remove during iterator or *BOOM*
    std::list<Buff*> expiredBuffs;
    std::list<Buff*>::const_iterator it;

    for (it = c.buffs.begin(); it != c.buffs.end(); it++) {
        (*it)->tick(c); //Exec buff effects

        if ((*it)->isExpired()) {
            expiredBuffs.push_back(*it);
        }

    }

    for (it = expiredBuffs.begin(); it != expiredBuffs.end(); it++) {
        c.buffs.remove(*it);
    }

}

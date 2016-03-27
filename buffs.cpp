#include "buffs.h"

//============================
// Buff & subclasses
//============================


Buff::Buff(bool dispel, int dur) {
    canDispel = dispel;
    duration = dur;
    turnsLeft = duration;
}

void Buff::checkExpire() {
    if (turnsLeft <= 0) {
        //TODO Remove self
    }
}

void DoT::tick(Creature &c) {
    c.damage(tickHP,tickSP,tickMP);
    turnsLeft -= 1;
    checkExpire();
}

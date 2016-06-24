#include "buffs.h"
#include <iostream>

//Multiply elements of *identical* maps together
Stats mergeStatMaps(Stats mapA, Stats mapB) {
    Stats::const_iterator itA, itB;
    itB = mapB.begin();
    Stats result;

    for (itA = mapA.begin(); itA != mapA.end(); itA++) {
        //Take key from A, and multiply values from A and B.
        result.emplace((*itA).first, (*itA).second * (*itB).second );

        itB++;
    }
    return result;
};

int runStatMultipliers (Stats stats, Stats multipliers) {
    int totalEffect = 0;
    Stats statEffects = mergeStatMaps(stats, multipliers);
    //Sum values in statEffects map
    Stats::const_iterator it;
    for (it = statEffects.begin(); it != statEffects.end(); it++) {
        totalEffect += (*it).second;
    }

    return totalEffect;
}


bool buffExists (std::list<Buff*> buffList, std::string buffName) {
    std::list<Buff*>::const_iterator it;
    for (it = buffList.begin(); it != buffList.end(); it++) {
        if ((*it)->getName() == buffName ) {
            return true;
        }
    }
    return false;
}

Buff * findBuffInList (std::list<Buff*> buffList, std::string buffName) {
    std::list<Buff*>::const_iterator it;

    for (it = buffList.begin(); it != buffList.end(); it++) {
        if ((*it)->getName() == buffName ) {
            return *it;
        }
    }
    //either check buffExists() first, or be able to handle this!
    return nullptr;
}

void checkExpiry (std::list<Buff*> &buffs) {
    std::list<Buff*> expiredBuffs;
    std::list<Buff*>::const_iterator it;

    for (it = buffs.begin(); it != buffs.end(); it++) {
        if ((*it)->isExpired()) {
            expiredBuffs.push_back(*it);
        }
    }

    for (it = expiredBuffs.begin(); it != expiredBuffs.end(); it++) {
        (*it)->dispel(buffs);
    }
}

//============================
// Buff
//============================

Buff::Buff() {};
Buff::Buff(std::string buffName, bool dispel, bool stacks, int baseDur, Stats buffDurationMultipliers) {
    name = buffName;
    canDispel = dispel;
    this->stacks = stacks;
    baseDuration = baseDur;
    durationMultipliers = buffDurationMultipliers;
}


 int Buff::getBaseDuration() {
    return baseDuration;
 }
 Stats  Buff::getDurationMultipliers() {
    return durationMultipliers;
 }

std::string Buff::getName() {
    return name;
}

skillDamageType Buff::getDamageType() {
    return damageType;
}

//Only override if special stacking mechanics - ie doesn't stack with other buff type
void Buff::apply(Creature &tgt) {



    if (stacks) {
        tgt.buffs.push_back(this);

    } else if ( not buffExists(tgt.buffs, name) ) {
        tgt.buffs.push_back(this);

    } else {
        //Since it doesn't stack, there SHOULD be only one to dispel
        findBuffInList(tgt.buffs, name)->dispel(tgt.buffs);
        tgt.buffs.push_back(this);
    }
}

bool Buff::isExpired() {
    if (turnsLeft <= 0) {
       return true;
    } else return false;
}

void Buff::dispel(std::list<Buff*> &buffs) {
    std::list<Buff*> expiredBuffs;
    std::list<Buff*>::const_iterator it;

    for (it = buffs.begin(); it != buffs.end(); it++) {
        if (*it == this) {
            expiredBuffs.push_back(*it);
        }
    }

    for (it = expiredBuffs.begin(); it != expiredBuffs.end(); it++) {
        buffs.remove(*it);
    }
}

//Default tick actions if not overridden
void Buff::pre_tick(Creature &c) { }

//Anything overriding this should call it at the end
//  unless it's doing something different with duration
void Buff::post_tick(Creature &c) {
    turnsLeft -= 1;
}

//============================
// DoT
//============================

DoT::DoT() {}

DoT::DoT(std::string buffName, bool dispel, bool stacks, int baseDur, Stats buffDurationMultipliers, Points dmg)
    : Buff(buffName, dispel, stacks, baseDur, buffDurationMultipliers) {
    tickDamage = dmg;
}

void DoT::post_tick(Creature &c) {
    c.damage(tickDamage, getDamageType());

    turnsLeft -= 1;
}

Buff* DoT::Clone() {
    return new DoT(*this);
}


//============================
// DamageMod
//============================

DamageMod::DamageMod() {}

DamageMod::DamageMod(std::string buffName, bool dispel, bool stacks, int baseDur, Stats buffDurationMultipliers, BuffTurnMultipliers buffEffects)
    : Buff(buffName, dispel, stacks, baseDur, buffDurationMultipliers) {
    effects = buffEffects;
}

void DamageMod::pre_tick(Creature &c) {
    //Yes, we want to apply every tick, because these effects are cleared every turn.
    c.mergeBuffTurnMultipliers(effects);
}

Buff* DamageMod::Clone() {
    return new DamageMod(*this);
}

//============================
// Extra functions
//============================

//Process all buff effects for this turn for a given Creature
void runPreBuffs(Creature &c) {
    std::list<Buff*>::const_iterator it;

    for (it = c.buffs.begin(); it != c.buffs.end(); it++) {
        (*it)->pre_tick(c); //Apply this buff's effects

    }
}

void runPostBuffs(Creature &c) {
    std::list<Buff*>::const_iterator it;

    for (it = c.buffs.begin(); it != c.buffs.end(); it++) {
        (*it)->post_tick(c); //Apply this buff's effects

    }
}

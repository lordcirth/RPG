#pragma once
#include "creature.h"
#include <string>

//============================
// Buff & general subclasses
//============================

class Buff
{
    std::string name;
    //Whether buff/debuff can be purged/dispelled
    bool canDispel;
    bool stacks;
    int duration;  //Starting duration - set by subclass ctors

public:
    int turnsLeft;
    Buff(); //Not used!
    Buff(std::string buffName, bool dispel, int dur);

    virtual Buff* Clone() = 0; //All subclasses must define this!

    virtual void tick(Creature &c);  //virtual, process buff for this turn
    void dispel(); //remove buff (dispel or expiry)
    void apply(Creature &tgt); //Handles stacking rules, etc
    bool isExpired(); //Time to remove buff?
};

//Damage over Time, poison, fire, etc
class DoT : public Buff   //Also Heal over Time maybe? Just use negative tickHP
{
    //Damage per turn
    Points tickDamage;
public:
    virtual Buff* Clone();
    DoT();
    DoT(std::string buffName, bool dispel, int dur, Points dmg);
    void tick(Creature &c);
};


void runBuffs(Creature &c);

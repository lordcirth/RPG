#pragma once
#include "creature.h"
#include <string>

int runStatMultipliers (Stats stats, Stats multipliers);
bool buffExists (std::list<Buff*> buffList, std::string buffName);
void checkExpiry (std::list<Buff*> &buffs);



//============================
// Buff & general subclasses
//============================

class Buff
{
    std::string name;
    //Whether buff/debuff can be purged/dispelled
    bool canDispel;
    bool stacks;
    int baseDuration;  //Starting duration - set by subclass ctors
    Stats durationMultipliers;
    skillDamageType damageType;

public:
    int turnsLeft;
    Buff(); //Not used!
    Buff(std::string buffName, bool dispel, bool stacks, int dur, Stats buffDurationMultipliers);
    int getBaseDuration();
    Stats getDurationMultipliers();
    std::string getName();
    skillDamageType getDamageType();

    virtual Buff* Clone() = 0; //All subclasses must define this!

    virtual void Pre_tick(Creature &c);  //virtual, process buff for this turn
    virtual void Post_tick(Creature &c);  //virtual, process buff for this turn
    void dispel(std::list<Buff*> &buffs); //remove buff (dispel or expiry)
    void apply(Creature &tgt); //Handles stacking rules, etc
    bool isExpired(); //Time to remove buff?
};

//Damage over Time, poison, fire, etc
class DoT : public Buff   //Also Heal over Time maybe? Just use negatives!
{
    //Damage per turn
    Points tickDamage;
public:
    Buff* Clone();
    DoT();
    DoT(std::string buffName, bool dispel, bool stacks, int dur, Stats buffDurationMultipliers, Points dmg);

    void Post_tick(Creature &c);
};

class DamageMod : public Buff
{
    BuffTurnMultipliers effects;
public:
    Buff* Clone();
    DamageMod();
    DamageMod(std::string buffName, bool dispel, bool stacks, int dur, Stats buffDurationMultipliers, BuffTurnMultipliers buffEffects);

    void tick(Creature &c);
};


void runPreBuffs(Creature &c);
void runPostBuffs(Creature &c);

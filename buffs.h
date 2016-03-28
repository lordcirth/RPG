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

    int duration;  //Starting duration - set by subclass ctors
    //



public:
    int turnsLeft;
    Buff(); //Not used!
    Buff(std::string buffName, bool dispel, int dur);

    void tick(Creature &c);  //virtual, process buff for this turn
    void purge(); //virtual, attempt to purge
    void apply(Creature &tgt); //Handles stacking rules, etc
    void checkExpire(); //Remove buff if time is up
};

//Damage over Time, poison, fire, etc
class DoT : public Buff   //Also Heal over Time, just use negative tickHP
{

    //Damage per turn
    int tickHP;
    int tickSP;
    int tickMP;
    bool stacks;

public:
    DoT();
    DoT(std::string buffName, bool dispel, int dur, int tickHP, int tickSP, int tickMP);
    void tick(Creature &c);
};

//============================
// Specific buffs
//============================
//
//class buff_FlameTouch : public DoT
//{
//public:
//    buff_FlameTouch();
//};

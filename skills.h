#pragma once

#include <list>
#include <memory>
#include <map>
#include "creature.h" //Stats and Points structs
#include "buffs.h"

//============================
// Skill & subclasses
//============================

class Skill {
    //Pointer to parent in skill tree
    const Skill *parent;
    bool unlocked;
    std::string name;
public:

    virtual void Use(Creature &caster);
    virtual void Use(Creature &caster, Creature &target);
    std::string getName();
    Skill();
    Skill(bool startsUnlocked, std::string name);
    Skill(Skill &parentNode, std::string name);
};

class Heal : public Skill {
    //Sane default 0
    //ctors overwrite
    int HP;
    int SP;
    int MP;

public:
    void Use(Creature &caster);
    Heal();
    Heal(bool startsUnlocked, std::string name, int healHP, int healSP, int healMP);
    Heal(Skill &parentNode, std::string name, int healHP, int healSP, int healMP);

};

class Melee : public Skill {

    int baseDmg;

    //If 0, not used
    //Else, each multiplied by stat and added (subject to change)
    int strDmgFactor;
    int dexDmgFactor;

public:

    void Use(Creature &caster, Creature &target);
    Melee();
    Melee(bool startsUnlocked, std::string skillName, int baseDmg, int strDmg, int dexDmg);
};

//Flame touch, ice, necro?, etc
class magicTouch : public Skill {
    //Direct damage
    int baseDmg;
    int pwrDmgFactor;
    int ctlDmgFactor;

    Buff debuff;

//    int baseDuration;
//    int stabilityDurationFactor;

public:
    magicTouch();
    magicTouch(Skill &parentNode, std::string name, int bDmg, int powerDmg, int controlDmg, Buff &buff);
};

//typedef std::map<std::string,Heal> healPtrMap;
//typedef std::map<std::string,Melee> meleePtrMap;

typedef std::list<Skill*> skillPtrList;
skillPtrList createSkillPtrList();

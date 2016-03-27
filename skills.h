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

    void Use(Creature &caster);
    void Use(Creature &caster, Creature &target);
    std::string getName();
    Skill();
    Skill(bool startsUnlocked, std::string name);
    Skill(Skill &parentNode, std::string name);
};

class Heal : public Skill {
    //Sane default 0
    //ctors overwrite
    int HP = 0;
    int SP = 0;
    int MP = 0;

public:
    Heal();
    Heal(bool startsUnlocked, std::string name, int healHP, int healSP, int healMP);
    Heal(Skill &parentNode, std::string name, int healHP, int healSP, int healMP);
    void Use(Creature &caster);
};

class Melee : public Skill {
private:

    //If 0, not used
    //Else, each multiplied by stat and added (subject to change)
    int strDmgFactor;
    int dexDmgFactor;

public:
    int baseDmg = 0;
    void Use(Creature &caster, Creature &target);
    Melee();
    Melee(bool startsUnlocked, std::string skillName, int baseDmg, int strDmg, int dexDmg);
};

typedef std::map<std::string,Heal> healPtrMap;
typedef std::map<std::string,Melee> meleePtrMap;

typedef std::list<Skill*> skillPtrList;
skillPtrList createSkillPtrList();

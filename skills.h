#pragma once

#include <list>
#include <memory>
#include <map>
#include "creature.h" //Stats and Points structs

class Skill
{
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

class Heal : public Skill
{
    //Default 0
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

class Melee : public Skill
{
private:

    int strDmgFactor;
    int dexDmgFactor;

public:
    int baseDmg = 0;
    void Use(Creature &caster, Creature &target);
    Melee();
    Melee(int strDmgFactor, int dexDmgFactor);
};

typedef std::map<std::string,Heal> healPtrMap;
typedef std::map<std::string,Melee> meleePtrMap;

struct skillList
{
    healPtrMap heals;
    meleePtrMap melees;
};

skillList createSkillStruct();


typedef std::list<Skill*> skillPtrList;
skillPtrList createSkillPtrList();

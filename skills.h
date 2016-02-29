#pragma once

#include <list>
#include <memory>
#include <map>
#include "creature.h" //Stats and Points structs

class Skill
{
    //Pointer to parent in skill tree
    Skill *parent;
    bool unlocked;
public:

    void Use(Creature &caster);
    void Use(Creature &caster, Creature &target);
    Skill();
    Skill(bool startsUnlocked);
    Skill(const Skill &parentNode);
};

class Heal : public Skill
{
    //Default 0
    //ctors overwrite
    int HP = 0;
    int SP = 0;
    int MP = 0;

public:
    Heal(); //Testing only!
    Heal(int healHP);
    Heal(bool startsUnlocked, int healHP);
    Heal(Skill parentNode, bool startsUnlocked, int healHP);
    Heal(const Skill &parentNode, int healHP, int healSP, int healMP);
    void Use(Creature &caster);
};

typedef std::map<std::string,Heal> healPtrMap;

struct skillList
{
    healPtrMap heals;
};

skillList createSkillStruct();

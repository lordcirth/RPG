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
    bool passive = false;

public:
    const char shortcut;
    virtual void Use(Creature &caster);
    virtual void Use(Creature &caster, Creature &target);
    std::string getName();
    bool isUnlocked() const;
    bool canUnlock();
    void unlock();

    Skill() : shortcut('@') {}; //Required by compiler.  If we ever see '@' as a hotkey, something broke!
    Skill(bool startsUnlocked, bool isPassive, Skill *parentNode, char key, std::string name);
    //Skill(, std::string name);

    // ~Skill();
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
    Heal(bool startsUnlocked, Skill *parentNode, char key, std::string name, int healHP, int healSP, int healMP);
    //Heal(std::string name, int healHP, int healSP, int healMP);

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
    Melee(bool startsUnlocked, Skill *parentNode, char key, std::string skillName, int bDmg, int strDmg, int dexDmg);
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
    magicTouch(bool startsUnlocked, Skill *parentNode, char key, std::string name, int bDmg, int powerDmg, int controlDmg, Buff &buff);
};

//typedef std::map<std::string,Heal> healPtrMap;
//typedef std::map<std::string,Melee> meleePtrMap;

typedef std::list<Skill*> skillPtrList;
skillPtrList createSkillPtrList();
void populateSkillPtrList (skillPtrList& skillPtrs);
//
//typedef std::list<std::shared_ptr<Skill>> skillSharedPtrList;
//skillSharedPtrList createSafeSkillList();

Skill * getSkillByHotkey(skillPtrList &skillPtrs, char key);

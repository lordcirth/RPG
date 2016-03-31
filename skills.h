#pragma once

#include <list>
#include <memory>
#include <map>
#include "creature.h" //Stats and Points structs
#include "buffs.h"

enum skillTargetType {
    TYPE_SELF,
    TYPE_ENEMY
};

//============================
// Skill & subclasses
//============================

class Skill {
    //Pointer to parent in skill tree
    const Skill *parent;
    bool unlocked;
    std::string name;
    bool passive = false;
    skillTargetType targetType;
    Points cost;

public:
    const char shortcut;
    virtual void Use(Creature &caster);
    virtual void Use(Creature &caster, Creature &target);
    std::string getName();
    Points getCost();

    bool isUnlocked() const;
    bool canUnlock();
    void unlock();

    skillTargetType getTargetType();

    Skill() : shortcut('@') {}; //Required by compiler.  If we ever see '@' as a hotkey, something broke!
    Skill(skillTargetType type, bool startsUnlocked, bool isPassive, Skill *parentNode, char key, std::string name, Points cost);
};

class Heal : public Skill {
    //Stored as negative (damage)
    Points baseHealPoints;

public:
    void Use(Creature &caster);
    Heal();
    Heal(bool startsUnlocked, Skill *parentNode, char key, std::string name, Points costPoints, Points basePointsToHeal);
};

class Melee : public Skill {
    int baseDamage; //TODO replace baseDamage with Points

    //If 0, not used
    //Else, each multiplied by stat and added (subject to change)
    Stats statDamageFactors;

public:

    void Use(Creature &caster, Creature &target);
    Melee();
    Melee(bool startsUnlocked, Skill *parentNode, char key, std::string skillName, Points costPoints, int bDmg, Stats damageFactors );
};

//Flame touch, ice, necro?, etc
class MagicTouch : public Skill {
    //Direct damage
    int baseDamage; //TODO replace baseDamage with Points
    Stats statDamageFactors;

    Buff *debuff;

public:
    void Use(Creature &caster, Creature &target);
    MagicTouch();
    MagicTouch(bool startsUnlocked, Skill *parentNode, char key, std::string name, Points costPoints, int bDmg, Stats damageFactors, Buff *buff);
};

//typedef std::map<std::string,Heal> healPtrMap;
//typedef std::map<std::string,Melee> meleePtrMap;

typedef std::list<Skill*> skillPtrList;
skillPtrList createSkillPtrList();
void populateSkillPtrList (skillPtrList& skillPtrs);

//typedef std::list<std::shared_ptr<Skill>> skillSharedPtrList;
//skillSharedPtrList createSafeSkillList();

Skill * getSkillByHotkey(skillPtrList &skillPtrs, char key);

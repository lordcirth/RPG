#include "skills.h"
#include <memory>
#include <iostream>
#include <unistd.h>
#include "player.h"

//============================
// Skill & subclasses
//============================

std::string Skill::getName() {
    return name;
}

// Skill::getNameC() {
//    return name.c_str();
//}

bool Skill::isUnlocked() const {
    return unlocked;
}

bool Skill::canUnlock() {
    return parent->isUnlocked();
}

void Skill::unlock() {
    unlocked = true;
}

skillTargetType Skill::getTargetType() {
    return targetType;
};

//
//Skill::Skill() {
//
//}

Skill::Skill(skillTargetType type, bool startsUnlocked, bool isPassive, Skill *parentNode, char key, std::string skillName, Points costPoints) : shortcut(key) {
    targetType = type;
    unlocked = startsUnlocked;
    passive = isPassive;
    parent = parentNode;
    //shortcut = key;
    name = skillName;
    cost = costPoints;
}

void Skill::Use(Creature &caster) {
    std::cerr << "Error: Skill::Use(Creature &caster) called!" << std::endl;
}

void Skill::Use(Creature &caster, Creature &target) {
    std::cerr << "Error: Skill::Use(Creature &caster, Creature &target) called!" << std::endl;
}

Points Skill::getCost() {
    return cost;
}

//Heal
Heal::Heal() {
}

Heal::Heal(bool startsUnlocked, Skill *parentNode, char key, std::string name, Points costPoints, Points pointsToHeal)
    : Skill(TYPE_SELF, startsUnlocked, false, parentNode, key, name, costPoints) { //Pass through to Skill constructor
    baseHealPoints = pointsToHeal;

}

void Heal::Use(Creature &caster) {
    caster.heal(baseHealPoints);
    //std::cout << "Healing";
}

//Melee

Melee::Melee() {
}

Melee::Melee(bool startsUnlocked, Skill *parentNode, char key, std::string skillName, Points costPoints, int baseDmg, Stats damageFactors )
    : Skill(TYPE_ENEMY, startsUnlocked, false, parentNode, key, skillName, costPoints) {
    baseDamage = baseDmg;
    statDamageFactors = damageFactors;

}

void Melee::Use(Creature &caster, Creature &target) {
    int dmg = baseDamage;
    Stats s = statDamageFactors;
    dmg += s.strength * caster.getStats().strength;
    dmg += s.dexterity * caster.getStats().dexterity;

    target.damage({dmg,0,0});
}

//MagicTouch

void MagicTouch::Use(Creature &caster, Creature &target) {
    if (caster.getPointValues().MP >= getCost().MP) {
        caster.damage(getCost());
        target.damage({baseDamage,0,0});
        debuff->Clone()->apply(target);
    }
}

MagicTouch::MagicTouch() {}


MagicTouch::MagicTouch(bool startsUnlocked, Skill *parentNode, char key, std::string name, Points costPoints, int baseDmg,  Stats damageFactors,  Buff *buff)
    : Skill(TYPE_ENEMY, startsUnlocked, false, parentNode, key, name, costPoints) {
    baseDamage = baseDmg;
    statDamageFactors = damageFactors;
    debuff = buff;
}


//=============================
// Provide Skill Tree
//=============================


skillPtrList createSkillPtrList() {
    skillPtrList skillPtrs;
    Points cost_none {0,0,0};
    static Skill RootSkill {TYPE_SELF, true, true, nullptr, '#', "RootSkill", cost_none}; //Empty parent node of everything, only time using default ctor
    RootSkill.unlock();
    //Not added to skill list

//Tier 0: Unlocked by default
    static Heal Rest {true, &RootSkill, 'r', "Rest", cost_none, {1,1,1}}; //Root of Mage tree
    skillPtrs.push_back(&Rest);

    Stats multipliers_Hit;
        multipliers_Hit.strength = 1;                      // 1 + 1*STR damage
    static Melee Hit {true, &RootSkill, 'h', "Hit", cost_none, 1, multipliers_Hit}; //Root of Warrior tree
    skillPtrs.push_back(&Hit);

//Tier 1: First unlockables
    Points cost_FlameTouch {0,0,2};
    Stats multipliers_FlameTouch;
        multipliers_FlameTouch.power = 1;
    static DoT buff_FlameTouch {"Flame Touch burn", true, 3, {1,0,0}};
    static MagicTouch FlameTouch {false, &Rest, 'f', "Flame Touch", cost_FlameTouch, 2, multipliers_FlameTouch, &buff_FlameTouch};
    skillPtrs.push_back(&FlameTouch);

    return skillPtrs;

    //Sample usage
    //std::cout << skillPtrs.front()->getName();
}

//Returns nullptr if not a valid skill.  Caller must handle this.
Skill * getSkillByHotkey(skillPtrList &skillPtrs, char key) {
    Skill *chosenSkill = nullptr;
    std::list<Skill*>::const_iterator it;

    for (it = skillPtrs.begin(); it != skillPtrs.end(); it++) {
        //First deref for iterator -> content, second for pointer -> Skill
        if (  ((**it).shortcut) == key  ) {
            chosenSkill = *(it);
            break;
        }
    }
    return chosenSkill;
}

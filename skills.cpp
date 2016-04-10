#include "skills.h"
#include <memory>
#include <iostream>
#include <unistd.h>
#include "player.h"

//============================
// Skill & subclasses
//============================

bool Skill::checkCost(Creature &caster) {
    CreaturePoints points = caster.getPointValues();

    if (points.HP < cost.HP) { return false; }
    else if (points.SP < cost.SP) { return false; }
    else if (points.MP < cost.MP) { return false; }
    else {return true;}
}

skillReturnType Skill::canCast(Creature &caster) {
    if (checkCost(caster) == false) {
        return SKILL_FAIL_COST;
    }
    else if (isUnlocked() == false) {
        return SKILL_NOT_UNLOCKED;
    }
    else {
        return SKILL_SUCCESS;
    }
}

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

skillReturnType Skill::Use(Creature &caster) {
    std::cerr << "Error: Skill::Use(Creature &caster) called!" << std::endl;
    return SKILL_BASE_CLASS_ERROR;
}

skillReturnType Skill::Use(Creature &caster, Creature &target) {
    std::cerr << "Error: Skill::Use(Creature &caster, Creature &target) called!" << std::endl;
    return SKILL_BASE_CLASS_ERROR;
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

skillReturnType Heal::Use(Creature &caster) {
    skillReturnType r = canCast(caster);
    if (r == SKILL_SUCCESS) {
        caster.damage(getCost());
        caster.heal(baseHealPoints);
    }
    return r;
}

//Melee

Melee::Melee() {
}

Melee::Melee(bool startsUnlocked, Skill *parentNode, char key, std::string skillName, Points costPoints, int baseDmg, Stats damageFactors )
    : Skill(TYPE_ENEMY, startsUnlocked, false, parentNode, key, skillName, costPoints) {
    baseDamage = baseDmg;
    statDamageFactors = damageFactors;

}

skillReturnType Melee::Use(Creature &caster, Creature &target) {
skillReturnType r = canCast(caster);
    if (r == SKILL_SUCCESS) {
        caster.damage(getCost());

        int dmg = baseDamage;
        Stats s = statDamageFactors;
        dmg += s.strength * caster.getStats().strength;
        dmg += s.dexterity * caster.getStats().dexterity;

        target.damage({dmg,0,0});
    }
    return r;


}

//MagicTouch

skillReturnType MagicTouch::Use(Creature &caster, Creature &target) {
    skillReturnType r = canCast(caster);

    if (r == SKILL_SUCCESS) {
        caster.damage(getCost());
        int dmg = baseDamage + runMultipliers(caster.getStats(), statDamageFactors);
        target.damage({dmg ,0,0});

        //Clone the "master copy" of the buff
        Buff *newBuff = debuff->Clone();

        //set buff duration based on stats
        newBuff->turnsLeft = debuff->getBaseDuration() + runMultipliers(caster.getStats(), debuff->getDurationMultipliers());
        newBuff->apply(target);
    }
    return r;
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
    Stats multipliers_none = {0,0,0,0,0,0};
    static Skill RootSkill {TYPE_SELF, true, true, nullptr, '#', "RootSkill", cost_none}; //Empty parent node of everything, only time using default ctor
    RootSkill.unlock();
    //Not added to skill list

//Tier 0: Unlocked by default
    //Heal::Heal(bool startsUnlocked, Skill* parentNode, char key, std::string name, Points costPoints, Points basePointsToHeal);
    static Heal Rest {true, &RootSkill, 'r', "Rest", cost_none, {1,1,1}}; //Root of Mage tree
    skillPtrs.push_back(&Rest);


    Stats multipliers_Hit;
        multipliers_Hit.strength = 1;                      // 1 + 1*STR damage
    static Melee Hit {true, &RootSkill, 'h', "Hit", cost_none, 1, multipliers_Hit}; //Root of Warrior tree
    skillPtrs.push_back(&Hit);

//Tier 1: First unlockables

    //Flame Touch
    //                          name                dispel, stacks, duration,   duration mults,     damage
    static DoT buff_FlameTouch {"Flame Touch burn", true, false,    4,          multipliers_none,   {1,0,0}};

    Points cost_FlameTouch {0,0,2};
    Stats multipliers_FlameTouch_damage; //Inits with 0's
        multipliers_FlameTouch_damage.power = 1;

    static MagicTouch FlameTouch {false, &Rest, 'f', "Flame Touch", cost_FlameTouch, 1, multipliers_FlameTouch_damage, &buff_FlameTouch};
    skillPtrs.push_back(&FlameTouch);

    FlameTouch.unlock(); //Debug

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

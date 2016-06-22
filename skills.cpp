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

Skill::Skill(skillTargetType type, skillDamageType damageType, bool startsUnlocked, bool isPassive, Skill *parentNode, char key, std::string skillName, std::string skillDescription, Points costPoints) : shortcut(key) {
    targetType = type;
    this->damageType = damageType;
    unlocked = startsUnlocked;
    passive = isPassive;
    parent = parentNode;
    //shortcut = key;
    name = skillName;
    description = skillDescription;
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

skillDamageType Skill::getDamageType() {
    return damageType;
}

//Heal
Heal::Heal() {
}

Heal::Heal(bool startsUnlocked, Skill *parentNode, char key, std::string name, std::string skillDescription, Points costPoints, Points pointsToHeal)
    : Skill(TYPE_SELF, DMGTYPE_NONE, startsUnlocked, false, parentNode, key, name, skillDescription, costPoints) { //Pass through to Skill constructor
    baseHealPoints = pointsToHeal;

}

skillReturnType Heal::Use(Creature &caster) {
    skillReturnType r = canCast(caster);
    if (r == SKILL_SUCCESS) {
        caster.takeCost(getCost());
        caster.heal(baseHealPoints);
    }
    return r;
}

//Melee

Melee::Melee() {
}

Melee::Melee(bool startsUnlocked, Skill *parentNode, char key, std::string skillName, std::string skillDescription, Points costPoints, int baseDmg, Stats damageFactors )
    : Skill(TYPE_ENEMY, DMGTYPE_PHYSICAL, startsUnlocked, false, parentNode, key, skillName, skillDescription, costPoints) {
    baseDamage = baseDmg;
    statDamageFactors = damageFactors;

}

skillReturnType Melee::Use(Creature &caster, Creature &target) {
skillReturnType r = canCast(caster);
    if (r == SKILL_SUCCESS) {
        caster.takeCost(getCost());

        Points dmg = {0,0,0};
        dmg.HP = baseDamage + runStatMultipliers(caster.getStats(), statDamageFactors);
        dmg = caster.runDamageMultipliers(dmg, getDamageType());

        target.damage(dmg, getDamageType());
    }
    return r;

}

//MagicTouch

skillReturnType MagicTouch::Use(Creature &caster, Creature &target) {
    skillReturnType r = canCast(caster);

    if (r == SKILL_SUCCESS) {
        caster.takeCost(getCost());
        Points dmg = {0,0,0};
        dmg.HP = baseDamage + runStatMultipliers(caster.getStats(), statDamageFactors);
        dmg = caster.runDamageMultipliers(dmg, getDamageType());
        target.damage(dmg, getDamageType());

        //Clone the "master copy" of the buff
        Buff *newBuff = debuff->Clone();

        //set buff duration based on stats
        newBuff->turnsLeft = debuff->getBaseDuration() + runStatMultipliers(caster.getStats(), debuff->getDurationMultipliers());
        newBuff->apply(target);
    }
    return r;
}

MagicTouch::MagicTouch() {}


MagicTouch::MagicTouch(bool startsUnlocked, Skill *parentNode, char key, std::string name, std::string skillDescription, Points costPoints, int baseDmg,  Stats damageFactors,  Buff *buff)
    : Skill(TYPE_ENEMY, DMGTYPE_MAGICAL, startsUnlocked, false, parentNode, key, name, skillDescription, costPoints) {
    baseDamage = baseDmg;
    statDamageFactors = damageFactors;
    debuff = buff;
}

//=============================
// Provide Skill Tree
//=============================

Skill * getSkill_RootSkill() {  //Empty parent node of everything, only time using Skill directly
    Skill *RootSkill;
    RootSkill = new Skill {TYPE_SELF, DMGTYPE_NONE, true, true, nullptr, '#', "RootSkill", "RootSkill", {0,0,0}};
    //RootSkill->unlock();
    return RootSkill;
}

skillPtrList createSkillPtrList() {
    skillPtrList skillPtrs;
    Points cost_none {0,0,0};
    Stats multipliers_none = {0,0,0,0,0,0};
    Skill RootSkill = *getSkill_RootSkill();



    //Not added to skill list

//Tier 0: Unlocked by default

    Skill *skill_Rest;
    skill_Rest = new Heal (true, &RootSkill, 'r', "Rest", "Rest a turn", cost_none, {1,1,1}); //Root of Mage tree
    skillPtrs.push_back(skill_Rest);


    Stats multipliers_Hit;
        multipliers_Hit.strength = 1;                      // 1 + 1*STR damage
    Skill *skill_Hit;
    skill_Hit = new Melee  (true, &RootSkill, 'h', "Hit", "Hit an enemy", cost_none, 1, multipliers_Hit); //Root of Warrior tree
    skillPtrs.push_back(skill_Hit);

//Tier 1: First unlockables


    //Flame Touch
    //                              name                dispel, stacks, duration,   duration mults,     damage
    Buff * buff_FlameTouch;
    buff_FlameTouch = new DoT       ("Flame Touch burn", true, false,    4,          multipliers_none,   {1,0,0});

    Points cost_FlameTouch {0,0,2};
    Stats multipliers_FlameTouch_damage; //Inits with 0's
        multipliers_FlameTouch_damage.power = 1;

    Skill *skill_FlameTouch;
    skill_FlameTouch = new MagicTouch (false, skill_Rest, 'f', "Flame Touch", "Scorch your enemy with your burning hand", cost_FlameTouch, 1, multipliers_FlameTouch_damage, buff_FlameTouch);
    skillPtrs.push_back(skill_FlameTouch);

    skill_FlameTouch->unlock(); //Debug


    //Frost Touch
    BuffTurnMultipliers effects_IceTouch;   //Inits to 1's
        effects_IceTouch.physicalDamageOutput = 0.5; //Debug, deals no physical dmg
    Buff * buff_IceTouch;
    //                              name                dispel, stacks, duration,   duration mults,     damage
    buff_IceTouch = new DamageMod ("Ice Touch slow", true, false, 4,            multipliers_none, effects_IceTouch);
    Points cost_IceTouch = {0,0,2};

    Stats multipliers_IceTouch_damage; //Inits with 0's
        multipliers_IceTouch_damage.power = 1;

    Skill *skill_IceTouch;
    skill_IceTouch = new MagicTouch (false, skill_Rest, 'i', "Ice Touch", "Impair your enemy with a freezing touch", cost_IceTouch, 1, multipliers_IceTouch_damage, buff_IceTouch);
    skillPtrs.push_back(skill_IceTouch);

    skill_IceTouch->unlock(); //Debug



    //Smash
    Stats multipliers_Smash;
        multipliers_Smash.strength = 2;     // 2 * STR damage
    Skill *skill_Smash;
    skill_Smash = new Melee  (false, skill_Hit, 's', "Smash", "A strike depending on sheer strength", {0,2,0}, 0, multipliers_Smash); //Root of Warrior tree
    skillPtrs.push_back(skill_Smash);
    skill_Smash->unlock();


    return skillPtrs;
}

Skill * getSkill_Strike() {
    Stats multipliers_Strike;
        multipliers_Strike.strength = 1;
    Skill *Strike;
                               // 1 + 1*STR damage
    Strike = new Melee (true, getSkill_RootSkill(), '.', "Strike", "Strike", {0,0,0}, 1, multipliers_Strike); //Root of Warrior tree
    return Strike;
}

//Default Skill list for monsters
skillPtrList createMonsterSkillList() {
    skillPtrList skillPtrs;

    //Default Monster attack - '.' for Monster hotkeys, never used
    skillPtrs.push_back(getSkill_Strike());

    return skillPtrs;
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



#include "skills.h"
#include <memory>
#include <iostream>
#include <unistd.h>
#include "player.h"

//============================
// Skill & subclasses
//============================

std::string Skill::getName() {
    //name = "Hi";
    return name;
}

//std::string Skill::getNameC() {
//    return "Rest";
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
//
//Skill::Skill( std::string skillName) {
//    parent = &parentNode;
//    unlocked = false;
//    name = skillName;
//}

//Skill::~Skill()

void Skill::Use(Creature &caster) {
    std::cerr << "Error: Skill::Use(Creature &caster) called!" << std::endl;
}

void Skill::Use(Creature &caster, Creature &target) {
    std::cerr << "Error: Skill::Use(Creature &caster, Creature &target) called!" << std::endl;
}

//Do not call! Only for std::map
Heal::Heal() {
}

Heal::Heal(bool startsUnlocked, Skill *parentNode, char key, std::string name, Points costPoints, Points pointsToHeal)
    : Skill(TYPE_SELF, startsUnlocked, false, parentNode, key, name, costPoints) { //Pass through to Skill constructor
    baseHealPoints = pointsToHeal;

}
//
//Heal::Heal(bool startsUnlocked, std::string skillName, int healHP, int healSP, int healMP)
//    : Skill(startsUnlocked, skillName) { //Pass through to Skill constructor
//    HP = healHP;
//    SP = healSP;
//    MP = healMP;
//}

void Heal::Use(Creature &caster) {
    caster.heal(baseHealPoints);
    //std::cout << "Healing";
}

//Do not call! Only for std::map, list, etc
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

MagicTouch::MagicTouch() {}

MagicTouch::MagicTouch(bool startsUnlocked, Skill *parentNode, char key, std::string name, Points costPoints, int baseDmg,  Stats damageFactors,  Buff &buff)
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
    static Heal Rest {true, &RootSkill, 'r', "Rest", {1,1,1},cost_none}; //Root of Mage tree
    skillPtrs.push_back(&Rest);

    //std::cout << Rest.getName() << std::endl; //Works "Rest"
    //std::cout << "skills: " << skillPtrs.front()->getName(); //Works "Rest"

    Stats multipliers_Hit;
        multipliers_Hit.strength = 1;                      // 1 + 1*STR damage
    static Melee Hit {true, &RootSkill, 'h', "Hit", cost_none, 1, multipliers_Hit}; //Root of Warrior tree
    skillPtrs.push_back(&Hit);
//    std::cout << skillPtrs.back()->getName();
//    std::cout << std::endl;

//Tier 1: First unlockables
    Points cost_FlameTouch {0,0,2};
    Stats multipliers_Flame_Touch;
        multipliers_Flame_Touch.power = 1;
    DoT buff_FlameTouch {"Flame Touch burn", true, 3, {1,0,0}};
    static MagicTouch FlameTouch {false, &Rest, 'f', "Flame Touch", cost_FlameTouch, 1, multipliers_Flame_Touch, buff_FlameTouch};

    return skillPtrs;

    //Sample usage
    //std::cout << skillPtrs.front()->getName();
}

Skill * getSkillByHotkey(skillPtrList &skillPtrs, char key) {
    Skill *chosenSkill = nullptr;
    std::list<Skill*>::const_iterator it;
    //bool validSkill = false;
    for (it = skillPtrs.begin(); it != skillPtrs.end(); it++) {
        //First deref for iterator -> content, second for pointer -> Skill
        if (  ((**it).shortcut) == key  ) {
            chosenSkill = *(it);
            //validSkill = true;
            break;
        }
    } //chosenSkill = RootSkill;}


//for (it = skillPtrs.begin(); it != skillPtrs.end(); it++) {
//        if (  ((**it).getName()) == "RootSkill"  )



    return chosenSkill;
}

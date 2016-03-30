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

Skill::Skill(skillTargetType type, bool startsUnlocked, bool isPassive, Skill *parentNode, char key, std::string skillName) : shortcut(key) {
    targetType = type;
    unlocked = startsUnlocked;
    passive = isPassive;
    parent = parentNode;
    //shortcut = key;
    name = skillName;
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

Heal::Heal(bool startsUnlocked, Skill *parentNode, char key, std::string name, Points pointsToHeal)
    : Skill(TYPE_SELF, startsUnlocked, false, parentNode, key, name) { //Pass through to Skill constructor
    //std::cout << parentNode.getName();
    healPoints = pointsToHeal;
}
//
//Heal::Heal(bool startsUnlocked, std::string skillName, int healHP, int healSP, int healMP)
//    : Skill(startsUnlocked, skillName) { //Pass through to Skill constructor
//    HP = healHP;
//    SP = healSP;
//    MP = healMP;
//}

void Heal::Use(Creature &caster) {
    caster.heal(healPoints);
    //std::cout << "Healing";
}

//Do not call! Only for std::map, list, etc
Melee::Melee() {
}

Melee::Melee(bool startsUnlocked, Skill *parentNode, char key, std::string skillName, int bDmg, int strDmg, int dexDmg)
    : Skill(TYPE_ENEMY, startsUnlocked, false, parentNode, key, skillName) {
    baseDmg = bDmg;
    strDmgFactor = strDmg;
    dexDmgFactor = dexDmg;

}

void Melee::Use(Creature &caster, Creature &target) {
    int dmg = baseDmg;

    dmg += strDmgFactor * caster.getStats().strength;
    dmg += dexDmgFactor * caster.getStats().dexterity;

    target.damage({dmg,0,0});
}

magicTouch::magicTouch() {}

magicTouch::magicTouch(bool startsUnlocked, Skill *parentNode, char key, std::string name, int bDmg, int powerDmg, int controlDmg, Buff &buff)
    : Skill(TYPE_ENEMY, startsUnlocked, false, parentNode, key, name) {
    baseDmg = bDmg;
    pwrDmgFactor = powerDmg;
    ctlDmgFactor = controlDmg;
    debuff = buff;
}


//=============================
// Provide Skill Tree
//=============================


skillPtrList createSkillPtrList() {
    skillPtrList skillPtrs;

    static Skill RootSkill {TYPE_SELF, true, true, nullptr, '#', "RootSkill"}; //Empty parent node of everything, only time using default ctor
    RootSkill.unlock();
    //Not added to skill list

//Tier 0: Unlocked by default
    static Heal Rest {true, &RootSkill, 'r', "Rest", {1,1,1}}; //Root of Mage tree
    skillPtrs.push_back(&Rest);

    //std::cout << Rest.getName() << std::endl; //Works "Rest"
    //std::cout << "skills: " << skillPtrs.front()->getName(); //Works "Rest"
                                // 1 + 1*STR damage
    static Melee Hit {true, &RootSkill, 'h', "Hit", 1,1,0}; //Root of Warrior tree
    skillPtrs.push_back(&Hit);
//    std::cout << skillPtrs.back()->getName();
//    std::cout << std::endl;

//Tier 1: First unlockables
    DoT buff_FlameTouch {"Flame Touch burn", true, 3, {1,0,0}};
    magicTouch FlameTouch {false, &Rest, 'f', "Flame Touch", 2, 0, 0, buff_FlameTouch};

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

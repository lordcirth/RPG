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
bool Skill::isUnlocked() {
    return unlocked;
}

Skill::Skill() {


}

Skill::Skill(bool startsUnlocked, std::string skillName) {
    unlocked = startsUnlocked;
    parent = this;
    name = skillName;
}

Skill::Skill(Skill &parentNode, std::string skillName) {
    parent = &parentNode;
    unlocked = false;
    name = skillName;
}

void Skill::Use(Creature &caster) {
    std::cout << "whyyy";
}

void Skill::Use(Creature &caster, Creature &target) {
    std::cout << "whyyy2";
}

//Do not call! Only for std::map
Heal::Heal() {
}

Heal::Heal(Skill &parentNode, std::string name, int healHP, int healSP, int healMP)
    : Skill(parentNode, name) { //Pass through to Skill constructor
    //std::cout << parentNode.getName();
    HP = healHP;
    SP = healSP;
    MP = healMP;
}

Heal::Heal(bool startsUnlocked, std::string skillName, int healHP, int healSP, int healMP)
    : Skill(startsUnlocked, skillName) { //Pass through to Skill constructor
    HP = healHP;
    SP = healSP;
    MP = healMP;
}

void Heal::Use(Creature &caster) {
    caster.damage(-HP,-SP,-MP);
    std::cout << "Healing";
}

//Do not call! Only for std::map, list, etc
Melee::Melee() {
}

Melee::Melee(bool startsUnlocked, std::string skillName, int bDmg, int strDmg, int dexDmg)
    : Skill(startsUnlocked, skillName) {
    baseDmg = bDmg;
    strDmgFactor = strDmg;
    dexDmgFactor = dexDmg;

}

void Melee::Use(Creature &caster, Creature &target) {
    int dmg = 0;

    dmg += strDmgFactor * caster.getStats().strength;
    dmg += dexDmgFactor * caster.getStats().dexterity;

    target.damage(dmg,0,0);
}

magicTouch::magicTouch() {}

magicTouch::magicTouch(Skill &parentNode, std::string name, int bDmg, int powerDmg, int controlDmg, Buff &buff)
    : Skill(parentNode, name) {
    baseDmg = bDmg;
    pwrDmgFactor = powerDmg;
    ctlDmgFactor = controlDmg;
    debuff = buff;
}


//=============================
// Provide Skill Tree
//=============================

//Must only ever be called once!
skillPtrList createSkillPtrList() {
    skillPtrList skillPtrs;

//Tier 0: Unlocked by default
    Heal Rest {true, "Rest", 1,1,1}; //Root of Mage tree
    skillPtrs.push_back(&Rest);


    //std::cout << Rest.getName() << std::endl; //Works "Rest"
    std::cout << "skills: " << skillPtrs.front()->getName() << std::endl; //Works "Rest"

    Melee Hit {true, "Hit", 0,1,0}; //Root of Warrior tree
    skillPtrs.push_back(&Hit);
    std::cout << skillPtrs.back()->getName() << std::endl;

    //std::cout <<  "Skills declared";
    //usleep(10000000); //Pause 10s so I can use htop

//Tier 1: First unlockables
    DoT buff_FlameTouch {"Flame Touch burn", true, 3, 1,0,0};
    magicTouch FlameTouch {Rest, "Flame Touch", 2, 0, 0, buff_FlameTouch};

//    Wolf skillTestWolf;
//    skillTestWolf.damage(5,0,0);
//    std::cout << skillTestWolf.getPointValues().HP;
//    skillPtrs.front()->Use(skillTestWolf);
//    std::cout << skillTestWolf.getPointValues().HP;

    return skillPtrs;
    //Sample usage
    //std::cout << skillPtrs.front()->getName();
}


//Old way:

//skillList createSkillStruct()
//{
//    skillList skills;
//
////    Heal Rest {nullptr, 1,1,1};
////    skills.heals.emplace("Rest",Rest);
//
////    Melee Hit {2,1};
////    skills.melees.emplace("Hit",Hit);
//
//    return skills;
//}

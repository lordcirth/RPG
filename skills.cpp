#include "skills.h"
#include <memory>
#include <iostream>

#include "player.h"

std::string Skill::getName()
{
    return name;
}

Skill::Skill()
{

}

Skill::Skill(bool startsUnlocked, std::string skillName)
{
    unlocked = startsUnlocked;
    parent = this;
    name = skillName;
}

Skill::Skill(Skill &parentNode, std::string name)
{
    parent = &parentNode;
    unlocked = false;
}

//============================
// subclasses of Skill
//============================

//Do not call! Only for std::map
Heal::Heal()
{
}

Heal::Heal(Skill &parentNode, std::string name, int healHP, int healSP, int healMP)
    : Skill(parentNode, name) //Pass through to Skill constructor
{
    //std::cout << parentNode.getName();
    HP = healHP;
    SP = healSP;
    MP = healMP;
}

Heal::Heal(bool startsUnlocked, std::string name, int healHP, int healSP, int healMP)
    : Skill(startsUnlocked, name) //Pass through to Skill constructor
{
    HP = healHP;
    SP = healSP;
    MP = healMP;
}

void Heal::Use(Creature &caster)
{
    caster.damage(-HP,-SP,-MP);
}

//Do not call! Only for std::map
Melee::Melee()
{
}


Melee::Melee(int bDmg, int strDmg, int dexDmg)
{
    strDmgFactor = strDmg;
    dexDmgFactor = dexDmg;
}

void Melee::Use(Creature &caster, Creature &target)
{
    int dmg = strDmgFactor * caster.getStats().strength;
    target.damage(dmg,0,0);
}


//=============================
// Provide Skill Tree
//=============================

skillList createSkillStruct()
{
    skillList skills;

//    Heal Rest {nullptr, 1,1,1};
//    skills.heals.emplace("Rest",Rest);

//    Melee Hit {2,1};
//    skills.melees.emplace("Hit",Hit);

    return skills;
}

skillPtrList createSkillPtrList()
{
    skillPtrList skillPtrs;
    Heal Rest {true, "Heal", 1,1,1};
//    std::cout << Rest.getName();
    skillPtrs.emplace_front(&Rest);

    //Sample usage
    //std::cout << skillPtrs.front()->getName();
    return skillPtrs;
}

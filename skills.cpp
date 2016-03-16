#include "skills.h"
#include <memory>
#include <iostream>

#include "player.h"

Skill::Skill()
{

}

Skill::Skill(bool startsUnlocked)
{
    //tree.skillList.emplace_front(*this);
    unlocked = startsUnlocked;
    parent = this;
}

Skill::Skill(const Skill *parentNode, std::string name)
{
    parent = parentNode;
}

//============================
// subclasses of Skill
//============================

//Testing only!
Heal::Heal()
    : Skill(false) //Pass through to Skill constructor
{
}

Heal::Heal(int healHP)
    : Skill(false) //Pass through to Skill constructor
{
    HP = healHP;
}

Heal::Heal(const Skill &parentNode, int healHP, int healSP, int healMP)
    : Skill(parentNode) //Pass through to Skill constructor
{
    HP = healHP;
    SP = healSP;
    MP = healMP;
}

void Heal::Use(Creature &caster)
{
    caster.damage(-HP,-SP,-MP);
}

Melee::Melee()
    : Skill(false)
{
}

Melee::Melee(int strDmg, int dexDmg)
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
// Provide Skill Tree as Struct
//=============================

skillList createSkillStruct()
{
    skillList skills;

    Heal Rest {true, 1,1,1};
    skills.heals.emplace("Rest",Rest);

    Melee Hit {2,1};
    skills.melees.emplace("Hit",Hit);

    return skills;
}

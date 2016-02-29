#include "skills.h"
#include <memory>
#include <iostream>

#include "player.h"

Skill::Skill()
{
    //tree.skillList.emplace_front(*this);
    //unlocked = startsUnlocked;
}

Skill::Skill(bool startsUnlocked)
{
    //tree.skillList.emplace_front(*this);
    unlocked = startsUnlocked;
    parent = this;
}

    Skill::Skill(const Skill &parentNode)
{

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

//=============================
// Provide Skill Tree as Struct
//=============================

skillList createSkillStruct()
{
    skillList skills;

    std::string restName = "Rest";
    Heal rest {true, 1,1,1};
    skills.heals.emplace(restName,rest);

    return skills;
}

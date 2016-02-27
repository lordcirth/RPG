#include "skills.h"
#include <memory>

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
}

    Skill::Skill(Skill parentNode, bool startsUnlocked)
{
    //tree.skillList.emplace_front(*this);
    unlocked = startsUnlocked;
}

//============================
// subclasses of Skill
//============================
Heal::Heal(int healHP)
    : Skill(false) //Pass through to Skill constructor
{
    HP = healHP;
}

Heal::Heal(bool startsUnlocked, int healHP)
    : Skill(startsUnlocked) //Pass through to Skill constructor
{
    HP = healHP;
}

Heal::Heal(Skill parentNode, bool startsUnlocked, int healHP)
    : Skill(parentNode, startsUnlocked) //Pass through to Skill constructor
{
    HP = healHP;
}

void Heal::Use(PlayerCharacter player)
{
    player.damage(-HP,0,0);
}


//============================
// Provide Skill Tree as Map
//============================
//
//skillPtrMap createSkillMap()
//{
//    skillPtrMap skills;
//
//    skills["Rest"] = std::make_unique<Heal>(true, 2);
//    Skill restObj = *skills["Rest"];
//    //restObj.Use
//    //skills["doNothing"] = Skill {true};


//=============================
// Provide Skill Tree as Struct
//=============================

skillList createSkillStruct()
{
    skillList skills;


    Heal rest {2};
    //skills.heals["Rest"] = Heal(2);

    return skills;
}

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

//void Heal::Use(PlayerCharacter *ptr)
//{
//    //PlayerCharacter play = ptr;
//    //*ptr->damage(-HP,0,0);
//}

PlayerCharacter Heal::Use(PlayerCharacter play)
{
    play.damage(-HP,0,0);
    return play;
}

//=============================
// Provide Skill Tree as Struct
//=============================

skillList createSkillStruct()
{
    skillList skills;
    PlayerCharacter pl;
    //PlayerCharacter *ptr = &pl;
    std::cout << displayPoints(pl.getPointValues()) << std::endl;
    pl.damage(4,0,0);
    std::cout << displayPoints(pl.getPointValues()) << std::endl;

    Heal rest {2};
    std::cout << typeid(rest).name() << std::endl;
    //rest.Use(ptr);
    pl = rest.Use(pl);
    //pl.damage(-2,0,0);
    std::cout << displayPoints(pl.getPointValues()) << std::endl;

    //skills.heals["Rest"] = rest;

    return skills;
}

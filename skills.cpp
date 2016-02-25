#include <iostream> //Temporary
#include "skills.h"
#include "player.h"

skillTree tree{};

Skill::Skill(Skill *parentNode, bool startsUnlocked)
{
    tree.skillList.emplace_front(*this);
    unlocked = startsUnlocked;
};


//Virtual function
//void Skill::Use(PlayerCharacter player)
//{
//};

// if (effects.targetsMonster)
//    {
//        //Nothing yet
//    }
//    if (effects.targetsPlayer)
//    {
//        int playerDamage = effects.playerDmg;
//        player.damage(playerDamage,0,0);
//    }


//============================
// subclasses of Skill
//============================

Heal::Heal(Skill *parentNode, bool startsUnlocked, int healHP)
    : Skill(parentNode, startsUnlocked) //Pass through to Skill constructor
{
    HP = healHP;
};

Skill Root
{
//No parent, unlocked, does nothing
    nullptr, true
};
//
//Skill Hit
//{
////parent is root, unlocked, hits enemies for 1 dmg
//&Root, true, {true, false, 1, 0}
//};
//
//
//Skill Rest
//{
////parent is root, unlocked, heals self (-1 damage)
//&Root, true, {false, true, 0, -1}
//};
//
////For debugging only!
//Skill HurtSelf
//{
////parent is root, unlocked, hurts self (1 damage)
//&Root, true, {false, true, 0, 1}
//};

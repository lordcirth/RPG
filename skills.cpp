#include <iostream> //Temporary
#include "skills.h"
#include "player.h"

Skill::Skill()
{
    //tree.skillList.emplace_front(*this);
    //unlocked = startsUnlocked;
};

Skill::Skill(bool startsUnlocked)
{
    //tree.skillList.emplace_front(*this);
    unlocked = startsUnlocked;
};

    Skill::Skill(Skill parentNode, bool startsUnlocked)
{
    //tree.skillList.emplace_front(*this);
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
Heal::Heal(bool startsUnlocked, int healHP)
    : Skill(startsUnlocked) //Pass through to Skill constructor
{
    HP = healHP;

};

Heal::Heal(Skill parentNode, bool startsUnlocked, int healHP)
    : Skill(parentNode, startsUnlocked) //Pass through to Skill constructor
{
    HP = healHP;

};

void Heal::Use(PlayerCharacter player)
{
    player.damage(-HP,0,0);
}


//============================
// Provide Skill Tree as Map
//============================

skillMap createSkillMap()
{
    skillMap skills;


    //Skill doNothing = new Skill(5, true);

    //Skill *ptr = &doNothing;
    skills["doNothing"] = {false};
    cout << to_string(skills["doNothing"].unlocked);

    //Make a Heal called Rest, +2 HP
    //skills["Heal"] = new Skill(true);


////For debugging only!
//Skill HurtSelf
//{
////parent is root, unlocked, hurts self (1 damage)
//&Root, true, {false, true, 0, 1}
//};
    return skills;
};

#include "player.h"  //Stats and Points structs
#ifndef SKILLS_H
#define SKILLS_H

struct skillEffect
{
    //eg damages enemy
    bool targetsMonster;
    //eg heals self
    bool targetsPlayer;

    int monsterDmg;
    int playerDmg; //To heal, deal negative selfDmg
};

class Skill
{
    //Pointer to parent in skill tree
    Skill *parent;
    bool unlocked;

    skillEffect effects;

    public:
    void Use(PlayerCharacter player); //Activate the skill.

    Skill(Skill *parentNode, bool startsUnlocked, skillEffect cEffects);
};



//Root of skill tree?
//Skill Root
//{
////No parent, unlocked, does nothing
//nullptr, true, {false, false}
//};

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


#endif

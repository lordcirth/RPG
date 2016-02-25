#include <list>
#include "player.h"  //Stats and Points structs
#include "monsters.h"
#ifndef SKILLS_H
#define SKILLS_H

//TODO: Create list for Skills


class Skill
{
    //Pointer to parent in skill tree
    Skill *parent;
    bool unlocked;

    //skillEffect effects;

public:
    void Use(PlayerCharacter player, Monster target); //Activate the skill.

    Skill(Skill *parentNode, bool startsUnlocked);
};

struct skillTree
{
    std::list<Skill> skillList;
};



class Heal : public Skill
{
    int HP;
    Heal(Skill *parentNode, bool startsUnlocked, int healHP);
};

//std::list<Skill> skillTree;

#endif

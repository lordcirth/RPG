#include <list>
#include <map>
#include "player.h"  //Stats and Points structs
#include "monsters.h"
#ifndef SKILLS_H
#define SKILLS_H

//TODO: Create list for Skills
using namespace std;

class Skill
{
    //Pointer to parent in skill tree
    Skill *parent;
    bool unlocked;

    //skillEffect effects;

public:
    void Use(PlayerCharacter player);
    void Use(PlayerCharacter player, Monster target);
    Skill(Skill *parentNode, bool startsUnlocked);
};

typedef map<string,Skill> skillMap;

skillMap createSkillMap();

class Heal : public Skill
{
    int HP;

public:
    Heal(Skill *parentNode, bool startsUnlocked, int healHP);
    void Use(PlayerCharacter player);
};



#endif

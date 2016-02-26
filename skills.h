#include <list>
#include <memory>
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


    //skillEffect effects;

public:
    bool unlocked;
    void Use(PlayerCharacter player);
    void Use(PlayerCharacter player, Monster target);
    Skill();
    Skill(bool startsUnlocked);
    Skill(Skill parentNode, bool startsUnlocked);
};

class Heal : public Skill
{
    int HP;

public:
    Heal(bool startsUnlocked, int healHP);
    Heal(Skill parentNode, bool startsUnlocked, int healHP);
    void Use(PlayerCharacter player);
};


typedef map<string,unique_ptr<Skill>> skillPtrMap;
typedef map<string,Skill> skillMap;

skillPtrMap createSkillMap();


#endif

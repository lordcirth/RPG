#ifndef SKILLS_H
#define SKILLS_H

#include <list>
#include <memory>
#include <map>
#include "player.h"  //Stats and Points structs
//#include "monsters.h"

//using namespace std;

class Skill
{
    //Pointer to parent in skill tree
    Skill *parent;


    //skillEffect effects;

public:
    bool unlocked;
    void Use(PlayerCharacter player);
    //void Use(PlayerCharacter player, Monster target);
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


typedef std::map<std::string,std::unique_ptr<Skill>> skillPtrMap;
typedef std::map<std::string,Skill> skillMap;

skillPtrMap createSkillMap();


#endif

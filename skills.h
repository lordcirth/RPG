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
    Skill *parent;
    bool unlocked;

    skillEffect effects;

    public:
    void Use(PlayerCharacter); //Activate the skill.

    Skill(Skill *parentNode, bool startsUnlocked, skillEffect cEffects);
};

#endif

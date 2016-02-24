#include "skills.h"
#include "player.h"
Skill::Skill(Skill *parentNode, bool startsUnlocked, skillEffect cEffects)
{
    unlocked = startsUnlocked;
    effects = cEffects;
//    targetsMonster = tgtMonster;
//    targetsPlayer = tgtPlayer;
};

void Skill::Use(PlayerCharacter player)
{
    if effects.targetsMonster
    {
        //Nothing yet
    }
    if effects.targetsPlayer
    {
        int playerDamage = effects.playerDmg;

    }
};

//Root of skill tree?
Skill root
{
//No parent, unlocked, does nothing
nullptr, true, {false, false}
};


Skill hit
{
//parent is root, unlocked, hits enemies for 1 dmg
&root, true, {true, false, 1, 0}
};


Skill rest
{
//parent is root, unlocked, heals self (-1 damage)
&root, true, {false, true, 0, -1}
};

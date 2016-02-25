#include "skills.h"
#include "player.h"
Skill::Skill(Skill *parentNode, bool startsUnlocked, skillEffect cEffects)
{
    unlocked = startsUnlocked;
    effects = cEffects;
};

void Skill::Use(PlayerCharacter player)
{
    if (effects.targetsMonster)
    {
        //Nothing yet
    }
    if (effects.targetsPlayer)
    {
        int playerDamage = effects.playerDmg;
        player.damage(playerDamage,0,0);
    }
};


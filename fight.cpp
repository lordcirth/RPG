#include "fight.h"
#include "monsters.h"
#include <iostream>

Fight::Fight(PlayerCharacter &pl, Monster &e)
{
    player = pl;
    enemy= e;
}

void Fight::start()
{
    while ( !player.isDead() && !enemy.isDead() )
    {
        //player.skills.heals["Rest"].Use(player);
        enemy.attack(player);
    }

}

#include "fight.h"
#include "monsters.h"
#include <iostream>
#include <sstream>
using namespace std;

Fight::Fight(PlayerCharacter &pl, Monster &e)
{
    player = pl;
    enemy= e;
}

fightResults Fight::start()
{
    string input = "";
    while ( !player.isDead() && !enemy.isDead())
    {
        cout << "Player: "<< endl;
        cout << displayPoints(player.getPointValues()) << endl;
        cout << "Monster: "<< endl;
        cout << displayPoints(enemy.getPointValues()) << endl;
        player.skills.melees["Hit"].Use(player,enemy);
        enemy.attack(player);
        getline(cin,input);
    }
    if (player.isDead())
    {
        cout << "You lose!";
        return fightResults {false, 0, 0};
    }
    else if (enemy.isDead())
    {
        cout << "You win!";
        return fightResults {true, 0, enemy.getXP()};
    }

}

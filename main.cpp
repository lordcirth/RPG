#include <string>
#include <iostream>
#include <memory> //unique_ptr
#include "player.h"
#include "skills.h"
#include "fight.h"

using namespace std;


int main()
{
    PlayerCharacter player;
    Monster testWolf {{5,0,0,5,0,0},2,5};
    //std::cout << testWolf.attackDamage; //2
    //player.damage(2,0,0);
    //testWolf.attack(player);
    Fight test {player, testWolf};
    fightResults testResults = test.start();

//    cout << "Start: " << endl;
//    cout << displayStats(player.getStats()) << endl;
//    cout << "Player: "<< endl;
//
//    cout << displayPoints(player.getPointValues()) << endl;
//
//    player.damage(5,2,2);
//    cout << "Damaged: " << endl;
//    cout << displayPoints(player.getPointValues()) << endl;
//
//    player.skills.heals["Rest"].Use(player);
//    cout << "Resting: " << endl;
//    cout << displayPoints(player.getPointValues()) << endl;

    return 0;
}

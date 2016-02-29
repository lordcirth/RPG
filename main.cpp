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

    cout << "Start: " << endl;
    cout << displayStats(player.getStats()) << endl;
    cout << endl;
    cout << displayPoints(player.getPointValues()) << endl;

    player.damage(5,2,2);
    cout << "Damaged: " << endl;
    cout << displayPoints(player.getPointValues()) << endl;

    player.skills.heals["Rest"].Use(player);
    cout << "Resting: " << endl;
    cout << displayPoints(player.getPointValues()) << endl;



    Monster testWolf {{5,0,0,5,0,0},5};
    Fight test {player, testWolf};
    //test.start();
    return 0;
}

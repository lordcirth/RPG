#include <string>
#include <iostream>
//#include <memory> //unique_ptr
#include "player.h"
#include "skills.h"
#include "fight.h"
#include "interface.h"

using namespace std;


int main()
{
    PlayerCharacter player("Player");
    Wolf testWolf {};

    //initSkillMenu(player);

    skillPtrList skillPtrs = createSkillPtrList();
    initSkillMenu(player);
    //Fight test {player, testWolf};
    //fightResults testResults = test.start();

    return 0;
}


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

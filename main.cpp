#include <string>
#include <iostream>
//#include <memory> //unique_ptr
#include "player.h"
#include "skills.h"
#include "fight.h"
#include "interface.h"
//#include "buffs.h"

using namespace std;


int main() {
    PlayerCharacter player("Player");

    //cout << player.skillPtrs.front()->getName() << endl;  //Works!!

    Wolf testWolf;

    Fight test {player, testWolf};
    fightResults testResults = test.start();

    return 0;
}

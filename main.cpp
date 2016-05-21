#include <string>
#include <iostream>
#include "player.h"
#include "skills.h"
#include "fight.h"
#include "interface.h"


using namespace std;


int main() {
    PlayerCharacter player("Player");
    //player.turnBuffEffects.allDamageOutput = 3; //Triple damage, debug

    Wolf testWolf;

    Fight test {player, testWolf};
    fightResults testResults = test.start();
    //cout << testResults.won << endl;

    return 0;
}

#include <string>
#include <iostream>
#include "player.h"
#include "skills.h"
#include "fight.h"
#include "interface.h"


using namespace std;


int main() {

    PlayerCharacter player("Player");
    fightResults testResults;

    do {
        Wolf testWolf;

        Fight test {player, testWolf};
        testResults = test.start();
        levelUpMenu(player);
    } while (testResults.won);

    return 0;
}

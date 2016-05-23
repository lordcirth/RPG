#include <string>
#include <iostream>
#include "player.h"
#include "skills.h"
#include "fight.h"
#include "interface.h"


using namespace std;


int main() {
    PlayerCharacter player("Player");
    while (true) {
        Wolf testWolf;

        Fight test {player, testWolf};
        fightResults testResults = test.start();
    }

    return 0;
}

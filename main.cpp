#include <string>
#include <iostream>
#include "player.h"
#include "skills.h"
#include "fight.h"
#include "interface.h"


using namespace std;


int main() {

    PlayerCharacter player("Player");
    fightResults results;

    do {
        Wolf testWolf;

        Fight test {player, testWolf};
        results = test.start();

        if (results.won) {

            player.giveXP(results.XP);

            levelUpMenu(player);
        } else {
            playerLost();
            break;
        }

    } while (true);

    cleanUpInterface();
    return 0;
}

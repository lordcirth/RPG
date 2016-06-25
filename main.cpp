#include <string>
#include <iostream>
//#include "player.h" //From fight
//#include "skills.h"
#include "fight.h"
//#include "interface.h"


using namespace std;


int main() {

    PlayerCharacter player("Player");
    fightResults results;

    do {
        player.healAll();
        Wolf testWolf;

        Fight test {player, testWolf};
        results = test.start();

        if (results.won) {

            player.giveXP(results.XP);

            skillMenu(player);
        } else {
            playerLost();
            break;
        }

    } while (true);

    cleanUpInterface();
    return 0;
}

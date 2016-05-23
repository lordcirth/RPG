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
        player.giveXP(results.XP);
        levelUpMenu(player);
    } while (results.won);

    return 0;
}

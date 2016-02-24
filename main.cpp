#include <string>
#include <iostream>
#include "player.h"
using namespace std;

int main()
{
    CreatureStats charStats {1,1,1,1,1,1};
    PlayerCharacter defaultPlayer;
    {
        10,0,0,charStats;
    };
    cout << displayStats(defaultPlayer.getStats()) << endl;

    //Increment character Strength
    CreatureStats currentStats = defaultPlayer.getStats();
    currentStats.strength++;
    defaultPlayer.setStats(currentStats);

    cout << to_string(defaultPlayer.getStats().strength) << endl;
    cout << displayStats(defaultPlayer.getStats()) << endl;
    //defaultPlayer::
    return 0;
};

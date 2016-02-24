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
    cout << displayStats(charStats) << std::endl;

    //defaultPlayer::
    return 0;
};

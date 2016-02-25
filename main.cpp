#include <string>
#include <iostream>
#include "player.h"
#include "skills.h"
using namespace std;

int main()
{
    PlayerCharacter player;

    cout << displayStats(player.getStats()) << endl;
    cout << endl;
    cout << displayPoints(player.getPointValues()) << endl;

    player.damage(1,0,0);

    cout << displayPoints(player.getPointValues()) << endl;

    player.damage(-1,0,0); //Heal

    cout << displayPoints(player.getPointValues()) << endl;

    //Hit.Use();


//cout << player.
    return 0;
};

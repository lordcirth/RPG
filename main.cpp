#include <string>
#include <iostream>
#include "player.h"
#include "skills.h"
using namespace std;


int main()
{
    PlayerCharacter player;
    cout << "Start: " << endl;
    cout << displayStats(player.getStats()) << endl;
    cout << endl;
    cout << displayPoints(player.getPointValues()) << endl;

    cout << "Damaged: " << endl;
    player.damage(5,0,0);

    cout << displayPoints(player.getPointValues()) << endl;

    cout << "Healed: " << endl;
    cout << displayPoints(player.getPointValues()) << endl;

    //Hit.Use();


//cout << player.
    return 0;
};

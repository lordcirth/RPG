#include <string>
#include <iostream>
#include "player.h"
#include "skills.h"
using namespace std;


int main()
{

    PlayerCharacter player;
    skillMap skills = createSkillMap();

    cout << "Start: " << endl;
    cout << displayStats(player.getStats()) << endl;
    cout << endl;
    cout << displayPoints(player.getPointValues()) << endl;

    cout << "Damaged: " << endl;
    player.damage(5,0,0);

    cout << displayPoints(player.getPointValues()) << endl;

    //skills["Rest"].Use(player);
    cout << "Healed: " << endl;
    cout << displayPoints(player.getPointValues()) << endl;

    return 0;
};

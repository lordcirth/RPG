#include <string>
#include <iostream>
#include "player.h"
#include "skills.h"
using namespace std;
//
//Skill* constructSkillTree()
//{
//    //Skill Root
//
//    Skill Root =
//    {
//        //No parent, unlocked, does nothing
//        nullptr, true, {false, false}
//    };
//    return Skill;
//};

int main()
{

    PlayerCharacter player;

    cout << displayStats(player.getStats()) << endl;
    cout << endl;
    cout << displayPoints(player.getPointValues()) << endl;

    player.damage(5,0,0);

    cout << displayPoints(player.getPointValues()) << endl;

    //player.damage(-1,0,0); //Heal

    cout << displayPoints(player.getPointValues()) << endl;

    //Hit.Use();


//cout << player.
    return 0;
};

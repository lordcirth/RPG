#include <string>
#include <iostream>
#include <memory> //unique_ptr
#include "player.h"
#include "skills.h"
using namespace std;


int main()
{

    PlayerCharacter player;
    //skillPtrMap skills = createSkillMap();

//    cout << "Start: " << endl;
//    cout << displayStats(player.getStats()) << endl;
//    cout << endl;
//    cout << displayPoints(player.getPointValues()) << endl;

//    cout << "Damaged: " << endl;
//    player.damage(5,0,0);

//    Monster wolf {{5,0,0,5,0,0}}; // 5/5 HP.
//    wolf.damage(2,0,0);

    skillList skills = createSkillStruct();
    //Heal rest = skills.heals["Rest"];

//    cout << displayPoints(player.getPointValues()) << endl;
//
//    cout << "Healed: " << endl;
//    cout << displayPoints(player.getPointValues()) << endl;

    //Skill doNothing {true};
    //unique_ptr<Skill> doN_ptr = make_unique<Skill>(true);

    return 0;
}

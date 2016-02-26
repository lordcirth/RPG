#include "monsters.h"

Creature::Creature(CreaturePoints points)
{
    pointValues = points;
}

Monster::Monster(CreaturePoints points)
    : Creature(points)
{

}

//Monster wolf {{5,0,0,5,0,0}}; // 5/5 HP.

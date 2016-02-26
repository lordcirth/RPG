#ifndef MONSTERS_H
#define MONSTERS_H

struct CreatureStats
{
    //Physical
    int strength;
    int dexterity;
    int endurance;
    //Magical
    int power;
    int control;
    int capacity;

};

struct CreaturePoints
{
    int maxHP;
    int maxSP;
    int maxMP;

    int HP;
    int SP;
    int MP;
};


class Creature
{
    CreaturePoints pointValues;
public:
    void healAll();
    void damage(int hpDmg, int spDmg, int mpDmg);
    Creature();
    Creature(CreaturePoints points);

};


class Monster : public Creature
{

public:
    Monster(CreaturePoints points);
};
#endif

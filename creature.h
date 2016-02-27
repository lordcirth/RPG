
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
private:
    CreatureStats stats;
    CreaturePoints pointValues;

public:
    CreatureStats getStats();
    void setStats(CreatureStats);
    CreaturePoints getPointValues();
    CreaturePoints setPointValues(CreaturePoints);
    void calcAttributes();

    void healAll();
    void damage(int hpDmg, int spDmg, int mpDmg);

    Creature();
    Creature(CreatureStats startingStats);
    Creature(CreaturePoints points);

};


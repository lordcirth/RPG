#include "interface.h"
#include "ncurses.h"
#include <string>
#include <iostream>
#include "menu.h"

using namespace std;

void initInterface()
{
    initscr();
    cbreak();
    noecho();
}

void cleanUpInterface()
{
    endwin();
}

char getPlayerKey()
{
    char ch = getch();
    return ch;
}

void displayPoints(int row, int col, Creature c)
{
    CreaturePoints points = c.getPointValues();
    string name = c.getName();

    mvprintw(row, col, "%s: \n", name.c_str());  //Null-terminated string
    mvprintw(++row, col, "HP: %d / %d \n", points.HP, points.maxHP);
    mvprintw(++row, col, "SP: %d / %d \n", points.SP, points.maxSP);
    mvprintw(++row, col, "MP: %d / %d \n", points.MP, points.maxMP);
    refresh();
    //std::cout << "SP: " + to_string(points.SP) << "  ";
}

void updatePoints(Creature player, Creature enemy)
{
    displayPoints(0,0, player);
    displayPoints(0,68, enemy);
}

void initSkillMenu(PlayerCharacter &player)
{
    skillList skills = player.skills;
    map<std::string,Melee>::iterator it;

    for (it = skills.melees.begin(); it != skills.melees.end(); ++it)
    {
        std::cout << (*it).second.baseDmg;
    }
}

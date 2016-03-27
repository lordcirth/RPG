#include "interface.h"
#include "ncurses.h"
#include <string>
#include <iostream>
#include "menu.h"

using namespace std;

void initInterface() {
    initscr();
    cbreak();
    noecho();
}

void cleanUpInterface() {
    endwin();
}

char getPlayerKey() {
    char ch = getch();
    return ch;
}

void displayPoints(int row, int col, Creature c) {
    CreaturePoints points = c.getPointValues();
    string name = c.getName();

    mvprintw(row, col, "%s: \n", name.c_str());  //Name as Null-terminated string
    mvprintw(++row, col, "HP: %d / %d \n", points.HP, points.maxHP);
    mvprintw(++row, col, "SP: %d / %d \n", points.SP, points.maxSP);
    mvprintw(++row, col, "MP: %d / %d \n", points.MP, points.maxMP);
    refresh();
    //std::cout << "SP: " + to_string(points.SP) << "  ";
}

void updatePoints(Creature player, Creature enemy) {
    displayPoints(0,0, player);
    displayPoints(0,68, enemy);
}

void initSkillMenu(PlayerCharacter &player) {
    //skillList skills = player.skills;
    skillPtrList skillPtrs = player.skillPtrs;
    list<Skill*>::iterator it;

    for (it = skillPtrs.begin(); it != skillPtrs.end(); ++it) {
        std::cout << (*it)->getName();
    }
}

//Demo menu.h
void showMenu() {
//ITEM *item1;
//item1 = new_item("first", "second");
//ITEM item2 = new_item("third", "fourth");
//MENU menu1 = new_menu();
}

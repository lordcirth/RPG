#include "interface.h"
#include "ncurses.h"
#include <string>
#include <iostream>
#include "menu.h"

using namespace std;

void initInterface() {
    //initscr();
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
    skillPtrList skillPtrs = player.skillPtrs;


    //C-style strings?
    const char *testStr = skillPtrs.front()->getName().c_str();
//    ITEM *testItem;   //Works!
//    testItem = new_item(testStr, testStr);

// ITEM *restItem = new_item(testStr,testStr);
cout << "Number of skills: " + to_string(skillPtrs.size());
//ITEM *skillItems[skillPtrs.size()];
//MENU *menu = new_menu(&restItem);

    list<Skill*>::const_iterator it;
    //int i = 0;
    for (it = skillPtrs.begin(); it != skillPtrs.end(); it++) {

        //skillItems[i] = new_item(skillPtrs.front()->getName().c_str(),skillPtrs.front()->getName().c_str());
        //cout << skillPtrs.front()->getName().c_str() << endl;
    };
    //MENU *menu = new_menu((ITEM **)skillItems);

}

//Demo menu.h
void showMenu(PlayerCharacter &player) {
    mvprintw(10,0, "r: %s", player.skillPtrs.front()->getName());
}

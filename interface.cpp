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
    return getch();
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

void printSkill(int row, int col, char key, const char *name) {
    mvprintw(row,col, "%c: %s", key, name);
}

//Demo menu.h
void showMenu(PlayerCharacter &player) {
    int startRow = 16;
    int startCol  = 1;

    int hOffset  = 10;
    int vOffset  = 1;

    int maxRows = 3;
    int maxCols = 5;

    int row = startRow;
    int col = startCol;

    list<Skill*>::const_iterator it;
    for (it = player.skillPtrs.begin(); it != player.skillPtrs.end(); it++) {
        printSkill(row, col, (**it).shortcut, (*it)->getName().c_str());
        row += vOffset;
    }
}

void printSkillUse(std::string skillName) {
    mvprintw(20,1, "Player used: %s", skillName.c_str());
}

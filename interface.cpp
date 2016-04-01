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
    int startVert = 16;
    int startHor  = 1;

    int vOffset  = 1;
    int hOffset  = 10;

    int maxVert = 5;
    int maxHor = 3;
    int vertSlot = 1;
    int horSlot = 1;

    int vert = startVert;
    int hor = startHor;

    list<Skill*>::const_iterator it;
    for (it = player.skillPtrs.begin(); it != player.skillPtrs.end(); it++) {
        printSkill(vert, hor, (**it).shortcut, (*it)->getName().c_str());
        if (horSlot < maxHor) {
            hor += hOffset;
            ++horSlot;
        } else {
            ++hor;
            vert = startVert;
            horSlot = 1;
        }
    }
}


void printBuff(std::string buffName) {
    mvprintw(6,1, "                                               ");  //Hacky clear.  TODO fix
    mvprintw(6,1, "%s", buffName.c_str());
}

typedef pair<string,int> buffStackPair;

void printAllBuffs(list<string> buffNames) {
    buffNames.sort(); //So we can deduplicate, also looks nice
    list<buffStackPair> printList; //Buffs and stack counts


    list<string>::const_iterator it;
    for (it = buffNames.begin(); it != buffNames.end(); it++) {
        if ( (*(printList.end())).first == *it ) {  //If last loop's buff = this loop's buff, increment stack count instead
            (*(printList.end())).second++;
        } else {
            printList.push_back({*it, 1});
        }

    }
}

void printSkillUse(std::string skillName) {
    mvprintw(20,1, "                                               ");  //Hacky clear.  TODO fix
    mvprintw(20,1, "Player used %s.", skillName.c_str());
}

void printSkillUse(std::string skillName, std::string targetName) {
    mvprintw(20,1, "                                               ");  //Hacky clear.  TODO fix
    mvprintw(20,1, "Player used %s on %s.", skillName.c_str(), targetName.c_str());
}


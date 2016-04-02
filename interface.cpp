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
}

void updatePoints(Creature &player, Creature &enemy) {
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

//    int vOffset  = 1;
    int hOffset  = 10;

//    int maxVert = 5;
    int maxHor = 3;
//    int vertSlot = 1;
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

void printBuff(int vert, int hor, buffStackPair buff) {
    mvprintw(vert,hor, "                                               ");  //Hacky clear.  TODO fix
    mvprintw(vert,hor, "%s X%i", buff.first.c_str(), buff.second);
}

void printBuffList(int startVert, int startHor, list<string> buffNames) {
    buffNames.sort(); //So we can deduplicate, also looks nice
    list<buffStackPair> printList; //Buffs and stack counts


    list<string>::const_iterator it;
    for (it = buffNames.begin(); it != buffNames.end(); it++) {
//

        if (printList.back().first == *it ) {  //If last loop's buff = this loop's buff

            printList.back().second++; // increment stack count

        } else {
            printList.push_back({*it, 1});          //Or if it's the first of it's kind, add it.
            cerr << "Fresh buff" << endl;
        }
    }

    int vert = startVert;
    int hor  = startHor;
    list<buffStackPair>::const_iterator buffIt;
    for (buffIt = printList.begin(); buffIt != printList.end(); buffIt++) {
//        cerr << "printing buff:" << endl;
        printBuff(vert, hor, (*buffIt));
        ++vert;
    }

    //TODO: Proper clear!
    mvprintw(vert,hor, "                                       ");
    mvprintw(vert,hor, "                                       ");
    mvprintw(vert,hor, "                                       ");
}

void printAllBuffs(std::list<Buff*> playerBuffs, std::list<Buff*> enemyBuffs) {
    list<string> playerBuffNames;
    list<string> enemyBuffNames;

    list<Buff*>::const_iterator it;
    for (it = playerBuffs.begin(); it != playerBuffs.end(); it++) {
       playerBuffNames.push_back((*it)->getName());
    }

    for (it = enemyBuffs.begin(); it != enemyBuffs.end(); it++) {
       enemyBuffNames.push_back((*it)->getName());
    }

    printBuffList(5,0, playerBuffNames);
    printBuffList(5,60, enemyBuffNames);
}


//Print string to player's messages.
void printMessage(string message) { //TODO scrolling!
    mvprintw(20,1, "                                               "); //TODO fix hacky clear
    mvprintw(20,1, message.c_str());
}

void printSkillUse(string skillName) {
    string message = "Player used " + skillName + ".";
    printMessage(message);
}

void printSkillUse(string skillName, string targetName) {
    string message = "Player used " + skillName + " on " + targetName + ".";
    printMessage(message);
}

void printSkillFails(Skill *a, skillReturnType error) {
    if (error == SKILL_FAIL_COST) {
        printMessage(a->getName() + " requires " + to_string(a->getCost().HP) + "HP, " + to_string(a->getCost().SP) + "SP, " + to_string(a->getCost().MP) + "MP");
    }
}

#include "interface.h"
#include <string>
#include <iostream>
#include "menu.h"

using namespace std;
WINDOW *fight_window; //Global - is this bad?
WINDOW *skill_window; //Skill points / levelup screen
const int buffPrintLength = 24;

void initInterface() {
    initscr();
    cbreak();
    noecho();

    fight_window = newwin(24,79,0,0);
    wborder(fight_window, '|', '|', '-', '-', '+', '+', '+', '+');
    //cerr << "initchar: " <<  wgetch(fight_window) << endl;
    wrefresh(fight_window);
    skill_window = newwin(24,79,0,0);
}

void cleanUpInterface() {
    //endwin();
}

char getPlayerKey() {
    return wgetch(fight_window);
}

void displayPoints(int row, int col, Creature c) {
    CreaturePoints points = c.getPointValues();
    string name = c.getName();

    mvwprintw(fight_window, row, col, "%s:", name.c_str());  //Name as Null-terminated string

    mvwprintw(fight_window, ++row, col, "HP: %d / %d", points.HP, points.maxHP);
    mvwprintw(fight_window, ++row, col, "SP: %d / %d", points.SP, points.maxSP);
    mvwprintw(fight_window, ++row, col, "MP: %d / %d", points.MP, points.maxMP);
    //wrefresh(fight_window);
}

void updatePoints(Creature &player, Creature &enemy) {
    displayPoints(1,1, player);
    displayPoints(1,64, enemy);
}

void printSkill(int row, int col, char key, const char *name) {
    mvwprintw(fight_window, row,col, "%c: %s", key, name);
}

//Demo menu.h
void showMenu(PlayerCharacter &player) {
    int startVert = 16;
    int startHor  = 1;

    int vOffset  = 1;
    int hOffset  = 16;

    int maxVert = 5;
    int maxHor = 3;
    int vertSlot = 1;
    int horSlot = 1;

    int vert = startVert;
    int hor = startHor;

    list<Skill*>::const_iterator it;
    for (it = player.skillPtrs.begin(); it != player.skillPtrs.end(); it++) {
        printSkill(vert, hor, (**it).shortcut, (*it)->getName().c_str());
        if (horSlot < maxHor) { //Move across
            hor += hOffset;
            ++horSlot;
        } else { //Down one line and reset (like carriage return)
            hor = startHor;
            horSlot = 1;

            ++vertSlot;
            vert += vOffset;
        }
    }
}

void printBuff(int vert, int hor, Buff* buff) {
    mvwprintw(fight_window, vert,hor, "                ");  //Hacky clear.  TODO fix
    //string buffString = format()
    mvwprintw(fight_window, vert,hor, "%s (%i)", buff->getName().c_str(), buff->turnsLeft);
}

void printBuffList(int startVert, int startHor, std::list<Buff*> buffs) {
    //buffNames.sort(); //So we can deduplicate, also looks nice
    //list<buffStackPair> printList; //Buffs and stack counts

    int vert = startVert;
    int hor  = startHor;

    std::list<Buff*>::const_iterator it;
    for (it = buffs.begin(); it != buffs.end(); it++) {
        printBuff(vert, hor, (*it));
        ++vert;
    }

    //TODO: Proper clear!
    mvwprintw(fight_window, vert++,hor, "                ");
    mvwprintw(fight_window, vert++,hor, "                ");
    mvwprintw(fight_window, vert++,hor, "                ");
}



//New buff printing, with duration:
void printAllBuffs(std::list<Buff*> playerBuffs, std::list<Buff*> enemyBuffs) {
    printBuffList(5, 1, playerBuffs);
    printBuffList(5, 79 - buffPrintLength, enemyBuffs);
}



//Print string to player's messages.
void printMessage(string message) { //TODO scrolling!
    mvwprintw(fight_window, 20,1, "                                               "); //TODO fix hacky clear
    mvwprintw(fight_window,20,1, message.c_str());
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

void levelUpMenu (PlayerCharacter player) {
    mvwprintw(skill_window, 1,1, "%s:", "Skill Menu");

    mvwprintw(skill_window, 3,1, "%s:  %i", "Stat points", player.getFreeStatPoints());
    mvwprintw(skill_window, 4,1, "%s: %i", "Skill points", player.getFreeSkillPoints());

    wgetch(skill_window);
}

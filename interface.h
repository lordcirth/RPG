#pragma once
#include "player.h"
#include "ncurses.h"
#include "skills.h"

class MessageBuffer {
    std::list<std::string> buffer;
    int maxLines = 6;   //List length
    int maxRows  = 40;  //String length
public:
    void addMessage(std::string message);
    std::list<std::string> getBuffer();
    int getBufferLength(); //Number of messages in buffer
};

void initInterface();
void cleanUpInterface();

char getPlayerKeyFight();
void displayPoints(int row, int col, Creature c);
void updatePoints(Creature &player, Creature &enemy);
void showMenu(PlayerCharacter &player);

void printMessage(std::string message);

std::string msgSkillUse(std::string skillName);
std::string msgSkillUse(std::string skillName, std::string targetName);
std::string msgSkillFails(Skill *attemptedSkill, skillReturnType error);

void printMessageBuffer(std::list<std::string> buffer);

typedef std::pair<std::string,int> buffStackPair;

void printBuff(int pos, buffStackPair buff);
void printBuffList(int vert, int hor, std::list<std::string> buffNames);
void printAllBuffs(std::list<Buff*> playerBuffs, std::list<Buff*> enemyBuffs);



void skillMenu (PlayerCharacter &player);

void playerLost();

Skill * getValidSkillChoice(WINDOW *window, skillPtrList skillPtrs);
Skill * getSkill_fight(skillPtrList skillPtrs);
Skill * getSkill_skills(skillPtrList skillPtrs);

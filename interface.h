#pragma once
#include "player.h"
#include "ncurses.h"

class MessageBuffer {
    std::list<std::string> buffer;
    int maxLength;
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

std::string msgSkillUse(MessageBuffer &buffer, std::string skillName);
std::string msgSkillUse(MessageBuffer &buffer, std::string skillName, std::string targetName);
std::string msgSkillFails(MessageBuffer &buffer, Skill *attemptedSkill, skillReturnType error);

typedef std::pair<std::string,int> buffStackPair;

void printBuff(int pos, buffStackPair buff);
void printBuffList(int vert, int hor, std::list<std::string> buffNames);
void printAllBuffs(std::list<Buff*> playerBuffs, std::list<Buff*> enemyBuffs);



void levelUpMenu (PlayerCharacter player);

void playerLost();

#pragma once
#include "player.h"
void initInterface();
void cleanUpInterface();

char getPlayerKey();
void displayPoints(int row, int col, Creature c);
void updatePoints(Creature &player, Creature &enemy);
void showMenu(PlayerCharacter &player);


void printMessage(std::string message);

void printSkillUse(std::string skillName);
void printSkillUse(std::string skillName, std::string targetName);

void printBuff(int pos, std::string buffName);
void printBuffList(int vert, int hor, std::list<std::string> buffNames);
void printAllBuffs(std::list<Buff*> playerBuffs, std::list<Buff*> enemyBuffs);

void printSkillFails(Skill *attemptedSkill, skillReturnType error);

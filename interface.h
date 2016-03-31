#pragma once
#include "fight.h"
void initInterface();
void cleanUpInterface();
char getPlayerKey();
void displayPoints(int row, int col, Creature c);
void updatePoints(Creature player, Creature enemy);
void showMenu(PlayerCharacter &player);
void printSkillUse(std::string skillName);
void printSkillUse(std::string skillName, std::string targetName);

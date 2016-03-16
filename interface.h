# include "fight.h"
void initInterface();
void cleanUpInterface();
char getPlayerKey();
void displayPoints(int row, int col, Creature c);
void updatePoints(Creature player, Creature enemy);
void initSkillMenu(PlayerCharacter &player);

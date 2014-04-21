#include "LogicGame.h"


LogicGame::LogicGame()
{
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			board[i][j] = 0;
		}
	}
}

LogicGame::~LogicGame()
{
}
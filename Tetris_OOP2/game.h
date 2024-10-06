#ifndef _GAME_H
#define _GAME_H


class Game
{
	Player* left_player =nullptr;
	Player* right_player = nullptr;
	bool game_running = false;

public:
	
	void instrucions(); //Display Tetris game instructions.
	bool run(Player* left_player, Player* right_player); 
	void start();
	void helloMessage();
};

#endif
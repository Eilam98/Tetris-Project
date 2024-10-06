#ifndef _HUMAN_H
#define _HUMAN_H

#include "gameConfig.h"
#include "point.h"
#include "general.h"
#include "gameConfig.h"
#include "player.h"
class Human : public Player
{
	char player_keyboard[10];

public: 
	Human(const char* keyboard);
	Human(const char* keyboard, int board_left_upper_edge_x, int board_left_upper_edge_y);
	void move_shape(char key_pressed);
	bool key_of_this_player(char key_pressed); //Checks if the input key corresponds to the player's controls.
};

#endif

#include "human.h"


Human::Human(const char* keyboard) : Player()
{
	for (int i = 0; i < 10; i++)
{
	player_keyboard[i] = keyboard[i];
} 
}
Human::Human(const char* keyboard, int board_left_upper_edge_x, int board_left_upper_edge_y) : Player(board_left_upper_edge_x, board_left_upper_edge_x)
{
	for (int i = 0; i < 10; i++)
	{
		player_keyboard[i] = keyboard[i];
	}
}
//Checks if the input key corresponds to the player's controls.
bool Human::key_of_this_player(char key_pressed)
{
	for (int i = 0; i < 10; i++)
	{
		if (player_keyboard[i] == key_pressed)
			return true;
	}
	return false;
}
void Human::move_shape(char key_pressed)
{
	if (key_pressed == player_keyboard[0] || key_pressed == player_keyboard[1])
	{
		if (can_move_left())
		{
			x--;
		}
	}
	else if (key_pressed == player_keyboard[2] || key_pressed == player_keyboard[3])
	{
		rotateShape_back();
	}
	else if (key_pressed == player_keyboard[4] || key_pressed == player_keyboard[5])
	{
		if (can_move_right())
		{
			x++;
		}
	}
	else if (key_pressed == player_keyboard[6] || key_pressed == player_keyboard[7])
	{
		rotateShape();
	}
	else if (key_pressed == player_keyboard[8] || key_pressed == player_keyboard[9])
	{
		dropShape();
	}
}
//TODO

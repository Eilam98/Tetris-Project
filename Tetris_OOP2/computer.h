#ifndef _COMPUTER_H
#define _COMPUTER_H

#include "gameConfig.h"
#include "point.h"
#include "general.h"
#include "gameConfig.h"
#include "player.h"
class Computer : public Player
{

	int best_x = 0;
	int best_rotation =0;
	char level = '0';

	void set_best_x(int _best_x) { best_x = _best_x; }
	void set_best_rotation(int _best_rotation) { _best_rotation; }

public:
	Computer(int board_left_upper_edge_x, int board_left_upper_edge_y) : Player(board_left_upper_edge_x, board_left_upper_edge_y) {};
	void move_shape();
	bool get_best_move();
	int find_bottom(int _x);
	bool optionValid(int index);
	int evaluate_score(int _x, int bottom);
	int evaluate_score_for_bomb(int _x, int bottom);
	int get_highest_y();
	int get_min_x_coor();
	bool set_level(int player_name);
	int miss_by_level();
};

#endif
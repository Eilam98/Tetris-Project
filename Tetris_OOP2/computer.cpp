#include "computer.h"
#include <Windows.h> ///for sleep
#include <conio.h> // for kbhit & getch
#include <iostream>
#include <stdlib.h>

void Computer::move_shape()
{
	bool right = can_move_right();
	bool left = can_move_left();
	if (best_x > x)
	{
		while (x != best_x && (right))
		{
			x++;
			right = can_move_right();
		}
	}
	else if (best_x < x)
	{
		while (x != best_x && (left))
		{
			x--;
			left = can_move_left();
		}
	}
	if (best_rotation > 0)
	{
		rotateShape();
		/*int _min_x = get_min_x_coor();
		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		{
			block[i].setPoint(block[i].getX() - _min_x, block[i].getY());
		}*/
		best_rotation--;
	}

}
bool Computer::get_best_move()
{
	int _best_x = 0, _best_rotation = 0; // i=x, j=rotation
	int max_score = 0;
	if (miss_by_level() == 0)
	{
		best_x = rand() % GameConfig::GAME_WIDTH;
		best_rotation = rand() % GameConfig::FULL_ROTATION_CYCLE;
		return top_row_empty();
	}
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		for (int j = 0; j < GameConfig::FULL_ROTATION_CYCLE; j++)
		{
			int _score = 0;
			if (optionValid(i))
			{
				int bottom = find_bottom(i);

				_score = evaluate_score(i, bottom);
				if (_score > max_score)
				{
					max_score = _score;
					_best_x = i;
					_best_rotation = j;
				}
			}
			rotateShape();
			//int _min_x = get_min_x_coor();
			//for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
			//{
			//	block[i].setPoint(block[i].getX() - _min_x, block[i].getY());
			//}
		}

	}
	best_x = _best_x;
	best_rotation = _best_rotation;
	if (max_score == 0)
		return false;
	return true;
}
int Computer::find_bottom(int _x)
{
	int _y = 1;
	int highest_y = get_highest_y();
	bool bottom_found = false;
	while (!bottom_found && _y + highest_y < GameConfig::GAME_HEIGHT)
	{

		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		{
			if (board[block[i].getX() + _x][block[i].getY() + _y] != ' ')
			{
				bottom_found = true;
			}
		}
		if (!bottom_found)
			_y++;
	}
	return _y - 1; //returns the row the block would prefer to land at.
}
bool Computer::optionValid(int index)
{
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		if (block[i].getX() + index >= GameConfig::GAME_WIDTH)
			return false;
	}
	return true;
}
int Computer::evaluate_score(int _x, int bottom)
{
	int _score = 0;

	char tmpBoard[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT];
	memcpy(tmpBoard, board, (GameConfig::GAME_HEIGHT * GameConfig::GAME_WIDTH));
	int highest_y = get_highest_y();
	int type = get_shape_type();

	if (type == GameConfig::BOMB)
	{
		_score = evaluate_score_for_bomb(_x, bottom);
	}

	else
	{
		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		{
			tmpBoard[block[i].getX() + _x][bottom + block[i].getY()] = '*';
		}

		int count_holes = 0;
		int asterisks_by_placement = 0;
		bool occupied_above = false;
		for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
		{
			occupied_above = false;
			for (int j = 1; j < GameConfig::GAME_HEIGHT; j++)
			{
				if (tmpBoard[i][j] != '*')
				{
					if (occupied_above)
					{
						count_holes++;
					}
					occupied_above = false;
				}
				else if (tmpBoard[i][j] == '*')
				{
					asterisks_by_placement += j;
					occupied_above = true;
				}
			}
		}
		_score += (asterisks_by_placement * 10); //*120 worked well

		bool row_empty = true;
		int max_height = 0; // refers to physical height rather than y value;
		for (int j = 1; j < GameConfig::GAME_HEIGHT; j++)
		{
			row_empty = true;
			for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
			{
				if (tmpBoard[i][j] == '*')
				{
					row_empty = false;
					break;
				}
			}
			if (row_empty)
			{
				if (max_height < j)
					max_height = j;
			}
		}
		bool row_full = true;
		int count_row_full = 0;
		for (int j = 1; j < GameConfig::GAME_HEIGHT; j++)
		{
			row_full = true;
			for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
			{
				if (tmpBoard[i][j] != '*')
				{
					row_full = false;
					break;
				}
			}
			if (row_full)
				count_row_full++;
		}
		_score += (count_row_full * 1000); // Reward for clearing full rows with quadratic scaling
		_score -= ((GameConfig::GAME_HEIGHT - max_height - 1) * 2); // Penalize for stack height
		_score -= (count_holes); // Penalize for holes
	}
	return _score;
}
int Computer::evaluate_score_for_bomb(int _x, int bottom)
{
	int square_start_x = 0;
	int square_end_x = 0;
	int square_start_y = 0;
	int square_end_y = 0;
	int _score = 0;

	int xPos = block[0].getX() + _x;
	int yPos = block[0].getY() + bottom;

	if (xPos - 4 < 0)
	{
		square_start_x = 0;
		square_end_x = xPos + 4;
	}
	else if (xPos + 4 > 11)
	{
		square_start_x = xPos - 4;
		square_end_x = 11;
	}
	else
	{
		square_start_x = xPos - 4;
		square_end_x = xPos + 4;
	}

	if (yPos - 4 < 0)
	{
		square_start_y = 0;
		square_end_y = yPos + 4;
	}
	else if (yPos + 4 > 17)
	{
		square_start_y = yPos - 4;
		square_end_y = 17;
	}
	else
	{
		square_start_y = yPos - 4;
		square_end_y = yPos + 4;
	}

	int hight = square_end_y - square_start_y + 1;


	for (int i = square_start_x; i <= square_end_x; i++)
	{
		for (int j = square_start_y; j <= square_end_y; j++)
		{
			if(board[i][j] == '*')
			_score++;
		}
	}

	return _score;

}
int Computer::get_highest_y()
{
	int highest_y = 0;
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		int tmp = block[i].getY();
		if (tmp > highest_y)
			highest_y = tmp;
	}
	return highest_y;
}
int Computer::get_min_x_coor()
{
	int minimal_x = GameConfig::SHAPE_SIZE;
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		if (minimal_x > block[i].getX())
			minimal_x = block[i].getX();
	}
	return minimal_x;
}
bool Computer::set_level(int player_name)
{
	clrscr();
	
	std::cout << "Set Level for ";
	
	if (player_name == GameConfig::LEFT_PLAYER)
		std::cout << "left player" << std::endl;
	
	else if ((player_name == GameConfig::RIGHT_PLAYER))
		std::cout << "right player" << std::endl;
	
	std::cout << "(1) BEST - will calculate the exact best step for each move"<<std::endl;
	std::cout << "(2) GOOD - will miss occasionally (e.g. randomly once in ~40 moves)" << std::endl;
	std::cout << "(3) NOVICE - will  miss occasionally (e.g. randomly once in ~10 moves)" << std::endl;
	std::cout << "(9) EXIT" << std::endl;

	char ch = _getch();
	
	while (ch != GameConfig::BEST && ch != GameConfig::GOOD && ch != GameConfig::NOVICE && ch!=GameConfig::ESC)
	{
		ch = _getch();
	}
	
	clrscr();
	
	if (ch == GameConfig::ESC)
	{
		return false;
	}
		level = ch;
		return true;
};
int Computer::miss_by_level()
{
	if (level == GameConfig::BEST)
		return 1;
	else if (level == GameConfig::GOOD)
		return (rand() % 40);
	else if (level == GameConfig::NOVICE)
		return (rand() % 10);
	return 1;
}
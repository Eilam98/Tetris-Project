#include <Windows.h> ///for sleep
#include <conio.h> // for kbhit & getch
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "player.h"


//Initializes TetrisGame with default player controls.
Player::Player()
{
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		for (int j = 0; j < GameConfig::GAME_HEIGHT; j++)
		{
			board[i][j] = ' ';
		}
	}
	block[0].setPoint(0, 0);
	block[1].setPoint(0, 0);
	block[2].setPoint(0, 0);
	block[3].setPoint(0, 0);
}

Player::Player(int board_left_upper_edge_x, int board_left_upper_edge_y)
{
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		for (int j = 0; j < GameConfig::GAME_HEIGHT; j++)
		{
			board[i][j] = ' ';
		}
	}
	min_x = board_left_upper_edge_x + 1;
	min_y = board_left_upper_edge_y + 1;
	
	block[0].setPoint(0, 0);
	block[1].setPoint(0, 0);
	block[2].setPoint(0, 0);
	block[3].setPoint(0, 0);
}

//Draws the border of the Tetris game board starting from a specified position.
 void Player::drawBorder(int _x, int _y)
{
	for (int col = _x; col <= _x + GameConfig::GAME_WIDTH; col++)
	{
		gotoxy(col, _y);
		cout << "-";

		gotoxy(col, _y + GameConfig::GAME_HEIGHT + 1);
		cout << "-";
	}

	for (int row = _y; row <= _y + GameConfig::GAME_HEIGHT + 1; row++)
	{
		gotoxy(_x, row);
		cout << "|";

		gotoxy(_x + GameConfig::GAME_WIDTH + 1, row);
		cout << "|";
	}
	min_x = _x + 1;
	min_y = _y + 1;
}

//Generates a random Tetris shapeand initializes the block coordinates accordingly.
//Generates a random Tetris shapeand initializes the block coordinates accordingly.
void Player::getShape()
{
	int index = 0;
	if (rand() % 20 == 0)
	{
		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		{
			block[i].setPoint(0, 0);
		}
		shape_type = GameConfig::BOMB;
	}
	else
	{
		shape_type = rand() % GameConfig::NUM_OF_SHAPES;
		switch (shape_type)
		{
		case (int)GameConfig::L_TYPE:
		{
			block[0].setPoint(0, 1);
			block[1].setPoint(1, 1);
			block[2].setPoint(2, 1);
			block[3].setPoint(2, 0);
			break;
		}
		case (int)GameConfig::I_TYPE:
		{
			block[0].setPoint(0, 0);
			block[1].setPoint(1, 0);
			block[2].setPoint(2, 0);
			block[3].setPoint(3, 0);
			break;
		}
		case (int)GameConfig::O_TYPE:
		{
			block[0].setPoint(0, 0);
			block[1].setPoint(1, 0);
			block[2].setPoint(0, 1);
			block[3].setPoint(1, 1);
			break;
		}
		case (int)GameConfig::S_TYPE:
		{
			block[0].setPoint(0, 1);
			block[1].setPoint(1, 1);
			block[2].setPoint(1, 0);
			block[3].setPoint(2, 0);
			break;
		}
		case (int)GameConfig::Z_TYPE:
		{
			block[0].setPoint(0, 0);
			block[1].setPoint(1, 0);
			block[2].setPoint(1, 1);
			block[3].setPoint(2, 1);
			break;
		}
		case (int)GameConfig::J_TYPE:
		{
			block[0].setPoint(0, 0);
			block[1].setPoint(0, 1);
			block[2].setPoint(1, 1);
			block[3].setPoint(2, 1);
			break;
		}
		case (int)GameConfig::T_TYPE:
		{
			block[0].setPoint(0, 0);
			block[1].setPoint(1, 0);
			block[2].setPoint(2, 0);
			block[3].setPoint(1, 1);
			break;
		}
		}
	}
	
}

//Draws the Tetris shape on the game board with the specified character.
void Player::drawShape(char ch)
{
	if (block != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			gotoxy(x + min_x + block[i].getX(), y + min_y + block[i].getY());
			cout << ch;
		}
	}
}

//Checks if the Tetris block has reached the bottom of the game board.
bool Player::blockReachedBottom()
{
	for (int i = 0; i < 4; i++)
	{
		if (block[i].getY() + y >= GameConfig::GAME_HEIGHT - 1)
			return true;
	}
	return false;

}

//Checks if the Tetris block can move down within the game board.
bool Player::canMoveDown()
{
	for (int i = 0; i < 4; i++)
	{
		if (board[block[i].getX() + x][block[i].getY() + y + 1] == '*')
			return false;
	}
	return true;

}

//Checks if the Tetris block can move left within the game board.
bool Player::can_move_left()
{
	int left_point = left_point_x();
	if (x <= 0)
	{
		if (left_point == 0)
			return false;
		else
		{
			for (int i = 0; i < 4; i++)
			{
				block[i].setPoint(block[i].getX() - 1, block[i].getY());
			}
			return false;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (board[block[i].getX() + x - 1][block[i].getY() + y] != ' ' || board[block[i].getX() + x - 1][block[i].getY() + y + 1] != ' ')
			return false;
	}
	return true;

}

//Determines the leftmost x-coordinate of the Tetris block
int Player::left_point_x()
{
	int min = block[0].getX();
	for (int i = 1; i < 4; i++)
	{
		if (block[i].getX() < min)
			min = block[i].getX();
	}
	return min;
}

//Checks if the Tetris block can move right within the game board.
bool Player::can_move_right()

{
	int right_point = right_point_x();
	if (x >= GameConfig::GAME_WIDTH)
	{
		if (right_point == GameConfig::BLOCK_SQUARE_SIZE - 1)
			return false;
		else
		{
			for (int i = 0; i < 4; i++)
			{
				block[i].setPoint(block[i].getX() + 1, block[i].getY());
			}
			return false;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (board[block[i].getX() + x + 1][block[i].getY() + y] != ' ' || board[block[i].getX() + x + 1][block[i].getY() + y + 1] != ' ')
			return false;
	}
	return true;

}

//Determines the rightmost x-coordinate of the Tetris block.
int Player::right_point_x()
{
	int max = block[0].getX();
	for (int i = 1; i < 4; i++)
	{
		if (block[i].getX() > max)
			max = block[i].getX();
	}
	return max;
}

//Rotates the Tetris block clockwise.
void Player::rotateShape()
{
	int newX, newY;
	if (!is_O_shape())
	{
		can_rotate_Shape();
		for (int i = 0; i < 4; i++)
		{
			newY = block[i].getX();
			newX = 3 - block[i].getY();
			block[i].setPoint(newX, newY);
		}
	}
}

void Player::can_rotate_Shape()
{
	bool flagX = false;
	bool flagY = false;
	while (!flagX || !flagY)
	{
		flagX = true;
		flagY = true;
		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		{
			if (3 - block[i].getY() + x >= GameConfig::GAME_WIDTH)
				flagX = false;
		}
		if (!flagX)
			x--;
		for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		{
			if (block[i].getX() + y >= GameConfig::GAME_HEIGHT)
			{
				flagY = false;
			}
			else if (board[3 - block[i].getY() + x][block[i].getX() + y] != ' ')
			{
				flagY = false;
			}
		}
		if (!flagY)
			y--;

	}
}

//Rotates the Tetris block counterclockwise.
void Player::rotateShape_back()
{
	int newX, newY;
	if (!is_O_shape())
	{
		can_rotate_Shape_back();
		for (int i = 0; i < 4; i++)
		{
			newX = block[i].getY();
			newY = 3 - block[i].getX();
			block[i].setPoint(newX, newY);
		}
	}
}

void Player::can_rotate_Shape_back()
{
	bool flagX = false;
	bool flagY = false;
	while (!flagX || !flagY)
	{
		flagX = true;
		flagY = true;
		for (int i = 0; i < 4; i++)
		{
			if (block[i].getY() + x >= GameConfig::GAME_WIDTH)
				flagX = false;
		}
		if (!flagX)
			x--;
		for (int i = 0; i < 4; i++)
		{
			if (3 - block[i].getX() + y >= GameConfig::GAME_HEIGHT)
			{
				flagY = false;
			}
			else if (board[block[i].getY() + x][3 - block[i].getX() + y] != ' ')
			{
				flagY = false;
			}
		}
		if (!flagY)
			y--;

	}
}

//Checks if the Tetris block represents an "O" shape.
bool Player::is_O_shape()
{
	for (int i = 0; i < GameConfig::BLOCK_SQUARE_SIZE; i++)
	{
		if ((block[i].getX() != 1 || (block[i].getY() != 1 && block[i].getY() != 0)) && (block[i].getX() != 2 || (block[i].getY() != 1 && block[i].getY() != 0)))
			return false;
	}
	return true;
}

//Drops the Tetris block to the lowest possible position.
void Player::dropShape()
{
	int count = 0;
	bool flag = false;
	while (!flag)
	{
		count++;
		for (int i = 0; i < 4; i++)
		{
			if (block[i].getY() + y + count >= GameConfig::GAME_HEIGHT)
			{
				flag = true;
				break;
			}
			else if (board[block[i].getX() + x][block[i].getY() + y + count] != ' ')
			{
				flag = true;
				break;
			}
		}

	}

	y = y + count - 1;

}

//Checks if a specific row on the game board is completely filled.
bool Player::is_row_full(int row)
{

	for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
	{
		if (board[col][row] == ' ')
			return false;
	}
	return true;
}

//Checksand deletes full rows on the game board, updating the score accordingly.
void Player::check_row_full()
{
	int row;
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		row = block[i].getY() + y + count;
		if (is_row_full(row))
		{
			delete_row(row);
			count++;
		}
	}
	if (count > 1)
	{
		score += 5;
	}
}

//Deletes a specified row on the game board.
void Player::delete_row(int row)
{
	if (row >= 1 && row < GameConfig::GAME_HEIGHT)
	{
		for (int j = row; j >= 1; j--)
		{
			for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
			{
				{
					board[i][j] = board[i][j - 1];
				}
			}
		}
		// Clear the top row
		for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
		{
			board[i][0] = ' ';
		}

		// Update the display after deleting the row
		drawBorder(min_x - 1, min_y - 1);

		// Display the updated board
		for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
		{
			for (int j = 0; j < GameConfig::GAME_HEIGHT; j++)
			{
				gotoxy(i + min_x, j + min_y);
				cout << board[i][j];
			}
		}
	}
	score += 10;
}

//Checks if the top row of the game board is empty.
bool Player::top_row_empty()
{
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		if (board[i][0] != ' ')
			return false;
	}
	return true;
}

//Updates the game board with the current Tetris block and checks for full rows.
void Player::update_board()
{
	for (int i = 0; i < 4; i++)
	{
		board[block[i].getX() + x][block[i].getY() + y] = '*';
		gotoxy(block[i].getX() + x + min_x, block[i].getY() + y + min_y);
		cout << board[block[i].getX() + x][block[i].getY() + y];
	}
	check_row_full();
	y = 0;
	x = GameConfig::GAME_WIDTH / 2;
	score++;
}

//Prepares the Tetris block for the next step, increasing the y-coordinate.
void Player::prepare_next_step()
{
	y++;
}

//Prints the current state of the game board to the console.
void Player::print_board() const
{
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
	{
		for (int j = 0; j < GameConfig::GAME_HEIGHT; j++)
		{
			gotoxy(i + min_x, j + min_y);
			cout << board[i][j];
		}
	}
}

// Returns the current score of the Tetris game.
int Player::getScore() const
{
	return score;
}

//Updates the score by adding the specified value.
void Player::setScore(int added_score)
{
	score += added_score;
}

void Player::remove_and_update_square()
{

	int square_start_x = 0;
	int square_end_x = 0;
	int square_start_y = 0;
	int square_end_y = 0;

	int xPos = block[0].getX() + x;
	int yPos = block[0].getY() + y;

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
			board[i][j] = ' ';
			gotoxy(i + min_x, j + min_y);
			cout << board[i][j];
		}
	}
	Sleep(50);

	for (int i = square_start_x; i <= square_end_x; i++)
	{
		for (int j = square_start_y; j <= square_end_y; j++)
		{
			if (j - hight >= 0)
			{
				board[i][j] = board[i][j - hight];
				board[i][j - hight] = ' ';
				gotoxy(i + min_x, (j - hight) + min_y);
				cout << board[i][j - hight];
				gotoxy(i + min_x, j + min_y);
				cout << board[i][j];

			}
			else
			{
				board[i][j] = ' ';
				gotoxy(i + min_x, j + min_y);
				cout << board[i][j];

			}
		}
	}

	y = 0;
	x = GameConfig::GAME_WIDTH / 2;

}
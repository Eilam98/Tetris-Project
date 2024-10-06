#include <Windows.h> ///for sleep
#include <conio.h> // for kbhit & getch
#include <iostream>
#include <cstdlib>
using namespace std;

#include "general.h"
#include "player.h"
#include "gameConfig.h"
#include "computer.h"
#include "human.h"
#include "game.h"

int main()
{
	srand(time(NULL));
	Game game;
	game.start();
}

//int main()
//{
//	Human left_player(GameConfig::key_board_L, GameConfig::MIN_X_LEFT, GameConfig::MIN_Y_LEFT);
//	Human right_player(GameConfig::key_board_L, GameConfig::MIN_X_LEFT, GameConfig::MIN_Y_LEFT);
//	clrscr();
//	left_player.drawBorder(GameConfig::MIN_X_LEFT, GameConfig::MIN_Y_LEFT);
//	right_player.drawBorder(GameConfig::MIN_X_RIGHT, GameConfig::MIN_Y_RIGHT);
//	bool lp_lost = false, rp_lost = false; // checks if one of the players lost the game, uses it as a stop condition going forward
//	char temp = 0;
//		left_player.getShape();
//		right_player.getShape();
//	bool game_ended = false;
//	while (!game_ended)
//	{
//		gotoxy(GameConfig::MIN_X_LEFT, GameConfig::MIN_Y_LEFT + GameConfig::GAME_HEIGHT + 2);
//		std::printf("Left player score: %d", left_player.getScore());
//		gotoxy(GameConfig::MIN_X_RIGHT, GameConfig::MIN_Y_RIGHT + GameConfig::GAME_HEIGHT + 2);
//		std::printf("Right player score: %d", right_player.getScore());
//		char key_pressed = 0;
//
//		while (_kbhit()) //respond by keys pressed by players and check if relevant to the game
//		{
//			key_pressed = _getch();
//
//			if (key_pressed == 27)
//			{
//				return key_pressed;
//			}
//			if (left_player.key_of_this_player(key_pressed))
//			{
//				left_player.move_shape(key_pressed);
//
//			}
//			else if (right_player.key_of_this_player(key_pressed))
//			{
//				right_player.move_shape(key_pressed);
//			}
//		}
//
//
//		left_player.drawShape('*');
//		right_player.drawShape('*');
//
//		Sleep(400);
//		//for each player check if current dropping block can continue to move down or has reached the bottom
//		// and update the board accordingly
//		if (left_player.blockReachedBottom() || !(left_player.canMoveDown()))
//		{
//			left_player.update_board();
//			left_player.getShape();
//		}
//		else
//		{
//			left_player.drawShape(' ');
//			left_player.prepare_next_step();
//		}
//
//		if (right_player.blockReachedBottom() || !(right_player.canMoveDown()))
//		{
//			right_player.update_board();
//			right_player.getShape();
//		}
//		else
//		{
//			right_player.drawShape(' ');
//			right_player.prepare_next_step();
//		}
//		// check if the last block that's dropped has caused the end of the game
//		if (!left_player.top_row_empty())
//		{
//			right_player.setScore(20);
//			lp_lost = true;
//			game_ended = true;
//		}
//		if (!right_player.top_row_empty())
//		{
//			rp_lost = true;
//			left_player.setScore(20);
//			game_ended = true;
//		}
//	}
//	//clear screen and announce winner
//	clrscr();
//	std::printf("Left Player: %d points\n", left_player.getScore());
//	std::printf("right Player: %d points\n", right_player.getScore());
//	if (lp_lost && !rp_lost)
//	{
//		std::printf("And the winner is... right player!\n\n");
//	}
//	else if (!lp_lost && rp_lost)
//	{
//		std::printf("And the winner is... left player!\n\n");
//	}
//	else // (lp_lost && rp_lost) in case they both reach the top of the board at the same time
//	{
//		if (left_player.getScore() > right_player.getScore())
//		{
//			std::printf("And the winner is... left player!\n\n");
//		}
//		else if (left_player.getScore() < right_player.getScore())
//		{
//			std::printf("And the winner is... right player!\n\n");
//		}
//		else
//		{
//			std::printf("A tie :)\n\n");
//		}
//	}
//	Sleep(3000); // making sure that if a key was pressed immediately after the game ended
//	while (_kbhit()) // it won't cause skipping from the winner announcement board directly to the menu 
//	{
//		temp = _getch();
//	}
//
//	cout << "Press any key to continue to the menu." << endl;
//}

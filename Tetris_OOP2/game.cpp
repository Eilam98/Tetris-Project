#include <Windows.h> ///for sleep
#include <conio.h> // for kbhit & getch
#include <iostream>
#include <cstdlib>

#include "player.h"
#include "game.h"
#include "gameConfig.h"
#include "computer.h"
#include "human.h"

void Game::instrucions()
	{
		char key;
		clrscr();
		std::cout << "Hello, Let's play Tetris!\n" << std::endl;

		std::cout << "Left player, use the following keys:" << std::endl;
		std::cout << "A - move right, S - rotate counterclockwise, D - move left, W - rotate clockwise, X - DROP!\n" << std::endl;

		std::cout << "Right player, use the following keys:" << std::endl;
		std::cout << "J - move right, K - rotate counterclockwise, L - move left, I - rotate clockwise, M - DROP!\n" << std::endl;

		std::cout << "Every block placed on the board gives a player 1 point" << std::endl;
		std::cout << "By filling a row with points, the row will be deleted and the player will recive 10 points!" << std::endl;
		std::cout << "Deleting more than one row by placing a single block grants 5 bonus points" << std::endl;
		std::cout << "The game ends if a players block reaches the top of the playing field, granting 20 point to the opponet" << std::endl;
		std::cout << "The winner is the player whose opponet reached the top of the playing field," << std::endl;
		std::cout << "In case both players reached the top at the same time, the winner will be the player with most points.\n" << std::endl;

		std::cout << "Press any key to continue to the menu, good luck!" << std::endl;
		key = _getch();
		clrscr();

	}

void Game::start()
{
	char key_pressed;
	bool end_key_pressed = false;
	//bool game_running = false;
	Player* left_player = nullptr;// = new Player(GameConfig::MIN_X_LEFT, GameConfig::MIN_Y_LEFT);
	Player* right_player = nullptr;// = new Player(GameConfig::MIN_X_RIGHT, GameConfig::MIN_Y_RIGHT);
	helloMessage();
	clrscr();
	while (true)
	{
		clrscr();
		std::cout << "Hello, Let's play Tetris!" << std::endl; //TODO- put into menu function
		std::cout << "choose option:" << std::endl;
		std::cout << "(1) Start a new game - Human vs Human" << std::endl;
		std::cout << "(2) Start a new game - Human vs Computer" << std::endl;
		std::cout << "(3) Start a new game - Computer vs Computer" << std::endl;
		if (game_running)
		{
			std::cout << "(4) Continue a paused game" << std::endl;
		}
		std::cout << "(8) Present instructions and keys" << std::endl;
		std::cout << "(9) EXIT" << std::endl;

		while (true)
		{
			key_pressed = _getch();


			if ((key_pressed == GameConfig::HUMAN_VS_HUMAN))
			{
				clrscr();
				game_running = false;
				left_player = new Human(GameConfig::key_board_L, GameConfig::MIN_X_LEFT, GameConfig::MIN_Y_LEFT);
				right_player = new Human(GameConfig::key_board_R, GameConfig::MIN_X_RIGHT, GameConfig::MIN_Y_RIGHT);
				run(left_player, right_player);
				break;
			}
			else if ((key_pressed == GameConfig::HUMAN_VS_COMPUTER))
			{
				clrscr();
				game_running = false;
				left_player = new Human(GameConfig::key_board_L, GameConfig::MIN_X_LEFT, GameConfig::MIN_Y_LEFT);
				right_player = new Computer(GameConfig::MIN_Y_RIGHT, GameConfig::MIN_Y_RIGHT);
				Computer* right_player_c = dynamic_cast<Computer*>(right_player);
				if (right_player_c->set_level(GameConfig::RIGHT_PLAYER))
					run(left_player, right_player);
				break;
			}
			else if ((key_pressed == GameConfig::COMPUTER_VS_COMPUTER))
			{
				clrscr();
				game_running = false;
				left_player = new Computer(GameConfig::MIN_X_LEFT, GameConfig::MIN_Y_LEFT);
				right_player = new Computer(GameConfig::MIN_Y_RIGHT, GameConfig::MIN_Y_RIGHT);
				Computer* right_player_c = dynamic_cast<Computer*>(right_player);
				Computer* left_player_c = dynamic_cast<Computer*>(left_player);
				if (right_player_c->set_level(GameConfig::RIGHT_PLAYER))
				{
					if(left_player_c->set_level(GameConfig::LEFT_PLAYER))
						run(left_player, right_player);
				}
				break;
			}
			else if (key_pressed == GameConfig::PAUSED && game_running && left_player && right_player)
			{
				clrscr();
				left_player->print_board();
				right_player->print_board();
				run(left_player, right_player);
				break;
			}
			//getting the instruction and keys of the game
			else if (key_pressed == GameConfig::PRESENT_INSTRUCTIONS)
			{
				clrscr();
				instrucions();
				break;
			}
			//player wants to stop plat the game
			else if (key_pressed == GameConfig::ESC)
			{
				clrscr();
				end_key_pressed = true;
				break;
			}
		}
		if (end_key_pressed)
		{
			break;
		}
	}
	clrscr();
	std::cout << "bye bye..";


}

bool Game::run(Player* left_player, Player* right_player)
{
	Human* left_player_h = dynamic_cast<Human*>(left_player);
	Human* right_player_h = dynamic_cast<Human*>(right_player);
	Computer* left_player_c = dynamic_cast<Computer*>(left_player);
	Computer* right_player_c = dynamic_cast<Computer*>(right_player);
	left_player->drawBorder(GameConfig::MIN_X_LEFT, GameConfig::MIN_Y_LEFT);
	right_player->drawBorder(GameConfig::MIN_X_RIGHT, GameConfig::MIN_Y_RIGHT);
	bool lp_lost = false, rp_lost = false; // checks if one of the players lost the game, uses it as a stop condition going forward
	char temp = 0;
	if (!game_running)
	{
		left_player->getShape();
		right_player->getShape();
		game_running = false;
		if (left_player_c)
		{
			bool flag = left_player_c->get_best_move();
		}
		if (right_player_c)
		{
			bool flag = right_player_c->get_best_move();
		}
	}

	bool game_ended = false;

	while (!game_ended)
	{
		gotoxy(GameConfig::MIN_X_LEFT, GameConfig::MIN_Y_LEFT + GameConfig::GAME_HEIGHT + 2);
		std::cout << "Left player score: "<< left_player->getScore();
		gotoxy(GameConfig::MIN_X_RIGHT, GameConfig::MIN_Y_RIGHT + GameConfig::GAME_HEIGHT + 2);
		std::cout<<"Right player score: "<< right_player->getScore();
		char key_pressed = 0;

		while (_kbhit()) //respond by keys pressed by players and check if relevant to the game
		{
			key_pressed = _getch();

			if (key_pressed == 27)
			{
				game_running = true;
				return key_pressed;
			}
			if (left_player_h)
			{
				if (left_player_h->key_of_this_player(key_pressed))
				{
					left_player_h->move_shape(key_pressed);

				}
			}
			if (right_player_h)
			{
			 if (right_player_h->key_of_this_player(key_pressed))
			{
				right_player_h->move_shape(key_pressed);
			}
			}
		}


		left_player->drawShape('*');
		right_player->drawShape('*');

		Sleep(250);
		//for each player check if current dropping block can continue to move down or has reached the bottom
		// and update the board accordingly
		if (left_player->blockReachedBottom() || !(left_player->canMoveDown()))
		{
			if (left_player->get_shape_type() == GameConfig::BOMB)
			{
				left_player->remove_and_update_square();
			}
			else
			{
				left_player->update_board();
			}
			left_player->getShape();
			if (left_player_c)
			{
				bool flag = left_player_c->get_best_move();
				if (!flag)
					game_ended = true;
			}
		}
		else
		{
			left_player->drawShape(' ');
			if (left_player_c)
			{
				left_player_c->move_shape();
			}
			left_player->prepare_next_step();
		}

		if (right_player->blockReachedBottom() || !(right_player->canMoveDown()))
		{
			if (right_player->get_shape_type() == GameConfig::BOMB)
			{
				right_player->remove_and_update_square();
			}
			else
			{
				right_player->update_board();
			}
			right_player->getShape();
			if (right_player_c)
			{
				bool flag = right_player_c->get_best_move();
				if (!flag)
					game_ended = true;
			}
		}
		else
		{
			right_player->drawShape(' ');
			if (right_player_c)
			{
				right_player_c->move_shape();
			}
			right_player->prepare_next_step();
		}
		// check if the last block that's dropped has caused the end of the game
		if (!left_player->top_row_empty())
		{
			right_player->setScore(20);
			lp_lost = true;
			game_ended = true;
		}
		if (!right_player->top_row_empty())
		{
			rp_lost = true;
			left_player->setScore(20);
			game_ended = true;
		}
	}
	//clear screen and announce winner
	clrscr();
	printf("Left Player: %d points\n", left_player->getScore());
	printf("right Player: %d points\n", right_player->getScore());
	if (lp_lost && !rp_lost)
	{
		printf("And the winner is... right player!\n\n");
	}
	else if (!lp_lost && rp_lost)
	{
		printf("And the winner is... left player!\n\n");
	}
	else // (lp_lost && rp_lost) in case they both reach the top of the board at the same time
	{
		if (left_player->getScore() > right_player->getScore())
		{
			printf("And the winner is... left player!\n\n");
		}
		else if (left_player->getScore() < right_player->getScore())
		{
			printf("And the winner is... right player!\n\n");
		}
		else
		{
			printf("A tie :)\n\n");
		}
	}

	Sleep(3000); // making sure that if a key was pressed immediately after the game ended
	while (_kbhit()) // it won't cause skipping from the winner announcement board directly to the menu 
	{
		temp = _getch();
	}

	std::cout << "Press any key to continue to the menu." << std::endl;
	return temp;
}

void Game::helloMessage()
{
	gotoxy(20, 10);
	std::cout << "Hello And Welcome To Our Tetris Game :)" << std::endl;
	Sleep(1500);

}

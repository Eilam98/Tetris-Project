#ifndef _GAME_CONFIG_H
#define _GAME_CONFIG_H


class GameConfig
{
public:
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	//LEFT PLAYER
	static constexpr int MIN_X_LEFT = 0;
	static constexpr int MIN_Y_LEFT = 0;
	static constexpr char key_board_L[10] = { 'a', 'A', 's', 'S', 'd', 'D', 'w', 'W', 'x', 'X' };

	//RIGHT PLAYER
	static constexpr int MIN_X_RIGHT = 30;
	static constexpr int MIN_Y_RIGHT = 0;
	static constexpr char key_board_R[10] = { 'j', 'J', 'k', 'K', 'l', 'L', 'i', 'I', 'm', 'M' };

	static constexpr int BLOCK_SQUARE_SIZE = 4;
	static constexpr int NUM_OF_SHAPES = 7;

	//MENU KEYS
	static constexpr char HUMAN_VS_HUMAN = '1';
	static constexpr char HUMAN_VS_COMPUTER = '2';
	static constexpr char COMPUTER_VS_COMPUTER = '3';
	static constexpr char PAUSED = '4';
	static constexpr char PRESENT_INSTRUCTIONS = '8';
	static constexpr char ESC = '9';



	static constexpr int L_TYPE = 0;
	static constexpr int I_TYPE = 1;
	static constexpr int O_TYPE = 2;
	static constexpr int S_TYPE = 3;
	static constexpr int Z_TYPE = 4;
	static constexpr int J_TYPE = 5;
	static constexpr int T_TYPE = 6;
	static constexpr int BOMB = 7;

	static constexpr int FULL_ROTATION_CYCLE = 4;
	static constexpr int SHAPE_SIZE = 4;

	static constexpr char BEST = '1';
	static constexpr char GOOD = '2';
	static constexpr char NOVICE = '3';
	static constexpr int LEFT_PLAYER = 0;
	static constexpr int RIGHT_PLAYER = 1;

};


#endif
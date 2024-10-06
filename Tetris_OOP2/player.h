#ifndef _TETRIS_GAME_H
#define _TETRIS_GAME_H

#include "gameConfig.h"
#include "point.h"
#include "general.h"
#include "gameConfig.h"

class Player
{

	int score = 0;
	int shape_type = 0;

protected:
	Point block[4];
	char board[GameConfig::GAME_WIDTH][GameConfig::GAME_HEIGHT];
	int x = GameConfig::GAME_WIDTH / 2;
	int y = 0;
	int min_x = 1;
	int min_y = 1;

public:
	Player(); //Initializes TetrisGame with default player controls.
	//Initializes a TetrisGame with player controls and the position of the player's board.
	/*TetrisGame(TetrisGame& tg);*/ //TODO
	Player(int board_left_upper_edge_x, int board_left_upper_edge_y);
	//Player(const Player& game_to_copy); //copy ctor
	virtual void drawBorder(int _x, int _y); //Draws the border of the Tetris game board starting from a specified position.
	virtual void getShape(); //Generates a random Tetris shapeand initializes the block coordinates accordingly.
	void drawShape(char ch); //Draws the Tetris shape on the game board with the specified character.
	bool blockReachedBottom(); //Checks if the Tetris block has reached the bottom of the game board.
	bool canMoveDown(); //Checks if the Tetris block can move down within the game board.
	//virtual void move_shape(char key_pressed) const = 0;

	bool can_move_left(); //Checks if the Tetris block can move left within the game board.
	int left_point_x(); //Determines the leftmost x-coordinate of the Tetris block

	bool can_move_right(); //Checks if the Tetris block can move right within the game board.
	int right_point_x(); //Determines the rightmost x-coordinate of the Tetris block.

	void rotateShape(); //Rotates the Tetris block clockwise.
	void can_rotate_Shape(); //Checks if rotation fits board limits and doesnt hit a square that's already place on the board.
	void rotateShape_back(); //Rotates the Tetris block counterclockwise.
	void can_rotate_Shape_back(); //Checks if rotation fits board limits
	bool is_O_shape(); //Checks if the Tetris block represents an "O" shape.
	void dropShape(); //Drops the Tetris block to the lowest possible position.

	bool is_row_full(int row); //Checks if a specific row on the game board is completely filled.
	void check_row_full(); //Checksand deletes full rows on the game board, updating the score accordingly
	void delete_row(int row); //Deletes a specified row on the game board.
	bool top_row_empty(); //Checks if the top row of the game board is empty.
	void update_board(); //Updates the game board with the current Tetris block and checks for full rows.
	void prepare_next_step(); //Prepares the Tetris block for the next step, increasing the y-coordinate.
	void print_board() const; //Prints the current state of the game board to the console.
	virtual int getScore() const; // Returns the current score of the Tetris game.
	void setScore(int added_score); //Updates the score by adding the specified value.
	void remove_and_update_square();
	int get_shape_type() const { return shape_type; }
	virtual ~Player() {}

};

#endif

#pragma once
#include "Pixel.h"


typedef enum {
	Up,
	Down,
	Right,
	Left,
	NoMove
} Direction;


class Snake
{
public:
	Snake();
	Snake(int nRow, int nCol);
	~Snake();

	const int snRows;
	const int snColumns;
	const int snMaxSize;
	uint16_t Score = 0;
	Pixel AppleColor;
	Pixel HeadColor;
	Pixel BodyColor;

	void drawBoard(Pixel***);
	int8_t move(Direction Dir);

private:
	uint8_t Lenght = 0;
	uint8_t* Body; //Define Body max size as matrix size. Head is Cell 0
	uint8_t Apple = 0;
	bool AppleCaught = false;

	void resetBody();
	void resetApple();
	void endGame();
};


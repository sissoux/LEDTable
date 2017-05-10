#include "Snake.h"
#include <iostream>


Snake::Snake() : snRows(10), snColumns(10), snMaxSize(snRows*snColumns)
{
	AppleColor = Pixel(90, 255, 255); // Green
	HeadColor = Pixel(28, 255, 255); // Orange
	BodyColor = Pixel(0, 255, 255); // Red
	Body = new uint8_t[snMaxSize];
	this->resetBody();
	this->resetApple();
}

Snake::Snake(int nRow, int nCol) : snRows(nRow), snColumns(nCol), snMaxSize(snRows*snColumns)
{
	AppleColor = Pixel(90, 255, 255); // Green
	HeadColor = Pixel(28, 255, 255); // Orange
	BodyColor = Pixel(0, 255, 255); // Red
	Body = new uint8_t[snMaxSize];
	this->resetBody();
	this->resetApple();
}


Snake::~Snake()
{
	delete[] Body;
}

void Snake::drawBoard(Pixel*** outBuffer)
{
	for (uint8_t x = 0; x < snColumns; x++)
	{
		for (uint8_t y = 0; y < snRows; y++)
		{
			uint8_t CurrentPoint = y * snColumns + x;
			Pixel CurrentColor = Pixel(0, 0, 0);

			if (CurrentPoint == Apple) CurrentColor = AppleColor;
			else if (CurrentPoint == Body[0]) CurrentColor = HeadColor;
			else
			{
				for (int i = 1; i < this->Lenght; i++)
				{
					if (CurrentPoint == Body[i]) CurrentColor = BodyColor;
				}
			}
			*outBuffer[x][y] = CurrentColor;
		}
	}
}

int8_t Snake::move(Direction Dir)
{
	//define new Head position
	uint8_t Head = this->Body[0];
	switch (Dir)
	{
	case Up:
		if (Head / snColumns == 0) //We are on upper edge
		{
			Head = Head + (snColumns * (snRows - 1));
		}
		else Head = Head - (snColumns);
		break;

	case Down:
		if (Head / snColumns == snRows - 1) //We are on lower edge
		{
			Head = Head - (snColumns * (snRows - 1));
		}
		else Head = Head + (snColumns);
		break;

	case Left:
		if (Head % snColumns == 0) //We are on left edge
		{
			Head = Head + (snColumns - 1);
		}
		else Head = Head - 1;
		break;

	case Right:
		if (Head % snColumns == snColumns - 1) //We are on right edge
		{
			Head = Head - (snColumns - 1);
		}
		else Head = Head + 1;
		break;

	default:
		return 0;
		break;
	}
	if (Head != Body[1])  //No Backward movement allowed, do nothing
	{
		// SI Apple ==> Lenght++ / Reset Apple
		if (Head == Apple)
		{
			if (Lenght < snMaxSize) Lenght++;
			else endGame();
			AppleCaught = true;
		}

		uint8_t LenghtMinusOne = this->Lenght - 1;
		for (uint8_t i = 0; i < LenghtMinusOne; i++)
		{
			this->Body[LenghtMinusOne - i] = this->Body[LenghtMinusOne - i - 1];
			if (Head == Body[LenghtMinusOne - i]) //Check Collision with own body
			{
				endGame();
				return -1;
			}
		}
		this->Body[0] = Head;
		if (AppleCaught) resetApple();
		AppleCaught = false;
	}
}

void Snake::resetBody()
{
	Score = Lenght - 2;
	Lenght = 2;
	Body[0] = 1;
	Body[1] = 0;
}

void Snake::resetApple()
{
	bool retry = false;
	do {
		Apple = std::rand()% snRows * snColumns;
		for (int i = 0; i < this->Lenght; i++)
		{
			if (Apple == Body[i]) retry = true;
		}
	} while (retry);
}

void Snake::endGame()
{
	resetBody();
	resetApple();
	std::cout<<"You Lost!, Score = %d"<<Score<<std::endl;
}
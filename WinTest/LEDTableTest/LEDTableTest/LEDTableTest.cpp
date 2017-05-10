// LEDTableTest.cpp : définit le point d'entrée pour l'application console.
//

#define BLACKOUT

#include "stdafx.h"
#include <iostream>
#include "Pixel.h"
#include "LEDMatrix.h"
#include "Snake.h"
#include <sys/timeb.h>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


using namespace std;
LEDMatrix MainMatrix(20,10);
Snake MySnake(20, 10);
void time_Manager(timeb* T, timeb* TPrev);
Direction getInput();
uint32_t maxTime = 0;



int main()
{
	timeb tnow;
	timeb tprev;
	
	cout << "Hello World!" << endl;
	int Maxr = 0;
	int Maxg = 0;
	int Maxb = 0;

	//*MainMatrix.Buffer[3][4] = Pixel(0, 0, 255);

	MySnake.drawBoard(MainMatrix.Buffer);
	MainMatrix.render();
	
	while (true)
	{
		//time_Manager(&tnow, &tprev);
		Direction movement = getInput();
		if (movement != NoMove)
		{
			cout << endl << endl;
			MySnake.move(movement);
			MySnake.drawBoard(MainMatrix.Buffer);
			MainMatrix.render();
		}
	}
    return 0;
}

void time_Manager(timeb* T, timeb* TPrev)
{
	uint32_t diff = 0;
	ftime(T);
	if (T->time != TPrev->time)
	{
		diff = 999*(TPrev->time-T->time) - TPrev->millitm + T->millitm;
	}
	else
	{
		if (TPrev->millitm != T->millitm)
		{
			diff = T->millitm - TPrev->millitm;
			TPrev = T;
		}
	}
}

void refresh_display()
{
	MainMatrix.render();
}

Direction getInput()
{
	int c = getch();
	switch (c) {
	case KEY_UP:
		return (Direction)Up;	//cout << endl << "Up" << endl;//key up
		break;
	case KEY_DOWN:
		return (Direction)Down;	//cout << endl << "Down" << endl;   // key down
		break;
	case KEY_LEFT:
		return (Direction)Left;	//cout << endl << "Left" << endl;  // key left
		break;
	case KEY_RIGHT:
		return (Direction)Right;//cout << endl << "Right" << endl;  // key right
		break;
	default:
		return (Direction)NoMove;
		break;
	}
}
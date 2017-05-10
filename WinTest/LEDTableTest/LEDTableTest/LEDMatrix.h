#pragma once
#include "Pixel.h"

//#define N_ROW 20
//#define N_COL 10
//#define STRIP_LENGHT N_ROW*N_COL

class LEDMatrix
{
public:
	const int m_nRows;
	const int m_nColumns;
	const int m_nMaxSize;
	Pixel*** Buffer;
	Pixel** Strip;
	LEDMatrix();
	LEDMatrix(int nRow, int nCol);
	~LEDMatrix();
	int render();	//Fill Strip with active Buffer

private: 
	void display();	//Display current Strip
	Pixel*** bufferCreation(int rows, int columns);
	void bufferDestruction(Pixel*** tBuffer, int rows, int columns);
};


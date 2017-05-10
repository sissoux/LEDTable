#include "stdafx.h"
#include "LEDMatrix.h"
#include <iostream>
#include "string"


LEDMatrix::LEDMatrix() :m_nRows(10), m_nColumns(10), m_nMaxSize(m_nRows*m_nColumns)
{
	Buffer = bufferCreation(m_nRows, m_nColumns);
	this->render();
}

LEDMatrix::LEDMatrix(int nRow, int nCol) : m_nRows(nRow), m_nColumns(nCol), m_nMaxSize(m_nRows*m_nColumns)
{
	Buffer = bufferCreation(m_nRows, m_nColumns);
	this->render();
}


LEDMatrix::~LEDMatrix()
{
	bufferDestruction(Buffer, m_nRows, m_nColumns);
}


int LEDMatrix::render()
{
	display();
	/*
	bool NewFrame = false;
	for (int x = 0; x < m_nColumns; x++)
	{
		for (int y = 0; y < m_nRows; y++)
		{
			unsigned int index = 0;
			
			if (x % 2 == 0) index = m_nRows*(x + 1) - 1 - y;
			else index = m_nRows * x + y;

			if (index < m_nMaxSize)
			{
				/*if (this->Strip[index] != this->Buffer[x][y])
				{
					this->Strip[index] = *(this->Buffer[x][y]);
					NewFrame = true;
				}
			}
		}
	}
	if (NewFrame) display();*/
	return 0;
}

void LEDMatrix::display()
{
	for (int y = 0; y < m_nRows; y++)
	{
		for (int x = 0; x < m_nColumns; x++)
		{
			if (Buffer[x][y]->value != 0) std::cout << 1<<" ";
			else std::cout << 0 << " ";
		}
		std::cout << std::endl;
	}

#ifndef BLACKOUT

#endif
}


Pixel*** LEDMatrix::bufferCreation(int rows, int columns)
{
	Pixel*** tBuffer = new Pixel**[columns];
	Strip = new Pixel*[rows*columns];
	for (int x = 0; x < columns; x++)		//for each double pointer of the table, allocate size of a single pointer
	{
		tBuffer[x] = new Pixel*[rows];
		for (int y = 0; y < rows; y++)		//for each pointer, instanciate a Pixel;
		{
			unsigned int index = 0;

			if (x % 2 == 0) index = m_nRows*(x + 1) - 1 - y;
			else index = m_nRows * x + y;

			tBuffer[x][y] = new Pixel(0,0,0);
			if (index < m_nMaxSize) Strip[index] = tBuffer[x][y];
		}
	}
	return tBuffer;
}

void LEDMatrix::bufferDestruction(Pixel*** tBuffer, int rows, int columns)
{
	for (int x = 0; x < columns; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			delete tBuffer[x][y];	//Delete each Pixel
		}
		delete[] tBuffer[x];	//Delete each pointer table in table tbuffer[x]
	}
	delete[] tBuffer;	//Delete each pointer table in tbuffer
}
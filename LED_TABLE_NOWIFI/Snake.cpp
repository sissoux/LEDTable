#include "Snake.h"
#include "define.h"


Snake::Snake() : Game("Snake")
{
  AppleColor = CHSV(96, 255, 255); // Green
  HeadColor = CHSV(32, 255, 255); // Orange
  BodyColor = CHSV(0, 255, 255); // Red

  this->resetBody();
  this->resetApple();
}


void Snake::setDirection(SnakeDirection Dir)
{
  switch (Direction) //We check first that we are not turning back
  {
    case Up: if (Dir == Down) return; break;
    case Down: if (Dir == Up) return; break;
    case Right: if (Dir == Left) return; break;
    case Left: if (Dir == Right) return; break;
  }
  Serial.println(Dir);
  Direction = Dir;
}


void Snake::cmdUp()
{
  this->setDirection(Down);
}

void Snake::cmdDown()
{
  this->setDirection(Up);
}

void Snake::cmdRight()
{
  this->setDirection(Left);
}

void Snake::cmdLeft()
{
  this->setDirection(Right);
}

void Snake::cmdStart()
{
  Paused = !Paused;
}

void Snake::update()
{
  this->move();
}

int8_t Snake::move()
{
  if (!Paused)
  {
    //define new Head position
    uint8_t Head = this->Body[0];
    switch (Direction)
    {

      case Up:
        if (Head / N_COLUMN == 0) //We are on upper edge
        {
          Head = Head + (N_COLUMN * (N_ROW - 1));
        }
        else Head = Head - (N_COLUMN);
        break;

      case Down:
        if (Head / N_COLUMN == N_ROW-1) //We are on lower edge
        {
          Head = Head - (N_COLUMN * (N_ROW - 1));
        }
        else Head = Head + (N_COLUMN);
        break;

      case Left:
        if ((Head) % N_COLUMN == 0) //We are on left edge
        {
          Head = Head + (N_COLUMN -1);
        }
        else Head = Head - 1;
        break;

      case Right:
        if ((Head) % N_COLUMN == 9) //We are on right edge
        {
          Head = Head - (N_COLUMN - 1);
        }
        else Head = Head + 1;
        break;

      default:
        break;
    }

    if (Head == Body[1])
    {
      Head = Body[0];
    }
    else
    {
      // SI Apple ==> Lenght++ / Reset Apple
      if (Head == Apple)
      {
        if (Lenght < MAX_SIZE) Lenght++;
        else restartGame();
        AppleCaught = true;

        //Increase game loop speed
        this->Rate = Rate - 15;
        if (this->Rate < MIN_SNAKE_RATE) this->Rate = MIN_SNAKE_RATE;
      }

      uint8_t LenghtMinusOne = this->Lenght - 1;
      for (uint8_t i = 0; i < LenghtMinusOne; i++)
      {
        this->Body[LenghtMinusOne - i] = this->Body[LenghtMinusOne - i - 1];
        if (Head == Body[LenghtMinusOne - i]) //Check Collision with own body
        {
          restartGame();
        }
      }
    }
    this->Body[0] = Head;
    if (AppleCaught)
    {
      resetApple();
    }
    AppleCaught = false;
  }
}

void Snake::resetBody()
{
  Lenght = 2;
  Body[0] = 1;
  Body[1] = 0;
  Rate = DEFAULT_SNAKE_RATE;
  Score = 0;
}

void Snake::resetApple()
{
  bool retry = false;
  this->Score += 2 + Lenght / 10; //the longer snake is, the higher score is increased
  do {
    Apple = random(0, N_ROW * N_COLUMN);
    for (int i = 0; i < this->Lenght; i++)
    {
      if (Apple == Body[i]) retry = true;
    }
  } while (retry);
}

void Snake::endGame()
{
  Paused = true;
  resetBody();
  resetApple();
}

void Snake::restartGame()
{
  IsReseting = true;
}

void Snake::drawBoard(CRGB Buffer[][N_COLUMN])
{
  if (!IsReseting)
  {
    for (uint8_t x = 0; x < N_COLUMN; x++)    //We check each pixel, if it's supposed to be ON : Set corresponding LED ON, else turn it off
    {
      for (uint8_t y = 0; y < N_ROW; y++)
      {
        uint8_t CurrentPoint = y * N_COLUMN + x;
        CRGB CurrentColor = CRGB(0, 0, 0);
        if (CurrentPoint == Apple) CurrentColor = AppleColor;
        else if (CurrentPoint == Body[0]) CurrentColor = HeadColor;
        else
        {
          for (int i = 1; i < this->Lenght; i++)
          {
            if (CurrentPoint == Body[i]) CurrentColor = BodyColor;
          }
        }
        Buffer[y][x] = CurrentColor;
      }
    }
  }
  else
  {
    if (ResetStep < MAX_SIZE)
    {
      for (uint8_t x = 0; x < N_COLUMN; x++)    //We check each pixel, if it's supposed to be ON : Set corresponding LED ON, else turn it off
      {
        for (uint8_t y = 0; y < N_ROW; y++)
        {
          uint8_t CurrentPoint = y * N_COLUMN + x;
          CRGB CurrentColor = CRGB(0, 0, 0);
          if (CurrentPoint == ResetStep )
          {
            CurrentColor = CHSV(random(0, 255), random(0, 255), 255);
            Buffer[y][x] = CurrentColor;
          }
        }
      }
      ResetStep++;
    }
    else
    {
      for (uint8_t x = 0; x < N_COLUMN; x++)    //We check each pixel, if it's supposed to be ON : Set corresponding LED ON, else turn it off
      {
        for (uint8_t y = 0; y < N_ROW; y++)
        {
            Buffer[y][x] = CRGB(0, 0, 0);
          
        }
      }
      resetBody();
      resetApple();
      IsReseting = false;
      ResetStep = 0;
    }
  }

}

















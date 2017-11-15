#include "FastLED.h"
#include "FastLED_Matrix.h"
#include "ESP8266_DotMatrix.h"
#include "Clock.h"
#include "define.h"
#include <elapsedMillis.h>
#include "Game.h"
#include "Snake.h"
#include <Wire.h>
#include "NESController.h"

FastMatrix10x20 MainMatrix;
DotMatrix8x32 ScoreDisplay = DotMatrix8x32();

NESController Controller;

Game NoGame;
Snake SnakeInstance;
Snake *SnakePtr = &SnakeInstance;
Game *CurrentGame = &NoGame;

Clock MyClock;

elapsedMillis SerialTimer = 0;
#define SERIAL_REFRESH_RATE 10

elapsedMillis TimeRefreshTimer = 0;

elapsedMillis DisplayRefreshTimer = 0;

elapsedMillis ScrollTextTimer = 0;

elapsedMillis SecondCounter = 0;

elapsedMillis GameTimer = 0;

elapsedMillis ControllerTimer = 0;

uint8_t ScrollLoops = 0;
uint8_t ScrollRate = 70;  //ms between scroll steps
int16_t LimitIndex = 0;
int16_t ScrollIndex = 0;
String ScrollText;

typedef enum {
  Snake,
  Tetris,
  Time,
  Temp,
  Ambient,
  Music,
  Standby
} Mode;

Mode CurrentMode = Standby;
bool NextMode = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, DATA_PIN, CLOCK_PIN, BGR>(MainMatrix.leds, NUM_LEDS);
  ScoreDisplay.begin(0x72, 0x71);
  ScoreDisplay.setRotation(3);
  Controller.begin();
  ScrollSet("Retro Gaming table - VisionOfLight design", 1);
  resetTimers();

}

void ScrollClear()
{
  if (ScrollLoops)
  {
    ScoreDisplay.clear();
    ScoreDisplay.writeDisplay();
    ScrollLoops = 0;
  }
}

void ScrollSet(const char* Text, uint8_t NumberOfScroll)
{
  ScrollSet(String(Text), NumberOfScroll);
}

void ScrollSet(String Text, uint8_t NumberOfScroll)
{
  ScrollLoops = NumberOfScroll;
  ScrollRate = 50;
  LimitIndex = -((int16_t)Text.length() + 1) * 6;
  ScrollText = Text;
  ScrollIndex = 32; //Start on the left side for left to right scroll
  ScoreDisplay.setTextSize(1);
  ScoreDisplay.setTextWrap(false);

}

void ScrollUpdate()
{
  if (ScrollLoops)
  {
    if (ScrollIndex >= LimitIndex)
    {
      ScoreDisplay.clear();
      ScoreDisplay.setCursor(ScrollIndex, 0);
      ScoreDisplay.print(ScrollText);
      ScoreDisplay.writeDisplay();
      ScrollIndex--;
    }
    else
    {
      ScrollLoops--;
      ScrollIndex = 32;
    }
  }
}

void DisplayScore(uint16_t Score)
{
  if (!ScrollLoops)   //We know we are not scrolling text
  {
    for (uint8_t i = 0 ; i < 5; i++)
    {
      ScoreDisplay.drawChar(6 * (4 - i), 0, '0' + (Score % 10), 1, 0, 1);
      Score = Score / 10;
    }
    ScoreDisplay.writeDisplay();
  }
}


void resetTimers()
{
  //SerialTimer = 0;
  //TimeRefreshTimer = 0;
  DisplayRefreshTimer = 0;
  SecondCounter = 0;
  //NTPTimeout = 0;
  GameTimer = 0;
  ControllerTimer = 0;
}


void loop()
{
  TaskManager();
}

void TaskManager()
{

  if (ScrollTextTimer >= ScrollRate)
  {
    ScrollTextTimer = 0;
    ScrollUpdate();
  }

  if (ControllerTimer >= CONTROLLER_REFRESH_RATE)
  {
    ControllerTimer = 0;
    Controller.update();

    for (int i = 0; i < NB_CMD; i++)
    {
      if ((Controller.ActiveCommands & (1 << i)) ^ (Controller.PreviousCommands & (1 << i)) && ((Controller.ActiveCommands & (1 << i)) != 0))
      {
        switch ((Controller_cmd)i)
        {
          case CrossUp: CurrentGame->cmdUp();
            Serial.println("Up");
            break;
          case CrossDown: CurrentGame->cmdDown();
            Serial.println("Down");
            break;
          case CrossLeft: CurrentGame->cmdLeft();
            Serial.println("Left");
            break;
          case CrossRight: CurrentGame->cmdRight();
            Serial.println("Right");
            break;
          case A: CurrentGame->cmdA();
            Serial.println("A");
            break;
          case B: CurrentGame->cmdB();
            Serial.println("B");
            break;
          case Select: NextMode = true;
            Serial.println("Select");
            break;
          case Start: CurrentGame->cmdStart();
            Serial.println("Start");
            break;
          default:
            break;
        }
      }
    }
    Controller.PreviousCommands = Controller.ActiveCommands;
  }

  while (SecondCounter >= ONE_SECOND)
  {
    SecondCounter -= ONE_SECOND; //Substract only one second as we want to remain synchronized to system time (avoid drifting)
    MyClock.UnixTimeStamp++;
    MyClock.UpdateTime();

#ifdef SERIAL_VERBOSE
    TimeCounter++;
    if (TimeCounter >= 60) //Print state every minute
    {
      TimeCounter = 0;
      Serial.print("Current time is : ");
      Serial.print(MyClock.Hour);
      Serial.print(":");
      Serial.println(MyClock.Minute);
      Serial.print("s before next sync : ");
      Serial.println((TimeReSyncPeriod - TimeReSyncTimer) / 1000);
    }
#endif
  }

  if (GameTimer >= CurrentGame->Rate) //Game loop refresh rate is depending on the game itself, and on its state ==> Difficulty for tetris increase with the speed of the game, thus CurrentGame->Rate is decreasing.
  {
    GameTimer -= CurrentGame->Rate;
    if (!CurrentGame->Paused && strcmp(CurrentGame->Name, "TheCakeIsALie") != 0) CurrentGame->update();
  }

  if (DisplayRefreshTimer >= DISPLAY_REFRESH_RATE)  //Display refresh is also coupled with state update depending on received commands.
  {
    DisplayRefreshTimer = 0;

    if (strcmp(CurrentGame->Name, "TheCakeIsALie") != 0 && !CurrentGame->Paused)  //If we are in a running game ==> we cannot change currentMode by mistake, Display of the score is also updated
    {
      Serial.println("Here");
      ScrollClear();
      CurrentGame->drawBoard(MainMatrix.OutputBuffer);
      DisplayScore(SecondCounter);
      // Update secondary matrix with current score

    }
    else
    {

      switch (CurrentMode)
      {
        case Standby:
          MainMatrix.clear();
          if (NextMode)
          {
            MainMatrix.clear();
            NextMode = false;
            CurrentMode = Time;
            ScrollSet("Time Display", 2);
          }
          break;

        case Time:
          MainMatrix.clear();
          MainMatrix.writeTime(MyClock.Hour, MyClock.Minute);
          if (NextMode)
          {
            MainMatrix.clear();
            NextMode = false;
            CurrentMode = Snake;
            CurrentGame->endGame();
            CurrentGame = SnakePtr;
            ScrollSet(String(CurrentGame->Name) + " - Press Start", 2);
          }
          break;

        case Snake:
          CurrentGame->drawBoard(MainMatrix.OutputBuffer);
          if (NextMode)
          {
            MainMatrix.clear();
            NextMode = false;
            CurrentMode = Standby;
            CurrentGame->endGame();
            CurrentGame = &NoGame;
            ScrollSet("Standby", 2);
          }
          break;

        default:
          CurrentMode = Standby;
          break;
      }
    }
    MainMatrix.writeDisplay();
  }
}


























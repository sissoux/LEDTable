#ifndef Game_h
#define Game_h
#include "Arduino.h"
#include "FastLED.h"
#include "define.h"



class Game
{
  public:
    const char* Name;
    uint16_t Score = 0;
    uint16_t Rate = 500;
    bool Paused = true; //Paused by default for easy start
    Game();
    Game(char* GameName);
    virtual void cmdUp();
    virtual void cmdDown();
    virtual void cmdLeft();
    virtual void cmdRight();
    virtual void cmdStart();
    virtual void cmdA();
    virtual void cmdB();
    virtual void drawBoard(CRGB Buffer[][COLUMN_COUNT]);
    virtual void update();
    virtual void endGame();
    virtual void restartGame();
};


#endif

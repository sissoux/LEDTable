#ifndef Snake_h
#define Snake_h
#include "Arduino.h"
#include "FastLED.h"
#include "define.h"
#include "Game.h"


#define MAX_SIZE N_ROW*N_COLUMN
#define DEFAULT_SNAKE_RATE 1000 // Move every second
#define MIN_SNAKE_RATE 100

// Game Matrix is build this way: 0-----------> N_COLUMN-1
//                                 ----------->
//                                 ----------->
//                                 -----------> (N_ROW*N_COLUMN)-1

typedef enum {
  Up,
  Down,
  Right,
  Left
} SnakeDirection;


class Snake : public Game
{
  public:
    uint8_t Lenght = 0;
    uint8_t Body[MAX_SIZE]; //Define Body max size as matrix size. Head is Cell 0
    uint8_t Apple = 0;
    bool AppleCaught = false;
    //uint16_t Score = 0;
    CHSV AppleColor;
    CHSV HeadColor;
    CHSV BodyColor;
    void drawBoard(CRGB Buffer[][COLUMN_COUNT]);
    void endGame();
    void restartGame();

    void cmdUp();
    void cmdDown();
    void cmdRight();
    void cmdLeft();
    void cmdStart();
    void update();

    Snake();
    int8_t move();
    //bool Paused = true; //Paused by default for easy start

  private:
    void setDirection(SnakeDirection Dir);
    SnakeDirection Direction = Right;
    uint16_t ResetStep = 0;
    bool IsReseting = false;
    void resetBody();
    void resetApple();

};
#endif


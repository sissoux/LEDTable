
#include "Game.h"


Game::Game() : Name("TheCakeIsALie") {
}

Game::Game(char* GameName) : Name(GameName) {
}

void Game::cmdUp() {
  Serial.println("Up Not implemented");
}
void Game::cmdDown() {
  Serial.println("Down Not implemented");
}
void Game::cmdLeft() {
  Serial.println("Left Not implemented");
}
void Game::cmdRight() {
  Serial.println("Right Not implemented");
}
void Game::cmdStart() {
  Serial.println("Start Not implemented");
}
void Game::cmdA() {
  Serial.println("A Not implemented");
}
void Game::cmdB() {
  Serial.println("B Not implemented");
}
void Game::drawBoard(CRGB Buffer[][COLUMN_COUNT]) {
  Serial.println("DrawBoard Not implemented");
}
void Game::update() {
  Serial.println("Update Not implemented");
}
void Game::endGame() {
}
void Game::restartGame() {
  Serial.println("restart Not implemented");
}

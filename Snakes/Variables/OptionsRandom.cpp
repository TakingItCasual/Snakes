#include "OptionsRandom.h"

void OptionsRandom::setBorderTeleport(bool setBorderTeleport){
  BorderTeleport = setBorderTeleport;
}

bool OptionsRandom::getBorderTeleport(){
  return BorderTeleport;
}

void OptionsRandom::setPlayerAmount(int setPlayerAmount){
  PlayerAmount = setPlayerAmount;
}

int OptionsRandom::getPlayerAmount(){
  return PlayerAmount;
}

void OptionsRandom::setSnakeAmount(int setSnakeAmount){
  SnakeAmount = setSnakeAmount;
}

int OptionsRandom::getSnakeAmount(){
  return SnakeAmount;
}

void OptionsRandom::setAISmartness(int setAISmartness){
  AISmartness = setAISmartness;
}

int OptionsRandom::getAISmartness(){
  return AISmartness;
}

void OptionsRandom::setTailSpeed(int setTailSpeed){
  TailSpeed = setTailSpeed;
}

int OptionsRandom::getTailSpeed(){
  return TailSpeed;
}

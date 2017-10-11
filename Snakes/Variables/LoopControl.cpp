#include "LoopControl.h"

void LoopControl::setGameReset(bool setGameReset){
  GameReset = setGameReset;
  if(!GameReset){
    ExitState = true;
    MenuState = -1;
    InputLoopBreak = true;
    ForLoopIfCheck = false;
  }
}

bool LoopControl::getGameReset(){
  return GameReset;
}

void LoopControl::setExitState(bool setExitState){
  if(GameReset){
    ExitState = setExitState;
  }
}

bool LoopControl::getExitState(){
  return ExitState;
}

void LoopControl::setMenuState(int setMenuState){
  if(GameReset){
    MenuState = setMenuState;
  }
}

int LoopControl::getMenuState(){
	return MenuState;
}

void LoopControl::setInputLoopBreak(bool setInputLoopBreak){
  if(GameReset){
    InputLoopBreak = setInputLoopBreak;
  }
}

bool LoopControl::getInputLoopBreak(){
  return InputLoopBreak;
}

void LoopControl::setForLoopIfCheck(bool setForLoopIfCheck){
  if(GameReset){
    ForLoopIfCheck = setForLoopIfCheck;
  }
}

bool LoopControl::getForLoopIfCheck(){
  return ForLoopIfCheck;
}

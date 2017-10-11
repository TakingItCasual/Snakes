#include "Snake.h"

void Snake::setTailLength(int PlayerNumber, int setTailLength){
  TailLength[PlayerNumber] = setTailLength;
}

int Snake::getTailLength(int PlayerNumber){
  return TailLength[PlayerNumber];
}

int Snake::DirectionReverse(int Direction){
  if(Direction == 1 || Direction == 3){
    return Direction+1;
  }else if(Direction == 2 || Direction == 4){
    return Direction-1;
  }else{
    return 0;
  }
}

void Snake::setATL(int PlayerNumber, int setATL){
  ATL[PlayerNumber] = setATL;
}

int Snake::getATL(int PlayerNumber){
  return ATL[PlayerNumber];
}

void Snake::setSnakePosY(int PlayerNumber, int setSnakePosY){
  SnakePosY[PlayerNumber] = setSnakePosY;
}

int Snake::getSnakePosY(int PlayerNumber){
  return SnakePosY[PlayerNumber];
}

void Snake::setSnakePosX(int PlayerNumber, int setSnakePosX){
  SnakePosX[PlayerNumber] = setSnakePosX;
}

int Snake::getSnakePosX(int PlayerNumber){
  return SnakePosX[PlayerNumber];
}

void Snake::initializeVectors(int SnakeAmount){
  SnakeTailConnect.resize(SnakeAmount);
  TailRetract.resize(SnakeAmount);
}

void Snake::setTailRetractSize(int SnakeNumber, int setTailRetractSize){
  TailRetract[SnakeNumber].resize(setTailRetractSize);
  SnakeTailConnect[SnakeNumber].resize(setTailRetractSize);
  for(int FLL=0; FLL<setTailRetractSize; FLL++){
    TailRetract[SnakeNumber][FLL].resize(2);
    SnakeTailConnect[SnakeNumber][FLL].resize(2);
  }
}

void Snake::setTailRetract(int PlayerNumber, int TailSlot, int YorX, int setTailRetract){
  TailRetract[PlayerNumber][TailSlot][YorX] = setTailRetract;
}

int Snake::getTailRetract(int PlayerNumber, int TailSlot, int YorX){
  return TailRetract[PlayerNumber][TailSlot][YorX];
}

void Snake::setSnakeTailConnect(int SnakeNumber, int TailSlot, int setBackward, int setForward){
  if(setBackward!=5){
    SnakeTailConnect[SnakeNumber][TailSlot][0] = setBackward;
  }
  if(setForward!=5){
    SnakeTailConnect[SnakeNumber][TailSlot][1] = setForward;
  }
}

int Snake::getSnakeTailConnect(int SnakeNumber, int TailSlot, int Direction){
  return SnakeTailConnect[SnakeNumber][TailSlot][Direction];
}

void Snake::setTECy(int PlayerNumber, int setTECy){
  TECy[PlayerNumber] = setTECy;
}

int Snake::getTECy(int PlayerNumber){
  return TECy[PlayerNumber];
}

void Snake::setTECx(int PlayerNumber, int setTECx){
  TECx[PlayerNumber] = setTECx;
}

int Snake::getTECx(int PlayerNumber){
  return TECx[PlayerNumber];
}

void Snake::setCISIA(int PlayerNumber, bool setCISIA){
  CISIA[PlayerNumber] = setCISIA;
}

bool Snake::getCISIA(int PlayerNumber){
  return CISIA[PlayerNumber];
}

void Snake::setSnakeDelete(int PlayerNumber, bool setSnakeDelete){
  SnakeDelete[PlayerNumber] = setSnakeDelete;
}

bool Snake::getSnakeDelete(int PlayerNumber){
  return SnakeDelete[PlayerNumber];
}

void Snake::setInput(int PlayerNumber, int setInput){
  Input[PlayerNumber] = setInput;
}

int Snake::getInput(int PlayerNumber){
  return Input[PlayerNumber];
}

void Snake::setLastInput(int PlayerNumber, int setLastInput){
  LastInput[PlayerNumber] = setLastInput;
}

int Snake::getLastInput(int PlayerNumber){
  return LastInput[PlayerNumber];
}

void Snake::setDTNF(int SnakeNumber, int YorX, int DistanceOrDirection, int setDTNF){
  DTNF[SnakeNumber][YorX][DistanceOrDirection] = setDTNF;
}

int Snake::getDTNF(int SnakeNumber, int YorX, int DistanceOrDirection){
  return DTNF[SnakeNumber][YorX][DistanceOrDirection];
}

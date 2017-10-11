#include "Tail.h"

void Tail::ProcessUserInput(InternalRandom& IRand, LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake){
  for(int SN=0; SN<ORand.getSnakeAmount(); SN++){ //SN = SnakeNumber
    if(Snake.getCISIA(SN)){
      if(Snake.getInput(SN) == 1){ //Moves the Snake up.
        if(Snake.getSnakePosY(SN)>1){
          if(Map.CollideCheck((Snake.getSnakePosY(SN)-1), Snake.getSnakePosX(SN))){
            Snake.setCISIA(SN, false);
            Snake.setSnakeDelete(SN, 1);
          }else{
            Snake.setSnakePosY(SN, Snake.getSnakePosY(SN)-1);
          }
        }else if(ORand.getBorderTeleport()){
          if(Map.CollideCheck(Map.getMapSizeY()-2, Snake.getSnakePosX(SN))){
            Snake.setCISIA(SN, false);
            Snake.setSnakeDelete(SN, 1);
          }else{
            Snake.setSnakePosY(SN, Map.getMapSizeY()-2);
          }
        }else{
          Snake.setCISIA(SN, false);
          Snake.setSnakeDelete(SN, 1);
        }
      }else if(Snake.getInput(SN) == 2){ //Moves the Snake down.
        if(Snake.getSnakePosY(SN)<(Map.getMapSizeY()-2)){
          if(Map.CollideCheck(Snake.getSnakePosY(SN)+1, Snake.getSnakePosX(SN))){
            Snake.setCISIA(SN, false);
            Snake.setSnakeDelete(SN, 1);
          }else{
            Snake.setSnakePosY(SN, Snake.getSnakePosY(SN)+1);
          }
        }else if(ORand.getBorderTeleport()){
          if(Map.CollideCheck(1, Snake.getSnakePosX(SN))){
            Snake.setCISIA(SN, false);
            Snake.setSnakeDelete(SN, 1);
          }else{
            Snake.setSnakePosY(SN, 1);
          }
        }else{
          Snake.setCISIA(SN, false);
          Snake.setSnakeDelete(SN, 1);
        }
      }else if(Snake.getInput(SN) == 3){ //Moves the Snake left
        if(Snake.getSnakePosX(SN)>1){
          if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)-1)){
            Snake.setCISIA(SN, false);
            Snake.setSnakeDelete(SN, 1);
          }else{
            Snake.setSnakePosX(SN, Snake.getSnakePosX(SN)-1);
          }
        }else if(ORand.getBorderTeleport()){
          if(Map.CollideCheck(Snake.getSnakePosY(SN), Map.getMapSizeX()-2)){
            Snake.setCISIA(SN, false);
            Snake.setSnakeDelete(SN, 1);
          }else{
            Snake.setSnakePosX(SN, Map.getMapSizeX()-2);
          }
        }else{
          Snake.setCISIA(SN, false);
          Snake.setSnakeDelete(SN, 1);
        }
      }else if(Snake.getInput(SN) == 4){ //Moves the Snake right
        if(Snake.getSnakePosX(SN)<(Map.getMapSizeX()-2)){
          if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)+1)){
            Snake.setCISIA(SN, false);
            Snake.setSnakeDelete(SN, 1);
          }else{
            Snake.setSnakePosX(SN, Snake.getSnakePosX(SN)+1);
          }
        }else if(ORand.getBorderTeleport()){
          if(Map.CollideCheck(Snake.getSnakePosY(SN), 1)){
            Snake.setCISIA(SN, false);
            Snake.setSnakeDelete(SN, 1);
          }else{
            Snake.setSnakePosX(SN, 1);
          }
        }else{
          Snake.setCISIA(SN, false);
          Snake.setSnakeDelete(SN, 1);
        }
      }else{
        IRand.setExitStatus(4);
        Loop.setExitState(true);
      }
    }
  }
}

void Tail::DeleteSnakeTail(InternalRandom& IRand, Map& Map, OptionsRandom& ORand, Snake& Snake){
  for(int SN1=0; SN1<(ORand.getSnakeAmount()-1); SN1++){ //Deletes snakes that run into each other
    for(int SN2=(SN1+1); SN2<ORand.getSnakeAmount(); SN2++){
      if(Snake.getSnakePosX(SN1)==Snake.getSnakePosX(SN2) && Snake.getSnakePosY(SN1)==Snake.getSnakePosY(SN2)){

        Snake.setCISIA(SN1, false);
        Snake.setSnakeDelete(SN1, 1);
        Snake.setCISIA(SN2, false);
        Snake.setSnakeDelete(SN2, 1);
      }
    }
  }
  for(int SN=0; SN<ORand.getSnakeAmount(); SN++){ //Deletes snake that dies from collision or other causes
    if(!Snake.getCISIA(SN) && Snake.getSnakeDelete(SN)){
      for(int TailPart=0; TailPart<Snake.getATL(SN); TailPart++){
        Map.setMapCollision(Snake.getTailRetract(SN, TailPart, 0), Snake.getTailRetract(SN, TailPart, 1), 0);
        Snake.setSnakeTailConnect(SN, TailPart, 0, 0),
        Snake.setSnakePosY(SN, 0);
        Snake.setSnakePosX(SN, 0);
      }
      Snake.setATL(ORand.getSnakeAmount(), Snake.getATL(ORand.getSnakeAmount())-Snake.getATL(SN));
      Snake.setATL(SN, 0);
      Snake.setSnakeDelete(SN, 0);
      Snake.setTailRetractSize(SN, 4);
    }
  }
}

void Tail::TailLengthMaintainer(InternalRandom& IRand, Map& Map, OptionsRandom& ORand, Snake& Snake){
  //Maintains the length of the tail
  for(int SN=0; SN<ORand.getSnakeAmount(); SN++){ //SN = SnakeNumber
    if(Snake.getCISIA(SN)){ //Checks if the snake is alive
      for(int TailSlot=Snake.getTailLength(SN); TailSlot>0; TailSlot--){ //TailRetracts get pushed up, while TailConnects get pushed down

        Snake.setTailRetract(SN, TailSlot, 0, Snake.getTailRetract(SN, TailSlot-1, 0));
        Snake.setTailRetract(SN, TailSlot, 1, Snake.getTailRetract(SN, TailSlot-1, 1));
        Snake.setSnakeTailConnect(SN, TailSlot, Snake.getSnakeTailConnect(SN, TailSlot-1, 0),
                                  Snake.getSnakeTailConnect(SN, TailSlot-1, 1));
      }

      Snake.setTailRetract(SN, 0, 0, Snake.getSnakePosY(SN));
      Snake.setTailRetract(SN, 0, 1, Snake.getSnakePosX(SN));
      Snake.setSnakeTailConnect(SN, 1, 5, Snake.getInput(SN));
      Snake.setSnakeTailConnect(SN, 0, Snake.DirectionReverse(Snake.getInput(SN)), 0);

      if(Snake.getATL(SN)==Snake.getTailLength(SN)){ //If the snake hasn't eaten, deletes tail end
        Snake.setTECy(SN, Snake.getTailRetract(SN, Snake.getTailLength(SN), 0));
        Snake.setTECx(SN, Snake.getTailRetract(SN, Snake.getTailLength(SN), 1));
        Snake.setSnakeTailConnect(SN, Snake.getATL(SN)-1, 0, 5);
        Map.setMapCollision(Snake.getTECy(SN), Snake.getTECx(SN), 0);
      }else if(Snake.getATL(SN)<Snake.getTailLength(SN)){ //If the snake has eaten, increases tail size
        Snake.setATL(SN, Snake.getATL(SN)+1); //Snake that ate getting it's size increased
        Snake.setATL(ORand.getSnakeAmount(), Snake.getATL(ORand.getSnakeAmount())+1); //Last ATL value is all snake sizes combined, increase that too
      }
      //Places the new Snake head onto the map.
      Map.setMapCollision(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN), 2);
    }
  }
}

#include "NPC.h"

void NPC::NPC_Move(Food& Food, Map& Map, OptionsRandom& ORand, Snake& Snake){
  for(int SN=ORand.getPlayerAmount(); SN<ORand.getSnakeAmount(); SN++){
    if(Snake.getCISIA(SN)){

      if(Snake.getSnakePosY(SN)>=Food.getFoodPosY()){
        Snake.setDTNF(SN, 0, 1, 1);
        Snake.setDTNF(SN, 0, 0, (Snake.getSnakePosY(SN)-Food.getFoodPosY()));
      }else{
        Snake.setDTNF(SN, 0, 1, 2);
        Snake.setDTNF(SN, 0, 0, (Food.getFoodPosY()-Snake.getSnakePosY(SN)));
      }
      if(Snake.getSnakePosX(SN)>=Food.getFoodPosX()){
        Snake.setDTNF(SN, 1, 1, 3);
        Snake.setDTNF(SN, 1, 0, (Snake.getSnakePosX(SN)-Food.getFoodPosX()));
      }else{
        Snake.setDTNF(SN, 1, 1, 4);
        Snake.setDTNF(SN, 1, 0, (Food.getFoodPosX()-Snake.getSnakePosX(SN)));
      }

      if((Snake.getDTNF(SN, 0, 0)<=Snake.getDTNF(SN, 1, 0) && Snake.getDTNF(SN, 0, 0)>0) || Snake.getDTNF(SN, 1, 0)==0){

        if(Snake.getDTNF(SN, 0, 1)==1){

          if(Snake.getLastInput(SN)!=2){
            if(Map.CollideCheck(Snake.getSnakePosY(SN)-1, Snake.getSnakePosX(SN))){
              if(Snake.getDTNF(SN, 1, 1)==3 && Snake.getLastInput(SN)!=3){
                if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)-1)){
                  if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)+1)){
                    Snake.setInput(SN, 2);
                  }else{
                    Snake.setInput(SN, 4);
                  }
                }else{
                  Snake.setInput(SN, 3);
                }
              }else if(Snake.getLastInput(SN)!=4){
                if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)+1)){
                  if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)-1)){
                    Snake.setInput(SN, 2);
                  }else{
                    Snake.setInput(SN, 3);
                  }
                }else{
                  Snake.setInput(SN, 4);
                }
              }else{
                Snake.setInput(SN, 1);
              }
            }else{
              Snake.setInput(SN, 1);
            }
          }else{
            if(Snake.getDTNF(SN, 1, 1)==3){
              if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)-1)){
                if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)+1)){
                  Snake.setInput(SN, 2);
                }else{
                  Snake.setInput(SN, 4);
                }
              }else{
                Snake.setInput(SN, 3);
              }
            }else{
              if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)+1)){
                if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)-1)){
                  Snake.setInput(SN, 2);
                }else{
                  Snake.setInput(SN, 3);
                }
              }else{
                Snake.setInput(SN, 4);
              }
            }
          }

        }else{

          if(Snake.getLastInput(SN)!=1){
            if(Map.CollideCheck(Snake.getSnakePosY(SN)+1, Snake.getSnakePosX(SN))){
              if(Snake.getDTNF(SN, 1, 1)==3 && Snake.getLastInput(SN)!=3){
                if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)-1)){
                  if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)+1)){
                    Snake.setInput(SN, 1);
                  }else{
                    Snake.setInput(SN, 4);
                  }
                }else{
                  Snake.setInput(SN, 3);
                }
              }else if(Snake.getLastInput(SN)!=4){
                if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)+1)){
                  if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)-1)){
                    Snake.setInput(SN, 1);
                  }else{
                    Snake.setInput(SN, 3);
                  }
                }else{
                  Snake.setInput(SN, 4);
                }
              }else{
                Snake.setInput(SN, 2);
              }
            }else{
              Snake.setInput(SN, 2);
            }
          }else{
            if(Snake.getDTNF(SN, 1, 1)==3){
              if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)-1)){
                if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)+1)){
                  Snake.setInput(SN, 1);
                }else{
                  Snake.setInput(SN, 4);
                }
              }else{
                Snake.setInput(SN, 3);
              }
            }else{
              if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)+1)){
                if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)-1)){
                  Snake.setInput(SN, 1);
                }else{
                  Snake.setInput(SN, 3);
                }
              }else{
                Snake.setInput(SN, 4);
              }
            }
          }
        }

      }else if(Snake.getDTNF(SN, 1, 0)>0){

        if(Snake.getDTNF(SN, 1, 1)==3){

          if(Snake.getLastInput(SN)!=4){
            if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)-1)){
              if(Snake.getDTNF(SN, 0, 1)==1 && Snake.getLastInput(SN)!=1){
                if(Map.CollideCheck(Snake.getSnakePosY(SN)-1, Snake.getSnakePosX(SN))){
                  if(Map.CollideCheck(Snake.getSnakePosY(SN)+1, Snake.getSnakePosX(SN))){
                    Snake.setInput(SN, 4);
                  }else{
                    Snake.setInput(SN, 2);
                  }
                }else{
                  Snake.setInput(SN, 1);
                }
              }else if(Snake.getLastInput(SN)!=2){
                if(Map.CollideCheck(Snake.getSnakePosY(SN)+1, Snake.getSnakePosX(SN))){
                  if(Map.CollideCheck(Snake.getSnakePosY(SN)-1, Snake.getSnakePosX(SN))){
                    Snake.setInput(SN, 4);
                  }else{
                    Snake.setInput(SN, 1);
                  }
                }else{
                  Snake.setInput(SN, 2);
                }
              }else{
                Snake.setInput(SN, 3);
              }
            }else{
              Snake.setInput(SN, 3);
            }
          }else{
            if(Snake.getDTNF(SN, 0, 1)==1){
              if(Map.CollideCheck(Snake.getSnakePosY(SN)-1, Snake.getSnakePosX(SN))){
                if(Map.CollideCheck(Snake.getSnakePosY(SN)+1, Snake.getSnakePosX(SN))){
                  Snake.setInput(SN, 3);
                }else{
                  Snake.setInput(SN, 2);
                }
              }else{
                Snake.setInput(SN, 1);
              }
            }else{
              if(Map.CollideCheck(Snake.getSnakePosY(SN)+1, Snake.getSnakePosX(SN))){
                if(Map.CollideCheck(Snake.getSnakePosY(SN)-1, Snake.getSnakePosX(SN))){
                  Snake.setInput(SN, 3);
                }else{
                  Snake.setInput(SN, 1);
                }
              }else{
                Snake.setInput(SN, 2);
              }
            }
          }

        }else{

          if(Snake.getLastInput(SN)!=3){
            if(Map.CollideCheck(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN)+1)){
              if(Snake.getDTNF(SN, 0, 1)==1 && Snake.getLastInput(SN)!=1){
                if(Map.CollideCheck(Snake.getSnakePosY(SN)-1, Snake.getSnakePosX(SN))){
                  if(Map.CollideCheck(Snake.getSnakePosY(SN)+1, Snake.getSnakePosX(SN))){
                    Snake.setInput(SN, 3);
                  }else{
                    Snake.setInput(SN, 2);
                  }
                }else{
                  Snake.setInput(SN, 1);
                }
              }else if(Snake.getLastInput(SN)!=2){
                if(Map.CollideCheck(Snake.getSnakePosY(SN)+1, Snake.getSnakePosX(SN))){
                  if(Map.CollideCheck(Snake.getSnakePosY(SN)-1, Snake.getSnakePosX(SN))){
                    Snake.setInput(SN, 3);
                  }else{
                    Snake.setInput(SN, 1);
                  }
                }else{
                  Snake.setInput(SN, 2);
                }
              }else{
                Snake.setInput(SN, 4);
              }
            }else{
              Snake.setInput(SN, 4);
            }
          }else{
            if(Snake.getDTNF(SN, 0, 1)==1){
              if(Map.CollideCheck(Snake.getSnakePosY(SN)-1, Snake.getSnakePosX(SN))){
                if(Map.CollideCheck(Snake.getSnakePosY(SN)+1, Snake.getSnakePosX(SN))){
                  Snake.setInput(SN, 4);
                }else{
                  Snake.setInput(SN, 2);
                }
              }else{
                Snake.setInput(SN, 1);
              }
            }else{
              if(Map.CollideCheck(Snake.getSnakePosY(SN)+1, Snake.getSnakePosX(SN))){
                if(Map.CollideCheck(Snake.getSnakePosY(SN)-1, Snake.getSnakePosX(SN))){
                  Snake.setInput(SN, 4);
                }else{
                  Snake.setInput(SN, 1);
                }
              }else{
                Snake.setInput(SN, 2);
              }
            }
          }

        }
      }
      Snake.setLastInput(SN, Snake.getInput(SN));
    }
  }
}

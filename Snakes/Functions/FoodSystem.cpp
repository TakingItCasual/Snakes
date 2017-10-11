#include "FoodSystem.h"

void FoodSys::FoodProcess(Food& Food, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                          LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake){

  for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
    if(Food.getFoodPosY() == Snake.getSnakePosY(SN) && Food.getFoodPosX() == Snake.getSnakePosX(SN)){
      IRand.setScore(SN,IRand.getScore(SN)+1);

      string Score;
      stringstream IntToString;
      IntToString << IRand.getScore(SN);
      Score = IntToString.str();
      IRand.setScoreText(SN, 1, IRand.getScoreText(SN, 0)+IntToString.str());
      GF_Var.Scores[SN] = TTF_RenderText_Solid(GF_Var.font, IRand.getScoreText(SN, 1).c_str(), GF_Var.textColor);

      Snake.setTailLength(SN, Snake.getTailLength(SN)+1);
      Snake.setTailRetractSize(SN, Snake.getTailLength(SN)+1);

      if(Snake.getATL(ORand.getSnakeAmount())<(((Map.getMapSizeY()-2)*(Map.getMapSizeX()-2))-Food.getMFCIA()-1)){
        srand(time(0));
        do{
          Food.setFoodPosY(1+(rand()%(Map.getMapSizeY()-2)));
          Food.setFoodPosX(1+(rand()%(Map.getMapSizeX()-2)));
        }while(Map.getMapCollision(Food.getFoodPosY(), Food.getFoodPosX())!=0);

        if(!Food.getMFCIA()){
          srand(time(0));
          Food.setMFI(1+(rand()%Food.getSFCOS()));
        }

        Map.setMapCollision(Food.getFoodPosY(), Food.getFoodPosX(), 3);
      }
    }
  }

  if(Food.getMFI() == Food.getSFCOS()){
    if(Snake.getATL(ORand.getSnakeAmount())<(((Map.getMapSizeY()-2)*(Map.getMapSizeX()-2))-2)){
      Food.setMFCIA(true);
      Food.setMFI(0);

      srand(time(0));
      do{
        Food.setFoodPos2Y(1+(rand()%(Map.getMapSizeY()-2)));
        Food.setFoodPos2X(1+(rand()%(Map.getMapSizeX()-2)));
      }while(Map.getMapCollision(Food.getFoodPos2Y(), Food.getFoodPos2X())!=0);

      Map.setMapCollision(Food.getFoodPos2Y(), Food.getFoodPos2X(), 3);
      Food.setFoodDirection(1+(rand()%4));
      Food.setFoodRetract(0, 0, Food.getFoodPos2Y());
      Food.setFoodRetract(0, 1, Food.getFoodPos2X());
    }else{
      Food.setMFCIA(false);
      Food.setMFI(0);
    }
  }else if(Food.getMFCIA()){
    Loop.setForLoopIfCheck(false);
    for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
      if(Food.getFoodPos2Y() == Snake.getSnakePosY(SN) && Food.getFoodPos2X() == Snake.getSnakePosX(SN)){
        Food.setFood2Eater(SN+1);
        Food.setMFCIA(false);
        Loop.setForLoopIfCheck(true);
      }
    }
    if(Loop.getForLoopIfCheck()){
      Loop.setForLoopIfCheck(false);
    }else if(Food.getFoodDirection() == 1){ //Food goes up.

      if(Food.getFoodPos2Y()>1){
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if((Food.getFoodPos2Y()-1)==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision((Food.getFoodPos2Y()-1), Food.getFoodPos2X())!=0){
          Food.setFoodDirection(2);
          if(Food.getFoodPos2Y() < (Map.getMapSizeY()-2)){
            for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
              if((Food.getFoodPos2Y()+1)==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
                Food.setFood2Eater(SN+1);
                Food.setMFCIA(false);
                Loop.setForLoopIfCheck(true);
                break;
              }
            }
            if(Loop.getForLoopIfCheck()){
              Loop.setForLoopIfCheck(false);
            }else if(Map.getMapCollision((Food.getFoodPos2Y()+1), Food.getFoodPos2X())!=0){

            }else{
              Food.setFoodPos2Y(Food.getFoodPos2Y()+1);
            }
          }else{
            for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
              if(1==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
                Food.setFood2Eater(SN+1);
                Food.setMFCIA(false);
                Loop.setForLoopIfCheck(true);
                break;
              }
            }
            if(Loop.getForLoopIfCheck()){
              Loop.setForLoopIfCheck(false);
            }else if(Map.getMapCollision(1, Food.getFoodPos2X())!=0 ||
                     !(ORand.getBorderTeleport())){

            }else{
              Food.setFoodPos2Y(1);
            }
          }
        }else{
          Food.setFoodPos2Y(Food.getFoodPos2Y()-1);
        }
      }else if(ORand.getBorderTeleport()){
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if((Map.getMapSizeY()-2)==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision((Map.getMapSizeY()-2), Food.getFoodPos2X())!=0){
          Food.setFoodDirection(2);
          for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
            if((Food.getFoodPos2Y()+1)==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
              Food.setFood2Eater(SN+1);
              Food.setMFCIA(false);
              Loop.setForLoopIfCheck(true);
              break;
            }
          }
          if(Loop.getForLoopIfCheck()){
            Loop.setForLoopIfCheck(false);
          }else if(Map.getMapCollision((Food.getFoodPos2Y()+1), Food.getFoodPos2X())!=0){

          }else{
            Food.setFoodPos2Y(Food.getFoodPos2Y()+1);
          }
        }else{
          Food.setFoodPos2Y(Map.getMapSizeY()-2);
        }
      }else if(!ORand.getBorderTeleport()){
        Food.setFoodDirection(2);
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if((Food.getFoodPos2Y()+1)==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision((Food.getFoodPos2Y()+1), Food.getFoodPos2X())!=0){

        }else{
          Food.setFoodPos2Y(Food.getFoodPos2Y()+1);
        }
      }
    }else if(Food.getFoodDirection() == 2){ //Food goes down.

      if(Food.getFoodPos2Y()<(Map.getMapSizeY()-2)){
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if((Food.getFoodPos2Y()+1)==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision((Food.getFoodPos2Y()+1), Food.getFoodPos2X())!=0){
          Food.setFoodDirection(1);
          if(Food.getFoodPos2Y() > 1){
            for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
              if((Food.getFoodPos2Y()-1)==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
                Food.setFood2Eater(SN+1);
                Food.setMFCIA(false);
                Loop.setForLoopIfCheck(true);
                break;
              }
            }
            if(Loop.getForLoopIfCheck()){
              Loop.setForLoopIfCheck(false);
            }else if(Map.getMapCollision((Food.getFoodPos2Y()-1), Food.getFoodPos2X())!=0){

            }else{
              Food.setFoodPos2Y(Food.getFoodPos2Y()-1);
            }
          }else{
            for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
              if((Map.getMapSizeY()-2)==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
                Food.setFood2Eater(SN+1);
                Food.setMFCIA(false);
                Loop.setForLoopIfCheck(true);
                break;
              }
            }
            if(Loop.getForLoopIfCheck()){
              Loop.setForLoopIfCheck(false);
            }else if(Map.getMapCollision((Map.getMapSizeY()-2), Food.getFoodPos2X())!=0 ||
                     !(ORand.getBorderTeleport())){

            }else{
              Food.setFoodPos2Y((Map.getMapSizeY()-2));
            }
          }
        }else{
          Food.setFoodPos2Y(Food.getFoodPos2Y()+1);
        }
      }else if(ORand.getBorderTeleport()){
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if(1==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision(1, Food.getFoodPos2X())!=0){
          Food.setFoodDirection(1);
          for(int SN=1; SN<ORand.getSnakeAmount(); SN++){
            if((Food.getFoodPos2Y()-1)==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
              Food.setFood2Eater(SN+1);
              Food.setMFCIA(false);
              Loop.setForLoopIfCheck(true);
              break;
            }
          }
          if(Loop.getForLoopIfCheck()){
            Loop.setForLoopIfCheck(false);
          }else if(Map.getMapCollision((Food.getFoodPos2Y()-1), Food.getFoodPos2X())!=0){

          }else{
            Food.setFoodPos2Y(Food.getFoodPos2Y()-1);
          }
        }else{
          Food.setFoodPos2Y(1);
        }
      }else if(!ORand.getBorderTeleport()){
        Food.setFoodDirection(1);
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if((Food.getFoodPos2Y()-1)==Snake.getSnakePosY(SN) && Food.getFoodPos2X()==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision((Food.getFoodPos2Y()-1), Food.getFoodPos2X())!=0){

        }else{
          Food.setFoodPos2Y(Food.getFoodPos2Y()-1);
        }
      }
    }else if(Food.getFoodDirection() == 3){ //Food goes left.

      if(Food.getFoodPos2X()>1){
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && (Food.getFoodPos2X()-1)==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision(Food.getFoodPos2Y(), (Food.getFoodPos2X()-1))!=0){
          Food.setFoodDirection(4);
          if(Food.getFoodPos2X() < (Map.getMapSizeX()-2)){
            for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
              if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && (Food.getFoodPos2X()+1)==Snake.getSnakePosX(SN)){
                Food.setFood2Eater(SN+1);
                Food.setMFCIA(false);
                Loop.setForLoopIfCheck(true);
                break;
              }
            }
            if(Loop.getForLoopIfCheck()){
              Loop.setForLoopIfCheck(false);
            }else if(Map.getMapCollision(Food.getFoodPos2Y(), (Food.getFoodPos2X()+1))!=0){

            }else{
              Food.setFoodPos2X(Food.getFoodPos2X()+1);
            }
          }else{
            for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
              if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && 1==Snake.getSnakePosX(SN)){
                Food.setFood2Eater(SN+1);
                Food.setMFCIA(false);
                Loop.setForLoopIfCheck(true);
                break;
              }
            }
            if(Loop.getForLoopIfCheck()){
              Loop.setForLoopIfCheck(false);
            }else if(Map.getMapCollision(Food.getFoodPos2Y(), 1)!=0 ||
                     !(ORand.getBorderTeleport())){

            }else{
              Food.setFoodPos2X(1);
            }
          }
        }else{
          Food.setFoodPos2X(Food.getFoodPos2X()-1);
        }
      }else if(ORand.getBorderTeleport()){
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && (Map.getMapSizeX()-2)==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision(Food.getFoodPos2Y(), (Map.getMapSizeX()-2))!=0){
          Food.setFoodDirection(4);
          for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
            if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && (Food.getFoodPos2X()+1)==Snake.getSnakePosX(SN)){
              Food.setFood2Eater(SN+1);
              Food.setMFCIA(false);
              Loop.setForLoopIfCheck(true);
              break;
            }
          }
          if(Loop.getForLoopIfCheck()){
            Loop.setForLoopIfCheck(false);
          }else if(Map.getMapCollision(Food.getFoodPos2Y(), (Food.getFoodPos2X()+1))!=0){

          }else{
            Food.setFoodPos2X(Food.getFoodPos2X()+1);
          }
        }else{
          Food.setFoodPos2X(Map.getMapSizeX()-2);
        }
      }else if(!ORand.getBorderTeleport()){
        Food.setFoodDirection(4);
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && (Food.getFoodPos2X()+1)==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision(Food.getFoodPos2Y(), (Food.getFoodPos2X()+1))!=0){

        }else{
          Food.setFoodPos2X(Food.getFoodPos2X()+1);
        }
      }
    }else if(Food.getFoodDirection() == 4){ //Food goes right.

      if(Food.getFoodPos2X()<(Map.getMapSizeX()-2)){
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && (Food.getFoodPos2X()+1)==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision(Food.getFoodPos2Y(), (Food.getFoodPos2X()+1))!=0){
          Food.setFoodDirection(3);
          if(Food.getFoodPos2X() > 1){
            for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
              if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && (Food.getFoodPos2X()-1)==Snake.getSnakePosX(SN)){
                Food.setFood2Eater(SN+1);
                Food.setMFCIA(false);
                Loop.setForLoopIfCheck(true);
                break;
              }
            }
            if(Loop.getForLoopIfCheck()){
              Loop.setForLoopIfCheck(false);
            }else if(Map.getMapCollision(Food.getFoodPos2Y(), (Food.getFoodPos2X()-1))!=0){

            }else{
              Food.setFoodPos2X(Food.getFoodPos2X()-1);
            }
          }else{
            for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
              if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && (Map.getMapSizeX()-2)==Snake.getSnakePosX(SN)){
                Food.setFood2Eater(SN+1);
                Food.setMFCIA(false);
                Loop.setForLoopIfCheck(true);
                break;
              }
            }
            if(Loop.getForLoopIfCheck()){
              Loop.setForLoopIfCheck(false);
            }else if(Map.getMapCollision(Food.getFoodPos2Y(), (Map.getMapSizeX()-2))!=0 ||
                     !(ORand.getBorderTeleport())){

            }else{
              Food.setFoodPos2X((Map.getMapSizeX()-2));
            }
          }
        }else{
          Food.setFoodPos2X(Food.getFoodPos2X()+1);
        }
      }else if(ORand.getBorderTeleport()){
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && 1==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision(Food.getFoodPos2Y(), 1)!=0){
          Food.setFoodDirection(3);
          for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
            if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && (Food.getFoodPos2X()-1)==Snake.getSnakePosX(SN)){
              Food.setFood2Eater(SN+1);
              Food.setMFCIA(false);
              Loop.setForLoopIfCheck(true);
              break;
            }
          }
          if(Loop.getForLoopIfCheck()){
            Loop.setForLoopIfCheck(false);
          }else if(Map.getMapCollision(Food.getFoodPos2Y(), (Food.getFoodPos2X()-1))!=0){

          }else{
            Food.setFoodPos2X(Food.getFoodPos2X()-1);
          }
        }else{
          Food.setFoodPos2X(1);
        }
      }else if(!ORand.getBorderTeleport()){
        Food.setFoodDirection(3);
        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          if(Food.getFoodPos2Y()==Snake.getSnakePosY(SN) && (Food.getFoodPos2X()-1)==Snake.getSnakePosX(SN)){
            Food.setFood2Eater(SN+1);
            Food.setMFCIA(false);
            Loop.setForLoopIfCheck(true);
            break;
          }
        }
        if(Loop.getForLoopIfCheck()){
          Loop.setForLoopIfCheck(false);
        }else if(Map.getMapCollision(Food.getFoodPos2Y(), (Food.getFoodPos2X()-1))!=0){

        }else{
          Food.setFoodPos2X(Food.getFoodPos2X()-1);
        }
      }
    }
    if(!(Food.getMFCIA())){
      for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
        if(Food.getFood2Eater()==(SN+1)){
          IRand.setScore(SN, IRand.getScore(SN)+2);

          string Score;
          stringstream IntToString;
          IntToString << IRand.getScore(SN);
          Score = IntToString.str();
          IRand.setScoreText(SN, 1, IRand.getScoreText(SN, 0)+IntToString.str());
          GF_Var.Scores[SN] = TTF_RenderText_Solid(GF_Var.font, IRand.getScoreText(SN, 1).c_str(), GF_Var.textColor);

          Snake.setTailLength(SN, Snake.getTailLength(SN)+1);
          Snake.setTailRetractSize(SN, Snake.getTailLength(SN)+1);
        }
      }
    }else{
      Map.setMapCollision(Food.getFoodRetract(0, 0), Food.getFoodRetract(0, 1), 0);
      Food.setFoodRetract(1, 0, Food.getFoodRetract(0, 0));
      Food.setFoodRetract(1, 1, Food.getFoodRetract(0, 1));

      Map.setMapCollision(Food.getFoodPos2Y(), Food.getFoodPos2X(), 3);
      Food.setFoodRetract(0, 0, Food.getFoodPos2Y());
      Food.setFoodRetract(0, 1, Food.getFoodPos2X());
    }
  }
}

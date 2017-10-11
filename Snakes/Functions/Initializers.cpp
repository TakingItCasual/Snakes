#include "Initializers.h"

void Initializers::ExternalVariableInitializers(Food& Food, GMI_Vars& GMI_Var, InternalRandom& IRand,
                                                LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake){
  //When the following is false, the program will exit
  Loop.setGameReset(true);
  //Sets ExitState to default
  Loop.setExitState(false);
  //Sets player/snake amount to default
  ORand.setPlayerAmount(1);
  ORand.setSnakeAmount(1);
  //The following 2 integers control everything about the game map size
  Map.setMapSizeY(22);
  Map.setMapSizeX(22);
  IRand.setMSABOMS(Map.getMapSizeX(), Map.getMapSizeY());
  //High scores default
  IRand.setHighScores(0, 0);
  IRand.setHighScores(1, 0);
  IRand.setHighScores(2, 0);
  IRand.setHighScores(3, 0);
  //Sets fast, medium and slow tailspeeds
  IRand.setTailSpeedNum(0, 125);
  IRand.setTailSpeedNum(1, 250);
  IRand.setTailSpeedNum(2, 500);
  //Sets default tailspeed
  ORand.setTailSpeed(IRand.getTailSpeedNum(1));
  //The following bool gives the option to allow teleporting to the opposite border or not
  ORand.setBorderTeleport(true);
}

void Initializers::InternalVariableInitializers(Food& Food, GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                                                LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake){
  for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
    string SnakeNumber;
    stringstream IntToString;
    IntToString << (SN+1);
    SnakeNumber = IntToString.str();

    if(SN<ORand.getPlayerAmount()){
      IRand.setScoreText(SN, 0, ("P"+IntToString.str())+": ");
    }else{
      IRand.setScoreText(SN, 0, ("p"+IntToString.str())+": ");
    }

    if(!IRand.getLoadGame()){
      IRand.setScoreText(SN, 1, IRand.getScoreText(SN, 0)+"0");
    }else{
      string Score;
      stringstream IntToString;
      IntToString << IRand.getScore(SN);
      Score = IntToString.str();
      IRand.setScoreText(SN, 1, IRand.getScoreText(SN, 0)+IntToString.str());
    }
    GMI_Var.setButtonPos(SN, SN*4, Map.getMapSizeY(), 4);
  }

  if(!IRand.getLoadGame()){ //If a game isn't being loaded this will initialize what needs to be initialized.
    Food.setMFCIA(false);

    Snake.initializeVectors(ORand.getSnakeAmount());

    for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
      IRand.setScore(SN, 0);
    }

    for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
      Snake.setTailLength(SN, 3);
      Snake.setATL(SN, 1);
      Snake.setTailRetractSize(SN, Snake.getTailLength(SN)+1);
      Snake.setCISIA(SN, true);
      Snake.setSnakeDelete(SN, false);
    }

    for(int SN=0, Even=true; SN<ORand.getSnakeAmount(); SN++, Even=!Even){

      if(Even){
        Snake.setSnakePosX(SN, 2);
        Snake.setInput(SN, 4);
        Snake.setLastInput(SN, 4);
      }else{
        Snake.setSnakePosX(SN, (Map.getMapSizeX()-3));
        Snake.setInput(SN, 3);
        Snake.setLastInput(SN, 3);
      }

    }
    Snake.setSnakePosY(0, 2);
    if(ORand.getSnakeAmount()>1){
      Snake.setSnakePosY(ORand.getSnakeAmount()-1, (Map.getMapSizeY()-3));

      if(ORand.getSnakeAmount()>2){
        for(int SN=ORand.getSnakeAmount()-2, ExtraY=0; SN>0; SN--){
          for(int ExtraGap=0; true; ExtraGap++){
            if((Map.getMapSizeY()-6) == (ORand.getSnakeAmount()-2)+((ORand.getSnakeAmount()-1)*(2+ExtraGap))){
              Snake.setSnakePosY(SN, 2+(SN*(3+ExtraGap)));
              break;
            }else if((Map.getMapSizeY()-6) < ((ORand.getSnakeAmount()-2)*2+1)+((ORand.getSnakeAmount()-1)*(2+ExtraGap))){
              Snake.setSnakePosY(SN, 2+(SN*(3+ExtraGap)));

              ExtraY=(ORand.getSnakeAmount()-1)-(Map.getMapSizeY()-(2+(ORand.getSnakeAmount()*(3+ExtraGap)-ExtraGap)));
              if(SN-ExtraY>0){
                Snake.setSnakePosY(SN, Snake.getSnakePosY(SN) + (SN-ExtraY));
              }

              break;
            }
          }
        }
      }
    }

    for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
      for(int TailPart=0; TailPart<=Snake.getTailLength(SN); TailPart++){
        Snake.setSnakeTailConnect(SN, TailPart, 0, 0);
      }
    }
    for(int SN=ORand.getSnakeAmount(); SN<Const::MaxPlayerAmount; SN++){
      Snake.setCISIA(SN, false);
      Snake.setATL(SN, 0);
      Snake.setSnakePosY(SN, 0);
      Snake.setSnakePosX(SN, 0);
    }
    Snake.setATL(ORand.getSnakeAmount(), ORand.getSnakeAmount());
  }

  for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
    GF_Var.Scores[SN] = TTF_RenderText_Solid(GF_Var.font, IRand.getScoreText(SN, 1).c_str(), GF_Var.textColor);
  }

  Food.setSFCOS(4);
  Food.setFood2Eater(0);
  Loop.setExitState(false);
  IRand.setExitStatus(1);
  Loop.setInputLoopBreak(false);
  Loop.setForLoopIfCheck(false);
}

void Initializers::MapBorderBuild(InternalRandom& IRand, Map& Map){ //Creates the borders of the map.
  Map.setMapSize(Map.getMapSizeY(), Map.getMapSizeX());
  for(int TBLO = 0; TBLO < Map.getMapSizeX(); TBLO++){ //TBLO = TopBottomLayOut
    Map.setMapCollision(0, TBLO, 1);
    if(!IRand.getLoadGame()){ //If a game isn't being loaded the map will be filled empty.
      for(int MapColumns=1; MapColumns<(Map.getMapSizeY()-2); MapColumns++){
        Map.setMapCollision(MapColumns, TBLO, 0);
      }
    }
    Map.setMapCollision(Map.getMapSizeY()-1, TBLO, 1);
  }
  for(int SLO = 1; SLO < (Map.getMapSizeY()-1); SLO++){ //SLO = SidesLayOut
    Map.setMapCollision(SLO, 0, 1);
    Map.setMapCollision(SLO, (Map.getMapSizeX()-1), 1);
  }
}

void Initializers::FunctionInitializers(Food& Food, InternalRandom& IRand, Map& Map, OptionsRandom& ORand, Snake& Snake, Timer& Timer){
  if(!IRand.getLoadGame()){
    //Snake head(s) initializer
    for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
      Map.setMapCollision(Snake.getSnakePosY(SN), Snake.getSnakePosX(SN), 2);
    }

    //Food initializer
    srand(time(0));
    do{
      Food.setFoodPosY(1+(rand()%(Map.getMapSizeY()-2)));
      Food.setFoodPosX(1+(rand()%(Map.getMapSizeX()-2)));
    }while(Map.getMapCollision(Food.getFoodPosY(), Food.getFoodPosX())!=0);
    Map.setMapCollision(Food.getFoodPosY(), Food.getFoodPosX(), 3);

    //Initializes the TailRetract process
    for(int PN=0; PN<ORand.getSnakeAmount(); PN++){
      Snake.setTailRetract(PN, 0, 0, Snake.getSnakePosY(PN));
      Snake.setTailRetract(PN, 0, 1, Snake.getSnakePosX(PN));
    }
  }
  //Initializes the timer
  Timer.StartTimer();
}

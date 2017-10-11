#include "Files.h"

void Files::ReadOptionsFile(InternalRandom& IRand, Map& Map, MidVars& MidVar, OptionsRandom& ORand, Snake& Snake){

  ifstream OptionsOpen("OptionsSave.txt");

  if(OptionsOpen){
    OptionsOpen >> MidVar.IntMidVar >> MidVar.IntMidVar2;
    if(MidVar.IntMidVar <= Const::MaxMapSizeX && MidVar.IntMidVar >= 6){
      Map.setMapSizeX(MidVar.IntMidVar);
    }
    if(MidVar.IntMidVar2 <= Const::MaxMapSizeY && MidVar.IntMidVar2 >= 6){
      Map.setMapSizeY(MidVar.IntMidVar2);
    }
    IRand.setMSABOMS(Map.getMapSizeX(), Map.getMapSizeY());

    OptionsOpen >> MidVar.IntMidVar;
    if(MidVar.IntMidVar==0 || MidVar.IntMidVar==1){
      ORand.setBorderTeleport(MidVar.IntMidVar);
    }

    OptionsOpen >> MidVar.IntMidVar;
    ORand.setTailSpeed(MidVar.IntMidVar);

    MidVar.IntMidVar = 0;
    MidVar.IntMidVar2 = 0;
  }
}

void Files::ReadHighScoresFile(InternalRandom& IRand, MidVars& MidVar){
  ifstream HighScores("HighScores.txt");

  if(HighScores){
    HighScores >> MidVar.IntMidVar;
    IRand.setHighScores(0, MidVar.IntMidVar);

    HighScores >> MidVar.IntMidVar;
    IRand.setHighScores(1, MidVar.IntMidVar);

    HighScores >> MidVar.IntMidVar;
    IRand.setHighScores(2, MidVar.IntMidVar);

    HighScores >> MidVar.IntMidVar;
    IRand.setHighScores(3, MidVar.IntMidVar);

    MidVar.IntMidVar = 0;
  }
}

void Files::ReadInputASCII(GraphicFiles_Vars& GF_Var, MidVars& MidVar){
  ifstream InputASCII("InputASCII.txt");

  if(InputASCII){
    for(int PN=0; PN<Const::MaxPlayerAmount; PN++){
      InputASCII >> MidVar.IntMidVar;
      GF_Var.Keys[PN][0] = (SDL_Keycode)MidVar.IntMidVar;

      InputASCII >> MidVar.IntMidVar;
      GF_Var.Keys[PN][1] = (SDL_Keycode)MidVar.IntMidVar;

      InputASCII >> MidVar.IntMidVar;
      GF_Var.Keys[PN][2] = (SDL_Keycode)MidVar.IntMidVar;

      InputASCII >> MidVar.IntMidVar;
      GF_Var.Keys[PN][3] = (SDL_Keycode)MidVar.IntMidVar;
    }
    MidVar.IntMidVar = 0;
  }
}

void Files::ReadSavedGame(Food& Food, InternalRandom& IRand, Map& Map, MidVars& MidVar, OptionsRandom& ORand, Snake& Snake){
  if(IRand.getLoadGame()){
    ifstream GameSave("SavedGame.txt");

    if(GameSave){
      GameSave >> MidVar.IntMidVar >> MidVar.IntMidVar2;
      Map.setMapSizeY(MidVar.IntMidVar);
      Map.setMapSizeX(MidVar.IntMidVar2);
      Map.setMapSize(Map.getMapSizeY(), Map.getMapSizeX());

      GameSave >> MidVar.IntMidVar >> MidVar.IntMidVar2;
      ORand.setSnakeAmount(MidVar.IntMidVar);
      ORand.setPlayerAmount(MidVar.IntMidVar2);
      Snake.initializeVectors(ORand.getSnakeAmount());

      GameSave >> MidVar.IntMidVar;
      ORand.setBorderTeleport(MidVar.IntMidVar);

      for(int Row=0; Row<Map.getMapSizeY(); Row++){
        for(int Column=0; Column<Map.getMapSizeX(); Column++){
          Map.setMapCollision(Row, Column, 0);
        }
      }

      GameSave >> MidVar.IntMidVar >> MidVar.IntMidVar2;
      Food.setFoodPosY(MidVar.IntMidVar);
      Food.setFoodPosX(MidVar.IntMidVar2);
      Map.setMapCollision(Food.getFoodPosY(), Food.getFoodPosX(), 3);

      GameSave >> MidVar.IntMidVar;
      Food.setMFCIA(MidVar.IntMidVar);
      if(Food.getMFCIA()){
        GameSave >> MidVar.IntMidVar >> MidVar.IntMidVar2;
        Food.setFoodPos2Y(MidVar.IntMidVar);
        Food.setFoodPos2X(MidVar.IntMidVar2);
        Food.setFoodRetract(0, 0, Food.getFoodPos2Y());
        Food.setFoodRetract(0, 1, Food.getFoodPos2X());
        Map.setMapCollision(Food.getFoodPos2Y(), Food.getFoodPos2X(), 3);

        GameSave >> MidVar.IntMidVar;
        Food.setFoodDirection(MidVar.IntMidVar);
      }

      for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
        GameSave >> MidVar.IntMidVar;
        Snake.setCISIA(SN, MidVar.IntMidVar);

        if(Snake.getCISIA(SN)){
          GameSave >> MidVar.IntMidVar >> MidVar.IntMidVar2;
          Snake.setInput(SN, MidVar.IntMidVar);
          Snake.setLastInput(SN, MidVar.IntMidVar2);

          GameSave >> MidVar.IntMidVar;
          IRand.setScore(SN, MidVar.IntMidVar);

          GameSave >> MidVar.IntMidVar >> MidVar.IntMidVar2;
          Snake.setTailLength(SN, MidVar.IntMidVar);
          Snake.setATL(SN, MidVar.IntMidVar2);
          Snake.setTailRetractSize(SN, (Snake.getTailLength(SN)+1));

          GameSave >> MidVar.IntMidVar >> MidVar.IntMidVar2;
          Snake.setSnakePosY(SN, MidVar.IntMidVar);
          Snake.setSnakePosX(SN, MidVar.IntMidVar2);

          for(int TL=0; TL<Snake.getATL(SN); TL++){
            GameSave >> MidVar.IntMidVar >> MidVar.IntMidVar2;
            Snake.setTailRetract(SN, TL, 0, MidVar.IntMidVar);
            Snake.setTailRetract(SN, TL, 1, MidVar.IntMidVar2);
            Map.setMapCollision(MidVar.IntMidVar, MidVar.IntMidVar2, 2);

            GameSave >> MidVar.IntMidVar >> MidVar.IntMidVar2;
            Snake.setSnakeTailConnect(SN, TL, MidVar.IntMidVar, MidVar.IntMidVar2);
          }
        }
      }

      for(int SN=(Const::MaxPlayerAmount-1); SN>=ORand.getSnakeAmount(); SN--){
        Snake.setCISIA(SN, false);
        Snake.setATL(SN, 0);
        Snake.setSnakePosY(SN, 0);
        Snake.setSnakePosX(SN, 0);
      }

      Snake.setATL(ORand.getSnakeAmount(), 0);
      for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
        Snake.setATL(ORand.getSnakeAmount(), Snake.getATL(ORand.getSnakeAmount())+Snake.getATL(SN));
      }

      MidVar.IntMidVar = 0;
      MidVar.IntMidVar2 = 0;
    }else{
      IRand.setLoadGame(false);
    }
  }
}

void Files::WriteOptionsFile(Map& Map, OptionsRandom& ORand, Snake& Snake){
  ofstream OptionsSave("OptionsSave.txt");

  if(OptionsSave.is_open()){
    OptionsSave << Map.getMapSizeX() << " " << Map.getMapSizeY() << endl;
    OptionsSave << ORand.getBorderTeleport() << endl;
    OptionsSave << ORand.getTailSpeed() << endl;

    OptionsSave.close();
  }
}

void Files::WriteHighScoresFile(InternalRandom& IRand, LoopControl& Loop, MidVars& MidVar, OptionsRandom& ORand){
  if(IRand.getExitStatus()!=1 && Loop.getGameReset()){
    for(int PN=0; PN<ORand.getPlayerAmount(); PN++){ //PN = PlayerNumber
      if(IRand.getScore(PN)>IRand.getHighScores(0)){

        MidVar.IntMidVar = IRand.getHighScores(2);
        IRand.setHighScores(3, MidVar.IntMidVar);
        MidVar.IntMidVar = IRand.getHighScores(1);
        IRand.setHighScores(2, MidVar.IntMidVar);
        MidVar.IntMidVar = IRand.getHighScores(0);
        IRand.setHighScores(1, MidVar.IntMidVar);
        MidVar.IntMidVar = 0;

        IRand.setHighScores(0, IRand.getScore(PN));
      }else if(IRand.getScore(PN)>IRand.getHighScores(1)){

        MidVar.IntMidVar = IRand.getHighScores(2);
        IRand.setHighScores(3, MidVar.IntMidVar);
        MidVar.IntMidVar = IRand.getHighScores(1);
        IRand.setHighScores(2, MidVar.IntMidVar);
        MidVar.IntMidVar = 0;

        IRand.setHighScores(1, IRand.getScore(PN));
      }else if(IRand.getScore(PN)>IRand.getHighScores(2)){

        MidVar.IntMidVar = IRand.getHighScores(2);
        IRand.setHighScores(3, MidVar.IntMidVar);
        MidVar.IntMidVar = 0;

        IRand.setHighScores(2, IRand.getScore(PN));
      }else if(IRand.getScore(PN)>IRand.getHighScores(3)){
        IRand.setHighScores(3, IRand.getScore(PN));
      }
    }
  }

  ofstream HighScores("HighScores.txt");

  if(HighScores.is_open()){
    HighScores << IRand.getHighScores(0) << endl;
    HighScores << IRand.getHighScores(1) << endl;
    HighScores << IRand.getHighScores(2) << endl;
    HighScores << IRand.getHighScores(3) << endl;

    HighScores.close();
  }
}

void Files::WriteInputASCII(GraphicFiles_Vars& GF_Var){
  ofstream InputASCII("InputASCII.txt");

  if(InputASCII.is_open()){
    for(int PN=0; PN<Const::MaxPlayerAmount; PN++){ //PN = PlayerNumber
      InputASCII << GF_Var.Keys[PN][0] << endl;
      InputASCII << GF_Var.Keys[PN][1] << endl;
      InputASCII << GF_Var.Keys[PN][2] << endl;
      InputASCII << GF_Var.Keys[PN][3] << endl;
    }

    InputASCII.close();
  }
}

//Can only run if the game was exited with esc.
void Files::WriteSavedGame(Food& Food, InternalRandom& IRand, LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake){
  if(Loop.getExitState()){
    if(IRand.getExitStatus()==1){ //If the game was exited under "Save and quit".
      ofstream SaveGame("SavedGame.txt");

      if(SaveGame.is_open()){
        SaveGame << Map.getMapSizeY() << " " << Map.getMapSizeX() << endl;

        SaveGame << ORand.getSnakeAmount() << " " << ORand.getPlayerAmount() << endl;

        SaveGame << ORand.getBorderTeleport() << endl;

        SaveGame << Food.getFoodPosY() << " " << Food.getFoodPosX() << endl;
        SaveGame << Food.getMFCIA() << endl;
        if(Food.getMFCIA()){
          SaveGame << Food.getFoodPos2Y() << " " << Food.getFoodPos2X() << endl;
          SaveGame << Food.getFoodDirection() << endl;
        }

        for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
          SaveGame << Snake.getCISIA(SN) << endl;

          if(Snake.getCISIA(SN)){
            SaveGame << Snake.getInput(SN) << " " << Snake.getLastInput(SN) << endl;

            SaveGame << IRand.getScore(SN) << endl;

            SaveGame << Snake.getTailLength(SN) << " " << Snake.getATL(SN) << endl;

            SaveGame << Snake.getSnakePosY(SN) << " " << Snake.getSnakePosX(SN) << endl;
            for(int TL=0; TL<Snake.getATL(SN); TL++){
              SaveGame << Snake.getTailRetract(SN, TL, 0) << " " << Snake.getTailRetract(SN, TL, 1) << endl;

              SaveGame << Snake.getSnakeTailConnect(SN, TL, 0) << " " << Snake.getSnakeTailConnect(SN, TL, 1) << endl;
            }
          }
        }

        SaveGame.close();
      }
    }
    for(int SN=0; SN<ORand.getSnakeAmount(); SN++){ //SN = SnakeNumber
      if(Snake.getCISIA(SN)){
        Snake.setSnakeDelete(SN, 1);
        Snake.setCISIA(SN, false);
      }
    }
  }
}

#include "GameOver.h"

void GameOver::GameLoopExit(InternalRandom& IRand, LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake){
  if(Snake.getATL(ORand.getSnakeAmount()) >= ((Map.getMapSizeY()-2)*(Map.getMapSizeX()-2))){ //If the sum of all the snake lengths is equal to the map area
    Loop.setExitState(true);
    IRand.setExitStatus(2);
  }else if(Snake.getATL(ORand.getSnakeAmount())==0){ //If all the snakes have died
    if(Loop.getExitState()){
      IRand.setExitStatus(1);
    }else{
      IRand.setExitStatus(3);
      Loop.setExitState(true);
    }
  }
}

void GameOver::GameOverMessage(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                               LoopControl& Loop, Map& Map, OptionsRandom& ORand){

  if(Loop.getGameReset()){

    GMI_Var.MenuChange(GF_Var, 13, ORand.getSnakeAmount()+6);

    GMI_Var.setNumberOfButtons(ORand.getSnakeAmount()+2, 1);

    if(IRand.getExitStatus()==1){
      GMI_Var.setText(GF_Var, 0, "You have exited the game");
    }else if(IRand.getExitStatus()==2){
      GMI_Var.setText(GF_Var, 0, "You filled up the map");
    }else if(IRand.getExitStatus()==3){
      GMI_Var.setText(GF_Var, 0, "You ran into something");
    }else if(IRand.getExitStatus()==4){
      GMI_Var.setText(GF_Var, 0, "Input corrupt");
    }
    GMI_Var.setText(GF_Var, 1, "Main Menu");

    GMI_Var.setButtonPos(0, 1, 1, GF_Var.TBSS(GF_Var.Text[0]));
    for(int SN=1; SN<=ORand.getSnakeAmount(); SN++){
      GMI_Var.setButtonPos(SN, 1, SN+2, 4);
    }
    GMI_Var.setButtonPos(ORand.getSnakeAmount()+1, 1, ORand.getSnakeAmount()+4, 5);

    GMI_Var.setButtonInfo(0, 0, 0, 0);
    for(int SN=1; SN<=ORand.getSnakeAmount(); SN++){
      GMI_Var.setButtonInfo(SN, 0, 0, SN+1);
    }
    GMI_Var.setButtonInfo(ORand.getSnakeAmount()+1, 1, 1, 1);

    GMI_Var.makeButton(GF_Var, 0, GF_Var.Text[0]);
    for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
      GMI_Var.makeButton(GF_Var, (SN+1), GF_Var.Scores[SN]);
    }
    GMI_Var.makeButton(GF_Var, ORand.getSnakeAmount()+1, GF_Var.Text[1], true);

    SDL_UpdateWindowSurface(GF_Var.Window);

    do{
      while(SDL_PollEvent(&GF_Var.event)){

        GMI_Var.getEventType(GF_Var, 0);

        if(GMI_Var.getInputType()!=0){

          if(GMI_Var.getInputType()==1 || GMI_Var.getInputType()==2){
            Loop.setInputLoopBreak(true);
          }
        }else if(GF_Var.event.type == SDL_QUIT){
          Loop.setInputLoopBreak(true);
          Loop.setGameReset(false);
        }
      }
    }while(!Loop.getInputLoopBreak());
    Loop.setInputLoopBreak(false);

    SDL_FreeSurface(GF_Var.Text[0]);
    for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
      SDL_FreeSurface(GF_Var.Scores[SN]);
    }
    SDL_FreeSurface(GF_Var.Text[1]);
  }
}

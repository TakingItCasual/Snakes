#include "Input.h"

void Input::GetInput(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                     LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake, Timer& Timer){
  do{
    if(Timer.CheckTimer(ORand.getTailSpeed())){
      Loop.setInputLoopBreak(true);
    }
    while(SDL_PollEvent(&GF_Var.event)){
      if(GF_Var.event.type == SDL_KEYDOWN){
        for(int PN=0; PN<ORand.getSnakeAmount(); PN++){
          for(int Direction=0; Direction<4; Direction++){

            if(GF_Var.event.key.keysym.sym == GF_Var.Keys[PN][Direction]){
               Snake.setInput(PN, Direction+1);

            }else if(ORand.getSnakeAmount()==1){

              if(GF_Var.event.key.keysym.sym == GF_Var.Keys[1][Direction]){
                Snake.setInput(0, Direction+1);
              }
            }
          }
        }
        if(GF_Var.event.key.keysym.sym == SDLK_ESCAPE){
          GameEsc(GMI_Var, GF_Var, IRand, Loop, Map, ORand);
        }else if(GF_Var.event.key.keysym.sym == SDLK_p){
          do{
            while(SDL_PollEvent(&GF_Var.event)){
              if(GF_Var.event.type == SDL_KEYDOWN){
                if(GF_Var.event.key.keysym.sym == SDLK_p){
                  Loop.setInputLoopBreak(true);
                }
              }else if(GF_Var.event.type == SDL_QUIT){
                Loop.setGameReset(false);
              }
            }
          }while(!Loop.getInputLoopBreak());
          Loop.setInputLoopBreak(false);
        }
      }else if(GF_Var.event.type == SDL_QUIT){
        Loop.setGameReset(false);
      }else if(GF_Var.event.type == SDL_WINDOWEVENT){
        if(GF_Var.event.window.event == SDL_WINDOWEVENT_FOCUS_LOST){
            do{
              while(SDL_PollEvent(&GF_Var.event)){
                if(GF_Var.event.type == SDL_KEYDOWN){
                  if(GF_Var.event.key.keysym.sym == SDLK_p){
                    Loop.setInputLoopBreak(true);
                  }
                }else if(GF_Var.event.type == SDL_QUIT){
                  Loop.setGameReset(false);
                }
              }
            }while(!Loop.getInputLoopBreak());
            Loop.setInputLoopBreak(false);
        }
      }
    }
  }while(!Loop.getInputLoopBreak());
  Loop.setInputLoopBreak(false);

  Timer.StartTimer();

  for(int PN=0; PN<ORand.getPlayerAmount(); PN++){ //PN = PlayerNumber
    if(Snake.getCISIA(PN)){
      if(Snake.getInput(PN)==1 || Snake.getInput(PN)==3 ||
         Snake.getInput(PN)==2 || Snake.getInput(PN)==4){
        if(Snake.getInput(PN)==1 && Snake.getLastInput(PN)==2){
          Snake.setInput(PN, 2);
        }else if(Snake.getInput(PN)==2 && Snake.getLastInput(PN)==1){
          Snake.setInput(PN, 1);
        }else if(Snake.getInput(PN)==3 && Snake.getLastInput(PN)==4){
          Snake.setInput(PN, 4);
        }else if(Snake.getInput(PN)==4 && Snake.getLastInput(PN)==3){
          Snake.setInput(PN, 3);
        }
      }else{
        Snake.setInput(PN, Snake.getLastInput(PN));
      }
      Snake.setLastInput(PN, Snake.getInput(PN));
    }
  }
}

void Input::GameEsc(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand, LoopControl& Loop, Map& Map, OptionsRandom& ORand){
  GMI_Var.setMenuSelect(1);

  GMI_Var.MenuChange(GF_Var, 12, 7);

  GMI_Var.setNumberOfButtons(4, 3);

  GMI_Var.setText(GF_Var, 0, "You have pressed esc");
  GMI_Var.setText(GF_Var, 1, "Continue game");
  GMI_Var.setText(GF_Var, 2, "Save and quit");
  GMI_Var.setText(GF_Var, 3, "Quit without saving");

  GMI_Var.setButtonPos(0, 1, 1, 10);
  GMI_Var.setButtonPos(1, 1, 3, 7);
  GMI_Var.setButtonPos(2, 1, 4, 7);
  GMI_Var.setButtonPos(3, 1, 5, 9);

  GMI_Var.setButtonInfo(0, 0, 0, 0);
  GMI_Var.setButtonInfo(1, 1, 1, 1);
  GMI_Var.setButtonInfo(2, 2, 1, 2);
  GMI_Var.setButtonInfo(3, 3, 1, 3);

  do{

    if(GMI_Var.getUpdateScreen()){
      GF_Var.apply_surface(0, 0, GF_Var.BackGround[1], GF_Var.screen);

      GMI_Var.UpdateButtons(GF_Var);

      SDL_UpdateWindowSurface(GF_Var.Window);

      GMI_Var.setUpdateScreen(false);
    }

    while(GMI_Var.InputLoop(GF_Var)){

      GMI_Var.getEventType(GF_Var, 1);

      if(GMI_Var.getInputType()!=0){

        GMI_Var.setUpdateScreen(true);

        if(GMI_Var.getInputType()==1 || GMI_Var.getInputType()==2){

          if(GMI_Var.getMenuSelect()==1){
            GMI_Var.MenuChange(GF_Var, Map.getMapSizeX(), Map.getMapSizeY()+1);
            for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
              GMI_Var.setButtonPos(SN, SN*4, Map.getMapSizeY(), 4);
            }
          }else if(GMI_Var.getMenuSelect()==2){
            IRand.setExitStatus(1);
            Loop.setExitState(true);
          }else if(GMI_Var.getMenuSelect()==3){
            IRand.setExitStatus(3);
            Loop.setExitState(true);
          }
          Loop.setInputLoopBreak(true);
        }
      }else if(GF_Var.event.type == SDL_QUIT){
        Loop.setGameReset(false);
      }
    }

  }while(!Loop.getInputLoopBreak());
  Loop.setInputLoopBreak(false);
  GMI_Var.WipeTexts(GF_Var);
}


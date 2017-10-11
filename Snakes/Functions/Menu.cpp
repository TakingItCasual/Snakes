#include "Menu.h"

void Menu::MainMenu(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                    LoopControl& Loop, Map& Map, MidVars& MidVar, OptionsRandom& ORand){

  GMI_Var.setMenuSelect(1);
  Loop.setMenuState(0);
  IRand.setLoadGame(false);
  do{
    //Main menu, where the player can access any of the submenus
    MainMainMenu(GMI_Var, GF_Var, Loop);
    if(Loop.getMenuState()==2){
      //New Game, where the player can start a new game
      NewGame(GMI_Var, GF_Var, IRand, Loop, MidVar, ORand);
    }else if(Loop.getMenuState()==3){
      //Load Game, where the player can load a saved game
      LoadGame(GMI_Var, GF_Var, IRand, Loop);
    }else if(Loop.getMenuState()==4){
      //High Scores, where the player can view his/her high scores
      HighScores(GMI_Var, GF_Var, IRand, Loop, MidVar);
    }else if(Loop.getMenuState()==5){
      //Help, basic control help/info
      Help(GMI_Var, GF_Var, Loop);
    }else if(Loop.getMenuState()==6){
      //Options, where the player can change options altering the game
      Options(GMI_Var, GF_Var, IRand, Loop, Map, MidVar, ORand);
    }else if(Loop.getMenuState()==7){
      //Quit, with confirmation request
      Quit(GMI_Var, GF_Var, Loop);
    }
  }while(Loop.getMenuState() != -1);
}

void Menu::MainMainMenu(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, LoopControl& Loop){

  GMI_Var.MenuChange(GF_Var, 17, 12);

  GMI_Var.setNumberOfButtons(6, 6);

  GMI_Var.setText(GF_Var, 0, "New Game");
  GMI_Var.setText(GF_Var, 1, "Load Game");
  GMI_Var.setText(GF_Var, 2, "High Scores");
  GMI_Var.setText(GF_Var, 3, "Help");
  GMI_Var.setText(GF_Var, 4, "Options");
  GMI_Var.setText(GF_Var, 5, "Quit");

  GMI_Var.setButtonPos(0, 1, 5, 4);
  GMI_Var.setButtonPos(1, 1, 6, 5);
  GMI_Var.setButtonPos(2, 1, 7, 6);
  GMI_Var.setButtonPos(3, 1, 8, 3);
  GMI_Var.setButtonPos(4, 1, 9, 4);
  GMI_Var.setButtonPos(5, 1, 10, 3);

  GMI_Var.setButtonInfo(0, 1, 1, 0);
  GMI_Var.setButtonInfo(1, 2, 1, 1);
  GMI_Var.setButtonInfo(2, 3, 1, 2);
  GMI_Var.setButtonInfo(3, 4, 1, 3);
  GMI_Var.setButtonInfo(4, 5, 1, 4);
  GMI_Var.setButtonInfo(5, 6, 1, 5);

  do{

    if(GMI_Var.getUpdateScreen()){

      GF_Var.apply_surface(0, 0, GF_Var.BackGround[1], GF_Var.screen);

      GF_Var.apply_surface(1, 1, GF_Var.Title, GF_Var.screen);

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
            Loop.setMenuState(2);
          }else if(GMI_Var.getMenuSelect()==2){
            Loop.setMenuState(3);
          }else if(GMI_Var.getMenuSelect()==3){
            Loop.setMenuState(4);
          }else if(GMI_Var.getMenuSelect()==4){
            Loop.setMenuState(5);
          }else if(GMI_Var.getMenuSelect()==5){
            Loop.setMenuState(6);
          }else if(GMI_Var.getMenuSelect()==6){
            Loop.setMenuState(7);
          }
          GMI_Var.setMenuSelect(1);
          Loop.setExitState(true);
        }
      }else if(GF_Var.event.type == SDL_QUIT){
        Loop.setGameReset(false);
      }
    }

  }while(!Loop.getExitState());
  Loop.setExitState(false);
  GMI_Var.WipeTexts(GF_Var);
}

void Menu::NewGame(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                   LoopControl& Loop, MidVars& MidVar, OptionsRandom& ORand){

  GMI_Var.setMenuSelect(1);

  GMI_Var.MenuChange(GF_Var, 14, 10);

  GMI_Var.setNumberOfButtons(10, 4, 8);

  GMI_Var.setText(GF_Var, 0, "Back to main menu");
  GMI_Var.setText(GF_Var, 1, "Play");

  MidVar.StringMidVar = "Player Amount: "+GF_Var.IntToString(ORand.getPlayerAmount());
  GMI_Var.setText(GF_Var, 2, MidVar.StringMidVar);

  MidVar.StringMidVar = "NPC Amount: "+GF_Var.IntToString(ORand.getSnakeAmount()-ORand.getPlayerAmount());
  GMI_Var.setText(GF_Var, 3, MidVar.StringMidVar);
  MidVar.StringMidVar = "";

  GMI_Var.setText(GF_Var, 4, "<");
  GMI_Var.setText(GF_Var, 5, ">");
  GMI_Var.setText(GF_Var, 6, "Please increase map size");
  GMI_Var.setText(GF_Var, 7, "to allow for more players");

  GMI_Var.setButtonPos(0, 1, 1, 8); //Back to main menu
  GMI_Var.setButtonPos(1, 1, 3, 3); //Play
  GMI_Var.setButtonPos(2, 1, 4, 1); //< (left arrow key)
  GMI_Var.setButtonPos(3, 2, 4, 1); //> (right arrow key)
  GMI_Var.setButtonPos(4, 3, 4, 8); //Player amount + value
  GMI_Var.setButtonPos(5, 1, 5, 1); //< (left arrow key)
  GMI_Var.setButtonPos(6, 2, 5, 1); //> (right arrow key)
  GMI_Var.setButtonPos(7, 3, 5, 7); //NPC amount + value
  GMI_Var.setButtonPos(8, 1, 7, 11); //Please increase map size
  GMI_Var.setButtonPos(9, 1, 8, 12); //to allow for more players

  GMI_Var.setButtonInfo(0, 1, 1, 0);
  GMI_Var.setButtonInfo(1, 2, 1, 1);
  GMI_Var.setButtonInfo(2, 3, 2, 4);
  GMI_Var.setButtonInfo(3, 3, 3, 5);
  GMI_Var.setButtonInfo(4, 3, 4, 2);
  GMI_Var.setButtonInfo(5, 4, 2, 4);
  GMI_Var.setButtonInfo(6, 4, 3, 5);
  GMI_Var.setButtonInfo(7, 4, 4, 3);
  GMI_Var.setButtonInfo(8, 0, 5, 6); //5 is an explicit "don't output me" to UpdateButtons
  GMI_Var.setButtonInfo(9, 0, 5, 7); //5 is an explicit "don't output me" to UpdateButtons

  do{

    if(GMI_Var.getUpdateScreen()){

      GF_Var.apply_surface(0, 0, GF_Var.BackGround[1], GF_Var.screen);

      GMI_Var.UpdateButtons(GF_Var);

      if(ORand.getSnakeAmount()==IRand.getMSABOMS() && IRand.getMSABOMS()<Const::MaxPlayerAmount){
        GMI_Var.makeButton(GF_Var, 8, GF_Var.Text[GMI_Var.getButtonTextLink(8)]);
        GMI_Var.makeButton(GF_Var, 9, GF_Var.Text[GMI_Var.getButtonTextLink(9)]);
      } //Since these 2 buttons where given the secondary ButtonInfo value of 5, UpdateButtons didn't affect them

      SDL_UpdateWindowSurface(GF_Var.Window);

      GMI_Var.setUpdateScreen(false);
    }

    while(GMI_Var.InputLoop(GF_Var)){

      GMI_Var.getEventType(GF_Var, 2);

      if(GMI_Var.getInputType()!=0){

        GMI_Var.setUpdateScreen(true);

        if(GMI_Var.getInputType()==1 || GMI_Var.getInputType()==2 ||
           GMI_Var.getInputType()==3 || GMI_Var.getInputType()==4){

          if(GMI_Var.getMenuSelect()==1 || GMI_Var.getMenuSelect()==2){

            if(GMI_Var.getInputType()==1 || GMI_Var.getInputType()==2){

              if(GMI_Var.getMenuSelect()==1){
                Loop.setMenuState(0);
                GMI_Var.setMenuSelect(1);
                Loop.setExitState(true);
              }else if(GMI_Var.getMenuSelect()==2){
                Loop.setMenuState(-1);
                Loop.setExitState(true);
              }
            }
          }else if(GMI_Var.getMenuSelect()==3){
            if(GMI_Var.getInputType()!=1){

              if(GMI_Var.getIsArrowLeft()){

                if(ORand.getPlayerAmount()>1){
                  ORand.setPlayerAmount(ORand.getPlayerAmount()-1);
                  if(ORand.getPlayerAmount()+MidVar.IntMidVar2>=IRand.getMSABOMS()){
                    ORand.setSnakeAmount(IRand.getMSABOMS());
                  }else{
                    ORand.setSnakeAmount(ORand.getSnakeAmount()-1);
                  }
                }else if(ORand.getPlayerAmount()==1){
                  if(ORand.getSnakeAmount()>1 && MidVar.IntMidVar2<IRand.getMSABOMS()){
                    ORand.setSnakeAmount(ORand.getSnakeAmount()-1);
                  }
                  ORand.setPlayerAmount(0);
                }else{
                  ORand.setPlayerAmount(IRand.getMSABOMS());
                  ORand.setSnakeAmount(IRand.getMSABOMS());
                }
                MidVar.IntMidVar = ORand.getPlayerAmount();

              }else if(!GMI_Var.getIsArrowLeft()){

                if(ORand.getPlayerAmount()<IRand.getMSABOMS()){
                  if(ORand.getPlayerAmount()==0 && MidVar.IntMidVar2<IRand.getMSABOMS()){
                    ORand.setSnakeAmount(MidVar.IntMidVar2+1);
                  }else if(ORand.getSnakeAmount()<IRand.getMSABOMS()){
                    ORand.setSnakeAmount(ORand.getSnakeAmount()+1);
                  }
                  ORand.setPlayerAmount(ORand.getPlayerAmount()+1);
                }else{
                  ORand.setPlayerAmount(0);
                  if(MidVar.IntMidVar2>0){
                    ORand.setSnakeAmount(MidVar.IntMidVar2);
                  }else{
                    ORand.setSnakeAmount(1);
                  }
                }
                MidVar.IntMidVar = ORand.getPlayerAmount();

              }

              MidVar.StringMidVar = "Player Amount: "+GF_Var.IntToString(ORand.getPlayerAmount());
              GMI_Var.setText(GF_Var, 2, MidVar.StringMidVar);

              MidVar.StringMidVar = "NPC Amount: "+GF_Var.IntToString(ORand.getSnakeAmount()-ORand.getPlayerAmount());
              GMI_Var.setText(GF_Var, 3, MidVar.StringMidVar);
              MidVar.StringMidVar = "";
            }
          }else if(GMI_Var.getMenuSelect()==4){
            if(GMI_Var.getInputType()!=1){

              if(GMI_Var.getIsArrowLeft()){

                if(ORand.getSnakeAmount()>1 && ORand.getSnakeAmount()>ORand.getPlayerAmount()){
                  if(MidVar.IntMidVar>ORand.getPlayerAmount()){
                    ORand.setPlayerAmount(ORand.getPlayerAmount()+1);
                  }else{
                    ORand.setSnakeAmount(ORand.getSnakeAmount()-1);
                  }
                }else{
                  if(ORand.getPlayerAmount()==0){
                    ORand.setSnakeAmount(1);
                    ORand.setPlayerAmount(1);
                  }else{
                    ORand.setSnakeAmount(IRand.getMSABOMS());
                    ORand.setPlayerAmount(0);
                  }
                }
                MidVar.IntMidVar2 = ORand.getSnakeAmount()-ORand.getPlayerAmount();

              }else if(!GMI_Var.getIsArrowLeft()){

                if(ORand.getSnakeAmount()<IRand.getMSABOMS()){
                  if(MidVar.IntMidVar==0 && ORand.getPlayerAmount()==1){
                    ORand.setSnakeAmount(1);
                    ORand.setPlayerAmount(0);
                  }else{
                    ORand.setSnakeAmount(ORand.getSnakeAmount()+1);
                  }
                }else if(ORand.getPlayerAmount()>0){
                  ORand.setPlayerAmount(ORand.getPlayerAmount()-1);
                }else{
                  if(MidVar.IntMidVar>0){
                    ORand.setSnakeAmount(MidVar.IntMidVar);
                    ORand.setPlayerAmount(MidVar.IntMidVar);
                  }else{
                    ORand.setSnakeAmount(1);
                    ORand.setPlayerAmount(1);
                  }
                }
                MidVar.IntMidVar2 = ORand.getSnakeAmount()-ORand.getPlayerAmount();

              }

              MidVar.StringMidVar = "Player Amount: "+GF_Var.IntToString(ORand.getPlayerAmount());
              GMI_Var.setText(GF_Var, 2, MidVar.StringMidVar);

              MidVar.StringMidVar = "NPC Amount: "+GF_Var.IntToString(ORand.getSnakeAmount()-ORand.getPlayerAmount());
              GMI_Var.setText(GF_Var, 3, MidVar.StringMidVar);
              MidVar.StringMidVar = "";
            }
          }
        }
      }else if(GF_Var.event.type == SDL_QUIT){
        Loop.setGameReset(false);
      }
    }

  }while(!Loop.getExitState());
  Loop.setExitState(false);
  GMI_Var.WipeTexts(GF_Var);

  MidVar.IntMidVar = 0;
  MidVar.IntMidVar2 = 0;
}

void Menu::LoadGame(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand, LoopControl& Loop){

  GMI_Var.setMenuSelect(1);

  GMI_Var.MenuChange(GF_Var, 10, 5);

  GMI_Var.setNumberOfButtons(2, 2);

  GMI_Var.setText(GF_Var, 0, "Back to main menu");
  GMI_Var.setText(GF_Var, 1, "Load game");

  GMI_Var.setButtonPos(0, 1, 1, 8);
  GMI_Var.setButtonPos(1, 1, 3, 5);

  GMI_Var.setButtonInfo(0, 1, 1, 0);
  GMI_Var.setButtonInfo(1, 2, 1, 1);

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
            Loop.setMenuState(0);
            GMI_Var.setMenuSelect(2);
          }else if(GMI_Var.getMenuSelect()==2){
            Loop.setMenuState(-1);
            IRand.setLoadGame(true);
          }
          Loop.setExitState(true);
        }
      }else if(GF_Var.event.type == SDL_QUIT){
        Loop.setGameReset(false);
      }
    }

  }while(!Loop.getExitState());
  Loop.setExitState(false);
  GMI_Var.WipeTexts(GF_Var);
}

void Menu::HighScores(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand, LoopControl& Loop, MidVars& MidVar){

  GMI_Var.setMenuSelect(1);

  GMI_Var.MenuChange(GF_Var, 10, 10);

  GMI_Var.setNumberOfButtons(7, 2);

  GMI_Var.setText(GF_Var, 0, "Back to main menu");
  GMI_Var.setText(GF_Var, 1, "Reset");
  GMI_Var.setText(GF_Var, 2, "High Scores");

  MidVar.StringMidVar = "1st: "+GF_Var.IntToString(IRand.getHighScores(0));
  GMI_Var.setText(GF_Var, 3, MidVar.StringMidVar);

  MidVar.StringMidVar = "2nd: "+GF_Var.IntToString(IRand.getHighScores(1));
  GMI_Var.setText(GF_Var, 4, MidVar.StringMidVar);

  MidVar.StringMidVar = "3rd: "+GF_Var.IntToString(IRand.getHighScores(2));
  GMI_Var.setText(GF_Var, 5, MidVar.StringMidVar);

  MidVar.StringMidVar = "4th: "+GF_Var.IntToString(IRand.getHighScores(3));
  GMI_Var.setText(GF_Var, 6, MidVar.StringMidVar);
  MidVar.StringMidVar = "";

  GMI_Var.setButtonPos(0, 1, 1, 8);
  GMI_Var.setButtonPos(1, 1, 2, 3);
  GMI_Var.setButtonPos(2, 1, 4, 6);
  GMI_Var.setButtonPos(3, 1, 5, GF_Var.TBSS(GF_Var.Text[3]));
  GMI_Var.setButtonPos(4, 1, 6, GF_Var.TBSS(GF_Var.Text[4]));
  GMI_Var.setButtonPos(5, 1, 7, GF_Var.TBSS(GF_Var.Text[5]));
  GMI_Var.setButtonPos(6, 1, 8, GF_Var.TBSS(GF_Var.Text[6]));

  GMI_Var.setButtonInfo(0, 1, 1, 0);
  GMI_Var.setButtonInfo(1, 2, 1, 1);
  GMI_Var.setButtonInfo(2, 0, 0, 2);
  GMI_Var.setButtonInfo(3, 0, 0, 3);
  GMI_Var.setButtonInfo(4, 0, 0, 4);
  GMI_Var.setButtonInfo(5, 0, 0, 5);
  GMI_Var.setButtonInfo(6, 0, 0, 6);

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
            Loop.setExitState(true);
            Loop.setMenuState(0);
            GMI_Var.setMenuSelect(3);
          }else if(GMI_Var.getMenuSelect()==2){
            IRand.setHighScores(0, 0);
            IRand.setHighScores(1, 0);
            IRand.setHighScores(2, 0);
            IRand.setHighScores(3, 0);

            GMI_Var.setText(GF_Var, 3, "1st: 0");
            GMI_Var.setText(GF_Var, 4, "2nd: 0");
            GMI_Var.setText(GF_Var, 5, "3rd: 0");
            GMI_Var.setText(GF_Var, 6, "4th: 0");

            GMI_Var.setButtonPos(3, 1, 5, 3);
            GMI_Var.setButtonPos(4, 1, 6, 3);
            GMI_Var.setButtonPos(5, 1, 7, 3);
            GMI_Var.setButtonPos(6, 1, 8, 3);
          }
        }
      }else if(GF_Var.event.type == SDL_QUIT){
        Loop.setGameReset(false);
      }
    }

  }while(!Loop.getExitState());
  Loop.setExitState(false);
  GMI_Var.WipeTexts(GF_Var);
}

void Menu::Help(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, LoopControl& Loop){

  GMI_Var.setMenuSelect(1);

  GMI_Var.MenuChange(GF_Var, 25, 7);

  GMI_Var.setNumberOfButtons(4, 1);

  GMI_Var.setText(GF_Var, 0, "Back to main menu");
  GMI_Var.setText(GF_Var, 1, "Ingame controls:");
  GMI_Var.setText(GF_Var, 2, "w,a,s,d or arrow controls for movement (modifiable),");
  GMI_Var.setText(GF_Var, 3, "p to pause and esc to exit.");

  GMI_Var.setButtonPos(0, 1, 1, 8);
  GMI_Var.setButtonPos(1, 1, 3, 8);
  GMI_Var.setButtonPos(2, 1, 4, 23);
  GMI_Var.setButtonPos(3, 1, 5, 12);

  GMI_Var.setButtonInfo(0, 1, 1, 0);
  GMI_Var.setButtonInfo(1, 0, 0, 1);
  GMI_Var.setButtonInfo(2, 0, 0, 2);
  GMI_Var.setButtonInfo(3, 0, 0, 3);

  GMI_Var.UpdateButtons(GF_Var);

  SDL_UpdateWindowSurface(GF_Var.Window);

  do{
    while(GMI_Var.InputLoop(GF_Var)){

      GMI_Var.getEventType(GF_Var, 0);

      if(GMI_Var.getInputType()!=0){

        if(GMI_Var.getInputType()==1 || GMI_Var.getInputType()==2){

          Loop.setExitState(true);
          Loop.setMenuState(0);
          GMI_Var.setMenuSelect(4);
        }
      }else if(GF_Var.event.type == SDL_QUIT){
        Loop.setGameReset(false);
      }
    }
  }while(!Loop.getExitState());
  Loop.setExitState(false);
  GMI_Var.WipeTexts(GF_Var);
}

void Menu::Options(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                   LoopControl& Loop, Map& Map, MidVars& MidVar, OptionsRandom& ORand){

  GMI_Var.setMenuSelect(1);

  do{

    GMI_Var.MenuChange(GF_Var, 15, 12);

    GMI_Var.setNumberOfButtons(10, 7);

    GMI_Var.setText(GF_Var, 0, "Back to main menu");
    GMI_Var.setText(GF_Var, 1, "Change map size");
    GMI_Var.setText(GF_Var, 2, "Change snake colors");
    GMI_Var.setText(GF_Var, 3, "Turn solid walls:");
    GMI_Var.setText(GF_Var, 4, "Adjust snake speed");
    GMI_Var.setText(GF_Var, 5, "Controls");
    GMI_Var.setText(GF_Var, 6, "Restore defaults");

    MidVar.StringMidVar = "X:"+GF_Var.IntToString(Map.getMapSizeX()-2)+" Y:"+GF_Var.IntToString(Map.getMapSizeY()-2);
    GMI_Var.setText(GF_Var, 7, MidVar.StringMidVar);

    if(ORand.getBorderTeleport()){
      GMI_Var.setText(GF_Var, 8, "Off");
    }else{
      GMI_Var.setText(GF_Var, 8, "On");
    }

    MidVar.StringMidVar = GF_Var.IntToString(ORand.getTailSpeed())+"ms/m";
    GMI_Var.setText(GF_Var, 9, MidVar.StringMidVar);
    MidVar.StringMidVar = "";

    GMI_Var.setButtonPos(0, 1, 1, 8); //Back to main menu
    GMI_Var.setButtonPos(1, 1, 3, 7); //Change map size
    GMI_Var.setButtonPos(2, 8, 3, GF_Var.TBSS(GF_Var.Text[7])); //Map size values
    GMI_Var.setButtonPos(3, 1, 4, 9); //Change snake colors
    GMI_Var.setButtonPos(4, 1, 5, 8); //Turn walls solid
    GMI_Var.setButtonPos(5, 9, 5, 2); //Wall solidity value
    GMI_Var.setButtonPos(6, 1, 6, 9); //Adjust snake speed
    GMI_Var.setButtonPos(7, 10, 6, GF_Var.TBSS(GF_Var.Text[9])); //Snake speed value
    GMI_Var.setButtonPos(8, 1, 8, 4); //Controls
    GMI_Var.setButtonPos(9, 1, 10, 8); //Restore defaults

    GMI_Var.setButtonInfo(0, 1, 1, 0);
    GMI_Var.setButtonInfo(1, 2, 1, 1);
    GMI_Var.setButtonInfo(2, 0, 0, 7);
    GMI_Var.setButtonInfo(3, 3, 1, 2);
    GMI_Var.setButtonInfo(4, 4, 1, 3);
    GMI_Var.setButtonInfo(5, 0, 0, 8);
    GMI_Var.setButtonInfo(6, 5, 1, 4);
    GMI_Var.setButtonInfo(7, 0, 0, 9);
    GMI_Var.setButtonInfo(8, 6, 1, 5);
    GMI_Var.setButtonInfo(9, 7, 1, 6);

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
              Loop.setExitState(true);
              Loop.setMenuState(0);
              GMI_Var.setMenuSelect(5);
            }else if(GMI_Var.getMenuSelect()==2){
              Loop.setExitState(true);
              GMI_Var.setMenuSelect(8);
            }else if(GMI_Var.getMenuSelect()==4){

              if(ORand.getBorderTeleport()){
                ORand.setBorderTeleport(false);
                GMI_Var.setText(GF_Var, 8, "On");
              }else{
                ORand.setBorderTeleport(true);
                GMI_Var.setText(GF_Var, 8, "Off");
              }
              GMI_Var.setUpdateScreen(true);
            }else if(GMI_Var.getMenuSelect()==5){

              if(ORand.getTailSpeed()<=IRand.getTailSpeedNum(0)){
                ORand.setTailSpeed(IRand.getTailSpeedNum(2));
              }else if(ORand.getTailSpeed()>IRand.getTailSpeedNum(0) && ORand.getTailSpeed()<IRand.getTailSpeedNum(2)){
                ORand.setTailSpeed(IRand.getTailSpeedNum(0));
              }else if(ORand.getTailSpeed()>=IRand.getTailSpeedNum(2)){
                ORand.setTailSpeed(IRand.getTailSpeedNum(1));
              }

              MidVar.StringMidVar = GF_Var.IntToString(ORand.getTailSpeed())+"ms/m";
              GMI_Var.setText(GF_Var, 9, MidVar.StringMidVar);
              MidVar.StringMidVar = "";
              GMI_Var.setButtonPos(7, -1, -1, GF_Var.TBSS(GF_Var.Text[9]));

              GMI_Var.setUpdateScreen(true);
            }else if(GMI_Var.getMenuSelect()==6){
              Loop.setExitState(true);
              GMI_Var.setMenuSelect(9);
            }
          }
        }else if(GF_Var.event.type == SDL_QUIT){
          Loop.setGameReset(false);
        }
      }

    }while(!Loop.getExitState());
    Loop.setExitState(false);

    if(GMI_Var.getMenuSelect()==8){
      GMI_Var.setMenuSelect(1);

      GMI_Var.MenuChange(GF_Var, 12, 8);

      GMI_Var.setNumberOfButtons(10, 3, 8);

      GMI_Var.setText(GF_Var, 0, "Back");
      GMI_Var.setText(GF_Var, 1, "Map size X");
      GMI_Var.setText(GF_Var, 2, "Map size Y");

      MidVar.StringMidVar = "Max player amount: "+GF_Var.IntToString(IRand.getMSABOMS());
      GMI_Var.setText(GF_Var, 3, MidVar.StringMidVar);

      MidVar.StringMidVar = GF_Var.IntToString(Map.getMapSizeX()-2);
      GMI_Var.setText(GF_Var, 4, MidVar.StringMidVar);
      MidVar.StringMidVar = GF_Var.IntToString(Map.getMapSizeY()-2);
      GMI_Var.setText(GF_Var, 5, MidVar.StringMidVar);
      MidVar.StringMidVar = "";

      GMI_Var.setText(GF_Var, 6, "<");
      GMI_Var.setText(GF_Var, 7, ">");

      GMI_Var.setButtonPos(0, 1, 1, 3); //Back
      GMI_Var.setButtonPos(1, 1, 3, 1); //< (left arrow key)
      GMI_Var.setButtonPos(2, 2, 3, 1); //> (right arrow key)
      GMI_Var.setButtonPos(3, 3, 3, 5); //Map Size X
      GMI_Var.setButtonPos(4, 8, 3, GF_Var.TBSS(GF_Var.Text[4])); //Map size x value
      GMI_Var.setButtonPos(5, 1, 4, 1); //< (left arrow key)
      GMI_Var.setButtonPos(6, 2, 4, 1); //> (right arrow key)
      GMI_Var.setButtonPos(7, 3, 4, 5); //Map Size Y
      GMI_Var.setButtonPos(8, 8, 4, GF_Var.TBSS(GF_Var.Text[5])); //Map Size y value
      GMI_Var.setButtonPos(9, 1, 6, GF_Var.TBSS(GF_Var.Text[3])); //Max player amount + value

      GMI_Var.setButtonInfo(0, 1, 1, 0);
      GMI_Var.setButtonInfo(1, 2, 2, 6);
      GMI_Var.setButtonInfo(2, 2, 3, 7);
      GMI_Var.setButtonInfo(3, 2, 4, 1);
      GMI_Var.setButtonInfo(4, 0, 4, 4);
      GMI_Var.setButtonInfo(5, 3, 2, 6);
      GMI_Var.setButtonInfo(6, 3, 3, 7);
      GMI_Var.setButtonInfo(7, 3, 4, 2);
      GMI_Var.setButtonInfo(8, 0, 4, 5);
      GMI_Var.setButtonInfo(9, 0, 0, 3);

      do{

        if(GMI_Var.getUpdateScreen()){

          GF_Var.apply_surface(0, 0, GF_Var.BackGround[1], GF_Var.screen);

          GMI_Var.UpdateButtons(GF_Var);

          SDL_UpdateWindowSurface(GF_Var.Window);

          GMI_Var.setUpdateScreen(false);
        }

        while(GMI_Var.InputLoop(GF_Var)){

          GMI_Var.getEventType(GF_Var, 2);

          if(GMI_Var.getInputType()!=0){

            GMI_Var.setUpdateScreen(true);

            if(GMI_Var.getInputType()==1 || GMI_Var.getInputType()==2 ||
               GMI_Var.getInputType()==3 || GMI_Var.getInputType()==4){

              if(GMI_Var.getMenuSelect()==1){

                if(GMI_Var.getInputType()==1 || GMI_Var.getInputType()==2){

                  Loop.setExitState(true);
                }
              }else if(GMI_Var.getMenuSelect()==2){
                if(GMI_Var.getInputType()!=1){

                  if(GMI_Var.getIsArrowLeft()){

                    if(Map.getMapSizeX()>6){
                      Map.setMapSizeX(Map.getMapSizeX()-1);
                    }else if(Map.getMapSizeX()==6){
                      Map.setMapSizeX(Const::MaxMapSizeX);
                    }
                  }else if(!GMI_Var.getIsArrowLeft()){

                    if(Map.getMapSizeX()<Const::MaxMapSizeX){
                      Map.setMapSizeX(Map.getMapSizeX()+1);
                    }else if(Map.getMapSizeX()==Const::MaxMapSizeX){
                      Map.setMapSizeX(6);
                    }
                  }
                  MidVar.StringMidVar = GF_Var.IntToString(Map.getMapSizeX()-2);
                  GMI_Var.setText(GF_Var, 4, MidVar.StringMidVar);
                  GMI_Var.setButtonPos(4, -1, -1, GF_Var.TBSS(GF_Var.Text[4]));

                  MidVar.IntMidVar = IRand.getMSABOMS();
                  IRand.setMSABOMS(Map.getMapSizeX(), Map.getMapSizeY());
                  if(MidVar.IntMidVar != IRand.getMSABOMS()){
                    MidVar.StringMidVar = "Max player amount: "+GF_Var.IntToString(IRand.getMSABOMS());
                    GMI_Var.setText(GF_Var, 3, MidVar.StringMidVar);
                  }
                  MidVar.StringMidVar = "";
                }
              }else if(GMI_Var.getMenuSelect()==3){
                if(GMI_Var.getInputType()!=1){

                  if(GMI_Var.getIsArrowLeft()){

                    if(Map.getMapSizeY()>6){
                      Map.setMapSizeY(Map.getMapSizeY()-1);
                    }else if(Map.getMapSizeY()==6){
                      Map.setMapSizeY(Const::MaxMapSizeY);
                    }
                  }else if(!GMI_Var.getIsArrowLeft()){

                    if(Map.getMapSizeY()<Const::MaxMapSizeY){
                      Map.setMapSizeY(Map.getMapSizeY()+1);
                    }else if(Map.getMapSizeY()==Const::MaxMapSizeY){
                      Map.setMapSizeY(6);
                    }
                  }
                  MidVar.StringMidVar = GF_Var.IntToString(Map.getMapSizeY()-2);
                  GMI_Var.setText(GF_Var, 5, MidVar.StringMidVar);
                  GMI_Var.setButtonPos(8, -1, -1, GF_Var.TBSS(GF_Var.Text[5]));

                  MidVar.IntMidVar = IRand.getMSABOMS();
                  IRand.setMSABOMS(Map.getMapSizeX(), Map.getMapSizeY());
                  if(MidVar.IntMidVar != IRand.getMSABOMS()){
                    MidVar.StringMidVar = "Max player amount: "+GF_Var.IntToString(IRand.getMSABOMS());
                    GMI_Var.setText(GF_Var, 3, MidVar.StringMidVar);
                  }
                  MidVar.StringMidVar = "";
                }
              }
            }
          }else if(GF_Var.event.type == SDL_QUIT){
            Loop.setGameReset(false);
          }
        }

      }while(!Loop.getExitState());
      Loop.setExitState(false);
      GMI_Var.WipeTexts(GF_Var);
      GMI_Var.setMenuSelect(2);

    }else if(GMI_Var.getMenuSelect()==9){
      GMI_Var.setMenuSelect(1);

      GMI_Var.MenuChange(GF_Var, 9, 9);

      GMI_Var.setNumberOfButtons(12, 6);

      GMI_Var.setSubMenu(0);

      GMI_Var.setText(GF_Var, 0, "Back");
      GMI_Var.setText(GF_Var, 1, "Player: 1");
      GMI_Var.setText(GF_Var, 2, "Up:");
      GMI_Var.setText(GF_Var, 3, SDL_GetKeyName(GF_Var.Keys[0][0]));
      GMI_Var.setText(GF_Var, 4, "Down:");
      GMI_Var.setText(GF_Var, 5, SDL_GetKeyName(GF_Var.Keys[0][1]));
      GMI_Var.setText(GF_Var, 6, "Left:");
      GMI_Var.setText(GF_Var, 7, SDL_GetKeyName(GF_Var.Keys[0][2]));
      GMI_Var.setText(GF_Var, 8, "Right:");
      GMI_Var.setText(GF_Var, 9, SDL_GetKeyName(GF_Var.Keys[0][3]));
      GMI_Var.setText(GF_Var, 10, "<");
      GMI_Var.setText(GF_Var, 11, ">");

      GMI_Var.setButtonPos(0, 1, 1, 3);
      GMI_Var.setButtonPos(1, 1, 3, 1);
      GMI_Var.setButtonPos(2, 2, 3, 1);
      GMI_Var.setButtonPos(3, 3, 3, GF_Var.TBSS(GF_Var.Text[1]));
      GMI_Var.setButtonPos(4, 1, 4, 3);
      GMI_Var.setButtonPos(5, 4, 4, GF_Var.TBSS(GF_Var.Text[3]));
      GMI_Var.setButtonPos(6, 1, 5, 3);
      GMI_Var.setButtonPos(7, 4, 5, GF_Var.TBSS(GF_Var.Text[5]));
      GMI_Var.setButtonPos(8, 1, 6, 3);
      GMI_Var.setButtonPos(9, 4, 6, GF_Var.TBSS(GF_Var.Text[7]));
      GMI_Var.setButtonPos(10, 1, 7, 3);
      GMI_Var.setButtonPos(11, 4, 7, GF_Var.TBSS(GF_Var.Text[9]));

      GMI_Var.setButtonInfo(0, 1, 1, 0);
      GMI_Var.setButtonInfo(1, 2, 2, 10);
      GMI_Var.setButtonInfo(2, 2, 3, 11);
      GMI_Var.setButtonInfo(3, 2, 4, 1);
      GMI_Var.setButtonInfo(4, 3, 1, 2);
      GMI_Var.setButtonInfo(5, 0, 0, 3);
      GMI_Var.setButtonInfo(6, 4, 1, 4);
      GMI_Var.setButtonInfo(7, 0, 0, 5);
      GMI_Var.setButtonInfo(8, 5, 1, 6);
      GMI_Var.setButtonInfo(9, 0, 0, 7);
      GMI_Var.setButtonInfo(10, 6, 1, 8);
      GMI_Var.setButtonInfo(11, 0, 0, 9);

      do{

        if(GMI_Var.getUpdateScreen()){

          GF_Var.apply_surface(0, 0, GF_Var.BackGround[1], GF_Var.screen);

          GMI_Var.UpdateButtons(GF_Var);

          SDL_UpdateWindowSurface(GF_Var.Window);

          GMI_Var.setUpdateScreen(false);
        }

        while(GMI_Var.InputLoop(GF_Var)){

          GMI_Var.getEventType(GF_Var, 2);

          if(GMI_Var.getInputType()!=0){

            GMI_Var.setUpdateScreen(true);

            if(GMI_Var.getInputType()==1 || GMI_Var.getInputType()==2 ||
               GMI_Var.getInputType()==3 || GMI_Var.getInputType()==4){

              if(GMI_Var.getMenuSelect()==1){

                if(GMI_Var.getInputType()==1 || GMI_Var.getInputType()==2){
                  Loop.setExitState(true);
                }
              }else if(GMI_Var.getMenuSelect()==2){
                if(GMI_Var.getInputType()!=1){

                  if(GMI_Var.getIsArrowLeft()){
                    if(GMI_Var.getSubMenu() > 0){
                      GMI_Var.setSubMenu(GMI_Var.getSubMenu()-1);
                    }else{
                      GMI_Var.setSubMenu(Const::MaxPlayerAmount-1);
                    }
                  }else if(!GMI_Var.getIsArrowLeft()){
                    if(GMI_Var.getSubMenu() < Const::MaxPlayerAmount-1){
                      GMI_Var.setSubMenu(GMI_Var.getSubMenu()+1);
                    }else{
                      GMI_Var.setSubMenu(0);
                    }
                  }
                  MidVar.StringMidVar = "Player: "+GF_Var.IntToString(GMI_Var.getSubMenu()+1);
                  GMI_Var.setText(GF_Var, 1, MidVar.StringMidVar);
                  MidVar.StringMidVar = "";

                  GMI_Var.setText(GF_Var, 3, SDL_GetKeyName(GF_Var.Keys[GMI_Var.getSubMenu()][0]));
                  GMI_Var.setButtonPos(5, -1, -1, GF_Var.TBSS(GF_Var.Text[3]));
                  GMI_Var.setText(GF_Var, 5, SDL_GetKeyName(GF_Var.Keys[GMI_Var.getSubMenu()][1]));
                  GMI_Var.setButtonPos(7, -1, -1, GF_Var.TBSS(GF_Var.Text[5]));
                  GMI_Var.setText(GF_Var, 7, SDL_GetKeyName(GF_Var.Keys[GMI_Var.getSubMenu()][2]));
                  GMI_Var.setButtonPos(9, -1, -1, GF_Var.TBSS(GF_Var.Text[7]));
                  GMI_Var.setText(GF_Var, 9, SDL_GetKeyName(GF_Var.Keys[GMI_Var.getSubMenu()][3]));
                  GMI_Var.setButtonPos(11, -1, -1, GF_Var.TBSS(GF_Var.Text[9]));
                }
              }else if(GMI_Var.getMenuSelect()==3 || GMI_Var.getMenuSelect()==4 ||
                       GMI_Var.getMenuSelect()==5 || GMI_Var.getMenuSelect()==6){

                if(GMI_Var.getInputType()==1 || GMI_Var.getInputType()==2){

                  GMI_Var.DefaultInputLoopVars();
                  GMI_Var.setText(GF_Var, GMI_Var.getMenuSelect()*2-3, " ");
                  GMI_Var.makeButton(GF_Var, GMI_Var.getMenuSelect()*2-1, GF_Var.Text[GMI_Var.getMenuSelect()*2-3]);
                  SDL_UpdateWindowSurface(GF_Var.Window);

                  do{

                    while(GMI_Var.InputLoop(GF_Var)){

                      if(GF_Var.event.type == SDL_KEYDOWN){
                        if(GF_Var.event.key.keysym.sym == SDLK_ESCAPE ||
                           GF_Var.event.key.keysym.sym == GF_Var.Keys[GMI_Var.getSubMenu()][GMI_Var.getMenuSelect()-3]){
                          Loop.setExitState(true);
                        }else if(GF_Var.event.key.keysym.sym != SDLK_p){
                          if(GF_Var.event.key.keysym.sym != GF_Var.Keys[GMI_Var.getSubMenu()][0] &&
                             GF_Var.event.key.keysym.sym != GF_Var.Keys[GMI_Var.getSubMenu()][1] &&
                             GF_Var.event.key.keysym.sym != GF_Var.Keys[GMI_Var.getSubMenu()][2] &&
                             GF_Var.event.key.keysym.sym != GF_Var.Keys[GMI_Var.getSubMenu()][3]){

                            GF_Var.Keys[GMI_Var.getSubMenu()][GMI_Var.getMenuSelect()-3] = GF_Var.event.key.keysym.sym;

                            Loop.setExitState(true);
                          }
                        }
                      }else if(GF_Var.event.type == SDL_QUIT){
                        Loop.setGameReset(false);
                      }
                    }

                  }while(!Loop.getExitState());
                  Loop.setExitState(false);

                  if(GMI_Var.getMenuSelect() == 3){

                    GMI_Var.setText(GF_Var, 3, SDL_GetKeyName(GF_Var.Keys[GMI_Var.getSubMenu()][0]));
                    GMI_Var.setButtonPos(5, -1, -1, GF_Var.TBSS(GF_Var.Text[3]));
                  }else if(GMI_Var.getMenuSelect() == 4){

                    GMI_Var.setText(GF_Var, 5, SDL_GetKeyName(GF_Var.Keys[GMI_Var.getSubMenu()][1]));
                    GMI_Var.setButtonPos(7, -1, -1, GF_Var.TBSS(GF_Var.Text[5]));
                  }else if(GMI_Var.getMenuSelect() == 5){

                    GMI_Var.setText(GF_Var, 7, SDL_GetKeyName(GF_Var.Keys[GMI_Var.getSubMenu()][2]));
                    GMI_Var.setButtonPos(9, -1, -1, GF_Var.TBSS(GF_Var.Text[7]));
                  }else if(GMI_Var.getMenuSelect() == 6){

                    GMI_Var.setText(GF_Var, 9, SDL_GetKeyName(GF_Var.Keys[GMI_Var.getSubMenu()][3]));
                    GMI_Var.setButtonPos(11, -1, -1, GF_Var.TBSS(GF_Var.Text[9]));
                  }
                }
              }
            }
          }else if(GF_Var.event.type == SDL_QUIT){
            Loop.setGameReset(false);
          }
        }

      }while(!Loop.getExitState());
      Loop.setExitState(false);
      GMI_Var.WipeTexts(GF_Var);
      GMI_Var.setMenuSelect(6);
    }

  }while(Loop.getMenuState()==6);
  GMI_Var.WipeTexts(GF_Var);
}

void Menu::Quit(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, LoopControl& Loop){

  GMI_Var.setMenuSelect(1);

  GMI_Var.MenuChange(GF_Var, 8, 6);

  GMI_Var.setNumberOfButtons(3, 2);

  GMI_Var.setText(GF_Var, 0, "Are you sure?");
  GMI_Var.setText(GF_Var, 1, "No");
  GMI_Var.setText(GF_Var, 2, "Yes");

  GMI_Var.setButtonPos(0, 1, 1, 6);
  GMI_Var.setButtonPos(1, 1, 3, 2);
  GMI_Var.setButtonPos(2, 1, 4, 2);

  GMI_Var.setButtonInfo(0, 0, 0, 0);
  GMI_Var.setButtonInfo(1, 1, 1, 1);
  GMI_Var.setButtonInfo(2, 2, 1, 2);

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
            Loop.setMenuState(0);
            GMI_Var.setMenuSelect(6);
          }else if(GMI_Var.getMenuSelect()==2){
            Loop.setGameReset(false);
          }
          Loop.setExitState(true);
        }
      }else if(GF_Var.event.type == SDL_QUIT){
        Loop.setGameReset(false);
      }
    }

  }while(!Loop.getExitState());
  Loop.setExitState(false);
  GMI_Var.WipeTexts(GF_Var);
}

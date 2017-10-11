#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include <cctype>

#include "../Systems/GMI_Vars.h"
#include "../Graphics/GraphicFiles_Vars.h"
#include "../Variables/InternalRandom.h"
#include "../Variables/LoopControl.h"
#include "../Variables/Map.h"
#include "../Variables/MidVars.h"
#include "../Variables/OptionsRandom.h"

#include "../Variables/Constants.h"

class Menu
{
  public:
    void MainMenu(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                  LoopControl& Loop, Map& Map, MidVars& MidVar, OptionsRandom& ORand);

  private:
  	void MainMainMenu(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, LoopControl& Loop);
  	void NewGame(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                 LoopControl& Loop, MidVars& MidVar, OptionsRandom& ORand);
		void LoadGame(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand, LoopControl& Loop);
	 	void HighScores(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand, LoopControl& Loop, MidVars& MidVar);
		void Help(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, LoopControl& Loop);
    void Options(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                 LoopControl& Loop, Map& Map, MidVars& MidVar, OptionsRandom& ORand);
		void Quit(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, LoopControl& Loop);
};

#endif // MENU_H

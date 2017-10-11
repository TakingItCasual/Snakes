#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "../Systems/GMI_Vars.h"
#include "../Graphics/GraphicFiles_Vars.h"
#include "../Variables/InternalRandom.h"
#include "../Variables/LoopControl.h"
#include "../Variables/Map.h"
#include "../Variables/MidVars.h"
#include "../Variables/OptionsRandom.h"
#include "../Variables/Snake.h"

class GameOver
{
  public:
    void GameLoopExit(InternalRandom& IRand, LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake);
    void GameOverMessage(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                         LoopControl& Loop, Map& Map, OptionsRandom& ORand);
};

#endif // GAMEOVER_H

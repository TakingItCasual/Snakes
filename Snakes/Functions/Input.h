#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "../Systems/GMI_Vars.h"
#include "../Graphics/GraphicFiles_Vars.h"
#include "../Variables/InternalRandom.h"
#include "../Variables/LoopControl.h"
#include "../Variables/Map.h"
#include "../Variables/OptionsRandom.h"
#include "../Variables/Snake.h"
#include "../Variables/Timer.h"

class Input
{
  public:
    void GetInput(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                  LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake, Timer& Timer);

  private:
    void GameEsc(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand, LoopControl& Loop, Map& Map, OptionsRandom& ORand);
};

#endif // INPUT_H

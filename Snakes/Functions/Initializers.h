#ifndef INITIALIZERS_H
#define INITIALIZERS_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <sstream>
#include <stdlib.h>
#include <ctime>

#include "../Variables/Food.h"
#include "../Systems/GMI_Vars.h"
#include "../Graphics/GraphicFiles_Vars.h"
#include "../Variables/InternalRandom.h"
#include "../Variables/LoopControl.h"
#include "../Variables/Map.h"
#include "../Variables/OptionsRandom.h"
#include "../Variables/Snake.h"
#include "../Variables/Timer.h"

#include "../Variables/Constants.h"

class Initializers
{
  public:
    void ExternalVariableInitializers(Food& Food, GMI_Vars& GMI_Var, InternalRandom& IRand, LoopControl& Loop,
                                      Map& Map, OptionsRandom& ORand, Snake& Snake);
    void InternalVariableInitializers(Food& Food, GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                                      LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake);
    void MapBorderBuild(InternalRandom& IRand, Map& Map);
    void FunctionInitializers(Food& Food, InternalRandom& IRand, Map& Map, OptionsRandom& ORand, Snake& Snake, Timer& Timer);
};

#endif // INITIALIZERS_H

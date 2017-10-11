#ifndef FOODSYSTEM_H
#define FOODSYSTEM_H

#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>

#include <ctime>

#include "../Variables/Food.h"
#include "../Graphics/GraphicFiles_Vars.h"
#include "../Variables/InternalRandom.h"
#include "../Variables/LoopControl.h"
#include "../Variables/Map.h"
#include "../Variables/MidVars.h"
#include "../Variables/OptionsRandom.h"
#include "../Variables/Snake.h"

class FoodSys
{
  public:
    void FoodProcess(Food& Food, GraphicFiles_Vars& GF_Var, InternalRandom& IRand,
                     LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake);
};

#endif // FOODSYSTEM_H

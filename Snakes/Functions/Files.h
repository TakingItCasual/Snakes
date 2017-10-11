#ifndef FILES_H
#define FILES_H

#include <SDL.h>
#include <fstream>

#include "../Variables/Food.h"
#include "../Graphics/GraphicFiles_Vars.h"
#include "../Variables/InternalRandom.h"
#include "../Variables/LoopControl.h"
#include "../Variables/Map.h"
#include "../Variables/MidVars.h"
#include "../Variables/OptionsRandom.h"
#include "../Variables/Snake.h"

#include "../Variables/Constants.h"

class Files
{
  public:
    void ReadOptionsFile(InternalRandom& IRand, Map& Map, MidVars& MidVar, OptionsRandom& ORand, Snake& Snake);
    void ReadHighScoresFile(InternalRandom& IRand, MidVars& MidVar);
    void ReadInputASCII(GraphicFiles_Vars& GF_Var, MidVars& MidVar);
    void ReadSavedGame(Food& Food, InternalRandom& IRand, Map& Map, MidVars& MidVar, OptionsRandom& ORand, Snake& Snake);
    void WriteOptionsFile(Map& Map, OptionsRandom& ORand, Snake& Snake);
    void WriteHighScoresFile(InternalRandom& IRand, LoopControl& Loop, MidVars& MidVar, OptionsRandom& ORand);
    void WriteInputASCII(GraphicFiles_Vars& GF_Var);
    void WriteSavedGame(Food& Food, InternalRandom& IRand, LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake);
};

#endif // FILES_H

#ifndef TAIL_H
#define TAIL_H

#include "../Variables/InternalRandom.h"
#include "../Variables/LoopControl.h"
#include "../Variables/Map.h"
#include "../Variables/MidVars.h"
#include "../Variables/OptionsRandom.h"
#include "../Variables/Snake.h"

class Tail
{
  public:
    void ProcessUserInput(InternalRandom& IRand, LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake);
    void DeleteSnakeTail(InternalRandom& IRand, Map& Map, OptionsRandom& ORand, Snake& Snake);
    void TailLengthMaintainer(InternalRandom& IRand, Map& Map, OptionsRandom& ORand, Snake& Snake);
};

#endif // TAIL_H

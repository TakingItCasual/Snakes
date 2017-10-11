#ifndef NPC_H
#define NPC_H

#include "../Variables/Food.h"
#include "../Variables/Map.h"
#include "../Variables/OptionsRandom.h"
#include "../Variables/Snake.h"

#include "../Variables/Constants.h"

class NPC
{
  public:
    void NPC_Move(Food& Food, Map& Map, OptionsRandom& ORand, Snake& Snake);
};

#endif // NPC_H

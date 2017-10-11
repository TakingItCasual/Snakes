#include "Map.h"

void Map::setMapSize(int setMapSizeY, int setMapSizeX){
  MapCollision.resize(setMapSizeY);
  for(int FLL=0; FLL<setMapSizeY; FLL++){ //FLL = ForLoopLimiter
    MapCollision[FLL].resize(setMapSizeX);
  }
}

void Map::setMapCollision(int setMapCollisionY, int setMapCollisionX, int setMapCollision){
  MapCollision[setMapCollisionY][setMapCollisionX] = setMapCollision;
}

int Map::getMapCollision(int getMapCollisionY, int getMapCollisionX){
  return MapCollision[getMapCollisionY][getMapCollisionX];
}

bool Map::CollideCheck(int getMapCollisionY, int getMapCollisionX){

  if(MapCollision[getMapCollisionY][getMapCollisionX] == 1 || //Spot is occupied by a wall
     MapCollision[getMapCollisionY][getMapCollisionX] == 2){ //Spot is occupied by a snake tail
    return true;
  }else{
    return false;
  }
}

void Map::setMapSizeY(int setMapSizeY){
  MapSizeY = setMapSizeY;
}

int Map::getMapSizeY(){
  return MapSizeY;
}

void Map::setMapSizeX(int setMapSizeX){
  MapSizeX = setMapSizeX;
}

int Map::getMapSizeX(){
  return MapSizeX;
}

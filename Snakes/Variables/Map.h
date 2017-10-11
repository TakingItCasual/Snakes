#ifndef MAP_H
#define MAP_H

#include <vector>

using namespace std;

class Map
{
  public:
    void setMapSize(int setMapSizeY, int setMapSizeX);
    void setMapCollision(int setMapCollisionY, int setMapCollisionX, int setMapCollision);
    int getMapCollision(int getMapCollisionY, int getMapCollisionX);
    bool CollideCheck(int getMapCollisionY, int getMapCollisionX); //Checks if snake will collide.
    void setMapSizeY(int setMapSizeY);
    int getMapSizeY();
    void setMapSizeX(int setMapSizeX);
    int getMapSizeX();

  private:
    vector< vector<int> > MapCollision; //Holds collidable values for the map. 1=Wall, 2=Snake, 3=Food
    int MapSizeY; //The size of the game map Y axis.
    int MapSizeX; //The size of the game map X axis.
};

#endif // MAP_H

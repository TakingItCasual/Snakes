#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "Constants.h"

using namespace std;

class Snake
{
  public:
    void setTailLength(int PlayerNumber, int setTailLength);
    int getTailLength(int PlayerNumber);
    int DirectionReverse(int Direction);
    void setATL(int PlayerNumber, int setATL);
    int getATL(int PlayerNumber);
    void setSnakePosY(int PlayerNumber, int setSnakePosY);
    int getSnakePosY(int PlayerNumber);
    void setSnakePosX(int PlayerNumber, int setSnakePosX);
    int getSnakePosX(int PlayerNumber);
    void initializeVectors(int SnakeAmount);
    void setTailRetractSize(int PlayerNumber, int setTailRetractSize);
    void setTailRetract(int PlayerNumber, int TailSlot, int YorX, int setTailRetract);
    int getTailRetract(int PlayerNumber, int TailSlot, int YorX);
    void setSnakeTailConnect(int SnakeNumber, int TailSlot, int setFoward, int setBackward);
    int getSnakeTailConnect(int SnakeNumber, int TailSlot, int Direction);
    void setTECy(int PlayerNumber, int setTECy);
    int getTECy(int PlayerNumber);
    void setTECx(int PlayerNumber, int setTECx);
    int getTECx(int PlayerNumber);
    void setCISIA(int PlayerNumber, bool setCISIA);
    bool getCISIA(int PlayerNumber);
    void setSnakeDelete(int PlayerNumber, bool setSnakeDelete);
    bool getSnakeDelete(int PlayerNumber);
    void setInput(int PlayerNumber, int setInput);
    int getInput(int PlayerNumber);
    void setLastInput(int PlayerNumber, int setLastInput);
    int getLastInput(int PlayerNumber);
    void setDTNF(int SnakeNumber, int YorX, int DistanceOrDirection, int setDTNF);
    int getDTNF(int SnakeNumber, int YorX, int DistanceOrDirection);

  private:
    int TailLength[Const::MaxPlayerAmount]; //The length of the tail, duh. Including unprocessed food.
    vector< vector< vector<int> > > SnakeTailConnect; //For SDL to determine which image should be used.
    int ATL[Const::MaxPlayerAmount+1]; //TLC = ActualTailLength, how long the tail really is
    int SnakePosY[Const::MaxPlayerAmount]; //Position of Snake head on Y axis of map.
    int SnakePosX[Const::MaxPlayerAmount]; //Position of Snake head on X axis of map.
    vector< vector< vector<int> > > TailRetract; //Holds location of tail members.
    int TECy[Const::MaxPlayerAmount]; //TECy = TailEndClearer y
    int TECx[Const::MaxPlayerAmount]; //TECx = TailEndClearer x
    bool CISIA[Const::MaxPlayerAmount]; //CISIA = Check if Snake is alive
    bool SnakeDelete[Const::MaxPlayerAmount]; //Deletes snake if snake just died.
    int Input[Const::MaxPlayerAmount]; //Player input Ingame.
    int LastInput[Const::MaxPlayerAmount]; //Last Player input Ingame.
    int DTNF[Const::MaxPlayerAmount][2][2]; //DTNF = DistanceToNearestFood //For AI
};

#endif // SNAKE_H

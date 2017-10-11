#ifndef INTERNALRANDOM_H
#define INTERNALRANDOM_H

#include <string>

#include "Constants.h"

using namespace std;

class InternalRandom
{
  public:
    void setScore(int SnakeNumber, int setScore);
    int getScore(int SnakeNumber);
    void setScoreText(int SnakeNumber, int TextOrScore, string setScoreText);
    string getScoreText(int SnakeNumber, int TextOrScore);
    void setHighScores(int HighScoreNumber, int setHighScores);
    int getHighScores(int getHighScores);
    void setExitStatus(int setExitStatus);
    int getExitStatus();
    void setTailSpeedNum(int setTailSpeedNum1, int setTailSpeedNum2);
    int getTailSpeedNum(int getTailSpeedNum);
    void setLoadGame(int setLoadGame);
    bool getLoadGame();
    void setMSABOMS(int MapSizeX, int MapSizeY);
    int getMSABOMS();

  private:
    int Score[Const::MaxPlayerAmount]; //Amount of food eaten by the player(s).
    string ScoreText[Const::MaxPlayerAmount][2]; //The 'P1: 's
    int HighScores[4]; //High score values.
    int ExitStatus; //Depending on how you exited will change this.
    int TailSpeedNum[3]; //fast, medium, and slow tailspeeds in here.
    bool LoadGame; //Checks whether to start a new game or load game from txt file.
    int MSABOMS; //MSABOMS = MaxSnakeAmountBasedOnMapSize
};

#endif // INTERNALRANDOM_H

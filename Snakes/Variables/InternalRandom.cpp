#include "InternalRandom.h"

void InternalRandom::setScore(int SnakeNumber, int setScore){
  Score[SnakeNumber] = setScore;
}

int InternalRandom::getScore(int SnakeNumber){
  return Score[SnakeNumber];
}

void InternalRandom::setScoreText(int SnakeNumber, int TextOrScore, string setScoreText){
  ScoreText[SnakeNumber][TextOrScore] = setScoreText;
}

string InternalRandom::getScoreText(int SnakeNumber, int TextOrScore){
  return ScoreText[SnakeNumber][TextOrScore];
}

void InternalRandom::setHighScores(int HighScoreNumber, int setHighScores){
  HighScores[HighScoreNumber] = setHighScores;
}

int InternalRandom::getHighScores(int getHighScores){
  return HighScores[getHighScores];
}

void InternalRandom::setExitStatus(int setExitStatus){
  ExitStatus = setExitStatus;
}

int InternalRandom::getExitStatus(){
  return ExitStatus;
}

void InternalRandom::setTailSpeedNum(int setTailSpeedNum1, int setTailSpeedNum2){
  TailSpeedNum[setTailSpeedNum1] = setTailSpeedNum2;
}

int InternalRandom::getTailSpeedNum(int getTailSpeedNum){
  return TailSpeedNum[getTailSpeedNum];
}

void InternalRandom::setLoadGame(int setLoadGame){
  LoadGame = setLoadGame;
}

bool InternalRandom::getLoadGame(){
  return LoadGame;
}

void InternalRandom::setMSABOMS(int MapSizeX, int MapSizeY){
  if(MapSizeX < Const::MaxPlayerAmount*4 || MapSizeY < Const::MaxPlayerAmount*3+2){
    for(int SnakeAmount=1; SnakeAmount<=Const::MaxPlayerAmount; SnakeAmount++){
      if(MapSizeX < SnakeAmount*4 || MapSizeY < SnakeAmount*3+2){
        MSABOMS = SnakeAmount-1;
        break;
      }
    }
  }else{
    MSABOMS = Const::MaxPlayerAmount;
  }
}

int InternalRandom::getMSABOMS(){
  return MSABOMS;
}

#include "Food.h"

void Food::setFoodRetract(int FoodSlot, int YorX, int setFoodRetract){
  FoodRetract[FoodSlot][YorX] = setFoodRetract;
}

int Food::getFoodRetract(int FoodSlot, int YorX){
  return FoodRetract[FoodSlot][YorX];
}

void Food::setFoodDirection(int setFoodDirection){
  FoodDirection = setFoodDirection;
}

int Food::getFoodDirection(){
  return FoodDirection;
}

void Food::setMFI(int setMFI){
  MFI = setMFI;
}

int Food::getMFI(){
  return MFI;
}

void Food::setMFCIA(bool setMFCIA){
  MFCIA = setMFCIA;
}

bool Food::getMFCIA(){
  return MFCIA;
}

void Food::setFood2Eater(int setFood2Eater){
  Food2Eater = setFood2Eater;
}

int Food::getFood2Eater(){
  return Food2Eater;
}

void Food::setSFCOS(int setSFCOS){
  SFCOS = setSFCOS;
}

int Food::getSFCOS(){
  return SFCOS;
}

void Food::setFoodPosY(int setFoodPosY){
  FoodPosY = setFoodPosY;
}

int Food::getFoodPosY(){
  return FoodPosY;
}

void Food::setFoodPosX(int setFoodPosX){
  FoodPosX = setFoodPosX;
}

int Food::getFoodPosX(){
  return FoodPosX;
}

void Food::setFoodPos2Y(int setFoodPos2Y){
  FoodPos2Y = setFoodPos2Y;
}

int Food::getFoodPos2Y(){
  return FoodPos2Y;
}

void Food::setFoodPos2X(int setFoodPos2X){
  FoodPos2X = setFoodPos2X;
}

int Food::getFoodPos2X(){
  return FoodPos2X;
}

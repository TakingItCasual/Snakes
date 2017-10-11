#ifndef FOOD_H
#define FOOD_H

class Food{
  public:
    void setFoodRetract(int FoodSlot, int YorX, int setFoodRetract);
    int getFoodRetract(int FoodSlot, int YorX);
    void setFoodDirection(int setFoodDirection);
    int getFoodDirection();
    void setMFI(int setMFI);
    int getMFI();
    void setMFCIA(bool setMFCIA);
    bool getMFCIA();
    void setFood2Eater(int setFood2Eater);
    int getFood2Eater();
    void setSFCOS(int setSFCOS);
    int getSFCOS();
    void setFoodPosY(int setFoodPosY);
    int getFoodPosY();
    void setFoodPosX(int setFoodPosX);
    int getFoodPosX();
    void setFoodPos2Y(int setFoodPos2Y);
    int getFoodPos2Y();
    void setFoodPos2X(int setFoodPos2X);
    int getFoodPos2X();

  private:
    int FoodRetract[2][2]; //Keeps the second food 1 character long.
    int FoodDirection; //Decides which direction the secondary food will go.
    int MFI; //MFI = MobileFoodInitializer
    bool MFCIA; //MFCIA = MobileFoodCheckIfActive
    int Food2Eater; //Identifies which snake ate the secondary food.
    int SFCOS; //SFCOS = SecondFoodChanceOfSpawning ((1/number) chance)
    int FoodPosY; //Position of food on the Y axis of the map.
    int FoodPosX; //Position of food on the X axis of the map.
    int FoodPos2Y; //Position of the second food on Y axis of map.
    int FoodPos2X; //Position of the second food on X axis of map.
};

#endif // FOOD_H

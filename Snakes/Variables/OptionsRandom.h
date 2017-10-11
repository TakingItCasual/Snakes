#ifndef OPTIONSRANDOM_H
#define OPTIONSRANDOM_H

class OptionsRandom
{
  public:
    void setBorderTeleport(bool setBorderTeleport);
    bool getBorderTeleport();
    void setPlayerAmount(int setPlayerAmount);
    int getPlayerAmount();
    void setSnakeAmount(int setSnakeAmount);
    int getSnakeAmount();
    void setAISmartness(int setAISmartness);
    int getAISmartness();
    void setTailSpeed(int setTailSpeed);
    int getTailSpeed();

  private:
    bool BorderTeleport; //Toggles if the snake can go through the walls.
    int PlayerAmount; //Amount of human players.
    int SnakeAmount; //Total amount of snakes.
    int AISmartness; //How smart NPC AI is.
    int TailSpeed; //Speed of the snake, in milliseconds.
};

#endif // OPTIONSRANDOM_H

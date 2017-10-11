#ifndef LOOPCONTROL_H
#define LOOPCONTROL_H


class LoopControl
{
  public:
    void setGameReset(bool setGameReset);
    bool getGameReset();
    void setExitState(bool setExitState);
    bool getExitState();
    void setMenuState(int setMenuState);
    int getMenuState();
    void setInputLoopBreak(bool setInputLoopBreak);
    bool getInputLoopBreak();
    void setForLoopIfCheck(bool setForLoopIfCheck);
    bool getForLoopIfCheck();

  private:
    bool GameReset; //Quits the game if false
    bool ExitState; //If an exiting condition for anything is met this is set to true
    int MenuState; //Which menu screen you're on
    bool InputLoopBreak; //Exits input loop after user input
    bool ForLoopIfCheck; //True if an if statement in a for loop is triggered
};

#endif // LOOPCONTROL_H

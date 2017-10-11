#ifndef GMI_VARS_H
#define GMI_VARS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "../Graphics/GraphicFiles_Vars.h"

#include "../Variables/Constants.h"

class GMI_Vars //Graphical Menu Interface
{
  public:
    void setNumberOfButtons(int setNumberOfButtons, int setMenuSelectLimit, int setNumberOfTexts = 0);
    int getNumberOfButtons(int ButtonsOrMenuSelectOrTextNumber);
    void setMenuSelect(int setMenuSelect);
    int getMenuSelect();
    void setSubMenu(int setSubMenu);
    int getSubMenu();
    int getInputType();
    bool getIsArrowLeft();
    void setButtonPos(int Button, int setPosX, int setPosY, int setBoxWidth);
    void setButtonInfo(int Button, int setMenuSelect, int setButtonPurpose, int setTextValue);
    int getButtonTextLink(int Button); //For buttons with ButtonInfo[...][1] of 5, so they can use makeButton from the menu
    void setUpdateScreen(bool setUpdateScreen);
    bool getUpdateScreen();

    void MenuChange(GraphicFiles_Vars& GF_Var, int setScreenSizeX, int setScreenSizeY); //Calls setBackgroundSize and changes a few GMI_Var bools.
    void UpdateButtons(GraphicFiles_Vars& GF_Var); //Updates the buttons based on the current MenuSelect value
    void getEventType(GraphicFiles_Vars& GF_Var, int KeyInclusion); //Event system for menus; enter, up, down, left, right, mousebutton, mousemovement
    void setText(GraphicFiles_Vars& GF_Var, int TextNum, std::string String); //Function to set the Text ttf sdl surface
    void WipeTexts(GraphicFiles_Vars& GF_Var); //Calls SDL_FreeSurface for all of the texts
    bool InputLoop(GraphicFiles_Vars& GF_Var); //Since EnableKeyRepeat doesn't seem to check the mouse, need to make manual function instead
    void DefaultInputLoopVars(); //Zeros everything InputLoop related
    void makeButton(GraphicFiles_Vars& GF_Var, int ButtonNum, SDL_Surface* Text, bool MouseOver = false); //Creates the button to be displayed on screen

  private:
    int NumberOfButtons[3]; //Number of buttons; for all button related vectors, second value is the top MenuSelect limit
  	int MenuSelect; //Used in menus for which (clickable) button the mouse/enter is focused on
    int SubMenu; //For example when there are identical options for multiple users.
    int InputType; //Determines what input type in SDL events is
    bool MouseOverButton; //If mouse is over a menu button
    bool MouseDown; //If left mouse button is pressed down
    bool FocusOnArrow; //If the focus is on a left/right selection arrow
    bool IsArrowLeft; //If the focus is on an arrow, this says if it's the left or right arrow; true, left, false, right
    int InputLoopStage; //Int used for the ClickArrowKeyLoop function. Has four states; 0, inactive, 1, triggered, 2, initialized timer, 3, active. Also not usable outside of class
    int InputLoopType; //What input type is being looped; click (on arrowkey), enter, up/down, left/right, respective to priority
    bool InputKeyStates[5]; //States for enter, up, down, left and right
    bool InputLoopTriggered; //For getEventType, ignores GF_Var.event if true
    int MousePosX; //Mouse position on X axis of screen
    int MousePosY; //Mouse position on Y axis of screen
    int ButtonPos[12][3]; //Position of the menu buttons on the map; position on X axis, position on Y axis and button length, respectively
    int ButtonInfo[12][3]; //Whether a button has a menuselect value, aditional info, and what GF_Var.Text is assigned to it
    bool UpdateScreen; //If an event occurs this will be set to true to allow the screen to update

    //Following 2 variables are for the StartTimer and CheckTimer functions
    Uint32 StartTime;
    int elapsedTime;

    void setInputLoopType(int setInputLoopType, bool Activate = true); //Sets InputLoopType to the value requested only if the current value is lower
    bool CheckIfMouseOverButton(int ButtonNum); //Specialized function for CheckWhichButtonMouseOver, for checking if the mouse is over a specific button
    void CheckWhichButtonMouseOver(GraphicFiles_Vars& GF_Var, bool MouseMove); //Checks if the mouse is over any clickable buttons and changes MenuSelect accordingly
    void UpMenuSelect(); //If the user presses up in a menu, MenuSelect goes down
    void DownMenuSelect(); //If the user presses down in a menu, MenuSelect goes up
    void StartTimer();
    bool CheckTimer(int MilliSeconds);
};

#endif // GMI_VARS_H

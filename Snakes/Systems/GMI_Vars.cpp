#include "GMI_Vars.h"

void GMI_Vars::setNumberOfButtons(int setNumberOfButtons, int setMenuSelectLimit, int setNumberOfTexts){
  NumberOfButtons[0] = setNumberOfButtons;
  NumberOfButtons[1] = setMenuSelectLimit;
  if(setNumberOfTexts == 0){
    NumberOfButtons[2] = setNumberOfButtons;
  }else{
    NumberOfButtons[2] = setNumberOfTexts;
  }
}

int GMI_Vars::getNumberOfButtons(int ButtonsOrMenuSelectOrTextNumber){
  return NumberOfButtons[ButtonsOrMenuSelectOrTextNumber];
}

void GMI_Vars::setMenuSelect(int setMenuSelect){
	MenuSelect = setMenuSelect;
}

int GMI_Vars::getMenuSelect(){
	return MenuSelect;
}

void GMI_Vars::setSubMenu(int setSubMenu){
  SubMenu = setSubMenu;
}

int GMI_Vars::getSubMenu(){
  return SubMenu;
}

int GMI_Vars::getInputType(){
	return InputType;
}

bool GMI_Vars::getIsArrowLeft(){
	return IsArrowLeft;
}

void GMI_Vars::DefaultInputLoopVars(){

  InputLoopStage = 0;
  InputLoopType = 0;
  InputKeyStates[0] = false;
  InputKeyStates[1] = false;
  InputKeyStates[2] = false;
  InputKeyStates[3] = false;
  InputKeyStates[4] = false;
  InputLoopTriggered = false;
}

void GMI_Vars::setButtonPos(int Button, int setPosX, int setPosY, int setBoxWidth){

	if(setPosX != -1){ //If setPosX is 0, then PosX will not be modified
    ButtonPos[Button][0] = setPosX;
	}
	if(setPosY != -1){ //If setPosY is 0, then PosY will not be modifed
    ButtonPos[Button][1] = setPosY;
	}
	if(setBoxWidth != -1){ //If setBoxWidth is 0, then BoxWidth will not be modified
    ButtonPos[Button][2] = setBoxWidth;
	}
}

void GMI_Vars::setButtonInfo(int Button, int setMenuSelect, int setButtonPurpose, int setTextValue){

  ButtonInfo[Button][0] = setMenuSelect;
  ButtonInfo[Button][1] = setButtonPurpose;
  ButtonInfo[Button][2] = setTextValue;
}

int GMI_Vars::getButtonTextLink(int Button){
  return ButtonInfo[Button][2];
}

void GMI_Vars::setUpdateScreen(bool setUpdateScreen){
	UpdateScreen = setUpdateScreen;
}

bool GMI_Vars::getUpdateScreen(){
	return UpdateScreen;
}

void GMI_Vars::MenuChange(GraphicFiles_Vars& GF_Var, int setScreenSizeX, int setScreenSizeY){
  UpdateScreen = true;
  MouseOverButton = false;
  FocusOnArrow = false;

  DefaultInputLoopVars();

  GF_Var.setBackgroundSize(setScreenSizeX, setScreenSizeY);
}

void GMI_Vars::UpdateButtons(GraphicFiles_Vars& GF_Var){

  for(int Button=0; Button<NumberOfButtons[0]; Button++){

    if(ButtonInfo[Button][1] == 5){ //5 is an express "don't print me", for when you only want to print it under special conditions
      //do nothing
    }else if(ButtonInfo[Button][0] == 0){ //If the button doesn't have a MenuSelect value (isn't clickable)
      makeButton(GF_Var, Button, GF_Var.Text[ButtonInfo[Button][2]]);
    }else if(ButtonInfo[Button][1] == 1 || ButtonInfo[Button][1] == 4){ //If the button has a MenuSelect value but isn't an arrowkey, or is right after arrowkeys
      if(ButtonInfo[Button][0] == MenuSelect){
        makeButton(GF_Var, Button, GF_Var.Text[ButtonInfo[Button][2]], true);
      }else{
        makeButton(GF_Var, Button, GF_Var.Text[ButtonInfo[Button][2]]);
      }
    }else if(ButtonInfo[Button][1] == 2){ //If the button has a MenuSelect value and is a left arrowkey
      if(FocusOnArrow && IsArrowLeft){
        if(ButtonInfo[Button][0] == MenuSelect){
          makeButton(GF_Var, Button, GF_Var.Text[ButtonInfo[Button][2]], true);
        }else{
          makeButton(GF_Var, Button, GF_Var.Text[ButtonInfo[Button][2]]);
        }
      }else{
        makeButton(GF_Var, Button, GF_Var.Text[ButtonInfo[Button][2]]);
      }
    }else if(ButtonInfo[Button][1] == 3){ //If the button has a MenuSelect value and is a right arrowkey
      if(FocusOnArrow && !IsArrowLeft){
        if(ButtonInfo[Button][0] == MenuSelect){
          makeButton(GF_Var, Button, GF_Var.Text[ButtonInfo[Button][2]], true);
        }else{
          makeButton(GF_Var, Button, GF_Var.Text[ButtonInfo[Button][2]]);
        }
      }else{
        makeButton(GF_Var, Button, GF_Var.Text[ButtonInfo[Button][2]]);
      }
    }
  }
}

void GMI_Vars::getEventType(GraphicFiles_Vars& GF_Var, int KeyInclusion){

  if(InputLoopTriggered){ //Input looping because of key (or mouse on arrow key) being held down
    if(InputLoopType == 4){ //Mouse held down on arrow key
      InputType = 2;
    }else if(InputLoopType == 3){ //Enter (InputKeyStates[0] should be true)
      InputType = 1;
    }else if(InputLoopType == 2){ //Up or down (shouldn't be both)
      if(InputKeyStates[1]){ //Up
        UpMenuSelect();
        InputType = 0;
      }else{ //Down (InputKeyStates[2] should be true)
        DownMenuSelect();
        InputType = 0;
      }
    }else if(InputLoopType == 1){ //Left or right (shouldn't be both)
      if(InputKeyStates[3]){ //Left
        InputType = 3;
      }else{ //Right (InputKeyStates[4] should be true)
        InputType = 4;
      }
    }
    InputLoopTriggered = false;
  }else if(GF_Var.event.type == SDL_KEYDOWN || GF_Var.event.type == SDL_KEYUP || GF_Var.event.type == SDL_MOUSEMOTION ||
           GF_Var.event.type == SDL_MOUSEBUTTONDOWN || GF_Var.event.type == SDL_MOUSEBUTTONUP){

    InputType = 0;
    if(GF_Var.event.type == SDL_KEYDOWN){
      if(GF_Var.event.key.keysym.sym == SDLK_RETURN){

        InputKeyStates[0] = true;
        if(InputLoopType != 4){
          InputType = 1;
          setInputLoopType(3);
        }
      }else if(GF_Var.event.key.keysym.sym == SDLK_UP && KeyInclusion>0){

        InputKeyStates[1] = true;
        if(!(MouseOverButton && MouseDown) && InputLoopType < 3){ //Only if mouse isn't down on button, and InputLoop priority is up/down or below

          FocusOnArrow = false;
          if(InputKeyStates[2]){ //Down is also held down, therefore InputType priority up/down must be deactivated
            setInputLoopType(2, false);
          }else{ //Down is not held down, so InputType 2 can be activated
            UpMenuSelect();
            setInputLoopType(2);
          }
        }
      }else if(GF_Var.event.key.keysym.sym == SDLK_DOWN && KeyInclusion>0){

        InputKeyStates[2] = true;
        if(!(MouseOverButton && MouseDown) && InputLoopType < 3){ //Only if mouse isn't down on button, and InputLoop priority is up/down or below

          FocusOnArrow = false;
          if(InputKeyStates[1]){ //Up is also held down, therefore InputType priority up/down must be deactivated
            setInputLoopType(2, false);
          }else{ //Up is not held down, so InputType 2 can be activated
            DownMenuSelect();
            setInputLoopType(2);
          }
        }
      }else if(GF_Var.event.key.keysym.sym == SDLK_LEFT && KeyInclusion==2){

        InputKeyStates[3] = true;
        if(InputLoopType < 2){ //Only if InputLoop priority is left/right or below

          IsArrowLeft = true;
          if(InputKeyStates[4]){ //Right is also held down, therefore InputType priority left/right must be deactivated
            FocusOnArrow = false;
            setInputLoopType(1, false);
          }else{ //Right is not held down, so InputType 2 can be activated
            FocusOnArrow = true;
            setInputLoopType(1);
            InputType = 3;
          }
        }
      }else if(GF_Var.event.key.keysym.sym == SDLK_RIGHT && KeyInclusion==2){

        InputKeyStates[4] = true;
        if(InputLoopType < 2){ //Only if InputLoop priority is left/right or below

          IsArrowLeft = false;
          if(InputKeyStates[3]){ //Left is also held down, therefore InputType priority left/right must be deactivated
            FocusOnArrow = false;
            setInputLoopType(1, false);
          }else{ //Left is not held down, so InputType 2 can be activated
            FocusOnArrow = true;
            setInputLoopType(1);
            InputType = 4;
          }
        }
      }
    }else if(GF_Var.event.type == SDL_KEYUP){
      if(GF_Var.event.key.keysym.sym == SDLK_RETURN){

        InputKeyStates[0] = false;
        setInputLoopType(3, false);
      }else if(GF_Var.event.key.keysym.sym == SDLK_UP && KeyInclusion>0){

        InputKeyStates[1] = false;
        if(InputLoopType < 3){ //Only if InputLoop priority is up/down or below
          if(!InputKeyStates[2]){
            setInputLoopType(2, false);
          }else if(!(MouseOverButton && MouseDown)){ //If mouse isn't down on button
            setInputLoopType(2);
          }
        }
      }else if(GF_Var.event.key.keysym.sym == SDLK_DOWN && KeyInclusion>0){

        InputKeyStates[2] = false;
        if(InputLoopType < 3){ //Only if InputLoop priority is up/down or below
          if(!InputKeyStates[1]){
            setInputLoopType(2, false);
          }else if(!(MouseOverButton && MouseDown)){ //If mouse isn't down on button
            setInputLoopType(2);
          }
        }
      }else if(GF_Var.event.key.keysym.sym == SDLK_LEFT && KeyInclusion==2){

        InputKeyStates[3] = false;
        if(InputLoopType < 2){ //Only if InputLoop priority is left/right or below
          if(!InputKeyStates[4]){
            FocusOnArrow = false;
            setInputLoopType(1, false);
          }else{
            FocusOnArrow = true;
            IsArrowLeft = false;
            setInputLoopType(1);
          }
        }
      }else if(GF_Var.event.key.keysym.sym == SDLK_RIGHT && KeyInclusion==2){

        InputKeyStates[4] = false;
        if(InputLoopType < 2){ //Only if InputLoop priority is left/right or below
          if(!InputKeyStates[3]){
            FocusOnArrow = false;
            setInputLoopType(1, false);
          }else{
            FocusOnArrow = true;
            IsArrowLeft = true;
            setInputLoopType(1);
          }
        }
      }
    }else if(GF_Var.event.type == SDL_MOUSEBUTTONUP){
      if(GF_Var.event.button.button == SDL_BUTTON_LEFT){
        MouseDown = false;
        setInputLoopType(4, false); //InputLoop type 4 (mouse down over arrow key) cancelled when mouse released
        if(MouseOverButton && !FocusOnArrow){
          InputType = 2;
        }
      }
    }else if(GF_Var.event.type == SDL_MOUSEMOTION){
      setInputLoopType(4, false); //InputLoop type 4 (mouse down over arrow key) cancelled when arrow moves
      CheckWhichButtonMouseOver(GF_Var, true);
    }else if(GF_Var.event.type == SDL_MOUSEBUTTONDOWN){
      if(GF_Var.event.button.button == SDL_BUTTON_LEFT){
        MouseDown = true;
        if(MouseOverButton && FocusOnArrow){ //If the mouse is over an arrow key, initiates InputLoop type 4
          InputType = 2;
          setInputLoopType(4);
        }else{
          InputType = 0;
          CheckWhichButtonMouseOver(GF_Var, false);
          if(MouseOverButton){
            setInputLoopType(2, false); //InputLoop type up/down can't loop when mouse down on button
          }
        }
      }
    }
  }else{
    InputType = 0;
  }
}

void GMI_Vars::setText(GraphicFiles_Vars& GF_Var, int TextNum, std::string String){
  GF_Var.Text[TextNum] = TTF_RenderText_Solid(GF_Var.font, String.c_str(), GF_Var.textColor);
}

void GMI_Vars::WipeTexts(GraphicFiles_Vars& GF_Var){

  for(int TextNum=0; TextNum<NumberOfButtons[2]; TextNum++){
    SDL_FreeSurface(GF_Var.Text[TextNum]);
  }
  NumberOfButtons[2] = 0;
}

bool GMI_Vars::InputLoop(GraphicFiles_Vars& GF_Var){

  if(SDL_PollEvent(&GF_Var.event)){
    return true;
  }else if(InputLoopStage != 0){
    if(InputLoopStage == 3 && CheckTimer(Const::KeyRepeatInterval)){ //3, has been activated and is running normally

      StartTimer(); //Resets timer
      InputLoopTriggered = true;
      return true;

    }else if(InputLoopStage == 2 && CheckTimer(Const::KeyRepeatDelay)){ //2 is for right after the timer being activated, using the delay time instead of interval
      
      StartTimer(); //Resets timer
      InputLoopStage = 3;
      InputLoopTriggered = true;
      return true;

    }else if(InputLoopStage == 1){ //InputLoopStage has just been activated, so the timer needs to be initialized
      
      StartTimer(); //Initializes timer
      InputLoopStage = 2;
      return false;
    }
  }
  return false;
}

void GMI_Vars::makeButton(GraphicFiles_Vars& GF_Var, int ButtonNum, SDL_Surface* Text, bool MouseOver){

  if(ButtonPos[ButtonNum][2]>1){ //If the button is wider than 1
    GF_Var.apply_surface(ButtonPos[ButtonNum][0], ButtonPos[ButtonNum][1], GF_Var.TextBox[MouseOver*4], GF_Var.screen); //Adds the beginning piece
    for(int BoxMiddle=ButtonPos[ButtonNum][0]+1; BoxMiddle<ButtonPos[ButtonNum][0]+ButtonPos[ButtonNum][2]-1; BoxMiddle++){
      GF_Var.apply_surface(BoxMiddle, ButtonPos[ButtonNum][1], GF_Var.TextBox[MouseOver*4+1], GF_Var.screen); //Adds all the middle pieces (if button width is more than 2)
    }
    GF_Var.apply_surface(ButtonPos[ButtonNum][0]+ButtonPos[ButtonNum][2]-1,
                         ButtonPos[ButtonNum][1], GF_Var.TextBox[MouseOver*4+2], GF_Var.screen); // Adds the end piece
  }else if(ButtonPos[ButtonNum][2] == 1){ //If the button width is only 1 (for example arrow keys)
    GF_Var.apply_surface(ButtonPos[ButtonNum][0], ButtonPos[ButtonNum][1], GF_Var.TextBox[MouseOver*4+3], GF_Var.screen);
  }
  GF_Var.apply_surface(ButtonPos[ButtonNum][0], ButtonPos[ButtonNum][1], Text, GF_Var.screen, NULL, 3, 2); //Adds the text
}

void GMI_Vars::setInputLoopType(int setInputLoopType, bool Activate){
  if(!Activate){
    if(InputLoopType == setInputLoopType){ //Checks that deactivation value is valid
      if(InputKeyStates[0]){ //If enter is held down

        InputLoopType = 3;
        InputLoopStage = 1;
      }else if(((InputKeyStates[1] && !InputKeyStates[2]) || //If up is held down but not down
               (InputKeyStates[2] && !InputKeyStates[1])) && //If down is held down but not up
               !(MouseOverButton && MouseDown)){ //If mouse isn't down on button

        InputLoopType = 2;
        InputLoopStage = 1;
      }else if((InputKeyStates[3] && !InputKeyStates[4]) || //If left is held down but not right
               (InputKeyStates[4] && !InputKeyStates[3])){ //If right is held down but not left

        InputLoopType = 1;
        InputLoopStage = 1;
      }else{
        InputLoopType = 0;
        InputLoopStage = 0;
      }
    }
  }else if(InputLoopType < setInputLoopType){ //Checks if setInputLoopType is higher priority than current InputLoopType
    InputLoopType = setInputLoopType;
    InputLoopStage = 1;
  }
}

bool GMI_Vars::CheckIfMouseOverButton(int ButtonNum){

  if(MousePosX>=ButtonPos[ButtonNum][0]*Const::Block_Size &&
     MousePosX<(ButtonPos[ButtonNum][0]+ButtonPos[ButtonNum][2])*Const::Block_Size &&
     MousePosY>=ButtonPos[ButtonNum][1]*Const::Block_Size &&
     MousePosY<(ButtonPos[ButtonNum][1]+1)*Const::Block_Size){

    return true;
  }
  return false;
}

void GMI_Vars::CheckWhichButtonMouseOver(GraphicFiles_Vars& GF_Var, bool MouseMove){

  if(MouseMove){
    MousePosX = GF_Var.event.motion.x;
    MousePosY = GF_Var.event.motion.y;
  }

  for(int Button=0; Button<=NumberOfButtons[0]; Button++){

    if(Button == NumberOfButtons[0]){ //This button does not exist, only gets here if no buttons where moused over
      MouseOverButton = false;
      FocusOnArrow = false;
    }else if(ButtonInfo[Button][0] != 0){ //Checks that the button has a MenuSelect value
      if(ButtonInfo[Button][1] == 1 || ButtonInfo[Button][1] == 4){ //If the button has a MenuSelect value but isn't an arrowkey, or is right after arrowkeys
        if(CheckIfMouseOverButton(Button)){
          MouseOverButton = true;
          FocusOnArrow = false;
          MenuSelect = ButtonInfo[Button][0];
          break;
        }
      }else if(ButtonInfo[Button][1] == 2){ //If the button has a MenuSelect value and is a left arrowkey
        if(CheckIfMouseOverButton(Button)){
          MouseOverButton = true;
          FocusOnArrow = true;
          IsArrowLeft = true;
          MenuSelect = ButtonInfo[Button][0];
          break;
        }
      }else if(ButtonInfo[Button][1] == 3){ //If the button has a MenuSelect value and is a right arrowkey
        if(CheckIfMouseOverButton(Button)){
          MouseOverButton = true;
          FocusOnArrow = true;
          IsArrowLeft = false;
          MenuSelect = ButtonInfo[Button][0];
          break;
        }
      }
    }
  }
  UpdateScreen = true;
}

void GMI_Vars::UpMenuSelect(){

  if(MenuSelect > 1){
    MenuSelect -= 1;
  }else{
    MenuSelect = NumberOfButtons[1];
  }
  UpdateScreen = true;
}

void GMI_Vars::DownMenuSelect(){

  if(MenuSelect < NumberOfButtons[1]){
    MenuSelect += 1;
  }else{
    MenuSelect = 1;
  }
  UpdateScreen = true;
}

void GMI_Vars::StartTimer(){
  StartTime = SDL_GetTicks();
}

bool GMI_Vars::CheckTimer(int MilliSeconds){
  elapsedTime = SDL_GetTicks()-StartTime;
  if(elapsedTime >= MilliSeconds){
    return true;
  }
  return false;
}

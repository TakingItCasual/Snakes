#include "GraphicFiles_Vars.h"

void GraphicFiles_Vars::apply_surface(
	int x, int y, SDL_Surface* source, SDL_Surface* destination, 
	SDL_Rect* clip, int ExtraX, int ExtraY){

  SDL_Rect offset;

  offset.x = x * Const::Block_Size + ExtraX;
  offset.y = y * Const::Block_Size + ExtraY;

  SDL_BlitSurface(source, clip, destination, &offset);
}

void GraphicFiles_Vars::setBackgroundSize(int ScreenSizeX, int ScreenSizeY){

  SDL_SetWindowSize(Window, Const::Block_Size*ScreenSizeX, Const::Block_Size*ScreenSizeY);
  screen = SDL_GetWindowSurface(Window);

  if(BackGround[1] != NULL){
    SDL_FreeSurface(BackGround[1]);
  }
  BackGround[1] = SDL_CreateRGBSurface(
		SDL_SWSURFACE, Const::Block_Size * ScreenSizeX, Const::Block_Size * ScreenSizeY, Const::SCREEN_BPP,
        BackGround[0]->format->Rmask, BackGround[0]->format->Gmask,
        BackGround[0]->format->Bmask, BackGround[0]->format->Amask);

  for(int SurfaceX=0; SurfaceX<ScreenSizeX; SurfaceX++){
    for(int SurfaceY=0; SurfaceY<ScreenSizeY; SurfaceY++){
      apply_surface(SurfaceX, SurfaceY, BackGround[0], BackGround[1]);
    }
  }

  apply_surface(0, 0, BackGround[1], screen);
  SDL_UpdateWindowSurface(Window);
}

std::string GraphicFiles_Vars::IntToString(int Num){

  std::stringstream IntToString;
  std::string String;
  IntToString << Num;
  String = IntToString.str();
  return String;
}

void GraphicFiles_Vars::Init_GF_Vars(){

  screen = NULL;
  SpriteSheet = NULL;
  BackGround[0] = NULL;
  BackGround[1] = NULL;
  Title = NULL;
  for(int Rotation=0; Rotation<4; Rotation++){
    Borders[Rotation] = NULL;
  }
  for(int SnakePart=0; SnakePart<5; SnakePart++){
    for(int RotatedPart=0; RotatedPart<4; RotatedPart++){
      SnakeImg[SnakePart][RotatedPart] = NULL;
    }
  }
  for(int Direction=0; Direction<5; Direction++){
    Food[Direction] = NULL;
  }
  for(int TextBoxNum=0; TextBoxNum<8; TextBoxNum++){
    TextBox[TextBoxNum] = NULL;
  }
  for(int Score=0; Score<Const::MaxPlayerAmount; Score++){
    Scores[Score] = NULL;
  }
  for(int TextNum=0; TextNum<12; TextNum++){
    Text[TextNum] = NULL;
  }
  MidSurface[0] = NULL;
  MidSurface[1] = NULL;

  Keys[0][0] = SDLK_UP;
  Keys[0][1] = SDLK_DOWN;
  Keys[0][2] = SDLK_LEFT;
  Keys[0][3] = SDLK_RIGHT;
  if(Const::MaxPlayerAmount>1){
    Keys[1][0] = SDLK_w;
    Keys[1][1] = SDLK_s;
    Keys[1][2] = SDLK_a;
    Keys[1][3] = SDLK_d;
    if(Const::MaxPlayerAmount>2){
      Keys[2][0] = SDLK_t;
      Keys[2][1] = SDLK_g;
      Keys[2][2] = SDLK_f;
      Keys[2][3] = SDLK_h;
      if(Const::MaxPlayerAmount>3){
        Keys[3][0] = SDLK_i;
        Keys[3][1] = SDLK_k;
        Keys[3][2] = SDLK_j;
        Keys[3][3] = SDLK_l;
      }
    }
  }
  if(Const::MaxPlayerAmount>4){
    for(int SN=4; SN<Const::MaxPlayerAmount; SN++){
      Keys[SN][0] = SDLK_UP;
      Keys[SN][1] = SDLK_DOWN;
      Keys[SN][2] = SDLK_LEFT;
      Keys[SN][3] = SDLK_RIGHT;
    }
  }

  SnakeColor[0][0] = 0;
  SnakeColor[0][1] = 0;
  SnakeColor[0][2] = 255;
  if(Const::MaxPlayerAmount>1){
    SnakeColor[1][0] = 255;
    SnakeColor[1][1] = 0;
    SnakeColor[1][2] = 0;
    if(Const::MaxPlayerAmount>2){
      SnakeColor[2][0] = 0;
      SnakeColor[2][1] = 255;
      SnakeColor[2][2] = 0;
      if(Const::MaxPlayerAmount>3){
        SnakeColor[3][0] = 255;
        SnakeColor[3][1] = 0;
        SnakeColor[3][2] = 255;
      }
    }
  }
  if(Const::MaxPlayerAmount>4){
    for(int SN=4; SN<Const::MaxPlayerAmount; SN++){
      SnakeColor[SN][0] = 0;
      SnakeColor[SN][1] = 0;
      SnakeColor[SN][2] = 255;
    }
  }

  font = NULL;
  textColor = {255, 255, 255};
}

int GraphicFiles_Vars::TBSS(SDL_Surface *Text){
  for(int TextBoxSize=0; TextBoxSize*Const::Block_Size<(Text->w)+5; TextBoxSize++){
    if((TextBoxSize+1)*Const::Block_Size >= (Text->w)+5){
      return TextBoxSize+1;
    }
  }
  return 1; //Shouldn't get here
}

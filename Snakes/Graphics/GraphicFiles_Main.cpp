#include "GraphicFiles_Main.h"

bool GraphicFiles_Main::UpdateGameScreen(
	GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, Food& Food,
  LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake){
  if(!Loop.getExitState()){
    GF_Var.apply_surface(0, 0, GF_Var.BackGround[1], GF_Var.screen);

    GF_Var.apply_surface(0, 0, GF_Var.Borders[0], GF_Var.screen);
    GF_Var.apply_surface(Map.getMapSizeX()-1, 0, GF_Var.Borders[1], GF_Var.screen);
    GF_Var.apply_surface(1, Map.getMapSizeY()-1, GF_Var.Borders[2], GF_Var.screen);
    GF_Var.apply_surface(0, 1, GF_Var.Borders[3], GF_Var.screen);

    for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
      if(Snake.getCISIA(SN)){
        for(int TailSlot=0; TailSlot<Snake.getATL(SN); TailSlot++){
          if(Snake.getSnakeTailConnect(SN, TailSlot, 0) != 0){
            if(Snake.getSnakeTailConnect(SN, TailSlot, 1) != 0){
              if(
								Snake.getSnakeTailConnect(SN, TailSlot, 0) ==
								Snake.DirectionReverse(Snake.getSnakeTailConnect(SN, TailSlot, 1))){

                GF_Var.apply_surface(
									Snake.getTailRetract(SN, TailSlot, 1), Snake.getTailRetract(SN, TailSlot, 0),
                  GF_Var.SnakeImg[0][Snake.getSnakeTailConnect(SN, TailSlot, 0)-1], GF_Var.screen);
              }else if(Snake.getSnakeTailConnect(SN, TailSlot, 0) == 1){

                GF_Var.apply_surface(
									Snake.getTailRetract(SN, TailSlot, 1), Snake.getTailRetract(SN, TailSlot, 0),
                  GF_Var.SnakeImg[
										Snake.DirectionReverse(Snake.getSnakeTailConnect(SN, TailSlot, 1)) -
                    Snake.DirectionReverse(Snake.getSnakeTailConnect(SN, TailSlot, 0))][0],
                  GF_Var.screen);
              }else if(Snake.getSnakeTailConnect(SN, TailSlot, 0) == 2){

                GF_Var.apply_surface(
									Snake.getTailRetract(SN, TailSlot, 1), Snake.getTailRetract(SN, TailSlot, 0),
									GF_Var.SnakeImg[
										Snake.getSnakeTailConnect(SN, TailSlot, 1) -
										Snake.getSnakeTailConnect(SN, TailSlot, 0)][1],
									GF_Var.screen);
              }else if(Snake.getSnakeTailConnect(SN, TailSlot, 0) == 3){

                GF_Var.apply_surface(
									Snake.getTailRetract(SN, TailSlot, 1), Snake.getTailRetract(SN, TailSlot, 0),
                  GF_Var.SnakeImg[
										Snake.getSnakeTailConnect(SN, TailSlot, 0) -
                    Snake.DirectionReverse(Snake.getSnakeTailConnect(SN, TailSlot, 1))][2],
                  GF_Var.screen);
              }else if(Snake.getSnakeTailConnect(SN, TailSlot, 0) == 4){

                GF_Var.apply_surface(
									Snake.getTailRetract(SN, TailSlot, 1), Snake.getTailRetract(SN, TailSlot, 0),
                  GF_Var.SnakeImg[
										Snake.DirectionReverse(Snake.getSnakeTailConnect(SN, TailSlot, 0)) -
                    Snake.getSnakeTailConnect(SN, TailSlot, 1)][3],
                  GF_Var.screen);
              }
            }else{

              GF_Var.apply_surface(
								Snake.getTailRetract(SN, TailSlot, 1), Snake.getTailRetract(SN, TailSlot, 0),
                GF_Var.SnakeImg[4][Snake.getSnakeTailConnect(SN, TailSlot, 0)-1], GF_Var.screen);
            }
          }else{

            GF_Var.apply_surface(
							Snake.getTailRetract(SN, TailSlot, 1), Snake.getTailRetract(SN, TailSlot, 0),
              GF_Var.SnakeImg[3][Snake.DirectionReverse(Snake.getSnakeTailConnect(SN, TailSlot, 1))-1],
              GF_Var.screen);
          }
        }
      }
    }

    GF_Var.apply_surface(Food.getFoodPosX(), Food.getFoodPosY(), GF_Var.Food[0], GF_Var.screen);
    if(Food.getMFCIA()){
      GF_Var.apply_surface(Food.getFoodPos2X(), Food.getFoodPos2Y(), GF_Var.Food[Food.getFoodDirection()], GF_Var.screen);
    }

    for(int SN=0; SN<ORand.getSnakeAmount(); SN++){
      if(Snake.getCISIA(SN)){
        GMI_Var.makeButton(GF_Var, SN, GF_Var.Scores[SN]);
      }else{
        GMI_Var.makeButton(GF_Var, SN, GF_Var.Scores[SN], true);
      }
    }

    if(SDL_UpdateWindowSurface(GF_Var.Window) != 0){
      return false;
    }
    return true;
  }else{
    return true;
  }
}

bool GraphicFiles_Main::init_SDL(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var){

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return false;
	}

	GF_Var.Init_GF_Vars();

	GF_Var.Window = SDL_CreateWindow(
		"Snakes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		Const::Block_Size*10, Const::Block_Size*10, SDL_WINDOW_SHOWN);
	GF_Var.screen = SDL_GetWindowSurface(GF_Var.Window);

  if(TTF_Init() == -1){
    return false;
  }

  GF_Var.font = TTF_OpenFont("lucon.ttf", 12);
  if(GF_Var.font == NULL){
    return false;
  }

  GF_Var.Title = load_image(GF_Var, "Title.png");
  if(GF_Var.Title == NULL){
    return false;
  }
  setSpriteTransparency(&GF_Var.Title, GF_Var.Title);
  GF_Var.SpriteSheet = load_image(GF_Var, "SpriteSheet.png");
  if(GF_Var.SpriteSheet == NULL){
    return false;
  }

  SpriteSheetToSprite(2, 0, &GF_Var.BackGround[0], GF_Var); //Background tile
  GMI_Var.MenuChange(GF_Var, 10, 10);

  SpriteSheetToSprite(0, 2, &GF_Var.TextBox[0], GF_Var); //Left end of button
  SpriteSheetToSprite(1, 2, &GF_Var.TextBox[1], GF_Var); //Middle of button
  GF_Var.TextBox[2] = rotate_surface(GF_Var.TextBox[0]); //Right end of button
  GF_Var.TextBox[2] = rotate_surface(GF_Var.TextBox[2]); //Rotating it twice for a 180
  SpriteSheetToSprite(2, 2, &GF_Var.TextBox[3], GF_Var); //Single length button
  //Following 4 are the focused on versions of the buttons above
  GF_Var.TextBox[4] = CustomizeSpriteColor(GF_Var.TextBox[0], 0, 0, 255, GF_Var);
  GF_Var.TextBox[5] = CustomizeSpriteColor(GF_Var.TextBox[1], 0, 0, 255, GF_Var);
  GF_Var.TextBox[6] = CustomizeSpriteColor(GF_Var.TextBox[2], 0, 0, 255, GF_Var);
  GF_Var.TextBox[7] = CustomizeSpriteColor(GF_Var.TextBox[3], 0, 0, 255, GF_Var);

  SDL_FreeSurface(GF_Var.SpriteSheet);
  if(GF_Var.screen == NULL){
    return false;
  }
  if(GF_Var.BackGround[0] == NULL || GF_Var.BackGround[1] == NULL){
    return false;
  }
  for(int TextBoxNum=0; TextBoxNum<8; TextBoxNum++){
    if(GF_Var.TextBox[TextBoxNum] == NULL){
      return false;
    }
  }

  return true;
}

bool GraphicFiles_Main::init_SDL_GameLoop(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, Map& Map, OptionsRandom& ORand){

  SDL_FreeSurface(GF_Var.Title);

  GF_Var.SpriteSheet = load_image(GF_Var, "SpriteSheet.png");

  if(GF_Var.SpriteSheet == NULL){
    return false;
  }

  GMI_Var.MenuChange(GF_Var, Map.getMapSizeX(), Map.getMapSizeY()+1);

  for(int SnakePart=0; SnakePart<5; SnakePart++){

    SpriteSheetToSprite(SnakePart, 1, &GF_Var.SnakeImg[SnakePart][0], GF_Var);
    GF_Var.SnakeImg[SnakePart][3] = rotate_surface(GF_Var.SnakeImg[SnakePart][0]);
    GF_Var.SnakeImg[SnakePart][1] = rotate_surface(GF_Var.SnakeImg[SnakePart][3]);
    GF_Var.SnakeImg[SnakePart][2] = rotate_surface(GF_Var.SnakeImg[SnakePart][1]);

    setSpriteTransparency(&GF_Var.SnakeImg[SnakePart][0], GF_Var.SnakeImg[SnakePart][0]);
    setSpriteTransparency(&GF_Var.SnakeImg[SnakePart][1], GF_Var.SnakeImg[SnakePart][1]);
    setSpriteTransparency(&GF_Var.SnakeImg[SnakePart][2], GF_Var.SnakeImg[SnakePart][2]);
    setSpriteTransparency(&GF_Var.SnakeImg[SnakePart][3], GF_Var.SnakeImg[SnakePart][3]);
  }

  SpriteSheetToSprite(0, 0, &GF_Var.MidSurface[0], GF_Var);
  SpriteSheetToSprite(1, 0, &GF_Var.MidSurface[1], GF_Var);

  if(ORand.getBorderTeleport()){
    GF_Var.MidSurface[0] = CustomizeSpriteColor(GF_Var.MidSurface[0], 0, 0, 255, GF_Var);
    GF_Var.MidSurface[1] = CustomizeSpriteColor(GF_Var.MidSurface[1], 0, 0, 255, GF_Var);
  }else{
    GF_Var.MidSurface[0] = CustomizeSpriteColor(GF_Var.MidSurface[0], 255, 0, 0, GF_Var);
    GF_Var.MidSurface[1] = CustomizeSpriteColor(GF_Var.MidSurface[1], 255, 0, 0, GF_Var);
  }

  SpriteSheetToSprite(0, 0, &GF_Var.Borders[0], GF_Var, Map.getMapSizeX()-1, 1);
  GF_Var.apply_surface(0, 0, GF_Var.MidSurface[1], GF_Var.Borders[0]);
  for(int Block=1; Block<Map.getMapSizeX(); Block++){
    GF_Var.apply_surface(Block, 0, GF_Var.MidSurface[0], GF_Var.Borders[0]);
  }
  setSpriteTransparency(&GF_Var.Borders[0], GF_Var.Borders[0]);
  GF_Var.MidSurface[0] = rotate_surface(GF_Var.MidSurface[0]);
  GF_Var.MidSurface[1] = rotate_surface(GF_Var.MidSurface[1]);

  SpriteSheetToSprite(0, 0, &GF_Var.Borders[1], GF_Var, 1, Map.getMapSizeY()-1);
  GF_Var.apply_surface(0, 0, GF_Var.MidSurface[1], GF_Var.Borders[1]);
  for(int Block=1; Block<Map.getMapSizeY(); Block++){
    GF_Var.apply_surface(0, Block, GF_Var.MidSurface[0], GF_Var.Borders[1]);
  }
  setSpriteTransparency(&GF_Var.Borders[1], GF_Var.Borders[1]);
  GF_Var.MidSurface[0] = rotate_surface(GF_Var.MidSurface[0]);
  GF_Var.MidSurface[1] = rotate_surface(GF_Var.MidSurface[1]);

  SpriteSheetToSprite(0, 0, &GF_Var.Borders[2], GF_Var, Map.getMapSizeX()-1, 1);
  GF_Var.apply_surface(Map.getMapSizeX()-2, 0, GF_Var.MidSurface[1], GF_Var.Borders[2]);
  for(int Block=0; Block<Map.getMapSizeX()-2; Block++){
    GF_Var.apply_surface(Block, 0, GF_Var.MidSurface[0], GF_Var.Borders[2]);
  }
  setSpriteTransparency(&GF_Var.Borders[2], GF_Var.Borders[2]);
  GF_Var.MidSurface[0] = rotate_surface(GF_Var.MidSurface[0]);
  GF_Var.MidSurface[1] = rotate_surface(GF_Var.MidSurface[1]);

  SpriteSheetToSprite(0, 0, &GF_Var.Borders[3], GF_Var, 1, Map.getMapSizeY()-1);
  GF_Var.apply_surface(0, Map.getMapSizeY()-2, GF_Var.MidSurface[1], GF_Var.Borders[3]);
  for(int Block=0; Block<Map.getMapSizeY()-2; Block++){
    GF_Var.apply_surface(0, Block, GF_Var.MidSurface[0], GF_Var.Borders[3]);
  }
  setSpriteTransparency(&GF_Var.Borders[3], GF_Var.Borders[3]);
  SDL_FreeSurface(GF_Var.MidSurface[0]);
  SDL_FreeSurface(GF_Var.MidSurface[1]);

  SpriteSheetToSprite(3, 0, &GF_Var.Food[0], GF_Var);
  setSpriteTransparency(&GF_Var.Food[0], GF_Var.Food[0]);

  SpriteSheetToSprite(4, 0, &GF_Var.Food[1], GF_Var);
  GF_Var.Food[4] = rotate_surface(GF_Var.Food[1]);
  GF_Var.Food[2] = rotate_surface(GF_Var.Food[4]);
  GF_Var.Food[3] = rotate_surface(GF_Var.Food[2]);
  setSpriteTransparency(&GF_Var.Food[1], GF_Var.Food[1]);
  setSpriteTransparency(&GF_Var.Food[2], GF_Var.Food[2]);
  setSpriteTransparency(&GF_Var.Food[3], GF_Var.Food[3]);
  setSpriteTransparency(&GF_Var.Food[4], GF_Var.Food[4]);

  SDL_FreeSurface(GF_Var.SpriteSheet);

  if(GF_Var.BackGround == NULL){
    return false;
  }
  for(int SnakePart=0; SnakePart<5; SnakePart++){
    for(int RotatedPart=0; RotatedPart<4; RotatedPart++){
      if(GF_Var.SnakeImg[SnakePart][RotatedPart] == NULL){
        return false;
      }
    }
  }
  for(int Border=0; Border<4; Border++){
    if(GF_Var.Borders[Border] == NULL){
      return false;
    }
  }
  for(int FoodImg=0; FoodImg<5; FoodImg++){
    if(GF_Var.Food[FoodImg] == NULL){
      return false;
    }
  }
  if(GF_Var.screen == NULL){
    return false;
  }

  return true;
}

bool GraphicFiles_Main::quit_SDL_GameLoop(GraphicFiles_Vars& GF_Var){

  for(int Border=0; Border<4; Border++){
    SDL_FreeSurface(GF_Var.Borders[Border]);
  }
  for(int SnakePart=0; SnakePart<5; SnakePart++){
    for(int RotatedPart=0; RotatedPart<4; RotatedPart++){
      SDL_FreeSurface(GF_Var.SnakeImg[SnakePart][RotatedPart]);
    }
  }
  for(int Food=0; Food<5; Food++){
    SDL_FreeSurface(GF_Var.Food[Food]);
  }

  GF_Var.Title = load_image(GF_Var, "Title.png");
  if(GF_Var.Title == NULL){
    return false;
  }
  setSpriteTransparency(&GF_Var.Title, GF_Var.Title);

  return true;
}

void GraphicFiles_Main::quit_SDL(GraphicFiles_Vars& GF_Var, OptionsRandom& ORand){

  SDL_FreeSurface(GF_Var.BackGround[0]);
  SDL_FreeSurface(GF_Var.BackGround[1]);
  SDL_FreeSurface(GF_Var.Title);
  for(int TextBoxNum=0; TextBoxNum<8; TextBoxNum++){
    SDL_FreeSurface(GF_Var.TextBox[TextBoxNum]);
  }

  TTF_Quit();
  SDL_Quit();
}

SDL_Surface *GraphicFiles_Main::load_image(GraphicFiles_Vars& GF_Var, std::string filename){

	SDL_Surface* optimizedSurface = NULL;

	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());

  optimizedSurface = SDL_ConvertSurface(loadedSurface, GF_Var.screen->format, NULL);

  SDL_FreeSurface(loadedSurface);

	return optimizedSurface;
}

void GraphicFiles_Main::SpriteSheetToSprite(int X, int Y, SDL_Surface **Sprite, GraphicFiles_Vars& GF_Var, int SizeX, int SizeY){

  *Sprite = SDL_CreateRGBSurface(SDL_SWSURFACE, SizeX*Const::Block_Size, SizeY*Const::Block_Size, Const::SCREEN_BPP,
                                 GF_Var.SpriteSheet->format->Rmask, GF_Var.SpriteSheet->format->Gmask,
                                 GF_Var.SpriteSheet->format->Bmask, GF_Var.SpriteSheet->format->Amask);

  GF_Var.Sprite.x = Const::Block_Size*X;
  GF_Var.Sprite.y = Const::Block_Size*Y;
  GF_Var.Sprite.w = Const::Block_Size;
  GF_Var.Sprite.h = Const::Block_Size;

  for(int SurfaceX=0; SurfaceX<SizeX; SurfaceX++){
    for(int SurfaceY=0; SurfaceY<SizeY; SurfaceY++){
      GF_Var.apply_surface(SurfaceX, SurfaceY, GF_Var.SpriteSheet, *Sprite, &GF_Var.Sprite);
    }
  }
}

void GraphicFiles_Main::setSpriteTransparency(SDL_Surface **Sprite, SDL_Surface *Format){
  SDL_SetColorKey(*Sprite, SDL_TRUE, SDL_MapRGB(Format->format, 0, 0xFF, 0xFF));
}

SDL_Surface *GraphicFiles_Main::CustomizeSpriteColor(SDL_Surface *surface, Uint8 Red, Uint8 Green, Uint8 Blue, GraphicFiles_Vars& GF_Var){

  SDL_Surface *Colored = NULL;
  SDL_Surface *IntoColor = NULL;

  if(surface->flags){
    Colored = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
                                   surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0);
    IntoColor = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
                                     surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0);
  }else{
    Colored = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
                                   surface->format->Rmask, surface->format->Gmask, surface->format->Bmask,
                                   surface->format->Amask);
    IntoColor = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
                                     surface->format->Rmask, surface->format->Gmask, surface->format->Bmask,
                                     surface->format->Amask);
  }

  Colored = surface;
  SDL_FillRect(IntoColor, &IntoColor->clip_rect, SDL_MapRGB(IntoColor->format, Red, Green, Blue));
  SDL_SetColorKey(Colored, SDL_TRUE, SDL_MapRGB(Colored->format, 255, 255, 255));
  GF_Var.apply_surface(0, 0, Colored, IntoColor);

  return IntoColor;
}

SDL_Surface *GraphicFiles_Main::rotate_surface(SDL_Surface *surface){

  SDL_Surface *rotated = NULL;
  Uint32 pixel = NULL;

  if(surface->flags){
    rotated = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
                                   surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0);
  }else{
    rotated = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
                                   surface->format->Rmask, surface->format->Gmask, surface->format->Bmask,
                                   surface->format->Amask);
  }

  if(SDL_MUSTLOCK(surface)){
    SDL_LockSurface(surface);
  }

  if(rotated->w == rotated->h){
    for(int x = 0, rx = rotated->w - 1; x < rotated->w; x++, rx--)
    {
      for(int y = 0, ry = rotated->h - 1; y < rotated->h; y++, ry--)
      {
        pixel = get_pixel32(surface, x, y);

        put_pixel32(rotated, ry, x, pixel);
      }
    }
  }else{
    rotated = surface;
  }

  if(SDL_MUSTLOCK(surface)){
    SDL_UnlockSurface(surface);
  }

  if(surface->flags){
    SDL_SetColorKey(rotated, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));
  }

  return rotated;
}

Uint32 GraphicFiles_Main::get_pixel32(SDL_Surface *surface, int x, int y){

  Uint32 *pixels = (Uint32 *)surface->pixels;

  return pixels[(y * surface->w) + x];
}

void GraphicFiles_Main::put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel){

  Uint32 *pixels = (Uint32*)surface->pixels;

  pixels[(y * surface->w) + x] = pixel;
}

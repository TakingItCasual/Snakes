#ifndef GRAPHICFILES_MAIN_H
#define GRAPHICFILES_MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include "../Variables/Food.h"
#include "../Systems/GMI_Vars.h"
#include "../Graphics/GraphicFiles_Vars.h"
#include "../Variables/InternalRandom.h"
#include "../Variables/LoopControl.h"
#include "../Variables/Map.h"
#include "../Variables/OptionsRandom.h"
#include "../Variables/Snake.h"
#include "../Variables/Timer.h"

#include "../Variables/Constants.h"

class GraphicFiles_Main
{
  public:
    bool UpdateGameScreen(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, Food& Food,
                          LoopControl& Loop, Map& Map, OptionsRandom& ORand, Snake& Snake);
    bool init_SDL(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var);
    bool init_SDL_GameLoop(GMI_Vars& GMI_Var, GraphicFiles_Vars& GF_Var, Map& Map, OptionsRandom& ORand);
    bool quit_SDL_GameLoop(GraphicFiles_Vars& GF_Var);
    void quit_SDL(GraphicFiles_Vars& GF_Var, OptionsRandom& ORand);

  private:
    SDL_Surface *load_image(GraphicFiles_Vars& GF_Var, std::string filename);
    void SpriteSheetToSprite(int X, int Y, SDL_Surface **Sprite, GraphicFiles_Vars& GF_Var, int SizeX = 1, int SizeY = 1);
    void setSpriteTransparency(SDL_Surface **Sprite, SDL_Surface *Format);
    SDL_Surface *CustomizeSpriteColor(SDL_Surface *surface, Uint8 Red, Uint8 Green, Uint8 Blue, GraphicFiles_Vars& GF_Var);
    SDL_Surface *rotate_surface(SDL_Surface *surface);
    Uint32 get_pixel32(SDL_Surface *surface, int x, int y);
    void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);
};

#endif // GRAPHICFILES_MAIN_H

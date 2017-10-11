#ifndef GRAPHICFILES_VARS_H
#define GRAPHICFILES_VARS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

#include <sstream>

#include "../Variables/Constants.h"

class GraphicFiles_Vars
{
  public:
    void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL,
                       int ExtraX = 0, int ExtraY = 0); //Your standard apply surface function
    void setBackgroundSize(int ScreenSizeX, int ScreenSizeY); //Handles creating a background sized to the window
    std::string IntToString(int Num); //Converts an int into a string
    void Init_GF_Vars(); //Initializes all the SDL specific types
    int TBSS(SDL_Surface *Text); //TBSS = TextBoxSizeSetter; Used with variable length text boxes. Not exact, or else I would have used it everywhere.

    SDL_Window* Window; //The main window
    SDL_Surface *screen; //The main screen, what everything gets blitted to
    SDL_Surface *SpriteSheet; //Gets sprites from an image and sets to surfaces
    SDL_Surface *BackGround[2]; //Background grass, first is the initial square, second is background sized
    SDL_Surface *Title; //Title; "Snakes!"
    SDL_Surface *Borders[4]; //Map borders in the game
    SDL_Surface *SnakeImg[5][4]; //Snake sprites
    SDL_Surface *Food[5]; //Food; the apple and the worms.
    SDL_Surface *TextBox[8]; //Text boxes for buttons and scores
    SDL_Surface *Scores[Const::MaxPlayerAmount]; //Scores in the game
    SDL_Surface *Text[12]; //Menu and other text
    SDL_Surface *MidSurface[2];

    SDL_Rect Sprite;

    SDL_Event event;
    SDL_Keycode Keys[Const::MaxPlayerAmount][4];
    Uint8 SnakeColor[Const::MaxPlayerAmount][3];

    TTF_Font *font;
    SDL_Color textColor;
};

#endif // GRAPHICFILES_VARS_H

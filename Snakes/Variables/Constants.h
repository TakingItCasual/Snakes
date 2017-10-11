#ifndef CONSTANTS_H
#define CONSTANTS_H

//For more configuration see "Functions/Initializers.cpp"

class Const{
  public:
    static const int MaxMapSizeX = 62; //Do not set below 22
    static const int MaxMapSizeY = 62; //Do not set below 22
    static const int MaxPlayerAmount = 4; //Do not set below 2

    static const int SCREEN_BPP = 32; //bits per pixel; for SDL
    static const int Block_Size = 16; //Block size value for SDL

    static const int KeyRepeatDelay = 250; //Amount of time button has to be held down before it automatically loops
    static const int KeyRepeatInterval = 100; //How fast it automatically loops after being held down for enough time
};

#endif // CONSTANTS_H

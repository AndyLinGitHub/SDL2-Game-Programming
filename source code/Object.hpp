#ifndef Object_hpp
#define Object_hpp
#include <stdio.h>
#include <iostream>
class Object{
public:
    //Maximum axis velocity
    static const int VEL = 15;
    
    //Checking for flip
    SDL_RendererFlip texture_flip = SDL_FLIP_NONE;
    
    //Ｆunction for getting tne inner information
    int getPosX() {return mPosX;}
    int getPosY() {return mPosY;}
    SDL_Rect& getRect(int n) { if (n == 1) return mCollider1; else return mCollider2;}
    void set_cam(int x, int y) {camX = x; camY = y;}
    
protected:
    //The X and Y offsets of the Object
    double mPosX, mPosY;
    
    //The velocity of the Object
    double mVelX, mVelY;
    int camX, camY;
    
    //Object collision box
    SDL_Rect mCollider1;
    SDL_Rect mCollider2;

    LTexture *currentTexture;
};
#endif /* Object_hpp */

#ifndef Button_hpp
#define Button_hpp

#include <stdio.h>
#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include "LTexture.hpp"
enum buttonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 1,
    BUTTON_SPRITE_MOUSE_UP = 0,
    BUTTON_SPRITE_TOTAL = 4
};
class Button
{
public:
    int state = 0;
    //Initializes internal variables
    Button(std::string path1, std::string path2, int st);
    ~Button();
    
    //Sets top left position
    void setPosition( int x, int y );
    
    //Handles mouse event
    void handleEvent( SDL_Event* e, int &current_state);
    
    //Shows button sprite
    void render();
    int getCurrentsprite() {return mcurrentsprite;}
    
    
private:
    //Top left position
    SDL_Point mPosition;
    
    LTexture button_texture[2];
    
    //Currently used global sprite
    buttonSprite mcurrentsprite;
};
#endif /* Button_hpp */

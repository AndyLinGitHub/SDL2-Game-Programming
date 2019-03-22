#ifndef _0_Timer_hpp
#define _0_Timer_hpp

#include <stdio.h>
#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>
#include "LTexture.hpp"
#include "Vocabulary.hpp"
class Timer
{
public:
    //Initializes internal variables
    Timer();
    ~Timer();
    
    //Sets position
    void setPosition( int x, int y );
    
    //Handles event
    void handleEvent( SDL_Event* e, int &current_state);
    
    //Show vocabulary
    void render(int level_index, int voc_count, Vocabulary voc);
    
private:
    SDL_Point mPosition;
    LTexture timer_texture[11];
    LTexture current_voc;
};
#endif /* _0_Timer_hpp */

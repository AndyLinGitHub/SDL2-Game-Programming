extern const int BUTTON_WIDTH;
extern const int BUTTON_HEIGHT;
extern const int TOTAL_BUTTONS;
extern bool isPause;
#include "Button.hpp"
#include <SDL_mixer.h>
extern Mix_Chunk *gButton_click;
Button::Button(std::string path1, std::string path2,int st)
{
    mPosition.x = 0;
    mPosition.y = 0;
    button_texture[0].loadFromFile(path1.c_str());
    button_texture[1].loadFromFile(path2.c_str());
    mcurrentsprite = BUTTON_SPRITE_MOUSE_OUT;
    state = st;
}

Button:: ~Button(){
    button_texture[0].free();
    button_texture[1].free();
}
void Button::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}
void Button::handleEvent( SDL_Event* e , int &current_state)
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
        
        //Check if mouse is in button
        bool inside = true;
        
        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + BUTTON_WIDTH )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + BUTTON_HEIGHT )
        {
            inside = false;
        }
        
        //Mouse is outside button
        if( !inside )
        {
            mcurrentsprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        //Mouse is inside button //flag
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
                case SDL_MOUSEMOTION:
                    mcurrentsprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                    
                case SDL_MOUSEBUTTONDOWN:
                    mcurrentsprite = BUTTON_SPRITE_MOUSE_DOWN;
                    Mix_PlayChannel( -1, gButton_click, 0 );
                    
                    break;
                    
                case SDL_MOUSEBUTTONUP:
                {mcurrentsprite = BUTTON_SPRITE_MOUSE_UP;
                    current_state = state;
                    isPause = false;
                    break;}
            }
        }
    }
}
void Button::render()
{
    //Show current button sprite
    button_texture[ mcurrentsprite ].render( mPosition.x, mPosition.y);
}


#include "10_Timer.hpp"
#include "Vocabulary.hpp"
#include<SDL2_mixer/SDL_mixer.h>
extern SDL_Renderer* gRenderer;
extern LTexture gBGTexture;
extern SDL_Color textColor ;
extern Mix_Chunk *gButton_click;

Timer::Timer()
{
    mPosition.x = 380;
    mPosition.y = 100;
    timer_texture[9].loadFromFile("1.png");
    timer_texture[8].loadFromFile("2.png");
    timer_texture[7].loadFromFile("3.png");
    timer_texture[6].loadFromFile("4.png");
    timer_texture[5].loadFromFile("5.png");
    timer_texture[4].loadFromFile("6.png");
    timer_texture[3].loadFromFile("7.png");
    timer_texture[2].loadFromFile("8.png");
    timer_texture[1].loadFromFile("9.png");
    timer_texture[0].loadFromFile("10.png");
    timer_texture[10].loadFromFile("start!!.png");
}

Timer:: ~Timer(){
    timer_texture[0].free();
    timer_texture[1].free();
    timer_texture[2].free();
    timer_texture[3].free();
    timer_texture[4].free();
    timer_texture[6].free();
    timer_texture[7].free();
    timer_texture[8].free();
    timer_texture[9].free();
    timer_texture[10].free();
}
void Timer::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}
void Timer::handleEvent( SDL_Event* e , int &current_state)
{
    
}
void Timer::render(int level_index, int voc_count, Vocabulary voc)
{
    SDL_Event E;
    int render_x = (-voc.voc_size[level_index][voc_count])* 30;
    current_voc.loadFromRenderedText(voc.font_array[level_index][voc_count],textColor);
    for(int i = 0 ; i < 11 ; i++)
    {   if (i !=  0)Mix_PlayChannel( -1, gButton_click, 0 );
        SDL_RenderClear( gRenderer );
        if (i != 10)
        {
            gBGTexture.render(0,0);current_voc.render(480 + render_x ,300);timer_texture[i].render(mPosition.x, mPosition.y);
            SDL_RenderPresent( gRenderer );SDL_Delay(1000);
            
        }
        else
        {
            gBGTexture.render(0,0);current_voc.render(480 + render_x,300);timer_texture[i].render(mPosition.x, mPosition.y);
            SDL_RenderPresent( gRenderer );SDL_Delay(100);}
        while( SDL_PollEvent( &E ) != 0 )
        {
            
        }
        
    }
    current_voc.free();
}


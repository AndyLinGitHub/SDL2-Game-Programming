#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "initailize.hpp"
#include "LTexture.hpp"
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <typeinfo>
//#include <cxxabi.h>
#include "Object.hpp"
extern LTexture gBGTexture;
extern LTexture gMENUTexture;
extern LTexture gHELPTexture;
extern LTexture gGAMEOVERTexture;
extern LTexture gLEVELCHOOSETexture;
extern LTexture gPAUSETexture;
extern LTexture gEXITTexture;
extern LTexture gGOALTexture;
extern LTexture texture_letter[26];
extern Mix_Music *gMusic;
extern Mix_Chunk *gButton_click;
extern Mix_Chunk *gEnemy_dead;
extern Mix_Chunk *gplayer_shoot;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Rect camera;
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

extern TTF_Font *gFont;
bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "Hunting V", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
                
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }
    
    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;
    if( !gBGTexture.loadFromFile( "bg.png" ))
    {
        printf( "Failed to load background texture!\n" );
        success = false;
    }
    //Open the font
    gFont = TTF_OpenFont( "game_font3.ttf", 80);
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    texture_letter[0].loadFromFile("A.png");
    texture_letter[1].loadFromFile("B.png");
    texture_letter[2].loadFromFile("C.png");
    texture_letter[3].loadFromFile("D.png");
    texture_letter[4].loadFromFile("E.png");
    texture_letter[5].loadFromFile("F.png");
    texture_letter[6].loadFromFile("G.png");
    texture_letter[7].loadFromFile("H.png");
    texture_letter[8].loadFromFile("I.png");
    texture_letter[9].loadFromFile("J.png");
    texture_letter[10].loadFromFile("K.png");
    texture_letter[11].loadFromFile("L.png");
    texture_letter[12].loadFromFile("M.png");
    texture_letter[13].loadFromFile("N.png");
    texture_letter[14].loadFromFile("O.png");
    texture_letter[15].loadFromFile("P.png");
    texture_letter[16].loadFromFile("Q.png");
    texture_letter[17].loadFromFile("R.png");
    texture_letter[18].loadFromFile("S.png");
    texture_letter[19].loadFromFile("T.png");
    texture_letter[20].loadFromFile("U.png");
    texture_letter[21].loadFromFile("V.png");
    texture_letter[22].loadFromFile("W.png");
    texture_letter[23].loadFromFile("X.png");
    texture_letter[24].loadFromFile("Y.png");
    texture_letter[25].loadFromFile("Z.png");
    gHELPTexture.loadFromFile("help.png");
    gMENUTexture.loadFromFile("menu.png");
    gGAMEOVERTexture.loadFromFile("gameover.png");
    gLEVELCHOOSETexture.loadFromFile("choose_level.png");
    gPAUSETexture.loadFromFile("pause.png");
    gEXITTexture.loadFromFile("exit.png");
    gGOALTexture.loadFromFile("goal.png");
    
    gMusic = Mix_LoadMUS( "game.wav" );
    gButton_click = Mix_LoadWAV( "button_0_2.wav" );
    if( gButton_click == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    gplayer_shoot = Mix_LoadWAV( "player_shoot.wav" );
    if( gButton_click == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
   gEnemy_dead = Mix_LoadWAV( "enemy_death.wav" );
    if( gButton_click == NULL )
    {
        printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    
    
    
    
    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    texture_letter[0].free();
    texture_letter[1].free();
    texture_letter[2].free();
    texture_letter[3].free();
    texture_letter[4].free();
    texture_letter[5].free();
    texture_letter[6].free();
    texture_letter[7].free();
    texture_letter[8].free();
    texture_letter[9].free();
    texture_letter[10].free();
    texture_letter[11].free();
    texture_letter[12].free();
    texture_letter[13].free();
    texture_letter[14].free();
    texture_letter[15].free();
    texture_letter[16].free();
    texture_letter[17].free();
    texture_letter[18].free();
    texture_letter[19].free();
    texture_letter[20].free();
    texture_letter[21].free();
    texture_letter[22].free();
    texture_letter[23].free();
    texture_letter[24].free();
    texture_letter[25].free();
    gBGTexture.free();
    gMENUTexture.free();
    gHELPTexture.free();
    gPAUSETexture.free();
    gEXITTexture.free();
    gGOALTexture.free();
    
    //Free the music
    Mix_FreeChunk( gButton_click );
    gButton_click = NULL;
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect & b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}


LTimer::LTimer()
{
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;
    
    mPaused = false;
    mStarted = false;
}

void LTimer::start()
{
    //Start the timer
    mStarted = true;
    
    //Unpause the timer
    mPaused = false;
    
    //Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop()
{
    //Stop the timer
    mStarted = false;
    
    //Unpause the timer
    mPaused = false;
    
    //Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    //If the timer is running and isn't already paused
    if (mStarted && !mPaused)
    {
        //Pause the timer
        mPaused = true;
        
        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    //If the timer is running and paused
    if (mStarted && mPaused)
    {
        //Unpause the timer
        mPaused = false;
        
        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        
        //Reset the paused ticks
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
    //The actual timer time
    Uint32 time = 0;
    
    //If the timer is running
    if (mStarted)
    {
        //If the timer is paused
        if (mPaused)
        {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    
    return time;
}

bool LTimer::isStarted()
{
    //Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused()
{
    //Timer is running and paused
    return mPaused && mStarted;
}



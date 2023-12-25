#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include "Enemy.hpp"
#include "shotgun.hpp"
#include "initailize.hpp"
#include "Bullet.hpp"
#include "LTexture.hpp"
#include "character.hpp"
#include "Object.hpp"
#include "Enemy_Bullet.hpp"
#include "Button.hpp"
#include <iostream>
#include "10_Timer.hpp"
#include "Vocabulary.hpp"
#define SIZE_OF_ARRAY(ary) sizeof(ary) / sizeof(*ary)


int current_state = 0;

//The dimensions of the level
const int LEVEL_WIDTH = 1440;
const int LEVEL_HEIGHT = 1080;

//Screen dimension constants
extern const int SCREEN_WIDTH = 960;
extern const int SCREEN_HEIGHT = 720;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//amount of the enemys
#define enemys_amount 26
#define bullets_amount 10

//pointer arrays for newing bulltes and enemys
Bullet* bullets[bullets_amount] = {};
Enemy* enemys[enemys_amount] = {};
Enemy_Bullet* enemy_bullets[enemys_amount] = {};

// counter to record the amounts of exist enemys and bullets
int enemys_count = 0;
int bullets_count = 0;

//The camera area
SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

//the array to handel all the walls of background
SDL_Rect walls[12];

//the window
SDL_Window* gWindow;

//The window renderer
SDL_Renderer* gRenderer;

//Globally used font
TTF_Font *gFont = NULL;

SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

//The music that will be played
Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *gButton_click = NULL;
Mix_Chunk *gEnemy_dead = NULL;
Mix_Chunk *gplayer_shoot = NULL;

//the background texture
LTexture gBGTexture;
LTexture gMENUTexture;
LTexture gHELPTexture;
LTexture gGAMEOVERTexture;
LTexture gLEVELCHOOSETexture;
LTexture gPAUSETexture;
LTexture gEXITTexture;
LTexture gGOALTexture;

LTexture texture_letter[26];

extern const int BUTTON_WIDTH = 190;
extern const int BUTTON_HEIGHT = 64;
extern const int TOTAL_BUTTONS = 4;

bool isPause = false;

Vocabulary voc;
//main loop

enum gmaing_state{Menu = 0, Level1 = 1, Level2 = 2, Level3 = 3,Help = 4, Quit = 5, LevelChoose = 6};
int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            //player
            Character John;
            
            //player's gun
            Shot_gun gun(John);
            
            
            //The frames per second timer
            LTimer fpsTimer;
            
            //The frames per second cap timer
            LTimer capTimer;
            
            //Start counting frames per second
            int countedFrames = 0;
            fpsTimer.start();
            
            Button gStartButton("start1.png","start2.png", 6);
            Button gHelpButton("help1.png","help2.png",4);
            Button gQuitButton("quit1.png","quit2.png",5);
            Button gBackButton("back.png","back.png",0);
            Button gLevel1Button("level12.png","level11.png", 1);
            Button gLevel2Button("level22.png","level21.png", 2);
            Button gLevel3Button("level32.png","level31.png", 3);
            
            //Set buttons in corners
            int xx=395;
            int yy=350;
            
            gStartButton.setPosition( xx, yy );
            gHelpButton.setPosition( xx, yy+100 );
            gQuitButton.setPosition( xx, yy+200 );
            gBackButton.setPosition(10, 10);
            gLevel1Button.setPosition(80, 330);
            gLevel2Button.setPosition(380, 330);
            gLevel3Button.setPosition(680, 330);
            
            Timer t;
            bool timed = false;
            
            
            //Set the wall
            SDL_Rect wall; wall.x = 499; wall.y = 953; wall.w = 495; wall.h = 1;
            SDL_Rect wall2; wall2.x = 440; wall2.y = 933; wall2.w = 615; wall2.h = 1;
            SDL_Rect wall3; wall3.x = 45; wall3.y = 792; wall3.w = 325; wall3.h = 1;
            SDL_Rect wall4; wall4.x = 1011; wall4.y = 792; wall4.w = 250; wall4.h = 1;
            SDL_Rect wall5; wall5.x = 423; wall5.y = 668; wall5.w = 500; wall5.h = 1;
            SDL_Rect wall6; wall6.x = 138; wall6.y = 524; wall6.w = 250; wall6.h = 1;
            SDL_Rect wall7; wall7.x = 1016; wall7.y = 525; wall7.w = 378; wall7.h = 1;
            SDL_Rect wall8; wall8.x = 442; wall8.y = 394; wall8.w = 507; wall8.h = 1;
            SDL_Rect wall9; wall9.x = 48; wall9.y = 269; wall9.w = 408; wall9.h = 1;
            SDL_Rect wallx; wallx.x = 1023; wallx.y = 269; wallx.w = 249; wallx.h = 1;
            SDL_Rect wallL; wallL.x = 0; wallL.y = 0; wallL.w = 43; wallL.h = 1;
            SDL_Rect wallR; wallR.x = 1397; wallR.y = 0; wallR.w = 43; wallR.h = 1;
            walls[0] = wall; walls[1] = wall2; walls[2] = wall3;
            walls[3] = wall4; walls[4] = wall5; walls[5] = wall6;
            walls[6] = wall7; walls[7] = wall8; walls[8] = wall9;
            walls[9] = wallx; walls[10] = wallL; walls[11] = wallR;
            
            int letter_count = 0;
            int* letter_index [13] = {};
            int voc_count = 0;
            Mix_PlayMusic( gMusic, -1 );
            //While application is running
            while( !quit )
            {
                
                if (current_state == Menu){
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        gStartButton.handleEvent(&e, current_state);
                        gHelpButton.handleEvent(&e, current_state);
                        gQuitButton.handleEvent(&e, current_state);
                    }
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                    SDL_RenderClear( gRenderer );
                    gMENUTexture.render(0, 0);
                    gStartButton.render();
                    gHelpButton.render();
                    gQuitButton.render();
                    SDL_RenderPresent( gRenderer );
                    John.initialize_cha();
                    letter_count = 0;
                    voc_count = 0;
                    for(int i = 0; i < letter_count ; i++) {delete letter_index[i]; letter_index[i] = NULL;}
                    SDL_ShowCursor(SDL_ENABLE);
                }
                else if (current_state == LevelChoose){
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        gLevel1Button.handleEvent(&e, current_state);
                        gLevel2Button.handleEvent(&e, current_state);
                        gLevel3Button.handleEvent(&e, current_state);
                        gBackButton.handleEvent(&e, current_state);
                        if (current_state == LevelChoose) {John.health = 145;timed = false;}
                    }
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                    SDL_RenderClear( gRenderer );
                    gLEVELCHOOSETexture.render(0, 0);
                    gLevel1Button.render();
                    gLevel2Button.render();
                    gLevel3Button.render();
                    gBackButton.render();
                    SDL_RenderPresent( gRenderer );
                }
                else if (current_state == Level1 || current_state == Level2 || current_state == Level3){
                    int level_index = current_state - 1;
                    if (!timed){
                        t.render(level_index,voc_count,voc);
                        timed = true;
                        John.health = 145;
                    }
                //hidind the mouse cursor
                SDL_ShowCursor(SDL_DISABLE);
                //Start cap timer
                capTimer.start();
                
                float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
                if( avgFPS > 2000000 )
                {
                    avgFPS = 0;
                }
                //Handle events on queue
                
                //checking for the collision between the player and walls
                for (int i = 0; i < 11 ; i++)
                {
                    if (checkCollision(John.getRect(1), walls[i]))
                    {
                        John.fall_flag = false;
                        //John.jump_flag = false;
                        break;
                    }
                    else John.fall_flag = true;
                }
                
                //checking for the collision between the player and enemys
                for (int i = 0; i < enemys_amount ; i++)
                {   if (enemys[i] != NULL){
                    if (checkCollision(John.getRect(2), enemys[i] -> getRect(2)))
                    {
                        if(John.health >= 0) John.health -= 0.05;
                        
                    }
                    else continue;
                }
                }
                
                //checking for the collision between the player and enemys' bullet
                for (int i = 0; i < enemys_amount ; i++)
                {   if (enemys[i] != NULL && enemy_bullets[i] != NULL){
                    if (checkCollision(John.getRect(2), enemy_bullets[i] -> getRect(2)))
                    {
                        if(John.health >= 0) John.health -= 0.1;
                        delete enemy_bullets[i];
                        enemy_bullets[i] = NULL;
                        
                    }
                    else continue;
                }
                }
                //checking for the collision between enemys and walls
                for(int j = 0 ;j < enemys_amount;j++)
                {
                    if (enemys[j] != NULL) {
                        for (int i = 0; i < 11 ; i++)
                        {
                            if (checkCollision(enemys[j] -> getRect(1), walls[i]))
                            {enemys[j] -> fall_flag = false; break;}
                            else enemys[j] -> fall_flag = true;
                        }
                    }
                }
                
                //checking for the collision between the enemys and bullets
                for(int j = 0 ;j < enemys_amount;j++)
                {
                    if (enemys[j] != NULL) {
                        for (int i = 0; i < bullets_amount ; i++)
                        {   if (bullets[i] != NULL && enemys[j] -> dead_flag == false){
                            if (checkCollision(enemys[j] -> getRect(2), bullets[i] -> getRect(1)))
                            {
                                Mix_PlayChannel( -1, gEnemy_dead, 0 );
                                enemys[j] -> dead_flag = true;
                                if (letter_count <= voc.voc_size[level_index][voc_count]){
                                if ((enemys[j] -> getIndex()) == voc.voc_level[level_index][voc_count][letter_count])
                                {
                                    letter_index[letter_count]  = new int (enemys[j] -> getIndex());
                                    letter_count ++;
                                }
                                else John.health -= 0.5;
                                }
                                delete bullets[i];
                                bullets[i] = NULL;
                                --bullets_count;
                                break;
                            }
                            else enemys[j] -> dead_flag = false;
                        }
                        }
                    }
                }
                
                //std::cout << John.fall_flag << std::endl;
                
                //adding enemys and enemys' bullets
                if (enemys_count < enemys_amount)
                {
                for(int i = 0 ;i < enemys_amount;i++)
                {
                    if (enemys[i] == NULL) {enemys[i] = new Enemy(i);}
                }
                  ++ enemys_count;
                }
                
                    for(int i = 0 ;i < enemys_amount;i++)
                    {
                        if (enemys[i] != NULL && enemy_bullets[i] == NULL && enemys[i] -> attack_flag == true) { enemy_bullets[i] = new Enemy_Bullet(*(enemys[i]));}
                    }
                
                //Center the camera over the character
                camera.x = ( John.getPosX() + 19 ) - SCREEN_WIDTH / 2;
                camera.y = ( John.getPosY() + 27 ) - SCREEN_HEIGHT / 2;
                
                //Keep the camera in bounds
                if( camera.x < 0 )
                {
                    camera.x = 0;
                }
                if( camera.y < 0 )
                {
                    camera.y = 0;
                }
                if( camera.x > LEVEL_WIDTH - camera.w )
                {
                    camera.x = LEVEL_WIDTH - camera.w;
                }
                if( camera.y > LEVEL_HEIGHT - camera.h )
                {
                    camera.y = LEVEL_HEIGHT - camera.h;
                }
                
                //let the objects have the camera position
                John.set_cam(camera.x, camera.y);
                gun.set_cam(camera.x, camera.y);
                
                for(int i = 0 ;i < enemys_amount;i++)
                {
                    if (enemys[i] != NULL) {enemys[i] -> set_cam(camera.x, camera.y);}
                }
                for(int i = 0 ;i < enemys_amount;i++)
                {
                    if (enemy_bullets[i] != NULL) {enemy_bullets[i] -> set_cam(camera.x, camera.y);}
                }
                for (int i = 0; i < bullets_amount; ++i)
                {
                    if (bullets[i] != NULL) bullets[i] -> set_cam(camera.x, camera.y);
                }
                
                
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        if (bullets_count < bullets_amount)
                        {
                            
                            //if player BUTTONDOWN, add a bullet
                            if( e.type == SDL_MOUSEBUTTONDOWN)
                            {
                                for(int i = 0 ;i < bullets_amount;i++){
                                    if (bullets[i] == NULL)
                                    {bullets[i] = new Bullet(gun);break;}}
                                ++ bullets_count;
                                Mix_PlayChannel( -1, gplayer_shoot, 0 );
                            }
                        }
                        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
                        {
                            //Adjust the velocity
                            switch( e.key.keysym.sym )
                            {
                                case SDLK_ESCAPE:
                                {isPause = true;gBackButton.render();
                                    gPAUSETexture.render(280, 300);
                                    gEXITTexture.render(40,15);
                                    SDL_RenderPresent( gRenderer );}
                            }
                        }
                        //handle input for the player
                        John.handleEvent(e);
                        gun.handleEvent(e);
                    }
                    while(isPause){
                        SDL_ShowCursor(SDL_ENABLE);
                        while( SDL_PollEvent( &e ) != 0 )
                        {
                            if( e.type == SDL_QUIT )
                            {
                                quit = true; isPause = false;
                            }
                            if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
                            {
                                //Adjust the velocity
                                switch( e.key.keysym.sym )
                                {
                                    case SDLK_ESCAPE: isPause = false;
                                }
                            }
                            gBackButton.handleEvent(&e, current_state);
                        }
                    }
                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                    SDL_RenderClear( gRenderer );
                    //Render background
                    gBGTexture.render( 0, 0, &camera );
                //handle move/jump/fall of the player
                const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
                
                if (!John.fall_flag)
                {if (currentKeyStates[ SDL_SCANCODE_D ]){
                    //John.texture_flip = SDL_FLIP_NONE;
                    if (!John.jump_flag) John.move();
                    else John.jump();
                }
                else if (currentKeyStates[ SDL_SCANCODE_A ]){
                    //John.texture_flip = SDL_FLIP_HORIZONTAL;
                    if (!John.jump_flag) John.move();
                    else John.jump();
                }
                else {if (John.jump_flag) John.jump();else John.stand();}}
                else {if (John.jump_flag) John.jump();else John.fall();}
                gun.move(John);
                John.movement();
                //( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
                //SDL_RenderDrawRect( gRenderer, &John.getRect(1) );
                if (gun.shoot_flag) gun.gun_effect(John);
                
                //handle move/jump/fall/dead/render letters of the enemys
                for(int i = 0 ;i < enemys_amount;i++)
                {
                if (enemys[i] != NULL)
                {
                    {enemys[i] -> assign_letter();}
                    if (!enemys[i] -> dead_flag)
                    {
                        if(!enemys[i] -> fall_flag)
                        {
                            if (!enemys[i] -> jump_flag){ if (!enemys[i] -> stand_flag) enemys[i] -> move(); else enemys[i] -> stand(); }
                            else enemys[i] -> jump();}
                        else
                        {
                            if (enemys[i] -> jump_flag) enemys[i] -> jump();
                            else enemys[i] -> fall();}
                        enemys[i] -> movement(John);enemys[i] -> attack();}
                    else enemys[i] -> dead();}
                    
                }
                
                //delete bullet if it is out of the map and handle move of the bullets
                for(int i = 0; i < bullets_amount ; i++) {
                    if (bullets[i] != NULL){
                    if (bullets[i] -> getPosX() > 1353 || bullets[i] -> getPosX() < 22 || bullets[i] -> getPosY() > 1080 || bullets[i] -> getPosY() < 0 )
                    {
                    delete bullets[i];
                    bullets[i] = NULL;
                    --bullets_count;
                    }
                    else {bullets[i] -> move(); bullets[i] -> movement();}
                }
                }
                
                //delete enemys' bullet if it is out of the map and handle move of the bullets
                for(int i = 0; i < enemys_amount ; i++) {
                    if (enemy_bullets[i] != NULL){
                        if (enemy_bullets[i] -> getPosX() > 1353 || enemy_bullets[i] -> getPosX() < 22 || enemy_bullets[i] -> getPosY() > 1080 || enemy_bullets[i] -> getPosY() < 0 )
                        {
                            delete enemy_bullets[i];
                            enemy_bullets[i] = NULL;
                        }
                        else {enemy_bullets[i] -> move(); enemy_bullets[i] -> movement();}
                    }
                }
                
                
                John.draw_health_bar();
                //SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0x00);
                //SDL_RenderDrawRect(gRenderer, &John.getRect(2));
                //for(int i = 0; i < enemys_amount ; i++){
                    //if(enemy_bullets[i] != NULL) SDL_RenderDrawRect(gRenderer, &enemy_bullets[i] -> getRect(2));
                //}
                for(int i = 0;i < letter_count; i++)
                texture_letter[*(letter_index[i])].render(200 + 56 * i, 10);
            
                SDL_RenderPresent( gRenderer );
                
                if (letter_count == voc.voc_size[level_index][voc_count])
                {   //SDL_Delay(10000);
                    for(int i = 0; i < letter_count ; i++) {delete letter_index[i]; letter_index[i] = NULL;}
                    letter_count = 0; voc_count += 1;timed = false;
                    gGOALTexture.render(280, 100);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(500);
                }
                
                    if (John.health <= 0) {isPause = true;gGAMEOVERTexture.render(0, 0);
                        gBackButton.render();
                        SDL_RenderPresent( gRenderer );
                        John.initialize_cha();
                        letter_count = 0;
                        voc_count = 0;
                        for(int i = 0; i < letter_count ; i++) {delete letter_index[i]; letter_index[i] = NULL;}
                        //timed = false;
                        
                    }
                    if (voc_count == 10){
                        voc_count = 0;
                        current_state = 0;
                        
                    }
                
                ++countedFrames;
                //If frame finished early
                int frameTicks = capTimer.getTicks();
                if( frameTicks < SCREEN_TICKS_PER_FRAME )
                {
                    //Wait remaining time
                    SDL_Delay( SCREEN_TICKS_PER_FRAME - frameTicks );
                }
                //std::cout << SIZE_OF_ARRAY(computer_voc[1]) << std::endl;
                }
                
                else if (current_state == Help){
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            quit = true;
                        }
                        gBackButton.handleEvent(&e, current_state);
                    }
                    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
                    SDL_RenderClear( gRenderer );
                    gHELPTexture.render(0, 0);
                    gBackButton.render();
                    SDL_RenderPresent( gRenderer );
                    
                }
                else if(current_state == Quit){
                    quit = true;
                }
                
                
            }
    
    //Free resources and close SDL
    close();
    Enemy:: free_media();
    Bullet:: free_media();
    Enemy_Bullet:: free_media();
    for (int i = 0; i < bullets_amount ; i++) if(bullets[i] != NULL) delete bullets[i];
    for (int i = 0; i < enemys_amount ; i++) if(enemys[i] != NULL) delete enemys[i];
    for (int i = 0; i < enemys_amount ; i++) if(enemy_bullets[i] != NULL) delete enemy_bullets[i];

    
    return 0;
}
}
}


#include <stdio.h>
#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.hpp"
#include "character.hpp"
#include "initailize.hpp"
#include <iostream>
extern SDL_Rect walls[12];
double Character:: gravity = 0.04;
int Character:: vel_modify = 3;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
Character::Character(){
    //Initialize the offsets
    mPosX = 480;
    mPosY = 300;
    jump_pos = 300;
    health = 145;
    health_bar.x = 0;
    health_bar.y = 0;
    health_bar.w = health;
    health_bar.h = 10;
    
    //Initialize the velocity and camera
    mVelX = 0;
    mVelY = 0;
    camX = ( 480 + 19 ) - SCREEN_WIDTH / 2;
    camY = ( 300 + 27 ) - SCREEN_HEIGHT / 2;
    
    //Load media
    texture_stand[0].loadFromFile("joan_stand.png");
    texture_run[0].loadFromFile("joan_run_1.png");
    texture_run[1].loadFromFile("joan_run_2.png");
    texture_run[2].loadFromFile("joan_run_3.png");
    texture_run[3].loadFromFile("joan_run_4.png");
    texture_run[4].loadFromFile("joan_run_5.png");
    texture_run[5].loadFromFile("joan_run_6.png");
    texture_jump[0].loadFromFile("joan_jump_1.png");
    texture_jump[1].loadFromFile("joan_jump_2.png");
    texture_blood[0].loadFromFile("boss_health_back.png");
    texture_blood[1].loadFromFile("boss_health.png");
    texture_blood[2].loadFromFile("missions_icon.png");
    texture_blood[3].loadFromFile("missions_icon_complete.png");
    
    //Set collision box dimension
    mCollider1.x = mPosX + 10;
    mCollider1.y = mPosY + 50;
    mCollider2.x = mPosX + 25;
    mCollider2.y = mPosY + 5;
    mCollider1.w = texture_stand[0].getWidth() - 25;
    mCollider1.h = texture_stand[0].getHeight() - 60;
    mCollider2.w = texture_stand[0].getWidth() - 50;
    mCollider2.h = texture_stand[0].getHeight() - 20;
}
Character::~Character(){
    texture_stand[0].free();
    texture_run[0].free();
    texture_run[1].free();
    texture_run[2].free();
    texture_run[3].free();
    texture_run[4].free();
    texture_run[5].free();
    texture_jump[0].free();
    texture_jump[1].free();
}
void Character::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_w:
                if (jump_flag == false && fall_flag == false){jump_flag = true; mVelY += VEL; jump_pos = mPosY ;break;} else break;
            case SDLK_SPACE:
                if (jump_flag == false && fall_flag == false){jump_flag = true; mVelY += VEL; jump_pos = mPosY ;break;} else break;
            case SDLK_a: mVelX -= VEL/2; break;
            case SDLK_d: mVelX += VEL/2; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_a: mVelX += VEL/2; break;
            case SDLK_d: mVelX -= VEL/2; break;
        }
    }
}
void Character::move()
{
    //Current animation frame
    static int frame = 0;
    //Render current frame
    currentTexture = &texture_run[ frame / 6 ];
    (*currentTexture).render( mPosX - camX, mPosY - camY,NULL,0,NULL,texture_flip);
    //Go to next frame
    ++frame;
    //SDL_RenderPresent( gRenderer );
    //Cycle animation
    if( frame / 6 >= 6 )
    {
        frame = 0;
    }
    mCollider1.x = mPosX + 10;
    mCollider1.y = mPosY + 50;
    mCollider2.x = mPosX + 25;
    mCollider2.y = mPosY + 5;
}
void Character::jump()
{
    //Current animation frame
    static double frame = 0;
    //Render current frame
    currentTexture = &texture_jump[ 0 ];
    (*currentTexture).render( mPosX - camX, mPosY - camY,NULL,0,NULL,texture_flip);
    //Go to next frame
    frame += 1;
    //SDL_RenderPresent( gRenderer );
    //Cycle animation
    for (int i = 0; i < 11 ; i++)
    {
        if (checkCollision(getRect(1), walls[i]))
        {if (frame >= 80)
        { fall_flag = false;
            jump_flag = false;
            mVelY = 0;
            frame = 0;
            break;}
        }
    }
    if (jump_flag){
    if (frame < 120) {mPosY = jump_pos - mVelY/vel_modify * frame + gravity * frame * frame;}
    else mPosY +=4;
        std::cout << frame << ":" << mPosY << "   VEL:  " << (jump_pos - mVelY/vel_modify * frame + gravity * frame * frame) - (jump_pos - mVelY/vel_modify * (frame-1) + gravity * (frame-1) * (frame-1)) <<std::endl;}
    
    mCollider1.x = mPosX + 10;
    mCollider1.y = mPosY + 50;
    mCollider2.x = mPosX + 25;
    mCollider2.y = mPosY + 5;
    if(frame < 120 && mPosY >= 1080) jump_pos -= 1080;
    if(frame >= 120 && mPosY >= 1080) mPosY = 0;
    //if (frame > 400) frame = 300;
    
}
void Character::stand()
{
    texture_stand[0].render(mPosX - camX, mPosY - camY,NULL,0,NULL,texture_flip);
    mCollider1.x = mPosX + 10;
    mCollider1.y = mPosY + 50;
    mCollider2.x = mPosX + 25;
    mCollider2.y = mPosY + 5;
}
void Character::movement(){
    if (mPosX + mVelX > 1353) mPosX = 1352;
    else if (mPosX + mVelX < 22) mPosX = 23;
    else mPosX += mVelX;
    //std::cout << mPosX << std::endl;
}
void Character::fall()
{
    texture_jump[0].render(mPosX - camX, mPosY - camY,NULL,0,NULL,texture_flip);
    if (jump_flag == false) mPosY += 4.5;
    if (mPosY > 1080) mPosY = 0;
    std::cout << mPosY << std::endl;
    //jump_flag = true;
    mCollider1.x = mPosX + 10;
    mCollider1.y = mPosY + 50;
    mCollider2.x = mPosX + 25;
    mCollider2.y = mPosY + 5;
}

void Character:: draw_health_bar()
{
    health_bar.w = health;
    texture_blood[0].render(38, 25);
    texture_blood[1].render(45, 29, &health_bar);
    if (health < 0) texture_blood[3].render(0,0);
    else texture_blood[2].render(0,0);
}

void Character:: initialize_cha(){
    //Initialize the offsets
    mPosX = 480;
    mPosY = 300;
    jump_pos = 300;
    health = 145;
    health_bar.x = 0;
    health_bar.y = 0;
    health_bar.w = health;
    health_bar.h = 10;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    jump_flag = false;
    fall_flag = false;
    
    camX = ( 480 + 19 ) - SCREEN_WIDTH / 2;
    camY = ( 300 + 27 ) - SCREEN_HEIGHT / 2;
}

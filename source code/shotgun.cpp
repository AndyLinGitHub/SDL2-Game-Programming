//
//  shotgun.cpp
//  Created by 林有安 on 2018/12/27.
//  Copyright © 2018 SDL_test. All rights reserved.
//
#include <stdio.h>
#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.hpp"
#include "shotgun.hpp"
Shot_gun::Shot_gun(Character& name){
    //Initialize the offsets
    mPosX = name.getPosX();
    mPosY = name.getPosY();
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    
    //Load media
    texture_shotgun[0].loadFromFile("sshotgun.png");
    texture_gun_effect[0].loadFromFile("sshotgun_shot_fx_1.png");
    texture_gun_effect[1].loadFromFile("sshotgun_shot_fx_2.png");
    texture_gun_effect[2].loadFromFile("sshotgun_shot_fx_3.png");
    texture_gun_effect[3].loadFromFile("sshotgun_shot_fx_4.png");
    texture_head[0].loadFromFile("head.png");
    texture_front[0].loadFromFile("pentacl_1.png");
    
    //Initialize the center
    center.x = 0;
    center.y = 0;
    
    //Initialize the mouse position
    mouse_x = 0;
    mouse_y = 0;
    
}
Shot_gun::~Shot_gun(){
    texture_shotgun[0].free();
    texture_gun_effect[0].free();
    texture_gun_effect[1].free();
    texture_gun_effect[2].free();
    texture_gun_effect[3].free();
    texture_head[0].free();
}
void Shot_gun::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_MOUSEMOTION)
    {
        //Get mouse position
        SDL_GetMouseState( &mouse_x, &mouse_y );
        if (mouse_x > 960) mouse_x = 960; if (mouse_x < 0) mouse_x = 0;
        if (mouse_y > 720) mouse_x = 720; if (mouse_y < 0) mouse_y = 0;
        angle = -atan2(mouse_x - mPosX + camX, mouse_y - mPosY + camY) * 180 / M_PI + 90;
    }
    if( e.type == SDL_MOUSEBUTTONDOWN)
    {
        shoot_flag = true;
    }
}
void Shot_gun::move(Character& name)
{
    mPosX = name.getPosX();
    mPosY = name.getPosY();
    int x = 0, y = 0, revise = 0;
    double rot_angle = 0;
    if ((angle > 90 && angle < 270)) {  texture_flip = name.texture_flip = SDL_FLIP_HORIZONTAL; revise = 12;}
    else {texture_flip = name.texture_flip = SDL_FLIP_NONE; revise = 0;}
    if (!name.jump_flag && name.texture_flip == SDL_FLIP_NONE) {x = mPosX - 2; y = mPosY - 1 ;}
    if (!name.jump_flag && name.texture_flip == SDL_FLIP_HORIZONTAL) {x = mPosX-11; y = mPosY-1;}
    if (name.jump_flag && name.texture_flip == SDL_FLIP_NONE) {x = mPosX; y = mPosY-1;}
    if (name.jump_flag && name.texture_flip == SDL_FLIP_HORIZONTAL) {x = mPosX-13; y = mPosY-1;}
    if (name.texture_flip == SDL_FLIP_NONE) {rot_angle = angle; center.x = 28; center.y = 37;}
    if (name.texture_flip == SDL_FLIP_HORIZONTAL) {rot_angle = angle + 180; center.x = 50; center.y = 37;}
    texture_head[0].render(x + revise - camX, y - camY + 1, NULL, rot_angle, NULL, name.texture_flip);
    texture_shotgun[0].render(x - camX, y - camY, NULL, rot_angle, &center, name.texture_flip);
    texture_front[0].render(mouse_x + 10, mouse_y + 10 , NULL, 0, NULL, name.texture_flip);
    
}
void Shot_gun::gun_effect(Character& name){
    //Current animation frame
    static int frame = 0;
    //Render current frame
    currentTexture = &texture_gun_effect[ frame / 4 ];
    int x = 0, y = 0;
    double rot_angle = 0, inverse = 1;
    if ((angle > 90 && angle < 270)) {name.texture_flip = SDL_FLIP_HORIZONTAL; inverse = -0.9;}
    else {name.texture_flip = SDL_FLIP_NONE;inverse = 1.1;}
    if (!name.jump_flag && name.texture_flip == SDL_FLIP_NONE) {x = mPosX-2; y = mPosY-1;}
    if (!name.jump_flag && name.texture_flip == SDL_FLIP_HORIZONTAL) {x = mPosX-11; y = mPosY-1;}
    if (name.jump_flag && name.texture_flip == SDL_FLIP_NONE) {x = mPosX; y = mPosY-1;}
    if (name.jump_flag && name.texture_flip == SDL_FLIP_HORIZONTAL) {x = mPosX-13; y = mPosY-1;}
    if (name.texture_flip == SDL_FLIP_NONE) {rot_angle = angle; center.x = 28; center.y = 37;}
    if (name.texture_flip == SDL_FLIP_HORIZONTAL) {rot_angle = angle + 180; center.x = 50; center.y = 37;}
    (*currentTexture).render( x + 70 * cos(rot_angle * M_PI / 180) * inverse - camX, y + 70 * sin(rot_angle * M_PI / 180) * inverse - camY, NULL, rot_angle, &center,name.texture_flip);
    //Go to next frame
    ++frame;
    //SDL_RenderPresent( gRenderer );
    //Cycle animation
    if( frame / 4 >= 4 )
    {
        frame = 0;
        shoot_flag = false;
    }
}

//
//  Enemy_Bullet.cpp
//  SDL_test
//
//  Created by 林有安 on 2019/1/1.
//  Copyright © 2019 SDL_test. All rights reserved.
//

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.hpp"
#include "Enemy_Bullet.hpp"
LTexture Enemy_Bullet::texture_bullet[1];
Enemy_Bullet::Enemy_Bullet(Enemy& enemy)
{
    //Initialize the offsets
    if (enemy.texture_flip == SDL_FLIP_NONE) {
        mPosX = enemy.getPosX() + 70;
        mPosY = enemy.getPosY();}
    else{mPosX = enemy.getPosX() - 70;
        mPosY = enemy.getPosY();}
    
    texture_flip = enemy.texture_flip;
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    //Load media
    texture_bullet[0].loadFromFile("ivan_laser_shot_fx_3.png");
    //Set collision box dimension
    mCollider1.x = mPosX + 5;
    mCollider1.y = mPosY + 33;
    mCollider2.x = mPosX + 5;
    mCollider2.y = mPosY + 33;
    mCollider1.w = texture_bullet[0].getWidth() - 60;
    mCollider1.h = texture_bullet[0].getHeight() - 60;
    mCollider2.w = texture_bullet[0].getWidth() - 60;
    mCollider2.h = texture_bullet[0].getHeight()- 60;
}
Enemy_Bullet::~Enemy_Bullet(){
    //texture_bullet[0].free();
    //texture_bullet[1].free();
}
void Enemy_Bullet::handleEvent( SDL_Event& e )
{
}
void Enemy_Bullet::move()
{
    currentTexture = &texture_bullet[0];
    (*currentTexture).render( (mPosX) - camX, (mPosY) - camY,NULL,0,NULL,texture_flip);
    
    mCollider1.x = mPosX + 5;
    mCollider1.y = mPosY + 33;
    mCollider2.x = mPosX + 5;
    mCollider2.y = mPosY + 33;
}
void Enemy_Bullet::movement(){
    if (texture_flip == SDL_FLIP_HORIZONTAL) mPosX -= 5;
    else mPosX += 5;
    mCollider1.x = mPosX + 5;
    mCollider1.y = mPosY + 33;
    mCollider2.x = mPosX + 5;
    mCollider2.y = mPosY + 33;
    
}
void Enemy_Bullet::free_media(){
    Enemy_Bullet::texture_bullet[0].free();
}

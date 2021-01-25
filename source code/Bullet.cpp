#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.hpp"
#include "Bullet.hpp"
#include <iostream>
LTexture Bullet::texture_bullet[2];
Bullet::Bullet(Shot_gun& gun)
{
    //Initialize the offsets
    angle = gun.getAngle();
    if (gun.texture_flip == SDL_FLIP_NONE) {
    mPosX = gun.getPosX() + 65 * cos(angle * M_PI / 180) + 14;
        mPosY = gun.getPosY() + 32 + 65* sin(angle * M_PI / 180);}
    else{mPosX = gun.getPosX() + 65 * cos(angle * M_PI / 180) + 25;
        mPosY = gun.getPosY() + 32 + 65* sin(angle * M_PI / 180);}
    
    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
    //Load media
    texture_bullet[0].loadFromFile("grenade_bullet_1.png");
    texture_bullet[1].loadFromFile("grenade_bullet_2.png");
    //Set collision box dimension
    mCollider1.x = mPosX;
    mCollider1.y = mPosY;
    mCollider2.x = mPosX;
    mCollider2.y = mPosY;
    mCollider1.w = texture_bullet[0].getWidth();
    mCollider1.h = texture_bullet[0].getHeight();
    mCollider2.w = texture_bullet[0].getWidth();
    mCollider2.h = texture_bullet[0].getHeight();
}
Bullet::~Bullet(){
    //texture_bullet[0].free();
    //texture_bullet[1].free();
}
void Bullet::handleEvent( SDL_Event& e )
{
    //If a key was pressed
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
           
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
    }
}
void Bullet::move()
{
    //Current animation frame
    static int frame = 0;
    
    //Render current frame
    currentTexture = &texture_bullet[ frame / 50 ];
    (*currentTexture).render( (mPosX) - camX, (mPosY) - camY,NULL,angle,NULL,texture_flip);
    
    //Go to next frame
    ++frame;
    
    //Cycle animation
    if( frame / 50 >= 2 )
    {
        frame = 0;
    }
    mCollider1.x = mPosX;
    mCollider1.y = mPosY;
    mCollider2.x = mPosX;
    mCollider2.y = mPosY;
}
void Bullet::movement(){
    mPosX += 40 * cos(angle * M_PI / 180);
    mPosY +=  40 * sin(angle * M_PI / 180);
    mCollider1.x = mPosX;
    mCollider1.y = mPosY;
    mCollider2.x = mPosX;
    mCollider2.y = mPosY;
    
}
void Bullet::free_media(){
    Bullet::texture_bullet[0].free();
    Bullet::texture_bullet[1].free();
}

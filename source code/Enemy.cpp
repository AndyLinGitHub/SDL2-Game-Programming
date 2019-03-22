#include <stdio.h>
#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Enemy.hpp"
#include "initailize.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Enemy_Bullet.hpp"
#define enemys_amount 26
extern LTexture texture_letter[26];
extern SDL_Rect walls[12];
//extern const int enemys_amount;
extern Enemy* enemys[enemys_amount];
extern Enemy_Bullet* enemy_bullets[enemys_amount];
double Enemy:: gravity = 0.04;
int Enemy:: vel_modify = 3;
extern int enemys_count;
bool Enemy::init_rndseed = 0;
const int Enemy::SCREEN_HEIGHT_ = 1080;
const int Enemy::SCREEN_WIDTH_ = 1340;
int Enemy::wallnum = 0;
LTexture Enemy::texture_stand[1];
LTexture Enemy::texture_run[6];
LTexture Enemy::texture_jump[6];
LTexture Enemy::texture_weapon[3];
LTexture Enemy::texture_weapon_effect[3];
LTexture Enemy::texture_dead[9];
LTexture Enemy::texture_blood[5];
Enemy::Enemy(int ind)
{
    //Load media
    texture_stand[0].loadFromFile("ivan_stand.png");
    texture_run[0].loadFromFile("ivan_run_1.png");
    texture_run[1].loadFromFile("ivan_run_2.png");
    texture_run[2].loadFromFile("ivan_run_3.png");
    texture_run[3].loadFromFile("ivan_run_4.png");
    texture_run[4].loadFromFile("ivan_run_5.png");
    texture_run[5].loadFromFile("ivan_run_6.png");
    texture_jump[0].loadFromFile("ivan_jump_1.png");
    texture_jump[1].loadFromFile("ivan_jump_2.png");
    texture_jump[2].loadFromFile("ivan_jump_3.png");
    texture_jump[3].loadFromFile("ivan_jump_4.png");
    texture_jump[4].loadFromFile("ivan_jump_5.png");
    texture_jump[5].loadFromFile("ivan_jump_6.png");
    texture_weapon[0].loadFromFile("ivan_laser_1.png");
    texture_weapon[1].loadFromFile("ivan_laser_2.png");
    texture_weapon[2].loadFromFile("ivan_laser_3.png");
    texture_weapon_effect[0].loadFromFile("ivan_laser_shot_fx_1.png");
    texture_weapon_effect[1].loadFromFile("ivan_laser_shot_fx_2.png");
    texture_weapon_effect[2].loadFromFile("ivan_laser_shot_fx_3.png");
    texture_dead[0].loadFromFile("ivan_death_1.png");
    texture_dead[1].loadFromFile("ivan_death_2.png");
    texture_dead[2].loadFromFile("ivan_death_3.png");
    texture_dead[3].loadFromFile("ivan_death_4.png");
    texture_dead[4].loadFromFile("ivan_death_5.png");
    texture_dead[5].loadFromFile("ivan_death_6.png");
    texture_dead[6].loadFromFile("ivan_death_7.png");
    texture_dead[7].loadFromFile("ivan_death_8.png");
    texture_dead[8].loadFromFile("ivan_death_9.png");
    texture_blood[0].loadFromFile("blood_splash_fx_2_1.png");
    texture_blood[1].loadFromFile("blood_splash_fx_2_2.png");
    texture_blood[2].loadFromFile("blood_splash_fx_2_3.png");
    texture_blood[3].loadFromFile("blood_splash_fx_2_4.png");
    texture_blood[4].loadFromFile("blood_splash_fx_2_5.png");
    
    //Initialize the offsets
    init_seed();
    mPosX = rand() % SCREEN_WIDTH_ + 50;
    mPosY = rand() % SCREEN_HEIGHT_ + 100;
    while (checkCollision_(0, 0) || EnemyCollision(0, 0)) {
        mPosX = rand() % SCREEN_WIDTH_ + 50;
        mPosY = rand() % SCREEN_HEIGHT_;
        mCollider1.x = mPosX + 10;
        mCollider1.y = mPosY + 50;
        mCollider2.x = mPosX + 25;
        mCollider2.y = mPosY + 5;
        mCollider1.w = texture_stand[0].getWidth() - 25;
        mCollider1.h = texture_stand[0].getHeight() - 60;
        mCollider2.w = texture_stand[0].getWidth() - 50;
        mCollider2.h = texture_stand[0].getHeight() - 10;
    }
    
    stuck_count = 0;
    //Initialize the velocity
    mVelX = rand() % (5 - 1 + 1) + 1;
    mVelY = 0;
    texture_flip = SDL_FLIP_HORIZONTAL;
    //Initialize the frame
    move_frame = 0;
    attack_frame = 0;
    attack_index = 0;
    dead_frame = 0;
    jump_frame = 0;
    
    //Set collision box dimension
    mCollider1.x = mPosX + 10;
    mCollider1.y = mPosY + 50;
    mCollider2.x = mPosX + 25;
    mCollider2.y = mPosY + 5;
    mCollider1.w = texture_stand[0].getWidth() - 25;
    mCollider1.h = texture_stand[0].getHeight() - 60;
    mCollider2.w = texture_stand[0].getWidth() - 50;
    mCollider2.h = texture_stand[0].getHeight() - 10;
    
    index = ind;
}
void Enemy::free_media(){
    texture_stand[0].free();
    texture_run[0].free();
    texture_run[1].free();
    texture_run[2].free();
    texture_run[3].free();
    texture_run[4].free();
    texture_run[5].free();
    texture_jump[0].free();
    texture_jump[1].free();
    texture_jump[2].free();
    texture_jump[3].free();
    texture_jump[4].free();
    texture_jump[5].free();
    texture_weapon[0].free();
    texture_weapon[1].free();
    texture_weapon[2].free();
    texture_weapon_effect[0].free();
    texture_weapon_effect[1].free();
    texture_weapon_effect[2].free();
    texture_dead[0].free();
    texture_dead[1].free();
    texture_dead[2].free();
    texture_dead[3].free();
    texture_dead[4].free();
    texture_dead[5].free();
    texture_dead[6].free();
    texture_dead[7].free();
    texture_dead[8].free();
    texture_blood[0].free();
    texture_blood[1].free();
    texture_blood[2].free();
    texture_blood[3].free();
    texture_blood[4].free();
}
Enemy::~Enemy(){
    for(int i = 0; i < enemys_amount; i++)
        if ((enemys[i]) == (this)) { std::cout << "Delete Enemy" << std::endl;enemys[i] = NULL; -- enemys_count;break;}
}
void Enemy::handleEvent( SDL_Event& e )
{
    
}

void Enemy::movement(Character& name){
    
    if (abs(name.getPosY() - mPosY) < 30 && abs(name.getPosX() - mPosX) < 200)
        for (int i = 0; i < enemys_amount; i++)
        {
            if ((enemys[i]) == (this)) if (enemy_bullets[i] == NULL) { attack_flag = true; break; }
        } //// 這段讓射擊動畫在不會一直出
    static int count = 0;
    count++;
    SDL_Rect cam;
    cam.x = camX; cam.y = camY; cam.w = 960; cam.h = 720;
    if (count % 150 == 1)
    {if(SDL_HasIntersection(&(this->getRect(1)),&cam)){
        if (name.getPosX() > mPosX - 100) {
            if (!EnemyCollision(mVelX, 0)) { mPosX += mVelX; texture_flip = SDL_FLIP_NONE; stand_flag = false;}
            else {  mPosX -= mVelX; //texture_flip = SDL_FLIP_HORIZONTAL;
            }
        }
        else {
            if (!EnemyCollision(-mVelX, 0)) { mPosX -= mVelX; texture_flip = SDL_FLIP_HORIZONTAL; }
            else
            {
                mPosX += mVelX;// texture_flip = SDL_FLIP_NONE;
            }
        }
        if (mPosY > name.getPosY() && !jump_flag && !fall_flag) {
            jump_flag = true; jump_pos = getPosY(); mVelY = 15;
        }}}
    else {
       
        if (count % 1000 == 0){
            if (texture_flip == SDL_FLIP_HORIZONTAL) mPosX += mVelX;
            else mPosX -= mVelX;}
        
        else{
            if (texture_flip == SDL_FLIP_HORIZONTAL) mPosX -= mVelX;
            else mPosX += mVelX;}
    }
    if (mPosX == mPosY + 300 && texture_flip == SDL_FLIP_HORIZONTAL) texture_flip = SDL_FLIP_NONE;
    if (mPosX == mPosY + 300 && texture_flip == SDL_FLIP_NONE) texture_flip = SDL_FLIP_HORIZONTAL;
    if (mPosX >= 1340) { mPosX = 1340; texture_flip = SDL_FLIP_HORIZONTAL; mPosX -= 5;}
    if (mPosX <= 22) { mPosX = 22; texture_flip = SDL_FLIP_NONE; mPosX += 8;}
    
    
    
}
void Enemy ::assign_letter(){
    texture_letter[index].render(mPosX - camX, mPosY- camY - 10,NULL,0,NULL,SDL_FLIP_NONE);
}
void Enemy::attack(){

    //Render current frame
    if (attack_flag){
        currentTexture = &texture_weapon[ attack_frame / 10 ];
        
        //Go to next frame
        ++attack_frame;
        //Cycle animation
        if( attack_frame / 10 == 3 )
        {
            attack_flag = false;
            attack_frame = 0;
        }
        int x = 0, y = mPosY;
        if (texture_flip == SDL_FLIP_HORIZONTAL) {x = mPosX - 12;}
        else x = mPosX;
        (*currentTexture).render(x - camX,y - camY,NULL,0,NULL,texture_flip);
        
        if (attack_frame / 10 == 2) {
            currentTexture = &texture_weapon_effect[attack_index/10];
            if (texture_flip == SDL_FLIP_NONE)
                (*currentTexture).render(x + 72 - camX,y - camY,NULL,0,NULL,texture_flip);
            else (*currentTexture).render(x - 60 - camX,y - camY,NULL,0,NULL,texture_flip);
            attack_index++;
            if (attack_index/10 < 2) attack_frame = 20;
            else {attack_index = 0; attack_frame = 29;}
        }
    }
    else {
        int x = 0, y = mPosY;
        if (texture_flip == SDL_FLIP_HORIZONTAL) {x = mPosX - 12;}
        else x = mPosX;
        currentTexture = &texture_weapon[ 0 ];
        (*currentTexture).render(x - camX, y - camY, NULL, 0, NULL, texture_flip);
    }
    
}
void Enemy::move()
{
    //Current animation frame
    //Render current frame
    currentTexture = &texture_run[ move_frame / 6 ];
    (*currentTexture).render( mPosX - camX, mPosY - camY,NULL,0,NULL,texture_flip);
    //Go to next frame
    ++move_frame;
    //SDL_RenderPresent( gRenderer );
    //Cycle animation
    if( move_frame / 6 >= 6 )
    {
        move_frame = 0;
    }
    mCollider1.x = mPosX + 10;
    mCollider1.y = mPosY + 50;
    mCollider2.x = mPosX + 25;
    mCollider2.y = mPosY + 5;
}
void Enemy::jump()
{
    
    //Render current frame
    currentTexture = &texture_jump[ 0 ];
    (*currentTexture).render( mPosX - camX, mPosY - camY,NULL,0,NULL,texture_flip);
    //Go to next frame
    jump_frame += 1;
    //SDL_RenderPresent( gRenderer );
    //Cycle animation
    for (int i = 0; i < 11 ; i++)
    {
        if (checkCollision(getRect(1), walls[i]))
        {if (jump_frame >= 10)
        { fall_flag = false;
            jump_flag = false;
            mVelY = 0;
            jump_frame = 0;
            break;}
        }
    }
    if (jump_flag){
        if (jump_frame < 120) {mPosY = jump_pos - mVelY/vel_modify * jump_frame + gravity * jump_frame * jump_frame;}
        else mPosY +=4;}
        //std::cout << frame << ":" << mPosY << "   VEL:  " << (jump_pos - mVelY/vel_modify * frame + gravity * frame * frame) - (jump_pos - mVelY//vel_modify * (frame-1) + gravity * (frame-1) * (frame-1)) <<std::endl;}
    
    mCollider1.x = mPosX + 10;
    mCollider1.y = mPosY + 50;
    mCollider2.x = mPosX + 25;
    mCollider2.y = mPosY + 5;
    if(jump_frame < 400 && mPosY >= 1080) jump_pos -= 1080;
    if(jump_frame >= 400 && mPosY >= 1080) mPosY = 0;
    //if (frame > 400) frame = 300;
}
void Enemy::stand()
{
    texture_stand[0].render(mPosX - camX, mPosY - camY,NULL,0,NULL,texture_flip);
    mCollider1.x = mPosX + 10;
    mCollider1.y = mPosY + 50;
    mCollider2.x = mPosX + 25;
    mCollider2.y = mPosY + 5;
}

void Enemy:: fall()
{
    texture_jump[0].render(mPosX - camX, mPosY - camY,NULL,0,NULL,texture_flip);
    mPosY += 4;
    if (mPosY > 1080) mPosY = 0;
    //jump_flag = true;
    mCollider1.x = mPosX + 10;
    mCollider1.y = mPosY + 50;
    mCollider2.x = mPosX + 25;
    mCollider2.y = mPosY + 5;
}

void Enemy:: dead()
{
    //Current animation frame
    //Render current frame
    currentTexture = &texture_dead[ dead_frame / 10 ];
    if( dead_frame / 10 <= 8 )
    (*currentTexture).render( mPosX - camX, mPosY - camY,NULL,0,NULL,texture_flip);
    if(dead_frame / 10 <= 4) currentTexture = &texture_blood[ dead_frame / 10 ];
    (*currentTexture).render( mPosX - camX, mPosY - camY,NULL,0,NULL,texture_flip);
    //Go to next frame
    ++dead_frame;
    //SDL_RenderPresent( gRenderer );
    //Cycle animation
    if( dead_frame / 10 == 9 )
    {
        dead_frame = 0;
        this -> ~Enemy();
    }
}

void Enemy::init_seed() {
    if (!init_rndseed) {
        init_rndseed = 1;
    }
}

bool Enemy::checkCollision_(int a, int b)
{
    int temp_x = mPosX; int temp_y = mPosY;
    mPosX += a; mPosY += b;
    for (int i = 0; i < wallnum; ++i) {
        if (SDL_HasIntersection(&(walls[i]), this)) {
            mPosX = temp_x; mPosY = temp_y;
            return true;
        }
    }
    mPosX = temp_x; mPosY = temp_y;
    return false;
}

bool Enemy::EnemyCollision(int a, int b)
{
    SDL_Rect temp = this->getRect(2);
    temp.x += (a-30); temp.y += (b-30); temp.w+=60; temp.h += 60;
    for (int i = 0; i < enemys_amount; ++i) {
        if(enemys[i]!=NULL && this != enemys[i]){
            if (stuck_count > 10) {
                if (mPosX > 1340)mPosX = 1250;
                if (mPosX < 25)mPosX = 75;
                mPosX += (((rand() % 3) -1)*30);
                //mPosY -+((rand() % 3)-1)*this->getRect(2).h;
                stuck_count = 0;
                //return false;
            }
            if (SDL_HasIntersection(&(enemys[i]->getRect(2)), &temp)) {
                ++stuck_count;
                return true;
            }
        }
    }
    stuck_count = 0;
    return false;
}

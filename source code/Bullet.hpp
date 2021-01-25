//
//  Bullet.hpp
//  SDL_test
//
//  Created by 林有安 on 2018/12/27.
//  Copyright © 2018 SDL_test. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "character.hpp"
#include "shotgun.hpp"
class Bullet:public Object
{
public:
    //Initializes the variables
    Bullet(Shot_gun& gun);
    ~Bullet();
    //Takes key presses
    void handleEvent( SDL_Event& e );
    
    //Move the Bullet
    void move();

    //Movement of the Bullet
    void movement();
    static void free_media();
    
private:
    //Image of the Bullet
    static LTexture texture_bullet[2];
    
    double angle;
    
    LTexture *currentTexture;
};
#endif /* Bullet_hpp */

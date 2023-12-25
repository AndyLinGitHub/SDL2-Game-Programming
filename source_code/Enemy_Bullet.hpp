#ifndef Enemy_Bullet_hpp
#define Enemy_Bullet_hpp

#include <stdio.h>
#include "Enemy.hpp"
#include "Object.hpp"
class Enemy_Bullet: public Object
{
public:
    //Initializes the variables
    Enemy_Bullet(Enemy& enemy);
    ~Enemy_Bullet();
    //Takes key presses
    void handleEvent( SDL_Event& e );
    
    //Move the Bullet
    void move();
    
    //Movement of the Bullet
    void movement();
    static void free_media();
    
private:
    static LTexture texture_bullet[1];
    //Image of the Bullet
    LTexture *currentTexture;
};
#endif /* Enemy_Bullet_hpp */

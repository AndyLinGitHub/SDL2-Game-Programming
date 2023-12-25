#ifndef shotgun_hpp
#define shotgun_hpp
#include "character.hpp"

class Shot_gun : public Object
{
public:
    
    //Checking for shoot
    bool shoot_flag = false;
    
    //Initializes the variables
    Shot_gun( Character& );
    ~Shot_gun();
    //Takes key presses
    void handleEvent( SDL_Event& e );
    
    //Move the Shot_gun
    void move(Character& name);
    
    //Movement of the Shot_gun
    void movement();
    
    //effect of the Shot_gun
    void gun_effect(Character& name);
    
    double getAngle() {return angle;};
    
    
private:
    //The degree of the Shot_gun
    double angle;
    //The center of the Shot_gun
    SDL_Point center;
    //The position of mouse
    int mouse_x;
    int mouse_y;
    //Image of the Shot_gun
    LTexture texture_shotgun[1];
    LTexture texture_gun_effect[4];
    LTexture texture_head[1];
    LTexture texture_front[1];
    LTexture *currentTexture;
};
#endif /* shotgun_hpp */

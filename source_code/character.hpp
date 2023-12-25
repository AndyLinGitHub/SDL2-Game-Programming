#ifndef character_hpp
#define character_hpp
#include "Object.hpp"
class Character : public Object
{
public:
    //Checking for jump
    bool jump_flag = false;
    //Checking for fall
    bool fall_flag = false;
    double health;
    //Initializes the variables
    Character();
    ~Character();
    //Takes key presses and adjusts the character's velocity
    void handleEvent( SDL_Event& e );
    
    //Move the Character
    void move();
    
    //Jump the Character
    void jump();
    
    //Movement of the Character
    void movement();
    
    //Stand the Character
    void stand();
    
    //Fall the Charater
    void fall();
    void draw_health_bar();
    void initialize_cha();
    
private:
    int jump_pos;
    static double gravity;
    static int vel_modify;
    SDL_Rect health_bar;
    //Image of the Character
    LTexture texture_stand[1];
    LTexture texture_run[6];
    LTexture texture_jump[2];
    LTexture texture_blood[4];
    LTexture *currentTexture;
};

#endif /* character_hpp */

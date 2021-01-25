#ifndef Enemy_hpp
#define Enemy_hpp
#include "LTexture.hpp"
#include "Object.hpp"
#include "character.hpp"
//#include "Enemy_Bullet.hpp"

class Enemy : public Object, SDL_Rect
{
public:
    static const int SCREEN_WIDTH_;
    static const int SCREEN_HEIGHT_;
    //Checking for jump
    bool jump_flag = false;
    //Checking for fall
    bool fall_flag = false;
    //Checking for attack
    bool attack_flag = false;
    //Checking for dead
    bool dead_flag = false;
    bool stand_flag = false;
    //Initializes the variables
    Enemy(int ind);
    ~Enemy();
    static void free_media();
    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );
    
    //Move the Enemy
    void move();
    
    //Jump the Enemy
    void jump();
    
    //Movement of the Enemy
    void movement(Character& name);
    
    //Stand the Enemy
    void stand();
    
    //Render a letter
    void assign_letter();
    
    void dead();
    
    //Enemy attack
    void attack();
    void fall();
    int getIndex() {return index;}
    
    bool checkCollision_(int dx, int dy);
    
    //collision between enemy
    bool EnemyCollision(int a, int b);
    
private:
    int jump_pos;
    int stuck_count;
    static double gravity;
    static int vel_modify;
    int index;
    static bool init_rndseed;
    static void init_seed();
    static int wallnum;
    int move_frame;
    double jump_frame;
    int attack_frame;
    int attack_index;
    int dead_frame;
    
    //Image of the Enemy
    static LTexture texture_stand[1];
    static LTexture texture_run[6];
    static LTexture texture_jump[6];
    static LTexture texture_weapon[3];
    static LTexture texture_weapon_effect[3];
    static LTexture texture_dead[9];
    static LTexture texture_blood[5];
    LTexture *currentTexture;
};
#endif /* Enemy_hpp */

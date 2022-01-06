#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#include "screen.h"


typedef struct Player Player;


//------ PROTOTYPES -------------------
Player player_init(Screen *screen);   //function to init the player structure
void player_display(Screen *screen, Player *player); //function to display the player on the screen

void player_move(Player *player);   //function to check the position of the player and the animation of the player

void player_animationStandBy(Player *player, int *lastTimeAnimation); //the function to animate the player in standby
void player_animationRun(Player *player, int *lastTimeAnimation); //the function to animate the player in run action
void player_animationSquatDown(Player *player, int *lasTimeAnimation); //function to animate the player in squat position to down or stay down
void player_animationSquatUp(Player *player, int *lastTimeAnimation); //function to animate the player in squat position to up
//-------------------------------------



struct Player {
    SDL_Surface                 *m_spritesheet_surface; //the surface to load the image
    SDL_Texture                 *m_spritesheet_texture; //the texture to get the surface into the texture

    SDL_Rect                    m_sprite; //the Rectangle to get the good sprite on the spritesheet (the source rect)
    SDL_Rect                    m_position; //the Rectangle to display the sprite on the screen    (the dest rect)
    SDL_Rect                    m_hitbox;   //the rectangle to set hitbox of player (the collision)

    int                         m_timerAnimation; //the timer to set the speed animation
    int                         m_timerMove;      //the timer to set the speed move of the player on the screen

    unsigned char               m_life; //the life of the player
    unsigned char               m_attack;  //the force when attack

    unsigned char               m_isSquating; //if the player is squating down this variable is set to 1 , when is down completly the value is 2 else 0 the player not squat 
    unsigned char               m_isJumping; //if the player is jumping this variable is set to 1 else 0

    unsigned char               m_direction; //the direction of the look (to flip the player image) 0 : look on the right | 1 : look on the left

    void                        (*display)(Screen *screen, Player *player); //the pointer of function player_display
    void                        (*move)(Player *player); //pointer of function player_move
};


#endif
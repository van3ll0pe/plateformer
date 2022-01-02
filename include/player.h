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
//-------------------------------------



struct Player {
    SDL_Surface                 *m_spritesheet_surface; //the surface to load the image
    SDL_Texture                 *m_spritesheet_texture; //the texture to get the surface into the texture

    SDL_Rect                    m_sprite; //the Rectangle to get the good sprite on the spritesheet (the source rect)
    SDL_Rect                    m_position; //the Rectangle to display the sprite on the screen    (the dest rect)

    int                         m_timerAnimation; //the timer to set the speed animation
    int                         m_timerMove;      //the timer to set the speed move of the player on the screen

    unsigned char               m_life; //the life of the player
    unsigned char               m_attack;  //the force when attack

    unsigned char               m_direction; //the direction of the look (to flip the player image) 0 : look on the right | 1 : look on the left

    void                        (*display)(Screen *screen, Player *player); //the pointer of function player_display
    void                        (*move)(Player *player); //pointer of function player_move
};


#endif
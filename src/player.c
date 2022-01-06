#include "../include/player.h"

/**
 * @brief Player_init(void) is a function to init the main player and return all the stat of the player
 * 
 * @return Player 
 */
Player player_init(Screen *screen) {
    
    Player player = {
            .m_life                 = 100,
            .m_direction            = 0,

            .m_timerAnimation       = 0,
            .m_timerMove            = 0,

            .m_spritesheet_surface  = NULL,
            .m_spritesheet_texture  = NULL,

            //set the player rect on the spritesheet
            .m_sprite.x = 17,
            .m_sprite.y = 10,
            .m_sprite.w = 69, //the width of the spritesheet / the number of sprite in columns
            .m_sprite.h = 44, //the height of the spritesheet / the number of sprite in line 

            //set the player rect on the screen
            .m_position.x = 400,
            .m_position.y = 100,
            .m_position.w = 69 *3, //à changer en fonction de la taille de l'écran
            .m_position.h = 44 *3, //à changer en fonction de la largeur de l'écran

            .m_isJumping  = 0,
            .m_isSquating = 0,

            //set pointers of function
            .display = &player_display,
            .move = &player_move
    };

    //set the surface
    player.m_spritesheet_surface = IMG_Load("data/spritesheet_player");
    if (player.m_spritesheet_surface == NULL) {
        fprintf(stderr, "PROBLEME : Initialisation spritesheet surface - player\n");
        exit(EXIT_FAILURE); 
    }

    //set the trexture from the surface
    player.m_spritesheet_texture = SDL_CreateTextureFromSurface(screen->m_render, player.m_spritesheet_surface);
    if (player.m_spritesheet_texture == NULL) {
        fprintf(stderr, "PROBLEME : Initialisation spritesheet texture - player\n");
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(player.m_spritesheet_surface);

    return player;
}


/**
 * @brief player_display is a function to display the player on the screen
 *        The function take the rect_src and apply the rect_dest in the player.
 *        This Function has a pointer of function called display in the structure player
 * 
 * @param screen 
 * @param player 
 */
void player_display(Screen *screen, Player *player) {
    if (player->m_direction == 1) { //if the player looks on the left we gonna flip horizontaly the sprite
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(screen->m_render, player->m_spritesheet_texture, &player->m_sprite, &player->m_position, 0, NULL, flip);
    } else {    //if the player looks on the right
        SDL_RenderCopy(screen->m_render, player->m_spritesheet_texture, &player->m_sprite, &player->m_position);
    }
}



/**
 * @brief player_move is a function to set all the movement of the player and animation
 *        the function is separated in 3 if
 * 
 * @param player 
 */
void player_move(Player *player) {
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
    int isNotMoving = 0; //if isMoving equals 3 the player doesn't move else the player move (to define the standby player animation)
    static int lastTimeAnimation = 0;  //this variable will stock the timeAnimation + the time (it is static to save the value) -> pour faire le temps sauvegardé
    
    player->m_timerAnimation = SDL_GetTicks(); //get the time

    //condition to move left/right
    if (keyboard[SDL_SCANCODE_RIGHT] && !(keyboard[SDL_SCANCODE_LEFT])) { //move to the right
        player->m_direction = 0;
        if (player->m_isSquating == 0) {
            player_animationRun(player, &lastTimeAnimation);
        }
    } else if (keyboard[SDL_SCANCODE_LEFT] && !(keyboard[SDL_SCANCODE_RIGHT])) { //move to the left
        player->m_direction = 1;
        if (player->m_isSquating == 0) {
            player_animationRun(player, &lastTimeAnimation);
        }
    } else {
        isNotMoving++;
    }
    

    if (keyboard[SDL_SCANCODE_DOWN]) { //the player squat
        player_animationSquatDown(player, &lastTimeAnimation);
    }else if (!(keyboard[SDL_SCANCODE_DOWN]) && (player->m_isSquating == 2)) {
        player_animationSquatUp(player, &lastTimeAnimation);
    } else { //if no move left or right
        isNotMoving++;
    } //END condition to move left/right


    //condition to jump in more to move left/right
    if (keyboard[SDL_SCANCODE_UP]) { //jump the player

    } else { //if no jump
        isNotMoving++;
    } //END condition to jump in more to move left/right



    //confition to attack in more to jump/left/right
    if (keyboard[SDL_SCANCODE_D]) { //the player attack

    } else { //if no attack
        isNotMoving++;
    } //END confition to attack in more to jump/left/right


    //if no keycap is pressed, the player is inactive
    if (isNotMoving == 4) { //the player is in standby position
        player_animationStandBy(player, &lastTimeAnimation);
    }


}

/**
 * @brief Function to animate the player in standby position
 * It takes a pointer on the address of lastTimeAnimation to set the value of the static variable
 * 
 * @param player 
 * @param lastTimeAnimation 
 */
void player_animationStandBy(Player *player, int *lastTimeAnimation) {
    if (player->m_sprite.y != 0) { //put on the first sprite standby animation
            player->m_sprite.y = 0;
            player->m_sprite.x = 0;
        }
        
        if (player->m_timerAnimation > (*lastTimeAnimation) + 100) { //the animation is each 100 microseconds
            (*lastTimeAnimation) = player->m_timerAnimation;
            
            if (player->m_sprite.x < 345) {
                player->m_sprite.x += 69;
            } else {
                player->m_sprite.x = 0;
            }
        }
}

/**
 * @brief function to animate the player in running
 * It takes a pointer on the address of lastTimeAnimation to set the value of the static variable
 * 
 * @param player 
 * @param lastTimeAnimation 
 * @param direction 
 */
void player_animationRun(Player *player, int *lastTimeAnimation) {

    if ((player->m_sprite.y != 44) && (player->m_sprite.y != 88 && (player->m_sprite.x > 69))){
        player->m_sprite.x = 0;
        player->m_sprite.y = 44;
    }

    if (player->m_timerAnimation > (*lastTimeAnimation) + 70) { //the animation is each 70 microseconds
        (*lastTimeAnimation) = player->m_timerAnimation;
            
        if (player->m_sprite.y == 44 && player->m_sprite.x < 345) {
            player->m_sprite.x += 69;
        } else if (player->m_sprite.y == 44 && player->m_sprite.x >= 345){
            player->m_sprite.x = 0;
            player->m_sprite.y = 88;
        } else if (player->m_sprite.y == 88 && player->m_sprite.x < 69) {
            player->m_sprite.x += 69;
        } else {
            player->m_sprite.x = 0;
            player->m_sprite.y = 44;
        }
    }
}

void player_animationSquatDown(Player *player, int *lasTimeAnimation) {
    if (player->m_isSquating == 0 ||player->m_isSquating == 1) { //if is not squating or begin the down
        if (!(player->m_sprite.y == 440 && player->m_sprite.x >= 207) && player->m_isSquating == 0) { //Set the starting position 
            player->m_sprite.y = 440;
            player->m_sprite.x = 207;
            player->m_isSquating = 1;

        }

        if (player->m_timerAnimation > (*lasTimeAnimation) + 60) {
            (*lasTimeAnimation) = player->m_timerAnimation;

            if (player->m_sprite.x < 345) {
                player->m_sprite.x += 69;
            } else {
                player->m_isSquating = 2;
            }
        }

    } else { //if is already squatting
        player->m_sprite.x = 345;
        player->m_sprite.y = 440;

    }
}

void player_animationSquatUp(Player *player, int *lastTimeAnimation) {
    if (player->m_isSquating == 2) {  //if the player is already down with the squat

        if (!(player->m_sprite.y == 484 && player->m_sprite.x <= 138)) { //starting position for the animation
            player->m_sprite.y = 484;
            player->m_sprite.x = 0;
        }

        if (player->m_timerAnimation > (*lastTimeAnimation) + 60) {
            (*lastTimeAnimation) = player->m_timerAnimation;

            if (player->m_sprite.x < 138) {
                player->m_sprite.x += 69;
            } else {
                player->m_isSquating = 0;
            }
        }
    }
}
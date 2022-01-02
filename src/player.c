#include "../include/player.h"

/**
 * @brief Player_init(void) is a function to init the main player and return all the stat of the player
 * 
 * @return Player 
 */
Player player_init(Screen *screen) {
    
    Player player;

    player.m_life = 100;
    player.m_direction = 0; //look on the right

    player.m_timerAnimation = 0;
    player.m_timerMove = 0;

    //set the position of the rect to get the picture
    player.m_sprite.x = 17;
    player.m_sprite.y = 10;
    player.m_sprite.h = 33;
    player.m_sprite.w = 20;   

    player.m_spritesheet_surface = NULL;
    player.m_spritesheet_texture = NULL;


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

    //set the position on the screen of the player
    player.m_position.x = 400;
    player.m_position.y = 100;
    player.m_position.w = 46;
    player.m_position.h = 70;

    //set pointers of function
    player.display = &player_display;
    player.move = &player_move;

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
    SDL_RenderCopy(screen->m_render, player->m_spritesheet_texture, &player->m_sprite, &player->m_position);
}

/**
 * @brief player_move is a function to set all the movement of the player and animation
 *        the function is separated in 3 if
 * 
 * @param player 
 */
void player_move(Player *player) {
    const Uint8 *keyboard = SDL_GetKeyboardState(NULL);
    int isMoving = 0; //if isMoving equals 3 the player doesn't move else the player move (to define the standby player animation)
    static int lastTimeAnimation = 0;  //this variable will stock the timeAnimation + the time (it is static to save the value)
    
    player->m_timerAnimation = SDL_GetTicks(); //get the time

    //condition to move left/right/squat
    if (keyboard[SDL_SCANCODE_RIGHT]) { //move to the right

    } else if (keyboard[SDL_SCANCODE_LEFT]) { //move to the left

    } else { //if no move left or right
        isMoving++;
    }

    //condition to jump in more to move left/right
    if (keyboard[SDL_SCANCODE_UP]) { //jump the player

    } else { //if no jump
        isMoving++;
    }

    //confition to attack in more to jump/left/right
    if (keyboard[SDL_SCANCODE_D]) { //the player attack

    } else { //if no attack
        isMoving++;
    }

    //if no keycap is pressed, the player is inactive
    if (isMoving == 3) { //the player is in standby position
        if (player->m_sprite.y != 10) { //if the ordinate isn't on the standby line we put to the correct line and begin the standby at the first frame
            player->m_sprite.y = 10;
            player->m_sprite.x = 17;
        }

        if (player->m_timerAnimation >= lastTimeAnimation + 150) { //the animation is each 150 microseconds
            lastTimeAnimation = player->m_timerAnimation;
            
            if (player->m_sprite.x < 362) {
                player->m_sprite.x += 69; //69 is the ecart between frame on the spritesheet
            } else {
                player->m_sprite.x = 17;
            }
        }
    }

}

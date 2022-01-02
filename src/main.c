#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/screen.h"
#include "../include/player.h"

int initSDL();

/**
 * @brief Function to Init the SDL.
 *        If the initialization is ok the function return 0 else return 1
 * 
 * @return int 
 */
int initSDL() {
    //init the SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return EXIT_FAILURE;
    }
    //init the SDL_image
    if (IMG_Init(IMG_INIT_JPG |IMG_INIT_PNG) == 0) {
        return EXIT_FAILURE;
    }
    //if everything OK
    return EXIT_SUCCESS;
}


int main(int ac, char **av) {

    if (initSDL() == 1) { //init the SDL
        return EXIT_FAILURE;
    }

    Screen screen = screen_init(900, 600, "Plateformer");
    if (screen.init_sdl(&screen) == 1) { //init the SDL variables in Screen structure
        return EXIT_FAILURE;
    }

    Player player = player_init(&screen);

    while (screen.m_isRunning) {
        screen.adaptRender(&screen);
        screen.getEvent(&screen);

        screen.clear(&screen);

        player.move(&player);

        player.display(&screen, &player);
        SDL_RenderPresent(screen.m_render);
        SDL_Delay(60);
    }


    screen.destroy(&screen);
    IMG_Quit();
    SDL_Quit();

    
    return EXIT_SUCCESS;
}
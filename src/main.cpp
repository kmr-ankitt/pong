#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main()
{
	// Initialize SDL components
	SDL_Init(SDL_INIT_VIDEO);

	// Creates a window with the specified position, dimensions, and flags.
	SDL_Window* window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// Game logic
	{
		bool running = true;

		// Continue looping and processing events until user exits
		while (running)
		{
		    // Creates a new event structure queue
			SDL_Event event;
			
			/* 
            * Poll for currently pending events.
            *
            * If `event` is not NULL, the next event is removed from the queue and stored
            * in the SDL_Event structure pointed to by `event`. The 1 returned refers to
            * this event, immediately stored in the SDL Event structure -- not an event
            * to follow.
            *
            * If `event` is NULL, it simply returns 1 if there is an event in the queue,
            * but will not remove it from the queue.
            */
            
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
				else if (event.type == SDL_KEYDOWN)
				{
    				// event.key.keysym.sym returns the key that was pressed
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						running = false;
					}
				}
			}

			// Clear the window to black if no event is detected
			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_RenderClear(renderer);

			//
			// Rendering will happen here
			//

			/* Present the backbuffer
			* SDL_RENDERPresent() Updates the screen with any rendering performed since the previous call.
            *
            * SDL's rendering functions operate on a backbuffer; that is, calling a
            * rendering function such as SDL_RenderDrawLine() does not directly put a
            * line on the screen, but rather updates the backbuffer. 
            *
            * Commonly in graphics, you render to a buffer that is not on screen (i.e., the backbuffer), 
            * and then when ready you swap it with the buffer currently on screen and the frontbuffer 
            * becomes the backbuffer.F
            */
			SDL_RenderPresent(renderer);
		}
	}

	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

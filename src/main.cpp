#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;

/*
*2D Vector class  
*   - x, y are the coordinates of the vector
*   - Here some convienent operators are overloaded so
*     we can do something like `position += velocity * time` 
*/
class Vec2{
    public:
        float x, y;
        
        Vec2() : x(0.0f), y(0.0f) {}
        Vec2(float x, float y): x(x), y(y) {}
        
        Vec2 operator+(Vec2 const& rhs){
            return Vec2(x + rhs.x, y + rhs.y);
        }
        
        Vec2& operator+=(Vec2 const& rhs){
            x += rhs.x;
            y += rhs.y;
            return *this;
        }      

        Vec2 operator*(float rhs){
            return Vec2(x * rhs, y * rhs);
        }
};

class Ball{
    public:
        Vec2 position;
        SDL_Rect rect;
        
        Ball(Vec2 position): position(position){
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            rect.h = BALL_HEIGHT;
            rect.w = BALL_WIDTH;
        }   
        
        void Draw(SDL_Renderer *renderer){
            rect.x = static_cast<int>(position.x);
            rect.y = static_cast<int>(position.y);
            
            // Fills the rectangle on the current rendering target with the drawing color.
            SDL_RenderFillRect(renderer, &rect);
        }
};


int main(){
	// Initialize SDL components
    SDL_Init(SDL_INIT_VIDEO);

	// Creates a window with the specified position, dimensions, and flags.
	SDL_Window* window = SDL_CreateWindow("Pong", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	
	/*
    * Ball object is created and it's initial position is set to the center of the window.
    *   - Half of the ball’s width and height are subtracted from the x and y
	*     values because SDL2 considers the origin of an
	*     object to be the upper left corner
	*/
	Ball ball(Vec2(WINDOW_WIDTH/2.0f - BALL_WIDTH/2.0f , WINDOW_HEIGHT/2.0f - BALL_HEIGHT/2.0f));

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

			// Clear the window to black
			SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_RenderClear(renderer);
			
			// Setting the renderer colour to white 
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			
			/*
			* Drawing the Net
			*    - y%5 is used to draw the dotted line
			*/
			for(int y = 0 ; y < WINDOW_HEIGHT ; ++y ){
			    if(y%5)
		          SDL_RenderDrawPoint(renderer,WINDOW_WIDTH/2, y);
			}
			
			/* 
			* Drawing the Ball
		    */
			ball.Draw(renderer);
			
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

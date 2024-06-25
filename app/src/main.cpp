#include <SDL.h>
#include <ctime>
#include <cstdlib>

const int h = 480;
const int w = 480;

int bresenhams(SDL_Renderer* renderer, int x1, int y1, int x2, int y2)
{
	float dy = y2 - y1;
	float dx = x2 - x1;
	int x_dir=1, y_dir=1;

	if (dy < 0.0) {
		y_dir = -1;
		dy = -dy;
	}
	if (dx < 0.0) {
		x_dir = -1;
		dx = -dx;
	}

	float m = dy / dx;
	int j=0, da_dir, da_end, other_dir,  da_inv=0;

	if (m <= 1.0) {
		// x is the driving axis
		da_end = abs(x2-x1);
		da_dir = x_dir;
		other_dir = y_dir;
	} else {
		// y is the driving axis
		da_inv = 1;
		m = 1/m;
		da_dir = y_dir;
		other_dir = x_dir;
		da_end = y2-y1;
	}

	float e = m - 1;
	int da=0;

	while (da != da_end) {
		if (e > 0.0) {
			j += other_dir;
			e -= 1.0;
		}
		if (!da_inv) {
			SDL_RenderDrawPoint(renderer, x1+da, y1+j);
		} else {
			SDL_RenderDrawPoint(renderer, x1+j, y1+da);
		}
		e += m;
		da += da_dir;
	}
	return 0;
}

int main()
{
	SDL_Window* window = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return 1;
	}

	window = SDL_CreateWindow("xgraph", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		h, w, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);

	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	int exit = 0;

	while (!exit) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			exit = 1;
			break;
		};
		}
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff );
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff );

		// (x1, y1, x2, y2)
		SDL_RenderDrawLine(renderer, w/2, 0, w/2, h); 
		SDL_RenderDrawLine(renderer, 0, h/2, w, h/2); 

		int dw = 10;
		int tick_height = 8;
		for (int i=0; i<w; i+=dw) {
			SDL_RenderDrawLine(renderer, i, (w/2)-(tick_height/2), i, (w/2)+(tick_height/2)); 
			SDL_RenderDrawLine(renderer, (h/2)-(tick_height/2), i, (h/2)+(tick_height/2), i); 
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0xff, 0xff );

		bresenhams(renderer, 0, 0, 400, 100);
		bresenhams(renderer, 100, 200, 400, 100); // dy=100-200=-200 dx=400-100=300 dy/dx=-2/3
		bresenhams(renderer, 0, 400, 200, 0); // dy=0-400=-400 dx=200-0=200 dy/dx=-2
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

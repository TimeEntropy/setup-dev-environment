#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
	SDL_Window*   window   = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool          running  = true;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
		"test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		800,
		SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI
	);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	while (running) {
	
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { running = false; break; }
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		{

		}
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:03:15 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/18 19:52:45 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Event event;
	SDL_Surface *surface;
	t_env   *env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		print_error(1, NULL);
	init_env(env);
	img(env);
	fill_tab(env);
	init_thread(env);

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return 3;
	}

	window = SDL_CreateWindow("SDL_CreateTexture",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			800, 600,
			SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_ShowCursor(SDL_DISABLE);
	(void)argc;
	(void)argv;
	Uint32	pixels[800 * 600];

	int i = 0;
	while (i < 800 * 600)
	{
		pixels[i] = (0xFF000000 | env->mlx.data[i]);
		i++;
	}
	surface = surface_new(pixels, 800, 600);
	if (surface == NULL) {
		fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
		exit(1);
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL) {
		fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_FreeSurface(surface);
	surface = NULL;
	while (1) {
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
			break;
		if (event.type == SDL_KEYDOWN)
		{
			sdl_keyhook(env, event);
			i = 0;
			while (i < 800 * 600)
			{
				pixels[i] = (0xFF000000 | env->mlx.data[i]);
				i++;
			}
			surface = surface_new(pixels, 800, 600);
			if (surface == NULL) {
				fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
				exit(1);
			}

			texture = SDL_CreateTextureFromSurface(renderer, surface);

			if (texture == NULL) {
				fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
				exit(1);
			}

			SDL_FreeSurface(surface);
			surface = NULL;

		}
		if (event.type == SDL_MOUSEMOTION)
		{
			int x;
			int y;
			SDL_GetMouseState(&x, &y);
			if (x != 400 && y != 300)
			{
				sdl_motion_mouse(env, x, y);
				i = 0;
				while (i < 800 * 600)
				{
					pixels[i] = (0xFF000000 | env->mlx.data[i]);
					i++;
				}
				surface = surface_new(pixels, 800, 600);
				if (surface == NULL) {
					fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
					exit(1);
				}

				texture = SDL_CreateTextureFromSurface(renderer, surface);

				if (texture == NULL) {
					fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
					exit(1);
				}
				SDL_FreeSurface(surface);
				surface = NULL;
				SDL_WarpMouseInWindow(window, 400, 300);
			}
		}
		SDL_SetRenderTarget(renderer, texture);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}

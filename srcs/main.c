/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/06 18:56:38 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		main(void)
{
	t_env			env;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Couldn't initialize SDL: %s", SDL_GetError());
		return (3);
	}
	if (TTF_Init() < 0)
	{
		fprintf(stderr, "init TTF failed: %s\n", SDL_GetError());
		exit(1);
	}
	env.sdl.window = SDL_CreateWindow("Doom nukem",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		W, H, SDL_WINDOW_SHOWN);
	SDL_SetWindowFullscreen(env.sdl.window, SDL_WINDOW_FULLSCREEN);
	env.sdl.renderer = SDL_CreateRenderer(env.sdl.window, -1, 0);
	env.sdl.texture = NULL;
	env.engine.nsectors = 0;
	env.engine.sectors = NULL;
	env.sdl.surface = SDL_CreateRGBSurface(0, W, H, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	env.engine.surface = env.sdl.surface;
	LoadData(&env.engine, &env);
	verify_map(&env.engine);
	init_container(&env);
	sdl_loop(&env);
	UnloadData(env.sdl.texture, env.sdl.renderer, env.sdl.window, &env.engine);
	Mix_FreeChunk(env.sounds.shot);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	return (0);
}

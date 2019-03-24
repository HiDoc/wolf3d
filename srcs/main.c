/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:56:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/19 19:45:28 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_floor(t_env *env)
{
	env->world.surfaces.floors[0].sprite = new_surface("floor/01");
}

int		init_gameplay_env(t_env *env)
{
	return (init_fonts(&env->player.hud.text)
	&& init_consumable(env)
	&& init_character(&env->player)
	&& init_weapon(env)
	&& set_simple_strings(env)
	&& init_hud_container(env));
}

int		main(void)
{
	t_env			env;

	ft_bzero(&env, sizeof(t_env));
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

	/* SDL structure initialize */
	env.sdl.window = SDL_CreateWindow("Doom nukem",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		W, H, SDL_WINDOW_SHOWN);
	// SDL_SetWindowFullscreen(env.sdl.window, SDL_WINDOW_FULLSCREEN);
	env.sdl.renderer = SDL_CreateRenderer(env.sdl.window, -1, 0);
	env.sdl.surface = SDL_CreateRGBSurface(0, W, H, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
	env.sdl.texture = SDL_CreateTexture(env.sdl.renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, W, H);

	ft_bzero(&env.engine, sizeof(t_engine));

	SDL_Cursor* cursor;
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetCursor(cursor);

	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096))
		return (0);
	LoadData(&env.engine, &env);
	if (!init_gameplay_env(&env))
	{
		UnloadData(env.sdl.texture, env.sdl.renderer, env.sdl.window, &env.engine);
		free_ui(&env);
		return (0);
	}
	verify_map(&env.engine);
	init_floor(&env);
	////////////////////////////////////////////
	// initialisation : blame -> sgalasso
	// - penser a destroy ceci a la fin
	printf("OKKKKKKKKKKKK\n");
	if (!(env.arial_font = TTF_OpenFont("rsrc/font/Arial.ttf", 100)))
	{
		ft_putendl(TTF_GetError()); // provisoire
		exit(EXIT_FAILURE); // provisoire, erreur a rediriger
	}
	////////////////////////////////////////////

	init_container(&env);
	sdl_loop(&env);
	UnloadData(env.sdl.texture, env.sdl.renderer, env.sdl.window, &env.engine);
	free_ui(&env);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	SDL_FreeCursor(cursor);
	return (0);
}

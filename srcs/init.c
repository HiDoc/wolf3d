/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:23:15 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/28 15:32:56 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom.h"

int		initialisation_cursor(t_env *env)
{
	SDL_Cursor* cursor;

	(void)env;
	if (!(cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR)))
		return (0);
	SDL_SetCursor(cursor);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (1);
}

int		initialisation_sound_text(t_env *env)
{
	if (TTF_Init() < 0)
	{
		fprintf(stderr, "init TTF failed: %s\n", SDL_GetError());
		exit(1);
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096))
		return (0);
	if (!(env->arial_font = TTF_OpenFont("rsrc/font/Arial.ttf", 100)))
	{
		ft_putendl(TTF_GetError()); // provisoire
		return (0);
	}
	return (1);
}

int		initialisation_sdl(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Couldn't initialize SDL: %s", SDL_GetError());
		return (3);
	}

	/* SDL structure initialize */
	env->sdl.window = SDL_CreateWindow("Doom nukem",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		W, H, SDL_WINDOW_SHOWN);
	// SDL_SetWindowFullscreen(env->sdl.window, SDL_WINDOW_FULLSCREEN);
	env->sdl.renderer = SDL_CreateRenderer(env->sdl.window, -1, 0);
	env->sdl.surface = SDL_CreateRGBSurface(
	0, W, H, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
	env->sdl.texture = SDL_CreateTexture(env->sdl.renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, W, H);
	return (1);
}

int		initialisation(t_env *env)
{

	initialisation_sdl(env);
	initialisation_sound_text(env);
	initialisation_cursor(env);
	return (1);
}
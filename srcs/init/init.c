/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:23:15 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 20:26:06 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	initialisation_sdl(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		doom_error_exit("Doom_nukem error, can't SDL_Init");
	if (!(env->sdl.window = lt_push(SDL_CreateWindow("Doom nukem",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	W, H, SDL_WINDOW_SHOWN), wdw_del)))
		doom_error_exit("Doom_nukem error, can't create window");
	if (!(env->sdl.renderer = lt_push(
	SDL_CreateRenderer(env->sdl.window, -1, SDL_RENDERER_SOFTWARE), rdr_del)))
		doom_error_exit("Doom_nukem error, can't create renderer");
	env->sdl.surface = make_surface(W, H);
	if (!(env->sdl.texture = lt_push(
	SDL_CreateTexture(env->sdl.renderer, SDL_PIXELFORMAT_ARGB32,
	SDL_TEXTUREACCESS_STREAMING, W, H), txr_del)))
		doom_error_exit("Doom_nukem error, can't create texture");
}

static void	initialisation_sound_text(void)
{
	if (TTF_Init() < 0)
		doom_error_exit("Doom_nukem error, can't TTF_Init");
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096))
		doom_error_exit("Doom_nukem error, can't Mix_OpenAudio");
}

static void	initialisation_cursor(void)
{
	SDL_Cursor	*cursor;

	if (!(cursor = lt_push(
	SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR), crs_del)))
		doom_error_exit("Doom_nukem error on SDL_CreateSystemCursor");
	SDL_SetCursor(cursor);
	if ((SDL_SetRelativeMouseMode(SDL_TRUE)) < 0)
		doom_error_exit("Doom_nukem error on SDL_SetRelativeMouseMode");
}

void		init_env(int ac, char **av, t_env *env)
{
	ft_bzero(env, sizeof(t_env));
	env->god_mod = (ac > 1 && !ft_strcmp(av[1], "god")) ? 1 : 0;
	initialisation_sdl(env);
	initialisation_sound_text();
	initialisation_cursor();
	init_rsrc(env);
	init_enemies(env, (t_brain){0, 0, 0, 0, 0, 0, 0, 0, {0, 0}}, -1);
}

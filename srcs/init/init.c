/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:23:15 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/09 00:26:58 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom.h"

static void		initialisation_sdl(t_env *env)
{
	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		doom_error_exit("Doom_nukem error, can't SDL_Init");

	// init window
	if (!(env->sdl.window = lt_push(SDL_CreateWindow("Doom nukem",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			W, H, SDL_WINDOW_SHOWN), wdw_del)))
		doom_error_exit("Doom_nukem error, can't create window");

	// SDL_SetWindowFullscreen(env->sdl.window, SDL_WINDOW_FULLSCREEN);

	// init renderer
	if (!(env->sdl.renderer = lt_push(
			SDL_CreateRenderer(env->sdl.window, -1, 0), rdr_del)))
		doom_error_exit("Doom_nukem error, can't create renderer");

	// init main surface
	if (!(env->sdl.surface = lt_push(
			SDL_CreateRGBSurface(0, W, H, 32,
			0xff000000, 0xff0000, 0xff00, 0xff), srf_del)))
		doom_error_exit("Doom_nukem error, can't create surface");

	// init main texture
	if (!(env->sdl.texture = lt_push(
			SDL_CreateTexture(env->sdl.renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STREAMING, W, H), txr_del)))
		doom_error_exit("Doom_nukem error, can't create texture");
}

static void		initialisation_sound_text(void)
{
	if (TTF_Init() < 0)
		doom_error_exit("Doom_nukem error, can't TTF_Init");
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096))
		doom_error_exit("Doom_nukem error, can't Mix_OpenAudio");
}

static void		initialisation_cursor(void)
{
	SDL_Cursor* cursor;

	if (!(cursor = lt_push(
			SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR), crs_del)))
		doom_error_exit("Doom_nukem error on SDL_CreateSystemCursor");
	SDL_SetCursor(cursor);
	if ((SDL_SetRelativeMouseMode(SDL_TRUE)) < 0)
		doom_error_exit("Doom_nukem error on SDL_SetRelativeMouseMode");
}

void	init_env(int ac, char **av, t_env *env)
{
	ft_bzero(env, sizeof(t_env));
	env->god_mod = (ac > 1 && ft_strcmp(av[1], "god")) ? 1 : 0;

	// init librairies
	initialisation_sdl(env);
	initialisation_sound_text();
	initialisation_cursor();

	// init ressources
	load_fonts(env); // <- lifetime
	load_images(env);
	init_strings(env, 0, 0);

	// init game datas
	init_hud(env);
	init_weapon(env);
	init_enemies(env);
}

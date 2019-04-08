/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:23:15 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/08 23:13:59 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom.h"

static void		initialisation_sdl(t_env *env)
{
	// init SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		doom_error_exit("Doom_nukem error, can't SDL_Init", env);

	// init window
	if (!(env->sdl.window = SDL_CreateWindow("Doom nukem",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN)))
		doom_error_exit("Doom_nukem error, can't create window", env);

	// SDL_SetWindowFullscreen(env->sdl.window, SDL_WINDOW_FULLSCREEN);

	// init renderer
	if (!(env->sdl.renderer = SDL_CreateRenderer(env->sdl.window, -1, 0)))
		doom_error_exit("Doom_nukem error, can't create renderer", env);

	// init main surface
	if (!(env->sdl.surface = SDL_CreateRGBSurface(0, W, H, 32,
					0xff000000, 0xff0000, 0xff00, 0xff)))
		doom_error_exit("Doom_nukem error, can't create surface", env);

	// init main texture
	if (!(env->sdl.texture = SDL_CreateTexture(env->sdl.renderer,
					SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, W, H)))
		doom_error_exit("Doom_nukem error, can't create texture", env);
}

static void		initialisation_sound_text(t_env *env)
{
	if (TTF_Init() < 0)
		doom_error_exit("Doom_nukem error, can't TTF_Init", env);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096))
		doom_error_exit("Doom_nukem error, can't Mix_OpenAudio", env);
}

static void		initialisation_cursor(t_env *env)
{
	SDL_Cursor* cursor;

	if (!(cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR)))
		doom_error_exit("Doom_nukem error on SDL_CreateSystemCursor", env);
	SDL_SetCursor(cursor);
	if ((SDL_SetRelativeMouseMode(SDL_TRUE)) < 0)
		doom_error_exit("Doom_nukem error on SDL_SetRelativeMouseMode", env);
}

void	init_env(int ac, char **av, t_env *env)
{
	ft_bzero(env, sizeof(t_env));
	env->god_mod = (ac > 1 && ft_strcmp(av[1], "god")) ? 1 : 0;

	// init librairies
	initialisation_sdl(env);
	initialisation_sound_text(env);
	initialisation_cursor(env);

	// init ressources
	load_fonts(env);
	load_images(env);
	init_strings(env, 0, 0);

	// init game datas
	init_hud(env);
	init_weapon(env);
	init_enemies(env);
}

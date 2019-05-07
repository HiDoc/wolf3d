/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:23:15 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/07 16:07:45 by abaille          ###   ########.fr       */
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
	SDL_CreateRenderer(env->sdl.window, -1, SDL_RENDERER_SOFTWARE), rdr_del)))
		doom_error_exit("Doom_nukem error, can't create renderer");

	// init main surface
	env->sdl.surface = make_surface(W, H);

	// init main texture
	if (!(env->sdl.texture = lt_push(
	SDL_CreateTexture(env->sdl.renderer, SDL_PIXELFORMAT_ARGB32,
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

void	init_rsrc(t_env *e, int i)
{
	SDL_Surface	*img;
	SDL_Rect	r;
	t_bloc		fi;
	void		(* const f[6])(t_env *) = {
		&load_fonts,
		&load_images,
		&init_sounds,
		&init_blocs_menu,
		&init_hud,
		&init_weapon};
	const char	*state[6] = {"Loading fonts...", "Loading textures...",
	"Loading sounds...", "Loading menu...", "Loading hud elements...",
	"Loading weapons..."};
	TTF_Font	*font;

	e->sdl.keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	if (!(font = lt_push(TTF_OpenFont(F_QTFY, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	ft_bzero(&fi, sizeof(t_bloc));
	img = load_image("./rsrc/img/menu/loadin.png");
	r = (SDL_Rect){W / 5, H / 1.6, 0, H / 24};
	fi.rect = (SDL_Rect){0, 0, W, H};
	// loop_rsrc(e, img, )
	while (1)
	{
		draw_img(e, img, &fi);
		if (++i < 6)
		{
			ui_draw_full_rect(e->sdl.surface, r, 0x47d147ff);
			ui_put_data(e, (t_font){GOLD, state[i], font,
				(t_vtx){W / 1.7, H / 1.4}, W / 50, -1, -1});
			f[i](e);
			r.w += (W / 1.5) / 6;
		}
		ui_draw_full_rect(e->sdl.surface, r, 0x47d147ff);
		(i > 5) ? ui_put_data(e, (t_font){GREEN, "Loading completed", font,
			(t_vtx){W / 1.7, H / 1.4}, W / 50, -1, -1}) : 0;
		ui_put_data(e, (t_font){GOLD, "Continue", font,
			(t_vtx){W / 1.1, H / 100}, W / 60, -1, -1});
		SDL_WaitEvent(&e->sdl.event);
		if (e->sdl.event.type == SDL_KEYDOWN)
			break ;
		SDL_UpdateTexture(e->sdl.texture, NULL,
			e->sdl.surface->pixels, e->sdl.surface->pitch);
		SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, NULL);
		SDL_RenderPresent(e->sdl.renderer);
	}
	lt_release((void**)&img);
	lt_release((void**)&font);
}

void	init_env(int ac, char **av, t_env *env)
{
	ft_bzero(env, sizeof(t_env));
	env->god_mod = (ac > 1 && !ft_strcmp(av[1], "god")) ? 1 : 0;
	// init libraries
	initialisation_sdl(env);
	initialisation_sound_text();
	initialisation_cursor();

	init_rsrc(env, -1);
	init_enemies(env, (t_brain){0, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0}}, -1);
	printf("time enemies: %u\n", SDL_GetTicks());
}

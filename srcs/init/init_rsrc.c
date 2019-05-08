/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rsrc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:25:38 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 19:16:43 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		draw_end_loadin(t_env *e, int i, TTF_Font *font, SDL_Rect r)
{
	ui_draw_full_rect(e->sdl.surface, r, 0x47d147ff);
	if (i > 5)
	{
		put_data(e, (t_font){GREEN, "Loading completed", font,
			(t_vtx){W / 1.7, H / 1.4}, W / 50, -1, -1});
		put_data(e, (t_font){GOLD, "Continue", font,
			(t_vtx){W / 1.1, H / 100}, W / 60, -1, -1});
	}
	SDL_WaitEvent(&e->sdl.event);
	return (e->sdl.event.type == SDL_KEYDOWN);
}

void	loop_rsrc(t_env *e, SDL_Surface *img, char **state, t_bloc fi)
{
	int			i;
	SDL_Rect	r;
	TTF_Font	*font;
	void		(*const f[6])(t_env *) = {&ld_fonts, &ld_img, &ld_sound,
				&init_bl_menu, &init_hud, &init_weapon};

	r = (SDL_Rect){W / 5, H / 1.6, 0, H / 24};
	if (!(font = lt_push(TTF_OpenFont(F_QTFY, 100), ttf_del)))
		doom_error_exit("Doom_nukem error on TTF_OpenFont");
	i = -1;
	while (1 && update_render(e))
	{
		draw_img(e, img, &fi);
		if (++i < 6)
		{
			ui_draw_full_rect(e->sdl.surface, r, 0x47d147ff);
			f[i](e);
			put_data(e, (t_font){GOLD, state[i], font,
				(t_vtx){W / 1.7, H / 1.4}, W / 50, -1, -1});
			r.w += (W / 1.5) / 6;
		}
		if (draw_end_loadin(e, i, font, r))
			break ;
	}
	lt_release((void**)&font);
}

void	init_rsrc(t_env *e)
{
	SDL_Surface	*img;
	t_bloc		fi;
	const char	*state[6] = {"Loading fonts...", "Loading textures...",
	"Loading sounds...", "Loading menu...", "Loading hud elements...",
	"Loading weapons..."};

	e->sdl.keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	ft_bzero(&fi, sizeof(t_bloc));
	img = load_image("./rsrc/img/menu/loadin.png");
	fi.rect = (SDL_Rect){0, 0, W, H};
	loop_rsrc(e, img, (char **)state, fi);
	lt_release((void**)&img);
}

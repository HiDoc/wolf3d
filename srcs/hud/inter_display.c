/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:09:07 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 19:14:24 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_inter(t_env *e, int l)
{
	t_bloc	f;
	int		ref;

	ref = (l % NB_INTER_IMG) + I_INTER1;
	ft_bzero(&f, sizeof(t_bloc));
	f.rect = (SDL_Rect){0, 0, W, H};
	draw_img(e, e->world.surfaces.img_menu[ref].sprite, &f);
	put_data(e, (t_font){M_WHITE, "Continue",
		e->hud.font.quantify, (t_vtx){W / 1.1, H / 100}, W / 60, -1, -1});
	put_data(e, (t_font){M_WHITE, e->levels[l % 3]->text,
		e->hud.font.text, (t_vtx){0, H / 1.2}, W / 40, -1, -1});
}

void	stats_endgame(t_env *e)
{
	int		i;
	char	*t;
	char	*string;
	t_vtx	pos;

	i = -1;
	pos = (t_vtx){W / 4, H / 3};
	while (++i < e->nb_levels)
	{
		t = time_to_str(e->levels[i]->tplay);
		string = ft_itoa(i);
		string = ft_strrjoin("Level ", string);
		string = ft_strljoin(string, " : ");
		string = ft_strljoin(string, t);
		put_data(e, (t_font){GOLD, string, e->hud.font.text,
			pos, W / 40, -1, -1});
		lt_release((void**)&t);
		lt_release((void**)&string);
		pos.y += H / 18;
	}
}

int		update_render(t_env *e)
{
	SDL_UpdateTexture(e->sdl.texture, NULL,
		e->sdl.surface->pixels, e->sdl.surface->pitch);
	SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, NULL);
	SDL_RenderPresent(e->sdl.renderer);
	return (1);
}

void	display_credits(t_env *e)
{
	t_bloc	f;

	ft_bzero(&f, sizeof(t_bloc));
	f.rect = (SDL_Rect){0, 0, W, H};
	e->menu.status.endgame = 2;
	while (e->menu.status.endgame)
	{
		if (e->menu.status.endgame == 2)
		{
			draw_img(e, e->world.surfaces.img_menu[I_ENDGAME].sprite, &f);
			stats_endgame(e);
			print_stats(e, W / 60,
				(t_vtx){W / 3.9, W / 1.7}, (t_vtx){H / 4.5, H / 18});
		}
		if (e->menu.status.endgame == 1)
			draw_img(e, e->world.surfaces.img_menu[I_CREDITS].sprite, &f);
		SDL_WaitEvent(&e->sdl.event);
		if (e->menu.status.endgame == 2
		&& e->sdl.keycodes[SDL_SCANCODE_RETURN])
			e->menu.status.endgame = 1;
		else if (e->menu.status.endgame == 1
		&& e->sdl.keycodes[SDL_SCANCODE_RETURN])
			e->menu.status.endgame = 0;
		update_render(e);
	}
}

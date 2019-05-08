/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 02:21:58 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 02:24:53 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	newgame_blocs(t_env *e, t_bloc *b)
{
	SDL_Rect	r;

	(void)e;
	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	fill_menu(e, b, &r, H / 10);
	b->name = ft_strdup("Return");
	b->limit.v1.x = I_IMAINMENU;
	b->limit.v2.x = e->nb_games + 1;
}

void	key_binding(t_engine *e)
{
	e->keys[I_OUP] = SDL_SCANCODE_W;
	e->keys[I_ODOWN] = SDL_SCANCODE_S;
	e->keys[I_OLEFT] = SDL_SCANCODE_A;
	e->keys[I_ORIGHT] = SDL_SCANCODE_D;
	e->keys[I_OJUMP] = SDL_SCANCODE_SPACE;
	e->keys[I_ODUCK] = SDL_SCANCODE_LCTRL;
	e->keys[I_OINVENTR] = SDL_SCANCODE_TAB;
	e->keys[I_OPICKOPN] = SDL_SCANCODE_E;
	e->keys[I_ORELOAD] = SDL_SCANCODE_R;
	e->keys[I_OJETPACKON] = SDL_SCANCODE_1;
	e->keys[I_OBLUEGEM] = SDL_SCANCODE_2;
	e->keys[I_OGREEGEM] = SDL_SCANCODE_3;
	e->keys[I_OREDGEM] = SDL_SCANCODE_4;
	e->keys[I_OPURPGEM] = SDL_SCANCODE_5;
}

void	options_blocs(t_env *e, t_bloc *data)
{
	SDL_Rect	r;
	int			i;

	key_binding(&e->engine);
	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	fill_menu(e, &data[NB_OPT_KEY], &r, H / 10);
	r = (SDL_Rect){W / 1.2, H / 4, W / 45, 0};
	fill_menu(e, &data[NB_OPT_KEY + 1], &r, H / 10);
	r = (SDL_Rect){W / 2.6, H / 3.1, W / 45, 0};
	fill_menu(e, &data[0], &r, H / 10);
	data[0].limit.v1.x = I_IOPT;
	data[0].limit.v2.x = NB_OPT_MENU;
	r.y = H / 2;
	i = 0;
	while (++i < NB_OPT_KEY)
	{
		i == I_OPICKOPN ? r.y = H / 2 : 0;
		fill_menu(e, &data[i], &r, H / 15);
		data[i].rect.x = i < I_OPICKOPN ? W / 6.5 : W / 1.9;
	}
}

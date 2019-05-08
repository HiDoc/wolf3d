/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:37:42 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 19:10:42 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		fill_menu(t_env *e, t_bloc *b, SDL_Rect *r, float s)
{
	SDL_Surface	*img;

	img = e->world.surfaces.img_menu[I_IBTN].sprite;
	b->rect.x = r->x;
	b->rect.y = r->y;
	b->rect.w = r->w;
	b->cross = (t_mbloc){
	{b->rect.x - W / 15, b->rect.y + H / 200, W / 25, W / 25}, img};
	b->use.rect.w = r->w;
	r->y += s;
}

static void	mainmenu_blocs(t_env *env, t_bloc *data)
{
	SDL_Rect	r;

	r = (SDL_Rect){W / 2, H / 2.25, W / 23.53f, 0};
	fill_menu(env, &data[0], &r, H / 10);
	data[0].limit.v1.x = I_IMAINMENU;
	data[0].limit.v2.x = NB_BL_NG;
	fill_menu(env, &data[1], &r, H / 10);
	fill_menu(env, &data[2], &r, H / 10);
	fill_menu(env, &data[3], &r, H / 10);
}

static void	ingame_blocs(t_env *e, t_bloc *data)
{
	SDL_Rect	r;

	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	fill_menu(e, &data[3], &r, H / 10);
	data[0].limit.v1.x = I_INGAME;
	data[0].limit.v2.x = NB_BLOC_IG;
	r = (SDL_Rect){W / 2, H / 2.5, W / 27, 0};
	fill_menu(e, &data[0], &r, H / 10);
	fill_menu(e, &data[1], &r, H / 10);
	fill_menu(e, &data[2], &r, H / 10);
}

static void	loadgame_blocs(t_env *e, t_bloc **b)
{
	SDL_Rect	r;

	(void)e;
	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	*b = ft_memalloc(sizeof(t_bloc));
	fill_menu(e, *b, &r, H / 10);
	(*b)->name = ft_strdup("Return");
	(*b)->limit.v1.x = I_LOADMENU;
	(*b)->limit.v2.x = e->menu.status.nb_save + 1;
	(*b)->next = NULL;
}

void		init_bl_menu(t_env *env)
{
	t_menu		*menu;
	SDL_Rect	r;

	menu = &env->menu;
	menu->status.on = 1;
	menu->status.home = 1;
	menu->status.sound = 1;
	menu->status.inter = 1;
	menu->status.msc_vol = MIX_MAX_VOLUME;
	env->stats.save_img = make_surface(W / 10, H / 10);
	r = (SDL_Rect){W / 2, H / 1.17, W / 50, 0};
	mainmenu_blocs(env, menu->main_menu);
	ingame_blocs(env, menu->ingame_menu);
	loadgame_blocs(env, &menu->save);
	options_blocs(env, menu->options_menu);
	newgame_blocs(env, &menu->new_game);
}

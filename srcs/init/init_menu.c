/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:37:42 by abaille           #+#    #+#             */
/*   Updated: 2019/04/19 21:53:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	fill_menu(t_env *e, t_bloc *b, SDL_Rect *r, float s)
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
	data[0].limit.v2.x = NB_BLOC_NG;
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
	// r.x = W - W / 10;
	// fill_menu(env, &data[1], &r, H / 10);
}

static void	loadgame_blocs(t_env *e, t_bloc **b)
{
	SDL_Rect	r;

	(void)e;
	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	*b = ft_memalloc(sizeof(t_bloc));
	fill_menu(e, *b, &r, H / 10);
	// r = (SDL_Rect){W / 2, H / 2.5, W / 40, 0};
	// fill_menu(e, *b, &r, H / 10);
	(*b)->limit.v1.x = I_LOADMENU;
	(*b)->limit.v2.x = e->menu.status.nb_save + 1;
	(*b)->next = NULL;
}

static void	key_binding(t_engine *e)
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

static void	options_blocs(t_env *e, t_bloc *data)
{
	SDL_Rect	r;
	int			i;

	key_binding(&e->engine);
	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	fill_menu(e, &data[NB_OPT_KEY], &r, H / 10);
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


void		init_blocs_menu(t_env *env)
{
	t_menu		*menu;
	SDL_Rect	r;

	menu = &env->menu;
	menu->status.on = 1;
	menu->status.home = 1;
	menu->status.sound = 1;
	create_surface(&env->stats.save_img, (t_vtx){W / 10, H / 10});
	r = (SDL_Rect){W / 2, H / 1.17, W / 50, 0};
	mainmenu_blocs(env, menu->main_menu);
	ingame_blocs(env, menu->ingame_menu);
	loadgame_blocs(env, &menu->save_game);
	options_blocs(env, menu->options_menu);
}


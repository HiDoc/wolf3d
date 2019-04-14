/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:37:42 by abaille           #+#    #+#             */
/*   Updated: 2019/04/14 15:30:42 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	fill_menu(t_env *env, t_bloc *b, SDL_Rect *r)
{
	SDL_Surface	*img;

	img = env->world.surfaces.img_menu[I_IBTN].sprite;
	b->rect.x = r->x;
	b->rect.y = r->y;
	b->rect.w = r->w;
	b->cross = (t_mbloc){
	{b->rect.x - W / 15, b->rect.y + H / 100, W / 25, W / 25}, img};
	b->use.rect.w = r->w;
	r->y += H / 10;
}

static void	mainmenu_blocs(t_env *env, t_bloc *data)
{
	SDL_Rect	r;

	r = (SDL_Rect){W / 2, H / 2.25, W / 23.53f, 0};
	fill_menu(env, &data[0], &r);
	data[0].limit.v1.x = I_IMAINMENU;
	fill_menu(env, &data[1], &r);
	fill_menu(env, &data[2], &r);
	fill_menu(env, &data[3], &r);

}

static void	ingame_blocs(t_env *env, t_bloc *data)
{
	SDL_Rect	r;

	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	fill_menu(env, &data[0], &r);
	data[0].limit.v1.x = I_INGAME;
	r = (SDL_Rect){W / 2, H / 2.5, W / 27, 0};
	fill_menu(env, &data[1], &r);
	fill_menu(env, &data[2], &r);
	fill_menu(env, &data[3], &r);
	// r.x = W - W / 10;
	// fill_menu(env, &data[1], &r);
}

// static void	loadgame_blocs(t_env *env, t_bloc *data)
// {
// 	SDL_Rect	r;

// 	games_ldmenu = ft_memalloc(sizeof(t_bloc) * 2); // realloc si plusieurs saves ?
// 	r = (SDL_Rect){W / 6, H / 2.5, W / 40, 0};
// 	fill_menu(&games_ldmenu[0], &r);
// 	// r.w = W / 40;
// 	// r.y += H / 10;
// 	// fill_menu(env, &data[1], &r);
// }

static void	key_binding(t_menu *m)
{
	m->keys[I_OUP] = SDL_SCANCODE_W;
	m->keys[I_ODOWN] = SDL_SCANCODE_S;
	m->keys[I_OLEFT] = SDL_SCANCODE_A;
	m->keys[I_ORIGHT] = SDL_SCANCODE_D;
	m->keys[I_OJUMP] = SDL_SCANCODE_SPACE;
	m->keys[I_ODUCK] = SDL_SCANCODE_LCTRL;
	m->keys[I_OINVENTR] = SDL_SCANCODE_TAB;
	m->keys[I_OPICK] = SDL_SCANCODE_E;
	m->keys[I_OOPENDOOR] = SDL_SCANCODE_E;
	m->keys[I_OJETPACKON] = SDL_SCANCODE_1;
	m->keys[I_OBLUEGEM] = SDL_SCANCODE_2;
	m->keys[I_OGREEGEM] = SDL_SCANCODE_3;
	m->keys[I_OREDGEM] = SDL_SCANCODE_4;
	m->keys[I_OPURPGEM] = SDL_SCANCODE_5;
}

static void	options_blocs(t_env *e, t_bloc *data)
{
	SDL_Rect	r;
	int			i;

	key_binding(&e->menu);
	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	fill_menu(e, &data[0], &r);
	r = (SDL_Rect){W / 4, r.y - H / 50, W / 45, 0};
	fill_menu(e, &data[1], &r);
	i = -1;
	while (++i < NB_OPT_KEY)
	{
		i == I_OPICK ? r.y = H / 40 : 0;
		fill_menu(e, &data[i + 2], &r);
		data[i + 2].rect.x = i < I_OPICK
		? data[2].rect.x + data[2].rect.w : W / 1.5;
		data[i + 5].rect.y -= H / 20;
	}
}


void		init_blocs_menu(t_env *env)
{
	t_menu		*menu;
	SDL_Rect	r;

	menu = &env->menu;
	menu->status.on = 1;
	menu->status.home = 1;
	r = (SDL_Rect){W / 2, H / 1.17, W / 50, 0};
	mainmenu_blocs(env, menu->main_menu);
	ingame_blocs(env, menu->ingame_menu);
	// loadgame_blocs(env, menu, menu->load_menu);
	options_blocs(env, menu->options_menu);
}


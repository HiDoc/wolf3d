/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:37:42 by abaille           #+#    #+#             */
/*   Updated: 2019/04/12 13:48:02 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	fill_menu(t_env *env, t_bloc *b, t_mbloc em, SDL_Surface * fi)
{
	t_vtx		new_size;
	SDL_Surface	*img;

	img = env->world.surfaces.img_menu[I_IBTN].sprite;
	new_size = (t_vtx){em.sprite->w / (100 / em.rect.w),
	em.sprite->h / (100 / em.rect.w)};
	b->bg_empty = em.sprite;
	b->bg_fill = fi;
	b->rect.w = new_size.x;
	b->rect.h = new_size.y;
	b->rect.x = em.rect.x - b->rect.w / 2;
	b->rect.y = em.rect.y;
	b->cross = (t_mbloc){
	{b->rect.x - W / 15, em.rect.y + H / 98, W / 20, W / 20}, img};
	return (b->rect.h + H / 25);
}

static void	mainmenu_blocs(t_env *env, t_menu *m, t_bloc *data)
{
	SDL_Rect	r;

	r = (SDL_Rect){W / 2, H / 40, W / 17, 0};
	r.y += fill_menu(env, &data[0],
	(t_mbloc){r, m->title[2]}, NULL);
	r.w = W / 27;
	r.y += H / 10;
	r.y += fill_menu(env, &data[1],
	(t_mbloc){r, m->string[I_NEWGAME]}, m->hover[I_NEWGAME]);
	r.y += fill_menu(env, &data[2],
	(t_mbloc){r, m->string[I_LOADGAME]}, m->hover[I_LOADGAME]);
	r.y += fill_menu(env, &data[3],
	(t_mbloc){r, m->string[I_OPTIONS]}, m->hover[I_OPTIONS]);
	fill_menu(env, &data[4],
	(t_mbloc){r, m->string[I_QUIT]}, m->hover[I_QUIT]);

}

static void	ingame_blocs(t_env *env, t_menu *m, t_bloc *data)
{
	SDL_Rect	r;

	r = (SDL_Rect){W / 2, H / 50, W / 17, 0};
	r.y += fill_menu(env, &data[0],
	(t_mbloc){r, m->title[3]}, NULL);
	r.w = W / 27;
	r.y += H / 10;
	r.y += fill_menu(env, &data[1],
	(t_mbloc){r, m->string[I_SAVE]}, m->hover[I_SAVE]);
	r.y += fill_menu(env, &data[2],
	(t_mbloc){r, m->string[I_OPTIONS]}, m->hover[I_OPTIONS]);
	r.y += fill_menu(env, &data[3],
	(t_mbloc){r, m->string[I_MAINMENU]}, m->hover[I_MAINMENU]);
	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	fill_menu(env, &data[4],
	(t_mbloc){r, m->string[I_RETURN]}, NULL);
	r.x = W - W / 10;
	fill_menu(env, &data[5],
	(t_mbloc){r, m->string[I_SAVED]}, NULL);
}

static void	loadgame_blocs(t_env *env, t_menu *m, t_bloc *data)
{
	SDL_Rect	r;

	r = (SDL_Rect){W / 2, H / 50, W / 17, 0};
	r.y += fill_menu(env, &data[0],
	(t_mbloc){r, m->title[4]}, NULL);
	r.w = W / 40;
	r.y += H / 10;
	fill_menu(env, &data[1],
	(t_mbloc){r, m->string[I_NOSAVE]}, NULL);
}

static void	key_binding(t_menu *m)
{
	m->keys[I_OUP] = SDL_SCANCODE_W;
	m->keys[I_ODOWN] = SDL_SCANCODE_S;
	m->keys[I_OLEFT] = SDL_SCANCODE_A;
	m->keys[I_ORIGHT] = SDL_SCANCODE_D;
	m->keys[I_OJUMP] = SDL_SCANCODE_SPACE;
	m->keys[I_ODUCK] = SDL_SCANCODE_LCTRL;
	m->keys[I_OPICK] = SDL_SCANCODE_E;
	m->keys[I_OOPENDOOR] = SDL_SCANCODE_E;
	m->keys[I_OINVENTR] = SDL_SCANCODE_TAB;
	m->keys[I_OJETPACKON] = SDL_SCANCODE_1;
	m->keys[I_OBLUEGEM] = SDL_SCANCODE_2;
	m->keys[I_OGREEGEM] = SDL_SCANCODE_3;
	m->keys[I_OREDGEM] = SDL_SCANCODE_4;
	m->keys[I_OPURPGEM] = SDL_SCANCODE_5;
}

static void	options_blocs(t_env *env, t_menu *m, t_bloc *data)
{
	SDL_Rect	r;
	int			i;

	key_binding(m);
	r = (SDL_Rect){W / 2, H / 70, W / 17, 0};
	r.y += fill_menu(env, &data[0], (t_mbloc){r, m->title[5]}, NULL);
	r = (SDL_Rect){W / 4, r.y, W / 37, 0};
	r.y += fill_menu(env, &data[1], (t_mbloc){r, m->string[I_OSOUND]}, NULL);
	r.y += fill_menu(env, &data[2], (t_mbloc){r, m->string[I_OCOMMANDS]}, NULL);
	r.y += fill_menu(env, &data[3],
	(t_mbloc){r, m->string[I_OON]}, m->string[I_OOFF]);
	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	r.y += fill_menu(env, &data[4], (t_mbloc){r, m->string[I_RETURN]}, NULL);
	r = (SDL_Rect){data[2].rect.x + data[2].rect.w,
	data[2].rect.y + data[2].rect.h, W / 45, 0};
	i = -1;
	while (++i < NB_OPT_KEY)
	{
		i == I_OOPENDOOR ? r.y = data[2].rect.y + data[2].rect.h : 0;
		r.y += fill_menu(env, &data[i + 5], (t_mbloc){r, m->opt_str[i]}, NULL);
		data[i + 5].rect.x = i < I_OOPENDOOR
		? data[2].rect.x + data[2].rect.w : W / 1.5;
		data[i + 5].rect.y -= H / 25;
		data[i + 5].use = (t_mbloc){{data[i + 5].rect.x + data[i + 5].rect.w,
		data[i + 5].rect.y, W / 60, 0}, NULL};
	}
}

void		init_blocs_menu(t_env *env)
{
	t_menu		*menu;
	SDL_Rect	r;

	menu = &env->menu;
	r = (SDL_Rect){W / 2, H / 1.17, W / 50, 0};
	fill_menu(env, &menu->mother_menu,
	(t_mbloc){r, menu->title[0]}, menu->title[1]);
	mainmenu_blocs(env, menu, menu->main_menu);
	ingame_blocs(env, menu, menu->ingame_menu);
	loadgame_blocs(env, menu, menu->load_menu);
	options_blocs(env, menu, menu->options_menu);
}
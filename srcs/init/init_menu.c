/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:37:42 by abaille           #+#    #+#             */
/*   Updated: 2019/04/14 02:34:09 by abaille          ###   ########.fr       */
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
	{b->rect.x - W / 15, b->rect.y + H / 98, W / 20, W / 20}, img};
	b->use.rect.w = r->w;
	r->y += H / 25;
}

static void	mainmenu_blocs(t_env *env, t_bloc *data)
{
	SDL_Rect	r;

	r = (SDL_Rect){W / 2, H / 2.5, W / 33, 0};
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

// static void	key_binding(t_menu *m)
// {
// 	m->keys[I_OUP] = SDL_GetKeyFromScancode(SDL_SCANCODE_W);
// 	m->keys[I_ODOWN] = SDL_GetKeyFromScancode(SDL_SCANCODE_S);
// 	m->keys[I_OLEFT] = SDL_GetKeyFromScancode(SDL_SCANCODE_A);
// 	m->keys[I_ORIGHT] = SDL_GetKeyFromScancode(SDL_SCANCODE_D);
// 	m->keys[I_OJUMP] = SDL_GetKeyFromScancode(SDL_SCANCODE_SPACE);
// 	m->keys[I_ODUCK] = SDL_GetKeyFromScancode(SDL_SCANCODE_LCTRL);
// 	m->keys[I_OINVENTR] = SDL_GetKeyFromScancode(SDL_SCANCODE_TAB);
// 	m->keys[I_OPICK] = SDL_GetKeyFromScancode(SDL_SCANCODE_E);
// 	m->keys[I_OOPENDOOR] = SDL_GetKeyFromScancode(SDL_SCANCODE_E);
// 	m->keys[I_OJETPACKON] = SDL_GetKeyFromScancode(SDL_SCANCODE_1);
// 	m->keys[I_OBLUEGEM] = SDL_GetKeyFromScancode(SDL_SCANCODE_2);
// 	m->keys[I_OGREEGEM] = SDL_GetKeyFromScancode(SDL_SCANCODE_3);
// 	m->keys[I_OREDGEM] = SDL_GetKeyFromScancode(SDL_SCANCODE_4);
// 	m->keys[I_OPURPGEM] = SDL_GetKeyFromScancode(SDL_SCANCODE_5);
// }

// static void	options_blocs(t_env *env, t_bloc *data)
// {
// 	SDL_Rect	r;
// 	int			i;

// 	key_binding(m);
// 	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
// 	fill_menu(env, &data[0], &r);
// 	r = (SDL_Rect){W / 4, r.y - H / 50, W / 45, 0};
// 	fill_menu(env, &data[1], &r);
// 	i = -1;
// 	while (++i < NB_OPT_KEY)
// 	{
// 		i == I_OPICK ? r.y = H / 40 : 0;
// 		fill_menu(env, &data[i + 2], &r);
// 		data[i + 2].rect.x = i < I_OPICK
// 		? data[2].rect.x + data[2].rect.w : W / 1.5;
// 		data[i + 5].rect.y -= H / 20;
// 	}
// }

void		getsizebloc_n_draw(t_env *e, t_font d, t_bloc *b)
{
	t_vtx		n_size;
	SDL_Surface	*tmp;

	tmp = ui_create_simple_string((t_font){d.color,
	d.str, d.font, {0, 0}, 0, -1, -1});
	n_size = (t_vtx){tmp->w / (100 / b->use.rect.w), tmp->h / (100 / b->use.rect.w)};
	b->rect.w = n_size.x;
	b->rect.h = n_size.y;
	draw_img(e, tmp, b);
	lt_release(tmp);
}

void		draw_bloc_pack(t_env *e, t_bloc *b, const char **s, int limit)
{
	int	i;
	SDL_Color	c;
	t_font		d;
	t_bloc		f;

	i = -1;
	while (++i < limit)
	{
		c = e->menu.status.current == i ? GOLD : WHITE;
		d = (t_font){c, s[i], e->hud.text.deadfont,
		(t_vtx){b[i].rect.x, b[i].rect.y}, 0, -1, -1};
		getsizebloc_n_draw(e, d, &b[i]);
		ft_bzero(&f, sizeof(t_bloc));
		f.rect = b[i].cross.rect;
		e->menu.status.current == i ? draw_img(e, b[i].cross.sprite, &f) : 0;
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
	// fill_menu(env, &menu->mother_menu, r);
	mainmenu_blocs(env, menu->main_menu);
	ingame_blocs(env, menu->ingame_menu);
	// loadgame_blocs(env, menu, menu->load_menu);
	// options_blocs(env, menu, menu->options_menu);
}

void	draw_page_menu(t_env *e, t_bloc *b, const char **s, int limit)
{
	t_bloc	fill;

	ft_bzero(&fill, sizeof(t_bloc));
	fill.rect = (SDL_Rect){0, 0, W, H};
	draw_img(e, e->world.surfaces.img_menu[(int)b[0].limit.v1.x].sprite, &fill);
	draw_bloc_pack(e, b, s, limit);
}

void	draw_menu(t_env *e)
{
	const char	*mainmenu[NB_BLOC_NG] = {S_NEWGAME, S_LOADGAME, S_OPTIONS, S_QUIT};
	const char	*ingame[NB_BLOC_IG] = {S_RETURN, S_SAVE, S_OPTIONS, S_MAINMENU};
	t_bloc		fill;
	t_menu		*m;

	ft_bzero(&fill, sizeof(t_bloc));
	fill.rect = (SDL_Rect){0, 0, W, H};
	m = &e->menu;
	m->status.home ? draw_img(e, e->world.surfaces.img_menu[I_IHOME].sprite, &fill) : 0;
	m->status.main_menu ? draw_page_menu(e, m->main_menu, mainmenu, NB_BLOC_NG) : 0;
	if (m->status.load_menu)
	{
		draw_page_menu(e, m->games_ldmenu, (const char**)"", 0);
		if (!m->status.nb_save)
			ui_put_data(e, (t_font){WHITE, "No save yet", e->hud.text.deadfont,
			(t_vtx){W / 3, H / 2.5}, W / 40, -1, -1});
	}	// if (m->status.new_game)
	// if (m->status.options_menu)
	// {
	// 	draw_page_menu(env, m->options_menu, I_ILOAD_OPT, NB_OPT_MENU - NB_OPT_KEY);
	// 	draw_keys_options_menu(env, m->options_menu, m->keys);
	// }
	if (m->status.ingame_menu)
		draw_page_menu(e, m->ingame_menu, ingame, NB_BLOC_IG);

}
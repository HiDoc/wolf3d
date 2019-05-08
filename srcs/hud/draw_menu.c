/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:48:04 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 17:46:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	getsizebloc_n_draw(t_env *e, t_font d, t_bloc *b, int l)
{
	t_vtx		n_size;
	SDL_Rect	f;
	SDL_Surface	*tmp;

	tmp = make_string((t_font){d.color, d.str, d.font, {0, 0}, 0, -1, -1});
	n_size = (t_vtx){tmp->w / (100 / b->use.rect.w),
		tmp->h / (100 / b->use.rect.w)};
	b->rect.w = n_size.x;
	b->rect.h = n_size.y;
	f = b->rect;
	l < NB_OPT_MENU ? f.x = b->rect.x - b->rect.w / 2 : 0;
	l < NB_OPT_MENU ? b->cross.rect.x = f.x - b->cross.rect.w - H / 50 : 0;
	draw_scaled_string(e->sdl.surface, (t_font){d.color, "", d.font, {f.x, f.y},
		b->use.rect.w, -1, -1}, tmp, (t_vtx){0, 0});
	lt_release((void**)&tmp);
}

void	render_menu(t_env *e, t_bloc *b, const char **s, int limit)
{
	int			i;
	char		*p;
	t_bloc		f;
	t_font		d;
	t_status	*st;

	st = &e->menu.status;
	ft_bzero(&f, sizeof(t_bloc));
	f.rect = (SDL_Rect){0, 0, W, H};
	draw_img(e, e->world.surfaces.img_menu[(int)b[0].limit.v1.x].sprite, &f);
	i = -1;
	while (++i < limit)
	{
		p = which_str_menu(e, limit, s[i], i);
		d = (t_font){st->cur == i ? M_GOLD : M_WHITE,
		p, e->hud.font.quantify, (t_vtx){b[i].rect.x, b[i].rect.y}, 0, -1, -1};
		getsizebloc_n_draw(e, d, &b[i], limit);
		f.rect = b[i].cross.rect;
		st->cur == i && !st->options_menu && !st->load_menu
		&& (st->main_menu || (st->ingame && i != limit - 1))
		? draw_img(e, b[i].cross.sprite, &f) : 0;
		lt_release((void**)&s);
	}
}

void	draw_saves(t_env *e, t_bloc *b)
{
	t_bloc		*cur;
	SDL_Rect	r;
	t_bloc		f;
	int			i;

	ft_bzero(&f, sizeof(t_bloc));
	cur = b->next;
	i = e->menu.status.start;
	while (cur && ++i < e->menu.status.end)
	{
		put_data(e, (t_font){
			i == (e->menu.status.cur + e->menu.status.start)
			? GOLD : M_WHITE, cur->name, e->hud.font.quantify,
			(t_vtx){r.x, r.y}, W / 60, -1, -1});
		f.rect = cur->use.rect;
		r = cur->use.rect;
		draw_img(e, cur->use.sprite, &f);
		r.y += H / 10;
		cur = cur->next;
	}
}

void	draw_games(t_env *e)
{
	SDL_Rect	r;
	int			i;

	i = -1;
	r = (SDL_Rect){W / 10, H / 20, W / 60, 0};
	put_data(e, (t_font){
		(e->menu.status.cur == e->nb_games)
		? GOLD : M_WHITE, e->menu.new_game.name, e->hud.font.quantify,
		(t_vtx){r.x, r.y}, r.w, -1, -1});
	r = (SDL_Rect){W / 4, H / 3, W / 60, 0};
	if (e->games)
	{
		while (e->games[++i] && i < e->nb_games)
		{
			put_data(e, (t_font){
				i == (e->menu.status.cur)
				? GOLD : M_WHITE, e->games[i], e->hud.font.quantify,
				(t_vtx){r.x, r.y}, r.w, -1, -1});
			r.y += H / 10;
		}
	}
}

void	draw_menu(t_env *e)
{
	t_bloc		f;
	t_status	*s;
	const char	*mainmenu[NB_BL_NG] = {S_NGAME, S_LGAME, S_OPTIONS, S_QUIT};
	const char	*ingame[NB_BLOC_IG] = {S_SAVE, S_OPTIONS, S_MAINMENU, S_RETURN};
	const char	*options[NB_OPT_MENU] = {"   < >", S_OUP, S_ODOWN, S_OLEFT,
	S_ORIGHT, S_OJUMP, S_ODUCK, S_OINVENTR, S_OPICK, S_ORELOAD, S_OJETPACKON,
	S_OBLUEGEM, S_OGREEGEM, S_OREDGEM, S_OPURPGEM, S_RETURN, S_RESET};

	ft_bzero(&f, sizeof(t_bloc));
	f.rect = (SDL_Rect){0, 0, W, H};
	s = &e->menu.status;
	s->home ? draw_img(e, e->world.surfaces.img_menu[I_IHOME].sprite, &f) : 0;
	s->main_menu ? render_menu(e, e->menu.main_menu, mainmenu, NB_BL_NG) : 0;
	(s->gameover)
		? draw_img(e, e->world.surfaces.img_menu[I_GAMEOVER].sprite, &f) : 0;
	(s->gameover) ? print_stats(e, W / 40, (t_vtx){W / 3.9, W / 1.7},
		(t_vtx){H / 4.5, H / 18}) : 0;
	(s->ingame) ? render_menu(e, e->menu.ingame_menu, ingame, NB_BLOC_IG) : 0;
	(s->options_menu)
		? render_menu(e, e->menu.options_menu, options, NB_OPT_MENU) : 0;
	if (s->new_game)
	{
		draw_img(e, e->world.surfaces.img_menu[I_INEWGAME].sprite, &f);
		draw_games(e);
	}
}

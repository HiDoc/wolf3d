/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:48:04 by abaille           #+#    #+#             */
/*   Updated: 2019/04/22 19:04:03 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom.h"

void		getsizebloc_n_draw(t_env *e, t_font d, t_bloc *b, int l)
{
	t_vtx		n_size;
	t_bloc		f;
	SDL_Surface	*tmp;

	ft_bzero(&f, sizeof(t_bloc));
	tmp = make_string((t_font){d.color, d.str, d.font, {0, 0}, 0, -1, -1});
	n_size = (t_vtx){tmp->w / (100 / b->use.rect.w),
		tmp->h / (100 / b->use.rect.w)};
	b->rect.w = n_size.x;
	b->rect.h = n_size.y;
	f.rect = b->rect;
	l < NB_OPT_MENU ? f.rect.x = b->rect.x - b->rect.w / 2 : 0;
	l < NB_OPT_MENU ? b->cross.rect.x = f.rect.x - b->cross.rect.w - H / 50 : 0;
	draw_img(e, tmp, &f);
	lt_release(tmp);
}

void		draw_page_menu(t_env *e, t_bloc *b, const char **s, int limit)
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
		if (limit == NB_OPT_MENU && !i)
			p = ft_strljoin(ft_itoa(st->msc_vol), (char*)s[i]);
		else if (limit != NB_OPT_MENU || (st->current == i && st->key_change))
			p = ft_strdup(s[i]);
		else
			p = ft_strjoin(s[i], (char*)SDL_GetScancodeName(e->engine.keys[i]));
		d = (t_font){st->current == i ? M_GOLD : M_WHITE,
		p, e->hud.text.quantify, (t_vtx){b[i].rect.x, b[i].rect.y}, 0, -1, -1};
		getsizebloc_n_draw(e, d, &b[i], limit);
		f.rect = b[i].cross.rect;
		st->current == i && !st->options_menu && !st->load_menu
		&& (st->main_menu || (st->ingame_menu && i != limit - 1))
		? draw_img(e, b[i].cross.sprite, &f) : 0;
		lt_release(s);
	}
}

void	draw_saves(t_env *e, t_bloc *b)
{
	t_bloc 		*cur;
	SDL_Rect	r;
	t_bloc		f;
	int			i;

	ft_bzero(&f, sizeof(t_bloc));
	cur = b->next;
	i = e->menu.status.start;
	// r = (SDL_Rect){}
	while (cur && ++i < e->menu.status.end)
	{
		ui_put_data(e, (t_font){
			i == (e->menu.status.current + e->menu.status.start)
			? GOLD : M_WHITE, cur->name, e->hud.text.quantify,
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
	ui_put_data(e, (t_font){
		(e->menu.status.current == e->nb_games)
		? GOLD : M_WHITE, e->menu.new_game.name, e->hud.text.quantify,
		(t_vtx){r.x, r.y}, r.w, -1, -1});
	r = (SDL_Rect){W / 4, H / 3, W / 60, 0};
	if (e->games)
	{
		while (e->games[++i] && i < e->nb_games)
		{
			ui_put_data(e, (t_font){
				i == (e->menu.status.current)
				? GOLD : M_WHITE, e->games[i], e->hud.text.quantify,
				(t_vtx){r.x, r.y}, r.w, -1, -1});
			r.y += H / 10;
		}
	}
}

void	draw_menu(t_env *e)
{
	t_bloc		f;
	t_menu		*m;
	const char	*mainmenu[NB_BLOC_NG] = {S_NEWGAME, S_LOADGAME, S_OPTIONS, S_QUIT};
	const char	*ingame[NB_BLOC_IG] = {S_SAVE, S_OPTIONS, S_MAINMENU, S_RETURN};
	const char	*options[NB_OPT_MENU] = {"   < >", S_OUP, S_ODOWN, S_OLEFT,
	S_ORIGHT, S_OJUMP, S_ODUCK, S_OINVENTR, S_OPICK, S_ORELOAD, S_OJETPACKON,
	S_OBLUEGEM, S_OGREEGEM, S_OREDGEM, S_OPURPGEM, S_RETURN, S_RESET};

	ft_bzero(&f, sizeof(t_bloc));
	f.rect = (SDL_Rect){0, 0, W, H};
	m = &e->menu;
	m->status.home ? draw_img(e,
		e->world.surfaces.img_menu[I_IHOME].sprite, &f) : 0;
	m->status.main_menu ? draw_page_menu(e, m->main_menu, mainmenu, NB_BLOC_NG) : 0;
	if (m->status.load_menu)
	{
		draw_img(e, e->world.surfaces.img_menu[I_LOADMENU].sprite, &f);
		ui_put_data(e, (t_font){
			e->menu.status.current == e->menu.status.nb_save ? GOLD : M_WHITE,
			m->save_game->name, e->hud.text.quantify, (t_vtx){m->save_game->rect.x,
			m->save_game->rect.y}, m->save_game->rect.w, -1, -1});
		if (m->status.nb_save)
			draw_saves(e, m->save_game);
		else
			ui_put_data(e, (t_font){M_WHITE, "No save yet", e->hud.text.quantify,
			(t_vtx){W / 2.5, H / 2.5}, W / 40, -1, -1});
	}
	(m->status.ingame_menu)
		? draw_page_menu(e, m->ingame_menu, ingame, NB_BLOC_IG) : 0;
	(m->status.options_menu)
		? draw_page_menu(e, m->options_menu, options, NB_OPT_MENU) : 0;
	if (m->status.new_game)
	{
		draw_img(e, e->world.surfaces.img_menu[I_INEWGAME].sprite, &f);
		draw_games(e);
	}

}

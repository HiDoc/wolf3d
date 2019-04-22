/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:48:04 by abaille           #+#    #+#             */
/*   Updated: 2019/04/21 14:16:23 by sgalasso         ###   ########.fr       */
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

	ft_bzero(&f, sizeof(t_bloc));
	f.rect = (SDL_Rect){0, 0, W, H};
	draw_img(e, e->world.surfaces.img_menu[(int)b[0].limit.v1.x].sprite, &f);
	i = -1;
	while (++i < limit)
	{
		if (limit != NB_OPT_MENU || (e->menu.status.current == i
		&& e->menu.status.key_change) || (limit == NB_OPT_MENU && !i))
			p = ft_strdup(s[limit == NB_OPT_MENU && !i
			&& !e->menu.status.sound ? limit : i]);
		else
			p = ft_strjoin(s[i], (char*)SDL_GetScancodeName(e->engine.keys[i]));
		d = (t_font){e->menu.status.current == i ? M_GOLD : M_WHITE,
		p, e->hud.text.quantify, (t_vtx){b[i].rect.x, b[i].rect.y}, 0, -1, -1};
		getsizebloc_n_draw(e, d, &b[i], limit);
		f.rect = b[i].cross.rect;
		e->menu.status.current == i && limit < NB_OPT_MENU
		&& (i < limit - 1 || limit == NB_BLOC_NG)
		? draw_img(e, b[i].cross.sprite, &f) : 0;
		lt_release(s);
	}
}

void	draw_menu(t_env *e)
{
	t_bloc		f;
	t_menu		*m;
	const char	*mainmenu[NB_BLOC_NG] = {S_NEWGAME, S_LOADGAME, S_OPTIONS, S_QUIT};
	const char	*ingame[NB_BLOC_IG] = {S_SAVE, S_OPTIONS, S_MAINMENU, S_RETURN};
	const char	*options[NB_OPT_MENU + 1] = {S_OON, S_OUP, S_ODOWN, S_OLEFT,
	S_ORIGHT, S_OJUMP, S_ODUCK, S_OINVENTR, S_OPICK, S_ORELOAD, S_OJETPACKON,
	S_OBLUEGEM, S_OGREEGEM, S_OREDGEM, S_OPURPGEM, S_RETURN, S_OOFF};

	ft_bzero(&f, sizeof(t_bloc));
	f.rect = (SDL_Rect){0, 0, W, H};
	m = &e->menu;
	m->status.home ? draw_img(e,
		e->world.surfaces.img_menu[I_IHOME].sprite, &f) : 0;
	m->status.main_menu ? draw_page_menu(e, m->main_menu, mainmenu, NB_BLOC_NG) : 0;
	if (m->status.load_menu)
	{
		draw_page_menu(e, m->games_ldmenu, ingame, m->status.nb_save + 1);
		if (!m->status.nb_save)
			ui_put_data(e, (t_font){M_WHITE, "No save yet", e->hud.text.quantify,
			(t_vtx){W / 2.5, H / 2.5}, W / 40, -1, -1});
	}
	m->status.ingame_menu
		? draw_page_menu(e, m->ingame_menu, ingame, NB_BLOC_IG) : 0;
	m->status.options_menu
		? draw_page_menu(e, m->options_menu, options, NB_OPT_MENU) : 0;
}

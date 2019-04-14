/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:48:04 by abaille           #+#    #+#             */
/*   Updated: 2019/04/14 15:29:58 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom.h"

void		getsizebloc_n_draw(t_env *e, t_font d, t_bloc *b)
{
	t_vtx		n_size;
	SDL_Surface	*tmp;
	t_bloc		f;

	ft_bzero(&f, sizeof(t_bloc));
	tmp = ui_create_simple_string((t_font){d.color,
	d.str, d.font, {0, 0}, 0, -1, -1});
	n_size = (t_vtx){tmp->w / (100 / b->use.rect.w), tmp->h / (100 / b->use.rect.w)};
	b->rect.w = n_size.x;
	b->rect.h = n_size.y;
	f.rect = (SDL_Rect){b->rect.x - b->rect.w / 2, b->rect.y, b->rect.w, b->rect.h};
	draw_img(e, tmp, &f);
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
		c = e->menu.status.current == i ? M_GOLD : WHITE;
		d = (t_font){c, s[i], e->hud.text.deadfont,
		(t_vtx){b[i].rect.x, b[i].rect.y}, 0, -1, -1};
		getsizebloc_n_draw(e, d, &b[i]);
		ft_bzero(&f, sizeof(t_bloc));
		f.rect = b[i].cross.rect;
		e->menu.status.current == i ? draw_img(e, b[i].cross.sprite, &f) : 0;
	}
}
void	draw_page_menu(t_env *e, t_bloc *b, const char **s, int limit)
{
	t_bloc	fill;

	ft_bzero(&fill, sizeof(t_bloc));
	fill.rect = (SDL_Rect){0, 0, W, H};
	draw_img(e, e->world.surfaces.img_menu[(int)b[0].limit.v1.x].sprite, &fill);
	draw_bloc_pack(e, b, s, limit);
}

void	draw_keys_options_menu(t_env *e, t_bloc *b, int *k, const char **t)
{
	int			i;
	char		*s;
	t_bloc		fill;
	t_font		d;

	i = 0;
	while (++i < NB_OPT_MENU)
	{
		s = ft_strjoin(t[i], (char*)SDL_GetKeyName(SDL_GetKeyFromScancode(k[i])));
		d = (t_font){WHITE, s, e->hud.text.deadfont, (t_vtx){b[i].rect.x, b[i].rect.y}, 0, -1, -1};
		getsizebloc_n_draw(e, d, &b[i]);
		ft_bzero(&fill, sizeof(t_bloc));
		fill.rect= b[i].cross.rect;
		i == e->menu.status.current ? draw_img(e, b[i].cross.sprite, &fill) : 0;
		lt_release(s);
	}
}

void	draw_menu(t_env *e)
{
	const char	*mainmenu[NB_BLOC_NG] = {S_NEWGAME, S_LOADGAME, S_OPTIONS, S_QUIT};
	const char	*ingame[NB_BLOC_IG] = {S_RETURN, S_SAVE, S_OPTIONS, S_MAINMENU};
	const char	*options[NB_OPT_MENU] = {S_RETURN, S_OON, S_OUP, S_ODOWN, S_OLEFT,
	S_ORIGHT, S_OJUMP, S_ODUCK, S_OINVENTR, S_OPICK, S_OOPENDOOR, S_OJETPACKON,
	S_OBLUEGEM, S_OGREEGEM, S_OREDGEM, S_OPURPGEM};
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
	}
	if (m->status.options_menu)
	{
		draw_page_menu(e, m->options_menu, options, 1);
		draw_keys_options_menu(e, m->options_menu, m->keys, options);
	}
	if (m->status.ingame_menu)
		draw_page_menu(e, m->ingame_menu, ingame, NB_BLOC_IG);

}
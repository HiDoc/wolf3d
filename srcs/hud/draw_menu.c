/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:48:04 by abaille           #+#    #+#             */
/*   Updated: 2019/04/14 01:11:32 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom.h"

// void	draw_bloc(t_env *env, t_bloc *b, SDL_Surface *img)
// {
// 	SDL_Surface	*surf;

// 	create_scaled_surface(&surf, (t_vtx){b->rect.w, b->rect.h});
// 	ui_scaled_copy(img, surf);
// 	draw_img(env, surf, b);
// 	lt_release(surf);
// }

// void	draw_bloc_isvisible(t_env *env, t_bloc *b, int i)
// {
// 	t_bloc	fill;

// 	ft_bzero(&fill, sizeof(t_bloc));
// 	if (env->menu.status.current != i )
// 	{
// 		if (b->bg_empty)
// 			draw_bloc(env, b, b->bg_empty);
// 	}
// 	else
// 	{
// 		if (b->bg_fill)
// 			draw_bloc(env, b, b->bg_fill);
// 		fill.rect = b->cross.rect;
// 		if (!b->is_visible)
// 			draw_img(env, b->cross.sprite, &fill);
// 	}

// }

// void	draw_page_menu(t_env *env, t_bloc *b, int index, int limit)
// {
// 	t_bloc		fill;
// 	int			i;

// 	ft_bzero(&fill, sizeof(t_bloc));
// 	fill.rect = (SDL_Rect){0, 0, W, H};
// 	draw_img(env, env->world.surfaces.img_menu[index].sprite, &fill);
// 	i = -1;
// 	while (++i < limit)
// 		draw_bloc_isvisible(env, &b[i], i);
// }


// void	draw_keys_options_menu(t_env *e, t_bloc *b, int *k)
// {
// 	int			i;
// 	char		*s;
// 	t_vtx		n_size;
// 	t_bloc		fill;
// 	SDL_Surface	*tmp;
// 	const char	*opt[NB_OPT_KEY] = {S_OUP, S_ODOWN, S_OLEFT, S_ORIGHT,
// 	S_OJUMP, S_ODUCK, S_OINVENTR, S_OPICK, S_OOPENDOOR, S_OJETPACKON,
// 	S_OBLUEGEM, S_OGREEGEM, S_OREDGEM, S_OPURPGEM};

// 	i = -1;
// 	while (++i < NB_OPT_KEY)
// 	{
// 		s = ft_strjoin(opt[i], (char*)SDL_GetKeyName(k[i]));
// 		tmp = ui_create_simple_string((t_font){WHITE,
// 		s, e->hud.text.text, {0, 0}, 0, -1, -1});
// 		n_size = (t_vtx){tmp->w / (100 / (W / 45)), tmp->h / (100 / (W / 45))};
// 		b[i + 5].rect.w = n_size.x;
// 		b[i + 5].rect.h = n_size.y;
// 		draw_img(e, tmp, &b[i + 5]);
// 		ft_bzero(&fill, sizeof(t_bloc));
// 		fill.rect= b[i + 5].cross.rect;
// 		(i + 5) == e->menu.status.current ? draw_img(e, b[i + 5].cross.sprite, &fill) : 0;
// 		lt_release(tmp);
// 		lt_release(s);
// 	}
// }

// void	draw_menu(t_env *env)
// {
// 	t_menu	*m;

// 	m = &env->menu;
// 	if (m->status.home)
// 		draw_page_menu(env, &m->mother_menu, I_IHOME, 1);
// 	if (m->status.main_menu)
// 		draw_page_menu(env, m->main_menu, I_IMAINMENU, NB_BLOC_NG);
// 	if (m->status.load_menu)
// 		draw_page_menu(env, m->load_menu, I_ILOAD_OPT, 2);
// 		// if (m->status.new_game)
// 	if (m->status.options_menu)
// 	{
// 		draw_page_menu(env, m->options_menu, I_ILOAD_OPT, NB_OPT_MENU - NB_OPT_KEY);
// 		draw_keys_options_menu(env, m->options_menu, m->keys);
// 	}
// 	if (m->status.ingame_menu)
// 		draw_page_menu(env, m->ingame_menu, I_INGAME, NB_BLOC_IG);

// }
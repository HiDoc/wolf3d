/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:48:04 by abaille           #+#    #+#             */
/*   Updated: 2019/04/12 14:41:30 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "doom.h"

void	draw_bloc(t_env *env, t_bloc *b, SDL_Surface *img)
{
	SDL_Surface	*surf;

	create_scaled_surface(&surf, (t_vtx){b->rect.w, b->rect.h});
	ui_scaled_copy(img, surf);
	draw_img(env, surf, b);
	lt_release(surf);
}

void	draw_bloc_isvisible(t_env *env, t_bloc *b)
{
	t_bloc	fill;

	ft_bzero(&fill, sizeof(t_bloc));
	if (!b->is_visible)
	{
		if (b->bg_empty)
			draw_bloc(env, b, b->bg_empty);
	}
	else
	{
		if (b->bg_fill)
			draw_bloc(env, b, b->bg_fill);
		fill.rect = b->cross.rect;
		draw_img(env, b->cross.sprite, &fill);
	}

}

void	draw_page_menu(t_env *env, t_bloc *b, int index, int limit)
{
	t_bloc		fill;
	int			i;

	ft_bzero(&fill, sizeof(t_bloc));
	fill.rect = (SDL_Rect){0, 0, W, H};
	draw_img(env, env->world.surfaces.img_menu[index].sprite, &fill);
	i = -1;
	while (++i < limit)
		draw_bloc_isvisible(env, &b[i]);
}

void	draw_keys_options_menu(t_env *e, t_bloc *b, Uint8 *k)
{
	int	i;
	// const char	*s;

	i = -1;
	(void)e;
	(void)b;
	(void)k;
	while (++i < NB_OPT_KEY)
	{
		// char	*s;

		// s = SDL_GetKeyName(k[i]);
		// printf("%s \n", s);
		// if (ft_isalnum(k[i]))
		// {
		// 	printf("is_alnum\n");
		// 	s = ft_strnew(2);
		// 	s[0] = (char)k[i];
		// }
			// ui_put_data(e, (t_font){WHITE, s, e->hud.text.text,
			// (t_vtx){b->use.rect.x, b->use.rect.x}, b->use.rect.w,  -1, -1});
			// lt_release(s);
	}
}

void	menu_status(t_env *env)
{
	t_menu	*m;

	m = &env->menu;
	// if (m->status.on)
	// {
		draw_page_menu(env, m->ingame_menu, I_IINGAME, NB_BLOC_IG);
		draw_page_menu(env, m->load_menu, I_ILOAD_OPT, 2);
		draw_page_menu(env, &m->mother_menu, I_IHOME, 1);
		draw_page_menu(env, m->main_menu, I_IMAINMENU, NB_BLOC_NG);
		draw_page_menu(env, m->options_menu, I_ILOAD_OPT, NB_OPT_MENU);
		draw_keys_options_menu(env, m->options_menu, m->keys);
	// 	draw_launch_menu(env);
	// 	// if (m->status.new_game)
	// 		draw_main_menu(env);
	// // }
	// // if (m->status.pause_game)
	// 	draw_ingame_menu(env);

}
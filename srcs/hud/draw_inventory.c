/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:54 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 16:49:05 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		fill_icon(t_env *env, int iter)
{
	t_bloc	*b;

	b = &env->hud.inventory.icons[iter];
	draw_img(env, b->sprite, b);
	ui_icon_data(env, (t_vtx){b->rect.x + W / 15, b->rect.y + H / 60}, iter);
}

static void		fill_wpn(t_env *env, int iter)
{
	t_bloc	*bloc;

	bloc = &env->hud.inventory.wpn[iter];
	if (env->player.inventory.weapons[iter].is_full)
	{
		draw_img(env, bloc->bg_fill, bloc);
		put_data(env, (t_font){WHITE, S_CROSS, env->hud.font.text,
			(t_vtx){bloc->cross.rect.x, bloc->cross.rect.y}, W / 80, -1, -1});
	}
	else
		draw_img(env, bloc->bg_empty, bloc);
}

static void		fill_gems(t_env *e, int iter)
{
	t_bloc		*bloc;
	t_bloc		fill;
	SDL_Rect	rect;

	bloc = &e->hud.inventory.gems[iter];
	rect = (SDL_Rect){bloc->rect.x + bloc->rect.w / 16,
	bloc->rect.y + bloc->rect.w / 16,
	bloc->rect.w - bloc->rect.w / 10, bloc->rect.w - bloc->rect.w / 10};
	ft_bzero(&fill, sizeof(t_bloc));
	fill.rect = rect;
	if (e->player.inventory.gems[iter].is_full)
	{
		draw_img(e, bloc->bg_fill, bloc);
		draw_img(e,
			e->world.objects[e->player.inventory.gems[iter].ref].sprite, &fill);
		put_data(e, (t_font){WHITE, "", e->hud.font.text,
			(t_vtx){bloc->rect.x, bloc->rect.y}, W / 60,
			e->player.inventory.gems[iter].nb_stack, -1});
	}
	else
		draw_img(e, bloc->bg_empty, bloc);
}

static void		fill_bloc(t_env *env, int i)
{
	t_bloc		*b;
	t_bloc		fill;

	b = &env->hud.inventory.objects[i];
	if (env->player.inventory.objects[i].is_full)
	{
		draw_img(env, b->bg_fill, b);
		ft_bzero(&fill, sizeof(t_bloc));
		fill.rect = (SDL_Rect){b->rect.x + b->rect.w / 16,
			b->rect.y + b->rect.w / 16,
			b->rect.w - b->rect.w / 10,
			b->rect.w - b->rect.w / 10};
		draw_img(env, b->sprite, &fill);
		fill.rect = b->cross.rect;
		put_data(env, (t_font){WHITE, S_CROSS, env->hud.font.text,
			(t_vtx){b->cross.rect.x, b->cross.rect.y}, W / 60, -1, -1});
		put_data(env, (t_font){WHITE, S_USE, env->hud.font.text,
			(t_vtx){b->use.rect.x, b->use.rect.y}, W / 60, -1, -1});
		put_data(env, (t_font){GOLD, "", env->hud.font.number,
		(t_vtx){b->rect.x + W / 80, b->rect.y + 5}, W / 60, -1,
		env->player.inventory.objects[i].nb_stack});
	}
	else
		draw_img(env, b->bg_empty, b);
}

void			print_inventory(t_env *env)
{
	t_bloc	*bloc;
	int		iter;

	bloc = &env->hud.inventory.bg;
	draw_img(env, bloc->sprite, bloc);
	iter = 0;
	while (iter < 6)
	{
		fill_bloc(env, iter);
		if (iter < WORLD_NB_GEMS)
			fill_gems(env, iter);
		if (iter < GAME_NB_WPN)
			fill_wpn(env, iter);
		(iter < 2) ? fill_icon(env, iter) : 0;
		iter++;
	}
	ui_txt_inv(env, -1, 3);
}

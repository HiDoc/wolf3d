/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:54 by abaille           #+#    #+#             */
/*   Updated: 2019/05/03 02:37:09 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		fill_icon(t_env *env, int iter)
{
	t_bloc	*bloc;

	bloc = &env->hud.inventory.icons[iter];
	draw_img(env, bloc->sprite, bloc);
	ui_icon_data(env, (t_vtx){bloc->rect.x + W / 15, bloc->rect.y + H / 60}, iter);
}

static void		fill_wpn(t_env *env, int iter)
{
	t_bloc	*bloc;

	bloc = &env->hud.inventory.wpn[iter];
	if (env->player.inventory.weapons[iter].current)
	{
		draw_img(env, bloc->bg_fill, bloc);
		ui_put_data(env, (t_font){WHITE, S_CROSS, env->hud.text.text,
			(t_vtx){bloc->cross.rect.x, bloc->cross.rect.y}, W / 80, -1, -1});
	}
	else
		draw_img(env, bloc->bg_empty, bloc);
}

static void		fill_gems(t_env *env, int iter)
{
	t_bloc		*bloc;
	t_wrap_sect	*g_ref;
	t_bloc		fill;
	SDL_Rect	rect;

	bloc = &env->hud.inventory.gems[iter];
	rect = (SDL_Rect){bloc->rect.x + bloc->rect.w / 16,
	bloc->rect.y + bloc->rect.w / 16,
	bloc->rect.w - bloc->rect.w / 10, bloc->rect.w - bloc->rect.w / 10};
	ft_bzero(&fill, sizeof(t_bloc));
	fill.rect = rect;
	if (env->player.inventory.gems[iter].current)
	{
		g_ref = env->player.inventory.gems[iter].current;
		draw_img(env, bloc->bg_fill, bloc);
		draw_img(env, env->world.objects[g_ref->ref].sprite, &fill);
	}
	else
		draw_img(env, bloc->bg_empty, bloc);
}

static void		fill_bloc(t_env *env, int i)
{
	t_bloc		*b;
	t_bloc		fill;
	SDL_Rect	rect;

	b = &env->hud.inventory.objects[i];
	if (env->player.inventory.objects[i].current)
	{
		draw_img(env, b->bg_fill, b);
		rect = (SDL_Rect){b->rect.x + b->rect.w / 16,
		b->rect.y + b->rect.w / 16,
		b->rect.w - b->rect.w / 10,
		b->rect.w - b->rect.w / 10};
		ft_bzero(&fill, sizeof(t_bloc));
		fill.rect = rect;
		draw_img(env, b->sprite, &fill);
		fill.rect = b->cross.rect;
		ui_put_data(env, (t_font){WHITE, S_CROSS, env->hud.text.text,
			(t_vtx){b->cross.rect.x, b->cross.rect.y}, W / 60, -1, -1});
		ui_put_data(env, (t_font){WHITE, S_USE, env->hud.text.text,
			(t_vtx){b->use.rect.x, b->use.rect.y}, W / 60, -1, -1});
		ui_put_data(env, (t_font){GOLD, "", env->hud.text.number,
		(t_vtx){b->rect.x + W / 80,	b->rect.y + 5}, W / 60, -1,
		env->player.inventory.objects[i].nb_stack});
	}
	else
		draw_img(env, b->bg_empty, b);
}

void		print_inventory(t_env *env)
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

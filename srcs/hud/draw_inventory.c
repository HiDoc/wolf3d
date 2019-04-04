/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:54 by abaille           #+#    #+#             */
/*   Updated: 2019/04/03 23:46:28 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		fill_bloc(t_env *env, int i)
{
	t_bloc		*bloc;
	t_bloc		fill;
	SDL_Rect	rect;

	bloc = &env->hud.inventory.objects[i];
	if (env->player.inventory.objects[i].current)
	{
		rect = (SDL_Rect){bloc->rect.x + bloc->rect.w / 16, bloc->rect.y + bloc->rect.w / 16,
			bloc->rect.w - bloc->rect.w / 10, bloc->rect.w - bloc->rect.w / 10};
		draw_img(env, bloc->bg_fill, bloc);
		fill = (t_bloc){bloc->cross, bloc->use, NULL, NULL, NULL, rect, 0, 0, (t_edge){{0, 0}, {0, 0}}};
		draw_img(env, bloc->sprite, &fill);
		fill.rect = bloc->cross.rect;
		draw_img(env, bloc->cross.sprite, &fill);
		fill.rect = bloc->use.rect;
		draw_img(env, bloc->use.sprite, &fill);
		ui_put_data(env, (t_font){GOLD, "", env->hud.text.number,
		(t_vtx){bloc->rect.x + W / 80,	bloc->rect.y + 5}, 20, -1,
		env->player.inventory.objects[i].nb_stack});
	}
	else
		draw_img(env, bloc->bg_empty, bloc);
	return (1);
}

int		fill_wpn(t_env *env, int iter)
{
	t_bloc		*bloc;
	t_bloc		fill;

	bloc = &env->hud.inventory.wpn[iter];
	if (env->player.inventory.weapons[iter].current)
	{
		fill = (t_bloc){bloc->cross, bloc->use, NULL, NULL, NULL, bloc->cross.rect, 0, 0, (t_edge){{0, 0}, {0, 0}}};
		draw_img(env, bloc->bg_fill, bloc);
		draw_img(env, bloc->cross.sprite, &fill);
	}
	else
		draw_img(env, bloc->bg_empty, bloc);
	return (1);
}

int		fill_icon(t_env *env, int iter)
{
	t_bloc	*bloc;

	bloc = &env->hud.inventory.icons[iter];
	draw_img(env, bloc->sprite, bloc);
	ui_icon_data(env, (t_vtx){bloc->rect.x + W / 15, bloc->rect.y + H / 60}, iter);
	return (1);
}

int		fill_gems(t_env *env, int iter)
{
	t_bloc		*bloc;
	t_wrap_sect	*g_ref;
	t_bloc		fill;
	SDL_Rect	rect;

	bloc = &env->hud.inventory.gems[iter];
	rect = (SDL_Rect){bloc->rect.x + bloc->rect.w / 16,	bloc->rect.y + bloc->rect.w / 16,
	bloc->rect.w - bloc->rect.w / 10, bloc->rect.w - bloc->rect.w / 10};
	fill = (t_bloc){bloc->cross, bloc->use, NULL, NULL, NULL, rect, 0, 0, (t_edge){{0, 0}, {0, 0}}};
	if (env->player.inventory.gems[iter].current)
	{
		g_ref = env->player.inventory.gems[iter].current;
		draw_img(env, bloc->bg_fill, bloc);
		draw_img(env, env->world.objects[g_ref->ref].sprite, &fill);
	}
	else
		draw_img(env, bloc->bg_empty, bloc);
	return (1);
}

int		fill_inventory(t_env *env)
{
	int		iter;

	iter = 0;
	while (iter < 6)
	{
		if (!fill_bloc(env, iter))
			return (0);
		if (iter < WORLD_NB_GEMS)
			fill_gems(env, iter);
		if (iter < WORLD_NB_WEAPONS)
			fill_wpn(env, iter);
		if (iter < 2)
		{
			if (!fill_icon(env, iter))
				return (0);
		}
		iter++;
	}
	return (1);
}

int		print_inventory(t_env *env)
{
	t_bloc	*bloc;

	bloc = &env->hud.inventory.bg;
	draw_img(env, bloc->sprite, bloc);
	fill_inventory(env);
	ui_txt_inv(env);
	return (1);
}

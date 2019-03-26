/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:54 by abaille           #+#    #+#             */
/*   Updated: 2019/03/26 12:42:11 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		fill_bloc(t_env *env, int i)
{
	t_bloc		*bloc;
	SDL_Rect	rect;

	bloc = &env->hud.inventory.objects[i];
	if (env->player.inventory.objects[i].current)
	{
		rect = (SDL_Rect){bloc->rect.x + bloc->rect.w / 16,
		bloc->rect.y + bloc->rect.w / 16,
		bloc->rect.w - bloc->rect.w / 10, bloc->rect.w - bloc->rect.w / 10};
		draw_img(env, bloc->bg_fill, bloc);
		draw_img(env, bloc->sprite,
		&((t_bloc){bloc->cross, bloc->use, NULL, NULL, NULL,
		rect, 0, 0, (t_vtx){0, 0}}));
		draw_img(env, bloc->cross.sprite,
		&((t_bloc){bloc->cross, bloc->use, NULL, NULL, NULL,
		bloc->cross.rect, 0, 0, (t_vtx){0, 0}}));
		draw_img(env, bloc->use.sprite,
		&((t_bloc){bloc->cross, bloc->use, NULL, NULL, NULL,
		bloc->use.rect, 0, 0, (t_vtx){0, 0}}));
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
	SDL_Surface	*mwpn;
	t_bloc		*bloc;

	bloc = &env->hud.inventory.wpn[iter];
	if (env->player.inventory.weapons[iter].current)
		mwpn = bloc->bg_fill;
	else
		mwpn = bloc->bg_empty;
	draw_img(env, mwpn, bloc);
	return (1);
}

int		fill_icon(t_env *env, int iter)
{
	t_bloc	*bloc;

	bloc = &env->hud.inventory.icons[iter];
	draw_img(env, bloc->sprite, bloc);
	// ui_icon_data(env, (t_vtx){n->x + W / 20, bloc->v1.y + H / 70}, iter);
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
		if (iter < WORLD_NB_WEAPONS)
		{
			if (!fill_wpn(env, iter))
				return (0);
		}
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

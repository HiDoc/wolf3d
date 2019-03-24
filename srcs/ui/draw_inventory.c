/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:54 by abaille           #+#    #+#             */
/*   Updated: 2019/03/24 10:13:50 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// int		use_drop_icon(t_env *env, t_edge bloc, int i)
// {
// 	const float	size_cross = (bloc.v2.x - bloc.v1.x) / 5;
// 	t_wrap_inv	objects;
// 	t_edge		*cross;
// 	t_edge		*use;

// 	objects = env->player.inventory.objects[i];
// 	cross = &objects.udbox[0];
// 	use = &objects.udbox[1];

// 	cross->v1 = (t_vtx){bloc.v2.x - size_cross + W / 28, bloc.v1.y};
// 	cross->v2 = (t_vtx){bloc.v2.x, bloc.v1.y + size_cross};
// 	draw_flat_rect(env->sdl.surface, *cross, 0x0);
// 	draw_scaled_string(
// 		(t_font){WHITE, "X", env->player.hud.text.text, cross->v1, 25, -1, -1},
// 		env->player.hud.text.t_inv[2], env->sdl.surface, (t_vtx){0, 0});

// 	// udbox[1]->v1 = (t_vtx){bloc.v2.x - blocx / 2, bloc.v2.y - blocx / 2};
// 	// udbox[1]->v2 = bloc.v2;
// 	// draw_flat_rect(env->sdl.surface,
// 	// env->player.inventory.objects[i].udbox[1], 0x0);
// 	// draw_scaled_string((t_font){WHITE, "Use", env->player.hud.text.text,
// 	// (t_vtx){udbox[1]->v1.x + 2,	udbox[1]->v1.y}, 20, -1, -1}, env->player.hud.text.t_inv[3], env->sdl.surface, (t_vtx){0, 0});
// 	// ui_put_data(env, (t_font){c[0], "USE", env->player.hud.text.text,
// 	// (t_vtx){udbox[1]->v1.x + 2,	udbox[1]->v1.y}, 20, -1, -1});
// 	// ui_put_data(env, (t_font){c[1], "", env->player.hud.text.number,
// 	// (t_vtx){bloc.v1.x + 8,	bloc.v1.y + 5}, 20, -1,
// 	// env->player.inventory.objects[i].nb_stack});
// 	return (0);
// }

int		fill_bloc(t_env *env, int i)
{
	t_bloc	*bloc;

	bloc = &env->player.hud.inventory.objects[i];
	if (env->player.inventory.objects[i].current)
	{
		draw_img(env, bloc->bg_fill, (t_ixy){bloc->rect.x, bloc->rect.y}, (t_edge){{0, 0}, {bloc->rect.w, bloc->rect.h}});
		draw_img(env, bloc->sprite, (t_ixy){bloc->rect.x + bloc->rect.w / 16, bloc->rect.y + bloc->rect.w / 16},
		(t_edge){{0, 0}, {bloc->rect.w - bloc->rect.w / 10, bloc->rect.w - bloc->rect.w / 10}});
		draw_img(env, bloc->cross.sprite, (t_ixy){bloc->cross.rect.x, bloc->cross.rect.y},
		(t_edge){{0, 0}, {bloc->cross.rect.w, bloc->cross.rect.h}});
	}
	else
	{
		draw_img(env, bloc->bg_empty, (t_ixy){bloc->rect.x, bloc->rect.y}, (t_edge){{0, 0}, {bloc->rect.w, bloc->rect.h}});
	}
	return (1);
}

int		fill_wpn(t_env *env, int iter)
{
	SDL_Surface	*mwpn;
	t_bloc		*bloc;

	bloc = &env->player.hud.inventory.wpn[iter];
	if (env->player.inventory.weapons[iter].current)
		mwpn = bloc->bg_fill;
	else
		mwpn = bloc->bg_empty;
	draw_img(env, mwpn, (t_ixy){bloc->rect.x, bloc->rect.y}, (t_edge){{0, 0}, {bloc->rect.w, bloc->rect.h}});
	return (1);
}

int		fill_icon(t_env *env, int iter)
{
	t_bloc	*bloc;

	bloc = &env->player.hud.inventory.icons[iter];
	draw_img(env, bloc->sprite, (t_ixy){bloc->rect.x, bloc->rect.y}, (t_edge){{0, 0}, {bloc->rect.w, bloc->rect.h}});
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
	draw_img(env, env->world.surfaces.hud[0], (t_ixy){0, 0}, (t_edge){{0, 0}, {W, H}});
	fill_inventory(env);
	ui_txt_inv(env);

	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:54 by abaille           #+#    #+#             */
/*   Updated: 2019/03/22 17:15:21 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		use_drop_icon(t_env *env, t_edge bloc, int i)
{
	const float	size_cross = (bloc.v2.x - bloc.v1.x) / 5;
	t_wrap_inv	objects;
	t_edge		*cross;
	t_edge		*use;

	objects = env->player.inventory.objects[i];
	cross = &objects.udbox[0];
	use = &objects.udbox[1];

	cross->v1 = (t_vtx){bloc.v2.x - size_cross + W / 28, bloc.v1.y};
	cross->v2 = (t_vtx){bloc.v2.x, bloc.v1.y + size_cross};
	draw_flat_rect(env->sdl.surface, *cross, 0x0);
	draw_scaled_string(
		(t_font){WHITE, "X", env->ui.text, cross->v1, 25, -1, -1},
		env->ui.t_inv[2], env->sdl.surface, (t_vtx){0, 0});

	// udbox[1]->v1 = (t_vtx){bloc.v2.x - blocx / 2, bloc.v2.y - blocx / 2};
	// udbox[1]->v2 = bloc.v2;
	// draw_flat_rect(env->sdl.surface,
	// env->player.inventory.objects[i].udbox[1], 0x0);
	// draw_scaled_string((t_font){WHITE, "Use", env->ui.text,
	// (t_vtx){udbox[1]->v1.x + 2,	udbox[1]->v1.y}, 20, -1, -1}, env->ui.t_inv[3], env->sdl.surface, (t_vtx){0, 0});
	// ui_put_data(env, (t_font){c[0], "USE", env->ui.text,
	// (t_vtx){udbox[1]->v1.x + 2,	udbox[1]->v1.y}, 20, -1, -1});
	// ui_put_data(env, (t_font){c[1], "", env->ui.number,
	// (t_vtx){bloc.v1.x + 8,	bloc.v1.y + 5}, 20, -1,
	// env->player.inventory.objects[i].nb_stack});
	return (0);
}

int		fill_bloc(t_env *env, t_edge *bloc, t_vtx *n, int i)
{
	float inter;
	float sbloc;
	SDL_Surface	*sprite;

	inter = (float)W / 128;
	sbloc = W / 8;
	bloc->v1 = *n;
	bloc->v2 = (t_vtx){sbloc, W / 8};
	if (env->player.inventory.objects[i].current)
	{
		sprite = env->player.inventory.ui.box[0];
		draw_img(env, sprite, (t_ixy){bloc->v1.x, bloc->v1.y}, (t_edge){{0, 0}, bloc->v2});
		sprite = env->world.objects[env->player.inventory.objects[i].current->ref].sprite;
		draw_img(env, sprite, (t_ixy){bloc->v1.x + sbloc / 16,
		bloc->v1.y + sbloc / 16},
		(t_edge){{0, 0}, {sbloc - sbloc / 10, sbloc - sbloc / 10}});
		use_drop_icon(env, *bloc, i);
	}
	else
	{
		sprite = env->player.inventory.ui.box[1];
		draw_img(env, sprite, (t_ixy){bloc->v1.x, bloc->v1.y}, (t_edge){{0, 0}, bloc->v2});
	}
	n->x = i == 2 ? W / 28 : n->x + inter + sbloc;
	n->y = i < 2 ? H / 6 : inter + H / 6 + sbloc;
	return (1);
}

int		fill_wpn(t_env *env, t_edge *bloc, t_vtx *n, int iter)
{
	float inter;
	float sbloc;
	SDL_Surface	*mwpn;

	inter = (float)W / 64;
	sbloc = W / 7;
	bloc->v1 = *n;
	bloc->v2 = (t_vtx){sbloc, H / 7};
	if (env->player.inventory.weapons[iter].current)
		mwpn = env->player.inventory.ui.mini_wpn[iter];
	else
		mwpn = env->player.inventory.ui.empt_wpn[iter];
	draw_img(env, mwpn, (t_ixy){bloc->v1.x, bloc->v1.y}, (t_edge){{0, 0}, bloc->v2});
	n->x += inter + sbloc;
	n->y = H - H / 3;
	return (1);
}

int		fill_icon(t_env *env, t_edge *bloc, t_vtx *n, int iter)
{
	float		inter;
	float		sbloc;
	SDL_Surface	*icon;

	icon = env->player.inventory.ui.icon[iter];
	inter = (float)W / 8;
	sbloc = W / 21;
	bloc->v1 = *n;
	bloc->v2 = (t_vtx){sbloc, H / 15.5};
	draw_img(env, icon, (t_ixy){bloc->v1.x, bloc->v1.y}, (t_edge){{0, 0}, bloc->v2});
	ui_icon_data(env, (t_vtx){n->x + W / 20, bloc->v1.y + H / 70}, iter);
	n->x += inter + sbloc;
	return (1);
}

int		fill_inventory(t_env *env)
{
	t_vtx	n1;
	t_vtx	n2;
	t_vtx	n3;
	int		iter;
	t_uinv	*ui;

	ui = &env->player.inventory.ui;
	iter = 0;
	n1 = (t_vtx){W / 28, H / 6};
	n2 = (t_vtx){W / 32, H - H / 3};
	n3 = (t_vtx){W / 24, H - H / 11};
	while (iter < WORLD_NB_OBJECTS)
	{
		if (!fill_bloc(env, &ui->blocs[iter], &n1, iter))
			return (0);
		if (iter < WORLD_NB_WEAPONS)
		{
			if (!fill_wpn(env, &ui->wblocs[iter], &n2, iter))
				return (0);
		}
		if (iter < 2)
		{
			if (!fill_icon(env, &ui->iblocs[iter], &n3, iter))
				return (0);
		}
		iter++;
	}
	return (1);
}

int		print_inventory(t_env *env)
{
	t_uinv	*ui;

	ui = &env->player.inventory.ui;
	draw_img(env, ui->front_pic, (t_ixy){0, 0}, (t_edge){{0, 0}, {W, H}});
	fill_inventory(env);
	ui_txt_inv(env);

	return (1);
}

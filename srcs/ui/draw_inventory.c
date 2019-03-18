/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:54 by abaille           #+#    #+#             */
/*   Updated: 2019/03/18 13:03:55 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		use_drop_icon(t_env *env, t_edge bloc, SDL_Surface *sprite, int i)
{
	float	blocx;
	t_edge	*udbox[2];
	const	SDL_Color c[2] = {{255, 255, 255, 255}, {242, 204, 42, 255}};

	udbox[0] = &env->player.inventory.objects[i].udbox[0];
	udbox[1] = &env->player.inventory.objects[i].udbox[1];
	blocx = sprite->w;
	udbox[0]->v1 = (t_vtx){bloc.v2.x - blocx / 7, bloc.v1.y};
	udbox[0]->v2 = (t_vtx){bloc.v2.x, bloc.v1.y + blocx / 7};
	ui_put_string(env, (t_font){c[0], "X", F_TEXT,
	(t_vtx){udbox[0]->v1.x + 2,	udbox[0]->v1.y}, 20, -1, -1});
	udbox[1]->v1 = (t_vtx){bloc.v2.x - blocx / 3, bloc.v2.y - blocx / 7};
	udbox[1]->v2 = bloc.v2;
	draw_flat_rect(env->sdl.surface,
	env->player.inventory.objects[i].udbox[1], 0x0);
	// ui_put_string(env, (t_font){c[0], "USE", F_TEXT,
	// (t_vtx){udbox[1]->v1.x + 2,	udbox[1]->v1.y}, 20, -1, -1});
	// ui_put_string(env, (t_font){c[1], "", F_NUMB,
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
	bloc->v1 = *n;
	sbloc = env->player.inventory.ui.box[1]->w;
	bloc->v2 = (t_vtx){sbloc, env->player.inventory.ui.box[1]->h};
	if (env->player.inventory.objects[i].current)
	{
		sprite = env->player.inventory.ui.box[0];
		draw_img(env, sprite, (t_ixy){bloc->v1.x, bloc->v1.y}, (t_edge){{0, 0}, bloc->v2});
		sprite = env->world.objects[env->player.inventory.objects[i].current->ref].sprite;
		draw_img(env, sprite, (t_ixy){bloc->v1.x + env->player.inventory.ui.box[0]->w / 128,
		bloc->v1.y + env->player.inventory.ui.box[0]->h / 128},
		(t_edge){{0, 0}, {sprite->w, sprite->h}});
		use_drop_icon(env, *bloc, sprite, i);
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
	sbloc = env->player.inventory.ui.mini_wpn[iter]->w;
	bloc->v1 = *n;
	bloc->v2 = (t_vtx){sbloc, env->player.inventory.ui.mini_wpn[iter]->h};
	if (env->player.inventory.weapons[iter].current)
	{
		mwpn = env->player.inventory.ui.mini_wpn[iter];
		draw_img(env, mwpn, (t_ixy){bloc->v1.x, bloc->v1.y}, (t_edge){{0, 0}, {mwpn->w, mwpn->h}});
	}
	// else
	// 	mwpn = env->player.inventory.ui.empt_wpn[iter];
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
	inter = (float)W / 32;
	sbloc = (float)W / 6 - (float)W / 64;
	bloc->v1 = *n;
	n->x += sbloc;
	n->y = H - H / 32;
	bloc->v2 = *n;
	bloc->v2.x = iter == 0 ? bloc->v1.x + bloc->v2.x / 4.5 : bloc->v2.x - bloc->v2.x / 4.2;
	iter == 2 ? bloc->v2.x = n->x - n->x / 5.3 : 0;
	draw_img(env, icon, (t_ixy){bloc->v1.x, bloc->v1.y}, (t_edge){{0, 0}, {icon->w, icon->h}});
	ui_icon_data(env, (t_vtx){bloc->v2.x, bloc->v1.y}, iter);
	n->x += inter;
	n->y = 	H - H / 11;
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
	while (iter < 6)
	{
		if (!fill_bloc(env, &ui->blocs[iter], &n1, iter))
			return (0);
		if (iter < 3)
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
	draw_img(env, ui->front_pic, (t_ixy){0, 0}, (t_edge){{0, 0}, {ui->front_pic->w, ui->front_pic->h}});
	fill_inventory(env);
	ui_txt_inv(env);

	return (1);
}

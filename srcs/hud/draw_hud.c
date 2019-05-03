/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:56:11 by abaille           #+#    #+#             */
/*   Updated: 2019/05/03 01:35:05 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	print_wpn_hud(t_env *env, t_wrap_wpn *wpn)
{
	t_bloc	*bloc;

	bloc = &env->hud.hud_wpn[wpn->current->ref];
	draw_img(env, bloc->sprite, bloc);
	ui_put_data(env, (t_font){GOLD, "", env->hud.text.number,
	(t_vtx){W - W / 7, H / 1.3}, W / 40,
	*env->player.inventory.current->ammo_current, -1});
	ui_put_data(env, (t_font){GOLD, "/", env->hud.text.number,
	(t_vtx){W - W / 8.5, H / 1.22}, W / 40,
	-1, *env->player.inventory.current->ammo_magazine});
}

void	check_object_stack(t_env *env, t_wrap_inv *pack, t_ixy ref, int limit)
{
	int			iter;
	t_bloc		*bloc;
	const char	*numb[5] = {"1", "2", "3", "4", "5"};

	bloc = &env->hud.objects[ref.y];
	if ((iter = check_object_type(pack, ref.x, limit)) > -1)
	{
		draw_img(env, bloc->bg_fill, bloc);
		draw_img(env, env->world.objects[ref.x].sprite, bloc);
		ui_put_data(env, (t_font){GOLD, "", env->hud.text.text,
			(t_vtx){bloc->use.rect.x, bloc->use.rect.y}, W / 90, -1,
			pack[iter].nb_stack});
	}
	else
		draw_img(env, bloc->bg_empty, bloc);
	ui_put_data(env, (t_font){WHITE, numb[(int)ref.y], env->hud.text.text,
		(t_vtx){bloc->cross.rect.x, bloc->cross.rect.y}, W / 90, -1, -1});
}

void	print_pad(t_env *env)
{
	int	i;

	check_object_stack(env, env->player.inventory.objects, (t_ixy){5, 0}, 6);
	i = 6;
	while (i < 10)
	{
		check_object_stack(env, env->player.inventory.gems, (t_ixy){i, i - 5}, 4);
		i++;
	}
}

float	size_bar(int tmax, int datamax, int data)
{
	return ((tmax - tmax / 2.8) / datamax * data + tmax / 2.8);
}

void	draw_hp_bars(t_env *env, t_bloc *bloc, int max, int data)
{
	if (data < max)
		bloc->limit.v2.x = bloc->rect.w - size_bar(bloc->rect.w, max, data);
	draw_img(env, bloc->sprite, bloc);
	bloc->limit.v2.x = 0;
}

void	print_cross(t_env *env)
{
	Uint32		*dst;
	int			x;
	int			y;
	const int	w = env->sdl.surface->w;
	const int	h = env->sdl.surface->h;

	dst = (Uint32*)env->sdl.surface->pixels;
	x = 0;
	while (x < 20)
	{
		y = 0;
		while (y < 20)
		{
			if (y + h / 2 == h / 2)
				dst[w * (y + h / 2) + (x + w / 2 - 10)] = 0xBB4EFF;
			if (x + w / 2 == w / 2)
				dst[w * (y + h / 2 - 10) + (x + w / 2)] = 0xBB4EFF;
			y++;
		}
		x++;
	}
}

int print_hud(t_env *env)
{
	t_character *player;
	t_bloc		*bloc;
	int			h;
	int			index;

	player = &env->player;
	h = player->max_health;
	while (h > player->health)
		h -= 50;
	if (player->inventory.current
	&& player->inventory.current->current->ref != 4)
		print_wpn_hud(env, player->inventory.current);
	index = h > 50 ? (int)(h / 50) - 1 : 0;
	bloc = &env->hud.faces[index];
	draw_img(env, bloc->sprite, bloc);
	draw_hp_bars(env, &env->hud.bar[0], player->max_health, player->health);
	draw_hp_bars(env, &env->hud.bar[1], player->max_shield, player->shield);
	print_pad(env);
	print_cross(env);
	return (1);
}
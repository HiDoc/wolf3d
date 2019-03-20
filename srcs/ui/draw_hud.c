/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:56:11 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 16:22:00 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	print_wpn_hud(t_env *env, t_wrap_wpn *wpn)
{
	SDL_Surface	*sprite;

	sprite = env->player.hud.hud_wpn[wpn->current->ref];
	draw_img(env, sprite, (t_ixy){W - W / 6, H / 1.2},
	(t_edge){{0, 0},{sprite->w, sprite->h}});
	ui_put_string(env, (t_font){GOLD, "", F_NUMB,
	(t_vtx){W - W / 7, H / 1.3}, 30,
	env->player.inventory.current->ammo_current, -1});
	ui_put_string(env, (t_font){GOLD, "/", F_NUMB,
	(t_vtx){W - W / 8.5, H / 1.22}, 30,
	-1, env->player.inventory.current->ammo_magazine});
	return (1);
}

int	check_wpn_stack(t_env *env, int ref)
{
	int	rref;
	t_weapon	*wpn;

	if (env->player.inventory.current)
	{
		rref = env->player.inventory.current->current->ref;
		wpn = &env->world.armory[rref];
		if (ref == env->world.armory[rref].type)
			return (1);
	}
	return (0);
}

int	check_object_stack(t_env *env, int ref, t_ixy start)
{
	int	iter;
	SDL_Surface	*sprite;

	if ((iter = check_object_type(env, ref)) > -1)
	{
		if (((ref > 1 && ref < 5) && check_wpn_stack(env, ref)) || ref < 2 || ref == 5)
			sprite = env->player.hud.objects[ref];
		else
			sprite = env->player.hud.empty_b;
		draw_img(env, sprite, start,
		(t_edge){{0, 0}, {sprite->w, sprite->h}});
	}
	else
		draw_img(env, env->player.hud.empty_b, start,
		(t_edge){{0, 0}, {env->player.hud.empty_b->w, env->player.hud.empty_b->h}});
	return (0);
}

int	print_pad(t_env *env)
{
	int		size_b;
	int		i;
	t_ixy	start;

	start = (t_ixy){W - W / 1.27, H - H  / 8};
	size_b = env->player.hud.empty_b->w + 2;
	check_object_stack(env, 0, start);
	start.x += size_b;
	check_object_stack(env, 1, start);
	start.x += size_b;
	i = 2;
	while (i < 5)
		check_object_stack(env, i++, start);
	start.x += size_b;
	check_object_stack(env, 5, start);
	return (0);
}

float	size_bar(int tmax, int datamax, int data)
{
	return ((tmax - tmax / 2.8) / datamax * data + tmax / 2.8);
}

int print_hud(t_env *env)
{
	int	h;
	int	limit_bar;
	int	index;

	h = 200;
	while (h > env->player.health)
		h -= 50;
	if (env->player.inventory.current)
	{
		if (!print_wpn_hud(env, env->player.inventory.current))
			return (0);
	}
	index = h > 50 ? (int)(h / 50) - 1 : 0;
	draw_img(env, env->player.hud.faces[index], (t_ixy){W / 128, H - H / 2.8},
	(t_edge){{0, 0}, {env->player.hud.faces[index]->w,
	env->player.hud.faces[index]->h}});
	limit_bar = size_bar(env->player.hud.bar[0]->w,
	env->player.max_health, env->player.health);
	draw_img(env, env->player.hud.bar[0], (t_ixy){W / 128, H - H / 2.8},
	(t_edge){{0, 0}, {limit_bar, env->player.hud.bar[0]->h}});
	limit_bar = size_bar(env->player.hud.bar[1]->w,
	env->player.max_shield, env->player.shield);
	draw_img(env, env->player.hud.bar[1], (t_ixy){W / 128, H - H / 2.8},
	(t_edge){{0, 0}, {limit_bar, env->player.hud.bar[1]->h}});
	print_pad(env);
	return (1);
}
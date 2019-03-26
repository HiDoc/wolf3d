/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 21:56:11 by abaille           #+#    #+#             */
/*   Updated: 2019/03/26 16:49:13 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	print_wpn_hud(t_env *env, t_wrap_wpn *wpn)
{
	t_bloc	*bloc;

	bloc = &env->hud.hud_wpn[wpn->current->ref];
	draw_img(env, bloc->sprite, bloc);
	ui_put_data(env, (t_font){GOLD, "", env->hud.text.number,
	(t_vtx){W - W / 7, H / 1.3}, W / 40,
	env->player.inventory.current->ammo_current, -1});
	ui_put_data(env, (t_font){GOLD, "/", env->hud.text.number,
	(t_vtx){W - W / 8.5, H / 1.22}, W / 40,
	-1, env->player.inventory.current->ammo_magazine});
	return (1);
}

int	check_wpn_stack(t_env *env, int ref)
{
	int			rref;
	t_weapon	*wpn;

	if (env->player.inventory.current)
	{
		rref = env->player.inventory.current->current->ref;
		wpn = &env->world.armory[rref];
		if (ref == wpn->type)
			return (1);
	}
	return (0);
}

int	check_object_stack(t_env *env, int ref, int index)
{
	int			iter;
	SDL_Surface	*sprite;
	t_bloc		*bloc;

	bloc = &env->hud.objects[index];
	if ((iter = check_object_type(env, ref)) > -1)
	{
		if (((ref > 1 && ref < 5) && check_wpn_stack(env, ref)) || ref < 2 || ref == 5)
			sprite = env->world.objects[ref].sprite;
		else
			sprite = bloc->bg_empty;
		draw_img(env, bloc->bg_fill, bloc);
		draw_img(env, sprite, bloc);
	}
	else
		draw_img(env, bloc->bg_empty, bloc);
	return (0);
}

int	print_pad(t_env *env)
{
	int	i;

	check_object_stack(env, 0, 0);
	check_object_stack(env, 1, 1);
	check_object_stack(env, 5, 2);
	i = 2;
	while (i < 5)
		check_object_stack(env, i++, 3);
	return (0);
}

float	size_bar(int tmax, int datamax, int data)
{
	return ((tmax - tmax / 2.8) / datamax * data + tmax / 2.8);
}

int	draw_hp_bars(t_env *env, t_bloc *bloc, int max, int data)
{
	int	rectw_save;

	rectw_save = bloc->rect.w;
	if (data < max)
		bloc->rect.w = size_bar(bloc->rect.w, max, data);
	draw_img(env, bloc->sprite, bloc);
	bloc->rect.w = rectw_save;
	return (1);
}

int print_hud(t_env *env)
{
	int		h;
	int		index;
	t_bloc	*bloc;

	h = env->player.max_health;
	while (h > env->player.health)
		h -= 50;
	if (env->player.inventory.current)
	{
		if (!print_wpn_hud(env, env->player.inventory.current))
			return (0);
	}
	index = h > 50 ? (int)(h / 50) - 1 : 0;
	bloc = &env->hud.faces[index];
	draw_img(env, bloc->sprite, bloc);
	draw_hp_bars(env, &env->hud.bar[0], env->player.max_health, env->player.health);
	draw_hp_bars(env, &env->hud.bar[1], env->player.max_shield, env->player.shield);
	print_pad(env);
	return (1);
}
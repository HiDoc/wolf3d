/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_weapons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:07 by abaille           #+#    #+#             */
/*   Updated: 2019/03/27 19:21:25 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	reload_ammo(t_env *env)
{
	int	cur_max;
	int	*cur;
	int	*mag;
	int	tmp;

	cur_max = env->world.armory[env->player.inventory.current->current->ref].ammo_curr_max;
	cur = &env->player.inventory.current->ammo_current;
	mag = &env->player.inventory.current->ammo_magazine;
	tmp = cur_max - *cur;
	*cur += *mag >= tmp ? tmp : *mag;
	*mag -= *mag >= tmp ? tmp : *mag;
	return (0);
}

int	load_weapon(t_env *env)
{
	t_wrap_wpn	*wpn;
	int			curr_max;

	wpn = env->player.inventory.current;
	if (wpn)
	{
		curr_max = env->world.armory[wpn->current->ref].ammo_curr_max;
		if (wpn->ammo_magazine && wpn->ammo_current < curr_max)
			env->player.actions.is_loading = 1;
	}
	return (0);
}

int	put_gun_load(t_env *env, int frame)
{
	t_wrap_wpn	*weapon;
	t_weapon	*wpn_ref;

	weapon = env->player.inventory.current;
	wpn_ref = &env->world.armory[weapon->current->ref];
	frame /= 2.5;
	if (frame < wpn_ref->time_reload - 1)
		put_gun(env, wpn_ref->sprite_reload[frame].sprite,
		&wpn_ref->sprite_reload[frame]);
	else
		env->player.actions.is_loading = 0;
	if (frame == (int)(wpn_ref->time_reload / 2))
		reload_ammo(env);
	return (1);
}

int	put_gun_shoot(t_env *env, int frame)
{
	t_wrap_wpn	*weapon;
	t_weapon	*wpn_ref;

	weapon = env->player.inventory.current;
	wpn_ref = &env->world.armory[weapon->current->ref];
	frame /= 2.5;
	if (frame < wpn_ref->time_shoot - 1)
		put_gun(env, wpn_ref->sprite_shoot[frame].sprite,
		&wpn_ref->sprite_shoot[frame]);
	else
		env->player.actions.is_shooting = 0;
	return (1);
}

int	select_limit(t_env *env, t_bloc *bloc)
{
	const int	ref = env->player.inventory.current->current->ref;
	if ((!env->player.actions.is_loading && !env->player.actions.is_shooting)
	|| (ref == 2 && env->player.actions.is_shooting))
		bloc->limit = (t_vtx){W / 2, H / 2};
	else
	{
		if (ref == 0)
			bloc->limit = (t_vtx){W / 2, H / 3};
		else if (ref == 1)
			bloc->limit = (t_vtx){W / 3, 0};
		else if (ref == 2 && env->player.actions.is_loading)
			bloc->limit = (t_vtx){0, H / 3};
	}
	return (1);
}

int	put_gun(t_env *env, SDL_Surface *sprite, t_bloc *bloc)
{
	select_limit(env, bloc);
	draw_img(env, sprite, bloc);
	return (1);
}
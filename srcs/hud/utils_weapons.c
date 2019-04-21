/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_weapons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:07 by abaille           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/04/13 16:58:00 by fmadura          ###   ########.fr       */
=======
/*   Updated: 2019/04/19 16:50:47 by abaille          ###   ########.fr       */
>>>>>>> d1a6321fbd2e25ab7a6c2acaf292726a07fdf815
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		reload_ammo(t_env *env)
{
	t_wrap_wpn		*wp = env->player.inventory.current;
	int				cur_max;
	int				*cur;
	int				*mag;
	int				tmp;

	cur_max = env->world.armory[wp->current->ref].ammo_curr_max;
	cur = wp->ammo_current;
	mag = wp->ammo_magazine;
	tmp = cur_max - *cur;
	*cur += *mag >= tmp ? tmp : *mag;
	*mag -= *mag >= tmp ? tmp : *mag;
	return (0);
}

int		load_weapon(t_env *env)
{
	t_wrap_wpn		*wpn;
	int				curr_max;

	wpn = env->player.inventory.current;
	if (wpn && wpn->current->ref != FIST)
	{
		curr_max = env->world.armory[wpn->current->ref].ammo_curr_max;
		if (*wpn->ammo_magazine && *wpn->ammo_current < curr_max)
		{
			env->player.actions.is_loading = 1;
			env->engine.player.sound.loadin = 1;
		}
	}
	return (0);
}

int		put_gun(t_env *env, t_bloc *bloc)
{
	const int		ref = env->player.inventory.current->current->ref;
	const t_actions *a = &env->player.actions;

	if (((!a->is_loading && !a->is_shooting) && ref != 4)
	|| (ref == 2 && a->is_shooting))
		bloc->limit.v1 = (t_vtx){W / 2, H / 2};
	else if (ref == 0)
		bloc->limit.v1 = (t_vtx){W / 2, H / 3};
	else if (ref == 1)
		bloc->limit.v1 = (t_vtx){W / 3, 0};
	else if (ref == 2 && a->is_loading)
		bloc->limit.v1 = (t_vtx){0, H / 2};
	if (ref == 3 && !a->is_loading)
		bloc->limit.v1 = (t_vtx){W / 2, 0};
	else if (ref == 4)
		bloc->limit.v1 = (t_vtx){0, H / 4};
	else
		bloc->limit.v1 = (t_vtx){0, 0};
	draw_img(env, bloc->sprite, bloc);
	return (1);
}

int		put_gun_load(t_env *env, int frame)
{
	const t_wrap_wpn	*weapon = env->player.inventory.current;
	const t_weapon		*wpn_ref = &env->world.armory[weapon->current->ref];

<<<<<<< HEAD
	weapon = env->player.inventory.current;
	wpn_ref = &env->world.armory[weapon->current->ref];
=======
	frame /= 1.2;
>>>>>>> d1a6321fbd2e25ab7a6c2acaf292726a07fdf815
	if (frame < wpn_ref->time_reload - 1)
		put_gun(env, &wpn_ref->sprite_reload[frame]);
	else
	{
		env->player.actions.is_loading = 0;
		env->player.actions.mouse_state = 0;
	}
	if (frame == (int)(wpn_ref->time_reload / 2))
	{
		reload_ammo(env);
		env->player.actions.mouse_state = 0;
	}
	return (1);
}

int		put_gun_shoot(t_env *env, int frame)
{
	t_wrap_wpn		*weapon;
	t_weapon		*wpn_ref;
	t_bloc			*sprite;

	weapon = env->player.inventory.current;
	wpn_ref = &env->world.armory[weapon->current->ref];
	sprite = &wpn_ref->sprite_shoot[frame];
	if (frame < wpn_ref->time_shoot - 1)
		put_gun(env, sprite);
	else
	{
		env->player.actions.is_shooting = 0;
		env->player.actions.mouse_state = 0;
	}
	return (1);
}

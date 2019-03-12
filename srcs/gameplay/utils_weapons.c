/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_weapons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:07 by abaille           #+#    #+#             */
/*   Updated: 2019/03/12 23:44:42 by abaille          ###   ########.fr       */
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
	SDL_FlushEvent(SDL_KEYDOWN | SDL_KEYUP);
	return (0);
}

int	put_gun_shoot(t_env *env, int frame)
{
	t_wrap_wpn	*weapon;
	t_weapon	*wpn_ref;

	weapon = env->player.inventory.current;
	wpn_ref = &env->world.armory[weapon->current->ref];
	frame /= 2.5;
	if (frame < wpn_ref->time_shoot)
		put_gun(env, wpn_ref->sprite_shoot[frame]);
	else
		env->player.actions.is_shooting = 0;
	return (1);
}

int	put_gun_load(t_env *env, int frame)
{
	t_wrap_wpn	*weapon;
	t_weapon	*wpn_ref;

	weapon = env->player.inventory.current;
	wpn_ref = &env->world.armory[weapon->current->ref];
	frame /= 2.5;
	if (frame < wpn_ref->time_reload - 1)
		put_gun(env, wpn_ref->sprite_reload[frame]);
	else
		env->player.actions.is_loading = 0;
	if (frame == (int)(wpn_ref->time_reload / 2))
		reload_ammo(env);
	return (1);
}

int	put_gun(t_env *env, SDL_Surface *sprite)
{
	int x;
	int y;

	x = W - sprite->w;
	y = H - sprite->h;
	draw_img(env, (t_edge){{x, y}, {W, H}},
	sprite, (t_ixy){50, 0});
	return (1);
}
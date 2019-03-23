/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:20:50 by abaille           #+#    #+#             */
/*   Updated: 2019/03/23 22:04:41 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int weapon_mask(long ref, int pos)
{
	return (((ref >> (pos << 2)) & 0xFF));
}

/*
** Protect this area
** from null malloc
*/

SDL_Surface **weapon_fill(char *path, int size)
{
	int			i;
	SDL_Surface	**weapons;

	i = 0;
	if (!(weapons = malloc(sizeof(SDL_Surface *) * size)))
		return (NULL);
	while (i < size)
	{
		if (!(weapons[i] = ui_img(path, i)))
			return (NULL);
		i++;
	}
	return (weapons);
}

int     weapon_sprites(t_weapon *weapon, char *name)
{
	char	*r_path;
	char	*s_path;
	char	*sprite;
	int		ret;

	ret = 0;
	r_path = NULL;
	s_path = NULL;
	sprite = NULL;
	if ((r_path = ft_strjoin(name, "/reload/"))
	&& (s_path = ft_strjoin(name, "/shoot/"))
	&& (sprite = ft_strjoin(name, "/"))
	&& (weapon->sprite = ui_img(sprite, 0))
	&& (weapon->sprite_reload = weapon_fill(r_path, weapon->time_reload))
	&& (weapon->sprite_shoot = weapon_fill(s_path, weapon->time_shoot)))
		ret = 1;
	if (r_path)
		free(r_path);
	if (s_path)
		free(s_path);
	if (sprite)
		free(sprite);
	return (ret);
}

int weapon_set(t_weapon *weapon, char *name, int dam)
{
	long	ref;

	ref = weapon->ref;
	weapon->type = (ref & 0xF);
	weapon->time_reload = weapon_mask(ref, 1);
	weapon->time_shoot = weapon_mask(ref, 3);
	weapon->time_shoot_between = weapon_mask(ref, 5);
	weapon->ammo_curr_max = weapon_mask(ref, 7);
	weapon->ammo_mag_max = weapon_mask(ref, 9);
	weapon->ammo_current = weapon_mask(ref, 7);
	weapon->ammo_magazine = weapon_mask(ref, 9);
	weapon->damage = dam;
	if (weapon_sprites(weapon, name))
		return (1);
	return (0);
}

int		init_weapon(t_env *env)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_WEAPONS)
		env->player.inventory.weapons[i++].current = NULL;
	env->player.inventory.current = NULL;
	env->world.armory[0].ref = 0xa2a0601042a2;
	env->world.armory[1].ref = 0xa2a020105123;
	env->world.armory[2].ref = 0xa8e2000042a4;
	if (weapon_set(&env->world.armory[0], "weapons/magnum", 56)
	&& weapon_set(&env->world.armory[1], "weapons/pompe", 100)
	&& weapon_set(&env->world.armory[2], "weapons/rifle", 30))
		return (1);
	return (0);
}
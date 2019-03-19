/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:20:50 by abaille           #+#    #+#             */
/*   Updated: 2019/03/19 21:04:31 by abaille          ###   ########.fr       */
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
	char		*filename;
	char		*nb;
	int			ret;

	i = 0;
	ret = 1;
	if ((weapons = malloc(sizeof(SDL_Surface *) * size)) == NULL)
		return (NULL);
	while (i < size)
	{
		nb = NULL;
		filename = NULL;
		if (!(nb = ft_itoa(i + 1)) || !(filename = ft_strrjoin((char *)path,
		ft_itoa(i + 1))) || !(weapons[i] = img_wpn(filename)))
			ret = 0;
		if (nb)
			free(nb);
		if (filename)
			free(filename);
		if (!ret)
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

	r_path = NULL;
	s_path = NULL;
	sprite = NULL;
	if ((r_path = ft_strjoin(name, "/reload/"))
	&& (s_path = ft_strjoin(name, "/shoot/"))
	&& (sprite = ft_strjoin(name, "/"))
	&& (sprite = ft_strljoin(sprite, name))
	&& (weapon->sprite = img_wpn(sprite))
	&& (weapon->sprite_reload = weapon_fill(r_path, weapon->time_reload))
	&& (weapon->sprite_shoot = weapon_fill(s_path, weapon->time_shoot)))
		ret = 1;
	else
		ret = 0;
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
	if (weapon_sprites(weapon, name)
	&& load_sounds(weapon, name, "shot/"))
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
	// env->world.armory[0].ref = 0xa2a0602012a2;
	env->world.armory[1].ref = 0xa2a020105123;
	env->world.armory[2].ref = 0xa8e2000042a4;
	// weapon_set(&env->world.armory[0], "pistol", 17);
	if (weapon_set(&env->world.armory[0], "magnum", 56)
	&& weapon_set(&env->world.armory[1], "pompe", 100)
	&& weapon_set(&env->world.armory[2], "rifle", 30))
	{
		env->player.inventory.weapons[0].current = env->engine.sectors[0].head_object;
		env->player.inventory.current = &env->player.inventory.weapons[0];
		env->player.inventory.current->ammo_current = 50;
		env->player.inventory.current->ammo_magazine = 100;
		return (1);
	}
	return (0);
}
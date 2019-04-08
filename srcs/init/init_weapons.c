/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:56:37 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/08 23:35:07 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int weapon_mask(long ref, int pos)
{
	return (((ref >> (pos << 2)) & 0xFF));
}

static t_bloc *weapon_fill(t_weapon *mother, char *path, int size)
{
	int	i;
	t_bloc		*weapons;

	if (!(weapons = malloc(sizeof(t_bloc) * size)))
		return (NULL);

	i = 0;
	// (void)mother;
	// while (i < size)
	// {
	// 	if (!current_sprite(&weapons[i], path, i))
	// 		return (0);
	// 	i++;
	// }
	init_thread(mother, weapons, path, size);
	return (weapons);
}


static int     weapon_sprites(t_weapon *weapon, char *name)
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
	&& (current_sprite(&weapon->sprite, sprite, 0))
	&& (weapon->sprite_reload = weapon_fill(weapon, r_path, weapon->time_reload))
	&& (weapon->sprite_shoot = weapon_fill(weapon, s_path, weapon->time_shoot)))
		ret = 1;
	if (r_path)
		free(r_path);
	if (s_path)
		free(s_path);
	if (sprite)
		free(sprite);
	return (ret);
}

static int weapon_set(t_weapon *weapon, char *name, int dam, t_vctr ray_scope_vel, int devset)
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
	weapon->ray = ray_scope_vel.x;
	weapon->scop = ray_scope_vel.y;
	weapon->velocity = ray_scope_vel.z;
	(void)name;
	if (devset)
	{
		if (!weapon_sprites(weapon, name))
			return (0);
	}
	return (1);
}

int		init_weapon(t_env *env)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_WEAPONS)
		env->player.inventory.weapons[i++].current = NULL;
	env->player.inventory.current = NULL;
	env->world.armory[MAGNUM].ref = 0xa2a0601042a2;
	env->world.armory[SHOTGUN].ref = 0xa2a020105123;
	env->world.armory[RIFLE].ref = 0xa8e2000042a4;
	env->world.armory[RPG].ref = 0xa08010108242;
	env->world.armory[FIST].ref = 0xa00000103002;
	weapon_set(&env->world.armory[MAGNUM], "weapons/magnum", 56, (t_vctr){R_MAGNUM, S_MAGNUM, V_MAGNUM}, 0);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[SHOTGUN], "weapons/pompe", 100, (t_vctr){R_SHOTGUN, S_SHOTGUN, V_SHOTGUN}, 0);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[RIFLE], "weapons/rifle", 30, (t_vctr){R_RIFLE, S_RIFLE, V_RIFLE}, 0);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[RPG], "weapons/rpg", 100, (t_vctr){R_RPG, S_RPG, V_RPG}, 1);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[FIST], "weapons/fist", 45, (t_vctr){R_FIST, S_FIST, V_FIST}, 1);
	printf("time weapon: %u\n", SDL_GetTicks());

	// if (weapon_set(&env->world.armory[MAGNUM], "weapons/magnum", 56, (t_vctr){R_MAGNUM, S_MAGNUM, V_MAGNUM}, 1)
	// && weapon_set(&env->world.armory[SHOTGUN], "weapons/pompe", 100, (t_vctr){R_SHOTGUN, S_SHOTGUN, V_SHOTGUN}, 1)
	// && weapon_set(&env->world.armory[RIFLE], "weapons/rifle", 30, (t_vctr){R_RIFLE, S_RIFLE, V_RIFLE}, 1)
	// && weapon_set(&env->world.armory[RPG], "weapons/rpg", 100, (t_vctr){R_RPG, S_RPG, V_RPG}, 1)
	// && weapon_set(&env->world.armory[FIST], "weapons/fist", 45, (t_vctr){R_FIST, S_FIST, V_FIST}, 1))
	// {
		env->player.inventory.f.ref = FIST;
		env->player.inventory.weapons[FIST].current = &env->player.inventory.f;
		env->player.inventory.weapons[FIST].ammo[0] = env->world.armory[FIST].ammo_current;
		env->player.inventory.weapons[FIST].ammo[1] = env->world.armory[FIST].ammo_magazine;
		env->player.inventory.weapons[FIST].ammo[2] = env->world.armory[FIST].damage;
		set_current_wpn(&env->player.inventory, FIST);
		return (1);
	// }
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:20:50 by abaille           #+#    #+#             */
/*   Updated: 2019/03/29 17:10:43 by abaille          ###   ########.fr       */
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
int		current_sprite(t_bloc *bloc, char *file, int i)
{
	SDL_Surface	*sprite;
	Uint32		*p;

	sprite = NULL;
	if (!(sprite = ui_img(file, i))
	|| !(bloc->sprite = SDL_CreateRGBSurface(0, W, H, 32,
		0xff000000, 0xff0000, 0xff00, 0xff)))
		return (0);
	bloc->rect = (SDL_Rect){0, 0, W, H};
	bloc->limit = (t_vtx){0, 0};
	SDL_LockSurface(bloc->sprite);
	p = (Uint32*)bloc->sprite->pixels;
	scale_img(p, bloc->rect, sprite);
	SDL_UnlockSurface(bloc->sprite);
	if (sprite)
		SDL_FreeSurface(sprite);
	return (1);
}

t_bloc *weapon_fill(char *path, int size)
{
	int			i;
	t_bloc		*weapons;

	i = 0;
	if (!(weapons = malloc(sizeof(t_bloc) * size)))
		return (NULL);
	while (i < size)
	{
		if (!current_sprite(&weapons[i], path, i))
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
	&& (current_sprite(&weapon->sprite, sprite, 0))
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
	(void)name;
	// if (weapon_sprites(weapon, name))
	// 	return (1);
	return (1);
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
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[0], "weapons/magnum", 56);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[1], "weapons/pompe", 100);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[2], "weapons/rifle", 30);
	printf("time weapon: %u\n", SDL_GetTicks());
	return (1);
}
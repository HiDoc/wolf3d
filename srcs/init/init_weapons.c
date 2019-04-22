/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:56:37 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/22 11:37:56 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		current_sprite(t_bloc *bloc, char *file, int i)
{
	SDL_Surface	*sprite;

	sprite = ui_img(file, i);
	bloc->sprite = make_surface(W, H);
	img_scaled_copy(sprite, bloc->sprite);
	bloc->rect = (SDL_Rect){0, 0, W, H};
	bloc->limit.v1 = (t_vtx){0, 0};
	lt_release(sprite);
}

static void	thread_current_sprite(t_bloc *child, char *path, int line, int size)
{
	int	i;

	i = line;
	while (i < size)
	{
		current_sprite(&child[i], path, i);
		i += NB_THREAD_IMG;
	}
}

static void		set_thread(t_weapon *mother, t_bloc *child, char *path, int size)
{
	int	i;

	i = 0;
	while (i < NB_THREAD_IMG)
	{
		mother->threads[i].mother = mother;
		mother->threads[i].child = child;
		mother->threads[i].path = path;
		mother->threads[i].size = size;
		mother->threads[i].nb = i;
		i++;
	}
}

static void		*launch_thread(void *arg)
{
	t_thread	*tmp;

	tmp = (t_thread *)arg;
	thread_current_sprite(tmp->child, tmp->path, tmp->nb, tmp->size);
	pthread_exit(NULL);
}

static void		init_thread(t_weapon *mother, t_bloc *child, char *path, int size)
{
	int	i;

	i = 0;
	set_thread(mother, child, path, size);
	while (i < NB_THREAD_IMG)
	{
		if (pthread_create(&mother->threads[i].th, NULL,
		launch_thread, &mother->threads[i]))
			doom_error_exit("Doom_nukem error on pthread_create");
		i++;
	}
	i = 0;
	while (i < NB_THREAD_IMG)
	{
		if (pthread_join(mother->threads[i].th, NULL))
			doom_error_exit("Doom_nukem error on pthread_join");
		i++;
	}
}

static t_bloc *weapon_fill(t_weapon *mother, char *path, int size)
{
	t_bloc	*weapons;

	weapons = ft_memalloc(sizeof(t_bloc) * size);
	init_thread(mother, weapons, path, size);
	return (weapons);
}

static void     weapon_sprites(t_weapon *weapon, char *name)
{
	char	*r_path;
	char	*s_path;
	char	*sprite;

	r_path = ft_strjoin(name, "/reload/");
	s_path = ft_strjoin(name, "/shoot/");
	sprite = ft_strjoin(name, "/");
	current_sprite(&weapon->sprite, sprite, 0);
	weapon->sprite_reload = weapon_fill(weapon, r_path, weapon->time_reload);
	weapon->sprite_shoot = weapon_fill(weapon, s_path, weapon->time_shoot);
	lt_release(r_path);
	lt_release(s_path);
	lt_release(sprite);
}

static void		weapon_set(t_weapon *weapon, char *name, int dam,
				t_vctr ray_scope_vel, int devset)
{
	long	ref;

	ref = weapon->ref;
	weapon->type = (ref & 0xF);
	weapon->time_reload = ((ref >> (1 << 2)) & 0xFF);
	weapon->time_shoot = ((ref >> (3 << 2)) & 0xFF);
	weapon->time_shoot_between = ((ref >> (5 << 2)) & 0xFF);
	weapon->ammo_curr_max = ((ref >> (7 << 2)) & 0xFF);
	weapon->ammo_mag_max = ((ref >> (9 << 2)) & 0xFF);
	weapon->ammo_current = ((ref >> (7 << 2)) & 0xFF);
	weapon->ammo_magazine = ((ref >> (9 << 2)) & 0xFF);
	weapon->damage = dam;
	weapon->ray = ray_scope_vel.x;
	weapon->scop = ray_scope_vel.y;
	weapon->velocity = ray_scope_vel.z;
	if (devset)
		weapon_sprites(weapon, name);
}

void			init_weapon(t_env *env)
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
	weapon_set(&env->world.armory[MAGNUM], "weapons/magnum", 56,
		(t_vctr){R_MAGNUM, S_MAGNUM, V_MAGNUM}, 1);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[SHOTGUN], "weapons/pompe", 100,
		(t_vctr){R_SHOTGUN, S_SHOTGUN, V_SHOTGUN}, 1);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[RIFLE], "weapons/rifle", 30,
		(t_vctr){R_RIFLE, S_RIFLE, V_RIFLE}, 1);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[RPG], "weapons/rpg", 100,
		(t_vctr){R_RPG, S_RPG, V_RPG}, 1);
	printf("time weapon: %u\n", SDL_GetTicks());
	weapon_set(&env->world.armory[FIST], "weapons/fist", 45,
		(t_vctr){R_FIST, S_FIST, V_FIST}, 1);
	printf("time weapon: %u\n", SDL_GetTicks());

	env->player.inventory.f.ref = FIST;
	env->player.inventory.weapons[FIST].current =
		&env->player.inventory.f;
	env->player.inventory.weapons[FIST].ammo[0] =
		env->world.armory[FIST].ammo_current;
	env->player.inventory.weapons[FIST].ammo[1] =
		env->world.armory[FIST].ammo_magazine;
	env->player.inventory.weapons[FIST].ammo[2] =
		env->world.armory[FIST].damage;
	set_current_wpn(env, &env->player.inventory, FIST);
}

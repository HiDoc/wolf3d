/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:56:37 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 21:53:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		current_sprite(t_bloc *bloc, char *file, int i)
{
	SDL_Surface	*sprite;

	sprite = ui_img(file, i, 0);
	bloc->sprite = make_surface(W, H);
	img_scaled_copy(sprite, bloc->sprite);
	bloc->rect = (SDL_Rect){0, 0, W, H};
	bloc->limit.v1 = (t_vtx){0, 0};
	lt_release((void**)&sprite);
}

static t_bloc	*weapon_fill(char *path, int size)
{
	t_bloc	*weapons;
	int		i;

	weapons = ft_memalloc(sizeof(t_bloc) * size);
	i = -1;
	while (++i < size)
		current_sprite(&weapons[i], path, i);
	return (weapons);
}

static void		weapon_sprites(t_weapon *weapon, char *name)
{
	char	*r_path;
	char	*s_path;
	char	*sprite;

	r_path = ft_strjoin(name, "/reload/");
	s_path = ft_strjoin(name, "/shoot/");
	sprite = ft_strjoin(name, "/");
	current_sprite(&weapon->sprite, sprite, 0);
	weapon->sprite_reload = weapon_fill(r_path, weapon->time_reload);
	weapon->sprite_shoot = weapon_fill(s_path, weapon->time_shoot);
	lt_release((void**)&r_path);
	lt_release((void**)&s_path);
	lt_release((void**)&sprite);
}

static void		weapon_set(t_weapon *weapon, char *name, int dam,
				t_vctr ray_scope_vel)
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
	weapon_sprites(weapon, name);
}

void			init_weapon(t_env *env)
{
	t_wrap_wpn	*wpn;
	t_wrap_sect	obj;

	ft_bzero(&obj, sizeof(t_wrap_sect));
	env->world.armory[MAGNUM].ref = 0xa2a0601042a2;
	env->world.armory[SHOTGUN].ref = 0xa2a020105123;
	env->world.armory[RIFLE].ref = 0xa8e2000042a4;
	env->world.armory[RPG].ref = 0xa08010108242;
	env->world.armory[FIST].ref = 0xa00000103002;
	weapon_set(&env->world.armory[MAGNUM], "weapons/magnum", 56,
		(t_vctr){R_MAGNUM, S_MAGNUM, V_MAGNUM});
	weapon_set(&env->world.armory[SHOTGUN], "weapons/pompe", 100,
		(t_vctr){R_SHOTGUN, S_SHOTGUN, V_SHOTGUN});
	weapon_set(&env->world.armory[RIFLE], "weapons/rifle", 37,
		(t_vctr){R_RIFLE, S_RIFLE, V_RIFLE});
	weapon_set(&env->world.armory[RPG], "weapons/rpg", 100,
		(t_vctr){R_RPG, S_RPG, V_RPG});
	weapon_set(&env->world.armory[FIST], "weapons/fist", 45,
		(t_vctr){R_FIST, S_FIST, V_FIST});
	env->player.inventory.current = ft_memalloc(sizeof(t_wrap_wpn));
	wpn = &env->player.inventory.weapons[FIST];
	obj.ref = FIST;
	fill_wpn_inv(wpn, &env->world.armory[FIST], &obj);
	set_current_wpn(env, &env->player.inventory, FIST);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_gameplay.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:34:12 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/27 20:31:12 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_GAMEPLAY_H
# define DOOM_S_GAMEPLAY_H

/*
** Gameplay structures
** 1 - Objects
** 2 - Weapons
** 3 - Surface
** 4 - Container
** 5 - World
** 6 - Inventory
** 7 - Character
*/

typedef struct s_object			t_object;
typedef struct s_weapon			t_weapon;
typedef struct s_surface		t_surface;
typedef struct s_container		t_container;
typedef struct s_world			t_world;
typedef struct s_inventory		t_inventory;
typedef struct s_character		t_character;

struct					s_object
{
	SDL_Surface	*sprite;
	int			is_consumable;
	int			nb_use;
};

/*
** Weapon struct
** ref : 0xgffeeddccbba
** type = a
** time_reload = bb
** time_shoot = cc
** time_shoot_between = dd
** ammo_current = ee
** ammo_magazine = ff
** damage = g
*/
struct					s_weapon
{
	SDL_Surface	*sprite;
	SDL_Surface	*sprite_bullet;
	SDL_Surface			**sprite_reload;
	SDL_Surface			**sprite_shoot;
	long				ref;
	int					type;
	int					time_reload;
	int					time_shoot;
	double				time_shoot_between;
	int					ammo_current;
	int					ammo_magazine;
	int					ammo_max;
	int					damage;
};

struct					s_container
{
	t_surface		walls[30];
	t_surface		floors[30];
	t_surface		ceils[30];
};

struct					s_world
{
	t_weapon		armory[WORLD_NB_WEAPONS];
	t_object		objects[WORLD_NB_OBJECTS];
	t_container		surfaces;
};

struct					s_inventory
{
	t_weapon	*current;
	t_weapon	*weapons[15];
	t_object	*objects[15];
};

struct					s_character
{
	int			health;
	int			shield;
	int			max_health;
	int			max_shield;
	int			max_weapons;
	int			max_objects;
	float		angle;
	float		anglecos;
	float		anglesin;
	float		yaw;
	float		eyeheight;
	t_inventory	inventory;
	SDL_Surface	*sprite;
};
#endif
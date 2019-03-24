/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_gameplay.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:34:12 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/24 20:30:13 by abaille          ###   ########.fr       */
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
** 7 - Actions
** 8 - Character
*/

typedef struct s_object		t_object;
typedef struct s_weapon		t_weapon;
typedef struct s_surface	t_surface;
typedef struct s_container	t_container;
typedef struct s_world		t_world;
typedef struct s_inventory	t_inventory;
typedef struct s_actions	t_actions;
typedef struct s_character	t_character;

struct						s_object
{
	SDL_Surface	*sprite;

	int			nb_use;
	int			max_stack;
	int			ref;
	int			sectorno;
	t_vtx		vertex;
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
struct						s_weapon
{
	t_bloc				sprite;
	t_bloc				sprite_bullet;
	t_bloc				*sprite_reload;
	t_bloc				*sprite_shoot;
	// SDL_Surface			*sprite;
	// SDL_Surface			*sprite_bullet;
	// SDL_Surface			**sprite_reload;
	// SDL_Surface			**sprite_shoot;
	long				ref;
	int					type;
	int					time_reload;
	int					time_shoot;
	double				time_shoot_between;
	int					ammo_current;
	int					ammo_curr_max;
	int					ammo_magazine;
	int					ammo_mag_max;
	int					ammo_max;
	int					damage;
	Mix_Chunk			*shot;
};

struct						s_container
{
	t_surface	walls[30];
	t_surface	floors[30];
	t_surface	ceils[30];
	SDL_Surface	*hud[NB_HUD_OBJ];
};

struct						s_world
{
	t_weapon	armory[WORLD_NB_WEAPONS];
	t_object	objects[WORLD_NB_OBJECTS];
	t_container	surfaces;
};

struct						s_inventory
{
	t_wrap_wpn	*current;
	t_wrap_wpn	weapons[WORLD_NB_WEAPONS];
	t_wrap_inv	objects[6];
	int			nb_current_obj;
};

struct						s_actions
{
	t_edge		edge;
    int         is_shield;
    int         is_health;
    int         is_ammo;
	int			is_running;
	int			sub_action;
	int			is_shooting;
	int			is_loading;
	int			is_flying;
	int			mouse_state;
};

struct						s_character
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
	SDL_Surface	*sprite;
	t_inventory	inventory;
	t_actions	actions;
	t_hud		hud;
};

#endif

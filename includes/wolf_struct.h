/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_struct.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:54:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/23 14:07:47 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_STRUCT_H
# define WOLF_STRUCT_H

typedef struct s_env				t_env;
typedef struct s_sdl				t_sdl;
typedef struct s_msc				t_msc;

/*
**	Gameplay Structure
*/

typedef struct s_object			t_object;
typedef struct s_world			t_world;
typedef struct s_surface		t_surface;
typedef struct s_weapon			t_weapon;
typedef struct s_action			t_action;
typedef struct s_inventory		t_inventory;
typedef struct s_container		t_container;
typedef struct s_character		t_character;
typedef struct s_bot			t_bot;

struct					s_sdl
{
	Uint32				pixels[WIDTH * HEIGHT];
	int					width;
	int					height;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Surface			*surface;
	SDL_Event			event;
};



struct					s_msc
{
	Mix_Music	*load;
	Mix_Chunk	*shot;
};

/*
** Gameplay structures
** 1 - Objects
** 2 - Weapons
** 3 - Surface
** 4 - Container
** 5 - World
** 6 - Actions
** 7 - Inventory
** 8 - Character
*/

struct					s_object
{
	SDL_Surface	*sprite;
	int			is_consumable;
	int			nb_use;
};

/*
** Weapon struct
** ref : 0xgffeeddccbba
** weapon->type = a
** weapon->time_reload = bb
** weapon->time_shoot = cc
** weapon->time_shoot_between = dd
** weapon->ammo_current = ee
** weapon->ammo_magazine = ff
** weapon->damage = g
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

struct					s_surface
{
	SDL_Surface			*sprite;
	int					health;
	int					height;
	int					width;
	double				angle;
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

struct					s_action
{
	int					is_shooting;
	int					is_loading;
	int					is_swimming;
	int					is_flying;
	int					is_jumping;
	int					is_up_down;
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
	double		angle_d;
	double		angle_r;
	t_action	actions;
	t_inventory	inventory;
	SDL_Surface	*sprite;
};

struct					s_env
{
	int			map_w;
	int			map_h;
	t_msc		sounds;

	t_character player;
	t_world		world;
	t_sdl		sdl;
};

#include "doom_engine.h"

#endif

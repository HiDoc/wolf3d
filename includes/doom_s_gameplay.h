/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_gameplay.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:34:12 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/12 13:37:46 by sgalasso         ###   ########.fr       */
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
typedef struct s_thread		t_thread;


struct 								s_thread
{
	int				nb;
	char			*path;
	t_character		*mom;
	SDL_Surface		**kid;
	t_weapon		*mother;
	t_bloc			*child;
	int				size;
	pthread_t		th;
};

struct						s_inventory
{
	t_wrap_sect	f;
	t_wrap_wpn	*current;
	t_wrap_wpn	weapons[WORLD_NB_WEAPONS];
	t_wrap_inv	objects[6];
	t_wrap_inv	gems[4];
	int			nb_current_obj;
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
	t_thread			threads[NB_THREAD_IMG];
	t_bloc				sprite;
	t_bloc				sprite_bullet;
	t_bloc				*sprite_reload;
	t_bloc				*sprite_shoot;
	t_bloc				bullet;
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
	int					scop;
	int					ray;
	int					velocity;

	Mix_Chunk			*shot;
};

struct						s_container
{
	t_surface	walls[WORLD_NB_WALLS];
	t_surface	floors[30];
	t_surface	ceils[30];
	t_surface	hud[NB_HUD_OBJ];
	t_surface	poster[WORLD_NB_POSTERS];
	t_surface	doors[NB_DOOR_IMG];
	t_surface	button[2];
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
	int			is_ammo_illimited;
	int			is_invulnerable;
	int			is_invisible;
	int			is_superstrong;
	int			mouse_state;
};

struct						s_character
{
	long		ref;
	int			type;
	int			is_boss;
	int			damage;
	int			time_walk;
	int			time_shoot;
	int			time_death;
	int			cadence_shoot;
	int			health;
	int			shield;
	int			max_health;
	int			max_shield;
	int			max_weapons;
	int			max_objects;
	SDL_Surface	**walk;
	SDL_Surface	**shoot;
	SDL_Surface	**death;
	SDL_Surface	*bullet;
	t_inventory	inventory;
	t_actions	actions;
	t_impact	*shot;
	t_brain		brain;
	t_thread	threads[NB_THREAD_IMG];
	int			nb_shot;
};

struct						s_world
{
	t_weapon	armory[WORLD_NB_WEAPONS];
	t_object	objects[WORLD_NB_OBJECTS];
	t_character	enemies[WORLD_NB_ENEMIES];
	t_container	surfaces;
};

#endif

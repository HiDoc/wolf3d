/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_wrapper.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:01:35 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 16:09:01 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

#ifndef DOOM_S_WRAPPER_H
# define DOOM_S_WRAPPER_H

typedef struct s_wrap_inv		t_wrap_inv;
typedef struct s_wrap_wpn		t_wrap_wpn;
typedef struct s_wrap_sect      t_wrap_sect;
typedef struct s_wrap_enmy      t_wrap_enmy;
typedef struct	s_vision		t_vision;
typedef struct	s_player		t_player;
typedef struct s_impact			t_impact;
typedef struct s_brain			t_brain;
typedef struct s_actions		t_actions;


struct						s_actions
{
	t_edge		edge;
    int         is_shield;
    int         is_health;
    int         is_ammo;
	int			is_alive;
	int			is_dying;
	int			is_moving;
	int			is_running;
	int			is_flying;
	int			is_shot;
	int			is_shooting;
	int			is_loading;
	int			is_ammo_illimited;
	int			is_invulnerable;
	int			is_invisible;
	int			is_superstrong;
	int			is_alerted;
	int			has_detected;
	int			close_seen;
	int			mouse_state;
};

struct						s_brain
{
	int			health;
	int			scop;
	float		yaw;
	float		dist_player; /* bot dist limit from player */
	float		dist_alert; /* player running */
	float		dis_detec; /* player normal status */
	float		dist_close; /* player ducked */
	float		velocity;
	t_l_float	size; /* sprite size */
};

struct						s_object
{
	SDL_Surface	*sprite;

	int			nb_use;
	int			max_stack;
	int			ref;
	t_vtx		vertex;
	t_l_float	size;
};

struct						s_vision
{
	int			ground;
	int			falling;
	int			moving;
	int			ducking;
	float		yaw;
	float		eyeheight;
};

struct						s_player
{
	t_vctr		origin;
	t_vctr		where;
	t_vctr		whereto;
	t_vctr		velocity;
	t_vision	vision;
	float		angle;
	float		anglesin;
	float		anglecos;
	float		yaw;
	float		yaw_d;
	float		roll_d;
	int		 	nb_shot;
	unsigned 	sector;
	SDL_Surface	*sprite;
	t_sd_stat	sound;
};

struct 						s_impact
{
	SDL_Surface			*sprite;
	int					is_shot;
	t_player			position;
	int					is_alive;
	int					is_shooting;
	float				v;
	int					ref;
};
struct					s_wrap_sect
{
	t_vtx		vertex;
	int			is_picked;
	int			ref;
	int			is_wpn;
    int         (*action)(void *, t_wrap_inv *);
	int			is_pickable;
	int			sectorno;
	int			used;
	t_wrap_sect	*next;
};

struct 					s_wrap_enmy
{
	int				ref;
	int				sectorno;
	int				health;
	int				shield;
	int				damage;
	int				frame;
	int				hit_frame;
	int				walk_frame;
	int				shoot_frame;
	int				die_frame;
	SDL_Surface		*sprite;
	t_brain			brain;
	t_player		player;
	t_actions		a;
	t_impact		shot[NB_SHOT];
	t_wrap_enmy		*next;
};

struct					s_wrap_inv
{
	// t_wrap_sect		*current;
    int         	(*action)(void *, t_wrap_inv *);
	int				nb_stack;
    int             is_used;
	int				is_full;
	int				ref;
};

struct					s_wrap_wpn
{
	// t_wrap_sect		*current;
	int				*ammo_current;
	int				*ammo_magazine;
	int				*damage;
	int				ammo[3];
	int				is_full;
	int				ref;
};

#endif

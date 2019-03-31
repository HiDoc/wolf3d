/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_wrapper.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:01:35 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/31 14:59:34 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

#ifndef DOOM_S_WRAPPER_H
# define DOOM_S_WRAPPER_H

typedef struct s_wrap_inv		t_wrap_inv;
typedef struct s_wrap_wpn		t_wrap_wpn;
typedef struct s_wrap_sect      t_wrap_sect;
typedef struct s_wrap_enmy      t_wrap_enmy;

struct					s_wrap_sect
{
	t_vtx		vertex;
	int			is_picked;
	int			ref;
	int			is_wpn;
    int         (*action)(void *, t_wrap_inv *);
	int			is_pickable;
	t_wrap_sect	*next;
};

struct 					s_wrap_enmy
{
	int				ref;
	int				health;
	int				shield;
	int				damage;
	int				is_alive;
	int				is_alerted;
	int				has_detected;
	int				close_seen;
	int				is_shooting;
	int				frame;
	float			angle;
	float			anglecos;
	float			anglesin;
	float			yaw;
	t_vtx			origin;
	t_vtx			where;
	t_vtx			whereto;
	t_vtx			velocity;
	t_wrap_enmy		*next;
};


struct					s_wrap_inv
{
	t_wrap_sect		*current;
	int				nb_stack;
    int             is_used;
};

struct					s_wrap_wpn
{
	t_wrap_sect		*current;
	int				ammo_current;
	int				ammo_magazine;
	int				damage;
};

#endif

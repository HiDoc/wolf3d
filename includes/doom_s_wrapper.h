/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_wrapper.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 14:01:35 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/15 18:35:47 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

#ifndef DOOM_S_WRAPPER_H
# define DOOM_S_WRAPPER_H

typedef struct s_wrap_inv		t_wrap_inv;
typedef struct s_wrap_wpn		t_wrap_wpn;
typedef struct s_wrap_sect      t_wrap_sect;

struct					s_wrap_sect
{
	t_vtx		vertex;
	int			is_picked;
	int			ref;
	int			is_wpn;
    int         (*action)(void *, t_wrap_inv *);
	t_wrap_sect	*next;
};

struct					s_wrap_inv
{
	t_wrap_sect		*current;
	int				nb_stack;
    int             is_used;
	t_edge			udbox[2];
};

struct					s_wrap_wpn
{
	t_wrap_sect		*current;
	int				ammo_current;
	int				ammo_magazine;
};

#endif
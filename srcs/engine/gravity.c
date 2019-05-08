/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:03:17 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 21:25:39 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	set_gravity(t_player *plr, t_l_float l, t_vision *v)
{
	plr->where.z = l.floor + v->eyeheight;
	plr->velocity.z = 0;
	v->falling = 0;
	v->ground = 1;
}

void	handle_gravity(t_vision *v, t_engine *e, float gravity)
{
	t_l_float	l;
	t_player	*plr;
	float		nextz;
	t_vtx		bezier;

	l.ceil = e->sectors[e->player.sector].ceil;
	l.floor = e->sectors[e->player.sector].floor;
	plr = &e->player;
	plr->velocity.z -= gravity;
	bezier = bezier_curve(
		(t_edge){(t_vtx){0, EYEHEIGHT}, (t_vtx){20, EYEHEIGHT}},
		(t_vtx){0, 40}, 1 - (plr->velocity.z + 0.12f));
	nextz = (plr->velocity.z < 0) ? plr->where.z + plr->velocity.z : bezier.y;
	if (plr->velocity.z < 0 && nextz < (l.floor + v->eyeheight))
		set_gravity(plr, l, v);
	if (plr->where.z > l.ceil || nextz > l.ceil)
		plr->where.z = l.ceil;
	if (v->falling)
	{
		plr->where.z = bezier.y;
		v->moving = 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 12:31:27 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/20 14:12:07 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vtx	relative_to_absolute(t_player player, float X, float Z)
{
	float			rtx;
	float			rtz;
	const float		pcos = player.anglecos;
	const float		psin = player.anglesin;

	rtx = (Z) * pcos + (X) * psin;
	rtz = (Z) * psin - (X) * pcos;
	X = rtx + player.where.x;
	Z = rtz + player.where.y;
	return (t_vtx){X, Z};
}

t_vtx	screen_to_map(t_engine *e, float mapY, float screenX, float screenY)
{
	const t_player	player = e->player;
	float 			Z;
	float 			X;

	Z = (mapY) * H * VFOV / ((H / 2 - (screenY)) - player.yaw * H * VFOV);
	X = (Z) * (W / 2 - (screenX)) / (W * HFOV);
	return relative_to_absolute(player, X, Z);
}

int scaler_next(t_scaler *i)
{
	i->cache += i->fd;
    while (i->cache >= i->ca)
	{
	  	i->result += i->bop;
	 	i->cache -= i->ca;
	}
    return (i->result);
}

t_scaler scaler_init(int a, int b, int c, int d, int f)
{
	t_scaler	new;

	new = (t_scaler)
	{
		d + (b - 1 - a) * (f - d) / (c - a),
		((f < d) ^ (c < a)) ? -1 : 1,
      	abs(f - d),
		abs(c - a),
		(int)((b - 1 - a) * abs(f - d)) % abs(c - a)
	};
	return (new);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 21:26:01 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/25 21:26:03 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static float	yaw(float p_yaw, float y, float z)
{
	return (y + z * p_yaw);
}

t_projec		calc_projection(float p, t_limit_float l, t_edge t, t_edge s)
{
	t_projec	projection;
	const int	h2 = H / 2;

	projection = (t_projec)
	{
		h2 - (int)(yaw(p, l.ceil, t.v1.y) * s.v1.y),
		h2 - (int)(yaw(p, l.floor, t.v1.y) * s.v1.y),
		h2 - (int)(yaw(p, l.ceil, t.v2.y) * s.v2.y),
		h2 - (int)(yaw(p, l.floor, t.v2.y) * s.v2.y)
	};
	return (projection);
}
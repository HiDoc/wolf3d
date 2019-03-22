/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 21:26:01 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/22 13:06:12 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float		yaw(float p_yaw, float y, float z)
{
	return (y + z * p_yaw);
}

t_projec	calc_projec(float pyaw, t_l_float lim, t_edge rot, t_edge scale)
{
	t_projec	ret;
	const int	h2 = H / 2;

	ret.y1a = h2 - (int)(yaw(pyaw, lim.ceil, rot.v1.y) * scale.v1.y);
	ret.y1b = h2 - (int)(yaw(pyaw, lim.floor, rot.v1.y) * scale.v1.y);
	ret.y2a = h2 - (int)(yaw(pyaw, lim.ceil, rot.v2.y) * scale.v2.y);
	ret.y2b = h2 - (int)(yaw(pyaw, lim.floor, rot.v2.y) * scale.v2.y);
	return (ret);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:29:45 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/14 18:58:31 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** e.v1 is the start point
** e.v2 is the end point
** c_point is the control point
** time is the parameter, from 0 to 1
*/
t_vtx	bezier_curve(t_edge e, t_vtx c_point, float t)
{
	t_vtx		res;

	e.v1 = (t_vtx) {0, 6};
	e.v2 = (t_vtx) {20, 6};
	c_point = (t_vtx) {0, 15};
	res.x = (1 - t) * (1 - t) * e.v1.x + 2 * (1 - t) * t * c_point.x + t * t * e.v2.x;
	res.y = (1 - t) * (1 - t) * e.v1.y + 2 * (1 - t) * t * c_point.y + t * t * e.v2.y;
	return (res);
}

int		edge_parallel(t_edge e1, t_edge e2)
{
	const float dist = e1.v2.y - e1.v1.y;
	const float scale = e1.v2.x - e1.v1.x;
	const float a = dist / scale;
	const float b = (cross_product(e1.v2, e1.v1)) / (scale);

	return (e2.v1.y == a * e2.v1.x + b
		&& e2.v2.y == a * e2.v2.x + b);
}

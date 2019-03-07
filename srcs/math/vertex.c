/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 19:48:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/25 21:51:01 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Calculate the cross product of two vertexes
*/
float   cross_product(t_vtx v1, t_vtx v2)
{
	return (v1.x * v2.y - v2.x * v1.y); 
}

/*
** Determine which side of a line the point is on.
** Return value: <0, =0 or >0.
*/
float pointside(t_vtx p, t_vtx v0, t_vtx v1)
{
	return (cross_product(diff_vertex(v1, v0), diff_vertex(p, v0)));
}

/*
** Calculate the point of intersection between two lines.
*/
t_vtx		intersect_vtx(t_vtx v1, t_vtx v2, t_vtx v3, t_vtx v4)
{
	t_vtx   v;
	float   div;
	float   xs1;
	float   xs2;
	float   (*f)(t_vtx, t_vtx);

	f = &cross_product;
	xs1 = f(v1, v2);
	xs2 = f(v3, v4);
	div = f((t_vtx){v1.x - v2.x, v1.y - v2.y},
		(t_vtx){v3.x - v4.x, v3.y - v4.y});
	v.x = f((t_vtx){xs1, v1.x - v2.x}, (t_vtx){xs2, v3.x - v4.x}) / div;
	v.y = f((t_vtx){xs1, v1.y - v2.y}, (t_vtx){xs2, v3.y - v4.y}) / div;
	return (v);
}

/*
** Return if ranges a & b are overlaping
*/
static int	overlap(float a0, float a1, float b0, float b1)
{
	return (fmin(a0, a1) <= fmax(b0, b1) && fmin(b0, b1) <= fmax(a0, a1));
}

/*
** Return if two rectangles got an intersection
*/
int			intersect_rect(t_vtx a_up, t_vtx a_bot, t_vtx b_up, t_vtx b_bot)
{
	return (overlap(a_up.x, a_bot.x, b_up.x, b_bot.x)
			&& overlap(a_up.y, a_bot.y, b_up.y, b_bot.y));
}
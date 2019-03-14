/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vertex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 21:29:30 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/12 14:10:30 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Return if vertex are equals
*/
int     equal_vertex(t_vtx v1, t_vtx v2)
{
    return (v1.x == v2.x && v1.y == v2.y);
}

/*
** Calculate distance between a and b
*/
float   dist_vertex(t_vtx a, t_vtx b)
{
    const float distx = b.x - a.x;
    const float disty = b.y - a.y;

    return (distx * distx + disty * disty);
}

/*
** Difference of two vertex.
** Return a new vertex {x1 - x2, y1 - y2}
*/
t_vtx   diff_vertex(t_vtx v1, t_vtx v2)
{
    return ((t_vtx){v1.x - v2.x, v1.y - v2.y});
}

/*
** Addition of two vertex.
** Return a new vertex {x1 + x2, y1 + y2}
*/
t_vtx   add_vertex(t_vtx v1, t_vtx v2)
{
    return ((t_vtx){v1.x + v2.x, v1.y + v2.y});
}

/*
** Clamp value into set range.
*/
float   clamp(float a, float min, float max)
{
    return (fmin(fmax(a, min), max));
}
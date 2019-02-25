/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vertex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 21:29:30 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/25 21:35:02 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
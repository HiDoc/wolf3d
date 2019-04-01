/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_edge.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 19:47:11 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/29 20:34:37 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int     equal_edge(t_edge e1, t_edge e2)
{
	return (equal_vertex(e1.v1, e2.v1) && equal_vertex(e1.v2, e2.v2))
		|| (equal_vertex(e1.v1, e2.v2) && equal_vertex(e1.v2, e2.v1));
}
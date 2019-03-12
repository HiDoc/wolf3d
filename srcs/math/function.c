/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 20:29:45 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/12 12:07:56 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		edge_parallel(t_edge e1, t_edge e2)
{
	const float dist = e1.v2.y - e1.v1.y;
	const float scale = e1.v2.x - e1.v1.x;
	const float a = dist / scale;
	const float b = (cross_product(e1.v2, e1.v1)) / (scale);

	return (e2.v1.y == a * e2.v1.x + b
		&& e2.v2.y == a * e2.v2.x + b);
}

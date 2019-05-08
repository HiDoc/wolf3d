/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:14:02 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 13:45:38 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			point_in_rect(t_pos pos, SDL_Rect rect)
{
	return (pos.x >= rect.x && pos.x <= rect.x + rect.w
	&& pos.y >= rect.y && pos.y <= rect.y + rect.h);
}

float		pythagore(t_pos p1, t_pos p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

t_pos		get_edge_center(t_pos a, t_pos b)
{
	t_pos	center;

	center.x = (a.x + b.x) / 2;
	center.y = (a.y + b.y) / 2;
	return (center);
}

/*
** Determine which side of a line the point is on.
** Return value: left < 0, on line 0, right > 0.
*/

float		pointside(t_pos p, t_pos p0, t_pos p1)
{
	t_pos	res1;
	t_pos	res2;
	float	res;

	res1 = (t_pos){p1.x - p0.x, p1.y - p0.y};
	res2 = (t_pos){p.x - p0.x, p.y - p0.y};
	res = res1.x * res2.y - res2.x * res1.y;
	return (res);
}

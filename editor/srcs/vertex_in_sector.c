/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_in_sector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 22:51:52 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/10 15:02:25 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

// TEMPORAIRE ////////////////////////////////////////////
static int	max(int a, int b)
{
	return (a > b ? a : b);
}

static int	min(int a, int b)
{
	return (a < b ? a : b);
}

int			onSegment(t_pos p, t_pos q, t_pos r) 
{ 
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x)
	&& q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
		return (1);
	return (0); 
}

static int	orientation(t_pos p, t_pos q, t_pos r) 
{
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 

	if (val == 0)
		return (0);
	return (val > 0) ? 1 : 2;
}

int		intersect_vrx(t_pos p1, t_pos q1, t_pos p2, t_pos q2) 
{ 
	//Find the four orientations needed for general and 
	// special cases
	int o1 = orientation(p1, q1, p2); 
	int o2 = orientation(p1, q1, q2); 
	int o3 = orientation(p2, q2, p1); 
	int o4 = orientation(p2, q2, q1); 

	// General case 
	if (o1 != o2 && o3 != o4) 
		return (1); 

	// Special Cases 
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1))
		return (1); 

	// p1, q1 and q2 are colinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1))
		return (1); 

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2))
		return (1); 

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2))
		return (1); 

	return (0); // Doesn't fall in any of the above cases 
} 
//////////////////////////////////////////////////////////////

static int	filter_target(t_sct *sector, t_env *env)
{
	return (env->data->mouse.x >= sector->xmin
			&& env->data->mouse.x <= sector->xmax
			&& env->data->mouse.y >= sector->ymin
			&& env->data->mouse.y <= sector->ymax);
}

static int	filter_edges(const t_pos pos, t_vtx *vertex)
{
	const float		a_y = vertex->pos.y;
	const float		b_y = vertex->next->pos.y;

	if (a_y < b_y && (pos.y < a_y || pos.y > b_y))
		return (0);
	else if (a_y > b_y && (pos.y < b_y || pos.y > a_y))
		return (0);
	return (1);
}

int			vertex_in_sector(t_sct *sector, t_pos pos_b, t_env *env)
{
	const t_pos	pos_a = (t_pos){sector->xmin, pos_b.y};
	t_vtx		*vertex;
	int			intersect;

	intersect = 0;
	if (!(filter_target(sector, env)))
		return (0);
	vertex = sector->vtx_start;
	while (vertex && vertex->next) // for each edge
	{
		if (filter_edges((const t_pos)pos_b, vertex))
		{
			if ((intersect_vrx(vertex->pos, vertex->next->pos, pos_a, pos_b)))
				intersect++;
		}
		vertex = vertex->next;
	}
	// for last edge
	if ((intersect_vrx(vertex->pos, sector->vtx_start->pos, pos_a, pos_b)))
		intersect++;
	return (intersect % 2);
}

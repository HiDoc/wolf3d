/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 17:14:02 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/03 16:41:55 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int     poscmp(t_pos a, t_pos b)
{
	return (a.x == b.x && a.y == b.y);
}

int             point_in_rect(t_pos pos, SDL_Rect rect)
{
	return (pos.x >= rect.x && pos.x <= rect.x + rect.w
	&& pos.y >= rect.y && pos.y <= rect.y + rect.h);
}

/*static*/ int	sctvtx_in_sct(t_sct *current, t_sct *sct)
{
	t_w_vtx		*w_vtx;

	w_vtx = sct->w_vtx_start;
	while (w_vtx)
	{
		if (!shared_vtx(w_vtx->vtx, current))
		{
			if (vertex_in_sector(current, w_vtx->vtx->pos))
				return (1);
		}
		w_vtx = w_vtx->next;
	}
	return (0);
}

/*
 * ** Return if ranges a & b are overlaping
 * */
static int	overlap(float a0, float a1, float b0, float b1)
{
		return (fmin(a0, a1) <= fmax(b0, b1) && fmin(b0, b1) <= fmax(a0, a1));
}

/*
 * ** Return if two rectangles got an intersection
 * */
static int	intersect_rect(t_pos a_up, t_pos a_bot, t_pos b_up, t_pos b_bot)
{
	return (overlap(a_up.x, a_bot.x, b_up.x, b_bot.x)
		&& overlap(a_up.y, a_bot.y, b_up.y, b_bot.y));
}

static int	vec_intersect(t_pos p0, t_pos p1, t_pos p2, t_pos p3)
{
	return (intersect_rect(p0, p1, p2, p3)
		&& fabs(pointside(p2, p0, p1) + pointside(p3, p0, p1)) != 2
		&& fabs(pointside(p0, p2, p3) + pointside(p1, p2, p3)) != 2);
}

static int	sctedg_intersect(t_sct *current, t_sct *sct)
{
	t_w_vtx		*cw_vtx;
	t_w_vtx		*sw_vtx;

	cw_vtx = current->w_vtx_start;
	while (cw_vtx && cw_vtx->next)
	{
		sw_vtx = sct->w_vtx_start;
		while (sw_vtx && sw_vtx->next)
		{
			if (vec_intersect(cw_vtx->vtx->pos, cw_vtx->next->vtx->pos,
					sw_vtx->vtx->pos, sw_vtx->next->vtx->pos))
				return (1);
			sw_vtx = sw_vtx->next;
		}
		if (vec_intersect(cw_vtx->vtx->pos, cw_vtx->next->vtx->pos,
				sw_vtx->vtx->pos, sct->w_vtx_start->vtx->pos))
			return (1);
		cw_vtx = cw_vtx->next;
	}
	sw_vtx = sct->w_vtx_start;
	while (sw_vtx && sw_vtx->next)
	{
		if (vec_intersect(cw_vtx->vtx->pos, current->w_vtx_start->vtx->pos,
				sw_vtx->vtx->pos, sw_vtx->next->vtx->pos))
			return (1);
		sw_vtx = sw_vtx->next;
	}
	if (vec_intersect(cw_vtx->vtx->pos, current->w_vtx_start->vtx->pos,
			sw_vtx->vtx->pos, sct->w_vtx_start->vtx->pos))
		return (1);
	return (0);
}

int			sector_overlap(t_env *env)
{
	t_sct		*current;
	t_sct		*sct;

	current = env->editor.sct_start;
	while (current)
	{
		sct = env->editor.sct_start;
		while (sct)
		{
			if (sct != current)
			{
				if (sctvtx_in_sct(current, sct))
					return (1);
				if (sctedg_intersect(current, sct))
					return (1);
			}
			sct = sct->next;
		}
		current = current->next;
	}
	return (0);
}

float	pythagore(t_pos p1, t_pos p2)
{
	return (sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

t_pos			get_edge_center(t_pos a, t_pos b)
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

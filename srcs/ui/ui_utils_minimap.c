/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_utils_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:48:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 23:02:49 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				point_in_circle(t_vtx vtx, t_circle circle)
{
	return (sqrt(pow(vtx.x - circle.x, 2) + pow(vtx.y - circle.y, 2))
		< circle.radius);
}

static void		norme(SDL_Rect src_rect, t_vtx pos,
	t_circle circle, t_env *env)
{
	t_vtx				origin = env->engine.minimap.origin;

	const t_engine		*e = &env->engine;
	const t_vtx     	c = {src_rect.w / 2, src_rect.h / 2};
	t_vtx           	dest;
	Uint32          	color;
	t_vtx				vtx;

	vtx = (t_vtx){origin.x + pos.x, origin.y + pos.y};
	if (point_in_circle(vtx, circle))
	{
		dest = (t_vtx){
		c.x + (pos.x - c.x) * sin(-e->player.angle)
			- (pos.y - c.y) * cos(-e->player.angle),
		c.y + (pos.x - c.x) * cos(-e->player.angle)
			+ (pos.y - c.y) * sin(-e->player.angle)};
		if ((color = getpixel(e->minimap.surface, src_rect.x + dest.x,
		src_rect.y + dest.y)))
			setpixel(env->sdl.surface, origin.x + pos.x, origin.y + pos.y, color);
	}
}

void			rotate_surface(SDL_Rect src_rect, t_circle circle, t_env *env)
{
	t_vtx				pos;

	pos.y = 0;
	while (pos.y < src_rect.h)
	{
		pos.x = 0;
		while (pos.x < src_rect.w)
		{
			norme(src_rect, pos, circle, env);
			pos.x++;
		}
		pos.y++;
	}
}

t_edge		translate_edge(t_vctr player_position, t_vtx v1, t_vtx v2)
{
	t_edge      edge;

	edge.v1 = (t_vtx){v1.x - player_position.x, v1.y - player_position.y};
	edge.v2 = (t_vtx){v2.x - player_position.x, v2.y - player_position.y};
	return (edge);
}

t_edge		rotate_edge(t_player player, t_edge v)
{
	const float pcos = -player.anglecos;
	const float psin = -player.anglesin;
	t_edge      edge;

	edge.v1 = (t_vtx){v.v1.x * psin - v.v1.y * pcos,
		v.v1.x * pcos + v.v1.y * psin};
	edge.v2 = (t_vtx){v.v2.x * psin - v.v2.y * pcos,
		v.v2.x * pcos + v.v2.y * psin};
	return (edge);
}

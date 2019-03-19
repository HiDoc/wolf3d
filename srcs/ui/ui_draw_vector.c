/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:12:33 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/19 19:20:51 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ui_draw_vector(SDL_Surface *surface, t_vtx vtx, float angle,
		float start, float size, Uint32 color) // mettre a la norme
{
	t_edge	edge;
	float	step_x;
	float	step_y;
	t_vtx	vtx_a;
	t_vtx	vtx_b;

	step_x = cos(angle * M_PI / 180) * start;
	step_y = sin(angle * M_PI / 180) * start;
	vtx_a.x = vtx.x + step_x;
	vtx_a.y = vtx.y + step_y;

	step_x = cos(angle * M_PI / 180) * size;
	step_y = sin(angle * M_PI / 180) * size;
	vtx_b.x = vtx.x + step_x;
	vtx_b.y = vtx.y + step_y;

	edge = (t_edge){vtx_a, vtx_b};

	ui_draw_line(surface, edge, color);
}

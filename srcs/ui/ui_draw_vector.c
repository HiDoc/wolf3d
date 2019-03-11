/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:12:33 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/11 16:06:01 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ui_draw_vector(SDL_Surface *surface, t_vtx vtx_a, float angle,
		float size, Uint32 color) // mettre a la norme
{
	t_edge	edge;
	float	step_x;
	float	step_y;
	t_vtx	vtx_b;

	step_x = cos(angle) * size;
	step_y = sin(angle) * size;

	vtx_b.x = vtx_a.x + step_x;
	vtx_b.y = vtx_a.y + step_y;

	edge = (t_edge){vtx_a, vtx_b};

	ui_draw_line(surface, edge, color);
}

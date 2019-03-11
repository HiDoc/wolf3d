/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_full_rect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 17:27:18 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/11 18:20:46 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ui_draw_full_rect(SDL_Surface *surface, SDL_Rect rect, Uint32 color)
{
	t_edge		edge;
	int			y;

	y = rect.y;
	while (y < rect.y + rect.h)
	{
		edge.v1 = (t_vtx){rect.x, y};
		edge.v2 = (t_vtx){rect.x + rect.w, y};
		ui_draw_line(surface, edge, color);
		y++;
	}
}

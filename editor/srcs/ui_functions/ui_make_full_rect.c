/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_full_rect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:29:53 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/16 15:14:27 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_make_full_rect(SDL_Surface *surface, SDL_Rect rect, Uint32 color)
{
	t_vec		edge;
	int			y;

	y = rect.y;
	while (y < rect.y + rect.h)
	{
		edge.a = (t_pos){rect.x, y};
		edge.b = (t_pos){rect.x + rect.w, y};
		ui_make_line(surface, edge, color);
		y++;
	}
}

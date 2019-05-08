/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:12:33 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 23:04:50 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
**	recup en radian
*/

void	ui_draw_vector(SDL_Surface *surface, t_pos pos, float angle,
		float size, Uint32 color) // mettre a la norme
{
	t_pos	pos_b;

	pos_b.x = pos.x + cos(angle) * size;
	pos_b.y = pos.y - sin(angle) * size;
	ui_make_line(surface, (t_vec){pos, pos_b}, color);
}

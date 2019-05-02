/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:12:33 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/01 12:58:10 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_draw_vector(SDL_Surface *surface, t_pos pos, float angle,
		float start, float size, Uint32 color) // mettre a la norme
{
	float	step_x;
	float	step_y;
	t_pos	pos_a;
	t_pos	pos_b;

	step_x = cos(angle) * start;
	step_y = sin(angle) * start;
	pos_a.x = pos.x + step_x;
	pos_a.y = pos.y + step_y;

	step_x = cos(angle) * size;
	step_y = sin(angle) * size;
	pos_b.x = pos.x + step_x;
	pos_b.y = pos.y + step_y;

	ui_make_line(surface, (t_vec){pos_a, pos_b}, color);
}

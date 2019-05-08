/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_fill_square.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:37:43 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 22:37:51 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_fill_square(SDL_Surface *surface, SDL_Rect rect, Uint32 color)
{
	t_vec		vec;

	vec.a = (t_pos){rect.x, rect.y};
	vec.b = (t_pos){rect.x + rect.w, rect.y};
	ui_make_line(surface, vec, color);
	vec.a = (t_pos){rect.x + rect.w, rect.y};
	vec.b = (t_pos){rect.x + rect.w, rect.y + rect.h};
	ui_make_line(surface, vec, color);
	vec.a = (t_pos){rect.x + rect.w, rect.y + rect.h};
	vec.b = (t_pos){rect.x, rect.y + rect.h};
	ui_make_line(surface, vec, color);
	vec.a = (t_pos){rect.x, rect.y + rect.h};
	vec.b = (t_pos){rect.x, rect.y};
	ui_make_line(surface, vec, color);
}

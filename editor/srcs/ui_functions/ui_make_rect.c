/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_rect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:34:21 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/07 23:01:40 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_make_rect(SDL_Surface *surface, SDL_Rect rect, Uint32 color)
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

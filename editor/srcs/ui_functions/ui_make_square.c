/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_square.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:43:40 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/02 19:54:55 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_make_square(t_rect rect, int grp, int idx, t_data *data)
{
	t_vec		vec;

	(void)grp;
	(void)idx;
	/*data->objects.square[data->objects.square_index].rect = rect;
	data->objects.square[data->objects.square_index].index = idx;
	data->objects.square[data->objects.square_index].group = grp;
	data->objects.square_index++;*/

	vec.a = (t_pos){rect.x, rect.y};
	vec.b = (t_pos){rect.x + rect.w, rect.y};
	ui_make_line(data->surface, vec, rect.color);

	vec.a = (t_pos){rect.x + rect.w, rect.y};
	vec.b = (t_pos){rect.x + rect.w, rect.y + rect.h};
	ui_make_line(data->surface, vec, rect.color);

	vec.a = (t_pos){rect.x + rect.w, rect.y + rect.h};
	vec.b = (t_pos){rect.x, rect.y + rect.h};
	ui_make_line(data->surface, vec, rect.color);

	vec.a = (t_pos){rect.x, rect.y + rect.h};
	vec.b = (t_pos){rect.x, rect.y};
	ui_make_line(data->surface, vec, rect.color);
}

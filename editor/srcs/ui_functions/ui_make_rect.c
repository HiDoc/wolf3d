/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_rect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:34:21 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/16 15:14:29 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_make_rect(t_rect rect, t_data *data)
{
	t_vec		vec;

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

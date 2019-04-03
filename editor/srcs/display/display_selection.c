/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:13 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/02 18:18:16 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_selection(t_env *env)
{
	t_rect		rect;

	// display selection area
	rect = (t_rect){890, 100, 290, 250, 0xFFFFFFFF};
	ui_make_rect(env->data->surface, rect);

	//dislay hovered
	rect = (t_rect){910, 120, 250, 30, 0xFFFFFFFF};
	if (env->obj_hover)
		ui_make_string(rect, "object", env->data);
	else if (env->sct_hover)
		ui_make_string(rect, "sector", env->data);
	else if (env->vtx_hover)
		ui_make_string(rect, "vertex", env->data);
}

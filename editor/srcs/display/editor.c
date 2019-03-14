/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 11:58:03 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/14 16:15:16 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		editor(t_env *env)
{
	t_rect		rect;

	display_interface(env);
	display_selection(env);

	// display buttons
	rect = (t_rect){20, 20, 100, 40, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);
	rect = (t_rect){45, 30, 0, 25, 0xFFFFFFFF};
	ui_make_string(rect, "New", env->data);
	rect = (t_rect){130, 20, 125, 40, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);
	rect = (t_rect){155, 30, 0, 25, 0xFFFFFFFF};
	ui_make_string(rect, "Upload", env->data);
	rect = (t_rect){300, 20, 100, 40, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);
	rect = (t_rect){324, 30, 0, 25, 0xFFFFFFFF};
	ui_make_string(rect, "Save", env->data);

	// display nb frames
	rect = (t_rect){1100, 20, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->data->nb_frames, env->data);

	// display nb element
	rect = (t_rect){900, 600, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Nb sectors : ", env->data);
	rect = (t_rect){1040, 600, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->nb_sct, env->data);
	/*rect = (t_rect){900, 630, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Nb edges : ", env->data);
	rect = (t_rect){1040, 630, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->edg_index + 1, env->data);*/
	rect = (t_rect){900, 660, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Nb vertex : ", env->data);
	rect = (t_rect){1040, 660, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->nb_vtx, env->data);

	// display mouse mode
	rect = (t_rect){720, 20, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Mouse mode : ", env->data);
	rect = (t_rect){850, 20, 0, 20, 0xFFFFFFFF};
	if (env->mouse_mode == 0)
		ui_make_string(rect, "select", env->data);
	else
		ui_make_string(rect, "draw", env->data);
}

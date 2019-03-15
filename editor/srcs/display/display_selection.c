/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:15:13 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/14 16:15:15 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		display_selection(t_env *env)
{
	t_rect		rect;

	// display selection area
	rect = (t_rect){890, 100, 290, 250, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);

	// display selected
	/*rect = (t_rect){30, 110, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "S ", env->data);
	rect = (t_rect){60, 110, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->cur_sct, env->data);*/
	/*rect = (t_rect){30, 130, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "E ", env->data);
	rect = (t_rect){60, 130, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->cur_edg, env->data);
	rect = (t_rect){30, 150, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "V ", env->data);
	rect = (t_rect){60, 150, 0, 20, 0xFFFFFFFF};
	ui_make_nbrstring(rect, env->cur_vrx, env->data);*/

	// display inputs
	rect = (t_rect){900, 110, 0, 20, 0xffffffff};
	ui_make_string(rect, "Selected vertex [S3] [V2]", env->data);
	rect = (t_rect){900, 150, 0, 20, 0xffffffff};
	ui_make_string(rect, "Height", env->data);
	rect = (t_rect){900, 180, 140, 20, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);
	rect = (t_rect){900, 210, 0, 20, 0xFFFFFFFF};
	ui_make_string(rect, "Texture", env->data);
	rect = (t_rect){900, 240, 140, 20, 0xFFFFFFFF};
	ui_make_square(rect, 0, 0, env->data);
}
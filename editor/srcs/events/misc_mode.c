/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 13:31:41 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/26 16:09:38 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		misc_mode(t_env *env)
{
	SDL_Rect	rect = get_element(E_R_RECT, env)->rect;
	t_pos		m = env->data->mouse;

	(void)env;
	return (ui_mouseenter(m.x, m.y, rect) && (m.x || m.y));
}

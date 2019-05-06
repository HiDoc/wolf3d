/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_gameloop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:58:57 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/06 15:07:24 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_gameloop(int (*event)(t_env *env),
		void (*fc)(t_env *env), t_env *env)
{
	ui_make_frame(fc, env);
	while (1)
	{
		if (ui_get_events(event, env))
			ui_make_frame(fc, env);
	}
}

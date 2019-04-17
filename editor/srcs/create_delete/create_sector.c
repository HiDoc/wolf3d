/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:14:48 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/17 04:15:43 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		create_sector(t_env *env)
{
	t_sct	*new;

	if (!(new = lt_push(ft_memalloc(sizeof(t_sct)), ft_memdel)))
		ui_error_exit_sdl("Editor: Out of memory");
	new->xmin = WIN_W + 1;
	new->xmax = -1;
	new->ymin = WIN_H + 1;
	new->ymax = -1;
	new->color = C_CYAN;
	new->next = 0;

	if (!(env->sct_start))
	{
		new->id = 0;
		env->sct_current = new;
		env->sct_start = new;
		env->sct_end = new;
	}
	else
	{
		new->id = env->sct_end->id + 1;
		env->sct_current = new;
		env->sct_end->next = new;
		env->sct_end = new;
	}
	env->nb_sct++;
}

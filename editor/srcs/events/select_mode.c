/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/16 16:03:57 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		unselect_all(t_env *env)
{
	int		i;

	i = 0;
	(void)env;
	/*while (i <= env->sct_index)
	{
		env->sector[i].color = 0xFFFFFFFF;
		env->sector[i].selected = 0;
		i++;
	}*/
}

int			select_mode(t_env *env)
{
	//t_vrx	*hover;

	(void)env;

	// for ISCLOSETO EDGE use pointside return distance from edge

	//unselect_all(env);
	/*if ((hover = dock_vertex(env)))
	{
		hover->sector->color = 0xFF00FF00;
		hover->sector->selected = 1;
	}*/
	return (1);
}

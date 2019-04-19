/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 04:18:03 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/18 01:32:12 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		delete_sct_content(t_sct *sector)
{
	t_w_vtx		*tmp;

	while (sector->w_vtx_start)
	{
		tmp = sector->w_vtx_start->next;
		lt_release(sector->w_vtx_start);
		sector->w_vtx_start = tmp;
	}
}

void			delete_sector(t_sct *sector, t_env *env)
{
	t_sct		*ptr;

	ptr = env->sct_start;
	if (ptr == sector)
	{
		env->sct_start = ptr->next;
		delete_sct_content(sector);
		lt_release(sector);
		return ;
	}
	while (ptr && ptr->next)
	{
		if (ptr->next == sector)
		{
			ptr->next = ptr->next->next;
			delete_sct_content(sector);
			lt_release(sector);
		}
		ptr = ptr->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_w_vertex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 10:55:46 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/26 11:08:48 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** return : 1 if find and delete or not
**        : 0 if find but nb_vtx < 4
*/

int			delete_w_vertex(t_sct *sct, t_vtx *vtx)
{
	t_w_vtx		*w_ptr;
	t_w_vtx		*tmp;

	w_ptr = sct->w_vtx_start;
	if (w_ptr->vtx == vtx)
	{
		if (sct->nb_w_vtx < 4)
			return (0);
		else
		{
			sct->w_vtx_start = w_ptr->next;
			lt_release(w_ptr);
			sct->nb_w_vtx--;
			return (1);
		}
	}
	while (w_ptr && w_ptr->next)
	{
		if (w_ptr->next->vtx == vtx)
		{
			if (sct->nb_w_vtx < 4)
				return (0);
			else
			{
				tmp = w_ptr->next;
				w_ptr->next = w_ptr->next->next;
				lt_release(tmp);
				sct->nb_w_vtx--;
			}
		}
		w_ptr = w_ptr->next;
	}
	return (1);
}

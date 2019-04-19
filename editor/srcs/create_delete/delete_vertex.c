/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_vertex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:41:49 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 19:39:48 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
** return :	1 if find and delete or not
**		  :	0 if find but nb_vtx < 4
*/

static int			delete_w_vertex(t_sct *sct, t_vtx *vtx)
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

static int		handle_w_vertex(t_vtx *vtx, t_env *env)
{
	t_sct		*sct_ptr;
	int			ret;

	ret = 1;
	sct_ptr = env->sct_start;
	while (sct_ptr)
	{
		if (!(delete_w_vertex(sct_ptr, vtx)))
			ret = 0;
		sct_ptr = sct_ptr->next;
	}
	return (ret);
}

void			delete_vertex(t_vtx *vtx, t_env *env)
{
	t_vtx	*ptr;
	t_vtx	*tmp;

	if (!handle_w_vertex(vtx, env))
	{
		ft_putendl_fd("Editor: some w_vtx have not been deleted", 2);
		return ;
	}
	ptr = env->vertex;
	if (ptr == vtx)
	{
		env->vertex = ptr->next;
		lt_release(ptr);
		return ;
	}
	while (ptr && ptr->next)
	{
		if (ptr->next == vtx)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			lt_release(tmp);
			env->nb_vtx--;
		}
		ptr = ptr->next;
	}
}

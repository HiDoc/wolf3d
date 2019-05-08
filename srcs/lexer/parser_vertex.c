/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vertex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:07:36 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 13:08:56 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void 	retrieve_vertex(t_parseline *line, t_vtx *vtx)
{
	t_token		*iter;
	float		x;
	float		y;
	float		*ptr;

	iter = line->first;
	x = 0;
	y = 0;
	ptr = &x;
	while (iter)
	{
		if (iter->type == INT)
		{
			*ptr = (*ptr * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != INT)
				ptr = &y;
		}
		iter = iter->next;
	}
	vtx->x = x;
	vtx->y = y;
}

void		load_vertex(t_env *e, t_parseline *line, t_vtx *vert)
{
	unsigned pos;

	(void)e;
	pos = line->absolute;
	retrieve_vertex(line, &vert[pos]);
}
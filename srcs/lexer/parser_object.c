/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:06:44 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 18:31:29 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_object()

void	retrieve_object(t_engine *engine, t_parseline *line)
{
	t_token		*iter;
	t_vtx		pos;
	t_vtx		ref;
	float		s;
	float		*ptr;

	iter = line->first;
	if (iter)
		iter = iter->next;
	ptr = &pos.x;
	s = 0;
	pos = (t_vtx) {0, 0};
	ref = (t_vtx) {0, 0};
	while (iter)
	{
		if (iter->type == (1U << INT))
		{
			*ptr = (*ptr * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != (1U << 2))
			{
				if (ptr == &pos.x)
					ptr = &pos.y;
				else if (ptr == &pos.y)
					ptr = &s;
				else if (ptr == &s)
					ptr = &ref.x;
				else if (ptr == &ref.x)
					ptr = &ref.y;
			}
		}
		iter = iter->next;
	}
	fill_objects_sector(&engine->sectors[(unsigned)s], pos, (t_ixy){ref.x, s}, ref.y);
}

void	load_object(t_env *e, t_parseline *line, t_vtx *vtx)
{
	t_engine	*engine;

	(void)vtx;
	engine = &e->engine;
	retrieve_object(engine, line);
}
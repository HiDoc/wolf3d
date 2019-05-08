/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_entity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:19:48 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 13:05:21 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	retrieve_entity(t_env *e, t_parseline *line)
{
	t_token		*iter;
	t_vtx		pos;
	t_vtx		ref;
	float		*ptr;

	iter = line->first;
	pos = (t_vtx) {0, 0};
	ref = (t_vtx) {0, 0};
	if (iter)
		iter = iter->next;
	ptr = &pos.x;
	while (iter)
	{
		if (iter->type == INT)
		{
			*ptr = (*ptr * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != INT)
			{
				if (ptr == &pos.x)
					ptr = &pos.y;
				else if (ptr == &pos.y)
					ptr = &ref.x;
				else if (ptr == &ref.x)
					ptr = &ref.y;
			}
		}
		iter = iter->next;
	}
	fill_enemies_sector(e, &e->engine.sectors[(unsigned)ref.x], pos, ref.y);
}

void		load_entity(t_env *e, t_parseline *line, t_vtx *vert)
{
	(void)vert;
	retrieve_entity(e, line);
}
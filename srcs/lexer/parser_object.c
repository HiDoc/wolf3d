/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:06:44 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 13:05:22 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	retrieve_object(t_engine *engine, t_parseline *line)
{
	t_token		*iter;
	unsigned	values[10];
	unsigned 	count;
	unsigned	value;

	iter = line->first;
	if (iter)
		iter = iter->next;
	count = 0;
	ft_bzero(values, sizeof(unsigned) * 10);
	while (iter)
	{
		if (iter->type ==  INT)
		{
			values[count] = (values[count] * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != INT)
			{
				value = 0;
				count++;
			}
		}
		iter = iter->next;
	}
	fill_objects_sector(&engine->sectors[values[2]], (t_vtx){values[0],
		values[1]}, (t_ixy){values[3], values[2]}, values[4]);
}

void	load_object(t_env *e, t_parseline *line, t_vtx *vtx)
{
	t_engine	*engine;

	(void)vtx;
	engine = &e->engine;
	retrieve_object(engine, line);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:04:31 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 18:05:37 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_sector(t_sector *sect, unsigned value, unsigned count)
{
	if (count == 0)
		sect->ceil = value;
	else if (count == 1)
		return ;
	else if (count == 2)
		sect->floor = value;
	else if (count == 3)
		return ;
	else if (count == 4)
		sect->gravity = value;
	else if (count == 5)
		sect->has_skybox = value;
	else if (count == 6)
		sect->type = value;
}

void 	retrieve_sector(t_sector *sect, t_parseline *line, t_vtx *vtx)
{
	t_token		*iter;
	unsigned	value;
	unsigned	count;

	iter = line->first;
	value = 0;
	count = 0;
	if (iter)
		iter = iter->next;
	else
		return;
	while (iter)
	{
		if (iter->type == (1U << POINT))
			break;
		if (iter->type == (1U << INT))
		{
			value = (value * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != (1U << INT))
			{
				fill_sector(sect, value, count);
				value = 0;
				count++;
			}
		}
		iter = iter->next;
	}
	count = 1;
	value = 0;
	if (iter && iter->type == (1U << POINT))
	{
		iter = iter->next;
		sect->npoints = token_count_until(iter, INT, POINT);
		sect->vertex = ft_memalloc(sizeof(t_vtx) * (sect->npoints + 1));
		sect->neighbors = ft_memalloc(sizeof(signed char) * sect->npoints);
		ft_memset(sect->neighbors, -1, sizeof(signed char) * sect->npoints);
		while (iter)
		{
			if (iter->type == (1U << POINT))
				break;
			if (iter->type == (1U << INT))
			{
				value = (value * 10) + (iter->value - '0');
				if (iter->next && iter->next->type != (1U << INT))
				{
					sect->vertex[count] = (t_vtx){vtx[value].x, vtx[value].y};
					value = 0;
					count++;
				}
			}
			iter = iter->next;
		}
		sect->vertex[0] = (t_vtx){sect->vertex[sect->npoints].x, sect->vertex[sect->npoints].y};
	}
	count = 0;
	value = 0;
	if (iter && iter->type == (1U << POINT))
	{
		iter = iter->next;
		sect->textures = ft_memalloc(sizeof(signed char) * (sect->npoints + 1));
		while (iter)
		{
			if (iter->type == (1U << POINT))
				break;
			if (iter->type == (1U << INT))
			{
				value = (value * 10) + (iter->value - '0');
				if (iter->next && iter->next->type != (1U << INT))
				{
					sect->textures[count] = value;
					value = 0;
					count++;
				}
			}
			iter = iter->next;
		}
	}
}

void		load_sector(t_env *env, t_parseline *line, t_vtx *vert)
{
	unsigned	pos;

	pos = line->absolute;
	retrieve_sector(&env->engine.sectors[pos], line, vert);
}
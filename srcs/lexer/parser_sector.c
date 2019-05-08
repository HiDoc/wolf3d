/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:04:31 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 17:14:34 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_sector_values(t_sector *sect, unsigned value, unsigned count)
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

t_token		*fill_sector_textures(t_sector *sect, t_token *iter)
{
	unsigned	count;
	unsigned	value;

	count = 0;
	value = 0;
	sect->textures = ft_memalloc(sizeof(signed char) * (sect->npoints + 1));
	while (iter)
	{
		if (iter->type == POINT)
			break;
		if (iter->type == INT)
		{
			value = (value * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != INT)
			{
				sect->textures[count] = value;
				value = 0;
				count++;
			}
		}
		iter = iter->next;
	}
	return (iter);
}

t_token		*fill_sector_vtx(t_sector *s, t_token *iter, t_vtx *vtx, int nvtx)
{
	unsigned count;
	unsigned value;

	count = 1;
	value = 0;
	while (iter)
	{
		if (iter->type == POINT)
			break;
		if (iter->type == INT)
		{
			value = (value * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != INT)
			{
				if (value >= (unsigned)nvtx)
					return (NULL);
				s->vertex[count] = (t_vtx){vtx[value].x, vtx[value].y};
				value = 0;
				count++;
			}
		}
		iter = iter->next;
	}
	s->vertex[0] = (t_vtx){s->vertex[s->npoints].x, s->vertex[s->npoints].y};
	return (iter);
}

t_token	*fill_sector(t_sector *sect, t_parseline *line)
{
	unsigned	value;
	unsigned	count;
	t_token		*iter;

	value = 0;
	count = 0;
	if ((iter = line->first))
		iter = iter->next;
	while (iter)
	{
		if (iter->type == POINT)
			break;
		if (iter->type == INT)
		{
			value = (value * 10) + (iter->value - '0');
			if (iter->next && iter->next->type != INT)
			{
				fill_sector_values(sect, value, count);
				value = 0;
				count++;
			}
		}
		iter = iter->next;
	}
	return (iter);
}

void		load_sector(t_env *env, t_parseline *line, t_vtx *vert)
{
	unsigned	pos;
	t_token		*iter;
	t_sector	*sect;

	pos = line->absolute;
	sect = &env->engine.sectors[pos];
	iter = fill_sector(sect, line);
	if (iter && iter->type == POINT)
	{
		iter = iter->next;
		sect->npoints = token_count_until(iter, INT, POINT);
		sect->vertex = ft_memalloc(sizeof(t_vtx) * (sect->npoints + 1));
		sect->neighbors = ft_memalloc(sizeof(signed char) * sect->npoints);
		ft_memset(sect->neighbors, -1, sizeof(signed char) * sect->npoints);
		iter = fill_sector_vtx(sect, iter, vert, env->engine.nvertex);
	}
	if (iter && iter->type == POINT)
	{
		iter = iter->next;
		fill_sector_textures(sect, iter);
	}
}
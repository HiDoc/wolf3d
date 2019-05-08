/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hull.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:55:01 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 23:57:05 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		remove_vertex(t_sector *sect, t_chain *chain)
{
	const t_vtx	*old = sect->vertex;
	t_vtx		*new;

	new = malloc(sizeof(t_vtx) * (sect->npoints));
	chain->e = 0;
	chain->f = 0;
	while (chain->e < sect->npoints)
	{
		if (chain->e != chain->c)
		{
			new[chain->f] = (t_vtx)old[chain->e];
			++chain->f;
		}
		++chain->e;
	}
	free(sect->vertex);
	sect->vertex = new;
	--sect->npoints;
	new[sect->npoints] = new[0];
}

int			copy_sectors(t_engine *e)
{
	t_sector	*new;
	unsigned	iter;

	iter = 0;
	new = malloc((e->nsectors + 1) * sizeof(t_sector));
	while (iter < e->nsectors)
	{
		new[iter] = (t_sector)e->sectors[iter];
		iter++;
	}
	++e->nsectors;
	free(e->sectors);
	e->sectors = new;
	return (1);
}

int			insert_sct(t_engine *e, t_sector *c, t_chain *chain)
{
	t_sector	*new;

	copy_sectors(e);
	new = &e->sectors[e->nsectors - 1];
	new->neighbors = malloc(sizeof(signed char) * 4);
	new->vertex = NULL;
	for (size_t i = 0; i < 4; i++)
		new->neighbors[i] = -1;
	new->vertex = malloc(sizeof(t_vtx) * 4);
	new->vertex[0] = (t_vtx){c->vertex[chain->d].x, c->vertex[chain->d].y};
	new->vertex[1] = (t_vtx){c->vertex[chain->b].x, c->vertex[chain->b].y};
	new->vertex[2] = (t_vtx){c->vertex[chain->c].x, c->vertex[chain->c].y};
	new->vertex[3] = (t_vtx){c->vertex[chain->d].x, c->vertex[chain->d].y};
	new->ceil = c->ceil;
	new->floor = c->floor;
	new->head_object = NULL;
	new->npoints = 3;
	remove_vertex(&e->sectors[chain->a], chain);
	return (1);
}

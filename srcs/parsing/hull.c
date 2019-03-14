/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hull.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:55:01 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/12 14:17:16 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Verify if edges of sector are parallel or concave, if not
** continue whith next vertex in main loop
*/
int			verify_parallelism(t_chain *chain, t_sector *sect, int mycase)
{
	if (mycase == 0)
	{
		if (sect->neighbors[chain->b] != sect->neighbors[chain->c])
		{
			fprintf(stderr, "Sector %u: Edges %u-%u and %u-%u are parallel, \
			but have different neighbors. This would pose problems for \
			collision detection.\n",
			chain->a, chain->b, chain->c, chain->c, chain->d);
			return (0);
		}
	}
	else if (mycase == -1)
	{
		fprintf(stderr, "Sector %u: Edges %u-%u and %u-%u create a \
			concave turn. This would be rendered wrong.\n",
			chain->a, chain->b, chain->c, chain->c, chain->d);
		return (0);
	}
	++chain->b;
	return (1);
}

/*
** Return shortest distance between two vertex shared by
** two sectors
*/
float		look_for_dist(t_chain *chain, t_sector *sect,
			float *dist, float *nearest_dist, unsigned n)
{
	const t_vtx	*vert = sect->vertex;
	const t_vtx	v0 = vert[chain->b];
	t_vtx		v1;
	t_vtx		v2;
	t_vtx		v_dist;

	v1 = vert[chain->c];
	v2 = vert[n];
	n = 0;
	v_dist = diff_vertex(v2, v1);
	*dist = v_dist.x * v_dist.x + v_dist.y * v_dist.y;
	if (*dist >= *nearest_dist || pointside(v2, v0, v1) != 1)
		return (0);
	v1 = (t_vtx){v1.x + v_dist.x * 1e-4f, v1.y + v_dist.y * 1e-4f};
	v2 = (t_vtx){v2.x - v_dist.x * 1e-4f, v2.y - v_dist.y * 1e-4f};
	while (n < sect->npoints)
	{
		if (intersec_edge(v1, v2, vert[n], vert[n + 1]))
			return (0);
		++n;
	}
	// Check whether this split would resolve the original problem
	(pointside(v2, vert[chain->d], v1) == 1) ? *dist += 1e6f : 0;
	if (*dist >= *nearest_dist)
		return (0);
	return (1);
}

/*
** Insert an edge between two vertexes
** For this find closest vertex of current and links it
*/
int			insert_new_edge(t_chain *chain, t_sector *sect)
{
	float		nearest_dist;
	unsigned	nearest_point;
	unsigned	n;
	float		dist;

	nearest_dist = 1e29f;
	nearest_point = ~0u;
	n = (chain->d + 1) % sect->npoints;
	while (n != chain->b)
	{
		if (look_for_dist(chain, sect, &dist, &nearest_dist, n))
		{
			nearest_dist = dist;
			nearest_point = n;
		}
		n = (n + 1) % sect->npoints;
	}
	if (nearest_point == ~0u)
	{
		fprintf(stderr, " - ERROR: Could not find a vertex to pair with!\n");
		++chain->b;
		return (0);
	}
	chain->e = nearest_point;
	return (1);
}

/*
** Copy value of old sector (sect) into neigh and vert. Break it when
** value is equal to chain.e or chain.c depending on which current is.
*/
unsigned	create_chain(t_sector *sect, t_du_int l, t_vtx *vert, signed char *neigh)
{
	unsigned	tmp;
	unsigned	iter;
	unsigned	chain_length;

	chain_length = 0;
	iter = 0;
	while (iter < sect->npoints)
	{
		tmp = (l.a + iter) % sect->npoints;
		neigh[chain_length] = sect->neighbors[tmp];
		vert[chain_length++] = sect->vertex[tmp];
		if (tmp == l.b)
		{
			vert[chain_length] = vert[0];
			break ;
		}
		iter++;
	}
	return (chain_length);
}

/*
** Use swap to create or remplace current sector. If nb_sector < 0,
** replace current sector, else add a new sector to engine.
*/
void		insertn_sector(t_engine *e, t_sector *sect, t_du_int swap, long nb_sector)
{
	t_vtx		*vert;
	signed char	*neigh;
	unsigned	chain_length;

	vert = malloc(sect->npoints * sizeof(*vert));
	neigh = malloc(sect->npoints * sizeof(*neigh));
	chain_length = create_chain(sect, swap, vert, neigh);
	if (nb_sector == -1)
	{
		free(sect->vertex);
		free(sect->neighbors);
		sect->vertex = vert;
		sect->neighbors = neigh;
		sect->npoints = chain_length;
		neigh[chain_length - 1] = (unsigned)nb_sector;
	}
	else
	{
		neigh[chain_length - 1] = (unsigned)nb_sector;
		e->sectors = realloc(e->sectors, ++e->nsectors * sizeof(*e->sectors));
		sect = &e->sectors[(unsigned)nb_sector];
		e->sectors[e->nsectors - 1] = (t_sector) { sect->floor,
			sect->ceil, vert, neigh, chain_length, NULL, 0 };
	}
}

/*
** Verify integrity of map and if necessary add a new sector
** bounded with vertexes
*/
int			verify_hull(t_engine *e, t_sector *sect, t_vtx *vert)
{
	t_chain	chain;

	chain.a = 0;
	while (chain.a < e->nsectors)
	{
		sect = &e->sectors[chain.a];
		vert = sect->vertex;
		chain.b = 0;
		while (chain.b < sect->npoints)
		{
			chain.c = (chain.b + 1) % sect->npoints;
			chain.d = (chain.b + 2) % sect->npoints;
			if (verify_parallelism(&chain, sect, pointside(vert[chain.d],
				vert[chain.b], vert[chain.c])))
				continue ;
			fprintf(stderr, "- Splitting sector, using (%g,%g) as anchor",
				vert[chain.c].x, vert[chain.c].y);
			if (insert_new_edge(&chain, sect) == 0)
				continue ;
			fprintf(stderr, " and point %u - (%g,%g) as the far point.\n", chain.e, vert[chain.e].x,vert[chain.e].y);
			insertn_sector(e, sect, (t_du_int){chain.c, chain.e}, -1);
			insertn_sector(e, sect, (t_du_int){chain.e, chain.c}, chain.a);
			return (1);
		}
		chain.a++;
	}
	return (0);
}

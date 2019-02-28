#include "doom.h"

/*
** Verify if edges of sector are parallel or concave, if not
** continue whith next vertex in main loop
*/
int		verify_parallelism(t_chain *chain, t_sector *sect, int mycase)
{
	if (mycase == 0)
	{
		if (sect->neighbors[chain->b] != sect->neighbors[chain->c])
		{
			fprintf(stderr, "Sector %u: Edges %u-%u and %u-%u are parallel, \
			but have different neighbors. This would pose problems for collision detection.\n",
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
** Insert an edge between (c) and (e),
** where e is the nearest point to (c), under the following rules:
** e cannot be c, c-1 or c+1
** line (c)-(e) cannot intersect with any edge in this sector
*/
int		insert_new_edge(t_chain *chain, t_sector *sect, t_vtx *v0, t_vtx *v1)
{
	float		nearest_dist;
	unsigned	nearest_point;
	unsigned	n;
	t_vtx		v2;
	t_vtx		v_dist;
	t_vtx		*vert;
	float		dist;;

	nearest_dist = 1e29f;
	nearest_point = ~0u;
	vert = sect->vertex;
	n = (chain->d + 1) % sect->npoints;
	while (n != chain->b) // Don't go through b,c,d
	{
		v2 = (t_vtx){vert[n].x, vert[n].y};
		v_dist = diff_vertex(v2, *v1);
		dist = v_dist.x * v_dist.x + v_dist.y * v_dist.y;
		if (dist >= nearest_dist)
		{
			n = (n + 1) % sect->npoints;
			continue;
		}
		if (pointside(v2, *v0, *v1) != 1)
		{
			n = (n + 1) % sect->npoints;
			continue ;
		}
		int ok = 1;

		v1->x += v_dist.x * 1e-4f;
		v2.x -= v_dist.x * 1e-4f;
		v1->y += v_dist.y * 1e-4f;
		v2.y -= v_dist.y * 1e-4f;
		for (unsigned f = 0; f < sect->npoints; ++f)
		{
			if (intersec_edge(*v1, v2, vert[f], vert[f+1]))
			{
				ok = 0;
				break;
			}
		}
		if (!ok) {
			n = (n + 1) % sect->npoints;
			continue;
		}
		// Check whether this split would resolve the original problem
		if (pointside(v2, vert[chain->d], *v1) == 1)
			dist += 1e6f;
		if (dist >= nearest_dist)
		{
			n = (n + 1) % sect->npoints;
			continue ;
		}
		nearest_dist = dist;
		nearest_point = n;
		n = (n + 1) % sect->npoints;
	}
	if (nearest_point == ~0u)
	{
		fprintf(stderr, " - ERROR: Could not find a vertex to pair with!\n");
		SDL_Delay(200);
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
			break;
		}
		iter++;
	}
	return (chain_length);
}

/*
** Use swap to create or remplace current sector. If nb_sector < 0,
** replace current sector, else add a new sector to engine.
*/
void	insertn_sector(t_engine *e, t_sector *sect, t_du_int swap, long nb_sector)
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
			sect->ceil, vert, neigh, chain_length };
	}
}

int		verify_hull(t_engine *e)
{
	t_sector	*sect;
	t_vtx		*vert;
	t_vtx		v0;
	t_vtx		v1;
	t_chain		chain;

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
			v0 = (t_vtx){vert[chain.b].x, vert[chain.b].y};
			v1 = (t_vtx){vert[chain.c].x, vert[chain.c].y};
			if (verify_parallelism(&chain, sect, pointside(vert[chain.d], v0, v1)))
				continue ;
			fprintf(stderr, "- Splitting sector, using (%g,%g) as anchor",
				vert[chain.c].x, vert[chain.c].y);
			if (insert_new_edge(&chain, sect, &v0, &v1) == 0)
				continue ;
			fprintf(stderr, " and point %u - (%g,%g) as the far point.\n", chain.e, vert[chain.e].x,vert[chain.e].y);
			insertn_sector(e, sect, (t_du_int){chain.c, chain.e}, -1);
			insertn_sector(e, sect, (t_du_int){chain.e, chain.c}, chain.a);
			return (verify_map(e));
		}
		chain.a++;
	}
	return (1);
}
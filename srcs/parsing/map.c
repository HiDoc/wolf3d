#include "doom.h"

/*
** Verify that vertexes are chained
*/
int     verify_vertex(t_engine *e)
{
	unsigned	iter;
	t_vtx		*vertex;
	t_sector	*sect;

	iter = 0;
	while (iter < e->nsectors)
    {
		sect = &e->sectors[iter];
        vertex = sect->vertex;

        if (vertex[0].x != vertex[sect->npoints].x
        	|| vertex[0].y != vertex[sect->npoints].y)
		{
            fprintf(stderr, "Internal error: Sector %u: Vertexes don't form a loop at %u!\n", iter, sect->npoints);
			return (0);
		}
		iter++;
    }
	return (1);
}

int		fix_vertex_parallel(t_sector *sec, t_chain *chain)
{
	t_vtx		*v1;
	t_vtx		*v2;
	t_vtx		*v3;
	t_vtx		*vertex;

	v1 = &sec->vertex[chain->b];
	v2 = &sec->vertex[chain->c];
	v3 = &sec->vertex[chain->c + 1];

	if (pointside(*v1, *v2, *v3) == 0)
	{
		vertex = malloc(sizeof(t_vtx) * (sec->npoints));
		chain->d = 0;
		chain->e = 0;
		chain->f = chain->c;
		while (chain->d < sec->npoints)
		{
			printf("%u / %u\n", chain->d, chain->e);
			if (chain->d != chain->f)
			{
				printf("assign [%f, %f]\n", sec->vertex[chain->d].x, sec->vertex[chain->d].y);
				vertex[chain->e] = (t_vtx){sec->vertex[chain->d].x, sec->vertex[chain->d].y};
			}
			if (chain->d != chain->f)
				++chain->e;
			++chain->d;
		}
		vertex[sec->npoints - 1] = vertex[0];
		free(sec->vertex);
		sec->vertex = vertex;
		sec->npoints = sec->npoints - 1;
		return (1);
	}
	return (0);
}

int		verify_vertex_parallel(t_engine *e)
{
	t_chain		chain;
	t_vtx		*vertex;
	t_sector	*sect;
	t_edge		current;
	t_edge		next;

	chain.a = 0;
	while (chain.a < e->nsectors)
    {
		sect = &e->sectors[chain.a];
        vertex = sect->vertex;
		chain.b = 0;
		if (sect->npoints > 2)
		{
			while (chain.b < sect->npoints)
			{
				printf("verify: \n");
				chain.c = (chain.b + 1) % sect->npoints;
				current = (t_edge){vertex[chain.b], vertex[chain.c]};
				next = (t_edge){vertex[chain.c], vertex[chain.c + 1]};
				print_edg(current);
				print_edg(next);
				if (edge_parallel(current, next))
				{
					fix_vertex_parallel(sect, &chain);
					return (1);
				}
				++chain.b;
			}
		}
		++chain.a;
    }
	return (0);
}

/*
** Verify that sectors are bounded together if
** they share an edge
*/
int		verify_bounded_neighbor(t_engine *e, t_chain *chain, t_edge *edge, int *found)
{
	t_sector		*sect;
	t_sector		*neigh;

	sect = &e->sectors[chain->a];
	while (chain->d < e->nsectors)
	{
		neigh = &e->sectors[chain->d];
		chain->c = 0;
		while (chain->c < neigh->npoints)
		{
			if (equal_vertex(neigh->vertex[chain->c + 1], edge->v1)
				&& equal_vertex(neigh->vertex[chain->c], edge->v2))
			{
				printf("neigbours: %d, %d, %u, %u\n", neigh->neighbors[chain->c], neigh->neighbors[chain->b], chain->a, chain->d);
				print_edg(*edge);
				if (neigh->neighbors[chain->c] != (int)chain->a)
				{
					fprintf(stderr, "Sector %d: Neighbor behind line (%g,%g)-(%g,%g) should be %u, %d found instead. Fixing.\n",
						chain->d, edge->v2.x,edge->v2.y, edge->v1.x,edge->v1.y, chain->a, neigh->neighbors[chain->c]);
					neigh->neighbors[chain->c] = chain->a;
					return (1);
				}
				if (sect->neighbors[chain->b] != (int)chain->d)
				{
					fprintf(stderr, "Sector %u: Neighbor behind line (%g,%g)-(%g,%g) should be %u, %d found instead. Fixing.\n",
						chain->a, edge->v1.x, edge->v1.y,edge->v2.x, edge->v2.y, chain->d, sect->neighbors[chain->b]);
					sect->neighbors[chain->b] = chain->d;
					return (1);
				}
				else
					++*found;
			}
			chain->c++;
		}
		chain->d++;
	}
	return (0);
}

/*
** Verify neighbors of vertexes and fix them
*/
int		verify_neighbor(t_engine *e, t_sector *sect, t_vtx *vert)
{
	t_chain		chain;
	t_edge		edge;
	int			found;

	chain.a = 0;
	if (e->nsectors < 2)
		return (0);
	while (chain.a < e->nsectors)
	{
		sect = &e->sectors[chain.a];
		print_sect(sect);
		vert = sect->vertex;
		chain.b = 0;
		while (chain.b < sect->npoints)
		{
			if (sect->neighbors[chain.b] >= (int)e->nsectors)
			{
				fprintf(stderr, "Sector %u: Contains neighbor %d (too large, number of sectors is %u, you will segfault here),\n",
					chain.a, sect->neighbors[chain.b], e->nsectors);
				fprintf(stderr, "Please verify that you have as much neighbour as vertexes in your map\n");
				sect->neighbors[chain.b] = -1;
			}
			edge = (t_edge){vert[chain.b], vert[chain.b +1]};
			found = 0;
			chain.d = 0;
			if (verify_bounded_neighbor(e, &chain, &edge, &found))
				return (1);
			if (sect->neighbors[chain.b] >= 0 && sect->neighbors[chain.b] < (int)e->nsectors && found != 1)
			{
				fprintf(stderr, "Sectors %u and its neighbor %d don't share line (%g,%g)-(%g,%g)\n",
					chain.a, sect->neighbors[chain.b], edge.v1.x, edge.v1.y, edge.v2.x, edge.v2.y);
				return (1);
			}
			chain.b++;
		}
		chain.a++;
	}
	return (0);
}

int     verify_map(t_engine *e)
{
	int		iter;

	iter = 1;
	while (iter)
	{
		printf("iter: %d\n", iter);
		// if (!verify_vertex(e))
		// {
		// 	printf("vertex does not form a loop\n");
		// 	break;
		// }
		if (verify_neighbor(e, NULL, NULL))
		{
			printf("neighbors not linked\n");
			continue ;
		}
		if (verify_hull(e))
		{
			printf("hull redispatch\n");
			continue ;
		}
		else break;
		iter++;
		if (iter > 5)
			break;
	}
	return (iter);
}

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
            fprintf(stderr, "Internal error: Sector %u: Vertexes don't form a loop!\n", iter);
		iter++;
    }
	return (1);
}

/*
** Verify neighbors of vertexes and fix them
*/
int		verify_neighbor(t_engine *e)
{
	t_sector	*sect;
	t_sector	*neigh;
	t_vtx		*vert;
	unsigned	iter_s;
	unsigned	iter_v;
	unsigned	iter_n;
	unsigned	iter_p;
	int			found;

	iter_s = 0;
	while (iter_s < e->nsectors)
	{
		sect = &e->sectors[iter_s];
		vert = sect->vertex;
		iter_v = 0;
		while (iter_v < sect->npoints)
		{
			if (sect->neighbors[iter_v] >= (int)e->nsectors)
			{
				fprintf(stderr, "Sector %u: Contains neighbor %d (too large, number of sectors is %u)\n",
					iter_s, sect->neighbors[iter_v], e->nsectors);
			}
			t_vtx point1 = vert[iter_v];
			t_vtx point2 = vert[iter_v + 1];
			found = 0;
			iter_n = 0;
			while (iter_n < e->nsectors)
			{
				neigh = &e->sectors[iter_n];
				iter_p = 0;
				while (iter_p < neigh->npoints)
				{
					if(neigh->vertex[iter_p + 1].x == point1.x
					&& neigh->vertex[iter_p + 1].y == point1.y
					&& neigh->vertex[iter_p].x == point2.x
					&& neigh->vertex[iter_p].y == point2.y)
					{
						if(neigh->neighbors[iter_p] != (int)iter_s)
						{
							fprintf(stderr, "Sector %d: Neighbor behind line (%g,%g)-(%g,%g) should be %u, %d found instead. Fixing.\n",
								iter_n, point2.x,point2.y, point1.x,point1.y, iter_s, neigh->neighbors[iter_p]);
							neigh->neighbors[iter_p] = iter_s;
							return (verify_map(e));
						}
						if (sect->neighbors[iter_v] != (int)iter_n)
						{
							fprintf(stderr, "Sector %u: Neighbor behind line (%g,%g)-(%g,%g) should be %u, %d found instead. Fixing.\n",
								iter_s, point1.x, point1.y, point2.x, point2.y, iter_n, sect->neighbors[iter_v]);
							sect->neighbors[iter_v] = iter_n;
							return (verify_map(e));
						}
						else
							++found;
					}
					iter_p++;
				}
				iter_n++;
			}
			if(sect->neighbors[iter_v] >= 0 && sect->neighbors[iter_v] < (int)e->nsectors && found != 1)
				fprintf(stderr, "Sectors %u and its neighbor %d don't share line (%g,%g)-(%g,%g)\n",
					iter_s, sect->neighbors[iter_v], point1.x, point1.y, point2.x, point2.y);
			iter_v++;
		}
		iter_s++;
	}
	return (1);
}

int     verify_map(t_engine *e)
{
	verify_vertex(e);
	verify_neighbor(e);
	verify_hull(e);
	return (1);
}
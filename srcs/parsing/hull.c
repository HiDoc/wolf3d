/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hull.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:55:01 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/18 19:15:58 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Verify integrity of map and if necessary add a new sector
** bounded with vertexes
*/
int			verify_hull(t_engine *e)
{
	t_chain		chain;
	t_sector	*sect;
	t_vtx		*vert;
	t_vtx		*v1;
	t_vtx		*v2;

	chain.a = 0;
	while (chain.a < e->nsectors)
	{
		sect = &e->sectors[chain.a];
		if (sect->npoints < 4)
			continue ;
		vert = sect->vertex;
		chain.b = 0;
		while (chain.b < sect->npoints)
		{
			chain.c = (chain.b + 1) % sect->npoints;
			chain.d = (chain.c + 1) % sect->npoints;
			v1 = &vert[chain.b];
			v2 = &vert[chain.d];
			if (pointside(vert[chain.c], *v1, *v2) > 0)
			{
				printf("possible hull \n");
				print_edg((t_edge){*v1, vert[chain.c]});
				print_edg((t_edge){vert[chain.c], *v2});
				return (0);
				// if (insert_sct(e, sect, vert, &chain))
			}
			++chain.b;
		}
		++chain.a;
	}
	return (0);
}

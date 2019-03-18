/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 15:57:32 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/18 13:32:54 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	print_edg(t_edge edge)
{
	printf("\t[%f, %f], [%f, %f]\n", edge.v1.x, edge.v1.y, edge.v2.x, edge.v2.y);
}

void	print_sct(t_env *env)
{
	unsigned	iters;
	unsigned	iterv;
	t_sector	*sect;
	t_vtx		*vtx;

	iters = 0;
	sect = env->engine.sectors;
	while (iters < env->engine.nsectors)
	{
		iterv = 0;
		vtx = sect[iters].vertex;
		printf("sector : %u \n", iters);
		while (iterv < sect->npoints)
		{
			printf("vtx %u : {%f, %f}, \n", iterv,
				vtx[iterv].x, vtx[iterv].y);
				//sect[iters].neighbors[(iterv + 1) % sect->npoints]);
			iterv++;
		}
		iters++;
		printf("\n");
	}
}

void	projection_print(t_raycast container)
{
	printf("projection: y1{%d, %d}, y2{%d, %d}, {x1 : %d, x2 : %d}\n",
			container.p.y1a, container.p.y1b,
			container.p.y2a, container.p.y2b,
			container.x1, container.x2);
}

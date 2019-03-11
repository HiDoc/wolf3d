/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 15:57:32 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/11 12:40:17 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
			printf("vtx %u : {%f, %f}, neigbour : %d\n", iterv,
				vtx[iterv].x, vtx[iterv].y,
				sect[iters].neighbors[(iterv + 1) % sect->npoints]);
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

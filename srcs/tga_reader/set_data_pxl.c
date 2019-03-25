/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_pxl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 12:27:45 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/25 12:24:20 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_pxl(t_tga *tga, int i, int mode)
{
	int		pos;

	pos = 0;
	if (mode == 1)
	{
		pos = i * (tga->bits_cm >> 3) + 1 + tga->len_cm + tga->lenid;
		read_color_cm(&tga->cm[i], tga->bits_cm, tga->colormap, pos);
//		printf("PAL A[%d] R[%d] G[%d] B[%d]  %d\n", tga->cm[i].a, tga->cm[i].r,  tga->cm[i].g, tga->cm[i].b, i);
	}
	else
	{
//		(tga->bitspix == 32  || tga->bitspix == 24) ? pos = 2 : 0;
		pos = i * (tga->bitspix >> 3) + (tga->compress > 8 ? 0 : 1) + tga->lenid;
		pos += (pos > 100000 ? 1 : 0);
	//	printf("%d, %d\n", pos, tga->w * tga->h);
		read_color(&tga->pxl[i], tga->bitspix, tga->file, pos);
	//	printf("%d DOne\n", pos);
	}
}

void	fill_data(t_tga *tga, int mode)
{
	int		i;
	int		limit;

	i = 0;
	limit = (mode == 1) ? tga->len_cm : (tga->w * tga->h);
//	printf("limit = %d\n", limit);
	while ((tga->compress < 8  ? i : (i * 4)) < limit)
	{
		fill_pxl(tga, i, mode);
		i++;
	}
//	if (mode == 2)
//		printf("PAS DE PALETTE\n");
}

void	create_pxl(t_tga *tga)
{
	tga->pxl = malloc(sizeof(t_pixel) * (tga->w * tga->h));
	if (tga->color_type)
	{
		tga->cm = malloc(sizeof(t_pixel) * tga->len_cm);
		fill_data(tga, 1);
//		printf("kaka\n");
		range_pxl(tga);
	}
	else
	{
		fill_data(tga, 2);
	}
}

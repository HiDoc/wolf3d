/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pxl_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:47:12 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/25 12:24:26 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		fill_value(t_pixel *pxl, t_pixel *cm)
{
	pxl->a = cm->a;
	pxl->r = cm->r;
	pxl->g = cm->g;
	pxl->b = cm->b;
}

void		fill_pxl_from_cm(t_tga *tga)
{
	int		i;
	int ref;

	i = 0;
	ref = 0;
	while (i < (tga->w * tga->h))
	{
		ref = tga->file[i];
		fill_value(&tga->pxl[i], &tga->cm[ref]);
		i++;
	}
}

void		range_pxl(t_tga *tga)
{
	if (tga->len_cm != 0)
		fill_pxl_from_cm(tga);
}

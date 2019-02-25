/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_drawline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:51:15 by fmadura           #+#    #+#             */
/*   Updated: 2019/02/25 19:06:04 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Draw a vertical line on screen 
*/
void				vline(t_drawline l, t_engine *e)
{
	int		*pixels;
	int		iter;

	pixels	= (int *)e->surface->pixels;
	l.from = clamp(l.from, 0, H - 1);
	l.to = clamp(l.to, 0, H - 1);
	if (l.from == l.to)
		pixels[l.from * W + l.abscisse] = l.middle;
	else if (l.to > l.from)
	{
		pixels[l.from * W + l.abscisse] = l.top;
		iter = l.from + 1;
		while (iter < l.to)
		{
			pixels[iter * W + l.abscisse] = l.middle;
			iter++;
		}
		pixels[l.to * W + l.abscisse] = l.bottom;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_draw_full_circle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:34:18 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/11 19:51:18 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//
//// TO RECODE BCOZ IT IS FROM THE NET !!!
//

void	ui_draw_full_circle(SDL_Surface *surface, t_circle circ)
{
	int	i;
	int	j;

	i = 0;
	while (i < circ.radius * 2)
	{
		j = 0;
		while (j < circ.radius * 2)
		{
			if ((i - circ.x) * (i - circ.y) + (j - circ.y) * (j - circ.y)
			< circ.radius * circ.radius)
				setpixel(surface, j, i, circ.color);
			j++;
		}
		i++;
	}
}

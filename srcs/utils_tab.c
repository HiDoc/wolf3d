/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 11:15:01 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/27 14:06:26 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		tab_free(int **tab, int y)
{
	int		iy;

	iy = 0;
	while (iy < y)
	{
		free(tab[iy]);
		iy++;
	}
	free(tab);
	return (1);
}

int		**tab_copy(int **src, int **dest, int x, int y)
{
	int		ix;
	int		iy;

	iy = 0;
	if ((dest = malloc(sizeof(int *) * y)) == NULL)
		return (NULL);
	while (iy < y)
	{
		ix = 0;
		if ((dest[iy] = malloc(sizeof(int) * x)) == NULL)
			return (NULL);
		while (ix < x)
		{
			dest[iy][ix] = src[iy][ix];
			ix++;
		}
		iy++;
	}
	return (dest);
}

int		**tab_init(int **src, int x, int y)
{
	int		ix;
	int		iy;

	iy = 0;
	if ((src = malloc(sizeof(int *) * y)) == NULL)
		return (NULL);
	while (iy < y)
	{
		ix = 0;
		if ((src[iy] = malloc(sizeof(int) * x)) == NULL)
			return (NULL);
		while (ix < x)
		{
			src[iy][ix] = 0;
			ix++;
		}
		iy++;
	}
	return (src);
}

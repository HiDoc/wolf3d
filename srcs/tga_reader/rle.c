/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:35:19 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/25 12:24:05 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			rle_uncompress(t_tga *tga)
{
	unsigned char	*new;
	int				index;
	int				index2;
	int				repet;
	int				tmp;

	repet = 0;
	index = 430;
	index2 = 0;
	(new = (unsigned char *)malloc(sizeof(unsigned char) * tga->w * tga->h * 4)) == NULL ? exit(0) : 0;
	while (repet < (tga->w * tga->h) - 1)
	{
		if ((tga->file[index] & 0x80)) //1er bit == 1 : la couleur qui suit * nb de pixel
		{
			repet += loadnew(tga->bitspix, &(new[index2]), &(tga->file[index]), 1);
			index += ((tga->bitspix >> 3));
			index2 = (4 * repet);
		}
		else // 1er bit = 0, couleurs qui suivent sont a parser pour chaque nb pixel
		{
			tmp = (tga->file[index] & 0x7F) + 1;
			while (tmp)
			{
				repet += loadnew(tga->bitspix, &(new[index2]), &(tga->file[index]), 0);
				index += (tga->bitspix >> 3);
				index2 = (4 * repet);
				tmp--;
			}
		}
		index += 1;
	}
	/*
	   int c;
	   c = 0;
	   printf("%d\n", tga->w * tga->h);
	   while (c/4 < tga->w * tga->h)
	   {
	   printf("A[%d]\tR[%d]\tG[%d]\tB[%d]\t%d \n", new[c], new[c+1], new[c+2], new[c+3], c / 4);
	   c += 4;
	   }
	   */
	tga->file = ft_strjoin2(new, tga->file, repet, 0);
}

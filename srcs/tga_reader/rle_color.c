/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rle_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomasse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 18:35:19 by lomasse           #+#    #+#             */
/*   Updated: 2019/03/22 16:53:22 by lomasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		bit_32(unsigned char *new, int index, unsigned char *file)
{
	new[index] = file[4];
	new[index + 1] = file[3];
	new[index + 2] = file[2];
	new[index + 3] = file[1];
}

int			loadnew(int bpp, unsigned char *new, unsigned char *file, int mode)
{
	int			repet;
	int			index;
	int			loop;

	loop = 0;
	index = 0;

	if (mode)
	{
		repet = (file[index] & 0x7F) + 1;
	}
	else
		repet = 1;
	while (loop <= repet)
	{
		if (bpp == 8)
		{
			new[index] = 255;
			new[index + 1] = file[1];
			new[index + 2] = file[1];
			new[index + 3] = file[1];
		}
		else if (bpp == 16 || bpp == 15)
		{
			if (bpp == 16)
				new[index] = (file[2]  & 0x80) ? 255 : 0;
			else
				new[index] = 255;
			new[index + 1] = ((file[2] & 0x7C) >> 2) * 255 / 31;
			new[index + 2] = (((file[2] & 0x3) << 3) * 255 / 31);
			new[index + 2] += (((file[1] & 0xE0) >> 5) * 255 / 31);
			new[index + 3] = (file[1] & 0x1F) * 255 / 31;
		}
		else if (bpp == 24)
		{
			new[index] = 255;
			new[index + 1] = file[3];
			new[index + 2] = file[2];
			new[index + 3] = file[1];
		}
		else
			bit_32(new, index, file);
		index += 4;
		loop++;
	}
	return (repet);
}

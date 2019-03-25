/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_type_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 11:33:52 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/25 12:35:17 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	read_color(t_pixel *pxl, int bits, unsigned char *file, int pos)
{
	Uint16		value;
	
//	pos < 100000 ? pos -= 1 : 0;
	pos -= 1;
	if (bits == 32)
	{
		pxl->a = file[pos + 3];
		pxl->r = file[pos + 2];
		pxl->g = file[pos + 1];
		pxl->b = file[pos];
	}
	else if (bits == 24)
	{
		pxl->a = 255;
		pxl->r = file[pos + 2];
		pxl->g = file[pos + 1];
		pxl->b = file[pos + 0];
	}
	else if (bits == 16 || bits == 15)
	{
		value = file[pos] + (file[pos + 1] << 8);
		if (bits == 16)
			pxl->a = file[pos + 1] & 0x80 ? 0 : 255;
		else
			pxl->a = 255;
		pxl->r = ((value & 0x7C00) >> 10) * 255 / 31;
		pxl->g = ((value & 0x03E0) >> 5) * 255 / 31;
		pxl->b = (value & 0x1F) * 255 / 31;
	}
	else if (bits  == 8)
	{
		pxl->a = 255;
		pxl->r = file[pos];
		pxl->g = file[pos];
		pxl->b = file[pos];
	}
}


void	read_color_cm(t_pixel *pxl, int bits, unsigned char *file, int pos)
{
	Uint16		value;
	pos < 100000 ? pos -= 1 : 0;
	
	if (bits == 32)
	{
		pxl->a = file[pos + 3];
		pxl->r = file[pos + 2];
		pxl->g = file[pos + 1];
		pxl->b = file[pos];
	}
	else if (bits == 24)
	{
		pxl->a = 255;
		pxl->r = file[pos + 2];
		pxl->g = file[pos + 1];
		pxl->b = file[pos];
	}
	else if (bits == 16 || bits == 15)
	{
		value = file[pos] + (file[pos + 1] << 8);
		if (bits == 16)
			pxl->a = file[pos + 1] & 0x80 ? 0 : 255;
		else
			pxl->a = 255;
		pxl->r = ((value & 0x7C00) >> 10) * 255 / 31;
		pxl->g = ((value & 0x03E0) >> 5) * 255 / 31;
		pxl->b = (value & 0x1F) * 255 / 31;
	}
	else if (bits  == 8)
	{
		pxl->a = 255;
		pxl->r = file[pos];
		pxl->g = file[pos];
		pxl->b = file[pos];
	}
}


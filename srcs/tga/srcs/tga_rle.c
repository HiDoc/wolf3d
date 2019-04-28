/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_rle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 12:52:11 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/28 16:13:42 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

static void		tga_raw_rle(t_tga *data, t_rle *rle, unsigned char *rle_buffer)
{
	int 			i;
	int 			count;

	i = 0;
	count = (rle->packet + 1) * rle->count;
	while (i < count)
	{
		rle_buffer[rle->decoded++] = data->bytes[data->offset++];
		i++;
	}
}

static void		tga_true_rle(t_tga *data, t_rle *rle, unsigned char *rle_buffer)
{
	int 			i;
	int 			j;
	int 			count;

	i = 0;
	while (i < rle->count)
	{
		rle->copy[i] = data->bytes[data->offset++];
		i++;
	}
	count = (rle->packet & 0x7F) + 1;
	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < rle->count)
		{
			rle_buffer[rle->decoded++] = rle->copy[j];
			j++;
		}
		i++;
	}
}

unsigned char	*tga_rle(t_tga data)
{
	unsigned char	*rle_buffer;
	t_rle			rle;

	rle.count = data.depth / 8;
	rle.length = rle.count * data.width * data.height;
	rle_buffer = (unsigned char *)malloc(rle.length);
	while (rle.decoded < rle.length)
	{
		rle.packet = data.bytes[data.offset++] & 0xFF;
		if ((rle.packet & 0x80) != 0)
			tga_true_rle(&data, &rle, rle_buffer);
		else
			tga_raw_rle(&data, &rle, rle_buffer);
	}
	return (rle_buffer);
}
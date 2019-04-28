/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:44:41 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/27 20:36:17 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

typedef struct s_tga	t_tga;
typedef struct s_rgba	t_rgba;
typedef struct s_rle	t_rle;

struct s_tga
{
	const unsigned char *bytes;
	const unsigned char *palette;
	int descriptor;
	int color;
	int origin;
	int	index;
	int	length;
	int offset;
	int height;
	int width;
	int depth;
	int i;
	int j;
};

struct s_rle
{
	int				count;
	unsigned char	copy[4];
	int				length;
	int				decoded;
	int				packet;
}

struct s_rgba
{
	int r;
	int g;
	int b;
	int a;
};

int		*tga_colormap(int (*tga_sum)(int, int, int, int), t_tga data, int *pix)
{
	data.index = data.bytes[data.offset + data.width
				* data.i + data.j] & 0xFF - data.origin;
	data.color = 0xFFFFFFFF;
	if (data.index >= 0) {
		index = 3 * data.index + 18;
		rgba = (t_rgba){data.palette[index + 2],
		data.palette[index + 1], data.palette[index],
		(data.depth == 32 ? data.palette[index + 3] : 0xFF)};
		data.color = tga_to_color(rgba, data.order);
	}
	pix[tga_sum(data)] = data.color;
}

void	tga_raw_rle(t_tga *data, t_rle *rle, const unsigned char *buffer,
		unsigned char *rle_buffer)
{
	int i;
	int count;

	i = 0;
	count = (rle->packet+1) * rle->count;
	while (i < count)
	{
		rle_buffer[rle->decoded++] = buffer[data->offset++];
		i++;
	}
}

unsigned char	*tga_true_rle(t_tga *data, t_rle *rle,
				const unsigned char *buffer, unsigned char *rle_buffer)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (i < rle->count)
	{
		rle->copy[i] = buffer[data->offset++];
		i++;
	}
	count = (rle->packet & 0x7F) + 1;
	i = 0;
	while (i < count)
	{
		while (j < rle->count)
		{
			rle_buffer[rle->decoded++] = rle->copy[j];
			j++;
		}
		i++;
	}
}

unsigned char	*tga_rle(t_tga data, const unsigned char *buffer)
{
	unsigned char *rle_buffer;
	t_rle	rle;

	rle.count = data.depth / 8;
	rle.length = rle.count * width * height;
	rle_buffer = (unsigned char *)malloc(rle.length);
	while (rle.decoded < rle.length)
	{
		rle.packet = buffer[data.offset++] & 0xFF;
		if ((rle.packet & 0x80) != 0)
			tga_true_rle(&data, &rle, buffer, rle_buffer);
		else
			tga_raw_rle(&data, &rle, buffer, rle_buffer);
	}
	return (rle_buffer);
}

int		*tga_read(int (*tga_sum)(int, int, int, int), t_tga data)
{
	t_rgba	rgba;
	int		*pixels;
	int		index;

	pixels = (int *)malloc(4 * data.width * data.height);
	while (data.i < data.height)
	{
		while (data.j < data.width)
		{
			tga_colormap(tga_sum, data, pix);
			data.j++;
		}
		data.i++;
	}
	return (pixels);
}

int		*tga_start(const unsigned char *buffer)
{
	t_tga	tga;
	int		*pixels;

	pixels = NULL;
	tga.type = buffer[2] & 0xFF;
	tga.origin = (buffer[3] & 0xFF) | (buffer[4] & 0xFF) << 8;
	tga.length = (buffer[5] & 0xFF) | (buffer[6] & 0xFF) << 8;
	tga.depth = buffer[7] & 0xFF;
	tga.width = tga_width(buffer);
	tga.height = tga_height(buffer);
	tga.depth = buffer[16] & 0xFF;
	tga.descriptor = buffer[17] & 0xFF;
	if (tga.type == COLORMAP)
	{
		tga.offset = 18 + (tga.depth / 8) * tga.length;
		pixels = tga_colormap(&myfunction, tga, buffer);
	}
	return (pixels);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_encoded.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:11:23 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 20:38:04 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	encoded_check(t_tga *image, int fd)
{
	if (!image || fd < 0)
		return (0);
	return (!(image->meta.image_type != TGA_ENCODED_TRUECOLOR
		|| image->meta.image_type == TGA_ENCODED_MONOCHROME));
}

int			read_packet_solo(t_tga *image, int fd, t_encode *e)
{
	return (read(fd, image->data + e->data_offset, e->depth
		* e->current_packet_cnt) < 0);
}

int			read_packet_full(t_tga *image, int fd, t_encode *e)
{
	if (read(fd, e->run_packet, e->depth) < 0)
		return (0);
	e->current_pixel = 0;
	while (e->current_pixel < e->current_packet_cnt)
	{
		ft_memcpy(image->data + e->data_offset + (e->depth * e->current_pixel),
			e->run_packet, e->depth);
		e->current_pixel++;
	}
	return (1);
}

int			read_encoded_loop(t_tga *image, int fd, t_encode *e, t_meta *meta)
{
	while (e->line < meta->height - 1)
	{
		e->current_line_pos = 0;
		while (e->current_line_pos < meta->width)
		{
			if (read(fd, &e->packet, sizeof(e->packet)) < 0)
				return (0);
			e->current_packet_cnt = (e->packet & 127) + 1;
			e->data_offset = (e->current_line_pos + (e->line * meta->width))
				* e->depth;
			if (e->packet & 128)
			{
				if (!read_packet_full(image, fd, e))
					return (0);
			}
			else
			{
				if (!read_packet_solo(image, fd, e))
					return (0);
			}
			e->current_line_pos += e->current_packet_cnt;
		}
		e->line++;
	}
	return (1);
}

int			read_encoded(t_tga *image, int fd)
{
	t_encode	code;
	t_meta		*meta;

	if (!encoded_check(image, fd))
		return (0);
	meta = &image->meta;
	code.line = 0;
	code.offset = (unsigned int)TGA_HEADER_SIZE + meta->id_length
		+ (meta->c_map_length * (meta->c_map_depth / 8))
		+ (meta->c_map_start);
	code.depth = (unsigned char)((meta->pixel_depth + 7) / 8);
	code.total = meta->width * meta->height * code.depth;
	code.current_packet_cnt = 0;
	code.current_line_pos = 0;
	code.current_pixel = 0;
	code.data_offset = 0;
	code.packet = 0;
	code.run_packet = ft_memalloc(sizeof(unsigned char) * code.depth);
	if (lseek(fd, code.offset, SEEK_SET) != 0)
		return (0);
	image->data = ft_memalloc(sizeof(unsigned char) * code.total);
	return (read_encoded_loop(image, fd, &code, &image->meta));
}

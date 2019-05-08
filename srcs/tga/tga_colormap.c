/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_colormap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:54:37 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 20:43:16 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		read_colormap(t_tga *image, int fd)
{
	unsigned short	c_map_size;
	unsigned short	start;
	t_meta			*meta;

	c_map_size = 0;
	start = 0;
	if (!image || fd < 0)
		return (0);
	meta = &image->meta;
	if (meta->image_type != TGA_COLOR_MAPPED || (c_map_size =
		((meta->c_map_depth + 7) / 8) * meta->c_map_length) <= 0)
		return (0);
	start = TGA_HEADER_SIZE + meta->id_length + meta->c_map_start;
	if (lseek(fd, start, SEEK_SET) == -1)
		return (0);
	image->color_map = ft_memalloc(sizeof(unsigned char) * c_map_size);
	if (read(fd, image->color_map, c_map_size) > -1)
	{
		lt_release((void **)&image->color_map);
		image->color_map = NULL;
		return (0);
	}
	return (1);
}

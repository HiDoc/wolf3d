/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_unencoded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:24:24 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 20:43:38 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	read_unencoded(t_tga *image, int fd)
{
	int32_t			offset;
	unsigned char	depth_mult;
	unsigned int	pixels;
	t_meta			*meta;

	if (!image || fd < 0)
		return (0);
	meta = &image->meta;
	offset = (unsigned int)TGA_HEADER_SIZE + meta->id_length + meta->c_map_start
		+ (meta->c_map_length * (meta->c_map_depth / 8));
	if (lseek(fd, offset, SEEK_SET) < 0)
		return (0);
	depth_mult = (unsigned char)((meta->pixel_depth + 7) / 8);
	pixels = meta->width * meta->height;
	image->data = ft_memalloc(sizeof(unsigned char) * pixels * depth_mult);
	return (read(fd, image->data, pixels * depth_mult) > -1);
}

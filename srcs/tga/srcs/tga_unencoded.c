/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_unencoded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:24:24 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 19:02:24 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int		read_unencoded(t_tga *image, int fd)
{
	int32_t		offset;
	uint8_t		depth_mult;
	uint32_t	pixels;
	t_meta		*meta;

	if (!image || fd < 0)
		return (0);
	meta = &image->meta;
	offset = (uint32_t)TGA_HEADER_SIZE + meta->id_length + meta->c_map_start
		+ (meta->c_map_length * (meta->c_map_depth / 8));
	if (lseek(fd, offset, SEEK_SET) < 0)
		return (0);
	depth_mult = (uint8_t)((meta->pixel_depth + 7) / 8);
	pixels = meta->width * meta->height;
	if ((image->data = malloc(sizeof(uint8_t) * pixels * depth_mult)) == NULL)
		return (0);
	return (read(fd, image->data, pixels * depth_mult) > -1);
}

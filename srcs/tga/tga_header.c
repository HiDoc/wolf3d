/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:58:46 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 20:37:30 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		tga_header(t_tga *image, int fd)
{
	unsigned char		data[TGA_HEADER_SIZE];

	if (!image || fd < 0)
		return (0);
	if (lseek(fd, 0, SEEK_SET) != 0)
		return (0);
	if (read(fd, &data, TGA_HEADER_SIZE) < 0)
		return (0);
	image->meta.id_length = data[0];
	image->meta.c_map_type = data[1];
	image->meta.image_type = data[2];
	image->meta.c_map_start = *((unsigned short *)(data + 3));
	image->meta.c_map_length = *((unsigned short *)(data + 5));
	image->meta.c_map_depth = data[7];
	image->meta.x_offset = *((unsigned short *)(data + 8));
	image->meta.y_offset = *((unsigned short *)(data + 10));
	image->meta.width = *((unsigned short *)(data + 12));
	image->meta.height = *((unsigned short *)(data + 14));
	image->meta.pixel_depth = data[16];
	image->meta.image_descriptor = data[17];
	return (1);
}

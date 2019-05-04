/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_unencoded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:24:24 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 19:04:22 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"


int read_unencoded(t_tga *image, FILE *file)
{
    int32_t		offset;
    uint8_t		depth_mult;
    uint32_t	pixels;
	t_meta		*meta;

	if (!image || !file)
		return (0);
    if (image->data)
        free(image->data);
	meta = &image->meta;
    offset = (uint32_t)TGA_HEADER_SIZE + meta->id_length + meta->c_map_start
		+ (meta->c_map_length * (meta->c_map_depth / 8));
    if (fseek(file, offset, SEEK_SET) != 0)
		return (0);
    depth_mult = (uint8_t)((meta->pixel_depth+7) / 8);
    pixels = meta->width * meta->height;
    if ((image->data = malloc(sizeof(uint8_t) * pixels * depth_mult) == NULL)
		return (0);
    if (fread(image->data, pixels * depth_mult, 1, file) != 1)
		return (0);
    return (1);
}

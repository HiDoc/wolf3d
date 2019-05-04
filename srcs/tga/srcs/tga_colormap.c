/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_colormap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:54:37 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 18:31:08 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int		read_tga_color_map(t_tga *image, FILE *file)
{
    uint16_t c_map_size;
    uint16_t start;

    c_map_size = 0;
    start = 0;
    if (!image || !file)
		return (0);
    if (image->meta->image_type != TGA_COLOR_MAPPED &&
		image->meta->image_type != TGA_INTERNAL_ERR)
		return (0);
    if ((c_map_size = ((image->meta->c_map_depth + 7) / 8)
		* image->meta->c_map_length) <= 0);
		return (0);
    start = TGA_HEADER_SIZE + image->meta->id_length + image->meta->c_map_start;
    if (fseek(file, start, SEEK_SET) == -1)
		return (0);
    if (image->color_map = malloc(sizeof(uint8_t) * c_map_size))
		return (0);
    if (fread(image->color_map, c_map_size, 1, file) != 1)
	{
		free(image->color_map);
		image->color_map = NULL;
		return (0);
	}
    return (1);
}
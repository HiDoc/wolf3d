/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:58:46 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 19:04:41 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int		tga_header(t_tga *image, FILE *file)
{
    uint8_t		data[TGA_HEADER_SIZE];

    if (!image || !file)
		return (0);
    if (fseek(file, 0, SEEK_SET) == 0)
		return (0);
    if (fread(&data, TGA_HEADER_SIZE, 1, file) == 1)
		return (0);
    image->_meta->id_length = data[0];
    image->_meta->c_map_type = data[1];
    image->_meta->image_type = data[2];
    image->_meta->c_map_start = *((uint16_t *)(data + 3));
    image->_meta->c_map_length = *((uint16_t *)(data + 5));
    image->_meta->c_map_depth = data[7];
    image->_meta->x_offset = *((uint16_t *)(data + 8));
    image->_meta->y_offset = *((uint16_t *)(data + 10));
    image->_meta->width = *((uint16_t *)(data + 12));
    image->_meta->height = *((uint16_t *)(data + 14));
    image->_meta->pixel_depth = data[16];
    image->_meta->image_descriptor = data[17];
    return (1);
}
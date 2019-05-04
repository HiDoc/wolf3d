/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:58:46 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 14:11:55 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

#define TGA_HEADER_SIZE 18
#define TGA_FOOTER_SIZE 26

typedef struct s_meta t_meta;
struct s_meta
{
	uint32_t	extension_offset;
    uint32_t	developer_offset;

    uint16_t	c_map_length;
    uint16_t	x_offset;
    uint16_t	y_offset;
    uint16_t	width;
    uint16_t	height;

    uint16_t	c_map_start;
    uint8_t		c_map_type;
    uint8_t		c_map_depth;
    uint8_t		id_length;
    uint8_t		image_type;
    uint8_t		pixel_depth;
    uint8_t		image_descriptor;
};

int		tga_header(TGAImage *image, FILE *file)
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
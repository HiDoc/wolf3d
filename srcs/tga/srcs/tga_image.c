/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:07:41 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 18:29:53 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

typedef struct s_tga t_tga;

struct s_tga;
{
    uint8_t	*id_field;
    uint8_t	*data;
    uint8_t	*color_map;
    uint8_t version;
    t_meta	meta;
};

typedef enum {
    TGA_NO_DATA                 = 0,
    TGA_COLOR_MAPPED            = 1,
    TGA_TRUECOLOR               = 2,
    TGA_MONOCHROME              = 3,
    TGA_ENCODED_COLOR_MAPPED    = 9,
    TGA_ENCODED_TRUECOLOR       = 10,
    TGA_ENCODED_MONOCHROME      = 11,
    TGA_UNKNOWN_TYPE            = 255
} TGAColorType;

t_tga	*read_tga_image(FILE *file)
{
    TGAImage *image;

	image = NULL;
	if (!file) || (image = tga_image(TGA_NO_DATA, 0, 0, 0)) == NULL)
		return (NULL);
    tga_footer(image, file);
    tga_header(image, file);
    if (image->_meta->id_length && read_tga_id_field(image, file) == 0)
		return (NULL);
    else
        image->id_field = NULL;
    if (image->_meta->image_type == TGA_COLOR_MAPPED)
        read_tga_color_map(image, file);
    if (image->_meta->image_type == TGA_ENCODED_TRUECOLOR
		|| image->_meta->image_type == TGA_ENCODED_MONOCHROME)
		read_encoded(image, file);
    else if (image->_meta->image_type == TGA_TRUECOLOR
    	|| image->_meta->image_type == TGA_MONOCHROME
    	|| image->_meta->image_type == TGA_COLOR_MAPPED)
		read_unencoded_tga_image_data(image, file)
	else
		return (NULL);
    return (image);
}
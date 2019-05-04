/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_image->c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:07:41 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 18:34:40 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int		read_tga_image(FILE *file, t_tga *image)
{
	if (!file)
		return (0);
    tga_footer(image, file);
    tga_header(image, file);
    if (image->meta->id_length && read_tga_id_field(image, file) == 0)
		return (0);
    else
        image->id_field = NULL;
    if (image->meta.image_type == TGA_COLOR_MAPPED)
        read_tga_color_map(image, file);
    if (image->meta.image_type == TGA_ENCODED_TRUECOLOR
		|| image->meta.image_type == TGA_ENCODED_MONOCHROME)
		read_encoded(image, file);
    else if (image->meta.image_type == TGA_TRUECOLOR
    	|| image->meta.image_type == TGA_MONOCHROME
    	|| image->meta.image_type == TGA_COLOR_MAPPED)
		read_unencoded_tga_image_data(image, file)
	else
		return (0);
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 19:25:56 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 19:25:58 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int		read_tga_image(int fd, t_tga *image)
{
	if (fd < 0)
		return (0);
	tga_footer(image, fd);
	tga_header(image, fd);
	if (image->meta.id_length && tga_id_field(image, fd) == 0)
		return (0);
	if (image->meta.image_type == TGA_COLOR_MAPPED)
		read_colormap(image, fd);
	if (image->meta.image_type == TGA_ENCODED_TRUECOLOR
		|| image->meta.image_type == TGA_ENCODED_MONOCHROME)
		read_encoded(image, fd);
	else if (image->meta.image_type == TGA_TRUECOLOR
		|| image->meta.image_type == TGA_MONOCHROME
		|| image->meta.image_type == TGA_COLOR_MAPPED)
		read_unencoded(image, fd);
	else
		return (0);
	return (1);
}

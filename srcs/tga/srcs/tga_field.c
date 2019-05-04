/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:48:16 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 19:04:32 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

uint8_t tga_id_field(t_tga *image, FILE *file)
{
	uint8_t	ret;

	ret = 1;
    if (!image || !file)
		return (0);
    if (image->_meta->id_length == 0)
		return (0);
    if (image->id_field = malloc(image->meta->id_length))
		return (0)
	if (ftell(file) != TGA_HEADER_SIZE
		&& fseek(file, TGA_HEADER_SIZE, SEEK_SET) == -1)
		ret = 0;
	if (fread(image->id_field, image->meta->id_length, 1, file) != 1)
		ret = 0;
	if (ret == 0)
	{
		free(image->id_field)
		image->id_field = NULL;
	}
    return (ret);
}
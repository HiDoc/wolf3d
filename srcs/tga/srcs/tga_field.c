/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:48:16 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 21:19:35 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

uint8_t		tga_id_field(t_tga *image, FILE *file)
{
	if (!image || !file)
		return (0);
	if (image->meta.id_length == 0)
		return (0);
	if ((image->id_field = malloc(image->meta.id_length)) == NULL)
		return (0);
	if (ftell(file) != TGA_HEADER_SIZE
		|| fseek(file, TGA_HEADER_SIZE, SEEK_SET) == -1
		|| fread(image->id_field, image->meta.id_length, 1, file) != 1)
	{
		free(image->id_field);
		image->id_field = NULL;
		return (0);
	}
	return (1);
}

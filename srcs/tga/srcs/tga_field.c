/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:48:16 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 19:10:52 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

uint8_t		tga_id_field(t_tga *image, int fd)
{
	if (!image || fd < -1)
		return (0);
	if (image->meta.id_length == 0)
		return (0);
	if ((image->id_field = malloc(image->meta.id_length)) == NULL)
		return (0);
	if (lseek(fd, 0, SEEK_CUR) != TGA_HEADER_SIZE
		|| lseek(fd, TGA_HEADER_SIZE, SEEK_SET) == -1
		|| read(fd, image->id_field, image->meta.id_length) < 0)
	{
		free(image->id_field);
		image->id_field = NULL;
		return (0);
	}
	return (1);
}

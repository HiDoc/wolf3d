/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_footer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:12:56 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 19:26:12 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

uint32_t	tga_set_offset(uint8_t *buffer, uint8_t pad)
{
	uint32_t	offset;

	offset = buffer[0 + pad];
	offset += ((uint16_t)(buffer[1 + pad])) << 8;
	offset += ((uint32_t)(buffer[2 + pad])) << 16;
	offset += ((uint32_t)(buffer[3 + pad])) << 24;
	return (offset);
}

uint8_t		tga_footer(t_tga *image, int fd)
{
	uint8_t		footer_buffer[TGA_FOOTER_SIZE];
	t_meta		*meta;
	unsigned	is_vision;

	if (!image || fd < 0)
		return (0);
	meta = &image->meta;
	if ((lseek(fd, -TGA_FOOTER_SIZE, SEEK_END) == -1) ||
		(read(fd, &footer_buffer, TGA_FOOTER_SIZE) < 0))
		return (0);
	is_vision = (ft_strncmp(((char *)(footer_buffer + 8)), TRUEVISION_SIG,
		TGA_SIG_SIZE - 1) == 0);
	image->version = is_vision ? 2 : 1;
	meta->ext_offset = is_vision ? tga_set_offset(footer_buffer, 0) : 0;
	meta->dev_offset = is_vision ? tga_set_offset(footer_buffer, 4) : 0;
	return (1);
}

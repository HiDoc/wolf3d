/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_footer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:12:56 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 20:44:03 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

unsigned int	tga_set_offset(unsigned char *buffer, unsigned char pad)
{
	unsigned int	offset;

	offset = buffer[0 + pad];
	offset += ((unsigned short)(buffer[1 + pad])) << 8;
	offset += ((unsigned int)(buffer[2 + pad])) << 16;
	offset += ((unsigned int)(buffer[3 + pad])) << 24;
	return (offset);
}

unsigned char	tga_footer(t_tga *image, int fd)
{
	unsigned char	footer_buffer[TGA_FOOTER_SIZE];
	t_meta			*meta;
	unsigned		is_vision;

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

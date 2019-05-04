/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_footer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:12:56 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 21:22:37 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

static void	tga_set_offset(uint32_t *set, uint8_t *buffer, uint8_t pad)
{
	uint32_t	offset;

	offset = buffer[0 + pad];
	offset += ((uint16_t)(buffer[1 + pad])) << 8;
	offset += ((uint32_t)(buffer[2 + pad])) << 16;
	offset += ((uint32_t)(buffer[3 + pad])) << 24;
	*set = offset;
}

uint8_t		tga_footer(t_tga *image, FILE *file)
{
	uint8_t		footer_buffer[TGA_FOOTER_SIZE];
	uint32_t	ext_off;
	uint32_t	dev_off;
	t_meta		*meta;

	if (!image || !file)
		return (0);
	meta = &image->meta;
	if (fseek(file, -TGA_FOOTER_SIZE, SEEK_END) == -1)
		return (0);
	if (fread(&footer_buffer, TGA_FOOTER_SIZE, 1, file) != 1)
		return (0);
	if (ft_strncmp(((char *)(footer_buffer + 8)),
		TRUEVISION_SIG, TGA_SIG_SIZE - 1) == 0)
	{
		image->version = 2;
		tga_set_offset(&ext_off, footer_buffer, 0);
		tga_set_offset(&dev_off, footer_buffer, 4);
		ext_off = footer_buffer[0];
		meta->extension_offset = ext_off;

		dev_off = footer_buffer[4];
		meta->developer_offset = dev_off;
	}
	else
	{
		image->version = 1;
		meta->extension_offset = 0;
		meta->developer_offset = 0;
	}
	return (1);
}

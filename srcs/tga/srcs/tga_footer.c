/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_footer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:12:56 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 14:44:52 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

#define TRUEVISION_SIG "TRUEVISION-XFILE."
#define TGA_SIG_SIZE  18

static void tga_set_offset(uint32_t *set, uint8_t *buffer, uint8_t pad)
{
	uint32_t	offset;

	offset = footer_buffer[0 + pad];
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

	if (!image || !file)
		return (0);
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
        image->meta->extension_offset = ext_off;

        dev_off = footer_buffer[4];
        image->meta->developer_offset = dev_off;
    }
    else
    {
        image->version = 1;
        image->meta->extension_offset = 0;
        image->meta->developer_offset = 0;
    }
    return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_encoded.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 15:11:23 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/04 18:33:55 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

static int encoded_check(t_tga *iage, FILE *file)
{
	if (!image || !file)
		return (0);
	if (image->meta.image_type != TGA_ENCODED_TRUECOLOR
		|| image->meta.image_type == TGA_ENCODED_MONOCHROME)
		return (0);
	return (1);
}

int read_encoded_loop(t_tga *image, FILe *file, t_encode *e, t_meta *meta)
{
	while (e->line < meta->height - 1)
    {
        e->current_line_pos = 0;
        while (e->current_line_pos < meta->width)
        {
            if (fread(&e->packet, sizeof(e->packet), 1, file) != 1)
				return (0);
            e->current_packet_cnt = (e->packet & 127) + 1;
            e->data_offset = (e->current_line_pos + (e->line * meta->width))
				* e->depth;
            if (e->packet & 128)
            {
                if (fread(e->run_packet, e->depth, 1, file) != 1)
					return (0);
				e->current_pixel = 0;
                while (e->current_pixel < e->current_packet_cnt)
				{
                    ft_memcpy(image->data + e->data_offset + (e->depth *
					e->current_pixel), e->run_packet, e->depth);
					e->current_pixel++;
				}
            }
            else
            {
                if (fread(image->data + e->data_offset, e->depth,
					e->current_packet_cnt, e->file) != e->current_packet_cnt)
					return (0);
            }
            e->current_line_pos += e->current_packet_cnt;
        }
		e->line++;
    }
	return (1);
}

int read_encoded(t_tga *image, FILE *file)
{
	t_encode		code;
	const t_meta	*meta = &image->meta;

	if (!encoded_check(image, file))
		return (0);
    code.line = 0;
    code.offset = (uint32_t)TGA_HEADER_SIZE + meta->id_length
		+ (meta->c_map_length * (meta->c_map_depth / 8))
		+ (meta->c_map_start);
    code.depth = (uint8_t)((meta->pixel_depth + 7) / 8);
    code.total = meta->width * meta->height * depth;
    code.current_packet_cnt = 0;
    code.current_line_pos = 0;
    code.current_pixel = 0;
    code.data_offset = 0;
    code.packet = 0;
    if ((code.run_packet = malloc(sizeof(uint8_t)*depth)) == NULL)
		return (0);
	//lst
    if (fseek(file, offset, SEEK_SET) != 0)
		return (0);
    if (image->data = malloc(sizeof(uint8_t) * total))
		return (0);
	return (read_encoded_loop(image, file, code, image->meta));
}
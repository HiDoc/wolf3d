/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:37:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 19:24:54 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>

#define TGA_HEADER_SIZE 18
#define TGA_FOOTER_SIZE 26
#define TGA_SIG_SIZE  18
#define TRUEVISION_SIG "TRUEVISION-XFILE."

typedef struct s_encode	t_encode;
typedef struct s_meta	t_meta;
typedef struct s_tga	t_tga;

enum {
    TGA_NO_DATA                 = 0,
    TGA_COLOR_MAPPED            = 1,
    TGA_TRUECOLOR               = 2,
    TGA_MONOCHROME              = 3,
    TGA_ENCODED_COLOR_MAPPED    = 9,
    TGA_ENCODED_TRUECOLOR       = 10,
    TGA_ENCODED_MONOCHROME      = 11,
    TGA_UNKNOWN_TYPE            = 255
};

struct s_encode
{
	uint16_t	line;
	uint32_t	offset;
    uint8_t		depth;
    uint32_t	total;
    uint8_t		packet;
    uint8_t		current_packet_cnt;
    uint16_t	current_line_pos;
    uint8_t		current_pixel;
    uint32_t	data_offset;
    uint8_t		*run_packet;
};

struct s_meta
{
	uint32_t	ext_offset;
    uint32_t	dev_offset;

    uint16_t	c_map_length;
    uint16_t	x_offset;
    uint16_t	y_offset;
    uint16_t	width;
    uint16_t	height;

    uint16_t	c_map_start;
    uint8_t		c_map_type;
    uint8_t		c_map_depth;
    uint8_t		id_length;
    uint8_t		image_type;
    uint8_t		pixel_depth;
    uint8_t		image_descriptor;
};

struct s_tga
{
    uint8_t	*id_field;
    uint8_t	*data;
    uint8_t	*color_map;
    uint8_t version;
    t_meta	meta;
};

int		read_tga_image(int fd, t_tga *image);
int     read_encoded(t_tga *image, int fd);
int     read_unencoded(t_tga *image, int fd);
int		read_colormap(t_tga *image, int fd);
int		tga_header(t_tga *image, int fd);
uint8_t	tga_footer(t_tga *image, int fd);
uint8_t tga_id_field(t_tga *image, int fd);


#endif

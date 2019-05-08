/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:37:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 20:38:48 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H

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
	unsigned short	line;
	unsigned int	offset;
    unsigned char	depth;
    unsigned int	total;
    unsigned char	packet;
    unsigned char	current_packet_cnt;
    unsigned short	current_line_pos;
    unsigned char	current_pixel;
    unsigned int	data_offset;
    unsigned char	*run_packet;
};

struct s_meta
{
	unsigned int	ext_offset;
    unsigned int	dev_offset;

    unsigned short	c_map_length;
    unsigned short	x_offset;
    unsigned short	y_offset;
    unsigned short	width;
    unsigned short	height;

    unsigned short	c_map_start;
    unsigned char	c_map_type;
    unsigned char	c_map_depth;
    unsigned char	id_length;
    unsigned char	image_type;
    unsigned char	pixel_depth;
    unsigned char	image_descriptor;
};

struct s_tga
{
    unsigned char	*id_field;
    unsigned char	*data;
    unsigned char	*color_map;
    unsigned char   version;
    t_meta	        meta;
};

int		        read_tga_image(int fd, t_tga *image);
int             read_encoded(t_tga *image, int fd);
int             read_unencoded(t_tga *image, int fd);
int		        read_colormap(t_tga *image, int fd);
int		        tga_header(t_tga *image, int fd);
unsigned char	tga_footer(t_tga *image, int fd);
unsigned char   tga_id_field(t_tga *image, int fd);
SDL_Surface     *load_tga(char *filename);

#endif

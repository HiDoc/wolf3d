/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 18:37:38 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/28 17:29:49 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H
# define COLORMAP 1
# define RGB 2
# define GRAYSCALE 3
# define COLORMAP_RLE 9
# define RGB_RLE 10
# define GRAYSCALE_RLE 11
# define RIGHT_ORIGIN 0x10
# define UPPER_ORIGIN 0x20
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <SDL.h>

typedef struct s_tga	t_tga;
typedef struct s_rgba	t_rgba;
typedef struct s_rle	t_rle;
typedef struct s_order	t_order;


struct s_rle
{
	int					count;
	unsigned char		copy[4];
	int					length;
	int					decoded;
	int					packet;
};

struct s_rgba
{
	int 				r;
	int 				g;
	int 				b;
	int 				a;
};

struct s_order
{
	int					rs;
	int					gs;
	int					bs;
	int					as;
};

struct s_tga
{
	const unsigned char	*bytes;
	const unsigned char	*palette;
	t_order				order;
	int 				descriptor;
	int 				color;
	int					type;
	int 				origin;
	int					index;
	int					length;
	int 				offset;
	int 				height;
	int 				width;
	int 				depth;
	int 				i;
	int 				j;
};

int				*tga_read(void *tga_parse, t_tga data);
int				*tga_rgb(int (*tga_sum)(t_tga *), t_tga data, int *pix);
int				*tga_map(int (*tga_sum)(t_tga *), t_tga data, int *pix);
int				*tga_greyscale(int (*)(t_tga *), t_tga data, int *pix);
unsigned char	*tga_rle(t_tga data);
int				pos_depth(t_tga *d);
int				tga_to_color(t_rgba c, t_order o);
int				tga_width(const unsigned char *buffer);
int				tga_height(const unsigned char *buffer);
void			*get_ft_index(t_tga *data);

#endif
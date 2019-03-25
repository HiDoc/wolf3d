/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauron <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 12:02:10 by jsauron           #+#    #+#             */
/*   Updated: 2019/03/25 12:29:16 by jsauron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		read_hdr(t_tga *tga, int fd)
{
	unsigned char	buff[18];

	if (read(fd, buff, 17) != 17)
	{
		ft_putstr("Invalid file\n");
		return(0);
	}
	printf("1\n");
	hdr_parser(tga, buff);
	printf("2\n");
	return (1);
}

void	hdr_parser(t_tga *tga, unsigned char *hdr)
{
	tga->lenid = hdr[0];
	tga->color_type = hdr[1];
	tga->compress = hdr[2];
	tga->cm_begin = hdr[3] + (hdr[4] * 256);
	tga->len_cm = hdr[5] + (hdr[6] * 256);
	tga->bits_cm = hdr[7];
	tga->xorigin = hdr[8] + (hdr[9] * 256);
	tga->yorigin = hdr[10] + (hdr[11] * 256);
	tga->w = hdr[12] + (hdr[13] * 256);
	tga->h = hdr[14]  + (hdr[15] * 256);
	tga->bitspix = hdr[16];
	tga->alpha = hdr[17];
	printf("Compress = %d\tBpp = %d\tX = %d\t Y = %d\n", tga->compress, tga->bitspix, tga->xorigin, tga->yorigin);
	//	printf("w = %d\nh = %d\nbits_cm = %d\ncolor_type = %d\ncompress = %d\nlen_cm = %d\nbit par pix = %d\nalpha = %d\ncm_begin = %d\n",
//			tga->w, tga->h, tga->bits_cm, tga->color_type, tga->compress, tga->len_cm,
//			tga->bitspix, tga->alpha, tga->cm_begin);
}

int			read_cm(t_tga *tga, int fd)
{
	unsigned char	buff[tga->len_cm * (tga->bits_cm >> 3)];
	int				i;

	i = -1;
	{
		if (!(tga->colormap = (unsigned char *)malloc(sizeof(unsigned char)
						* tga->len_cm * 4)))
			return (0);
		read(fd, buff, (tga->cm_begin));
		read(fd, buff, (tga->len_cm * (tga->bits_cm >> 3)));
		while (++i < (tga->len_cm * (tga->bits_cm >> 3)))
			tga->colormap[i] = buff[i];
	}
	i = 0;
/*	printf("PALETTE\n");
	while (i ++ < (tga->len_cm * (tga->bits_cm >> 3)))
		printf("%d ", tga->colormap[i]);
	printf("\n");
*/
	return (1);
}

int			read_data(t_tga *tga, int fd)
{
	unsigned char buff[100000];
	int				len;
	int i;

	i = 0;
	if (!(tga->file = (unsigned char *)ft_strdup("")))
		exit(EXIT_FAILURE); // recup error
	while (((len = read(fd, &buff, 100000)) > 0))
	{
		if (!(tga->file = (unsigned char *)ft_strjoin2(tga->file, buff, i, len)))
		{
			printf("Error join read_data\n");
			exit(EXIT_FAILURE);
		}
		i += len;
	}
	tga->file[i] = '\n';
	tga->nb_elem = i;
//	printf("i = %d\n", i);
//	printf("TRUEVISION = %d\n", ft_strcmp((const char *)&tga->file[tga->nb_elem - 18], "TRUEVISION-XFILE."));
//	printf("file-18 = %c, %c, %c, %c, %c, %c\n", tga->file[tga->nb_elem - 18], tga->file[tga->nb_elem - 17], tga->file[tga->nb_elem - 16], tga->file[tga->nb_elem - 15], tga->file[tga->nb_elem - 14], tga->file[tga->nb_elem - 13]);
	tga->file = (ft_strcmp((const char *)&tga->file[tga->nb_elem - 18], "TRUEVISION-XFILE.") == 0 ? (unsigned char *)ft_strsub((char const *)tga->file, 0, tga->nb_elem - 26) : tga->file);
	return (1);
}
/*
int		check_tv_signature(t_tga *tga)
{
	int	check;
	int i;

	i = 0;
	check = tga->file[tga->nb_elem - 26];
	while (i < 26)
	{
		if (check == 'T' && check + 1 == 'R' && check + 2 == 'U' && check + 3 == 'E')
			return (1);
		check++;
		i++;
	}
	return (0);
}*/

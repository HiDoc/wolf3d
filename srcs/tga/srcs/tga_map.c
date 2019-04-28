/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:15:03 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/28 17:24:57 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int		*tga_rgb(int (*tga_sum)(t_tga *), t_tga data, int *pix)
{
	t_rgba	rgba;
	int		index;

	index = pos_depth(&data);
	rgba = (t_rgba){data.bytes[index + 2],
		data.bytes[index + 1], data.bytes[index],
		(data.depth == 32 ? data.bytes[index + 3] : 0xFF)};
	data.color = tga_to_color(rgba, data.order);
	pix[tga_sum(&data)] = data.color;
	return (pix);
}

int		*tga_map(int (*tga_sum)(t_tga *), t_tga data, int *pix)
{
	t_rgba	rgba;
	int		index;

	data.index = data.bytes[pos_depth(&data)] & 0xFF - data.origin;
	data.color = 0xFFFFFFFF;
	if (data.index >= 0) {
		index = 3 * data.index + 18;
		rgba = (t_rgba){data.palette[index + 2],
		data.palette[index + 1], data.palette[index],
		(data.depth == 32 ? data.palette[index + 3] : 0xFF)};
		data.color = tga_to_color(rgba, data.order);
	}
	pix[tga_sum(&data)] = data.color;
	return (pix);
}

int		*tga_greyscale(int (*tga_sum)(t_tga *), t_tga data, int *pix)
{
	t_rgba	rgba;

	data.index = pos_depth(&data);
	data.color = data.bytes[data.index];
	rgba = (t_rgba){data.color, data.color, data.color,
		data.depth == 8 ? 0xFF : data.bytes[pos_depth(&data) + 1]};
	data.color = tga_to_color(rgba, data.order);
	pix[tga_sum(&data)] = data.color;
	return (pix);
}
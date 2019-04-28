/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:10:18 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/28 16:28:39 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

int		tga_to_color(t_rgba c, t_order o)
{
	c = (t_rgba){(c.r & 0xFF), (c.g & 0xFF), (c.b & 0xFF), (c.a & 0xFF)};
	return ((c.r << o.rs) | (c.g << o.gs) | (c.b << o.bs) | (c.a << o.as));
}

int		tga_width(const unsigned char *buffer)
{
	return ((buffer[12] & 0xFF) | (buffer[13] & 0xFF) << 8);
}

int		tga_height(const unsigned char *buffer)
{
	return ((buffer[14] & 0xFF) | (buffer[15] & 0xFF) << 8);
}

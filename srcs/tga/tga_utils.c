/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:10:18 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/27 20:10:21 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		tga_to_color(t_rgba rgba, t_order order)
{
	return ((rgba.r << order.rs) | (rgba.g << order.gs)
		| (rgba.b << order.bs) | (rgba.a << order.as));
}

int		tga_width(const unsigned char *buffer)
{
	return ((buffer[12] & 0xFF) | (buffer[13] & 0xFF) << 8));
}

int		tga_height(const unsigned char *buffer)
{
	return ((buffer[14] & 0xFF) | (buffer[15] & 0xFF) << 8);
}
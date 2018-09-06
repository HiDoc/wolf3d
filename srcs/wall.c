/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:13:50 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/06 18:04:43 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	line_wall(t_env *env, t_line *line, int y)
{
	int		x;
	int		yy;
	int		delta;

	(void)env;
	x = (int)(line->wall.x * 64.0);
	if (line->sidew == 0 && line->raydir.x > 0)
		x = 64.0 - x - 1;
	if (line->sidew == 1 && line->raydir.y < 0)
		x = 64.0 - x - 1;
	delta = y * 256 - HEIGHT * 128 + line->lineh * 128;
	yy = ((delta * 64.0) / (line->lineh)) / 256;
	return (line->text->data[yy * 64 + x]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 17:41:42 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/02 18:37:00 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int	line_floor(t_env *env, t_line *line, int y)
{
	double floorXWall, floorYWall; 
	if (line->sidew == 0 && line->raydir.x > 0)
	{
		floorXWall = line->map.x;
		floorYWall = line->map.y + line->wall.x;
	}
	else if (line->sidew == 0 && line->raydir.x < 0)
	{
		floorXWall = line->map.x + 1.0;
		floorYWall = line->map.y + line->wall.x;
	}
	else if (line->sidew == 1 && line->raydir.x > 0)
	{
		floorXWall = line->map.x + line->wall.x;
		floorYWall = line->map.y;
	}
	else
	{
		floorXWall = line->map.x + line->wall.x;
		floorYWall = line->map.y + 1.0;
	}

	double distWall, distPlayer, currentDist;

	distWall = line->wdist;
	distPlayer = 0.0;

	if (line->edraw < 0)
		line->edraw = HEIGHT; 
	currentDist = HEIGHT / (2.0 * y - HEIGHT);
	double weight = (currentDist - distPlayer) / (distWall - distPlayer);

	double currentFloorX = weight * floorXWall + (1.0 - weight) * env->pos.x;
	double currentFloorY = weight * floorYWall + (1.0 - weight) * env->pos.y;

	int floorTexX, floorTexY;
	floorTexX = (int)(currentFloorX * 64) % 64;
	floorTexY = (int)(currentFloorY * 64) % 64;
	return (64 * floorTexY + floorTexX);
}

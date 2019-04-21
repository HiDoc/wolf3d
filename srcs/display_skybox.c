/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_skybox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:56:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/21 20:09:40 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static Uint32	get_sb_color(int x, int y, float roll_d,
		float yaw_d, t_env *env, int floor_pos, int lol)
{
	float		wcalc;
	float		hcalc;

	//wcalc = (x * (env->skybox.sb->w / 4)) / W;
	//wcalc += (roll_d * env->skybox.sb->w) / 360;
	//wcalc = (int)wcalc % env->skybox.sb->w;

	(void)yaw_d;

	wcalc = (x * (env->skybox.sb->w / 4)) / W;
	wcalc += (roll_d * env->skybox.sb->w) / 360;
(void)floor_pos;
	hcalc = ((float)y * (float)env->skybox.sb->h / (float)H);
(void)lol;
	//hcalc = (floor_pos - (lol + y));
	return (getpixel(env->skybox.sb, wcalc, hcalc));
}

void			display_skybox(t_drawline l, t_env *env, int floor_pos)
{
	int     *pixels;
	int     x;
	int     iter;
	// faire ailleurs pour opti //
	float			roll_d;
	float			yaw_d;
	roll_d = env->engine.player.angle * 180 / M_PI;
	(roll_d > 360) ? roll_d = 0 : 0;
	(roll_d < 0) ? roll_d = 360 + roll_d : 0;
	yaw_d = (int)(env->engine.player.yaw * 180 / M_PI);
	//////////////////

	x = ((t_raycast *)l.container)->x;
	pixels  = (int *)env->sdl.surface->pixels;
	l.from = clamp(l.from, 0, H - 1);;

	l.to = clamp(floor_pos, 0, H - 1);
	if (l.from == l.to)
		pixels[l.from * W + x] = 0x00000000;
	else if (l.to > l.from)
	{
		pixels[l.from * W + x] = 0xff00ffff;
		iter = l.from + 1;
		int y = l.to;
		while (iter < l.to)
		{
			pixels[(l.to - y) * W + x] = get_sb_color(x, l.to - y,
					roll_d, yaw_d, env, floor_pos, l.to);
			y--;
			iter++;
		}
		pixels[l.to * W + x] = 0x00000000;
	}
}

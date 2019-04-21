/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_skybox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:56:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/21 17:14:45 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static Uint32	get_sb_color(int x, int y, float roll_d, float yaw_d, t_env *env)
{
	float		wcalc;
	float		hcalc;

	wcalc = (x * (env->skybox.sb->w / 4)) / W;
	wcalc += (roll_d * env->skybox.sb->w) / 360;
	wcalc = (int)wcalc % env->skybox.sb->w;

	hcalc = H;
	hcalc += (int)((y / 4) % env->skybox.sb->h);
	hcalc += (yaw_d * env->skybox.sb->h / 2) / 360;
	hcalc = (int)hcalc % env->skybox.sb->h;

	return (getpixel(env->skybox.sb, wcalc, hcalc));
}

void			display_skybox(t_drawline l, t_env *env)
{
	int     *pixels;
	int     x;
	int     iter;
	// faire ailleurs pour opti //
	float			roll_d;
	float			yaw_d;
	roll_d = (int)(env->engine.player.angle * 180 / M_PI) % 360;
	(roll_d < 0) ? roll_d = 360 + roll_d : 0;
	yaw_d = (int)(env->engine.player.yaw * 180 / M_PI);
	//////////////////

	x = ((t_raycast *)l.container)->x;
	pixels  = (int *)env->sdl.surface->pixels;
	l.from = clamp(l.from, 0, H - 1);
	l.to = clamp(l.to, 0, H - 1);
	if (l.from == l.to)
		pixels[l.from * W + x] = 0x00000000;
	else if (l.to > l.from)
	{
		pixels[l.from * W + x] = 0xff00ffff;
		iter = l.from + 1;
		int y = 0;
		while (iter < l.to)
		{
			pixels[iter * W + x] = get_sb_color(x, iter, roll_d, yaw_d, env);
			y++;
			iter++;
		}
		pixels[l.to * W + x] = 0x00000000;
	}
}

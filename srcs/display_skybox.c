/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_skybox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 12:56:28 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/22 13:21:28 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static Uint32	get_sb_color(int x, int y, float roll_d, t_env *env)
{
	float		wcalc;
	float		hcalc;

	wcalc = (x * (env->skybox.sb->w / 4)) / W;
	wcalc += (roll_d * env->skybox.sb->w) / 360;
	hcalc = ((y * env->skybox.sb->h) / H);
	return (getpixel(env->skybox.sb, wcalc, hcalc));
}

void			display_skybox(t_drawline l, t_env *env)
{
	int     x;
	int     y;

	x = ((t_raycast *)l.container)->x;
	l.from = clamp(l.from, 0, H - 1);
	l.to = clamp(l.to, 0, H - 1);
	if (l.from < l.to)
	{
		y = 0;
		while (y < l.to)
		{
			setpixel(env->sdl.surface, x, y,
			get_sb_color(x, y + env->engine.player.yaw_d,
			env->engine.player.roll_d, env));
			y++;
		}
	}
}

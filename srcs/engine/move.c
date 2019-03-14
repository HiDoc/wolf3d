/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:16:03 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/14 14:58:21 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Mouse aiming !
*/
int sdl_mouse(t_engine *e, t_vision *v)
{
	int			x;
	int			y;

	SDL_GetRelativeMouseState(&x, &y);
	e->player.angle += x * 0.03f;
	v->yaw = clamp(v->yaw + y * 0.05f, -5, 5);
	e->player.yaw = v->yaw - e->player.velocity.z * 0.5f;
	player_set(e, (t_vtx){0, 0});
	return (1);
}

int		sdl_set_velocity(t_env *env, t_vision *v, const Uint8 *keyb)
{
	t_engine	*e;
	t_vtx		move_vec;
	const int	pushing = (keyb[SDL_SCANCODE_W]) || (keyb[SDL_SCANCODE_S]) || (keyb[SDL_SCANCODE_A]) || (keyb[SDL_SCANCODE_D]);
	float		accel;
	const float	speed = env->player.actions.is_running ? SPEED_RUN : SPEED_WALK;

	move_vec = (t_vtx){0.f, 0.f};
	e = &env->engine;
	if (keyb[SDL_SCANCODE_W])
	{
		move_vec.x += e->player.anglecos * speed;
		move_vec.y += e->player.anglesin * speed;
	}
	if (keyb[SDL_SCANCODE_S])
	{
		move_vec.x -= e->player.anglecos * speed;
		move_vec.y -= e->player.anglesin * speed;
	}
	if (keyb[SDL_SCANCODE_A])
	{
		move_vec.x += e->player.anglesin * speed;
		move_vec.y -= e->player.anglecos * speed;
	}
	if (keyb[SDL_SCANCODE_D])
	{
		move_vec.x -= e->player.anglesin * speed;
		move_vec.y += e->player.anglecos * speed;
	}
	accel = pushing ? 0.4 : 0.2;
	e->player.velocity.x = e->player.velocity.x * (1 - accel) + move_vec.x * accel;
	e->player.velocity.y = e->player.velocity.y * (1 - accel) + move_vec.y * accel;
	v->moving = pushing;
	return (1);
}

void	player_falling(t_vision *v, t_engine *e, float limit, float speed)
{
	float nextz;

	e->player.velocity.z -= speed; /* Add gravity */
	nextz = e->player.where.z + e->player.velocity.z;
	if (e->player.velocity.z < 0
		&& nextz < e->sectors[e->player.sector].floor + v->eyeheight)
	{
		e->player.where.z = e->sectors[e->player.sector].floor + v->eyeheight;
		e->player.velocity.z = 0;
		v->falling = 0;
		v->ground = 1;
	}
	else if (e->player.velocity.z > 0
		&& nextz > limit) // When going up
	{
		/* Prevent jumping above ceiling */
		e->player.velocity.z = 0;
		v->falling = 1;
	}
	if (v->falling)
	{
		e->player.where.z += e->player.velocity.z;
		v->moving = 1;
	}
}

/*
**Vertical collision detection and horizontal collision detection
*/
void	player_collision(t_engine *e, t_vision *v, int jetpack)
{
	v->eyeheight = v->ducking ? DUCKHEIGHT : EYEHEIGHT;
	v->ground = !v->falling;
	// Change for jetpack
	/*
	if (!v->falling && jetpack)
		player_falling(v, e, e->sectors[e->player.sector].ceil, 0.05f);
	else */if (v->falling)
		player_falling(v, e, e->sectors[e->player.sector].floor + v->eyeheight * 2, 0.08f);
	if (v->moving)
		player_moving(v, 1, e);
}

void	player_set(t_engine *e, t_vtx d)
{
	e->player.where.x += d.x;
	e->player.where.y += d.y;
	e->player.anglesin = sinf(e->player.angle);
	e->player.anglecos = cosf(e->player.angle);
}

void	player_moving(t_vision *v, int set, t_engine *e)
{
	t_vtx			d;
	int				s;
	const t_vtx		p = {e->player.where.x, e->player.where.y};
	const t_sector	*sect = &e->sectors[e->player.sector];
	const t_vtx		*vert = sect->vertex;

	s = -1;
	(void)set;
	d = (t_vtx){e->player.velocity.x, e->player.velocity.y};

	/* Check if the player is about to cross one of the sector's edges */
	while (++s < (int)sect->npoints)
	{
		if (is_crossing(p, d, vert, s) && is_bumping(sect, v->eyeheight, s, e))
		{
			bumping_score(&d, (t_vtx){vert[s + 1].x - vert[s].x, vert[s + 1].y - vert[s].y});
			v->moving = 0;
			e->player.velocity = (t_vctr){0, 0, 0};
		}
	}
	s = -1;
	while (++s < (int)sect->npoints)
	{
		if (sect->neighbors[s] >= 0 && is_crossing(p, d, vert, s))
		{
			e->player.sector = sect->neighbors[s];
			break ;
		}
	}
	player_set(e, d);
	v->falling = 1;
}
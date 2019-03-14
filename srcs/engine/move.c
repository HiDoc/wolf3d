/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:16:03 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/14 19:02:50 by fmadura          ###   ########.fr       */
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
	e->player.anglesin = sinf(e->player.angle);
	e->player.anglecos = cosf(e->player.angle);
	v->falling = 1;
	return (1);
}

int		sdl_set_velocity(t_env *env, t_vision *v, const Uint8 *keyb)
{
	t_engine	*e;
	t_vtx		move_vec;
	const int	pushing = (keyb[SDL_SCANCODE_W]) || (keyb[SDL_SCANCODE_S]) || (keyb[SDL_SCANCODE_A]) || (keyb[SDL_SCANCODE_D]);
	float		accel;
	const float	speed = keyb[SDL_SCANCODE_LSHIFT] && v->ground ? SPEED_RUN * 2 : SPEED_WALK * 2;

	move_vec = (t_vtx){0.f, 0.f};
	e = &env->engine;
	if (keyb[SDL_SCANCODE_SPACE] && v->ground)
	{
		e->player.velocity.z += 1.0;
		v->falling = 1;
	}
	if ((keyb[SDL_SCANCODE_LCTRL] || keyb[SDL_SCANCODE_RCTRL]) && v->ground)
	{
        v->ducking = 1;
		v->falling = 1;
	}
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

	system("clear");
	e->player.velocity.z -= speed; /* Add gravity */
	t_vtx bezier = bezier_curve(
		(t_edge){(t_vtx){0, 0}, (t_vtx){0, 0}},
		(t_vtx){0, 0},
		1 - (e->player.velocity.z + 0.12f));
	if (e->player.velocity.z < 0)
		nextz = e->player.where.z + e->player.velocity.z;
	else
		nextz = bezier.y;
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
		e->player.where.z = bezier.y;
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
	(void)jetpack;
	/*
	Change for jetpack
	if (!v->falling && jetpack)
		player_falling(v, e, e->sectors[e->player.sector].ceil, 0.05f);
	*/
	if (v->falling)
		player_falling(v, e, e->sectors[e->player.sector].floor + v->eyeheight * 2, 0.05f);
	if (v->moving)
		player_moving(v, 1, e);
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
		printf("pointside: %f\n", pointside(add_vertex(p, d), vert[s], vert[s + 1]));
		if (is_crossing(p, d, vert, s) && is_bumping(sect, v->eyeheight, s, e))
		{
			float			x2;
			float			y2;
			const t_vtx		b = {vert[s + 1].x - vert[s].x, vert[s + 1].y - vert[s].y};

			x2 = b.x * b.x;
			y2 = b.y * b.y;
			d.x = (b.x * (d.x * b.x + b.y * d.y)) / (x2 + y2);
			d.y = (b.y * (d.x * b.x + b.y * d.y)) / (x2 + y2);
			printf("intersect: %d\n", intersect_rect(p, add_vertex(p, d), vert[s], vert[s + 1]));
			printf("pointside: %f\n", pointside(add_vertex(p, d), vert[s], vert[s + 1]));
			printf("[%f, %f], [%f, %f]\n", d.x, d.y, b.x, b.y);
			if (sect->neighbors[s] < 0 && pointside(add_vertex(p, d), vert[s], vert[s + 1]) < 0.3)
				v->moving = 0;
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
	if (v->moving)
	{
		e->player.where.x += d.x;
		e->player.where.y += d.y;
	}
	v->falling = 1;
}
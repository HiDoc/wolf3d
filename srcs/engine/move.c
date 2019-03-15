/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:16:03 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/15 14:26:16 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Set velocity of player in {x, y}
*/
int		pushing(const Uint8 *keyb)
{
	return (keyb[SDL_SCANCODE_W] || keyb[SDL_SCANCODE_S]
		|| keyb[SDL_SCANCODE_A] || keyb[SDL_SCANCODE_D]);
}

int		keyboard_movement(t_engine *e, t_vision *v, const Uint8 *keyb)
{
	float		accel;
	t_vtx		move_vec;
	const float	speed = keyb[SDL_SCANCODE_LSHIFT] && v->ground ? SPEED_RUN * 2 : SPEED_WALK * 2;
	const float	sin_move = e->player.anglesin * speed;
	const float	cos_move = e->player.anglecos * speed;

	move_vec = (t_vtx){0.f, 0.f};
	e->player.velocity.z += (float)(v->ground && keyb[SDL_SCANCODE_SPACE]);
	v->ground = !keyb[SDL_SCANCODE_SPACE];
	v->ducking = (keyb[SDL_SCANCODE_LCTRL] || keyb[SDL_SCANCODE_RCTRL]);
	if (keyb[SDL_SCANCODE_W])
		move_vec = add_vertex(move_vec, (t_vtx){cos_move, sin_move});
	if (keyb[SDL_SCANCODE_S])
		move_vec = diff_vertex(move_vec, (t_vtx){cos_move, sin_move});
	if (keyb[SDL_SCANCODE_A])
		move_vec = add_vertex(move_vec, (t_vtx){sin_move, -cos_move});
	if (keyb[SDL_SCANCODE_D])
		move_vec = diff_vertex(move_vec, (t_vtx){sin_move, -cos_move});
	accel = pushing(keyb) ? 0.4 : 0.2;
	e->player.velocity.x = e->player.velocity.x * (1 - accel) + move_vec.x * accel;
	e->player.velocity.y = e->player.velocity.y * (1 - accel) + move_vec.y * accel;
	v->moving = pushing(keyb);
	return (1);
}

/*
** gravity
*/
void	handle_gravity(t_vision *v, t_engine *e, float gravity)
{
	float		nextz;
	t_vtx		bezier;
	const float	floor = e->sectors[e->player.sector].floor;
	const float	limit = floor + v->eyeheight * 2;

	e->player.velocity.z -= gravity;
	bezier = bezier_curve((t_edge){(t_vtx){0, 6}, (t_vtx){20, 6}},
			(t_vtx){0, 15}, 1 - (e->player.velocity.z + 0.12f));
	nextz = (e->player.velocity.z < 0) ? e->player.where.z + e->player.velocity.z : bezier.y;
	if (e->player.velocity.z < 0 && nextz < (floor + v->eyeheight))
	{
		e->player.where.z = floor + v->eyeheight;
		e->player.velocity.z = 0;
		v->falling = 0;
		v->ground = 1;
	}
	else if (e->player.velocity.z > 0 && nextz > limit)
		e->player.velocity.z = 0;
	if (v->falling)
	{
		e->player.where.z = bezier.y;
		v->moving = 1;
	}
}

/*
** Verify is player is not in a wall
*/
// TODO: Change collision
static int sector_collision(t_vtx player, t_vtx *dest, t_edge wall)
{
	const t_vtx	b = diff_vertex(wall.v2, wall.v1);
	float		scale;

	scale = (dest->x * b.x + b.y * dest->y) / (b.x * b.x + b.y * b.y);
	dest->x = b.x * scale;
	dest->y = b.y * scale;
	return (pointside(add_vertex(player, *dest), wall.v1, wall.v2) < 0.3);
}

/*
** Collision detection.
** Check if the player is crossing an edge and if this edge has a neighbour
*/
void	collision(t_vision *v, t_engine *e, t_sector *sect)
{
	int				s;
	t_vtx			dest;
	t_edge			wall;
	const t_vtx		player = {e->player.where.x, e->player.where.y};
	const t_vtx		*vert = sect->vertex;

	s = -1;
	dest = (t_vtx){e->player.velocity.x, e->player.velocity.y};
	while (++s < (int)sect->npoints)
	{
		wall = (t_edge){vert[s], vert[s + 1]};
		if (is_crossing(player, dest, wall) && is_bumping(e, v, sect, s))
		{
			if (sector_collision(player, &dest, wall) && sect->neighbors[s] < 0)
				v->moving = 0;
		}
		if (sect->neighbors[s] >= 0 && is_crossing(player, dest, wall))
			e->player.sector = sect->neighbors[s];
	}
	if (v->moving)
	{
		e->player.where.x += dest.x;
		e->player.where.y += dest.y;
	}
}

/*
** Vertical collision detection and horizontal collision detection
*/
void	player_move(t_env *env, t_vision *v, const Uint8 *keycodes)
{
	t_engine	*e;
	int			x;
	int			y;

	e = &env->engine;
	v->falling = 1;
	SDL_GetRelativeMouseState(&x, &y);
	e->player.angle += x * 0.03f;
	v->yaw = clamp(v->yaw + y * 0.05f, -5, 5);
	e->player.yaw = v->yaw - e->player.velocity.z * 0.5f;
	e->player.anglesin = sinf(e->player.angle);
	e->player.anglecos = cosf(e->player.angle);
	v->eyeheight = v->ducking ? DUCKHEIGHT : EYEHEIGHT;
	handle_gravity(v, e, 0.05f);
	(v->moving) ? collision(v, e, &e->sectors[e->player.sector]) : 0;
	keyboard_movement(&env->engine, v, keycodes);
}
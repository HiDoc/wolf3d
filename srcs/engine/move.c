/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:16:03 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 15:16:36 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Set velocity of player in {x, y}
*/
int		pushing(const Uint8 *keyb, int *k)
{
	return (keyb[k[I_OUP]] || keyb[k[I_ODOWN]]
		|| keyb[k[I_OLEFT]] || keyb[k[I_ORIGHT]]);
}

int		keyboard_movement(t_engine *e, t_vision *v, const Uint8 *keyb)
{
	t_vtx		move_vec;
	t_vctr		*velocity;
	const float	speed = keyb[SDL_SCANCODE_LSHIFT] ? SPEED_RUN : SPEED_WALK;
	const float	sin_move = e->player.anglesin * speed;
	const float	cos_move = e->player.anglecos * speed;

	e->player.sound.run = (speed == SPEED_RUN) ? 1 : 0;
	velocity = &e->player.velocity;
	move_vec = (t_vtx){0.f, 0.f};
	velocity->z += (float)(v->ground && keyb[SDL_SCANCODE_SPACE]);
	v->ground = !keyb[SDL_SCANCODE_SPACE];
	v->ducking = (keyb[SDL_SCANCODE_LCTRL] || keyb[SDL_SCANCODE_RCTRL]);
	if (keyb[e->keys[I_OUP]])
		move_vec = add_vertex(move_vec, (t_vtx){cos_move, sin_move});
	if (keyb[e->keys[I_ODOWN]])
		move_vec = diff_vertex(move_vec, (t_vtx){cos_move, sin_move});
	if (keyb[e->keys[I_OLEFT]])
		move_vec = add_vertex(move_vec, (t_vtx){sin_move, -cos_move});
	if (keyb[e->keys[I_ORIGHT]])
		move_vec = diff_vertex(move_vec, (t_vtx){sin_move, -cos_move});
	velocity->x = velocity->x * (1 - speed) + move_vec.x * speed;
	velocity->y = velocity->y * (1 - speed) + move_vec.y * speed;
	v->moving = pushing(keyb, e->keys);
	return (1);
}

/*
** gravity
*/
void	handle_gravity(t_vision *v, t_engine *e, float gravity)
{
	const float	floor = e->sectors[e->player.sector].floor;
	const float	ceil = e->sectors[e->player.sector].ceil;
	t_player	*plr;
	float		nextz;
	t_vtx		bezier;

	plr = &e->player;
	plr->velocity.z -= gravity;
	bezier = bezier_curve(
		(t_edge){(t_vtx){0, EYEHEIGHT}, (t_vtx){20, EYEHEIGHT}},
		(t_vtx){0, 40}, 1 - (plr->velocity.z + 0.12f));
	nextz = (plr->velocity.z < 0) ? plr->where.z + plr->velocity.z : bezier.y;
	if (plr->velocity.z < 0 && nextz < (floor + v->eyeheight))
	{
		plr->where.z = floor + v->eyeheight;
		plr->velocity.z = 0;
		v->falling = 0;
		v->ground = 1;
	}
	if (plr->where.z > ceil || nextz > ceil)
		plr->where.z = ceil;
	if (v->falling)
	{
		plr->where.z = bezier.y;
		v->moving = 1;
	}
}

/*
** Verify is player is not in a wall
*/
// TODO: Change collision
int		sector_collision(t_vtx player, t_vtx *dest, t_edge wall)
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
	const t_vtx		player = {e->player.where.x, e->player.where.y};
	const t_vtx		*vert = sect->vertex;
	t_vtx			dest;
	t_edge			wall;
	int				s;

	s = -1;
	dest = (t_vtx){e->player.velocity.x, e->player.velocity.y};
	while (++s < (int)sect->npoints)
	{
		wall = (t_edge){vert[s], vert[s + 1]};
		if (is_crossing(player, dest, vert, s) && is_bumping(sect, v, s, e))
		{
			if (sector_collision(player, &dest, wall))
				v->moving = 0;
		}
	}
	s = -1;
	while (++s < (int)sect->npoints)
	{
		if (sect->neighbors[s] >= 0 && is_crossing(player, dest, vert, s))
		{
			e->player.sector = sect->neighbors[s];
			break;
		}
	}
	e->player.where.x += dest.x;
	e->player.where.y += dest.y;
	v->falling = 1;
}

/*
**Vertical collision detection and horizontal collision detection
*/
void	player_move(t_engine *e, t_vision *v, const Uint8 *keycodes)
{
	int	x;
	int y;

	v->falling = 1;
	SDL_GetRelativeMouseState(&x, &y);
	e->player.angle += x * 0.002f;
	v->yaw = clamp(v->yaw + y * 0.005f, -5, 5);
	e->player.yaw = v->yaw - e->player.velocity.z * 0.8f;
	e->player.yaw_d = (e->player.yaw * 180 / M_PI);
	e->player.roll_d = e->player.angle * 180 / M_PI;
	(e->player.roll_d < 0) ? e->player.roll_d = 360 + e->player.roll_d : 0;
	e->player.anglesin = sinf(e->player.angle);
	e->player.anglecos = cosf(e->player.angle);
	e->player.sound.o_veloc = e->player.velocity.z;
	e->player.sound.o_duck = v->ducking;
	v->eyeheight = v->ducking ? DUCKHEIGHT : EYEHEIGHT;
	e->player.origin = e->player.where;
	handle_gravity(v, e, 0.05f);
	if (v->moving)
		collision(v, e, &e->sectors[e->player.sector]);
	keyboard_movement(e, v, keycodes);
	sd_stat_player(e, v, &e->player.sound);
}

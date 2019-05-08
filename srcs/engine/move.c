/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:16:03 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/08 21:31:22 by fmadura          ###   ########.fr       */
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

void	set_velocity(t_engine *e, float speed, const Uint8 *keyb, t_vtx *mvtx)
{
	float		sin_move;
	float		cos_move;

	sin_move = e->player.anglesin * speed;
	cos_move = e->player.anglecos * speed;
	if (keyb[e->keys[I_OUP]])
		*mvtx = add_vertex(*mvtx, (t_vtx){cos_move, sin_move});
	if (keyb[e->keys[I_ODOWN]])
		*mvtx = diff_vertex(*mvtx, (t_vtx){cos_move, sin_move});
	if (keyb[e->keys[I_OLEFT]])
		*mvtx = add_vertex(*mvtx, (t_vtx){sin_move, -cos_move});
	if (keyb[e->keys[I_ORIGHT]])
		*mvtx = diff_vertex(*mvtx, (t_vtx){sin_move, -cos_move});
}

void	keyboard_movement(t_engine *e, t_vision *v, const Uint8 *keyb)
{
	t_vtx		move_vec;
	t_vctr		*velocity;
	float		speed;

	speed = keyb[SDL_SCANCODE_LSHIFT] ? SPEED_RUN : SPEED_WALK;
	e->player.sound.run = (speed == SPEED_RUN) ? 1 : 0;
	velocity = &e->player.velocity;
	move_vec = (t_vtx){0.f, 0.f};
	if (keyb[SDL_SCANCODE_SPACE] && v->ground)
	{
		v->ground = 0;
		velocity->z += 1.0;
	}
	v->ducking = (keyb[SDL_SCANCODE_LCTRL] || keyb[SDL_SCANCODE_RCTRL]);
	set_velocity(e, speed, keyb, &move_vec);
	velocity->x = velocity->x * (1 - speed) + move_vec.x * speed;
	velocity->y = velocity->y * (1 - speed) + move_vec.y * speed;
	v->moving = pushing(keyb, e->keys);
}

/*
**Vertical collision detection and horizontal collision detection
*/

void	player_move(t_engine *e, t_vision *v, const Uint8 *keycodes)
{
	int		x;
	int		y;

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

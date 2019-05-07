/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:31:30 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 23:04:44 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_player	bot_angle(t_player e, t_player src)
{
	t_player	new;

	new.where = e.where;
	new.whereto = src.where;
	new.angle = -e.where.x * 0.002f;
	new.anglesin = -sinf(new.angle);
	new.anglecos = -cosf(new.angle);
	new.sprite = src.sprite;
	return (new);
}

t_vtx		bot_orientation(t_player *bot, t_vctr p_where, float speed)
{
	t_vtx		move;
	const float	cos_move = bot->anglecos * speed;
	const float	sin_move = bot->anglesin * speed;

	move = (t_vtx){0.f, 0.f};
	if (bot->where.x < p_where.x && bot->where.y < p_where.y)
		move = add_vertex(move, (t_vtx){sin_move, -cos_move});
	else if (bot->where.x > p_where.x && bot->where.y > p_where.y)
		move = diff_vertex(move, (t_vtx){sin_move, -cos_move});
	else if (bot->where.x > p_where.x && bot->where.y < p_where.y)
		move = add_vertex(move, (t_vtx){cos_move, sin_move});
	else if (bot->where.x < p_where.x && bot->where.y > p_where.y)
		move = diff_vertex(move, (t_vtx){cos_move, sin_move});
	return (move);
}

void		bot_move(t_env *env, t_vtx p, t_wrap_enmy *enemy, float speed)
{
	t_vtx	move;
	t_vctr	*vel;

	vel = &enemy->player.velocity;
	enemy->player.whereto = (t_vctr){p.x, p.y, EYEHEIGHT};
	enemy->player.angle = -enemy->player.where.x * 0.002f;
	enemy->player.anglesin = -sinf(enemy->player.angle);
	enemy->player.anglecos = -cosf(enemy->player.angle);
	move = bot_orientation(&enemy->player, enemy->player.whereto, speed);
	vel->x = vel->x * (1 - speed) + move.x * speed;
	vel->y = vel->y * (1 - speed) + move.y * speed;
	if (!bot_wall_collision(&enemy->player,
		&env->engine.sectors[env->engine.player.sector]))
	{
		enemy->player.where.x += vel->x;
		enemy->player.where.y += vel->y;
	}
}

void		bot_check_friend(t_wrap_enmy *enemy, t_wrap_enmy *next)
{
	t_vtx	first;
	t_vtx	secd;

	first = (t_vtx){enemy->player.where.x, enemy->player.where.y};
	secd = (t_vtx){next->player.where.x, next->player.where.y};
	if (dist_vertex(first, secd) <= 9)
	{
		if (first.x < secd.x && first.y <= secd.y)
			next->player.where.x -= next->player.velocity.x;
		else if (first.x >= secd.x && first.y >= secd.y)
			next->player.where.x -= next->player.velocity.x;
		else if (first.x >= secd.x && first.y <= secd.y)
			next->player.where.y += next->player.velocity.y;
		else if (first.x <= secd.x && first.y >= secd.y)
			next->player.where.y += next->player.velocity.y;
	}
}

void		bot_status(t_env *env, t_vtx player,
			t_wrap_enmy *e, Uint8 *keycodes)
{
	t_vtx	where;

	where = (t_vtx){e->player.where.x, e->player.where.y};
	if (!env->player.actions.is_invisible && !e->a.is_dying && !e->a.is_shot)
	{
		e->a.is_alerted = (dist_vertex(player, where) < e->brain.dist_alert
		&& keycodes[SDL_SCANCODE_LSHIFT]);
		e->a.has_detected = (dist_vertex(player, where) < e->brain.dist_detect
		&& !keycodes[SDL_SCANCODE_LCTRL] && !keycodes[SDL_SCANCODE_RCTRL]);
		e->a.close_seen = (dist_vertex(player, where) < e->brain.dist_close);
		// if (e->a.is_alerted)
		// {
			if (dist_vertex(player, where) > e->brain.dist_player)
			{
				bot_move(env, player, e, e->brain.velocity);
				e->a.is_moving = 1;
				e->a.is_shooting = 0;
			e->a.is_shooting = 1;
			}
		// }
		// if (e->a.has_detected || e->a.close_seen)
	}
	else
		e->a.is_shooting = 0;
}

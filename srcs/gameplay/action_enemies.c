/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:32:01 by abaille           #+#    #+#             */
/*   Updated: 2019/03/31 21:01:30 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	bot_move(t_vtx p, t_wrap_enmy *enemy, float speed)
{
	t_vtx		move;

	move = (t_vtx){0.f, 0.f};
	enemy->angle = -p.x * 0.02f;
	enemy->anglesin = -sinf(enemy->angle);
	enemy->anglecos = -cosf(enemy->angle);
	float	sin_move = enemy->anglesin * speed;
	float	cos_move = enemy->anglecos * speed;
	if (enemy->where.x < p.x && enemy->where.y < p.y)
		move = add_vertex(move, (t_vtx){sin_move, -cos_move});
	else if (enemy->where.x > p.x && enemy->where.y > p.y)
		move = diff_vertex(move, (t_vtx){sin_move, -cos_move});
	else if (enemy->where.x > p.x && enemy->where.y < p.y)
		move = add_vertex(move, (t_vtx){cos_move, sin_move});
	else if (enemy->where.x < p.x && enemy->where.y > p.y)
		move = diff_vertex(move, (t_vtx){cos_move, sin_move});
	enemy->velocity.x = enemy->velocity.x * (1 - speed) + move.x * speed;
	enemy->velocity.y = enemy->velocity.y * (1 - speed) + move.y * speed;
	enemy->where.x += enemy->velocity.x;
	enemy->where.y += enemy->velocity.y;
}

void	bot_check_where(t_wrap_enmy *enemy, t_wrap_enmy *next)
{
	if (dist_vertex(enemy->where, next->where) <= 5)
	{
		if (enemy->where.x >= next->where.x)
			next->where.x -= next->velocity.x;
		else if (enemy->where.y >= next->where.y)
			next->where.x += next->velocity.x;
	}
}

void	bot_shoot(t_env *env, t_wrap_enmy *enemy)
{
	const t_vtx	p = (t_vtx){env->engine.player.where.x, env->engine.player.where.y};

	if (!enemy->shoot->is_shooting)
	{
		enemy->shoot->where = enemy->where;
		enemy->shoot->whereto = p;
		enemy->shoot->is_shooting = 1;
		enemy->shoot->is_alive = 1;
	}
	else if (enemy->shoot->is_alive)
	{

		if (dist_vertex(enemy->shoot->where, enemy->shoot->whereto) > 1)
		{
			bot_move(enemy->shoot->whereto, enemy->shoot, 0.4f);
			enemy->shoot->where.x += enemy->shoot->velocity.x;
			enemy->shoot->where.y += enemy->shoot->velocity.y;
		}
		else
		{
			if (enemy->shoot->whereto.x == p.x && enemy->shoot->whereto.y == p.y)
			{
				if (env->player.shield)
					env->player.shield -= 10;
				else
					env->player.health -= 10;
				if (env->player.health <= 10)
					env->player.health = 200;
			}
			enemy->shoot->is_alive = 0;
			enemy->shoot->is_shooting = 0;
		}
	}
}

void	bot_action(t_env *env, t_sector *sector)
{
	t_wrap_enmy	*enemy;

	(void)env;
	enemy = sector->head_enemy;
	while (enemy)
	{
		if (enemy->is_alive)
		{
			if (enemy->next && enemy->next->is_alive)
				bot_check_where(enemy, enemy->next);
			if (enemy->is_shooting)
				bot_shoot(env, enemy);
		}
		enemy = enemy->next;
	}
}

void	bot_status(t_env *env, t_vtx player, t_wrap_enmy *enemy, Uint8 *keycodes)
{
	if (!env->player.actions.is_invisible)
	{
		enemy->is_alerted = (dist_vertex(player, enemy->where) < 500
		&& keycodes[SDL_SCANCODE_LSHIFT]);
		enemy->has_detected = (dist_vertex(player, enemy->where) < 500
		&& !keycodes[SDL_SCANCODE_LCTRL] && !keycodes[SDL_SCANCODE_RCTRL]);
		enemy->close_seen = (dist_vertex(player, enemy->where) < 100);
		if (enemy->is_alerted || enemy->has_detected || enemy->close_seen)
		{
			if (dist_vertex(player, enemy->where) > 100)
				bot_move(player, enemy, 0.2f);
			else
				enemy->is_shooting = enemy->has_detected || enemy->close_seen;
		}
	}
}


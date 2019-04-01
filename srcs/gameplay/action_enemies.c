/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:32:01 by abaille           #+#    #+#             */
/*   Updated: 2019/04/01 11:26:58 by abaille          ###   ########.fr       */
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
		if (enemy->where.x <= next->where.x
		&& enemy->where.y <= next->where.y)
			next->where.x -= next->velocity.x;
		else if (enemy->where.x >= next->where.x
		&& enemy->where.y >= next->where.y)
			next->where.x -= next->velocity.x;
		else if (enemy->where.x >= next->where.x
		&& enemy->where.y <= next->where.y)
			next->where.y += next->velocity.y;
		else if (enemy->where.x <= next->where.x
		&& enemy->where.y >= next->where.y)
			next->where.y += next->velocity.y;
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
	}
	else
	{
		if (dist_vertex(enemy->shoot->where, enemy->shoot->whereto) > 1)
			bot_move(enemy->shoot->whereto, enemy->shoot, 0.4f);
		else
		{
			if (enemy->shoot->whereto.x == p.x && enemy->shoot->whereto.y == p.y)
			{
				if (env->player.shield)
					env->player.shield -= enemy->damage;
				else
					env->player.health -= enemy->damage;
				if (env->player.health <= 10)
					env->player.health = 200;
			}
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

/*
// ** Verify is player is not in a wall
// */
// // TODO: Change collision
// int		sector_collision(t_vtx player, t_vtx *dest, t_edge wall)
// {
// 	const t_vtx	b = diff_vertex(wall.v2, wall.v1);
// 	float		scale;

// 	scale = (dest->x * b.x + b.y * dest->y) / (b.x * b.x + b.y * b.y);
// 	dest->x = b.x * scale;
// 	dest->y = b.y * scale;
// 	return (pointside(add_vertex(player, *dest), wall.v1, wall.v2) < 0.3);
// }

/*
** Collision detection.
** Check if the player is crossing an edge and if this edge has a neighbour
*/
// void	impact_collision(t_wrap_enmy *shot, t_sector *sect)
// {
// 	const t_vtx		impact = {shot->where.x, shot->where.y};
// 	const t_vtx		*vert = sect->vertex;
// 	t_vtx			dest;
// 	t_edge			wall;
// 	int				s;

// 	s = -1;
// 	dest = (t_vtx){shot->velocity.x, shot->velocity.y};
// 	while (++s < (int)sect->npoints)
// 	{
// 		wall = (t_edge){vert[s], vert[s + 1]};
// 		if (is_crossing(impact, dest, vert, s))
// 		{
// 			if (sector_collision(impact, &dest, wall))
// 				shot->is_shooting = 0;
// 		}
// 	}
// 	// s = -1;
// 	// while (++s < (int)sect->npoints)
// 	// {
// 	// 	if (sect->neighbors[s] >= 0 && is_crossing(where, dest, vert, s))
// 	// 	{
// 	// 		e->player.sector = sect->neighbors[s];
// 	// 		break;
// 	// 	}
// 	// }
// }

// void	impact_bot(t_wrap_enmy *shot, t_sector *sector)
// {

// 	enemy = sector->head_enemy;
// 	while (enemy)
// 	{
// 		enemy = enemy->next;
// 	}
// }

// void	pl_kill_bot(t_env *env, t_ixy mouse, t_sector *sector)
// {
// 	t_wrap_enmy	*enemy;
// 	t_wrap_enmy	*shot;
// 	t_vtx		step;
// 	const t_player	p = env->engine.player;

// 	if (env->player.actions.is_shooting)
// 	{
// 		shot = &env->player.shoot;
// 		enemy = sector->head_enemy;
// 		if (!shot->is_shooting)
// 		{
// 			shot->origin = p.where;
// 			shot->where = p.where;
// 			shot->is_shooting = 1;
// 			step = (t_vtx){p.anglecos, p.anglesin};
// 		}
// 		else
// 		{
// 			shot->velocity.x = shot->velocity.x * (1 - 0.4f) + step.x * 0.4f;
// 			shot->velocity.y = shot->velocity.y * (1 - 0.4f) + step.y * 0.4f;
// 			impact_collision(shot, sector);
// 			impact_bot(shot, sector);
// 			if (shot->is_shooting)
// 			{
// 				shot->where.x += dest.x;
// 				shot->where.y += dest.y;
// 			}

// 		}

// 	}
// }

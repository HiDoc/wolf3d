/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:32:01 by abaille           #+#    #+#             */
/*   Updated: 2019/04/26 23:50:03 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_vtx	bot_orientation(t_player *bot, t_vctr p_where, float speed)
{
	t_vtx	move;
	float	cos_move = bot->anglecos * speed;
	float	sin_move = bot->anglesin * speed;

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

void	bot_move(t_env *env, t_vtx p, t_wrap_enmy *enemy, float speed)
{
	t_vtx		move;

	enemy->player.whereto = (t_vctr){p.x, p.y, EYEHEIGHT};
	enemy->player.angle = -p.x * 0.03f;
	enemy->player.anglesin = -sinf(enemy->player.angle);
	enemy->player.anglecos = -cosf(enemy->player.angle);
	move = bot_orientation(&enemy->player, enemy->player.whereto, speed);
	enemy->player.velocity.x = enemy->player.velocity.x * (1 - speed) + move.x * speed;
	enemy->player.velocity.y = enemy->player.velocity.y * (1 - speed) + move.y * speed;
	if (!bot_wall_collision(&enemy->player, &env->engine.sectors[env->engine.player.sector]))
	{
		enemy->player.where.x += enemy->player.velocity.x;
		enemy->player.where.y += enemy->player.velocity.y;
	}
}

void	bot_check_friend(t_wrap_enmy *enemy, t_wrap_enmy *next)
{
	t_vtx	first;
	t_vtx	secd;

	first = (t_vtx){enemy->player.where.x, enemy->player.where.y};
	secd = (t_vtx){next->player.where.x, next->player.where.y};
	if (dist_vertex(first, secd) <= 5)
	{
		if (first.x <= secd.x && first.y <= secd.y)
			next->player.where.x -= next->player.velocity.x;
		else if (first.x >= secd.x && first.y >= secd.y)
			next->player.where.x -= next->player.velocity.x;
		else if (first.x >= secd.x && first.y <= secd.y)
			next->player.where.y += next->player.velocity.y;
		else if (first.x <= secd.x && first.y >= secd.y)
			next->player.where.y += next->player.velocity.y;
	}
}

int		bot_new_kill(int shooting, t_player *p, t_wrap_enmy* enemy)
{
	int	i;

	i = 0;
	if (shooting)
	{
		while (i < BOT_NB_SHOT)
		{
			if (!enemy->shot[i].is_alive)
			{
				new_bullet(&enemy->shot[i], p, BOT_V_SHOT);
				return (1);
			}
			i++;
		}
		ft_bzero(&enemy->shot[0], sizeof(t_impact));
		new_bullet(&enemy->shot[0], p, BOT_V_SHOT);
		ft_bzero(&enemy->shot[1], sizeof(t_impact));
	}
	return (1);
}

t_player	bot_angle(t_player src)
{
	t_player	new;

	new.where = src.where;
	new.angle = -src.where.x * 0.03f;
	new.anglecos = -sinf(src.angle);
	new.anglecos = -cosf(src.angle);
	new.sprite = src.sprite;
	return (new);
}

static void	bot_shoot_cadence(t_env *env, t_wrap_enmy *e, t_player p)
{
	t_player	new_look;

	if (e->frame >= env->world.enemies[e->ref].cadence_shoot)
	{
		new_look = bot_angle(p);
		bot_new_kill(e->is_shooting, &new_look, e);
		e->player.sound.shootin = 1;
		e->frame = 0;
	}
	else
		e->frame++;
}

static void	bot_bullet(t_env *env, t_wrap_enmy *e, int damage)
{
	t_vtx		move;
	int			i;
	t_sector	*sector;

	i = 0;
	sector = &env->engine.sectors[env->engine.player.sector];
	while (i < BOT_NB_SHOT)
	{
		if (e->shot[i].is_shooting)
		{
			move = bot_orientation(&e->shot[i].position, e->player.whereto, BOT_V_SHOT);
			e->shot[i].position.velocity.x = e->shot[i].position.velocity.x * (1 - BOT_V_SHOT) + move.x * BOT_V_SHOT;
			e->shot[i].position.velocity.y = e->shot[i].position.velocity.y * (1 - BOT_V_SHOT) + move.y * BOT_V_SHOT;
			if (bot_wall_collision(&e->shot[i].position, sector))
			{
				e->shot[i].is_alive = 0;
				e->shot[i].is_shooting = 0;
			}
			impact_player(env, &e->shot[i], (t_vtx){env->engine.player.where.x,
			env->engine.player.where.y}, damage);
			if (e->shot[i].is_shooting)
			{
				e->shot[i].position.where.x += e->shot[i].position.velocity.x;
				e->shot[i].position.where.y += e->shot[i].position.velocity.y;
			}
			else
			{
				e->ref == LOSTSOUL && e->is_alive ? e->is_dying = 1 : 0;
				ft_bzero(&e->shot[i], sizeof(t_impact));
			}
		}
		i++;
	}
}

void	bot_action(t_env *env, t_sector *sector)
{
	t_wrap_enmy	*enemy;

	(void)env;
	enemy = sector->head_enemy;
	while (enemy)
	{
		if (enemy->is_alive && !enemy->is_dying && !enemy->is_shot)
		{
			if (enemy->next && enemy->next->is_alive)
				bot_check_friend(enemy, enemy->next);
			if (enemy->is_shooting)
				bot_shoot_cadence(env, enemy, env->engine.player);
			bot_bullet(env, enemy, enemy->damage);
		}
		enemy = enemy->next;
	}
}

static void	bot_dist_detect(t_wrap_enmy *e)
{
	e->is_shooting = (e->has_detected || e->close_seen);
}

void	bot_status(t_env *env, t_vtx player, t_wrap_enmy *e, Uint8 *keycodes)
{
	t_vtx	where;

	where = (t_vtx){e->player.where.x, e->player.where.y};
	if (!env->player.actions.is_invisible && !e->is_dying && !e->is_shot)
	{
		e->is_alerted = (dist_vertex(player, where) < e->brain.dist_alert
		&& keycodes[SDL_SCANCODE_LSHIFT]);
		e->has_detected = (dist_vertex(player, where) < e->brain.dist_detect
		&& !keycodes[SDL_SCANCODE_LCTRL] && !keycodes[SDL_SCANCODE_RCTRL]);
		e->close_seen = (dist_vertex(player, where) < e->brain.dist_close);
		if (e->is_alerted || e->has_detected || e->close_seen)
		{
			if (dist_vertex(player, where) > e->brain.dist_player)
			{
				e->is_shooting = 0;
				bot_move(env, player, e, e->brain.velocity);
			}
			else
				bot_dist_detect(e);
		}
	}
	else
		e->is_shooting = 0;
}

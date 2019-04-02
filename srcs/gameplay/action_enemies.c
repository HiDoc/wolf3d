/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:32:01 by abaille           #+#    #+#             */
/*   Updated: 2019/04/02 02:03:31 by abaille          ###   ########.fr       */
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

void	bot_move(t_vtx p, t_wrap_enmy *enemy, float speed)
{
	t_vtx		move;

	enemy->player.whereto = (t_vctr){p.x, p.y, 0};
	enemy->player.angle = -p.x * 0.03f;
	enemy->player.anglesin = -sinf(enemy->player.angle);
	enemy->player.anglecos = -cosf(enemy->player.angle);
	move = bot_orientation(&enemy->player, enemy->player.whereto, speed);
	enemy->player.velocity.x = enemy->player.velocity.x * (1 - speed) + move.x * speed;
	enemy->player.velocity.y = enemy->player.velocity.y * (1 - speed) + move.y * speed;
	enemy->player.where.x += enemy->player.velocity.x;
	enemy->player.where.y += enemy->player.velocity.y;
}

void	bot_check_where(t_wrap_enmy *enemy, t_wrap_enmy *next)
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

int		action_bot_kill(int shooting, t_player *p, t_wrap_enmy* enemy)
{
	int	i;

	i = 0;
	if (shooting)
	{
		while (i < 12)
		{
			if (!enemy->shot[i].is_alive)
			{
				new_bullet(&enemy->shot[i], p, i);
				return (1);
			}
			i++;
		}
		ft_bzero(&enemy->shot[0], sizeof(t_impact));
		new_bullet(&enemy->shot[0], p, 0);
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

void	bot_new_shoot(t_wrap_enmy *enemy, t_player p)
{
	t_player	new_look;

	if (enemy->frame > 60)
	{
		new_look = bot_angle(p);
		action_bot_kill(enemy->is_shooting, &new_look, enemy);
		enemy->frame = 0;
	}
	else
		enemy->frame++;
}


void	handle_bot_bul(t_env *env, t_wrap_enmy *enemy, int damage)
{
	t_vtx		move;
	int			i;
	t_sector	*sector;

	i = 0;
	sector = &env->engine.sectors[env->engine.player.sector];
	while (i < 12)
	{
		if (enemy->shot[i].is_shooting)
		{
			move = bot_orientation(&enemy->shot[i].position, enemy->player.whereto, 0.7f);
			enemy->shot[i].position.velocity.x = enemy->shot[i].position.velocity.x * (1 - 0.7f) + move.x * 0.7f;
			enemy->shot[i].position.velocity.y = enemy->shot[i].position.velocity.y * (1 - 0.7f) + move.y * 0.7f;
			impact_collision(&enemy->shot[i], sector);
			impact_player(env, &enemy->shot[i], (t_vtx){env->engine.player.where.x,
			env->engine.player.where.y}, damage);
			if (enemy->shot[i].is_shooting)
			{
				enemy->shot[i].position.where.x += enemy->shot[i].position.velocity.x;
				enemy->shot[i].position.where.y += enemy->shot[i].position.velocity.y;
			}
			else
				ft_bzero(&enemy->shot[i], sizeof(t_impact));
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
		if (enemy->is_alive)
		{
			if (enemy->next && enemy->next->is_alive)
				bot_check_where(enemy, enemy->next);
			if (enemy->is_shooting)
				bot_new_shoot(enemy, env->engine.player);
			handle_bot_bul(env, enemy, enemy->damage);
		}
		enemy = enemy->next;
	}
}

void	bot_status(t_env *env, t_vtx player, t_wrap_enmy *enemy, Uint8 *keycodes)
{
	t_vtx	where;

	where = (t_vtx){enemy->player.where.x, enemy->player.where.y};
	if (!env->player.actions.is_invisible)
	{
		enemy->is_alerted = (dist_vertex(player, where) < 500
		&& keycodes[SDL_SCANCODE_LSHIFT]);
		enemy->has_detected = (dist_vertex(player, where) < 500
		&& !keycodes[SDL_SCANCODE_LCTRL] && !keycodes[SDL_SCANCODE_RCTRL]);
		enemy->close_seen = (dist_vertex(player, where) < 100);
		if (enemy->is_alerted || enemy->has_detected || enemy->close_seen)
		{
			if (dist_vertex(player, where) > 100)
				bot_move(player, enemy, 0.2f);
			if (dist_vertex(player, where) < 400)
				enemy->is_shooting = enemy->has_detected || enemy->close_seen;
		}
	}
}


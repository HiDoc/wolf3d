/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:32:01 by abaille           #+#    #+#             */
/*   Updated: 2019/03/30 14:17:48 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	bot_status(t_env *env, t_vtx player, t_wrap_enmy *enemy, Uint8 *keycodes)
{
	if (!env->player.actions.is_invisible)
	{
		enemy->is_alerted = (dist_vertex(player, enemy->where) < 500
		&& keycodes[SDL_SCANCODE_LSHIFT]);
		enemy->has_detected = (dist_vertex(player, enemy->where) < 200
		&& !keycodes[SDL_SCANCODE_LCTRL] && !keycodes[SDL_SCANCODE_RCTRL]);
		enemy->close_seen = (dist_vertex(player, enemy->where) < 100);
		if (enemy->is_alerted)
		{
			printf("alerted %i \n", enemy->is_alerted);

		}
		if (enemy->has_detected)
		{
			printf("detected %i \n", enemy->has_detected);
			// enemy->where = diff_vertex(enemy->origin, player);
			// printf("enemy where %f, %f\n", enemy->where.x, enemy->where.y);

		}
		if (enemy->close_seen)
			printf("close\n");
		// printf("angle cos : %f\n", env->engine.player.anglecos);
		// printf("angle sin : %f\n", env->engine.player.anglesin);
		// printf("yaw : %f\n", env->engine.player.yaw);
		// system("clear");
	}
}
// void			handle_bots(t_env *env, t_vtx player, t_wrap_enmy *enemy)
// {
// 	enemy->has_detected = dist_vertex(player, enemy->where) < 20;
// 	enemy->is_alerted
// }

// static int		is_player_ahead(t_env *env, int bot)
// {
// 	t_point		pos;
// 	double		try;

// 	pos.x = env->bots[bot]->position.x;
// 	pos.y = env->bots[bot]->position.y;

// 	try = 0.2;
// 	if (fabs(env->bots[bot]->player_angl - env->bots[bot]->direction) < 30)
// 	{
// 		while (try < env->bots[bot]->player_dist)
// 		{
// 			if (env->w_map[(int)(env->bots[bot]->position.y
// 			+ pos.y)][(int)(env->bots[bot]->position.x + pos.x)] & 0x0010)
// 				return (0);

// 			pos.x = cos(env->bots[bot]->player_angl * M_PI / 180) * try;
// 			pos.y = sin(env->bots[bot]->player_angl * M_PI / 180) * try;

// 			printf("pos.x : %f\n", pos.x);
// 			printf("pos.y : %f\n", pos.y);

// 			env->bots[bot]->debug.x = pos.x;
// 			env->bots[bot]->debug.y = pos.y;

// 			try += 0.2;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// void			handle_botssss(t_env *env)
// {
// 	t_point		last_pos;
// 	int			i;

// 	i = 0;
// 	ft_bzero(&last_pos, sizeof(t_point));
// 	while (env->bots[i])
// 	{
// 		get_player_dist(env, i);
// 		get_player_angl(env, i);
// 		if (is_player_ahead(env, i))
// 		{
// 			/*env->bots[i]->position.x +=
// 			cos(env->bots[i]->direction * M_PI / 180) * 0.05;
// 			env->bots[i]->position.y +=
// 			cos(env->bots[i]->direction * M_PI / 180) * 0.05;*/

// 			last_pos.x = env->player.pos.x;
// 			last_pos.y = env->player.pos.y;

// 			env->bots[i]->direction = env->bots[i]->player_angl;
// 			env->bots[i]->detected = 1;
// 		}
// 		else
// 			env->bots[i]->detected = 0;
// 		/*else if (env->bots[i]->detected == 1)
// 		{
// 			move_bot(env, i, last_pos);
// 			if (env->pos_x == last_pos.x
// 			&& env->pos_y == last_pos.y)
// 			{
// 				//while ( 360 degres )
// 				{
// 					rotate_bot(env, i,  //new degre);
// 					if (is_player_ahead(env, i))
// 						return ;
// 				}
// 				env->bots[i]->detected = 0;
// 				move_bot(env, i, env->bots[i]->init_pos);
// 			}
// 		}*/
// 		if (env->bots[i]->player_dist < 4)
// 		// 4 arbitraire, peut servir de niveau de difficulte
// 		{
// 			env->bots[i]->direction = env->bots[i]->player_angl;
// 			env->bots[i]->alerted = 1;
// 		}
// 		else if (env->bots[i]->alerted == 1)
// 		{
// 			env->bots[i]->direction = env->bots[i]->init_dir;
// 			env->bots[i]->alerted = 0;
// 		}
// 		i++;
// 	}
// }

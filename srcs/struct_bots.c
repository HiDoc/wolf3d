#include "wolf.h"

double			ft_pythagore(double a, double b)
{
	return (sqrt(a * a + b * b));
}

static void		get_player_dist(t_env *env, int bot)
{
	env->bots[bot]->player_dist = ft_pythagore(
	fabs(env->bots[bot]->position.x - env->player.pos.x),
	fabs(env->bots[bot]->position.y - env->player.pos.y));
}

static int		calc_angle(t_env *env, int bot)
{
	double		step_x;
	double		res;

	step_x = (double)env->player.pos.y - env->bots[bot]->position.y;
	if ((double)env->player.pos.x > env->bots[bot]->position.x)
		res = acos(step_x / env->bots[bot]->player_dist);
	else
		res = -acos(step_x / env->bots[bot]->player_dist);
	res = res * 180 / M_PI;
	return (res);
}

void			handle_bots(t_env *env)
{
	t_point		last_pos;
	int			i;

	i = 0;
	ft_bzero(&last_pos, sizeof(t_point));
	while (env->bots[i])
	{
		get_player_dist(env, i);
		// get_player_angl();
		/*if (is_player_ahead(env, i))
		{
			move_bot(env, i, env->pos);
			last_pos.x = env->pos.x;
			last_pos.y = env->pos.y;
			env->bots[i]->detected = 1;
		}
		else if (env->bots[i]->detected == 1)
		{
			move_bot(env, i, last_pos);
			if (env->pos_x == last_pos.x
			&& env->pos_y == last_pos.y)
			{
				//while ( 360 degres )
				{
					rotate_bot(env, i,  //new degre);
					if (is_player_ahead(env, i))
						return ;
				}
				env->bots[i]->detected = 0;
				move_bot(env, i, env->bots[i]->init_pos);
			}
		}*/
		if (env->bots[i]->player_dist < 4)
		// 4 arbitraire, peut servir de niveau de difficulte
		{
			env->bots[i]->direction = calc_angle(env, i);
			env->bots[i]->alerted = 1;
		}
		else if (env->bots[i]->alerted == 1)
		{
			env->bots[i]->direction = env->bots[i]->init_dir;
			env->bots[i]->alerted = 0;
		}
		i++;
	}
}

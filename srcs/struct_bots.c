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

static void		get_player_angl(t_env *env, int bot)
{
	double		step_x;
	double		res;

	step_x = (double)env->player.pos.y - env->bots[bot]->position.y;
	if ((double)env->player.pos.x > env->bots[bot]->position.x)
		res = acos(step_x / env->bots[bot]->player_dist);
	else
		res = -acos(step_x / env->bots[bot]->player_dist);
	env->bots[bot]->player_angl = (int)(res * 180 / M_PI);
}

static int		is_player_ahead(t_env *env, int bot)
{
	t_point		pos;
	double		angle_r;

	pos.x = env->bots[bot]->position.x;
	pos.y = env->bots[bot]->position.y;
	angle_r = env->bots[bot]->player_angl * M_PI / 180;

	if (fabs(env->bots[bot]->player_angl - env->bots[bot]->direction) < 30)
	{
		printf("----------------\n");
		// 24 to set relatif
		while ((int)pos.x != (int)env->player.pos.x
		&& (int)pos.y != (int)env->player.pos.y)
		{
			if (env->w_map[(int)pos.y][(int)pos.x] & 0x0010)
			{
				printf("[][][] wall [][][]\n");
				env->bots[bot]->debug.x = pos.x;
				env->bots[bot]->debug.y = pos.y;
				return (0);
			}
			pos.x = pos.x + cos(angle_r) * 0.2;
			pos.y = pos.y + sin(angle_r) * 0.2;
			printf("point : [%d][%d]\n", (int)pos.x, (int)pos.y);
		}
		env->bots[bot]->debug.x = pos.x;
		env->bots[bot]->debug.y = pos.y;
		return (1);
	}
	else
		printf("--- No detection\n");
	return (0);
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
		get_player_angl(env, i);
		if (is_player_ahead(env, i))
		{
			//move_bot(env, i, env->pos);
			//last_pos.x = env->pos.x;
			//last_pos.y = env->pos.y;
			env->bots[i]->direction = env->bots[i]->player_angl;
			env->bots[i]->detected = 1;
		}
		else
			env->bots[i]->detected = 0;
		/*else if (env->bots[i]->detected == 1)
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
			env->bots[i]->direction = env->bots[i]->player_angl;
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

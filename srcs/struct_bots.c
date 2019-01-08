#include "wolf.h"

static void		player_near_bot(t_env *env)
{
	// code
}

static int		is_player_ahead(t_env *env, int bot)
{
	// code
}

static void		rotate_bot(t_env *env, int bot, int direction)
{
	// code
}

static void		move_bot(t_env *env, int bot, t_point position)
{
	// code
}

void			handle_bots(t_env *env)
{
	t_point		last_pos;
	int			i;

	i = 0;
	ft_bzero(last_pos, sizeof(t_point));
	player_near_bot(env);
	while (env->bots[i])
	{
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
		if (env->bots[i]->heard == 1)
			rotate_bot(env, i, /* to player */);
		else
			rotate_bot(env, i, env->bots[i]->init_dir);
		i++;
	}
}

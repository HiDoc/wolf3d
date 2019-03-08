#include "doom.h"

int	loop_frames(t_env *env, int *frame)
{
	if (env->player.actions.is_shooting)
	{
		put_gun_shoot(env, *frame);
		++(*frame);
	}
	else if (env->player.actions.is_loading)
	{
		put_gun_load(env, *frame);
		++(*frame);
	}
	else
	{
		put_gun(env, env->player.inventory.current->sprite);
		*frame = 0;
	}
	return (0);
}

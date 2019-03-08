#include "doom.h"


int		give_shield(void *e, t_wrap_inv *object)
{
	t_env *env;

	env = (t_env*)e;
	if (object)
	{
		if (env->player.shield < env->player.max_shield)
		{
			env->player.shield += 50;
			if (env->player.shield > env->player.max_shield)
				env->player.shield = env->player.max_shield;
			if (object->nb_stack > 1)
				object->nb_stack--;
			else
			{
				object->is_used = 1;
				drop_object(env, object);
			}
		}
		else
			env->player.hud.is_txt = 1;
	}
	else
		env->player.hud.is_txt = 2;
	SDL_Delay(100);
	return (0);
}

int		give_health(void *e, t_wrap_inv *object)
{
	t_env *env;

	env = (t_env*)e;
	if (object)
	{
		if (env->player.health < env->player.max_health)
		{
			env->player.health += 50;
			if (env->player.health > env->player.max_health)
				env->player.health = env->player.max_health;
			if (object->nb_stack > 1)
				object->nb_stack--;
			else
			{
				object->is_used = 1;
				drop_object(env, object);
			}
		}
		else
			env->player.hud.is_txt = 3;
	}
	else
		env->player.hud.is_txt = 4;
	SDL_Delay(100);
	return (0);
}

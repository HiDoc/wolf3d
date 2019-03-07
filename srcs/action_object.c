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
			printf("Mon shield passe a %i / 200\n", env->player.shield);
			if (object->nb_stack > 1)
			{
				object->nb_stack--;
				printf("J ai bu un shield, il m'en reste %i\n", object->nb_stack);
			}
			else
			{
				object->is_used = 1;
				drop_object(env, object);
				printf("J'ai pu de shield, il disparait de l'inventaire\n");
			}
		}
		else
		{
			printf("T deja a fond poto\n");
		}
	}
	else
	{
		printf("T'en as pas\n");
	}
	
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
			printf("Mon health passe a %i / 200\n", env->player.health);
			if (object->nb_stack > 1)
			{
				object->nb_stack--;
				printf("J ai bu un health, il m'en reste %i\n", object->nb_stack);
			}
			else
			{
				object->is_used = 1;
				drop_object(env, object);
				printf("J'ai pu de health, il disparait de l'inventaire\n");
			}
		}
		else
		{
			printf("T deja a fond poto\n");
		}
	}
	else
	{
		printf("T'en as pas\n");
	}
	SDL_Delay(100);
	return (0);
}

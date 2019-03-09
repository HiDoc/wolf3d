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
			object->nb_stack > 0 ? object->nb_stack-- : 0;
			object->is_used = object->nb_stack < 1
			? drop_object(env, object) : 0;
			SDL_Delay(100);
			return (0);
		}
		return (1);
	}
	return (2);
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
			object->nb_stack > 0 ? object->nb_stack-- : 0;
			object->is_used = object->nb_stack < 1
			? drop_object(env, object) : 0;
			SDL_Delay(100);
			return (0);
		}
		return (3);
	}
	return (4);
}

int	give_ammo(void *e, t_wrap_inv *obj)
{
	t_env		*env;
	int			ref;
	int			ammo;
	t_weapon	*wpn;

	env = (t_env*)e;
	if (obj)
	{
		ammo = obj->current->ref * 10;
		ref = obj->current->ref - 2;
		wpn = env->player.inventory.weapons[ref];
		if (wpn)
		{
			ammo -= wpn->ammo_curr_max - wpn->ammo_current;
			wpn->ammo_current = wpn->ammo_curr_max;
			wpn->ammo_magazine += ammo;
			if (wpn->ammo_magazine > wpn->ammo_mag_max)
				wpn->ammo_magazine = wpn->ammo_mag_max;
			obj->nb_stack > 0 ? obj->nb_stack-- : 0;
			obj->is_used = obj->nb_stack < 1 ? drop_object(env, obj) : 0;
			SDL_Delay(100);
			return (0);
		}
		return (3);
	}
	return (4);
}
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
	int			stack;
	int			ammo;
	t_wrap_wpn	*wpn;
	t_weapon	*wpn_ref;

	env = (t_env*)e;
	if (obj)
	{
		ammo = obj->current->ref * 10;
		wpn = &env->player.inventory.weapons[obj->current->ref - 2];
		stack = wpn->ammo_current + wpn->ammo_magazine;
		wpn_ref = &env->world.armory[obj->current->ref];
		if (wpn && stack < wpn_ref->ammo_curr_max + wpn_ref->ammo_mag_max)
		{
			ammo -= wpn_ref->ammo_curr_max - wpn->ammo_current;
			wpn->ammo_current = wpn_ref->ammo_curr_max;
			wpn->ammo_magazine += ammo;
			if (wpn->ammo_magazine > wpn_ref->ammo_mag_max)
				wpn->ammo_magazine = wpn_ref->ammo_mag_max;
			obj->nb_stack > 0 ? obj->nb_stack-- : 0;
			obj->is_used = obj->nb_stack < 1 ? drop_object(env, obj) : 0;
			SDL_Delay(100);
			return (0);
		}
		return (wpn ? 9 : 10);
	}
	return (4);
}

int	give_jetpack(void *e, t_wrap_inv *obj)
{
	t_env	*env;

	env = (t_env*)e;
	if (obj)
	{
		env->player.actions.is_flying = !env->player.actions.is_flying;
		SDL_Delay(100);
		return (env->player.actions.is_flying ? 11 : 12);
	}
	return (13);
}
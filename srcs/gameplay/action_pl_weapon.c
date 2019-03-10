#include "doom.h"

int		check_weapon_type(t_env *env, int ref)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (env->player.inventory.weapons[i].current != NULL)
		{
			if (ref == env->player.inventory.weapons[i].current->ref)
				return (1);
		}
		i++;
	}
	return (0);
}

int		pick_weapon(t_env *env, t_wrap_sect *obj)
{
	int	iter;

	iter = 0;
	if (env->player.inventory.ui.nb_wpn < 3)
	{
		iter = check_weapon_type(env, obj->ref);
		if (!iter)
		{
			env->player.inventory.ui.nb_wpn++;
			env->player.inventory.weapons[obj->ref].current = obj;
			env->player.inventory.current = &env->player.inventory.weapons[obj->ref];
		}
		else
			return (14);
		obj->is_picked = 1;
		//******************************
		//******************************
		//fonction pour retirer de la map
		//******************************
		//******************************

		return (15);
	}
	return (16);
}

int		drop_wpn(t_env *env, t_wrap_wpn *wpn)
{
	t_vtx	vertex;

	if (wpn != NULL)
	{
		vertex.x = env->engine.player.where.x;
		vertex.y = env->engine.player.where.y;
		fill_objects_sector(&env->engine.sectors[env->engine.player.sector],
		vertex, wpn->current->ref, wpn->current->is_wpn);
		*wpn = (t_wrap_wpn) {NULL, 0, 0};
		env->player.inventory.ui.nb_wpn--;
	}
	env->player.hud.is_txt = 17;
	return (1);
}

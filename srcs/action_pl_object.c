#include "doom.h"


int		get_inventory_place(t_env *env)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (env->player.inventory.objects[i].current == NULL)
			return (i);
		i++;
	}
	return (i);
}

int		check_object_type(t_env *env, int ref)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (env->player.inventory.objects[i].current != NULL)
		{
			if (ref == env->player.inventory.objects[i].current->ref)
				return (i);
		}
		i++;
	}
	return (-1);
}

int		pick_object(t_env *env, t_wrap_sect *obj)
{
	int	index;
	int	iter;

	iter = 0;
	printf("on a trouve le sprite ref %i\n", obj->ref);
	if (env->player.inventory.nb_current_obj < 6)
	{
		iter = check_object_type(env, obj->ref);
		if (iter > -1)
		{
			printf("on a deja ce type d'objet ds l'inventaire, a la place %i\n", iter);
			if (env->player.inventory.objects[iter].nb_stack >= env->world.objects[obj->ref].max_stack)
			{
				printf("Mais on stack deja le max\n");
				return (0);//on stack deja le max d'objets du mm type
			}
			env->player.inventory.objects[iter].nb_stack++;
			printf("On augmente la stack de cet objet à %i\n", env->player.inventory.objects[iter].nb_stack);
		}
		else
		{
			printf("C'est le 1er objet de ce type qu'on ramasse\n");
			index = get_inventory_place(env);
			printf("L'index %i de l'inventaire est vide\n", index);
			if (!env->player.inventory.objects[index].nb_stack)
				env->player.inventory.objects[index].nb_stack = 0;
			env->player.inventory.objects[index].nb_stack++;
			env->player.inventory.objects[index].current = obj;
			printf("On a placé l'objet de ref %i dans l'inventaire et augmenté sa stack a %i\n", env->player.inventory.objects[index].current->ref, env->player.inventory.objects[index].nb_stack);
		}
		env->player.inventory.nb_current_obj++;
		obj->is_picked = 1;
		//******************************
		//******************************
		//fonction pour retirer de la map
		//******************************
		//******************************
		return (1);
	}
	else
	{
		//pas assez de place, affiche un msg
		printf("Inventaire deja plein\n");
	}
	SDL_Delay(100);
	return (0);
}

int		drop_object(t_env *env, t_wrap_inv *object)
{
	t_vtx	vertex;

	if (object->current != NULL)
	{
		if (!object->is_used)
		{
			vertex.x = env->engine.player.where.x;
			vertex.y = env->engine.player.where.y;
			fill_objects_sector(&env->engine.sectors[env->engine.player.sector], vertex, object->current->ref);
			printf("On jete un objet non utilisé, on le drop ds le secteur du player\n");
		}
		*object = (t_wrap_inv) {NULL, 0, 0, {{{0, 0}, {0, 0}}, {{0, 0}, {0, 0}}}, NULL, {0, 0}};
		printf("L'objet a ete supprimé de l'inventaire\n");
		env->player.inventory.nb_current_obj--;
	}
	return (0);
}

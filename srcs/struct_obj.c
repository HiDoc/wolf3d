#include "doom.h"

int			pick_action(t_wrap_sect *new)
{
	if (new->ref == 0)
		new->action = &give_health;
	else if (new->ref == 1)
		new->action = &give_shield;
	// else if (new->ref == 2 || new->ref == 3)
	// 	new->action = &give_ammo;
	return (0);
}

t_wrap_sect	*new_wrap(t_vtx curr, int ref)
{
	t_wrap_sect *new;

	if (!(new = malloc(sizeof(t_wrap_sect))))
		return (NULL);
	new->ref = ref;
	new->vertex = curr;
	new->is_picked = 0;
	new->next = NULL;
	pick_action(new);
	return (new);
}

int		fill_objects_sector(t_sector *sector, t_vtx v, int ref)
{
	t_wrap_sect *iter;

	iter = NULL;
	if (sector->head_object == NULL)
		sector->head_object = new_wrap(v, ref);
	else
	{
		iter = sector->head_object;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new_wrap(v, ref);
	}
	return (0);
}


SDL_Surface *img_consumable(char *filename)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".png";

	path = ft_strjoin("./rsrc/img/consumable/", filename);
	path = ft_strljoin(path, (char *)png);
	new = create_surf(path);
	free(path);
	path = NULL;
	return (new);
}


int         object_new(t_object *new, char *filename, int max_stack)
{
    new->max_stack = max_stack;
	if ((new->sprite = img_consumable(filename)))
	    return (1);
    return (0);
}

int		init_inventory(t_env *env)
{
	int i;

	i = 0;
	while (i < 6)
	{
		env->player.inventory.objects[i] = (t_wrap_inv) {NULL, 0, 0};
		i++;
	}
	env->player.inventory.is_active = 0;
	return (0);
}

int         init_consumable(t_env *env)
{
	return (object_new(&env->world.objects[0], "health", 3)
	&& object_new(&env->world.objects[1], "shield", 3)
	&& object_new(&env->world.objects[2], "ammo_1", 5)
	&& object_new(&env->world.objects[3], "ammo_2", 5)
	&& object_new(&env->world.objects[4], "ammo_3", 5)
	&& object_new(&env->world.objects[5], "jetpack", 1)
	&& init_inventory(env));
}

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

int		drop_object(t_engine *e, t_env *env, t_wrap_inv *object)
{
	t_vtx	vertex;

	if (object->current != NULL)
	{
		if (!object->is_used)
		{
			vertex.x = e->player.where.x;
			vertex.y = e->player.where.y;
			fill_objects_sector(&e->sectors[e->player.sector], vertex, object->current->ref);
			printf("On jete un objet non utilisé, on le drop ds le secteur du player\n");
		}
		*object = (t_wrap_inv) {NULL, 0, 0};
		printf("L'objet a ete supprimé de l'inventaire\n");
		env->player.inventory.nb_current_obj--;
	}
	return (0);
}

int		give_shield(void *e, t_wrap_inv *object)
{
	t_env *env;

	env = (t_env*)e;
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
			drop_object(e, env, object);
			printf("J'ai pu de shield, il disparait de l'inventaire\n");
		}
	}
	else
	{
		printf("T deja a fond poto\n");
	}

	SDL_Delay(100);
	return (0);
}

int		give_health(void *e, t_wrap_inv *object)
{
	t_env *env;

	env = (t_env*)e;
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
			drop_object(e, env, object);
			printf("J'ai pu de health, il disparait de l'inventaire\n");
		}
	}
	else
	{
		printf("T deja a fond poto\n");
	}

	SDL_Delay(100);
	return (0);
}

void	surface_drawrect(SDL_Surface *surface, t_edge edge, Uint32 color)
{
	int		i;
	int		j;

	i = edge.v1.x;
	while (i < edge.v2.x)
	{
		j = edge.v1.y;
		while (j < edge.v2.y)
		{
			setpixel(surface, i, j, color);
			j++;
		}
		i++;
	}
}

int			select_object(t_env *env, int x, int y, t_edge *p)
{
	int i = 0;
	(void)env;
	while (i < 6)
	{
		if (x >= p[i].v1.x && x <= p[i].v2.x && y >= p[i].v1.y && y <= p[i].v2.y)
			printf("ok\n");
		i++;
	}
	return (0);
}

int			set_inventory(t_env *env)
{
	int	x;
	int	y;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_GetRelativeMouseState(&x,&y);
	print_inventory(env, &env->player.inventory, x, y);
	return (0);
}
int			print_inventory(t_env *env, t_inventory *inventory, int x, int y)
{
	(void)inventory;
	(void)env;
	t_edge	edge;
	t_edge	p0[6];
	edge.v1 = (t_vtx){0, 0};
	edge.v2 = (t_vtx){env->engine.surface->w / 2, env->engine.surface->h};
	surface_drawrect(env->engine.surface, edge, SDL_MapRGB(env->engine.surface->format, 255, 0, 0));
	p0[0].v1 = (t_vtx){10, 10};
	p0[0].v2 = (t_vtx){60, 60};
	surface_drawrect(env->engine.surface, p0[0], 0x88888888);
	p0[1].v1 = (t_vtx){80, 10};
	p0[1].v2 = (t_vtx){130, 60};
	surface_drawrect(env->engine.surface, p0[1], 0x88888888);
	p0[1].v1 = (t_vtx){150, 10};
	p0[1].v2 = (t_vtx){200, 60};
	surface_drawrect(env->engine.surface, p0[1], 0x88888888);

	select_object(env, x, y, p0);
	return (0);
}

// int		give_ammo(t_engine e, t_env *env, t_wrap_inv *object)
// {

// 	return (0);
// }

// int		use_object(t_env *env, t_wrap_inv *object)
// {

// 	return (0);
// }
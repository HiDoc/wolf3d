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
			drop_object(env, object);
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
			drop_object(env, object);
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

int			select_object(t_wrap_inv *object, int x, int y, t_edge *p)
{
	int i;
	
	i = 0;
	while (i < 6)
	{
		if (x >= p[i].v1.x && x <= p[i].v2.x && y >= p[i].v1.y && y <= p[i].v2.y)
		{
			if (object[i].current)
				return (i);
			else
				printf("Emplacement vide %i\n", i);
		}
		i++;
	}
	return (-1);
}

void	surface_draw_img(SDL_Surface *surface, t_edge edge, SDL_Surface *img)
{
	int		i;
	int		j;
	int		x;
	int		y;
	Uint32	c;

	SDL_LockSurface(surface);
	x = 0;
	i = edge.v1.x;
	while (i < edge.v2.x)
	{
		y = 0;
		j = edge.v1.y;
		while (j < edge.v2.y)
		{
			c = getpixel(img, x, y);
			setpixel(surface, i, j, c);
			// setpixel(surface, i, j, c) : setpixel(surface, i, j, 0x88888888);
			j++;
			y++;
		}
		x++;
		i++;
	}
	SDL_UnlockSurface(surface);
}
void		put_img(t_env *env, SDL_Surface *img, t_edge bloc)
{
	SDL_Rect	rect;
	int			x;
	int			y;
	SDL_Surface	*new;
	t_vtx		scale;
	Uint32		*pix;
	Uint32		*image;

	rect.w = bloc.v2.x - bloc.v1.x;
	rect.h = bloc.v2.y - bloc.v1.y;
	rect.y = bloc.v1.y;
	rect.x = bloc.v1.x;
	x = 0;
	if (img)
	{
		scale.x = (float)img->w / (float)rect.w;
		scale.y = (float)img->h / (float)rect.h;
		new = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0xff000000, 0xff0000, 0xff00, 0xff);
		SDL_LockSurface(new);
		pix = new->pixels;
		image = img->pixels;
		while (x < rect.w)
		{
			y = 0;
			int sx = x * scale.x;
			while (y < rect.h)
			{
				int sy = y * scale.y;
				Uint32 p = image[(int)(img->w * sy + sx)];
				p = ((p & 0xFF) << 24) + (((p & 0xFF00) >> 8) << 16) + (((p & 0xFF0000) >> 16) << 8) + (((p & 0xFF000000) >> 24));
				pix[rect.w * y + x] = p;
				y++;
			}
			x++;
		}
		SDL_UnlockSurface(new);
		surface_draw_img(env->engine.surface, bloc, new);
	}
}


int			fill_bloc(t_env *env, t_edge *bloc, t_vtx *n, int i)
{
	int inter;
	int sbloc;

	inter = W / 2 / 4 / 4 / 4;
	sbloc = W / 2 / 3 - inter;
	bloc->v1 = (t_vtx){n->x, n->y};
	n->x += sbloc;
	n->y = i < 3 ? sbloc + inter : (sbloc + inter) * 2;
	bloc->v2 = (t_vtx){n->x, n->y};
	if (env->player.inventory.objects[i].current)
		put_img(env, env->world.objects[env->player.inventory.objects[i].current->ref].sprite, *bloc);
	else
		surface_drawrect(env->engine.surface, *bloc, 0x88888888);
	n->x = i == 2 ? inter : n->x + inter;
	n->y = i < 2 ? inter : inter * 2 + sbloc;
	return (1);
}

int			select_action(t_edge *p, int x, int y)
{
	int i;
	
	i = 0;
	while (i < 2)
	{
		if (x >= p[i].v1.x && x <= p[i].v2.x && y >= p[i].v1.y && y <= p[i].v2.y)
			return (i);
		i++;
	}
	return (-1);
}

int			sub_action(t_env *env, t_edge bloc, int index, int x, int y)
{
	t_edge	sbloc[2];
	int		iter;
	SDL_Event	ev;
	
	sbloc[0].v1.x = bloc.v2.x / 2;
	sbloc[0].v1.y = bloc.v2.y - bloc.v2.y / 2;
	sbloc[0].v2.x = bloc.v2.x + bloc.v2.x / 2;
	sbloc[0].v2.y = bloc.v2.y - bloc.v2.y / 4;
	surface_drawrect(env->engine.surface, sbloc[0], 0xFF00FF00);
	sbloc[1].v1.x = bloc.v2.x;
	sbloc[1].v1.y = bloc.v2.y - bloc.v2.y / 4;
	sbloc[1].v2.x = sbloc[1].v1.x + bloc.v2.x / 2;
	sbloc[1].v2.y = bloc.v2.y;
	surface_drawrect(env->engine.surface, sbloc[1], 0xF0F0F0F0);
	// SDL_FlushEvents(SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP);
	SDL_WaitEvent(&ev);
	if (ev.type == SDL_MOUSEBUTTONDOWN && index > -1 && SDL_GetMouseState(&x, &y))
	{
		if ((iter = select_action(sbloc, x, y)) == 0)
			env->player.inventory.objects[index].current->action((void*)env, &env->player.inventory.objects[index]);
		else if ((iter = select_action(sbloc, x, y)) == 1)
			drop_object(env, &env->player.inventory.objects[index]);
		env->player.actions.sub_action = 0;
		SDL_FlushEvents(SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP);
	}
	return (0);
}



int			print_inventory(t_env *env, int x, int y)
{
	t_edge	edge;
	t_edge	bloc[6];
	t_vtx	n;
	int		iter;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	n = (t_vtx){W / 2 / 4 / 4 / 4, W / 2 / 4 / 4 / 4};
	iter = 0;
	edge.v1 = (t_vtx){0, 0};
	edge.v2 = (t_vtx){env->engine.surface->w / 2, env->engine.surface->h};
	surface_drawrect(env->engine.surface, edge, SDL_MapRGB(env->engine.surface->format, 0, 0, 0));
	while (iter < 6)
		iter += fill_bloc(env, &bloc[iter], &n, iter);
	iter = -1;	
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))
		iter = select_object(env->player.inventory.objects, x, y, bloc);
	if (iter > -1)
	{
		env->player.actions.sub_action = 1;
		env->player.actions.edge = bloc[iter];
	}
	while (env->player.actions.sub_action)
		sub_action(env, env->player.actions.edge, iter, 0, 0);
	SDL_Delay(100);
	return (0);
}

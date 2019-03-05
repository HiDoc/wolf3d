#include "doom.h"

int	select_action(t_edge *p, int x, int y)
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

int	select_object(t_wrap_inv *object, int x, int y, t_edge *p)
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

int	action_inventory(t_env *env, int x, int y)
{
	int	iter;
	int index;
	SDL_Surface	*drag_sprite;

	iter = -1;
	index = -1;
	drag_sprite = NULL;
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))
	{
		if ((index = select_object(env->player.inventory.objects, x, y, env->player.inventory.blocs)) > -1)
		{
			if ((iter = select_action(env->player.inventory.objects[index].udbox, x, y)) == 1)
				env->player.inventory.objects[index].current->action((void*)env, &env->player.inventory.objects[index]);
			else if ((iter = select_action(env->player.inventory.objects[index].udbox, x, y)) == 0)
				drop_object(env, &env->player.inventory.objects[index]);
		}
	}
	SDL_Delay(100);
	return (0);
}

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

int		obj_inv_collide(t_env *env, int index)
{
	int	i;
	t_wrap_sect *tmp;

	tmp = NULL;
	i = 0;
	while(i < 6)
	{
		if (intersect_rect(env->player.inventory.objects[index].where_img.v1,
		env->player.inventory.objects[index].where_img.v2, env->player.inventory.blocs[i].v1,
		env->player.inventory.blocs[i].v2))
		{
			tmp = env->player.inventory.objects[index].current;
			env->player.inventory.objects[index].current = env->player.inventory.objects[i].current;
			env->player.inventory.objects[i].current = tmp;
			printf("collide\n");
			return (1);
		}
		i++;
	}
	env->player.inventory.objects[index].mmotion.x = 0;
	env->player.inventory.objects[index].mmotion.y = 0;
	env->player.inventory.objects[index].where_img.v1 = env->player.inventory.blocs[i].v1;
	env->player.inventory.objects[index].where_img.v2 = env->player.inventory.blocs[i].v2;
	return (0);
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
			else
			{
				// env->player.inventory.objects[index].is_dragged = 1;
				drag_sprite = env->player.inventory.objects[index].curr_img;
			}
		}
	}
	if (env->player.inventory.objects[index].is_dragged)
	{
		if (drag_sprite)
		{
			SDL_GetRelativeMouseState(&x, &y);
			printf("mmotion x %i\n", env->player.inventory.objects[index].mmotion.x);
			printf("mmotion y %i\n", env->player.inventory.objects[index].mmotion.y);
			env->player.inventory.objects[index].mmotion.x += x;
			env->player.inventory.objects[index].mmotion.y += y;
			if (env->player.inventory.objects[index].mmotion.x < 0)
				env->player.inventory.objects[index].mmotion.x = 0;
			if (env->player.inventory.objects[index].mmotion.x > W / 2)
				env->player.inventory.objects[index].mmotion.x = W / 2 - 1;
			if (env->player.inventory.objects[index].mmotion.y < 0)
				env->player.inventory.objects[index].mmotion.y = 0;
			if (env->player.inventory.objects[index].mmotion.y > H)
				env->player.inventory.objects[index].mmotion.y = H - 1;
		}
		env->player.inventory.objects[index].is_dragged = 0;
		obj_inv_collide(env, index);
	}
	SDL_Delay(100);
	return (0);
}

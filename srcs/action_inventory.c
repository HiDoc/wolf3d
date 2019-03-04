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
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))
	{
		if ((index = select_object(env->player.inventory.objects, x, y, env->player.inventory.blocs)) > -1)
		{
			if ((iter = select_action(env->player.inventory.objects[index].udbox, x, y)) == 1)
				env->player.inventory.objects[index].current->action((void*)env, &env->player.inventory.objects[index]);
			else if ((iter = select_action(env->player.inventory.objects[index].udbox, x, y)) == 0)
				drop_object(env, &env->player.inventory.objects[index]);
			else if (env->player.inventory.objects[index].curr_img)
				drag_sprite = env->player.inventory.objects[index].curr_img;
		}
	}
	if (env->sdl.event.type == SDL_MOUSEMOTION)
	{
		if (drag_sprite)
		{
			env->player.inventory.objects[index].mmotion.x += env->sdl.event.motion.xrel;
			env->player.inventory.objects[index].mmotion.y += env->sdl.event.motion.yrel;
		}
	}
	SDL_Delay(100);
	return (0);
}



// Sprite* mySprites = getMySpriteArray(); 
// int numSprites = getNumSprites(); 

// Sprite* dragSprite = NULL; 

// while(!done) 
// { 
// while(SDL_PollEvent(&event)) 
// { 
// if(event.type == SDL_MOUSE_BUTTON_DOWN) 
// { 
// // This should loop over all the sprites available for grabbing 
// for(int i = 0; i < numSprites; i++) 
// { 
// if(isInBoundingRegion(event.button.x, event.button.y, 
// mySprites[i])) 
// dragSprite = mySprites[i]; 
// else 
// dragSprite = NULL; 
// } 
// } 
// else if(event.type == SDL_MOUSE_BUTTON_UP) 
// { 
// dragSprite = NULL; 
// } 
// else if(event.type == SDL_MOUSE_MOTION) 
// { 
// if(dragSprite != NULL) 
// { 
// dragSprite->x += event.motion.xrel; 
// dragSprite->y += event.motion.yrel; 
// } 
// } 
// } 


// // ... Draw and flip 
// } 
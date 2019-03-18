#include "doom.h"

void		free_img(SDL_Surface *sprite)
{
	if (sprite)
	{
		SDL_FreeSurface(sprite);
		sprite = NULL;
	}
}

void		free_world_img(t_world *world)
{
	int	i;
	int	j;

	i = 0;
	while (i < WORLD_NB_OBJECTS)
	{
		if (i < WORLD_NB_WEAPONS)
		{
			j = 0;
			while (j < world->armory[i].time_reload)
			{
				free_img(world->armory[i].sprite_reload[j]);
				j++;
			}
			free_img(world->armory[i].sprite);
			free_img(world->armory[i].sprite_shoot);
			free_img(world->armory[i].sprite_bullet);
		}
		free_img(world->objects[i].sprite);
		i++;
	}
}

void		free_inventory_img(t_uinv *ui)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_OBJECTS)
	{
		if (i < WORLD_NB_WEAPONS)
		{
			free_img(ui->mini_wpn[i]);
			free_img(ui->empt_wpn[i]);
		}
		if (i < 2)
		{
			free_img(ui->box[i]);
			free_img(ui->icon[i]);
		}
		i++;
	}
	free_img(ui->front_pic);
}

void		free_hud(t_hud *hud)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_OBJECTS)
	{
		free_img(hud->objects[i]);
		if (i < 4)
			free_img(hud->faces[i]);
		if (i < WORLD_NB_WEAPONS)
			free_img(hud->hud_wpn[i]);
		if (i < 2)
			free_img(hud->bar[i]);
		i++;
	}
	free_img(hud->empty_b);
	free_img(hud->full_b);
}

void		free_all_sprites(t_env *env)
{
	free_hud(&env->player.hud);
	free_inventory_img(&env->player.inventory.ui);
	free_world_img(&env->world);
}

void		UnloadData(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Window *window, t_engine *e)
{
	unsigned	a;
	t_wrap_sect	*b;

	a = 0;
	while (a < e->nsectors)
	{
		free(e->sectors[a].vertex);
		free(e->sectors[a].neighbors);
		b = e->sectors[a].head_object;
		while (b != NULL)
		{
			e->sectors[a].head_object = b->next;
			free(b);
			b = e->sectors[a].head_object;
		}
		a++;
	}
	free(e->sectors);
	e->sectors = NULL;
	e->nsectors = 0;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	texture = NULL;
	window = NULL;
	renderer = NULL;
}
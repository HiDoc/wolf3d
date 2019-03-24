#include "doom.h"

void	free_fonts(t_uitxt *f)
{
	TTF_CloseFont(f->arial);
	TTF_CloseFont(f->doom);
	TTF_CloseFont(f->text);
	TTF_CloseFont(f->number);
}

void		free_wpn_sounds(t_world *world)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_WEAPONS)
	{
		Mix_FreeChunk(world->armory[i].shot);
		i++;
	}
}

void		free_all_sounds(t_env *env)
{
	free_wpn_sounds(&env->world);
}

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
				if (world->armory[i].sprite_reload)
					free_img(world->armory[i].sprite_reload[j].sprite);
				j++;
			}
			j = 0;
			while (j < world->armory[i].time_shoot)
			{
				if (world->armory[i].sprite_shoot)
					free_img(world->armory[i].sprite_shoot[j].sprite);
				j++;
			}
			free_img(world->armory[i].sprite.sprite);
			free_img(world->armory[i].sprite_bullet.sprite);
		}
		free_img(world->objects[i].sprite);
		i++;
	}
}

void		free_hud(t_container *surface)
{
	int	i;

	i = 0;
	while (i < NB_HUD_OBJ)
	{
		free_img(surface->hud[i]);
	}
}

void		free_surface_string(t_uitxt*ui)
{
	int i;

	i = 0;
	while (i < UI_NB_STRING - UI_NB_STR_INV)
	{
		free_img(ui->string[i]);
		if (i < UI_NB_STR_INV)
			free_img(ui->t_inv[i]);
		i++;
	}
}

void		free_ui(t_env *env)
{
	free_hud(&env->world.surfaces);
	// free_inventory_img(&env->player.inventory.ui);
	free_world_img(&env->world);
	// free_all_sounds(env);
	free_fonts(&env->player.hud.text);
	free_surface_string(&env->player.hud.text);
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
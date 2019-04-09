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

	i = -1;
	while (++i < WORLD_NB_WEAPONS)
		Mix_FreeChunk(world->armory[i].shot);
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

void		free_obj_wpn_img(t_world *world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WORLD_NB_OBJECTS)
	{
		if (i < WORLD_NB_WEAPONS)
		{
			j = -1;
			while (++j < world->armory[i].time_reload)
			{
				if (world->armory[i].sprite_reload)
					free_img(world->armory[i].sprite_reload[j].sprite);
			}
			free(world->armory[i].sprite_reload);
			j = -1;
			while (++j < world->armory[i].time_shoot)
			{
				if (world->armory[i].sprite_shoot)
					free_img(world->armory[i].sprite_shoot[j].sprite);
			}
			free(world->armory[i].sprite_shoot);
			free_img(world->armory[i].sprite.sprite);
			free_img(world->armory[i].sprite_bullet.sprite);
		}
		free_img(world->objects[i].sprite);
	}
}

void		free_hud(t_container *surface)
{
	int	i;

	i = -1;
	while (++i < NB_HUD_OBJ)
		free_img(surface->hud[i].sprite);
}

void		free_surface_string(t_uitxt *ui)
{
	int i;

	i = -1;
	while (++i < UI_NB_STRING)
		free_img(ui->string[i]);
	i = -1;
	while (++i < DSCRIP_STR_INV)
		free_img(ui->i_obj_description[i]);
	i = -1;
	while (++i < 2)
		free_img(ui->doors[i]);
}

void		free_posters(t_container *surface)
{
	int	i;

	i = -1;
	while (++i < WORLD_NB_POSTERS)
		free_img(surface->poster[i].sprite);
}

void		free_walls(t_container *surface)
{
	int	i;

	i = -1;
	while (++i < WORLD_NB_WALLS)
		free_img(surface->walls[i].sprite);
}

void		free_enemies(t_world *world)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WORLD_NB_ENEMIES)
	{
		j = -1;
		while (++j < 6)
			free_img(world->enemies[i].sprites[j]);
	}
}

void		free_doors(t_container *surface)
{
	int	i;

	i = -1;
	while (++i < NB_DOOR_IMG)
		free_img(surface->doors[i].sprite);
}

void		free_world_surfaces(t_container *surface)
{
	free_posters(surface);
	free_walls(surface);
	free_hud(surface);
	free_doors(surface);
}

void		free_ui(t_env *env)
{
	free_fonts(&env->hud.text);
	free_surface_string(&env->hud.text);
	free_world_surfaces(&env->world.surfaces);
	free_obj_wpn_img(&env->world);
	free_enemies(&env->world);
	// free_all_sounds(env);
}


void		free_env(t_env *env)
{
	unsigned	a;
	t_engine	*e;
	t_wrap_sect	*b;
	t_wrap_enmy	*en;

	a = 0;
	e = &env->engine;
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
		en = e->sectors[a].head_enemy;
		while (en != NULL)
		{
			e->sectors[a].head_enemy = en->next;
			free(en->shot);
			free(en);
			en = e->sectors[a].head_enemy;
		}
		a++;
	}
	free(e->queue.renderedsectors);
	free(e->sectors);

	free(env->player.bullet);
	if (env->player.shot)
		free(env->player.shot);
	e->sectors = NULL;
	e->nsectors = 0;
	SDL_DestroyTexture(env->sdl.texture);
	SDL_DestroyRenderer(env->sdl.renderer);
	SDL_DestroyWindow(env->sdl.window);
	env->sdl.texture = NULL;
	env->sdl.window = NULL;
	env->sdl.renderer = NULL;
	free_ui(env);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}
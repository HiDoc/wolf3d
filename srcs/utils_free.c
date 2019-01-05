#include "wolf.h"

void	hub_free(t_hub *hub)
{
	if (hub->surface != NULL)
		SDL_FreeSurface(hub->surface);
	if (hub->img != NULL)
		SDL_FreeSurface(hub->img);
	if (hub->texture != NULL)
		SDL_DestroyTexture(hub->texture);
}

void	env_surface_free(SDL_Surface **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		SDL_FreeSurface(tab[i]);
		i++;
	}
}

void	wobj_free(t_wobj *obj)
{
	int	i;
	i = 0;
	if (obj->simpact)
		SDL_FreeSurface(obj->simpact);
	env_surface_free(obj->posters);
	env_surface_free(obj->wposters);
}

void	sdl_free(t_sdl *sdl)
{
	SDL_FreeSurface(sdl->surface);
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyRenderer(sdl->renderer);
	SDL_DestroyWindow(sdl->window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	SDL_Quit();
}

int		env_free(t_env *env)
{
	int i;

	i = 0;
	env_surface_free((SDL_Surface **)env->walls);
	env_surface_free((SDL_Surface **)env->ak_frms);
	env_surface_free((SDL_Surface **)env->bul_surf);
	env_surface_free((SDL_Surface **)env->stitch);
	wobj_free(&env->wobj);
	if (env->w_map)
		tab_free(env->w_map, 24);
	if (env->floor)
		SDL_FreeSurface(env->floor);
	if (env->sky)
		SDL_FreeSurface(env->sky);
	if (env->gun_impact)
		SDL_FreeSurface(env->gun_impact);
	Mix_FreeChunk(env->sounds.shot);
	Mix_CloseAudio();
	TTF_Quit();
	hub_free(&env->lscreen);
	hub_free(&env->title);
	hub_free(&env->life);
	sdl_free(&env->sdl);
	return (1);
}
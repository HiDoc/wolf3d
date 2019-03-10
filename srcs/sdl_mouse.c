#include "doom.h"

int	mouse_shoot(t_env *env)
{
    int x;
    int y;

    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1)
	&& env->player.inventory.current
	&& !env->player.inventory.ui.is_active
	&& !env->player.actions.is_loading)
	{
		if (env->player.inventory.current->ammo_current)
		{
			env->player.actions.is_shooting = 1;
			// Mix_PlayChannel(-1, env->sounds.shot, 0);
			env->player.inventory.current->ammo_current--;
			SDL_Delay(150);
		}
		else
			load_weapon(env);
	}
	SDL_FlushEvent(SDL_MOUSEBUTTONUP);
	return (0);
}
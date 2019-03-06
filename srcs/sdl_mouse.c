#include "doom.h"

int	mouse_shoot(t_env *env)
{
    int x;
    int y;

    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1) && !env->player.inventory.ui.is_active)
	    env->player.actions.is_shooting = 1;
	Mix_PlayChannel(-1, env->sounds.shot, 0);
	SDL_FlushEvent(SDL_MOUSEBUTTONUP);
	return (0);
}
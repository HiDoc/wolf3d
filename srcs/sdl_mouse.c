#include "wolf.h"

int	mouse_shoot(t_env *env)
{
	//wall_impact(env);
	env->player.actions.is_shooting = 1;
	//SDL_FlushEvent(SDL_MOUSEBUTTONDOWN | SDL_MOUSEBUTTONUP);
	Mix_PlayChannel(-1, env->sounds.shot, 0);
	return (0);
}

int	sdl_mouse_click(t_env *env, int x, int y)
{
	(void)x;
	(void)y;
	mouse_shoot(env);
	return (0);
}

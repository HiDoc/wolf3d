#include "wolf.h"

int	mouse_shoot(t_env *env)
{
	wall_impact(env);
	Mix_PlayChannel(-1, env->sounds.shot, 0);
	return (0);
}

int	sdl_mouse_click(t_env *env, int x, int y)
{
	(void)x;
	(void)y;
	mouse_shoot(env);
	init_thread(env);
	return (0);
}
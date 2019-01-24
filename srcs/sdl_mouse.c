#include "wolf.h"

int	mouse_shoot(t_env *env)
{
	t_line	line;

	line_init(env, &line, env->w_map, 400);
	env->player.actions.is_shooting = 1;
	Mix_PlayChannel(-1, env->sounds.shot, 0);
	SDL_FlushEvent(SDL_MOUSEBUTTONUP);
	return (0);
}

int	sdl_mouse_click(t_env *env, int x, int y)
{
	(void)x;
	(void)y;
	mouse_shoot(env);
	return (0);
}

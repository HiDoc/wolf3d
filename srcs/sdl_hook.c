#include "wolf.h"

int		sdl_exit_wolf(t_env *env, Uint8 keycode)
{
	if (keycode == SDL_SCANCODE_ESCAPE)
	{
		Mix_FreeChunk(env->sounds.shot);
		Mix_FreeMusic(env->sounds.load);
		Mix_CloseAudio();
		TTF_Quit();
		env_free(env);
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
		SDL_Quit();
		exit(0);
	}
	return (0);
}

static int sdl_check_pos(t_env *env, t_point mult, float check)
{
	int x;
	int y;

	x = env->pos.x + mult.x * check;
	y = env->pos.y;
	env->w_map[x][y] == 0 ? env->pos.x += mult.x * check : 0;
	x = env->pos.x;
	y = env->pos.y + mult.y * check;
	env->w_map[x][y] == 0 ? env->pos.y += mult.y * check : 0;
	return (1);
}

int		sdl_move(t_env *env, Uint8 *keycodes)
{
	if (keycodes[SDL_SCANCODE_W])
		sdl_check_pos(env, env->dir, 0.1);
	if (keycodes[SDL_SCANCODE_S])
		sdl_check_pos(env, env->dir, -0.1);
	if (keycodes[SDL_SCANCODE_D])
		sdl_check_pos(env, env->plane, 0.1);
	if (keycodes[SDL_SCANCODE_A])
		sdl_check_pos(env, env->plane, -0.1);
	if (keycodes[SDL_SCANCODE_V])
	{
		if (env->hratio <= 1.1)
			env->is_jump = 1;
		if (env->is_jump == 1)
		{
			env->is_updn += 20;
			env->hratio += 0.1;
		}
		else
		{
			env->is_updn -= 20;
			env->hratio -= 0.1;
		}
		if (env->hratio >= 2 && env->is_jump == 1)
			env->is_jump = 0;
	}
	return (0);
}

int		sdl_motion_mouse(t_env *env, int x, int y)
{
	double	mult;

	mult = x < 0 ? 4.0 : -4.0;
	env->dir = point_rotate(env->dir, mult);
	env->plane = point_rotate(env->plane, mult);
	env->pang += mult;
	env->pang > 358.0 ? env->pang = 0.0 : 0;
	env->pang < 0.0 ? env->pang = 358.0 : 0;
	if (y > 20)
	{
		if (env->is_updn > -400)
			env->is_updn -= 20;
	}
	else if (y < -20)
	{
		if (env->is_updn < 400)
			env->is_updn += 20;
	}
	return (0);
}

int	shooter(t_env *env, Uint8 *keycodes)
{
	if (keycodes[SDL_SCANCODE_X])
	{
		Mix_PlayChannel(-1, env->sounds.shot, 0);
	}
	return (0);
}

int sdl_keyhook(t_env *env, SDL_Event event)
{
	Uint8	keycode;
	Uint8	*keycodes;

	keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	keycode = event.key.keysym.scancode;
	sdl_move(env, (Uint8 *)keycodes);
	shooter(env, (Uint8 *)keycodes);
	sdl_exit_wolf(env, keycode);
	return (0);

}

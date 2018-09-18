#include "wolf.h"

int		sdl_exit_wolf(t_env *env, Uint8 keycode)
{
	if (keycode == SDL_SCANCODE_ESCAPE)
	{
		free_env(env);
		exit(0);
	}
	return (0);
}

t_point	sdl_rotate(t_point v, int ang)
{
	float	radian;
	t_point	r;

	radian = ang / 180.0 * 3.141;
	r.x = v.x * cos(radian) - v.y * sin(radian);
	r.y = v.x * sin(radian) + v.y * cos(radian);
	return (r);
}

static int sdl_check_pos(t_env *env, t_point mult, float check, char pos)
{
	int x;
	int y;

	if (pos == 'x')
	{
		x = env->pos.x + mult.x * check;
		y = env->pos.y;
		env->w_map[x][y] == 0 ? env->pos.x += mult.x * (check / 2.0) : 0;
	}
	else
	{
		x = env->pos.x;	
		y = env->pos.y + mult.y * check;
		env->w_map[x][y] == 0 ?  env->pos.y += mult.y * (check / 2.0) : 0;
	}
	return (0);
}

int		sdl_move(t_env *env, Uint8 keycode)
{
	if (keycode == SDL_SCANCODE_W)
	{
		sdl_check_pos(env, env->dir, 0.2, 'x');
		sdl_check_pos(env, env->dir, 0.2, 'y');
	}
	if (keycode == SDL_SCANCODE_S)
	{
		sdl_check_pos(env, env->dir, -0.2, 'x');
		sdl_check_pos(env, env->dir, -0.2, 'y');
	}
	if (keycode == SDL_SCANCODE_A)
	{
		sdl_check_pos(env, env->plane, -0.2, 'x');
		sdl_check_pos(env, env->plane, -0.2, 'y');
	}
	if (keycode == SDL_SCANCODE_D)
	{
		sdl_check_pos(env, env->plane, 0.2, 'x');
		sdl_check_pos(env, env->plane, 0.2, 'y');
	}
	return (0);
}

int		sdl_motion_mouse(t_env *env, int x, int y)
{
	double	mult;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		mult = (x < 400 ? 1.0 : -1.0);
		env->dir = sdl_rotate(env->dir, mult * env->ang);
		env->plane = sdl_rotate(env->plane, mult * env->ang);
		env->pang += mult * 2.0;
		env->pang > 358.0 ? env->pang = 0.0 : 0;
		env->pang < 0.0 ? env->pang = 358.0 : 0;
		if (y > 300)
		{
			if (env->is_updn > -300)
				env->is_updn -= 10;
		}
		else if (y < 300)
		{
			if (env->is_updn < 300)
				env->is_updn += 10;
		}
		init_thread(env);
	}
	return (0);
}

int sdl_keyhook(t_env *env, SDL_Event event)
{
	Uint8	keycode;

	keycode = event.key.keysym.scancode;
	sdl_move(env, keycode);
	sdl_exit_wolf(env, keycode);
	init_thread(env);
	return (0);
}

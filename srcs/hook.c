#include "wolf.h"

int		exit_wolf(t_env *env)
{
	mlx_destroy_image(E_MLX, E_IMG);
	mlx_destroy_window(E_MLX, E_WIN);
	free_env(env);
	exit(0);
	return (0);
}

t_point	rotate_up(t_point v, int ang)
{
	float	radian;
	t_point	r;

	radian = ang / 180.0 * 3.141;
	r.x = v.x * cos(radian) - v.y * sin(radian);
	r.y = v.x * sin(radian) + v.y * cos(radian);
	return (r);
}

t_point	rotate(t_point v, int ang)
{
	float	radian;
	t_point	r;

	(void)rotate_up;
	radian = ang / 180.0 * 3.141;
	r.x = v.x * cos(radian) - v.y * sin(radian);
	r.y = v.x * sin(radian) + v.y * cos(radian);
	return (r);
}

int		moove(int key, t_env *env)
{
	if (key == KEY_UP)
	{
		if (env->w_map[(int)(env->pos.x + env->dir.x * 0.1)][(int)env->pos.y] == 0)
			env->pos.x += env->dir.x * 0.1;
		if (env->w_map[(int)env->pos.x][(int)(env->pos.y + env->dir.y * 0.1)] == 0)
			env->pos.y += env->dir.y * 0.1;
	}
	if (key == KEY_DOWN)
	{
		if (env->w_map[(int)(env->pos.x + env->dir.x * 0.1)][(int)env->pos.y] == 0)
			env->pos.x -= env->dir.x * 0.1;
		if (env->w_map[(int)env->pos.x][(int)(env->pos.y + env->dir.y * 0.1)] == 0)
			env->pos.y -= env->dir.y * 0.1;
	}
	if (key == KEY_LFT)
	{
		if (env->w_map[(int)(env->pos.x + env->plane.x * 0.2)][(int)env->pos.y] == 0)
			env->pos.x -= env->plane.x * 0.2;
		if (env->w_map[(int)env->pos.x][(int)(env->pos.y + env->plane.y * 0.1)] == 0)
			env->pos.y -= env->plane.y * 0.2;
	}
	if (key == KEY_RGT)
	{
		if (env->w_map[(int)(env->pos.x + env->plane.x * 0.2)][(int)env->pos.y] == 0)
			env->pos.x += env->plane.x * 0.2;
		if (env->w_map[(int)env->pos.x][(int)(env->pos.y + env->plane.y * 0.1)] == 0)
			env->pos.y += env->plane.y * 0.2;
	}
	return (0);
}

int		motion_mouse(int x, int y, t_env *env)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		if (x < 400)
		{
			env->dir = rotate(env->dir, env->ang);
			env->plane = rotate(env->plane, env->ang);
			env->pang -= 2.0;
		}
		else if (x > 400)
		{
			env->dir = rotate(env->dir, -env->ang);
			env->plane = rotate(env->plane, -env->ang);
			env->pang += 2.0;
		}
		env->pang > 358.0 ? env->pang = 0.0 : 0;
		if (y > 300)
		{
			if (env->is_updn > -200)
				env->is_updn -= 10;
		}
		else if (y < 300)
		{
			if (env->is_updn < 300)
				env->is_updn += 10;
		}
		mlx_clear_window(E_MLX, E_WIN);
		init_thread(env);
		mlx_put_image_to_window(E_MLX, E_WIN, E_IMG, 0, 0);
	}
	return (0);
}

int key_hook(int key, t_env *env)
{
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_LFT || key == KEY_RGT)
		moove(key, env);
	if (key == 53)
		exit_wolf(env);
	mlx_clear_window(E_MLX, E_WIN);
	init_thread(env);
	mlx_put_image_to_window(E_MLX, E_WIN, E_IMG, 0, 0);
	return (0);
}

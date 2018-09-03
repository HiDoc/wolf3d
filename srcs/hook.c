#include "wolf.h"

int		exit_wolf(t_env *env)
{
	mlx_destroy_image(E_MLX, E_IMG);
	mlx_destroy_window(E_MLX, E_WIN);
	free_env(env);
	exit(0);
	return (0);
}

t_point	rotate(t_point v, int ang)
{
	float	radian;
	t_point	r;

	radian = ang / 180.0 * 3.141;
	r.x = v.x * cos(radian) - v.y * sin(radian);
	r.y = v.x * sin(radian) + v.y * cos(radian);
	return (r);
}

int		moove(int key, t_env *env)
{
	if (key == KEY_UP)
	{
		if (env->w_map[(int)(env->pos.x + env->dir.x * 0.05)][(int)env->pos.y] == 0)
			env->pos.x += env->dir.x * 0.05;
		if (env->w_map[(int)env->pos.x][(int)(env->pos.y + env->dir.y * 0.05)] == 0)
			env->pos.y += env->dir.y * 0.05;
	}
	if (key == KEY_DOWN)
	{
		if (env->w_map[(int)(env->pos.x + env->dir.x * 0.05)][(int)env->pos.y] == 0)
			env->pos.x -= env->dir.x * 0.05;
		if (env->w_map[(int)env->pos.x][(int)(env->pos.y + env->dir.y * 0.05)] == 0)
			env->pos.y -= env->dir.y * 0.05;
	}
	return (0);
}

int key_hook(int key, t_env *env)
{
	if (key == KEY_UP || key == KEY_DOWN
	|| key == KEY_LFT || key == KEY_RGT)
		moove(key, env);
	if (key == 53)
		exit_wolf(env);
	mlx_clear_window(E_MLX, E_WIN);
	wolf(env);
	mlx_put_image_to_window(E_MLX, E_WIN, E_IMG, 0, 0);
	return (0);
}

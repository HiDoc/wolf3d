#include "wolf.h"

int loop(t_env *env)
{
	// (void)key;
	// (void)env;

	env->oldtime = env->time;
	env->time = clock();
	env->frametime = (env->time - env->oldtime) / 1000.0;
	wolf(env);
	mlx_put_image_to_window(env->mlx->mptr, env->mlx->wptr, env->mlx->iptr, 0, 0);
	return(0);
}

void	exit_wolf(t_env *env)
{
	mlx_destroy_image(env->mlx->mptr, env->mlx->iptr);
	mlx_destroy_window(env->mlx->mptr, env->mlx->wptr);
	free_env(env);
	exit(0);
}

// int moove(int key, t_env *env)
// {
// 	double	moovespeed;
// 	double	rotspeed;

// 	moovespeed = env->frametime * 5.0;
// 	rotspeed = env->frametime * 3.0;
// 	if (key == KEY_DOWN)
// 	{
// 		if ()
// 	}
// }

int key_hook(int key, t_env *env)
{
	// if (key == KEY_UP || key == KEY_DOWN
	// || key == KEY_LFT || key == KEY_RGT)
	// 	moove(key, env);
	if (key == 53)
		exit_wolf(env);
	return (0);
}
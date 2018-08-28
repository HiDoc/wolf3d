#include "wolf.h"

void	init_mlx(t_env *env)
{
	if (!(env->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		print_error(1, env);
	env->mlx->mptr = mlx_init();
	env->mlx->wptr = mlx_new_window(env->mlx->mptr, WIDTH, HEIGHT, "Wolf 3D");
	env->mlx->iptr = mlx_new_image(env->mlx->mptr, WIDTH, HEIGHT);
	env->mlx->data = (int *)mlx_get_data_addr(env->mlx->iptr, &env->mlx->bpp, &env->mlx->size_l, &env->mlx->endian);
}

int		fill_tab(t_env *env)
{
	int	x;
	int	y;
	int w_map[24][24]=
		{
		{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
		{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
		{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
		{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
		{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
		{4,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
		{4,0,0,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
		{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
		{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
		{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
		{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
		{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
		{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
		{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
		{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
		{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
		{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
		{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
		{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
		};
	if (!(env->w_map = (int**)malloc(sizeof(int*) * 24)))
		print_error(1, env);
	y = 0;
	while (y < 24)
	{
		if (!(env->w_map[y] = (int*)malloc(sizeof(int) * 24)))
			print_error(1, env);
		x = 0;
		while (x < 24)
		{
			env->w_map[y][x] = w_map[y][x];
			x++;
		}
		y++;
	}
	return (0);
}

int		init_env(t_env *env)
{
	env->pos.x = 10;
	env->pos.y = 10;
	env->ang = 2.0;
	env->dir.x = -1.0;
	env->dir.y = 0.0;
	env->plane.x = 0.0;
	env->plane.y = 0.66;
	init_mlx(env);
	return (0);
}

int		main(int ac, char **av)
{
	t_env   *env;

	(void)ac;
	(void)av;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		print_error(1, NULL);
	init_env(env);
	fill_tab(env);
	wolf(env);
	mlx_do_key_autorepeaton(env->mlx->mptr);
	mlx_put_image_to_window(env->mlx->mptr, env->mlx->wptr, env->mlx->iptr, 0, 0);
	mlx_hook(env->mlx->wptr, KeyPress, KeyPressMask, &key_hook, env);

	mlx_loop(env->mlx->mptr);
	return (0);
}
#include "wolf.h"

void	init_mlx(t_env *env)
{
	E_MLX = mlx_init();
	E_WIN = mlx_new_window(E_MLX, WIDTH, HEIGHT, "Wolf 3D");
	E_IMG = mlx_new_image(E_MLX, WIDTH, HEIGHT);
	I_IMG = (int *)mlx_get_data_addr(E_IMG, &I_BPP, &I_SZL, &I_END);
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
	env->w_map = NULL;
	init_mlx(env);
	return (0);
}

void	put_gun(t_env *env)
{
	int x = 0;
	int y = 0;
	int pos = 0;

	while (y < 128)
	{
		x = 0;
		while (x < 128)
		{
			if (env->gun->data[pos] != 0xFFFFFF)
				env->mlx.data[572 * 672 + (y * 800 + x) - 50] = env->gun->data[pos]; 
			x++;
			pos++;
		}
		y++;
	}
	y = 0;
	while (y < 20)
	{
		x = 0;
		while (x < 20)
		{
			if ((x == 10 || y == 10) && x != y)
				env->mlx.data[800 * 300 + (y * 800 + x) + 390] = 0xFF00;
			x++;
		}
		y++;
	}
}

int		main(int ac, char **av)
{
	t_env   *env;

	(void)ac;
	(void)av;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		print_error(1, NULL);
	init_env(env);
	img(env);
	fill_tab(env);
	// wolf(env);
	init_thread(env);
	mlx_do_key_autorepeaton(E_MLX);
	mlx_put_image_to_window(E_MLX, E_WIN, E_IMG, 0, 0);
	mlx_hook(E_WIN, KeyPress, KeyPressMask, &key_hook, env);
	mlx_hook(E_WIN, 6, 3, &motion_mouse, env);
	mlx_loop(E_MLX);
	return (0);
}

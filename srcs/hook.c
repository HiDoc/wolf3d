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

static int check_pos(t_env *env, t_point mult, float check, char pos)
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

int		moove(int key, t_env *env)
{
	if (key == KEY_UP)
	{
		check_pos(env, env->dir, 0.2, 'x');
		check_pos(env, env->dir, 0.2, 'y');
	}
	if (key == KEY_DOWN)
	{
		check_pos(env, env->dir, -0.2, 'x');
		check_pos(env, env->dir, -0.2, 'y');
	}
	if (key == KEY_LFT)
	{
		check_pos(env, env->plane, -0.2, 'x');
		check_pos(env, env->plane, -0.2, 'y');
	}
	if (key == KEY_RGT)
	{
		check_pos(env, env->plane, 0.2, 'x');
		check_pos(env, env->plane, 0.2, 'y');
	}
	if (key == KEY_X)
	{
		int i;

		i = 0;
		env->pos_portal.x = env->pos.x;
		env->pos_portal.y = env->pos.y;
		if (!(env->blackportal = malloc(sizeof(t_img))))
			print_error(1, env);
		env->blackportal->iptr = mlx_new_image(E_MLX, 200, 100);
		env->blackportal->data = (int *)mlx_get_data_addr(env->blackportal->iptr, &env->blackportal->bpp, &env->blackportal->size_l, &env->blackportal->endian);
		// while (i < 20000)
		// 	env->blackportal->data[i] = 0x000000;
		env->inportal = 1;
	}
	if (key == KEY_SPACE)
	{
		t_point	odir;
		t_point	oplane;
		t_point	opos;
		double	ois_updn;
		double	opang;

		env->outportal = 1;
		if (!(env->portal = malloc(sizeof(t_img))))
			print_error(1, env);
		env->width = 200;
		env->height = 100;
		env->portal->iptr = mlx_new_image(E_MLX, env->width, env->height);
		env->portal->data = (int *)mlx_get_data_addr(env->portal->iptr, &env->portal->bpp, &env->portal->size_l, &env->portal->endian);
		odir.x = env->dir.x;
		odir.y = env->dir.y;
		oplane.x = env->plane.x;
		oplane.y = env->plane.y;
		ois_updn = env->is_updn;
		opang = env->pang;
		opos.x = env->pos.x;
		opos.y = env->pos.y;
		env->pang = 0.0;
		env->dir.x = -1.0;
		env->dir.y = 0.0;
		env->plane.x = 0.0;
		env->plane.y = 0.66;
		env->is_updn = 0.0;
		env->pos.x = env->pos_portal.x;
		env->pos.y = env->pos_portal.y;
		init_thread(env);
		env->outportal = 2;
		env->width = 800;
		env->height = 600;
		env->pang = opang;
		env->dir.x = odir.x;
		env->dir.y = odir.y;
		env->plane.x = oplane.x;
		env->plane.y = oplane.y;
		env->is_updn = ois_updn;
		env->pos.x = opos.x;
		env->pos.y = opos.y;
	}
	return (0);
}

int		motion_mouse(int x, int y, t_env *env)
{
	double	mult;

	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		mult = (x < 400 ? 1.0 : -1.0);
		env->dir = rotate(env->dir, mult * env->ang);
		env->plane = rotate(env->plane, mult * env->ang);
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
		mlx_clear_window(E_MLX, E_WIN);
		init_thread(env);
		mlx_put_image_to_window(E_MLX, E_WIN, E_IMG, 0, 0);
		if (env->inportal == 1)
			mlx_put_image_to_window(E_MLX, E_WIN, env->blackportal->iptr, 0, 0);
		if (env->outportal == 2)
			mlx_put_image_to_window(E_MLX, E_WIN, env->portal->iptr, 210, 0);
	}
	return (0);
}

int key_hook(int key, t_env *env)
{
	moove(key, env);
	if (key == 53)
		exit_wolf(env);
	mlx_clear_window(E_MLX, E_WIN);
	init_thread(env);
	mlx_put_image_to_window(E_MLX, E_WIN, E_IMG, 0, 0);
if (env->inportal == 1)
			mlx_put_image_to_window(E_MLX, E_WIN, env->blackportal->iptr, 0, 0);
	if (env->outportal == 2)
			mlx_put_image_to_window(E_MLX, E_WIN, env->portal->iptr, 210, 0);
	return (0);
}

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
		if (env->portal.out == 0)
		{
			if (!(env->portal.outimg = malloc(sizeof(t_img))))
				print_error(1, env);
			env->portal.outimg->iptr = mlx_new_image(E_MLX, 64, 64);
			env->portal.outimg->data = (int *)mlx_get_data_addr(env->portal.outimg->iptr, &env->portal.outimg->bpp, &env->portal.outimg->size_l, &env->portal.outimg->endian);
			env->portal.out = 1;
		}
		env->portal.outpos = env->pos;
		env->portal.hit = 0;
		while (env->portal.hit == 0)
			env->portal.outpos = portal_pos(env, env->portal.outpos);
		if (env->portal.hit == 1)
		{
			env->portal.outemp.x = env->portal.outpos.x + env->dir.x * 0.2;
			env->portal.outemp.y = env->portal.outpos.y;
		}
		else
		{
			env->portal.outemp.y = env->portal.outpos.y + env->dir.y * 0.2;
			env->portal.outemp.x = env->portal.outpos.x;
		}
		env->w_map[(int)env->portal.outemp.x][(int)env->portal.outemp.y] = 8;
		env->portal.outdir = rotate(env->dir, 180.0);
		env->portal.outplane = rotate(env->plane, 180.0);
	}
	if (key == KEY_A)
	{
		t_point	odir;
		t_point	oplane;
		t_point	opos;
		double	ois_updn;
		double	opang;

		env->width = 64;
		env->height = 64;
		if (env->portal.in == 0)
		{
			if (!(env->portal.inimg = malloc(sizeof(t_img))))
				print_error(1, env);
			env->portal.inimg->iptr = mlx_new_image(E_MLX, env->width, env->height);
			env->portal.inimg->data = (int *)mlx_get_data_addr(env->portal.inimg->iptr, &env->portal.inimg->bpp, &env->portal.inimg->size_l, &env->portal.inimg->endian);
			env->portal.in = 1;
		}
		env->portal.inpos = env->pos;
		env->portal.hit = 0;
		while (env->portal.hit == 0)
			env->portal.inpos = portal_pos(env, env->portal.inpos);
		if (env->portal.hit == 1)
		{
			env->portal.inemp.x = env->portal.inpos.x + env->dir.x * 0.2;
			env->portal.inemp.y = env->portal.inpos.y;
		}
		else
		{
			env->portal.inemp.y = env->portal.inpos.y + env->dir.y * 0.2;
			env->portal.inemp.x = env->portal.inpos.x;
		}
		env->portal.indir = rotate(env->dir, 180.0);
		env->portal.inplane = rotate(env->plane, 180.0);
		odir = env->dir;
		oplane = env->plane;
		ois_updn = env->is_updn;
		opang = env->pang;
		opos = env->pos;
	//generation img de sortie
		env->portal.out = 2;
		env->pang = 0.0;
		env->is_updn = 0.0;
		env->pos = env->portal.outpos;
		env->dir = env->portal.outdir;
		env->plane = env->portal.outplane;
		init_thread(env);
	//generation img d entree
		env->portal.out = 1;
		env->portal.in = 2;
		env->pos = env->portal.inpos;
		env->dir = env->portal.indir;
		env->plane = env->portal.inplane;
		init_thread(env);
	//reinitialisation aux donnees du player
		env->portal.in = 1;
		env->width = 800;
		env->height = 600;
		env->pang = opang;
		env->dir = odir;
		env->plane = oplane;
		env->is_updn = ois_updn;
		env->pos = opos;
		env->w_map[(int)env->portal.inemp.x][(int)env->portal.inemp.y] = 8;
		env->w_map[(int)env->portal.outemp.x][(int)env->portal.outemp.y] = 9;
		
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
	return (0);
}

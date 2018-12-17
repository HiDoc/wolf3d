#include "wolf.h"
/*
int		exit_wolf(t_env *env)
{
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
		if (env->outportal.inout == 0)
			env->outportal = new_portal_img(env, env->outportal);
		else
		{
			while (i < 64 * 64)
			{
				env->outportal.img->data[i] = 0x000000;
				i++;
			}
			if (env->inportal.bloc != 0)
			{
				printf("AV in bloc != 0 ds KEY X %d \n", env->w_map[(int)env->inportal.temp.x][(int)env->inportal.temp.y]);
				env->w_map[(int)env->inportal.save.x][(int)env->inportal.save.y] = env->inportal.bloc;
				printf("AP in bloc != 0 ds KEY X %d \n", env->w_map[(int)env->inportal.temp.x][(int)env->inportal.temp.y]);
			}
			printf("AV out bloc return valeur initiale %d \n", env->w_map[(int)env->outportal.temp.x][(int)env->outportal.temp.y]);
			env->w_map[(int)env->outportal.save.x][(int)env->outportal.save.y] = env->outportal.bloc;
			printf("AP out bloc return valeur initiale %d \n", env->w_map[(int)env->outportal.temp.x][(int)env->outportal.temp.y]);
		}
		env->outportal.pos = env->pos;
		env->outportal = portal(env, env->outportal);
		env->outportal.save = env->outportal.temp;
		env->outportal.psave = env->pos;
		env->outportal.bloc = env->w_map[(int)env->outportal.temp.x][(int)env->outportal.temp.y];
		env->w_map[(int)env->outportal.temp.x][(int)env->outportal.temp.y] = 8;
		env->inportal.on = 0;
		env->outportal.on = 0;
	}
	if (key == KEY_A)
	{
		t_portal	save;

		if (env->inportal.inout == 0)
			env->inportal = new_portal_img(env, env->inportal);
		else if (env->inportal.bloc != 0)
			env->w_map[(int)env->inportal.temp.x][(int)env->inportal.temp.y] = env->inportal.bloc;
		env->inportal.pos = env->pos;
		env->inportal = portal(env, env->inportal);
		env->inportal.psave = env->pos;
		save = save_pdata(env);
	//generation img de sortie
		env->outportal = swap_data(env, env->outportal);
		init_thread(env);
	//generation img d entree
		env->dir = save.dir;
		env->plane = save.plane;
		env->outportal.inout = 1;
		env->inportal = swap_data(env, env->inportal);
		init_thread(env);
	//reinitialisation aux donnees du player
		env->inportal.inout = 1;
		back_pdata(env, save);
		env->inportal.bloc = env->w_map[(int)env->inportal.temp.x][(int)env->inportal.temp.y];
		env->w_map[(int)env->inportal.temp.x][(int)env->inportal.temp.y] = 8;
		env->w_map[(int)env->outportal.temp.x][(int)env->outportal.temp.y] = 9;
		env->inportal.on = 1;
	}
	return (0);
}

int		motion_mouse(int x, int y, t_env *env)
{
	double	mult;
	// t_portal	save;

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
		// if (env->outportal.on == 1)
		// {
		// 	env->inportal = portal(env, env->inportal);
		// 	save = save_pdata(env);
		// //generation img de sortie
		// 	env->inportal.inout = 1;
		// 	env->outportal = swap_data(env, env->outportal);
		// 	init_thread(env);
		// //generation img d entree
		// 	env->outportal.inout = 1;
		// 	env->inportal = swap_data(env, env->inportal);
		// 	init_thread(env);
		// //reinitialisation aux donnees du player
		// 	env->inportal.inout = 1;
		// 	back_pdata(env, save);
		// }
		mlx_clear_window(E_MLX, E_WIN);
		init_thread(env);
		mlx_put_image_to_window(E_MLX, E_WIN, E_IMG, 0, 0);
	}
	return (0);
}

int key_hook(int key, t_env *env)
{
	t_portal	save;

	moove(key, env);
	if (key == 53)
		exit_wolf(env);
	if (env->inportal.on == 1)
	{
		save = save_pdata(env);
	//generation img de sortie
		env->inportal.inout = 1;
		// env->outportal.pos = env->outportal.psave;
		// env->outportal = portal(env, env->outportal);	
		// env->outportal = swap_data(env, env->outportal);
		init_thread(env);
	//generation img d entree
		env->outportal.inout = 1;
		env->dir = save.dir;
		env->plane = save.plane;
		// env->inportal.pos = env->inportal.psave;		
		// env->inportal = portal(env, env->inportal);
		// env->inportal = swap_data(env, env->inportal);
		init_thread(env);
	//reinitialisation aux donnees du player
		env->inportal.inout = 1;
		back_pdata(env, save);
	}
	mlx_clear_window(E_MLX, E_WIN);
	init_thread(env);
	mlx_put_image_to_window(E_MLX, E_WIN, E_IMG, 0, 0);
	return (0);
}
*/
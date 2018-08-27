#include "wolf.h"

// void    init_textures(t_env *env)
// {
// 	double xorcolor;
// 	double	ycolor;
// 	double	xycolor;
// 	int	x;
// 	int	y;

// 	x = 0;
// 	while (x < TEXW)
// 	{
// 		y = 0;
// 		while (y < TEXH)
// 		{
// 			// xorcolor = (x * 256 / TEXW) ^ (y * 256 / TEXH);
// 			// ycolor = y * 256 / TEXH;
// 			// xycolor = y * 128 / TEXH + x * 128 / TEXW;
// 			// env->texture[0][TEXW * y + x] = 65536 * 254 * (x != y && x != TEXW - y);
// 			// env->texture[1][TEXW * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
// 			// env->texture[2][TEXW * y + x] = 256 * xycolor + 65536 * xycolor;
// 			// env->texture[3][TEXW * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
// 			// env->texture[4][TEXW * y + x] = 256 * xorcolor;
// 			// env->texture[5][TEXW * y + x] = 65536 * 192 * (x % 16);
// 			// env->texture[6][TEXW * y + x] = 65536 * ycolor;
// 			// env->texture[7][TEXW * y + x] = 128 + 256 * 128 + 65536 * 128;
// 			env->texture[0] = 0xFFFD82;
// 			env->texture[1] = 0x645986;
// 			env->texture[2] = 0x35FF69;
// 			env->texture[3] = 0x4F518C;
// 			env->texture[4] = 0x35FF69;		
// 			env->texture[5] = 0xFFFD82;
// 			env->texture[6] = 0x645986;	
// 			env->texture[7] = 0x645986;
// 			y++;
// 		}
// 		x++;
// 	}
	
// }
// unsigned int	get_color(t_env *env)
// {
// 	if (env->side == 1)
// 	{
// 		if ((env->stepx == -1 && env->stepy == -1) ||
// 			(env->stepx == 1 && env->stepy == -1))
// 			return (0xFFFD82);
// 		if ((env->stepx == -1 && env->stepy == 1) ||
// 			(env->stepx == 1 && env->stepy == 1))
// 			return (0x35FF69);
// 	}
// 	if ((env->stepx == -1 && env->stepy == -1) ||
// 		(env->stepx == -1 && env->stepy == 1))
// 		return (0x645986);
// 	return (0x4F518C);
// }
void    init_mlx(t_env *env)
{
	if (!(env->mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		print_error(1, env);
	env->mlx->mptr = mlx_init();
	env->mlx->wptr = mlx_new_window(env->mlx->mptr, WIDTH, HEIGHT, "Wolf 3D");
	env->mlx->iptr = mlx_new_image(env->mlx->mptr, WIDTH, HEIGHT);
	env->mlx->data = (int *)mlx_get_data_addr(env->mlx->iptr, &env->mlx->bpp, &env->mlx->size_l, &env->mlx->endian);
}

int		wolf(t_env *env)
{
	int		x;
	int		y;
	// double	camx;
	// double	raydirx;
	// double	raydiry;
	// int		mapx;
	// int		mapy;
	// double	sidedistx;
	// double	sidedisty;
	// double	deltadistx;
	// double	deltadisty;
	// double	perpwalldist;
	// int		stepx;
	// int		stepy;
	// int		hit;
	// int		side;
	// int		lineh;
	// int		sdraw;
	// int		edraw;
	// int		color;
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
	x = 0;
	while (x < WIDTH)
	{
		env->hit = 0;
		env->perpwalldist = -1;
		env->side = -1;
		env->dirx = -1.0;
		env->diry = 0.0;
		env->planex = 0.0;
		env->planey = 0.66;
		env->time = 0;
		env->oldtime = 0;
		env->camx = 2 * x / (double)WIDTH - 1;
		env->mapx = (int)env->posx;
		env->mapy = (int)env->posy;
		env->raydirx = env->dirx + env->planex * env->camx;
		env->raydiry = env->diry + env->planey * env->camx;
		env->deltadistx = sqrt(1 + (env->raydiry * env->raydiry) /
			(env->raydirx * env->raydirx));
		env->deltadisty = sqrt(1 + (env->raydirx * env->raydirx) /
			(env->raydiry * env->raydiry));
		if (env->raydirx < 0)
		{
			env->stepx = -1;
			env->sidedistx = (env->posx - env->mapx) * env->deltadistx;
		}
		else
		{
			env->stepx = 1;
			env->sidedistx = (env->mapx + 1.0 - env->posx) * env->deltadistx;
		}
		if (env->raydiry < 0)
		{
			env->stepy = -1;
			env->sidedisty = (env->posy - env->mapy) * env->deltadisty;
		}
		else
		{
			env->stepy = 1;
			env->sidedisty = (env->mapy + 1.0 - env->posy) * env->deltadisty;
		}
		while (env->hit == 0)
		{
			if (env->sidedistx < env->sidedisty)
			{
				env->sidedistx += env->deltadistx;
				env->mapx += env->stepx;
				env->side = 0;
			}
			else
			{
				env->sidedisty += env->deltadisty;
				env->mapy += env->stepy;
				env->side = 1;
			}
			if (w_map[env->mapx][env->mapy] > 0)
			{
				env->hit = 1;
				if (env->side == 0)
					env->perpwalldist = (env->mapx - env->posx + (1 - env->stepx)
						/ 2) / env->raydirx;
				else
					env->perpwalldist = (env->mapy - env->posy + (1 - env->stepy)
						/ 2) / env->raydiry;
			}
		}
		printf("env->perpwalldist %f \n", env->perpwalldist);

		env->lineh = (int)(HEIGHT / env->perpwalldist);
		printf("env->lineh %i \n", env->lineh);

		env->sdraw = -env->lineh / 2 + HEIGHT / 2;
		if (env->sdraw < 0)
			env->sdraw = 0;
		env->edraw = env->lineh / 2 + HEIGHT / 2;
		if (env->edraw >= HEIGHT)
			env->edraw = HEIGHT - 1;
		printf("env->sdraw %i \n", env->sdraw);
		printf("env->edraw %i \n", env->edraw);
		y = -1;
		while (++y < env->sdraw)
			env->mlx->data[y * WIDTH + x] = 0x35FF69;
		y--;
		printf("y ap ciel %i\n", y);
		while (++y <= env->edraw && y < HEIGHT)
			env->mlx->data[y * WIDTH + x] = 0x645986;
		y--;
		printf("y ap mur %i\n", y);

		while (++y < HEIGHT)
			env->mlx->data[y * WIDTH + x] = 0xFFFD82;
		printf("y ap sol %i\n", y);
		
		x++;
	}
	return (0);
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
	if (!(env->w_map = (int**)malloc(sizeof(int**) * 24)))
		print_error(1, env);
	y = 0;
	while (y < 24)
	{
		if (!(env->w_map[y] = (int*)malloc(sizeof(int*) * 24)))
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

int		main(int ac, char **av)
{
	t_env   *env;

	(void)ac;
	(void)av;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		print_error(1, NULL);
	env->posx = 10;
	env->posy = 10;
	env->time = 0;
	env->oldtime = 0;
	// init_textures(env);
	init_mlx(env);
	// fill_tab(env);
	wolf(env);
	mlx_do_key_autorepeatoff(env->mlx->mptr);
	// mlx_key_hook(env->mlx->wptr, keycode, env);
	// mlx_mouse_hook(env->mlx->wptr, mousecode, env);
	// mlx_loop_hook(env->mlx->mptr, loop, env);
	mlx_hook(env->mlx->wptr, KeyPress, KeyPressMask, &key_hook, env);
	mlx_put_image_to_window(env->mlx->mptr, env->mlx->wptr, env->mlx->iptr, 0, 0);

	mlx_loop(env->mlx->mptr);
	return (0);
}
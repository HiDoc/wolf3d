#include "wolf.h"

int	init_w(t_env *env, int x)
{
	env->hit = 0;
	env->wdist = -1;
	env->side = -1;
	env->cam = 2 * x / (double)WIDTH - 1;
	env->mapx = (int)env->pos.x;
	env->mapy = (int)env->pos.y;
	env->raydir.x = env->dir.x + env->plane.x * env->cam;
	env->raydir.y = env->dir.y + env->plane.y * env->cam;
	env->delta.x = sqrt(1 + (env->raydir.y * env->raydir.y) /
		(env->raydir.x * env->raydir.x));
	env->delta.y = sqrt(1 + (env->raydir.x * env->raydir.x) /
		(env->raydir.y * env->raydir.y));
	return (0);
}

int	calc_step(t_env *env)
{
	if (env->raydir.x < 0)
	{
		env->stepx = -1;
		env->sidedist.x = (env->pos.x - env->mapx) * env->delta.x;
	}
	else
	{
		env->stepx = 1;
		env->sidedist.x = (env->mapx + 1.0 - env->pos.x) * env->delta.x;
	}
	if (env->raydir.y < 0)
	{
		env->stepy = -1;
		env->sidedist.y = (env->pos.y - env->mapy) * env->delta.y;
	}
	else
	{
		env->stepy = 1;
		env->sidedist.y = (env->mapy + 1.0 - env->pos.y) * env->delta.y;
	}
	return (0);
}

int	calc_dda(t_env *env)
{
	while (env->hit == 0)
	{
		if (env->sidedist.x < env->sidedist.y)
		{
			env->sidedist.x += env->delta.x;
			env->mapx += env->stepx;
			env->side = 0;
		}
		else
		{
			env->sidedist.y += env->delta.y;
			env->mapy += env->stepy;
			env->side = 1;
		}
		if (env->w_map[env->mapx][env->mapy] > 0)
		{
			env->hit = 1;
			if (env->side == 0)
				env->wdist = (env->mapx - env->pos.x + (1 - env->stepx)
					/ 2) / env->raydir.x;
			else
				env->wdist = (env->mapy - env->pos.y + (1 - env->stepy)
					/ 2) / env->raydir.y;
		}
	}
	return (0);
}

int	wolf(t_env *env)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		init_w(env, x);
		calc_step(env);
		calc_dda(env);
		env->lineh = (int)(HEIGHT / env->wdist);
		env->sdraw = -env->lineh / 2 + HEIGHT / 2;
		if (env->sdraw < 0)
			env->sdraw = 0;
		env->edraw = env->lineh / 2 + HEIGHT / 2;
		if (env->edraw >= HEIGHT)
			env->edraw = HEIGHT - 1;
		y = -1;
		while (++y < env->sdraw)
			env->mlx->data[y * WIDTH + x] = 0x35FF69;
		y--;
		while (++y <= env->edraw && y < HEIGHT)
			env->mlx->data[y * WIDTH + x] = 0x645986;
		y--;
		while (++y < HEIGHT)
			env->mlx->data[y * WIDTH + x] = 0xFFFD82;
		x++;
	}
	return (0);
}
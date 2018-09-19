#include "wolf.h"

int			wolf(t_env *env, int col)
{
	int		x;
	int		y;
	int		pos;
	int		imgpos;
	t_line	line;

	x = col - 1;
	while (x < WIDTH)
	{
		line_init(env, &line, x);
		y = -1;
		while (++y < line.sdraw)
		{
			pos = y * WIDTH + x;
			imgpos = line_sky(env, &line, y - env->is_updn);
			if (env->portal.out == 2)
				env->portal.outimg->data[pos] = imgpos;
			else if (env->portal.in == 2)
			env->portal.inimg->data[pos] = imgpos;
			else
				env->mlx.data[pos] = imgpos;
		}
		y--;
		while (++y <= line.edraw && y < HEIGHT)
		{
			pos = y * WIDTH + x;
			imgpos = line_wall(env, &line, y - env->is_updn);
			if (env->portal.out == 2)
				env->portal.outimg->data[pos] = imgpos;
			else if (env->portal.in == 2)
				env->portal.inimg->data[pos] = imgpos;
			else
				env->mlx.data[pos] = imgpos;
		}
		y--;
		while (++y < HEIGHT)
		{
			pos = y * WIDTH + x;
			imgpos = line_floor(env, &line, y - env->is_updn);
			if (env->portal.out == 2)
				env->portal.outimg->data[pos] = imgpos;
			else if (env->portal.in == 2)
				env->portal.inimg->data[pos] = imgpos;
			else
				env->mlx.data[pos] = imgpos;
		}
		x += 8;
	}
	return (0);
}

#include "wolf.h"

int			second_floor(t_env *env, int x)
{
	int		y;
	int		pos;
	int		imgpos;
	t_line	line;

	if (objs_init(env, &line, x, NULL) != NULL)
	{
		y = line.sdraw + (line.sdraw - line.edraw) / 1.55;
		while (++y < line.edraw && y < HEIGHT)
		y = line.sdraw + (line.sdraw - line.edraw) / 1.25;
		while (++y < line.edraw && y < HEIGHT)
		{
			pos = y * WIDTH + x;
			imgpos = line_wall(env, &line, y - env->is_updn);	
			env->mlx.data[pos] = imgpos;
		}
	}
	return (0);
}

int			wall_obj(t_env *env, int x)
{
	int		y;
	int		pos;
	int		imgpos;
	t_line	line;

	(void)imgpos;
	if (objs_init(env, &line, x, NULL) != NULL)
	{
		int bot = line.edraw;
		y = line.sdraw + (line.edraw - line.sdraw) / 1.25;
		while (++y < HEIGHT && y < bot)
		{
			pos = y * WIDTH + x;
			env->mlx.data[pos] = 0xFF00;
		}
	}
	return (0);
}


int			ceil_obj(t_env *env, int x)
{
	int		y;
	int		pos;
	int		imgpos;
	t_line	line;
	int		**tab;

	(void)imgpos;
	tab = NULL;
	if (objs_init(env, &line, x, NULL) != NULL)
	{
		int bot = line.edraw;
		tab = tab_copy(env->w_map, tab, 24, 24);
		if (line.raydir.x < 0)
			tab[(int)line.map.x - 1][(int)line.map.y] = 4;
		else
			tab[(int)line.map.x + 1][(int)line.map.y] = 4;
		if (line.raydir.y < 0)
			tab[(int)line.map.x][(int)line.map.y - 1] = 4;
		else
			tab[(int)line.map.x][(int)line.map.y + 1] = 4;
		objs_init(env, &line, x, tab);
		int mod = (line.edraw - line.sdraw) * 25.0 / 100.0;
		if (mod < 0)
			mod = 0;
		y = line.edraw;
		while (++y < HEIGHT && y < bot)
		{
			pos = ((y - mod) * WIDTH + x);
			env->mlx.data[pos] = 0xFF;
		}
		tab_free(tab, 24);
	}
	return (0);
}

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
		wall_obj(env, x);
		ceil_obj(env, x);
		x += 8;
	}
	return (0);
}

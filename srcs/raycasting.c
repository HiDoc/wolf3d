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
			env->sdl.pixels[pos] = 0xFF000000 | imgpos;
		}
	}
	return (0);
}

int			ceil_obj(t_env *env, int x)
{
	int		y;
	t_line	line;
	t_line	line2;
	int		bot;
	int		mod;
	int		mod2;
	int		**tab;

	tab = NULL;
	if (objs_init(env, &line, x, NULL) != NULL && 
		objs_init(env, &line2, x, NULL) != NULL)
	{
		bot = line.edraw;
		mod = (line.edraw - line.sdraw) * 0.50;
		int sline = line.sdraw + mod;
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
		mod2 = (line.edraw - line.sdraw) * 0.50;
		y = line.sdraw + mod2;
		Uint32 color = 0;
		(void)color;
		while (++y < HEIGHT && y < bot)
		{
			if (y < sline)
			{
				color = line_floor(env, &line2, y - env->is_updn);
				setpixel(env->sdl.surface, x, y, 0xFF000000 | color);
			}
			else
			{
				color = line_wall(env, &line2, y - env->is_updn);
				setpixel(env->sdl.surface, x, y, 0xFF000000 | color);
			}
		}
		tab_free(tab, 24);
	}
	return (0);
}

Uint32	add_fog(t_line *line, Uint32 c, double d, char f)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;
	Uint8	a;

	r = c >> 24;
	g = c >> 16;
	b = c >> 8;
	a = c;
	d = 7 / (100 / d);
	if (f == 's')
	{
		(void)line;
		// if (d > 0.6)
		// {
		// 	d = 0.6;
		// 	// printf("c dark\n");
		// }
	}
	if (d > 0.9)
		d = 0.9;
	if (r > 0)
		r = r * ( 1 - d) + ((0x0 >> 24) * d);
	if (g > 0)
		g = g * ( 1 - d) + ((0x0 >> 16) * d);
	if (b > 0)
		b = b * ( 1 - d) + ((0x0 >> 8) * d);
	if (a > 0)
		a = a * (1 - d) + (0x0 * d);
	return ((r << 24) + (g << 16) + (b << 8) + (a));
}


int			wolf(t_env *env, int col)
{
	int		x;
	int		y;
	Uint32	imgpos;
	t_line	line;

	x = col - 1;
	while (x < WIDTH)
	{
		line_init(env, &line, x);
		y = -1;
		while (++y < line.sdraw)
		{
			imgpos = line_sky(env, &line, y - env->is_updn);
			setpixel(env->sdl.surface, x, y, add_fog(&line, 0xFF000000 | imgpos, line.wdist, 's'));
		}
		y--;
		while (++y <= line.edraw && y < HEIGHT)
		{
			imgpos = line_wall(env, &line, y - env->is_updn);
			setpixel(env->sdl.surface, x, y, add_fog(&line, 0xFF000000 | imgpos, line.wdist, 'w'));
		}
		y--;
		while (++y < HEIGHT)
		{
			imgpos = line_floor(env, &line, y - env->is_updn);
			setpixel(env->sdl.surface, x, y, add_fog(&line, 0xFF000000 | imgpos, line.wdist, 's'));
		}
		//ceil_obj(env, x);
		(void)ceil_obj;
		x += 8;
	}
	return (0);
}

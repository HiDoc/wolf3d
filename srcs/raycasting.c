#include "wolf.h"

int	wolf(t_env *env)
{
	int	x;
	int	y;
	t_line	line;

	x = 0;
	while (x < WIDTH)
	{
		line_init(env, &line, x);
		line_step(env, &line);
		line_dda(env, &line);
		line.lineh = (int)(HEIGHT / line.wdist);
		line.sdraw = -line.lineh / 2 + HEIGHT / 2;
		if (line.sdraw < 0)
			line.sdraw = 0;
		line.edraw = line.lineh / 2 + HEIGHT / 2;
		if (line.edraw >= HEIGHT)
			line.edraw = HEIGHT - 1;
		y = -1;
		while (++y < line.sdraw)
			env->mlx.data[y * WIDTH + x] = 0xaabb088;
		y--;
		int nx;
		if (line.sidew == 0)
			line.wall.x = env->pos.y + line.wdist * line.raydir.y;
		else
			line.wall.x = env->pos.x + line.wdist * line.raydir.x;
		line.wall.x -= floor((line.wall.x));
		while (++y <= line.edraw && y < HEIGHT)
		{	
			nx = (int)(line.wall.x * 64.0);
			if (line.sidew == 0 && line.raydir.x > 0) 
				nx = 64.0 - nx - 1;
			if (line.sidew == 1 && line.raydir.y < 0) 
				nx = 64.0 - nx - 1;
			int d = y * 256 - HEIGHT * 128 + line.lineh * 128;
			int texY = ((d * 64.0) / line.lineh) / 256;
			env->mlx.data[y * WIDTH + x] = env->wall->data[texY * 64 + nx];
		}
		y--;
		while (++y < HEIGHT)
		{
			env->mlx.data[y * WIDTH + x] = env->floor->data[line_floor(env, &line, y) % (64 * 64)];
		}
		x++;
	}
	return (0);
}

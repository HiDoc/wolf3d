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
		line.sdraw < 0 ? line.sdraw = 0 : 0;
		line.edraw = line.lineh / 2 + HEIGHT / 2;
		line.edraw >= HEIGHT ? line.edraw = HEIGHT - 1 : 0;
		y = -1;
		while (++y < line.sdraw)
			env->mlx.data[y * WIDTH + x] = env->sky->data[line_floor(env, &line, y)];
		y--;
		if (line.sidew == 0)
			line.wall.x = env->pos.y + line.wdist * line.raydir.y;
		else
			line.wall.x = env->pos.x + line.wdist * line.raydir.x;
		line.wall.x -= floor((line.wall.x));
		while (++y <= line.edraw && y < HEIGHT)
			env->mlx.data[y * WIDTH + x] = env->wall->data[line_wall(env, &line, y)];
		y--;
		while (++y < HEIGHT)
			env->mlx.data[y * WIDTH + x] = env->floor->data[line_floor(env, &line, y)];
		x++;
	}
	return (0);
}

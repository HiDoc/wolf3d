#include "wolf.h"

Uint32			line_tron_floor(t_env *env, t_line *line, int y)
{
	t_point	fwall;
	double	weight;
	int		w;
	int		h;

	w = line->floor->w;
	h = line->floor->h;
	get_fwall(line, &fwall);
	weight = ((double)HEIGHT / (env->hratio * y - HEIGHT)) / line->wdist;
	w = (int)((weight * fwall.x + (1.0 - weight) * env->pos.x) * w);
	h = (int)((weight * fwall.y + (1.0 - weight) * env->pos.y) * h);
	if (w % line->floor->w < 20 || h % line->floor->h < 20)
		return (0xFFc7ff00);
    return (0xff000000);
}

Uint32			line_tron_ceil(t_env *env, t_line *line, int y)
{
	t_point	fwall;
	double	weight;
	int		w;
	int		h;

	w = 512;
	h = 512;
	get_fwall(line, &fwall);
	weight = ((double)HEIGHT / (2.0 * y - HEIGHT)) / line->wdist;
	w = (int)((weight * fwall.x - (1.0 + weight) * env->pos.x) * w);
	h = (int)((weight * fwall.y - (1.0 + weight) * env->pos.y) * h);
	w = w % 512;
	h = h % 512;
    if (w < 20 || h < 20)
		return (0xFFc7ff00);
    return (0xff000000);
}

Uint32			line_tron_wall(t_env *env, t_line *line, int y)
{
	int		x;
	int		yy;
	int		delta;

	x = (int)(line->wall.x * 512);
	delta = 256 * (2.0 * y - HEIGHT + line->lineh);
	yy = ft_abs(delta / line->lineh);
    if (x % 512 < 5 || yy % 512 < 20)
		return (0xffc7ff00);
    return (0xff000000);
}
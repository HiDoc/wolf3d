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
		return (0xffff00ff);
    return (0xff000000);
}

Uint32			line_tron_wall(t_env *env, t_line *line, int y)
{
	int		x;
	int		yy;
	int		delta;

	x = (int)(line->wall.x * line->text->w);
	x = ft_abs(line->text->w - x - 1);
	delta = line->text->h * (2.0 * y - HEIGHT + line->lineh);
	yy = ft_abs(delta * 0.5 / line->lineh);
    if (x % line->floor->w < 20 || yy % line->floor->h < 20)
		return (0xffff00ff);
    return (0xff000000);
}
#include "wolf.h"
void   color_modify(Uint8 *component, double delta, int arg)
{
    if (*component > 0)
        *component = (*component * (1 - delta) + ((0x0 >> arg) * delta));
}

static int  calc_color(Uint32 c, double delta)
{
    SDL_Color color;

    delta > 0.9 ? delta = 0.9 : 0;
    delta /= 1.50;
    c |= 0xFF000000;
	color.r = c >> 24;
	color.g = c >> 16;
	color.b = c >> 8;
	color.a = c;
    color_modify(&color.r, delta, 24);
    color_modify(&color.g, delta, 16);
    color_modify(&color.b, delta, 8);
    color_modify(&color.a, delta, 0);
	return ((color.r << 24) + (color.g << 16) + (color.b << 8) + (color.a));
}

int     wall_fog(t_env *env, t_line *line, Uint32 c, int y)
{
    double  delta;

    (void)y;
    (void)env;
	delta = 15 / (100 / line->wdist);
    return (calc_color(c, delta));
}

int			sky_fog(t_env *env, t_line *line, Uint32 c, int y)
{
    double  delta;

    (void)env;
    delta = (double)y / (double)line->sdraw * 1.2;
    return (calc_color(c, delta));
}

int			floor_fog(t_env *env, t_line *line, Uint32 c, int y)
{
    double  delta;

    (void)env;
    delta = (HEIGHT - (double)y) / (HEIGHT - line->edraw);
    return (calc_color(c, delta));
}

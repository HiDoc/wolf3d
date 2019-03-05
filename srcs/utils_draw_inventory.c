#include "doom.h"

void	draw_flat_rect(SDL_Surface *surface, t_edge edge, Uint32 color)
{
	int		i;
	int		j;

	i = edge.v1.x;
	while (i < edge.v2.x)
	{
		j = edge.v1.y;
		while (j < edge.v2.y)
		{
			setpixel(surface, i, j, color);
			j++;
		}
		i++;
	}
}



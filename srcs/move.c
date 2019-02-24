#include "wolf.h"

void	player_falling(int *falling, int *moving, int *ground, float *eyeheight, t_engine *e)
{
	float nextz;

	e->player.velocity.z -= 0.05f; /* Add gravity */
	nextz = e->player.where.z + e->player.velocity.z;
	if (e->player.velocity.z < 0 && nextz < e->sectors[e->player.sector].floor + *eyeheight) // When going down
	{
		/* Fix to ground */
		e->player.where.z    = e->sectors[e->player.sector].floor + *eyeheight;
		e->player.velocity.z = 0;
		*falling = 0;
		*ground  = 1;
	}
	else if (e->player.velocity.z > 0 && nextz > e->sectors[e->player.sector].ceil) // When going up
	{
		/* Prevent jumping above ceiling */
		e->player.velocity.z = 0;
		*falling = 1;
	}
	if (*falling)
	{
		e->player.where.z += e->player.velocity.z;
		*moving = 1;
	}
}

void	player_moving(int *moving, int *falling, float eyeheight, int set, t_engine *e)
{
	t_xy			d;
	int				s;
	const t_xy		p = {e->player.where.x, e->player.where.y};
	const t_sector	*sect = &e->sectors[e->player.sector];
	const t_xy		*vert = sect->vertex;

	s = -1;
	d = set ? (t_xy){e->player.velocity.x, e->player.velocity.y} : (t_xy){0, 0};
	/* Check if the player is about to cross one of the sector's edges */
	while (set && ++s < (int)sect->npoints)
	{
		if (is_crossing(p, d, vert, s, e) && is_bumping(sect, eyeheight, s, e))
		{
			bumping_score(&d, (t_xy){
				vert[s + 1].x - vert[s].x,
				vert[s + 1].y - vert[s].y});
			*moving = 0;
		}
	}
	s = -1;
	while (++s < (int)sect->npoints)
	{
		if (sect->neighbors[s] >= 0 && is_crossing(p, d, vert, s, e))
		{
			e->player.sector = sect->neighbors[s];
			break ;
		}
	}
	e->player.where.x += d.x;
	e->player.where.y += d.y;
	e->player.anglesin = sinf(e->player.angle);
	e->player.anglecos = cosf(e->player.angle);
	*falling = 1;
}
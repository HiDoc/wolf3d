#include "doom.h"

void	player_falling(t_vision *v, t_engine *e, float limit, float speed)
{
	float nextz;

	e->player.velocity.z -= speed; /* Add gravity */
	nextz = e->player.where.z + e->player.velocity.z;
	if (e->player.velocity.z < 0
		&& nextz < e->sectors[e->player.sector].floor + v->eyeheight) // When going down
	{
		/* Fix to v->ground */
		e->player.where.z = e->sectors[e->player.sector].floor + v->eyeheight;
		e->player.velocity.z = 0;
		v->falling = 0;
		v->ground = 1;
	}
	else if (e->player.velocity.z > 0
		&& nextz > limit) // When going up
	{
		/* Prevent jumping above ceiling */
		e->player.velocity.z = 0;
		v->falling = 1;
	}
	if (v->falling)
	{
		e->player.where.z += e->player.velocity.z;
		v->moving = 1;
	}
}

/*
**Vertical collision detection and horizontal collision detection
*/
void	player_collision(t_engine *e, t_vision *v, int jetpack)
{
	v->eyeheight = v->ducking ? DUCKHEIGHT : EYEHEIGHT;
	v->ground = !v->falling;
	if (!v->falling && jetpack)
		player_falling(v, e, e->sectors[e->player.sector].ceil, 0.05f);
	else if (v->falling)
		player_falling(v, e, e->sectors[e->player.sector].floor
		+ v->eyeheight * 2, 0.08f);
	if (v->moving)
		player_moving(v, 1, e);
}

void	set_player(t_engine *e, t_vision *v, t_vtx d)
{
	e->player.where.x += d.x;
	e->player.where.y += d.y;
	e->player.anglesin = sinf(e->player.angle);
	e->player.anglecos = cosf(e->player.angle);
	v->falling = 1;
}

void	player_moving(t_vision *v, int set, t_engine *e)
{
	t_vtx			d;
	int				s;
	const t_vtx		p = {e->player.where.x, e->player.where.y};
	const t_sector	*sect = &e->sectors[e->player.sector];
	const t_vtx		*vert = sect->vertex;

	s = -1;
	d = set ? (t_vtx){e->player.velocity.x, e->player.velocity.y} : (t_vtx){0, 0};
	/* Check if the player is about to cross one of the sector's edges */
	while (set && ++s < (int)sect->npoints)
	{
		if (is_crossing(p, d, vert, s) && is_bumping(sect, v->eyeheight, s, e))
		{
			bumping_score(&d, (t_vtx){vert[s + 1].x - vert[s].x, vert[s + 1].y - vert[s].y});
			v->moving = 0;
		}
	}
	s = -1;
	while (++s < (int)sect->npoints)
	{
		if (sect->neighbors[s] >= 0 && is_crossing(p, d, vert, s))
		{
			e->player.sector = sect->neighbors[s];
			break ;
		}
	}
	set_player(e, v, d);
}
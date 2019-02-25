#include "wolf.h"

t_edge  rotation_edge(t_engine *e, t_edge v)
{
	t_edge edge;
	const float pcos = e->player.anglecos;
	const float psin = e->player.anglesin;
	
	edge = (t_edge){
		v.x1 * psin - v.y1 * pcos,
		v.x1 * pcos + v.y1 * psin,
		v.x2 * psin - v.y2 * pcos,
		v.x2 * pcos + v.y2 * psin
	};
	return (edge);
}

t_edge  current_edge(t_engine *e, t_sector *sect, int s)
{
	t_edge edge;
	
	edge = (t_edge){
		sect->vertex[s + 0].x - e->player.where.x,
		sect->vertex[s + 0].y - e->player.where.y,
		sect->vertex[s + 1].x - e->player.where.x,
		sect->vertex[s + 1].y - e->player.where.y
	};
	return (edge);
}

t_edge  scale_edge(t_edge t)
{
	t_edge edge;
	
	edge = (t_edge){
		hfov / t.y1,
		vfov / t.y1,
		hfov / t.y2,
		vfov / t.y2
	};
	return (edge);
}

/*
** If it's partially behind the player, clip it against player's view frustrum
*/
void	clip_view(t_edge *t)
{
	const float nearz = 1e-4f;
	const float farz = 5;
	const float nearside = 1e-5f;
	const float farside = 20.f;
	// Find an intersection between the wall and the approximate edges of player's view
	t_xy i1 = Intersect(t->x1,t->y1,t->x2,t->y2, -nearside,nearz, -farside,farz);
	t_xy i2 = Intersect(t->x1,t->y1,t->x2,t->y2,  nearside,nearz,  farside,farz);
	if (t->y1 < nearz)
	{
		if (i1.y > 0)
		{
			t->x1 = i1.x;
			t->y1 = i1.y;
		}
		else
		{
			t->x1 = i2.x;
			t->y1 = i2.y;
		}
	}
	if (t->y2 < nearz)
	{
		if (i1.y > 0)
		{
			t->x2 = i1.x;
			t->y2 = i1.y;
		}
		else
		{
			t->x2 = i2.x;
			t->y2 = i2.y;
		}
	}
}
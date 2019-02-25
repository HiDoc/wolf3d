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
#include "wolf.h"

t_ylevel	get_ylevels(t_engine *e, t_sector *sect, int neighbor)
{
	t_ylevel	levels;

	levels = (t_ylevel)
	{
		sect->ceil - e->player.where.z,
		sect->floor - e->player.where.z,
		0, 0
	};
	// Is another sector showing through this portal?
	if (neighbor >= 0)
	{
		levels.nyceil = e->sectors[neighbor].ceil - e->player.where.z;
		levels.nyfloor = e->sectors[neighbor].floor - e->player.where.z;
	}
	return (levels);
}

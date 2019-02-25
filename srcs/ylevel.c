#include "wolf.h"

t_ylevel    get_ylevels(t_engine *e, t_sector *sect, int neighbor)
{
    float      yceil;
    float      yfloor;
    float      nyceil;
    float      nyfloor;

    yceil = sect->ceil  - e->player.where.z;
    yfloor = sect->floor - e->player.where.z;
    nyceil = 0;
    nyfloor = 0;
    if (neighbor >= 0) // Is another sector showing through this portal?
    {
        nyceil  = e->sectors[neighbor].ceil  - e->player.where.z;
        nyfloor = e->sectors[neighbor].floor - e->player.where.z;
    }
    return ((t_ylevel){yceil, yfloor, nyceil, nyfloor});
}
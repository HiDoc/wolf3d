#include "wolf.h"


/* Acquire the floor and ceiling heights, relative to where the player's view is */
/* Check the edge type. neighbor=-1 means wall, other=boundary between two e->sectors. */
t_ylevel    get_ylevel(t_sector *sect, t_engine *e, int neighbor)
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
}
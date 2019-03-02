#include "doom.h"

int     init_character(t_character *new)
{
    new->health = 100;
    new->shield = 0;
    new->max_weapons = 3;
    new->max_objects = 3;
    new->max_health = 200;
    new->max_shield = 200;
    new->inventory.nb_current_obj = 0;
    return (0);
}
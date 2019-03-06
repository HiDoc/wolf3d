#include "doom.h"

int     init_character(t_character *new)
{
    new->health = 100;
    new->shield = 0;
    new->max_weapons = 3;
    new->max_objects = 3;
    new->max_health = 200;
    new->max_shield = 200;
    new->actions.sub_action = 0;
    new->actions.is_loading = 0;
    new->actions.is_shooting = 0;
    return (0);
}
#include "doom.h"

int     wpn_mouse_wheel(t_env *env, SDL_Event event)
{
    if (event.type == SDL_MOUSEWHEEL)
    {
        if (event.wheel.y > 0 && env->player.inventory.ui.wwheel < env->player.inventory.ui.nb_wpn - 1)
            env->player.inventory.ui.wwheel++;
        else if (event.wheel.y < 0 && env->player.inventory.ui.wwheel > 0)
            env->player.inventory.ui.wwheel--;
        printf("on y est\n");
    }
    return (1);
}
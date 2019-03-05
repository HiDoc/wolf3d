#include "doom.h"

int     wpn_mouse_wheel(t_env *env, SDL_Event event)
{
    if (event.type == SDL_MOUSEWHEEL)
    {
        if (event.wheel.y > 0 && env->player.inventory.wwheel < env->player.inventory.nb_wpn - 1)
            env->player.inventory.wwheel++;
        else if (event.wheel.y < 0 && env->player.inventory.wwheel > 0)
            env->player.inventory.wwheel--;
        printf("on y est\n");
    }
    return (1);
}
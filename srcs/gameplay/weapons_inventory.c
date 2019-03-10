#include "doom.h"

int     wpn_mouse_wheel(t_env *env, SDL_Event event)
{
    if (event.type == SDL_MOUSEWHEEL)
    {
        if (env->player.inventory.current)
        {
            if (event.wheel.y > 0 && env->player.inventory.ui.wwheel < env->player.inventory.ui.nb_wpn - 1)
            {
                if (env->player.inventory.weapons[env->player.inventory.ui.wwheel + 1].current)
                    env->player.inventory.current->current = env->player.inventory.weapons[++env->player.inventory.ui.wwheel].current;
            }
            else if (event.wheel.y < 0 && env->player.inventory.ui.wwheel > 0)
            {
                if (env->player.inventory.weapons[env->player.inventory.ui.wwheel - 1].current)
                    env->player.inventory.current->current = env->player.inventory.weapons[--env->player.inventory.ui.wwheel].current;
            }
        }
    }
    return (1);
}
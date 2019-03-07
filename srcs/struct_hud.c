#include "doom.h"

int init_hud(t_env *env)
{
    int i;

    i = 0;
    while (i < 3)
        env->player.hud.shortcut[i++] = NULL;
    if ((env->player.hud.health = ui_img("hud/health")))
        return (1);
    return (0);
}

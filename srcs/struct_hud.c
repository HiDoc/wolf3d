#include "doom.h"

int init_hud(t_env *env)
{
    int i;

    i = 0;
    while (i < 3)
        env->player.hud.shortcut[i++] = NULL;
    if ((env->player.hud.empty_bar = ui_img("hud/empty_bar3"))
    && (env->player.hud.bar[0] = ui_img("hud/health_bar"))
    && (env->player.hud.bar[1] = ui_img("hud/shield_bar3"))
    && (env->player.hud.hud_wpn[0] = ui_img("hud/hud_pistol"))
    && (env->player.hud.hud_wpn[1] = ui_img("hud/hud_ak"))
    && (env->player.hud.hud_wpn[2] = ui_img("hud/hud_rifle"))
    && (env->player.hud.pad = ui_img("hud/pad2")))
        return (1);
    return (0);
}

#include "doom.h"

int     init_icon(t_env *env)
{
    if ((env->player.inventory.ui.icon[0] = ui_img("icons/icon_health"))
    && (env->player.inventory.ui.icon[1] = ui_img("icons/icon_shield"))
    && (env->player.inventory.ui.icon[2] = ui_img("icons/icon_key")))
        return (1);
    return (0);
}

int     init_wpn_inv(t_env *env)
{
    if ((env->player.inventory.ui.mini_wpn[1] = ui_img("wpn/lmini_ak"))
    && (env->player.inventory.ui.mini_wpn[0] = ui_img("wpn/lmini_pistol"))
    && (env->player.inventory.ui.mini_wpn[2] = ui_img("wpn/lmini_rifle"))
    && (env->player.inventory.ui.empt_wpn[1] = ui_img("wpn/empty_ak"))
    && (env->player.inventory.ui.empt_wpn[0] = ui_img("wpn/empty_pistol"))
    && (env->player.inventory.ui.empt_wpn[2] = ui_img("wpn/empty_rifle")))
        return (1);
    return (0);
}

int     init_inv_box(t_env *env)
{
    if((env->player.inventory.ui.box[0] = ui_img("box/full"))
    && (env->player.inventory.ui.box[1] = ui_img("box/empty")))
        return (1);
    return (0);
}

int    init_inventory_ui(t_env *env)
{
   	t_rgba	rgba;

    env->player.inventory.ui.front_pic = ui_img("inventaire");
    SetSurfaceAlpha(env->player.inventory.ui.front_pic, 100, &rgba);
	env->player.inventory.ui.wwheel = 0;
    env->player.inventory.ui.nb_wpn = 2;
    env->player.inventory.nb_current_obj = 0;
    return (init_wpn_inv(env)
    && init_icon(env)
    && init_inv_box(env));
}

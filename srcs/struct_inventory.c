#include "doom.h"

SDL_Surface *ui_img(char *filename)
{
	SDL_Surface	*new;
	char		*path;
	const char	*png = ".png";

	path = ft_strjoin("./rsrc/img/inventory/", filename);
	path = ft_strljoin(path, (char *)png);
	if (!(new = surface_fr_png(path)))
        return (NULL);
	free(path);
	path = NULL;
	return (new);
}

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
    if ((env->player.inventory.ui.mini_wpn[0] = ui_img("wpn/lmini_ak"))
    && (env->player.inventory.ui.mini_wpn[1] = ui_img("wpn/lmini_pistol"))
    && (env->player.inventory.ui.mini_wpn[2] = ui_img("wpn/lmini_rifle"))
    && (env->player.inventory.ui.hud_wpn[0] = ui_img("wpn/hud_ak"))
    && (env->player.inventory.ui.hud_wpn[1] = ui_img("wpn/hud_pistol"))
    && (env->player.inventory.ui.hud_wpn[2] = ui_img("wpn/hud_rifle"))
    && (env->player.inventory.ui.empt_wpn[0] = ui_img("wpn/empty_ak"))
    && (env->player.inventory.ui.empt_wpn[1] = ui_img("wpn/empty_pistol"))
    && (env->player.inventory.ui.empt_wpn[2] = ui_img("wpn/empty_rifle")))
        return (1);
    return (0);
}

int    init_inventory_ui(t_env *env)
{
    env->player.inventory.ui.front_pic = ui_img("fond3");
	env->player.inventory.ui.wwheel = 0;
    env->player.inventory.ui.nb_wpn = 1;    
    env->player.inventory.nb_current_obj = 0;
    return (init_wpn_inv(env) && init_icon(env));
}
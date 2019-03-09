#include "doom.h"

int fill_surface_color(SDL_Surface *img, Uint32 c)
{
    int i;
    Uint32  *p;

    i = 0;
    p = img->pixels;
    while (i < img->w * img->h)
    {
        p[i] = c;
        i++;
    }
    return (0);
}

int init_hud(t_env *env)
{
    int i;
    // t_rgba      rgb;
    // SDL_Surface *tmp;

    i = 0;
    while (i < 3)
        env->player.hud.shortcut[i++] = NULL;
    if (!(env->player.hud.shadow = ui_img("hud/hud_shadow")))
        return (0);
    // if (!(tmp = SDL_CreateRGBSurface(0, 190, 140, 32,
	// 0xff000000, 0xff0000, 0xff00, 0xff)))
    //     return (0);
    // fill_surface_color(tmp, 0x11000000);
    // env->player.hud.shadow = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0);
    env->player.hud.hud_wpn[0] = ui_img("hud/hud_pistol");
    // SetSurfaceAlpha(env->player.hud.hud_wpn[0], 255, &rgb);
    if ((env->player.hud.empty_bar = ui_img("hud/empty_barq"))
    && (env->player.hud.bar[0] = ui_img("hud/health_bar"))
    && (env->player.hud.bar[1] = ui_img("hud/shield_bar"))
    && (env->player.hud.hud_wpn[1] = ui_img("hud/hud_ak"))
    && (env->player.hud.hud_wpn[2] = ui_img("hud/hud_rifle"))
    && (env->player.hud.pad = ui_img("hud/pad3"))
    && (env->player.hud.e_pad[0] = ui_img("hud/hud_e_kit"))
    && (env->player.hud.e_pad[1] = ui_img("hud/hud_e_armor"))
    && (env->player.hud.e_pad[2] = ui_img("hud/hud_e_jetp")))
        return (1);
    return (0);
}

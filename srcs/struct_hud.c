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
    t_rgba      rgb;
    SDL_Surface *tmp;

    i = 0;
    while (i < 3)
        env->player.hud.shortcut[i++] = NULL;
    if (!(tmp = SDL_CreateRGBSurface(0, 190, 140, 32,
	0xff000000, 0xff0000, 0xff00, 0xff)))
        return (0);
    fill_surface_color(tmp, 0x11000000);
    env->player.hud.shadow = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0);
    SetSurfaceAlpha(env->player.hud.shadow, 200, &rgb);
    if ((env->player.hud.empty_bar = ui_img("hud/empty_barq"))
    && (env->player.hud.bar[0] = ui_img("hud/health_bar"))
    && (env->player.hud.bar[1] = ui_img("hud/shield_bar"))
    && (env->player.hud.hud_wpn[0] = ui_img("hud/hud_pistol"))
    && (env->player.hud.hud_wpn[1] = ui_img("hud/hud_ak"))
    && (env->player.hud.hud_wpn[2] = ui_img("hud/hud_rifle"))
    && (env->player.hud.pad = ui_img("hud/pad3")))
        return (1);
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:12 by abaille           #+#    #+#             */
/*   Updated: 2019/03/15 18:23:06 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    env->player.hud.mix = 0;
    while (i < 6)
        env->player.hud.shortcut[i++] = NULL;
    // if (!(env->player.hud.shadow = ui_img("hud/hud_shadow")))
    //     return (0);
    // if (!(tmp = SDL_CreateRGBSurface(0, 190, 140, 32,
	// 0xff000000, 0xff0000, 0xff00, 0xff)))
    //     return (0);
    // fill_surface_color(tmp, 0x11000000);
    // env->player.hud.shadow = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGBA32, 0);
    env->player.hud.hud_wpn[0] = ui_img("hud/hud_pistol");
    // set_surface_alpha(env->player.hud.hud_wpn[0], 255, &rgb);
    if ((env->player.hud.bar[0] = ui_img("hud/bar_h"))
    && (env->player.hud.bar[1] = ui_img("hud/bar_s"))
    && (env->player.hud.hud_wpn[1] = ui_img("hud/hud_ak"))
    && (env->player.hud.hud_wpn[2] = ui_img("hud/hud_rifle"))
    && (env->player.hud.empty_b = ui_img("hud/hud_empty"))
    && (env->player.hud.full_b = ui_img("hud/hud_full"))
    // && (env->player.hud.pad = ui_img("hud/pad3"))
    // && (env->player.hud.e_pad[0] = ui_img("hud/hud_e_kit"))
    // && (env->player.hud.e_pad[1] = ui_img("hud/hud_e_armor"))
    // && (env->player.hud.e_pad[2] = ui_img("hud/hud_e_jetp"))
    // && (env->player.hud.e_pad[3] = ui_img("hud/hud_e_ammo"))
    && (env->player.hud.faces[0] = ui_img("hud/hp_face1"))
    && (env->player.hud.faces[1] = ui_img("hud/hp_face2"))
    && (env->player.hud.faces[2] = ui_img("hud/hp_face3"))
    && (env->player.hud.faces[3] = ui_img("hud/hp_face4")))
        return (1);
    return (0);
}

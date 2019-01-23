/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 19:49:34 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/23 20:32:06 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void    ui_put_string(t_env *env, char *str, int x, int y)
{
	SDL_Surface	    *surface;
    TTF_Font        *font;
    SDL_Color       color;
    SDL_Rect        rect;

    // verify alloc not null
    rect.x = x;
    rect.y = y;
    font = TTF_OpenFont("rsrc/font/yorkbailehill.ttf", 20);
    color = (SDL_Color){255, 0, 0, 100};
	surface	= TTF_RenderText_Blended(font, str, color);
	SDL_BlitSurface(surface, NULL, env->sdl.surface, &rect);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

void    ui_put_fps(t_env *env, int fps)
{
    char            *fps_count;

    fps_count = ft_strrjoin("fps : ", ft_itoa(fps));
    ui_put_string(env, fps_count, 10, 10);
    free(fps_count);
}

void    ui_put_health(t_env *env)
{
    health(env);
    put_img(env, env->life.img, 20, 400);
}
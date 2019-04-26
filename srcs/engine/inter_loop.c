/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 12:01:18 by abaille           #+#    #+#             */
/*   Updated: 2019/04/26 14:32:55 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_intro(t_env *e, int level)
{
	const char	*str[NB_INTER_STR] = {S_INTER1_1, S_INTER1_2,S_INTER1_3,
	S_INTER2_1, S_INTER2_2, S_INTER2_3, S_INTER3_1, S_INTER3_2, S_INTER3_3};
	t_bloc	f;
	int		ref;

	if (level == 0)
		ref = I_INTER1_1;
	if (level == 1)
		ref = I_INTER2_1;
	if (level == 2)
		ref = I_INTER3_1;
	if (e->menu.status.inter)
	{
		ft_bzero(&f, sizeof(t_bloc));
		f.rect = (SDL_Rect){0, 0, W, H};
		draw_img(e, e->world.surfaces.img_menu[level + I_INTER1].sprite, &f);
		ui_put_data(e, (t_font){M_WHITE, "Continue",
			e->hud.text.quantify, (t_vtx){W / 1.1, H / 100}, W / 60, -1, -1});
		ui_put_data(e, (t_font){M_WHITE, str[ref],
			e->hud.text.text, (t_vtx){0, H / 1.2}, W / 40, -1, -1});
		ui_put_data(e, (t_font){M_WHITE, str[++ref],
			e->hud.text.text, (t_vtx){0, H / 1.15}, W / 40, -1, -1});
		ui_put_data(e, (t_font){M_WHITE, str[++ref],
			e->hud.text.text, (t_vtx){0, H / 1.1}, W / 40, -1, -1});
	}
}

static int				sdl_intro_render(t_env *env, int level)
{
	draw_intro(env, level);
	SDL_UpdateTexture(env->sdl.texture, NULL,
		env->sdl.surface->pixels, env->sdl.surface->pitch);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.renderer);
	return (1);
}

void	loop_intro(t_env *env, int level)
{
	env->sdl.keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	while (env->menu.status.inter)
	{
		if (env->sdl.keycodes[SDL_SCANCODE_Q] || env->menu.status.quit)
			doom_exit();
		if ((env->time.time_a = SDL_GetTicks()) - env->time.time_b > SCREEN_TIC)
		{
			env->time.fps = 1000 / (env->time.time_a - env->time.time_b);
			env->time.time_b = env->time.time_a;

			// SDL_PollEvent(&env->sdl.event);

			sdl_intro_render(env, level);
			SDL_WaitEvent(&env->sdl.event);
			if (env->sdl.keycodes[SDL_SCANCODE_RETURN])
				env->menu.status.inter = 0;
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 12:01:18 by abaille           #+#    #+#             */
/*   Updated: 2019/04/26 19:05:13 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		draw_inter(t_env *e, int l, int which)
{
	const char	*str[NB_INTER_STR] = {S_INTRO1_1, S_INTRO1_2,S_INTRO1_3,
	S_INTRO2_1, S_INTRO2_2, S_INTRO2_3, S_INTRO3_1, S_INTRO3_2, S_INTRO3_3,
	S_END1_1, S_END1_2,S_END1_3, S_END2_1, S_END2_2, S_END2_3,
	S_END3_1, S_END3_2, S_END3_3};
	t_bloc	f;
	int		ref;

	if (l == 0)
		ref = which ? I_INTRO1_1 : I_END1_1;
	if (l == 1)
		ref = which ? I_INTRO2_1 : I_END2_1;
	if (l == 2)
		ref = which ? I_INTRO3_1 : I_END3_1;
	ft_bzero(&f, sizeof(t_bloc));
	f.rect = (SDL_Rect){0, 0, W, H};
	draw_img(e,
		e->world.surfaces.img_menu[l + (which ? I_INTER1 : I_END1)].sprite,
		&f);
	ui_put_data(e, (t_font){M_WHITE, "Continue",
		e->hud.text.quantify, (t_vtx){W / 1.1, H / 100}, W / 60, -1, -1});
	ui_put_data(e, (t_font){M_WHITE, str[ref],
		e->hud.text.text, (t_vtx){0, H / 1.2}, W / 40, -1, -1});
	ui_put_data(e, (t_font){M_WHITE, str[++ref],
		e->hud.text.text, (t_vtx){0, H / 1.15}, W / 40, -1, -1});
	ui_put_data(e, (t_font){M_WHITE, str[++ref],
		e->hud.text.text, (t_vtx){0, H / 1.1}, W / 40, -1, -1});
}

static int	sdl_intro_render(t_env *env, int level, int which)
{
	draw_inter(env, level, which);
	SDL_UpdateTexture(env->sdl.texture, NULL,
		env->sdl.surface->pixels, env->sdl.surface->pitch);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.renderer);
	return (1);
}

void		loop_intro(t_env *env, int level, int which)
{
	env->sdl.keycodes = (Uint8 *)SDL_GetKeyboardState(NULL);
	while (env->menu.status.inter == which)
	{
		if (env->sdl.keycodes[SDL_SCANCODE_Q] || env->menu.status.quit)
			doom_exit();
		if ((env->time.time_a = SDL_GetTicks()) - env->time.time_b > SCREEN_TIC)
		{
			env->time.fps = 1000 / (env->time.time_a - env->time.time_b);
			env->time.time_b = env->time.time_a;
			sdl_intro_render(env, level, which);
			SDL_WaitEvent(&env->sdl.event);
			if (env->sdl.keycodes[SDL_SCANCODE_RETURN])
				env->menu.status.inter = !which;
		}
	}
}
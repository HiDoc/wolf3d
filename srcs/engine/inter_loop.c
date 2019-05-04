/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 12:01:18 by abaille           #+#    #+#             */
/*   Updated: 2019/05/04 03:54:16 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		draw_inter(t_env *e, int l)
{
	t_bloc	f;
	int		ref;

	ref = (l % NB_INTER_IMG) + I_INTER1;
	ft_bzero(&f, sizeof(t_bloc));
	f.rect = (SDL_Rect){0, 0, W, H};
	draw_img(e,
		e->world.surfaces.img_menu[ref].sprite, &f);
	ui_put_data(e, (t_font){M_WHITE, "Continue",
		e->hud.font.quantify, (t_vtx){W / 1.1, H / 100}, W / 60, -1, -1});
	ui_put_data(e, (t_font){M_WHITE, e->levels[l % 3]->text_start,
		e->hud.font.text, (t_vtx){0, H / 1.2}, W / 40, -1, -1});
}

void	stats_endgame(t_env *e)
{
	int	i;
	char	*t;
	char	*string;
	t_vtx	pos;

	i = -1;
	pos = (t_vtx){W / 4, H / 3};
	while (++i < e->nb_levels)
	{
		t = time_to_str(e->levels[i]->tplay);
		string = ft_itoa(i);
		string = ft_strrjoin("Level ", string);
		string = ft_strljoin(string, " : ");
		string = ft_strljoin(string, t);
		ui_put_data(e, (t_font){GOLD, string, e->hud.font.text,
			pos, W / 40, -1, -1});
		lt_release(t);
		lt_release(string);
		pos.y += H / 18;
	}
}

void	display_credits(t_env *e)
{
	t_bloc	f;

	ft_bzero(&f, sizeof(t_bloc));
	f.rect = (SDL_Rect){0, 0, W, H};
	e->menu.status.endgame = 2;
	while (e->menu.status.endgame)
	{
		if (e->menu.status.endgame == 2)
		{
			draw_img(e, e->world.surfaces.img_menu[I_ENDGAME].sprite, &f);
			stats_endgame(e);
			print_stats(e, W / 60,
				(t_vtx){W / 3.9, W / 1.7}, (t_vtx){H / 4.5, H / 18});
		}
		if (e->menu.status.endgame == 1)
			draw_img(e, e->world.surfaces.img_menu[I_CREDITS].sprite, &f);
		SDL_WaitEvent(&e->sdl.event);
		if (e->menu.status.endgame == 2
		&& e->sdl.keycodes[SDL_SCANCODE_RETURN])
			e->menu.status.endgame = 1;
		else if (e->menu.status.endgame == 1
		&& e->sdl.keycodes[SDL_SCANCODE_RETURN])
			e->menu.status.endgame = 0;
		SDL_UpdateTexture(e->sdl.texture, NULL,
			e->sdl.surface->pixels, e->sdl.surface->pitch);
		SDL_RenderCopy(e->sdl.renderer, e->sdl.texture, NULL, NULL);
		SDL_RenderPresent(e->sdl.renderer);
	}
}

void	action_endlevel(t_env *e, int level)
{
	Uint32	*t;

	if (level == e->nb_levels - 1)
		display_credits(e);
	else if (e->finish)
	{
		e->menu.status.inter = 0;
		e->finish = 0;
		t = &e->levels[e->curr_lvl]->tplay;
		*t = SDL_GetTicks() - *t;
	}
}

static void	sdl_intro_render(t_env *env, int level)
{
	draw_inter(env, level);
	SDL_UpdateTexture(env->sdl.texture, NULL,
		env->sdl.surface->pixels, env->sdl.surface->pitch);
	SDL_RenderCopy(env->sdl.renderer, env->sdl.texture, NULL, NULL);
	SDL_RenderPresent(env->sdl.renderer);
}

void		loop_intro(t_env *env, int level)
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
			sdl_intro_render(env, level);
			SDL_WaitEvent(&env->sdl.event);
			if (env->sdl.keycodes[SDL_SCANCODE_RETURN])
				env->menu.status.inter = 0;
		}
	}
}
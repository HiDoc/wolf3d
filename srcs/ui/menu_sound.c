/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:16:28 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 16:17:05 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


void	set_msc_menu(t_env *e, t_status *s)
{
	if (s->on && (s->home || s->main_menu || s->ingame))
	{
		if (Mix_Playing(CHAN_MENU))
			Mix_HaltChannel(CHAN_MENU);
		if (Mix_FadeInMusic(e->sound.ambiance[AB_IGMENU], CHAN_MENU, 3000) < 0)
			doom_error_exit("Doom_nukem error on Mix_FadeInMusic");
	}
	else if (s->on && s->gameover)
	{
		if (Mix_Playing(CHAN_MENU))
			Mix_HaltChannel(CHAN_MENU);
		if (Mix_FadeInMusic(e->sound.ambiance[AB_GMOVER], CHAN_MENU, 3000) < 0)
			doom_error_exit("Doom_nukem error on Mix_FadeInMusic");
	}
	if (!s->on && Mix_Playing(CHAN_MENU))
	{
		if (!Mix_FadeOutMusic(500))
			doom_error_exit("Doom_nukem error on Mix_FadeOutMusic");
	}
}

void	menu_btn_sound(t_env *e, const Uint8 *k)
{
	if (k[SDL_SCANCODE_UP] || k[SDL_SCANCODE_DOWN]
		|| k[SDL_SCANCODE_LEFT] || k[SDL_SCANCODE_RIGHT])
		play_chunk(-1, e->sound.hud[HUD_MENU], 0);
}

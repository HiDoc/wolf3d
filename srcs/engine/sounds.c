/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:33:24 by abaille           #+#    #+#             */
/*   Updated: 2019/04/18 03:39:32 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	set_msc_menu(t_env *e, t_status *s)
{
	if (s->on && (s->home || s->main_menu))
		Mix_FadeInMusic(e->sound.ambiance[AB_MENU], 0, 3000) < 0
		? doom_error_exit("Doom_nukem error on Mix_FadeInMusic")
		: 0;
	else if (s->on && s->ingame_menu)
		Mix_FadeInMusic(e->sound.ambiance[AB_IGMENU], 0, 3000) < 0
		? doom_error_exit("Doom_nukem error on Mix_FadeInMusic")
		: 0;
	else
		!Mix_FadeOutMusic(100)
		? doom_error_exit("Doom_nukem error on Mix_FadeOutMusic")
		: 0;

}

void	menu_btn_sound(t_env *e, const Uint8 *k)
{
	if (k[SDL_SCANCODE_UP] || k[SDL_SCANCODE_DOWN]
		|| k[SDL_SCANCODE_LEFT] || k[SDL_SCANCODE_RIGHT])
		Mix_PlayChannel(-1, e->sound.hud[HUD_MENU], 0);
}

unsigned int	sound_rand(int max)
{
	time_t	tmp;
	int		multi;
	int		addi;
	int		seed;

	tmp = time(NULL);
	multi = 12087;
	addi = 3876;
	seed = (multi * tmp + addi) % max;
	return ((unsigned int)seed);
}

// void	sound_enemies()
// {

// }

void	sound_player(t_env *e, t_player *p)
{
	p->sound.medkit ? Mix_PlayChannel(-1, e->sound.p_sound[P_HEALTH], 0) : 0;
	p->sound.medkit = 0;
}
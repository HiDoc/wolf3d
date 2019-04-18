/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:33:24 by abaille           #+#    #+#             */
/*   Updated: 2019/04/18 16:17:33 by abaille          ###   ########.fr       */
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

void	sound_enemies(t_env *e, t_wrap_enmy *enmy, t_vtx player)
{
	int	dist;
	dist = MIX_MAX_VOLUME - dist_vertex(player, (t_vtx){enmy->player.where.x, enmy->player.where.y});
	dist < 0 ? dist = 0 : 0;
	enmy->is_shooting && enmy->player.sound.shootin
	? Mix_PlayChannel(-1, e->sound.e_shot[enmy->ref], 0) : 0;
	enmy->player.sound.shootin && enmy->player.sound.shootin
	? Mix_VolumeChunk(e->sound.e_shot[enmy->ref], dist) : 0;
	enmy->player.sound.shootin = 0;
	enmy->is_dying && enmy->player.sound.dead
	? Mix_PlayChannel(-1, e->sound.e_death[enmy->ref], 0) : 0;
	enmy->is_dying && enmy->player.sound.dead
	? Mix_VolumeChunk(e->sound.e_death[enmy->ref], dist) : 0;
	enmy->player.sound.dead = 0;
}

void	sound_player(t_env *e, t_player *p)
{
	t_wrap_wpn	*wpn;
	// int			r;

	p->sound.medkit ? Mix_PlayChannel(-1, e->sound.p_sound[P_HEALTH], 0) : 0;
	p->sound.medkit = 0;
	wpn = e->player.inventory.current;
	p->sound.shootin ? Mix_PlayChannel(-1, e->sound.shot[wpn->current->ref], 0) : 0;
	p->sound.loadin ? Mix_PlayChannel(-1, e->sound.reload[wpn->current->ref], 0) : 0;
	p->sound.loadin = 0;
	// r = sound_rand(SD_RAND_GEM + 1);
	// r > SD_RAND_GEM - 1 ? r = SD_RAND_GEM - 1 : 0;
	// e->engine.player.sound.gem ? Mix_PlayChannel(1, e->sound.rp_gem[r], 0) : 0;
	// e->engine.player.sound.gem = 0;
}

void	sound_hud(t_env *e, t_player *p)
{
	p->sound.ammo ? Mix_PlayChannel(-1, e->sound.hud[HUD_AMMO], 0) : 0;
	p->sound.ammo = 0;
	p->sound.pick == 1 ? Mix_PlayChannel(-1, e->sound.hud[HUD_PICK], 0) : 0;
	p->sound.pick == 2 ? Mix_PlayChannel(-1, e->sound.hud[HUD_PCKGEM], 0) : 0;
	p->sound.pick == 3 ? Mix_PlayChannel(-1, e->sound.hud[HUD_PCKWPN], 0) : 0;
	p->sound.pick = 0;
	p->sound.nope ? Mix_PlayChannel(-1, e->sound.hud[HUD_NOPE], 0) : 0;
	p->sound.nope = 0;
	p->sound.drop ? Mix_PlayChannel(-1,	e->sound.hud[HUD_DROP], 0) : 0;
	p->sound.drop = 0;
}

void	sound_effect(t_env *e, t_player *p)
{
	p->sound.open ? Mix_PlayChannel(-1, e->sound.s_effect[EFCT_OP_BIGDOOR], 0) : 0;
	p->sound.open = 0;
}
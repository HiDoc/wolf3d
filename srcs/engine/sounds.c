/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:33:24 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 15:53:20 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

void			play_chunk(int chan, Mix_Chunk *c, int loop)
{
	if (Mix_PlayChannel(chan, c, loop) == -1)
		doom_error_exit("Doom_nukem error on play_chunk");
}

void			sound_enemies(t_env *e, t_wrap_enmy *enmy, t_vtx player)
{
	int	vol;

	vol = MIX_MAX_VOLUME - dist_vertex(player,
		(t_vtx){enmy->player.where.x, enmy->player.where.y}) / 2;
	vol < 0 ? vol = 0 : 0;
	if (enmy->a.is_shooting && enmy->player.sound.shootin)
		play_chunk(-1, e->sound.e_shot[enmy->ref], 0);
	Mix_VolumeChunk(e->sound.e_shot[enmy->ref], vol);
	enmy->player.sound.shootin = 0;
	if (enmy->a.is_dying && enmy->player.sound.dead)
		play_chunk(-1, e->sound.e_death[enmy->ref], 0);
	Mix_VolumeChunk(e->sound.e_death[enmy->ref], vol);
	enmy->player.sound.dead = 0;
}

void			sound_hud(t_env *e, t_sd_stat *s)
{
	(s->ammo) ? play_chunk(-1, e->sound.hud[HUD_AMMO], 0) : 0;
	s->ammo = 0;
	(s->pick == 1) ? play_chunk(-1, e->sound.hud[HUD_PICK], 0) : 0;
	(s->pick == 2) ? play_chunk(-1, e->sound.hud[HUD_PCKGEM], 0) : 0;
	(s->pick == 3) ? play_chunk(-1, e->sound.hud[HUD_PCKWPN], 0) : 0;
	s->pick = 0;
	(s->nope) ? play_chunk(-1, e->sound.hud[HUD_NOPE], 0) : 0;
	s->nope = 0;
	(s->drop) ? play_chunk(-1, e->sound.hud[HUD_DROP], 0) : 0;
	s->drop = 0;
}

void			sound_effect(t_env *e, t_sd_stat *s)
{
	(s->end_level) ? play_chunk(-1, e->sound.s_effect[EFCT_OP_BIGDOOR], 0) : 0;
	s->end_level = 0;
	(s->open == 1) ? play_chunk(-1, e->sound.s_effect[EFCT_BTNDOOR], 0) : 0;
	(s->open == 2) ? play_chunk(-1, e->sound.s_effect[EFCT_DOORLOCK], 0) : 0;
	s->open = 0;
	if (s->is_open == 1)
		play_chunk(CHAN_DOOR, e->sound.s_effect[EFCT_OP_LILDOOR], 0);
	if (s->is_open == 2)
		play_chunk(CHAN_DOOR, e->sound.s_effect[EFCT_CL_LILDOOR], 0);
	s->is_open = 0;
}

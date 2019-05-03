/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:33:24 by abaille           #+#    #+#             */
/*   Updated: 2019/05/02 17:39:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	set_msc_menu(t_env *e, t_status *s)
{
	if (s->on && (s->home || s->main_menu || s->ingame))
	{
		if (Mix_Playing(-1))
			Mix_HaltChannel(-1);
		Mix_FadeInMusic(e->sound.ambiance[AB_IGMENU], -1, 3000) < 0
		? doom_error_exit("Doom_nukem error on Mix_FadeInMusic")
		: 0;
	}
	else if (s->on && s->gameover)
	{
		if (Mix_Playing(-1))
			Mix_HaltChannel(-1);
		Mix_FadeInMusic(e->sound.ambiance[AB_GAMEOVER], -1, 3000) < 0
		? doom_error_exit("Doom_nukem error on Mix_FadeInMusic")
		: 0;
	}
	if (!s->on && Mix_Playing(-1))
		!Mix_FadeOutMusic(500)
		? doom_error_exit("Doom_nukem error on Mix_FadeOutMusic")
		: 0;
}

void	menu_btn_sound(t_env *e, const Uint8 *k)
{
	if (k[SDL_SCANCODE_UP] || k[SDL_SCANCODE_DOWN]
		|| k[SDL_SCANCODE_LEFT] || k[SDL_SCANCODE_RIGHT])
		play_chunk(-1, e->sound.hud[HUD_MENU], 0);
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

void	play_chunk(int chan, Mix_Chunk *c, int loop)
{
	if (Mix_PlayChannel(chan, c, loop) == -1)
		doom_error_exit("Doom_nukem error on play_chunk");
}

void	sound_enemies(t_env *e, t_wrap_enmy *enmy, t_vtx player)
{
	int	vol;
	vol = MIX_MAX_VOLUME - dist_vertex(player,
		(t_vtx){enmy->player.where.x, enmy->player.where.y}) / 2;
	vol < 0 ? vol = 0 : 0;
	enmy->a.is_shooting && enmy->player.sound.shootin
		? play_chunk(-1, e->sound.e_shot[enmy->ref], 0) : 0;
	Mix_VolumeChunk(e->sound.e_shot[enmy->ref], vol);
	enmy->player.sound.shootin = 0;
	enmy->a.is_dying && enmy->player.sound.dead
		? play_chunk(-1, e->sound.e_death[enmy->ref], 0) : 0;
	Mix_VolumeChunk(e->sound.e_death[enmy->ref], vol);
	enmy->player.sound.dead = 0;
}

static void	sound_player_life(t_env *e, t_sd_stat *s)
{
	(s->lowlife) ? play_chunk(CHAN_LOWLIFE, e->sound.p_sound[P_HTBIT], -1) : 0;
		s->lowlife = 0;
	if ((s->dead || e->player.health > 50) && Mix_Playing(CHAN_LOWLIFE))
		Mix_HaltChannel(CHAN_LOWLIFE);
	(s->dead) ? play_chunk(-1, e->sound.p_sound[P_DEATH], 0) : 0;
	s->dead = 0;
	(s->hit > 2 && !s->dead)
		? play_chunk(-1, e->sound.p_sound[P_HIT], 0) : 0;
	(s->hit > 2) ? s->hit = 0 : 0;
}

void		sd_stat_player(t_engine *e, t_vision *v, t_sd_stat *s)
{
	(!s->o_duck && v->ducking) ? s->duck = 1 : 0;
	(s->o_duck && v->ducking) ? s->duck = 2 : 0;
	(s->o_duck && !v->ducking) ? s->duck = 3 : 0;
	(!s->o_veloc && e->player.velocity.z) ? s->jump = 1 : 0;
	(s->o_veloc && !e->player.velocity.z) ? s->jump = 3 : 0;
	s->move = (!s->duck && !s->jump
	&& dist_vertex((t_vtx){e->player.origin.x, e->player.origin.y},
	(t_vtx){e->player.where.x, e->player.where.y})) ? 1 : 0;
	(s->move && s->run) ? s->move = 0 : 0;
}

static void	sound_player_move(t_env *e, t_sd_stat *s)
{
	s->duck == 1
		? play_chunk(CHAN_DUCK, e->sound.p_sound[P_DUCKDWN], 0) : 0;
	s->duck == 2 && !Mix_Playing(CHAN_DUCK)
		? play_chunk(CHAN_DUCK, e->sound.p_sound[P_DUCK], 0) : 0;
	if (s->duck == 3)
	{
		play_chunk(CHAN_DUCK, e->sound.p_sound[P_DUCKUP], 0);
		s->duck = 0;
	}
	if (s->jump == 1)
	{
		play_chunk(CHAN_DUCK, e->sound.p_sound[P_JUMPUP], 0);
		s->jump = 2;
	}
	if (s->jump == 3)
	{
		play_chunk(CHAN_DUCK, e->sound.p_sound[P_JUMPDWN], 0);
		s->jump = 0;
	}
	if (s->move && !Mix_Playing(CHAN_MOVE))
		play_chunk(CHAN_MOVE, e->sound.p_sound[P_WALK], 0);
	if (s->run && !Mix_Playing(CHAN_MOVE))
		play_chunk(CHAN_MOVE, e->sound.p_sound[P_RUN], 0);
}

void	sound_player(t_env *e, t_sd_stat *s)
{
	t_wrap_wpn	*wpn;
	int			r;

	(s->medkit) ? play_chunk(-1, e->sound.p_sound[P_HEALTH], 0) : 0;
	s->medkit = 0;
	wpn = e->player.inventory.current;
	(s->shootin) ? play_chunk(-1, e->sound.shot[wpn->current->ref], 0) : 0;
	s->shootin = 0;
	if (wpn->current->ref != FIST)
		(s->loadin) ? play_chunk(-1, e->sound.reload[wpn->current->ref], 0) : 0;
	s->loadin = 0;
	if (s->gem)
	{
		r = sound_rand(SD_RAND_GEM + 1);
		(r > SD_RAND_GEM - 1) ? r = SD_RAND_GEM - 1 : 0;
		(s->gem) ? play_chunk(CHAN_GEM, e->sound.rp_gem[r], 0) : 0;
		s->gem = 0;
	}
	sound_player_life(e, s);
	sound_player_move(e, s);
}

void	sound_hud(t_env *e, t_sd_stat *s)
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

void	sound_effect(t_env *e, t_sd_stat *s)
{
	(s->end_level) ? play_chunk(-1, e->sound.s_effect[EFCT_OP_BIGDOOR], 0) : 0;
	s->end_level = 0;
	(s->open == 1) ? play_chunk(-1, e->sound.s_effect[EFCT_BTNDOOR], 0) : 0;
	(s->open == 2) ? play_chunk(-1,	e->sound.s_effect[EFCT_DOORLOCK], 0) : 0;
	s->open = 0;
	(s->is_open == 1)
		? play_chunk(CHAN_DOOR, e->sound.s_effect[EFCT_OP_LILDOOR], 0) : 0;
	(s->is_open == 2)
		? play_chunk(CHAN_DOOR, e->sound.s_effect[EFCT_CL_LILDOOR], 0) : 0;
	s->is_open = 0;
}

void	handle_sound(t_env *e, t_sd_stat *s)
{
	sound_player(e, s);
	sound_hud(e, s);
	sound_effect(e, s);
}

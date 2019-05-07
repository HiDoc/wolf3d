/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_sound.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:17:28 by abaille           #+#    #+#             */
/*   Updated: 2019/05/07 15:26:36 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

void		sound_player(t_env *e, t_sd_stat *s)
{
	t_wrap_wpn	*wpn;
	int			r;

	(s->medkit) ? play_chunk(-1, e->sound.p_sound[P_HEALTH], 0) : 0;
	s->medkit = 0;
	wpn = e->player.inventory.current;
	(s->shootin) ? play_chunk(-1, e->sound.shot[wpn->ref], 0) : 0;
	s->shootin = 0;
	if (wpn->ref != FIST)
		(s->loadin) ? play_chunk(-1, e->sound.reload[wpn->ref], 0) : 0;
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

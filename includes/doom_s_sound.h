/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_sound.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:56:19 by abaille           #+#    #+#             */
/*   Updated: 2019/04/18 15:57:45 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_SOUND_H
# define DOOM_S_SOUND_H

typedef struct	s_sound		t_sound;
typedef struct	s_sd_stat	t_sd_stat;

struct 						s_sd_stat
{
	int			hit;
	int			dead;
	int			medkit;
	int			jump;
	int			duck;
	int			lowlife;
	int			impass;
	int			shootin;
	int			loadin;
	int			kill;
	int			gem;
	int			explode;
	int			pick;
	int			drop;
	int			ammo;
	int			nope;
	int			open;
};


struct						s_sound
{
	t_sd_stat	state;
	Mix_Chunk	*shot[WORLD_NB_WEAPONS];
	Mix_Chunk	*reload[GAME_NB_WPN];
	Mix_Chunk	*e_voice[WORLD_NB_ENEMIES];
	Mix_Chunk	*e_shot[WORLD_NB_ENEMIES];
	Mix_Chunk	*e_death[WORLD_NB_ENEMIES];
	Mix_Chunk	*p_sound[SD_PLAYER];
	Mix_Chunk	*rp_gem[SD_RAND_GEM];
	Mix_Chunk	*rp_hit[SD_RAND_HIT];
	Mix_Chunk	*rp_impass[SD_RAND_IMPASS];
	Mix_Chunk	*rp_kill[SD_RAND_KILL];
	Mix_Chunk	*hud[SD_HUD];
	Mix_Chunk	*s_effect[SD_EFFECT];
	Mix_Music	*ambiance[SD_AMBIANCE];
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_d_gameplay.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:48:08 by abaille           #+#    #+#             */
/*   Updated: 2019/05/03 16:42:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_D_GAMEPLAY_H
# define DOOM_D_GAMEPLAY_H

# define NB_DOOR_IMG	2

# define BOT_V_SHOT		1.1f

# define NB_SHOT		35
# define GAME_NB_WPN	4

# define FRAME_RATIO	6

/*
** World Enemies index - Works for sounds index
*/
# define MONSTER	0
# define SOLDIER	1
# define ROGER		2
# define LOSTSOUL	3
# define PAIN_ELEM	4
# define PINKBOY	5
# define CYBERDEMON	6
# define BOSS		7
# define BOSS_MIDL	8

/*
** World Enemies long ref
*/
# define L_MONSTER		0x01e060b071e0
# define L_SOLDIER		0x03c1104031e1
# define L_ROGER		0x03c110407282
# define L_LOSTSOUL		0x064110206283
# define L_PAIN_ELEM	0x03c0b0406284
# define L_PINKBOY		0x028060403285
# define L_CYBERDEMON	0x1960904063c6
# define L_BOSS			0x2c8040808467
# define L_BOSS_MIDL	0x2640308063c8

/*
** World WPN index
*/
# define MAGNUM		0
# define SHOTGUN	1
# define RIFLE		2
# define RPG		3
# define FIST		4

/*
** SCOP & RAY wpn
*/
# define R_MAGNUM	1
# define S_MAGNUM	300
# define V_MAGNUM	1.9f
# define R_SHOTGUN	5
# define S_SHOTGUN	100
# define V_SHOTGUN	1.9f
# define R_RIFLE	2
# define S_RIFLE	1000
# define V_RIFLE	2.0f
# define R_RPG		30
# define S_RPG		2000
# define V_RPG		1.1f
# define R_FIST		3
# define S_FIST		1
# define V_FIST		1.4f


/*
** WORLD_NB_OBJECTS - OBJECTS NAME
*/
# define N_HEALTH		"health_kit"
# define N_SHIELD		"armor"
# define N_AMMO_M_R		"ammo_Magnum_RPG-7"
# define N_AMMO_S		"ammo_Shotgun"
# define N_AMMO_R		"ammo_Rifle"
# define N_JETPACK		"Jetpack"
# define N_GEM_B		"Blue_Gem"
# define N_GEM_G		"Green_Gem"
# define N_GEM_R		"Red_Gem"
# define N_GEM_P		"Purple_Gem"
# define N_MAGNUM		"Magnum"
# define N_SHOTGUN		"Shotgun"
# define N_RIFLE		"Rifle"
# define N_RPG			"RPG-7"

/*
** WORLD_NB_OBJECTS - OBJECTS INDEX
*/
# define HEALTH		0
# define SHIELD		1
# define AMMO_MR	2
# define AMMO_S		3
# define AMMO_R		4
# define JETPACK	5

/*
** WORLD_NB_OBJECTS - GEMS INDEX
*/
# define B_GEM		6
# define G_GEM		7
# define R_GEM		8
# define P_GEM		9

/*
** SECTOR - TYPES
*/
# define SECT_BASE		0
# define SECT_BEGIN		1
# define SECT_MECHA		2
# define SECT_DEAD		3
# define SECT_ENDGAME	4
# define SECT_DOOR		5
# define SECT_ENDLEVEL	6
# define SECT_CYBER		7
#endif
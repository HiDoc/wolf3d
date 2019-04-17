/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_d_sound.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:55:19 by abaille           #+#    #+#             */
/*   Updated: 2019/04/17 21:16:33 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_D_SOUND_H
# define DOOM_D_SOUND_H

/*
** Sounds constants
*/
# define SD_PLAYER		13
# define SD_HUD			5
# define SD_EFFECT		13
# define SD_AMBIANCE	20
# define SD_RAND_GEM	3
# define SD_RAND_KILL	8
# define SD_RAND_HIT	3
# define SD_RAND_IMPASS	2

/*
** PLAYER sounds index
*/
# define P_DEATH	0
# define P_HTBIT	1
# define P_JUMPUP	2
# define P_JUMPDWN	3
# define P_HEALTH	4
# define P_BOOSTG	5
# define P_WALK		6
# define P_DUCKDWN	7
# define P_DUCK		8
# define P_DUCKUP	9
# define P_JTPACKON	10
# define P_JTPACK	11
# define P_JTPACKOF	12

/*
** AMBIANCE sounds index
*/
# define AB_MENU			0
# define AB_IGMENU			1
# define AB_GAMEOVER		2
# define AB_SPACE			3
# define AB_CYBDEMON		4
# define AB_BOSS			5
# define AB_DEADROOM		6
# define AB_METALLIC		7
# define AB_DRAMA			8
# define AB_STRESSUNDRGD	9
# define AB_UNDERWATER		10
# define AB_ACTIONSTRESS	11
# define AB_LOADINGPG		12
# define AB_DARK			13
# define AB_TENSION			14
# define AB_EPICLOOP		15
# define AB_CAVEWATER		16
# define AB_CINEM			17
# define AB_FACTORY			18

/*
** HUD sounds index
*/
# define HUD_MENU	0
# define HUD_PICK	1
# define HUD_DROP	2
# define HUD_PCKGEM	3
# define HUD_PCKWPN	4

/*
** EFFECTS sounds index
*/
# define EFCT_BTNDOOR		0
# define EFCT_DOORLOCK		1
# define EFCT_OP_LILDOOR	2
# define EFCT_CL_LILDOOR	3
# define EFCT_OP_BIGDOOR	4
# define EFCT_OP_ELVTR		5
# define EFCT_ELVTRRUN		6
# define EFCT_CL_ELVTR		7
# define EFCT_ELVTR_MSC		8
# define EFCT_WARNALARM		9
# define EFCT_CYDMN_FARSTEP	10
# define EFCT_INTRO_BOSS	11
# define EFCT_CREEPSCREAM	12

#endif
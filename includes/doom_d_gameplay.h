/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_d_gameplay.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 10:48:08 by abaille           #+#    #+#             */
/*   Updated: 2019/04/07 19:06:54 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_D_GAMEPLAY_H
# define DOOM_D_GAMEPLAY_H

# define NB_DOOR_IMG	2

# define BOT_NB_SHOT	12
# define BOT_V_SHOT		1.1f

# define PLYR_NB_SHOT	35
# define GAME_NB_WPN	4
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


#endif
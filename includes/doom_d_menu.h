/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_d_menu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:12:49 by abaille           #+#    #+#             */
/*   Updated: 2019/04/14 01:54:32 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_D_MENU_H
# define DOOM_D_MENU_H

# define NB_SCANCODE	283
# define NB_IMG_MENU	6
# define NB_BLOC_NG		4
# define NB_BLOC_IG		4
# define NB_OPT_KEY		15
# define NB_OPT_MENU	19
# define NB_MENU_BTN	8
# define NB_HOVER_STR	9
/*
** MENU Index IMG - title
*/
# define I_IHOME		0
# define I_IMAINMENU	1
# define I_IOPT			2
# define I_INGAME		3
# define I_LOADMENU		4
# define I_IBTN			5

/*
** MENU String -- NB_MENU_BTN --
*/
# define S_MAINMENU		"MAIN MENU"
# define S_NEWGAME		"NEW GAME"
# define S_LOADGAME		"LOAD GAME"
# define S_OPTIONS		"OPTIONS"
# define S_SAVE			"SAVE"
# define S_QUIT			"QUIT"
# define S_RETURN		"Return"

# define S_OOFF			"OFF"

/*
** OPTIONS string
*/
# define S_OON			"ON"
# define S_OUP			"Up               : "
# define S_ODOWN		"Down          : "
# define S_OLEFT		"Rift left     : "
# define S_ORIGHT		"Rift right    : "
# define S_OJUMP		"Jump           : "
# define S_ODUCK		"Duck            : "
# define S_OINVENTR		"Inventory   : "
# define S_OPICK		"Pick up : "
# define S_OOPENDOOR	"Open doors      : "
# define S_OJETPACKON	"Jetpack ON/OFF  : "
# define S_OBLUEGEM		"Blue Gem        : "
# define S_OGREEGEM		"Green Gem       : "
# define S_OREDGEM		"Red Gem         : "
# define S_OPURPGEM		"Purple Gem      : "

/*
** MENU Index String -- NB_STR_MENU --
*/
# define I_MAINMENU		0
# define I_NEWGAME		1
# define I_LOADGAME		2
# define I_OPTIONS		3
# define I_SAVE			4
# define I_QUIT			5
# define I_RETURN		6

# define I_OOFF			7
/*
** OPTIONS Index options
*/
# define I_OON			0
# define I_OUP			1
# define I_ODOWN		2
# define I_OLEFT		3
# define I_ORIGHT		4
# define I_OJUMP		5
# define I_ODUCK		6
# define I_OINVENTR		7
# define I_OPICK		8
# define I_OOPENDOOR	9
# define I_OJETPACKON	10
# define I_OBLUEGEM		11
# define I_OGREEGEM		12
# define I_OREDGEM		13
# define I_OPURPGEM		14
#endif

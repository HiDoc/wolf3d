/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_d_menu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:12:49 by abaille           #+#    #+#             */
/*   Updated: 2019/04/12 13:20:00 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_D_MENU_H
# define DOOM_D_MENU_H

# define NB_SCANCODE	283
# define NB_IMG_MENU	5
# define NB_BLOC_NG		5
# define NB_BLOC_IG		6
# define NB_OPT_KEY		14
# define NB_OPT_MENU	19
# define NB_MENU_BTN	16
# define NB_HOVER_STR	9
/*
** MENU Index IMG - title
*/
# define I_IHOME		0
# define I_IMAINMENU	1
# define I_ILOAD_OPT	2
# define I_IINGAME		3
# define I_IBTN			4

/*
** MENU String -- NB_MENU_BTN --
*/
# define S_MENU			"Menu"
# define S_PRESS		"PRESS ENTER"
# define S_MAINMENU		"MAIN MENU"
# define S_NEWGAME		"NEW GAME"
# define S_LOADGAME		"LOAD GAME"
# define S_OPTIONS		"OPTIONS"
# define S_SAVE			"SAVE"
# define S_QUIT			"QUIT"
# define S_RETURN		"Return"
# define S_PAUSE		"PAUSE"

# define S_SAVED		"Game saved"
# define S_NOSAVE		"No save yet"
# define S_OSOUND		"Sound Turn : "
# define S_OON			"ON"
# define S_OOFF			"OFF"
# define S_OCOMMANDS	"Commands :      "

/*
** OPTIONS string
*/
# define S_OUP			"Up               : "
# define S_ODOWN		"Down          : "
# define S_OLEFT		"Rift left     : "
# define S_ORIGHT		"Rift right    : "
# define S_OJUMP		"Jump           : "
# define S_ODUCK		"Duck            : "
# define S_OINVENTR		"Inventory   : "
# define S_OPICK		"Pick up Objects : "
# define S_OOPENDOOR	"Open doors      : "
# define S_OJETPACKON	"Jetpack ON/OFF  : "
# define S_OBLUEGEM		"Blue Gem        : "
# define S_OGREEGEM		"Green Gem       : "
# define S_OREDGEM		"Red Gem         : "
# define S_OPURPGEM		"Purple Gem      : "

/*
** MENU Index String -- NB_STR_MENU --
*/
# define I_MENU			0
# define I_PRESS		1
# define I_MAINMENU		2
# define I_NEWGAME		3
# define I_LOADGAME		4
# define I_OPTIONS		5
# define I_SAVE			6
# define I_QUIT			7
# define I_RETURN		8
# define I_PAUSE		9

# define I_SAVED		10
# define I_NOSAVE		11
# define I_OSOUND		12
# define I_OON			13
# define I_OOFF			14
# define I_OCOMMANDS	15
/*
** OPTIONS Index options
*/
# define I_OUP			0
# define I_ODOWN		1
# define I_OLEFT		2
# define I_ORIGHT		3
# define I_OJUMP		4
# define I_ODUCK		5
# define I_OPICK		6
# define I_OOPENDOOR	7
# define I_OINVENTR		8
# define I_OJETPACKON	9
# define I_OBLUEGEM		10
# define I_OGREEGEM		11
# define I_OREDGEM		12
# define I_OPURPGEM		13
#endif

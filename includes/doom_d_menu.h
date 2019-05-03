/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_d_menu.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:12:49 by abaille           #+#    #+#             */
/*   Updated: 2019/05/02 13:30:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_D_MENU_H
# define DOOM_D_MENU_H

# define NB_IMG_MENU	14
# define NB_INTER_IMG	6
# define NB_BL_NG		4
# define NB_BLOC_IG		4
# define NB_OPT_KEY		15
# define NB_OPT_MENU	17
# define NB_INTER_STR	18
/*
** MENU Index IMG - title
*/
# define I_IHOME		0
# define I_IMAINMENU	1
# define I_IOPT			2
# define I_INGAME		3
# define I_LOADMENU		4
# define I_IBTN			5
# define I_INEWGAME		6
# define I_GAMEOVER		7

# define I_INTER1		8
# define I_INTER2		9
# define I_INTER3		10
# define I_INTER4		11
# define I_INTER5		12
# define I_INTER6		13

/*
** MENU String
*/
# define S_MAINMENU		"MAIN MENU"
# define S_NGAME		"NEW GAME"
# define S_LGAME		"LOAD GAME"
# define S_OPTIONS		"SETTINGS"
# define S_SAVE			"SAVE"
# define S_QUIT			"QUIT"
# define S_RETURN		"Return"
# define S_RESET		"Reset keys"

/*
** OPTIONS string
*/
# define S_OUP			"UP     		  	    	 : "
# define S_ODOWN		"DOWN       	    : "
# define S_OLEFT		"RIFT LEFT       : "
# define S_ORIGHT		"RIFT RIGHT   : "
# define S_OJUMP		"JUMP       	       : "
# define S_ODUCK		"DUCK       	      : "
# define S_OINVENTR		"INVENTORY  : "
# define S_OPICK		"PICK/OPEN	 	     		: "
# define S_ORELOAD		"LOAD WPN   	 	   		: "
# define S_OJETPACKON	"JETPACK ON/OFF  : "
# define S_OBLUEGEM		"BLUE GEM       		 	    : "
# define S_OGREEGEM		"GREEN GEM     		  	 : "
# define S_OREDGEM		"RED GEM       	    		   : "
# define S_OPURPGEM		"PURPLE GEM          	 : "

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
# define I_OPICKOPN		8
# define I_ORELOAD		9
# define I_OJETPACKON	10
# define I_OBLUEGEM		11
# define I_OGREEGEM		12
# define I_OREDGEM		13
# define I_OPURPGEM		14

#endif

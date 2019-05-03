/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_d_hud.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:54:49 by abaille           #+#    #+#             */
/*   Updated: 2019/05/03 03:03:55 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_D_HUD_H
# define DOOM_D_HUD_H

/*
** HUD strings related constants
*/
# define NB_HUD_OBJ		24
# define UI_NB_STRING	30
# define HUD_NB_STRING	19
# define UI_NB_STR_INV	11
# define DSCRIP_STR_INV	14
# define NB_STATS		13
/*
** HUD index img -- NB_HUD_OBJ
*/
# define BG				0
# define BOX_E			1
# define BOX_F			2
# define ICON_SLOT_1 	3
# define ICON_SLOT_2 	4
# define ICON_SLOT_3 	5
# define FACE_1		 	6
# define FACE_2		 	7
# define FACE_3		 	8
# define FACE_4		 	9
# define HP_BAR_1	 	10
# define HP_BAR_2	 	11
# define W_SLOT_1		12
# define W_SLOT_2		13
# define W_SLOT_3		14
# define W_SLOT_LAST	15
# define INV_PISTOL		16
# define INV_SHOTGUN	17
# define INV_RIFLE		18
# define INV_W_LAST		19
# define HUD_PISTOL 	20
# define HUD_SHOTGUN 	21
# define HUD_RIFLE	 	22
# define HUD_W_LAST	 	23

/*
** HUD Strings -- UI_NB_STRING = HUD_NB_STRING + UI_NB_STR_INV
** HUD_NB_STRING
*/
# define STRING_0		" "
# define STRING_1		"Already full shield !"
# define STRING_2		"No shield in stock, stop crying & find some"
# define STRING_3		"Already full of life, enjoy mate !"
# define STRING_4		"No heal in stock, hang on !"
# define STRING_5		"Too greedy man.. Already full stack of this item"
# define STRING_6		"New item placed in inventory"
# define STRING_7		"Inventory full - Max 6 different items"
# define STRING_8		"Item suppressed from inventory"
# define STRING_9		"Weapon already full"
# define STRING_10		"No ammo for this weapon"
# define STRING_11		"JetPack ON"
# define STRING_12		"JetPack OFF"
# define STRING_13		"No JetPack here, keep looking bro !"
# define STRING_14		"Wanna reload what exactly ?"
# define STRING_15		"New weapon, use it wisely"
# define STRING_16		"Already have that weapon"
# define STRING_17		"Too many weapons, drop one"
# define STRING_18		"Weapon dropped"

/*
** UI_NB_STR_INV
*/
# define STRING_19		"Inventory"
# define STRING_20		"Weapons"
# define STRING_21		"Gems"
# define STRING_22		"Statistics"
# define S_CROSS		"X"
# define S_USE			"Use"
# define STRING_25		"1"
# define STRING_26		"2"
# define STRING_27		"3"
# define STRING_28		"4"
# define STRING_29		"5"

# define BLANK			0
# define FULL_SHIELD	1
# define NO_SHIELD		2
# define FULL_LIFE		3
# define NO_HEALTH		4
# define FULL_STACK		5
# define NEW_ITEM		6
# define FULL_INV		7
# define ITEM_SUP		8
# define WPN_FULL		9
# define NO_AMMO		10
# define JETPACK_ON		11
# define JETPACK_OFF	12
# define NO_JTPACK		13
# define WPN_LOADED		14
# define NEW_WPN		15
# define HAVE_WPN		16
# define TOO_MANY_WPN	17
# define WPN_DROPPED	18

# define T_INVENTORY	19
# define T_WEAPONS		20
# define T_GEMS			21
# define T_STATS		22

# define CROSS			23
# define USE			24

# define PAD_INDEX		25
/*
** INV string - Objects description -- DSCRIP_STR_INV
*/
# define I_STRING_0		"Give 50 of health"
# define I_STRING_1		"Give 50 of shield"
# define I_STRING_2		"Give ammo for Magnum / RPG"
# define I_STRING_3		"Give ammo for Shotgun"
# define I_STRING_4		"Give ammo for Pulsar Rifle"
# define I_STRING_5		"Turn JetPack ON/OFF"
# define I_STRING_6		"Give Illimited ammo - for 30 sec"
# define I_STRING_7		"Give Invisibility - for 30 sec"
# define I_STRING_8		"Give Super Strength - for 30 sec"
# define I_STRING_9		"Give Invulnerability - for 30 sec"
# define I_STRING_10	"Magnum - Damage : 56 - Scop : 300"
# define I_STRING_11	"Shotgun - Damage : 100 - Scop : 100"
# define I_STRING_12	"Pulsar Rifle - Damage : 37 - Scop : 1000"
# define I_STRING_13	"RPG-7 - Damage : 250 - Scop : 2000"

/*
** HUD string - Pick up description
*/
# define PICK_STRING	"E - Pick "

/*
** HUD string - Doors strings
*/
# define STR_DOOR_0		"E - Open the door"
# define STR_DOOR_1		"E - Finish the level to open the door"

/*
** HUD DATA STATS - NB_STATS string
*/
# define D_LEVEL		"Level : "
# define D_SECTOR		"Sector : "
# define D_KTOGO		"Kills to go : "
# define D_KD_RATIO		"Ratio kill/death : "
# define D_KD_PERMN		"Ratio kill/minute : "
# define D_KILLS		"Enemies killed : "
# define D_DEATHS		"Death number : "
# define D_TIMEPLAY		"Playing for : "
# define D_K_FIST		"Fists kills : "
# define D_K_MAGNUM		"Magnum kills : "
# define D_K_SHOTGUN	"Shotgun kills : "
# define D_K_RIFLE		"Rifle kills : "
# define D_K_RPG		"RPG-7 kills : "

/*
** HUD DATA STATS - index data[NB_STATS]
*/
# define I_LEVEL		0
# define I_SECTOR		1
# define I_KTOGO		2
# define I_KILLS		3
# define I_DEATHS		4
# define I_TIMEPLAY		5
# define I_KD_RATIO		6
# define I_KD_PERMN		7
# define I_K_MAGNUM		8
# define I_K_SHOTGUN	9
# define I_K_RIFLE		10
# define I_K_RPG		11
# define I_K_FIST		12
#endif
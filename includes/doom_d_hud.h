/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_d_hud.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:54:49 by abaille           #+#    #+#             */
/*   Updated: 2019/04/02 13:17:47 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_D_HUD_H
# define DOOM_D_HUD_H

/*
** HUD related constants
*/
# define NB_HUD_OBJ		21
# define UI_NB_STRING	24
# define UI_NB_STR_INV	5
# define HUD_PICK_OBJ	14
# define DSCRIP_STR_INV	12

/*
** HUD index img
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
# define INV_PISTOL		15
# define INV_SHOTGUN	16
# define INV_RIFLE		17
# define HUD_PISTOL 	18
# define HUD_SHOTGUN 	19
# define HUD_RIFLE	 	20

/*
** HUD Strings
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
# define STRING_19		"Inventory"
# define STRING_20		"Weapons"
# define STRING_21		"X"
# define STRING_22		"Use"
# define STRING_23		"Gems"

/*
** INV string - Objects description
*/
# define I_STRING_0		"Give 50 of health"
# define I_STRING_1		"Give 50 of shield"
# define I_STRING_2		"Give ammo for Magnum"
# define I_STRING_3		"Give ammo for Shotgun"
# define I_STRING_4		"Give ammo for Pulsar Rifle"
# define I_STRING_5		"Turn JetPack ON/OFF"
# define I_STRING_6		"Give Super Speed - for 2 minutes"
# define I_STRING_7		"Give Invisibility - for 2 minutes"
# define I_STRING_8		"Give Super Strength - for 2 minutes"
# define I_STRING_9		"Give Invulnerability - for 2 minutes"
# define I_STRING_10	"Drop object"
# define I_STRING_11	" "

/*
** HUD string - Pick up description
*/
# define P_STRING_0		"E - Pick health"
# define P_STRING_1		"E - Pick shield"
# define P_STRING_2		"E - Pick Magnum ammo"
# define P_STRING_3		"E - Pick Shotgun ammo"
# define P_STRING_4		"E - Pick Rifle ammo"
# define P_STRING_5		"E - Pick JetPack"
# define P_STRING_6		"E - Pick Blue Gem"
# define P_STRING_7		"E - Pick Green Gem"
# define P_STRING_8		"E - Pick Red Gem"
# define P_STRING_9		"E - Pick Purple Gem"
# define P_STRING_10	"E - Pick Magnum"
# define P_STRING_11	"E - Pick Shotgun"
# define P_STRING_12	"E - Pick Pulsar Rifle"
# define P_STRING_13	" "
#endif
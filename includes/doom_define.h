/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_define.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:53:44 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/24 18:39:05 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_DEFINE_H
# define DOOM_DEFINE_H
# include <pthread.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_mixer.h>

# include "libft.h"
# define PI             3.141592

/*
** Define window size
*/

# define W_TEXTURE		256
# define W				1200
# define H				800

/*
** FPS frames
*/
# define SCREEN_FPS     60
# define SCREEN_TIC     16

/*
** Define maximum queue in renderer
*/
# define MAXQUEUE		32

/*
** Define visions constants
*/
# define EYEHEIGHT		6
# define DUCKHEIGHT		2.5
# define HEADMARGIN		1
# define KNEEHEIGHT		2
# define NEARZ			1e-4f
# define NEARSIDE		1e-5f
# define FARZ			5
# define FARSIDE		20.f

/*
** Movement
*/
# define SPEED_WALK 0.2f
# define SPEED_RUN	0.4f

/*
** Field of view
*/
# define HFOV (.73f * H)
# define VFOV (.2f * H)

/*
** World related constants
*/
# define WORLD_NB_WEAPONS	3
# define WORLD_NB_OBJECTS	6
# define WORLD_NB_SURFACE	15
# define NB_HUD_OBJ			21
# define UI_NB_STRING		23
# define UI_NB_STR_INV		4
# define SIZE_OBJ			235
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
** Ui put string - FONTS
*/
# define F_DOOM "rsrc/font/AmazDooMLeft2.ttf"
# define F_TEXT "rsrc/font/interbureau.ttf"
# define F_NUMB "rsrc/font/5E.ttf"
# define F_ARIAL "rsrc/font/Arial.ttf"
/*
** Ui put string - STRING
*/
# define STRING_0	" "
# define STRING_1	"Already full shield !"
# define STRING_2	"No shield in stock, stop crying & find some"
# define STRING_3	"Already full of life, enjoy mate !"
# define STRING_4	"No heal in stock, hang on !"
# define STRING_5	"Too greedy man.. Already full stack of this item"
# define STRING_6	"New item placed in inventory"
# define STRING_7	"Inventory full - Max 6 different items"
# define STRING_8	"Item suppressed from inventory"
# define STRING_9	"Weapon already full"
# define STRING_10	"No ammo for this weapon"
# define STRING_11	"JetPack ON"
# define STRING_12	"JetPack OFF"
# define STRING_13	"No JetPack here, keep looking bro !"
# define STRING_14	"Wanna reload what exactly ?"
# define STRING_15	"New weapon, use it wisely"
# define STRING_16	"Already have that weapon"
# define STRING_17	"Too many weapons, drop one"
# define STRING_18	"Weapon dropped"
# define STRING_19	"Inventory"
# define STRING_20	"Weapons"
# define STRING_21	"X"
# define STRING_22	"Use"

/*
** Colors
*/
#define RED			(SDL_Color){255, 0, 0, 255}
#define WHITE		(SDL_Color){255, 255, 255, 255}
#define BLACK		(SDL_Color){0, 0, 0, 255}
#define BLUE		(SDL_Color){8, 8, 255, 0}
#define	GOLD		(SDL_Color){242, 204, 42, 255}
#define TRANSPARENT	(SDL_Color){0, 0, 0, 0}

/*
** Sounds
*/
# define SHOT_MAGNUM "rsrc/sound/shot/magnum.wav"
# define SHOT_SHOTGUN "rsrc/sound/shot/shotgun.wav"
# define SHOT_RIFLE "rsrc/sound/shot/rifle.wav"

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 13:57:58 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/04 15:32:22 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_UI
# define DOOM_S_UI

typedef struct s_uitxt		t_uitxt;
typedef struct s_font		t_font;
typedef struct s_circle		t_circle;
typedef struct s_minimap	t_minimap;

struct						s_uitxt
{
	TTF_Font			*arial;
	TTF_Font			*doom;
	TTF_Font			*text;
	TTF_Font			*number;
	SDL_Surface			*string[HUD_NB_STRING];
	SDL_Surface			*t_inv[UI_NB_STR_INV];
	SDL_Surface			*i_obj_description[DSCRIP_STR_INV];
	SDL_Surface			*pick_objects[HUD_PICK_OBJ];
};

struct 						s_font
{
	SDL_Color			color;
	const char			*str;
	TTF_Font			*font;
	t_vtx				pos;
	int					size;
	int					l;
	int					r;
};

struct						s_circle
{
	float				x;
	float				y;
	float				radius;
	Uint32				color;
};

struct						s_minimap
{
	int					xmin;
	int					xmax;
	int					ymin;
	int					ymax;

	SDL_Surface			*surface;		// calque sectors
	SDL_Surface			*background;	// calque background

	t_vtx				origin; 		// origin minimap on sdl.surface
};

#endif

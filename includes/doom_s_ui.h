/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 13:57:58 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/24 22:25:19 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_UI
# define DOOM_S_UI

typedef struct s_uitxt		t_uitxt;
typedef struct s_bloc		t_bloc;
typedef struct s_minibloc	t_minibloc;
typedef struct s_uinv		t_uinv;
typedef struct s_hud		t_hud;
typedef struct s_font		t_font;
typedef struct s_circle		t_circle;
typedef struct s_minimap	t_minimap;


struct						s_uitxt
{
	TTF_Font			*arial;
	TTF_Font			*doom;
	TTF_Font			*text;
	TTF_Font			*number;
	SDL_Surface			*string[19];
	SDL_Surface			*t_inv[4];
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

struct					s_minibloc
{
	SDL_Rect			rect;
	SDL_Surface			*sprite;
	int					*pxl;
};

struct					s_bloc
{
	t_minibloc			cross;
	t_minibloc			use;
	SDL_Surface			*bg_empty;
	SDL_Surface			*bg_fill;
	SDL_Surface			*sprite;
	SDL_Rect			rect;
	int					type;
	int					is_visible;
	int					*pxl;
	int					*pxl_obj;
};

struct 						s_uinv
{
	t_bloc				bg;
	t_bloc				wpn[3];
	t_bloc				icons[2];
	t_bloc				objects[6];
	int					is_active;
	int					wwheel;
	int					nb_wpn;
};

struct						s_hud
{
	t_uinv				inventory;
	t_bloc				bar[2];
	t_bloc				faces[4];
	t_bloc				hud_wpn[3];
	t_bloc				objects[6];
	t_wrap_inv			*shortcut[6];
	t_uitxt				text;
	int					is_txt;
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
	t_vtx				origin; // origin minimap
	t_vtx				player; // player pos relatif minimap
};

#endif

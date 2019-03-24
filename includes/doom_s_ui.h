/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 13:57:58 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/24 10:09:50 by abaille          ###   ########.fr       */
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
	SDL_Surface			*string[13];
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
};

struct 						s_uinv
{
	// t_bloc				box[2];
	t_bloc				wpn[3];
	t_bloc				icons[2];
	t_bloc				objects[6];
	SDL_Surface			*front_pic;
	// SDL_Surface			*mini_wpn[3];
	// SDL_Surface			*empt_wpn[3];
	// SDL_Surface			*icon[2];
	// SDL_Surface			*box[2];
	// t_edge				blocs[6];
	// t_edge				wblocs[3];
	// t_edge				iblocs[3];
	int					is_active;
	int					wwheel;
	int					nb_wpn;
};

struct						s_hud
{
	t_bloc				bar[2];
	t_bloc				faces[4];
	t_bloc				hud_wpn[3];
	t_bloc				objects[6];
	SDL_Surface			*empty_b;
	t_wrap_inv			*shortcut[6];
	t_uinv				inventory;
	t_uitxt				text;
	int					is_txt;
	int					mix;
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

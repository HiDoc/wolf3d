/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_hud.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:50:54 by abaille           #+#    #+#             */
/*   Updated: 2019/04/04 19:22:43 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_HUD_H
# define DOOM_S_HUD_H

typedef struct s_minibloc	t_minibloc;
typedef struct s_bloc		t_bloc;
typedef struct s_uinv		t_uinv;
typedef struct s_hud		t_hud;

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
	t_edge				limit;
};

struct 						s_uinv
{
	t_bloc				bg;
	t_bloc				wpn[GAME_NB_WPN];
	t_bloc				icons[2];
	t_bloc				objects[6];
	t_bloc				gems[4];
	int					is_active;
	int					wwheel;
	int					nb_wpn;
};

struct						s_hud
{
	t_uinv				inventory;
	t_bloc				bar[2];
	t_bloc				faces[4];
	t_bloc				hud_wpn[GAME_NB_WPN];
	t_bloc				objects[5];
	t_wrap_inv			*shortcut[5];
	t_uitxt				text;
	int					is_txt;
	int					txt_inv;
	int					txt_pick;
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 13:57:58 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/11 12:35:46 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_UI
# define DOOM_S_UI

typedef struct s_uinv	t_uinv;
typedef struct s_hud	t_hud;
typedef struct s_font	t_font;

struct 					s_font
{
	SDL_Color			color;
	const char			*str;
	const char			*font;
	t_vtx				pos;
	int					size;
	int					l;
	int					r;
};


struct					s_hud
{
	SDL_Surface			*empty_bar;
	SDL_Surface			*bar[2];
	SDL_Surface			*hud_wpn[3];
	SDL_Surface			*pad;
	SDL_Surface			*shadow;
	SDL_Surface			*e_pad[4];
	t_wrap_inv			*shortcut[6];
	int					is_txt;
	int					mix;
};

struct 					s_uinv
{
	SDL_Surface			*front_pic;
	SDL_Surface			*mini_wpn[3];
	SDL_Surface			*empt_wpn[3];
	SDL_Surface			*icon[3];
	SDL_Surface			*box[2];
	t_edge				blocs[6];
	t_edge				wblocs[3];
	t_edge				iblocs[3];
	int					is_active;
	int					wwheel;
	int					nb_wpn;
};

#endif

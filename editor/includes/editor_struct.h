/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:25:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/30 16:25:19 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_STRUCT_H
# define EDITOR_STRUCT_H

enum					e_type
{
	INPUT,
	BUTTON
};

/*
** M_ : MENU
** E_ : EDITOR
** _I : INPUT
** _B : BUTTON
** _ELM_ : 
*/

enum					e_elements
{
	M_I_NEW,
	M_B_START,
	M_B_CANCEL,
	M_B_EXIT,
	M_B_UP,
	M_B_DOWN,
	E_B_NEW,
	E_B_UPLOAD,
	E_B_SAVE,
	E_B_MODE_SELECT,
	E_B_MODE_DRAW,
	E_B_MODE_ELEM,
	E_B_PLAY,
	E_B_ELM_UP,
	E_B_ELM_DOWN,
	E_B_ELM_OBWL,
	E_B_ELM_CONS,
	E_B_ELM_NTTY,
	E_B_ELM_PRFB,
	E_B_ELM_SPEC/*,
	E_B_UP,
	E_B_DOWN*/
};

typedef struct  s_vtx   	t_vtx;
typedef struct  s_sct   	t_sct;
typedef struct	s_elem		t_elem;
typedef struct	s_menu		t_menu;
typedef struct	s_editor	t_editor;
typedef struct  s_env   	t_env;

struct					s_vtx
{
	t_pos			pos;
	t_sct			*sector;
	t_vtx			*next;
};

struct					s_sct
{
	t_vtx			*vtx_current;
	t_vtx			*vtx_start;
	t_vtx			*vtx_end;

	int				close;		// is sector close;

	float			xmin;
	float			xmax;
	float			ymin;
	float			ymax;

	Uint32			color;

	t_sct			*next;
};

struct					s_elem
{
	int				id;
	int				type;
	t_rect			rect;
	char			*str;		// if type == input
	int				str_max;		// if type == input
	int				clicked;
	int				hovered;
	t_elem			*next;
};

struct					s_menu
{
	int				state;
	int				nb_maps;
	int				idx_map;
	char			**maps;
	SDL_Surface		*background;
};

struct					s_editor
{
	// wall textures
	int             nb_wall_txtr;
	int             idx_wall_txtr;
	char            **wall_txtr;
};

struct					s_env
{
	t_data          *data;

	t_editor		editor;
	t_menu			menu;

	char			*map_name;

	// lst sectors
	t_sct			*sct_current;
	t_sct			*sct_start;
	t_sct			*sct_end;

	// hover / select hud
	t_sct			*sct_hover;
	t_vtx			*vtx_hover;

	// data infos
	int				nb_vtx;
	int				nb_sct;
	int				vtx_size; // current

	// state
	int				drawing;		// am i drawing an edge

	// mouse handling
	int				mouse_mode; // 0 : selection / 1 : draw
	int				obj_mode;	// 0/1/2/3/4 wall/cons/ntty/prfb/spe

	// lst elements
	t_elem			*elements;
	// lst wall_objects
	char			**wall_objects;
	// lst consumables
	char			**consumables;
	// lst entities
	char			**entities;
	// lst prefabs
	char			**prefabs;
	// lst specials
	char			**specials;
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:25:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/26 13:56:44 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_STRUCT_H
# define EDITOR_STRUCT_H

enum					e_type
{
	INPUT,
	BUTTON,
	RECT
};

/*
** M_ : MENU
** E_ : EDITOR
** _I : INPUT
** _B : BUTTON
** _ELM_ : element page
** _SELEC_ : selection page
** _MISC_ : misc page
*/

enum					e_elements
{
	M_I_NEW,
	M_B_START,
	M_B_CANCEL,
	M_B_UP,
	M_B_DOWN,
	E_R_RECT,
	E_B_MENU,
	E_B_SAVE,
	E_B_MODE_SELECT,
	E_B_MODE_MOVE,
	E_B_MODE_DRAW,
	E_B_MODE_ELEM,
	E_B_MODE_MISC,
	E_B_PLAY,
	E_B_ELM_UP,
	E_B_ELM_DOWN,
	E_B_ELM_OBWL,
	E_B_ELM_CONS,
	E_B_ELM_NTTY,
	E_B_ELM_PRFB,
	E_B_ELM_SPEC,
	E_B_SELEC_DEL,
	E_I_SELEC_HEIGHT,
	E_I_SELEC_GRAVITY,
	E_B_SELEC_SPLIT,
	E_B_SELEC_DOOR,
	E_B_SELEC_FDOOR,
	E_B_SELEC_CEIL,
	E_B_SELEC_SKY,
	E_B_MISC_MUSIC,
	E_B_MISC_SKY
};

enum					e_obj_category
{
	WALL_OBJ,
	CONSUMABLE,
	ENTITY,
	PREFAB,
	SPECIAL
};

typedef struct	s_w_vtx		t_w_vtx;
typedef struct  s_vtx   	t_vtx;
typedef struct  s_sct   	t_sct;
typedef struct	s_elem		t_elem;
typedef struct	s_object	t_object;
typedef struct	s_menu		t_menu;
typedef struct	s_editor	t_editor;
typedef struct  s_env   	t_env;

struct					s_w_vtx
{
	int			fdoor;	// is final door
	int			door;	// is door
	t_vtx		*vtx;
	t_sct		*sector;
	t_w_vtx		*next;
};

struct					s_vtx
{
	t_pos			pos;
	t_vtx			*next;
};

struct					s_sct
{
	int				id;			// identifiant du secteur

	int				nb_w_vtx;
	t_w_vtx			*w_vtx_current;	// vertex wrapper
	t_w_vtx			*w_vtx_start;	// vertex wrapper

	int				close;		// is sector close;

	int				height;
	int				gravity;

	int				roof;		// ceil or sky : 0 / 1

	float			xmin;
	float			xmax;
	float			ymin;
	float			ymax;

	Uint32			color;

	t_sct			*next;
};

struct					s_elem
{
	int				ref;		// if btn object
	int				id;
	int				type;
	SDL_Rect		rect;
	Uint32			color;
	SDL_Surface		*image;
	char			*str;		// if type == input
	int				str_max;	// if type == input
	int				clicked;
	int				hovered;
	t_elem			*next;
};

struct					s_object
{
	t_pos			pos;
	float			dir;	// if entity

	t_sct			*sct;
	int				ref;
	int				category;
	char			*name;

	Uint32			icon_color; // replace by image
	t_object		*next;
};

struct					s_menu
{
	int				state;
	int				nb_maps;
	int				idx_map;
	t_elem			*btn_maps;		// upload list
	t_elem			*selected;		// upload selected
	SDL_Surface		*background;
};

struct					s_editor
{
	time_t			timestamp;	// error_msg timestamp
	char			*error_msg;

	// mouse handling
	int				mouse_mode;

	// wall textures
	int             nb_wall_txtr;
	int             idx_wall_txtr;
	char            **wall_txtr;

	// drag vertex;
	int				mouse_drag;
	t_pos			new_pos;

	// grid move
	int				grid_drag;
	t_pos			grid_init_pos;
	t_pos			grid_mouse_var;
	t_pos			grid_translate;

	// hover / select
	t_vtx			*vtx_hover;
	t_w_vtx			*edg_hover;
	t_sct			*sct_hover;
	t_object		*obj_hover;

	t_vtx			*vtx_select;
	t_w_vtx			*edg_select;
	t_sct			*sct_select;
	t_object		*obj_select;

	// size current edge draw
	int				vtx_size;

	// state
	int				drawing;		// am i drawing an edge
};

struct					s_env
{
	t_data          *data;

	t_menu			menu;
	t_editor		editor;

	char			*map_name;

	// lst vertex
	t_vtx			*vertex;
	// lst sectors
	t_sct			*sct_current;
	t_sct			*sct_start;
	// lst objects
	t_object		*objects;
	// lst elements
	t_elem			*elements;
	// lst button objects
	t_elem			*btn_objs;

	// current elem / objects flags
	t_elem			*obj_elem;	// obj selectionne
	int				spawn_set;	// spawn pose, en attente de direction
	int				obj_mode;	// 0/1/2/3/4 wall/cons/ntty/prfb/spe

	// variables
	float			grid_scale;

	// relative mouse_position
	t_pos			mouse;

	// data infos
	int				nb_vtx;
	int				nb_sct;
};

#endif

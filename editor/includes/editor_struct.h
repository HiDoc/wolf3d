/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:25:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 11:39:37 by sgalasso         ###   ########.fr       */
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

enum					e_pages
{
	MENU,
	EDITOR,
	S_VTX,
	S_OBJ,
	S_EDG,
	S_SCT,
	S_MSC,
	DRAW,
	ELEM
};

enum					e_elements
{
	M_I_NEW,
	M_B_START,
	E_R_RECT,
	E_B_SAVE,
	E_B_MODE_SELECT,
	E_B_MODE_MOVE,
	E_B_MODE_DRAW,
	E_B_MODE_ELEM,
	E_B_ELM_UP,
	E_B_ELM_DOWN,
	E_B_DRW_UP,
	E_B_DRW_DOWN,
	E_B_ELM_OBWL,
	E_B_ELM_CONS,
	E_B_ELM_NTTY,
	E_B_ELM_PRFB,
	E_B_ELM_SPEC,
	E_B_SELEC_VTX_DEL,
	E_B_SELEC_OBJ_DEL,
	E_B_SELEC_EDG_DEL,
	E_B_SELEC_SCT_DEL,
	E_I_SELEC_HCEIL,
	E_I_SELEC_HFLOOR,
	E_I_SELEC_GRAVITY,
	E_B_SELEC_SPLIT,
	E_B_SELEC_NORMAL,
	E_B_SELEC_DOOR,
	E_B_SELEC_FDOOR,
	E_B_SELEC_CEIL,
	E_B_SELEC_SKY,
	E_B_SELEC_MUSIC,
	E_B_SELEC_SBTX,
	E_B_SELEC_MISC_UP,
	E_B_SELEC_MISC_DOWN,
	ENUM_END
};

typedef struct s_w_vtx		t_w_vtx;
typedef struct s_vtx		t_vtx;
typedef struct s_sct		t_sct;
typedef struct s_elem		t_elem;
typedef struct s_object		t_object;
typedef struct s_dropdown	t_dropdown;
typedef struct s_menu		t_menu;
typedef struct s_editor		t_editor;
typedef struct s_env		t_env;

/*
**	s_w_vtx
**
**	ref		: texture reference
**	size	: edge size
*/

struct					s_w_vtx
{
	int			ref;
	int			size;
	t_vtx		*vtx;
	t_sct		*sector;
	t_w_vtx		*next;
};

/*
**	s_vtx
**
**	id		: updated at level_export
*/

struct					s_vtx
{
	int				id;
	t_pos			pos;
	t_vtx			*next;
};

/*
**	s_sct
**
**	id		: update at creation and level_export
**	roof	: 1 ceil / 0 sky
**	type	: 0 normal / 1 door / 2 fdoor
**	color	: ?
*/

struct					s_sct
{
	int				id;
	int				nb_w_vtx;
	t_w_vtx			*w_vtx_current;
	t_w_vtx			*w_vtx_start;
	int				close;
	int				ceil;
	int				floor;
	int				gravity;
	int				roof;
	int				type;
	float			xmin;
	float			xmax;
	float			ymin;
	float			ymax;
	Uint32			color;
	t_sct			*next;
};

/*
**	s_elem
**
**	ref		: ?
**	id		: ?
**	type	: ?
**	dd		: dropdown (if elem of dropdown)
**	str_max	: ? for inputs
**	visible	: if visible on dropdown
**	page	: ?
**	clicked	: ?
**	hovered	: ?
*/

struct					s_elem
{
	int				ref;
	int				id;
	int				type;
	int				dd;
	SDL_Rect		rect;
	Uint32			color;
	SDL_Surface		*image;
	Mix_Music		*audio;
	char			*str;
	int				str_max;
	void			(*event_fc)(t_env *);
	int				visible;
	int				page;
	int				clicked;
	int				hovered;
	t_elem			*next;
};

/*
**	s_object
**
**	icon_color	: ?
*/

struct					s_object
{
	int				ref;
	t_pos			pos;
	float			dir;
	t_sct			*sct;
	int				iswpn;
	Uint32			color;
	int				dd;
	char			*name;
	Uint32			icon_color;
	t_object		*next;
};

enum					e_dropdowm_name
{
	DD_WALLTX,
	DD_SBTX,
	DD_BGAUDIO,
	DD_WOBJ,
	DD_CONS,
	DD_NTTY,
	DD_PRFB,
	DD_SPEC
};

struct					s_dropdown
{
	int				nb_element;
	int				idx_element;
	t_elem			*start;
	t_elem			*current;
};

struct					s_menu
{
	int				state;
	SDL_Surface		*background;
};

/*
**	s_editor
**
**	timestamp	: for error message
**	new_ois		: for mouse_drag
**	oneend		: une seule fin
**	drawing		: am i drawing an edge
*/

struct					s_editor
{
	t_vtx			*vertex;
	t_sct			*sct_current;
	t_sct			*sct_start;
	t_object		*objects;
	time_t			timestamp;
	char			*error_msg;
	t_dropdown		dropdown[12];
	void			(*display_fc)(t_env *);
	int				(*mode)(t_env *);
	int				mouse_drag;
	t_pos			new_pos;
	t_elem			*curr_elem_btn;
	int				curr_elem_dd;
	int				grid_drag;
	t_pos			grid_init_pos;
	t_pos			grid_mouse_var;
	t_pos			grid_translate;
	t_vtx			*vtx_hover;
	t_w_vtx			*edg_hover;
	t_sct			*sct_hover;
	t_object		*obj_hover;
	t_vtx			*vtx_select;
	t_w_vtx			*edg_select;
	t_sct			*sct_select;
	t_object		*obj_select;
	int				oneend;
	int				onespawn;
	int				spawn_set;
	t_pos			spawn_pos;
	float			spawn_dir;
	int				drawing;
	float			grid_scale;
};

struct					s_env
{
	t_data			*data;
	char			*map_name;
	t_menu			menu;
	t_editor		editor;
	t_elem			*elements;
	t_pos			mouse;
	int				nb_vtx;
	int				nb_sct;
};

#endif

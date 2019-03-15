/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:25:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/15 15:34:47 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_STRUCT_H
# define EDITOR_STRUCT_H

typedef struct  s_vtx   t_vtx;
typedef struct  s_sct   t_sct;
typedef struct	s_menu	t_menu;
typedef struct  s_env   t_env;

struct					s_vtx
{
	t_pos		pos;
	t_vtx		*next;
};

struct					s_sct
{
	t_vtx		*vtx_current;
	t_vtx		*vtx_start;
	t_vtx		*vtx_end;

	int			close;		// is sector close;

	float		xmin;
	float		xmax;
	float		ymin;
	float		ymax;

	Uint32		color;

	t_sct		*next;
};

struct					s_menu
{
	int				state;
	int				nb_maps;
	char			**maps;
	SDL_Surface		*background;
};

struct					s_env
{
	t_data          *data;

	t_menu			menu;

	char			*map_name;

	// sectors
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

	// mouse flag
	int				mouse_mode;
};

#endif

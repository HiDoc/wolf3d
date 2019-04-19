/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:58:34 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/19 02:43:23 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# define C_BLACK 0xFF000000
# define C_WHITE 0xFFFFFFFF
# define C_RED 0xFF0000FF
# define C_GREEN 0xFF00FF00
# define C_BLUE 0xFFFF0000

# define C_GREY 0xFF8C8C8C

# define VRX_MAX 500
# define EDG_MAX 250
# define SCT_MAX 50

# define PXL_VAL_MAX 20

# include <stdio.h>

# include "libft.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_image.h>
# include <dirent.h>
# include <math.h>

# include "libui_struct.h"
# include "editor_struct.h"
# include "libui.h"

/*
**	init/
*/

void		init_env(t_env *env, t_data *data);

/*
** release ////////////////// a ranger
*/

void        dir_del(void **ap);		// close directory
void        wdw_del(void **ap);		// destroy window
void        rdr_del(void **ap);		// destroy renderer
void        srf_del(void **ap);		// free surface
void        txr_del(void **ap);		// destroy texture
void        crs_del(void **ap);		// destroy cursor
void        ttf_del(void **ap);		// free font

/*
**	create_delete/
*/

void		create_object(t_elem *element, t_env *env);
void		create_vertex(t_pos pos, t_env *env);
void		create_w_vertex(t_vtx *vtx, t_env *env);
void        insert_w_vertex(t_w_vtx *prev, t_vtx *vtx, t_env *env);
void		create_sector(t_env *env);
void        delete_object(t_object *obj, t_env *env);
void		delete_sector(t_sct *sector, t_env *env);

/*
**	display/
*/

void        menu(t_env *env);
void		editor(t_env *env);
void		display_interface(t_env *env);
void		display_selection(t_env *env);
void		display_drawing(t_env *env);
void		display_element(t_env *env);

/*
**	events/
*/

int	        menu_events(t_env *env);
int			handle_events(t_env *env);
int			draw_mode(t_env *env);
int			select_mode(t_env *env);
int			elem_mode(t_env *env);
int			move_mode(t_env *env);
t_vtx		*target_vertex(t_env *env);
t_w_vtx		*target_edge(t_pos pos, t_env *env);
t_sct		*target_sector(t_pos pos, t_env *env);
t_object	*target_object(t_pos pos, t_env *env);
int			onSegment(t_pos p, t_pos q, t_pos r); // temporaire
//float		pointside(t_pos p, t_vrx v0, t_vrx v1);

/*
**	utils/
*/

t_pos		get_edge_center(t_pos a, t_pos b);
float       pointside(t_pos p, t_pos p0, t_pos p1);
int			input_add(int elem, char *key, t_env *env);
int			input_del(int elem, t_env *env);
int			ft_strchri(char *str, char c);
float		pythagore(t_pos p1, t_pos p2);
void		export_map(t_env *env);
int			poscmp(t_pos a, t_pos b);
t_elem		*get_element(int id, t_env *env);
char		*ft_zstrjoin(char *s1, char *s2);
int			vertex_in_sector(t_sct *sector, t_pos pos);

#endif

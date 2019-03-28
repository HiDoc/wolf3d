/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:58:34 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/28 20:47:08 by sgalasso         ###   ########.fr       */
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

# define SCT_VRX_MAX 50

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
**	display/
*/

void        menu(t_env *env);
void		editor(t_env *env);
void		display_interface(t_env *env);
void		display_selection(t_env *env);
void		display_drawing(t_env *env);

/*
**	events/
*/

int	        menu_events(t_env *env);
int			handle_events(t_env *env);
int			draw_mode(t_env *env);
int			select_mode(t_env *env);
t_vtx		*target_vertex(t_env *env);
t_sct		*target_sector(t_pos pos, t_env *env);
int			vertex_in_sector(t_sct *sector, t_pos pos, t_env *env);
int			onSegment(t_pos p, t_pos q, t_pos r); // temporaire
//float		pointside(t_pos p, t_vrx v0, t_vrx v1);

/*
**	utils/
*/

int			export_map(t_env *env);
int			poscmp(t_pos a, t_pos b);
t_elem		*get_element(int id, t_env *env);

#endif

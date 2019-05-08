/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:05:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/08 22:03:47 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_UI_H
# define DOOM_F_UI_H

void		init_minimap(t_env *env);
void		ui_minimap(t_env *env);
int			point_in_circle(t_vtx vtx, t_circle circle);
SDL_Surface	*rotate_surface(SDL_Rect src_rect, SDL_Surface *src,
			SDL_Surface *dst, t_vtx origin, t_circle circle, t_env *env);
t_edge		translate_edge(t_vctr player_position, t_vtx v1, t_vtx v2);
t_edge		rotate_edge(t_player player, t_edge v);
void		ui_draw_line(SDL_Surface *surface, t_edge edge, Uint32 color);
void		ui_draw_vector(SDL_Surface *surface, t_vtx vtx,
			float angle, t_vtx val);
void		ui_draw_rect(SDL_Surface *surface, SDL_Rect rect, Uint32 color);
void		ui_draw_full_rect(SDL_Surface *surface, SDL_Rect rect, Uint32 color);
void		ui_draw_circle(SDL_Surface *surface, t_circle circ);
void		ui_draw_full_circle(SDL_Surface *surface, t_circle circ);
void		ui_draw_string(SDL_Surface *dst_surface, SDL_Rect rect,
			char *text, Uint32 color, t_env *env);
void		img_scaled_copy(SDL_Surface *src, SDL_Surface *dst);
void		draw_scaled_string(SDL_Surface *dst, t_font data, SDL_Surface *src, t_vtx pos);
int			ui_draw_msg(t_env *env, int *nb, int *tframe);
int			load_sounds(t_weapon *wpn, char *name, char *action);

#endif

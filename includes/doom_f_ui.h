/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:05:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/04 18:17:23 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_UI_H
# define DOOM_F_UI_H

int			init_minimap(t_env *env);
void		ui_minimap(t_env *env);

void		ui_draw_line(SDL_Surface *surface, t_edge edge, Uint32 color);
void		ui_draw_vector(SDL_Surface *surface, t_vtx vtx, float angle,
			float start, float size, Uint32 color);
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

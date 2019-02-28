/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_engine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:41:58 by sgalasso          #+#    #+#             */
/*   Updated: 2019/02/28 15:58:43 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_ENGINE_H
# define DOOM_F_ENGINE_H

void		LoadData(t_engine *e);
void		UnloadData(SDL_Texture *texture, SDL_Renderer *renderer,
			SDL_Window *window, t_engine *e);

void		draw_screen(t_engine *e);
int			is_crossing(const t_vtx p, t_vtx d, const t_vtx *vert, unsigned s);
int			is_bumping(const t_sector *sect, float eyeheight,
			unsigned s, t_engine *e);
void		bumping_score(t_vtx *d, t_vtx b);

void		player_moving(t_vision *v, int set, t_engine *e);
void		player_falling(t_vision *v, t_engine *e);
void		player_collision(t_engine *e, t_vision *v);

t_edge		current_edge(t_vctr player_position, t_vtx v1, t_vtx v2);
t_edge 		rotation_edge(t_player player, t_edge v);
t_edge 		scale_edge(t_edge t);
void		clip_view(t_edge *t);

int			ini_queue(t_engine *e, t_queue *q);
int     	verify_map(t_engine *e);
int     	verify_hull(t_engine *e);

void		vline(t_drawline line, t_engine *e);
int			transform_vertex(t_engine *e, t_queue *q, t_transf *ctn, int s);
#endif

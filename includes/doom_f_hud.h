/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_hud.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 12:00:42 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 19:14:31 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_HUD_H
# define DOOM_F_HUD_H

SDL_Surface *ui_img(char *file, int i, int variable);
void		draw_img(t_env *env, SDL_Surface *img, t_bloc *bloc);

int         print_hud(t_env *env);
void		print_inventory(t_env *env);

void    	put_data(t_env *env, t_font data);
int     	ui_txt_inv(t_env *env, int i, int r);
int         ui_put_fps(t_env *env, int fps);
int		    ui_icon_data(t_env *env, t_vtx v, int iter);
int			draw_pick_infos(t_env *env, t_wrap_sect *obj, int ref);

void		print_stats(t_env *env, float size, t_vtx w, t_vtx h);

Uint32		mix_colors(t_env *env, Uint32 cr1, Uint32 cr2, float p);

float		size_bar(int tmax, int datamax, int data);
void		check_object_stack(t_env *e, t_wrap_inv *pack, t_ixy ref);

void		display_credits(t_env *e);
int			update_render(t_env *e);
void		stats_endgame(t_env *e);
void		draw_inter(t_env *e, int l);
#endif

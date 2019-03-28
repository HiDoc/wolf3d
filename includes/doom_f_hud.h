/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_hud.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 12:00:42 by abaille           #+#    #+#             */
/*   Updated: 2019/03/28 15:02:03 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_HUD_H
# define DOOM_F_HUD_H


SDL_Surface *surface_fr_png(char *path);
int			copy_img(Uint32 *pxl, SDL_Surface *img);
SDL_Surface *ui_img(char *file, int i);
int			draw_img(t_env *env, SDL_Surface *img, t_bloc *bloc);
int		    scale_img(Uint32 *dest, SDL_Rect rect, SDL_Surface *img);
int			set_surface_alpha(SDL_Surface *surface, Uint8 alpha, t_rgba *c);

int			init_hud_blocs(t_env *env);
int         print_hud(t_env *env);
int			print_inventory(t_env *env);

int    		ui_put_data(t_env *env, t_font data);
int         ui_txt_inv(t_env *env);
int         ui_put_fps(t_env *env, int fps);
int		    ui_icon_data(t_env *env, t_vtx v, int iter);
int			draw_pick_infos(t_env *env, t_wrap_sect *obj, int ref);

Uint32		mix_colors(t_env *env, Uint32 cr1, Uint32 cr2, float p);

#endif

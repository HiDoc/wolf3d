/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_hud.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 12:00:42 by abaille           #+#    #+#             */
/*   Updated: 2019/03/26 12:05:45 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_HUD_H
# define DOOM_F_HUD_H


int			draw_img(t_env *env, SDL_Surface *img, t_bloc *bloc, float ratio);

int         print_hud(t_env *env);
int			print_inventory(t_env *env);
int 		init_hud_container(t_env *env);
SDL_Surface *ui_img(char *file, int i);

int			copy_img(Uint32 *pxl, SDL_Surface *img);

int			*scale_hud_img(SDL_Surface *img, SDL_Rect rect, int *tab);
int			need_scale(SDL_Surface *img, SDL_Rect rect);
int			scale_tab(SDL_Surface *img, SDL_Rect rect, int *tab);

int    		ui_put_data(t_env *env, t_font data);
int         ui_txt_inv(t_env *env);
int         ui_put_fps(t_env *env, int fps);
int		    ui_icon_data(t_env *env, t_vtx v, int iter);

SDL_Surface *surface_fr_png(char *path);
SDL_Surface *img_wpn(char *filename);
int		    scale_img(Uint32 *dest, SDL_Rect rect, SDL_Surface *img, t_ixy padding);
int			set_surface_alpha(SDL_Surface *surface, Uint8 alpha, t_rgba *c);
void	    draw_flat_rect(SDL_Surface *surface, t_edge edge, Uint32 color);

Uint32		mix_colors(t_env *env, Uint32 cr1, Uint32 cr2, float p);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:05:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/25 18:43:46 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_UI_H
# define DOOM_F_UI_H

void		ui_minimap(t_env *env);

SDL_Surface	*ui_make_surface(int height, int width);
void		ui_draw_line(SDL_Surface *surface, t_edge edge, Uint32 color);
void		ui_draw_vector(SDL_Surface *surface, t_vtx vtx, float angle,
			float start, float size, Uint32 color);
void		ui_draw_rect(SDL_Surface *surface, SDL_Rect rect, Uint32 color);
void		ui_draw_full_rect(SDL_Surface *surface, SDL_Rect rect, Uint32 color);
void		ui_draw_circle(SDL_Surface *surface, t_circle circ);
void		ui_draw_full_circle(SDL_Surface *surface, t_circle circ);
void		ui_draw_string(SDL_Surface *dst_surface, SDL_Rect rect,
			char *text, Uint32 color, t_env *env);

int 		init_hud_container(t_env *env);
int			init_fonts(t_uitxt*f);

int    		ui_put_data(t_env *env, t_font data);
int			set_simple_strings(t_env *env, int i, int j);
int			draw_scaled_string(t_font data, SDL_Surface *src, SDL_Surface *dst, t_vtx pos);
int         ui_txt_inv(t_env *env);
SDL_Surface *ui_img(char *file, int i);
int         ui_put_fps(t_env *env, int fps);
int		    ui_icon_data(t_env *env, t_vtx v, int iter);
int			ui_draw_msg(t_env *env, int *nb, int *tframe);
int			ui_text_msg(t_env *env, char *msg);

int         print_hud(t_env *env);
int			print_inventory(t_env *env);

int			copy_img(Uint32 *pxl, SDL_Surface *img);

int			*scale_hud_img(SDL_Surface *img, SDL_Rect rect, int *tab);
int			need_scale(SDL_Surface *img, SDL_Rect rect);
int			scale_tab(SDL_Surface *img, SDL_Rect rect, int *tab);

SDL_Surface *surface_fr_png(char *path);
SDL_Surface *img_wpn(char *filename);
int			draw_img(t_env *env, SDL_Surface *img, t_bloc *bloc, float ratio);
// int			draw_img(t_env *env, SDL_Surface *img, t_ixy start, t_edge limit_img);
int		    scale_img(Uint32 *dest, SDL_Rect rect, SDL_Surface *img, t_ixy padding);
int			set_surface_alpha(SDL_Surface *surface, Uint8 alpha, t_rgba *c);
void	    draw_flat_rect(SDL_Surface *surface, t_edge edge, Uint32 color);

Uint32		mix_colors(t_env *env, Uint32 cr1, Uint32 cr2, float p);

int			load_sounds(t_weapon *wpn, char *name, char *action);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_ui.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:05:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/10 18:10:19 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_UI_H
# define DOOM_F_UI_H

void		ui_minimap(t_env *env);

SDL_Surface	*ui_make_surface(int height, int width);
void		ui_draw_line(SDL_Surface *surface, t_edge edge, Uint32 color);
void		ui_draw_rect(SDL_Surface *surface, SDL_Rect rect, Uint32 color);
void		ui_draw_full_rect(SDL_Surface *surface, SDL_Rect rect, Uint32 color);


int         text_font(t_env *env, char *str, t_vctr pos, SDL_Color color);
int    		number_font(t_env *env, char *str, t_vctr pos, SDL_Color color);
int    		ui_put_string(t_env *env, t_font data);
int         ui_txt_inv(t_env *env);
SDL_Surface *ui_img(char *filename);
int         ui_put_fps(t_env *env, int fps);
int		    ui_icon_data(t_env *env, t_vtx v, int iter);
int			ui_draw_msg(t_env *env, int *nb, int *tframe);
int			ui_text_msg(t_env *env, char *msg);

int         print_hud(t_env *env);
int			print_inventory(t_env *env);

SDL_Surface *surface_fr_png(char *path);
SDL_Surface *img_wpn(char *filename);
void	    put_img_inv(t_env *env, SDL_Surface *img, t_edge bloc, t_edge padding);
void	    draw_img(t_env *env, t_edge edge, SDL_Surface *img, t_ixy pxl);
int		    scale_img(Uint32 *dest, SDL_Rect rect, SDL_Surface *img, t_ixy padding);
int			set_surface_alpha(SDL_Surface *surface, Uint8 alpha, t_rgba *c);
void	    draw_flat_rect(SDL_Surface *surface, t_edge edge, Uint32 color);

Uint32		mix_colors(Uint32 cr1, Uint32 cr2, float p, int *mix);

void	    load_sounds(t_env *env);

#endif
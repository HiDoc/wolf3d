/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:52:53 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/04 17:45:17 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "doom_define.h"
# include "doom_maths.h"
# include "doom_struct_assets.h"
# include "doom_struct_obj.h"
# include "doom_struct_gameplay.h"
# include "doom_engine.h"
# include "doom_struct_env.h"


int         init_consumable(t_env *env);
int		    pick_object(t_env *env, t_wrap_sect *obj);
int		    drop_object(t_env *env, t_wrap_inv *object);
int		    give_shield(void *e, t_wrap_inv *object);
int		    give_health(void *e, t_wrap_inv *object);

int         init_character(t_character *new);
int		    init_weapon(t_env *env);
int         init_inventory_ui(t_env *env);

int         wpn_mouse_wheel(t_env *env, SDL_Event event);

void	    put_gun(t_env *env, SDL_Surface *sprite);

int		    scale_img(Uint32 *dest, SDL_Rect rect, SDL_Surface *img, t_ixy padding);
void	    draw_flat_rect(SDL_Surface *surface, t_edge edge, Uint32 color);
int			select_object(t_wrap_inv *object, int x, int y, t_edge *p);

int			set_inventory(t_env *env);
int			print_inventory(t_env *env);
int         action_inventory(t_env *env, int x, int y);
void	    put_img_inv(t_env *env, SDL_Surface *img, t_edge bloc, t_edge padding);

int         text_font(t_env *env, char *str, t_vctr pos, SDL_Color color);
int         doom_font(t_env *env, char *str, t_vctr pos, SDL_Color color);
int         ui_txt_inv(t_env *env);
SDL_Surface *ui_img(char *filename);
int         ui_put_fps(t_env *env, int fps);
int		    ui_icon_data(t_env *env, t_vtx v, int iter);

int         init_hud(t_env *env);
int         print_hud(t_env *env);

SDL_Surface *surface_fr_png(char *path);
SDL_Surface *img_wpn(char *filename);
void	    draw_img(t_env *env, t_edge edge, SDL_Surface *img, t_ixy pxl);

int			sdl_keyhook(t_env *env, SDL_Event event);
void	    load_sounds(t_env *env);

void		LoadData(t_engine *e, t_env *env);
int		    fill_objects_sector(t_sector *sector, t_vtx v, int ref);

void		setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32		getpixel(SDL_Surface *surface, int x, int y);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_engine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:41:58 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/10 13:19:52 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_ENGINE_H
# define DOOM_F_ENGINE_H

void		LoadData(t_engine *e, t_env *env);
void		UnloadData(SDL_Texture *texture, SDL_Renderer *renderer,
			SDL_Window *window, t_engine *e);

void		dfs(t_env *env);
int			is_crossing(const t_vtx p, t_vtx d, const t_vtx *vert, unsigned s);
int			is_bumping(const t_sector *sect, float eyeheight,
			unsigned s, t_engine *e);
void		bumping_score(t_vtx *d, t_vtx b);

void		player_moving(t_vision *vision, int set, t_engine *engine);
void		player_falling(t_vision *vision, t_engine *engine, float limit, float speed);
void		player_collision(t_engine *engine, t_vision *vision, int jetpack);

t_edge		current_edge(t_vctr player_position, t_vtx v1, t_vtx v2);
t_edge 		rotation_edge(t_player player, t_edge to_rotate);
t_edge 		scale_edge(t_edge to_scale);
void		clip_view(t_raycast *ctn);
int			ini_queue(t_engine *engine, t_queue *queue);
int     	verify_map(t_engine *engine);
int     	verify_hull(t_engine *engine, t_sector *sector, t_vtx *vertexes);

void		vline(t_drawline line, t_env *env);
void		render_cwall(t_drawline line, t_env *env);
void		render_nwall(t_drawline line, t_env *env);
void		render_floor(t_drawline line, t_env *env);
void		render_nfloor(t_drawline line, t_env *env);
void		render_ceil(t_drawline line, t_env *env);
void		render_nceil(t_drawline line, t_env *env);
int			transform_vertex(t_engine *e, t_queue *q, t_raycast *ctn, int s);

int         init_consumable(t_env *env);
int		    pick_object(t_env *env, t_wrap_sect *obj);
int		    drop_object(t_env *env, t_wrap_inv *object);
int		    give_shield(void *e, t_wrap_inv *object);
int		    give_health(void *e, t_wrap_inv *object);
int			give_ammo(void *e, t_wrap_inv *obj);
int			give_jetpack(void *e, t_wrap_inv *obj);
int			check_object_type(t_env *env, int ref);

int         init_character(t_character *new);
int		    init_weapon(t_env *env);
int         init_inventory_ui(t_env *env);

int			pick_weapon(t_env *env, t_wrap_sect *obj);
int         wpn_mouse_wheel(t_env *env, SDL_Event event);

int		    put_gun(t_env *env, SDL_Surface *sprite);
int			put_gun_load(t_env *env, int frame);
int			loop_frames(t_env *env, int *frame);
int			put_gun_shoot(t_env *env, int frame);
int			load_weapon(t_env *env);
int			reload_ammo(t_env *env);

int		    scale_img(Uint32 *dest, SDL_Rect rect, SDL_Surface *img, t_ixy padding);
int			SetSurfaceAlpha (SDL_Surface *surface, Uint8 alpha, t_rgba *c);
void	    draw_flat_rect(SDL_Surface *surface, t_edge edge, Uint32 color);
int			select_object(t_wrap_inv *object, int x, int y, t_edge *p);

int			set_inventory(t_env *env);
int			print_inventory(t_env *env);
int         action_inventory(t_env *env, int x, int y);
void	    put_img_inv(t_env *env, SDL_Surface *img, t_edge bloc, t_edge padding);

int         text_font(t_env *env, char *str, t_vctr pos, SDL_Color color);
int         doom_font(t_env *env, char *str, t_vctr pos, SDL_Color color);
int    		number_font(t_env *env, char *str, t_vctr pos, SDL_Color color);
int         ui_txt_inv(t_env *env);
SDL_Surface *ui_img(char *filename);
int         ui_put_fps(t_env *env, int fps);
int		    ui_icon_data(t_env *env, t_vtx v, int iter);
int			ui_draw_msg(t_env *env, int *nb, int *tframe);
int			ui_text_msg(t_env *env, char *msg);

int         init_hud(t_env *env);
int         print_hud(t_env *env);

SDL_Surface *surface_fr_png(char *path);
SDL_Surface *img_wpn(char *filename);
void	    draw_img(t_env *env, t_edge edge, SDL_Surface *img, t_ixy pxl);

int			sdl_keyhook(t_env *env, SDL_Event event);
int			mouse_shoot(t_env *env);
void	    load_sounds(t_env *env);

int		    fill_objects_sector(t_sector *sector, t_vtx v, int ref, int is_wpn);

#endif

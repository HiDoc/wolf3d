/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_gameplay.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:32:27 by abaille           #+#    #+#             */
/*   Updated: 2019/04/06 16:33:19 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_GAMEPLAY_H
# define DOOM_F_GAMEPLAY_H

int			god_mod(t_env *env);

int			is_pickable_object(t_env *env, t_sector *sector);
int		    pick_object(t_env *env, t_wrap_sect *obj);
int		    drop_object(t_env *env, t_wrap_inv *object);
int			select_object(t_wrap_inv *object, t_ixy xy, t_bloc *p, int limit);
int		    give_shield(void *e, t_wrap_inv *object);
int		    give_health(void *e, t_wrap_inv *object);
int			give_ammo(void *e, t_wrap_inv *obj);
int			give_jetpack(void *e, t_wrap_inv *obj);
int			check_object_type(t_wrap_inv *pack, int ref, int limit);
int         action_inventory(t_env *env, int x, int y);

int			handle_gems(t_env *env);
int			action_gems(t_env *env, t_wrap_inv *shortcut, int i);

int			pick_weapon(t_env *env, t_wrap_sect *obj);
int			set_current_wpn(t_env *env, t_inventory *inv, int i);
int			drop_wpn(t_env *env, t_wrap_wpn *wpn);
int         wpn_mouse_wheel(t_env *env, SDL_Event event);

int		    put_gun(t_env *env, t_bloc *bloc);
int			put_gun_load(t_env *env, int frame);
int			put_gun_shoot(t_env *env, int frame);
int			handle_weapon(t_env *env, int *frame);
int			load_weapon(t_env *env);
int			reload_ammo(t_env *env);

int			sdl_keyhook_game(t_env *env, SDL_Event event, const Uint8 *keycodes);
int			sdl_keyhook_inventory(t_env *env, SDL_Event event, const Uint8 *keycodes);
int			mouse_shoot(t_env *env);

int			bot_wall_collision(t_player *bot, t_sector *sect);
void		impact_player(t_env *env, t_impact *shot, t_vtx player, int damage);
int			new_bullet(t_impact *new, t_player *p, float velocity);
int			init_enemies(t_env *env);
void		bot_status(t_env *env, t_vtx player, t_wrap_enmy *enemy, Uint8 *keycodes);
void		bot_action(t_env *env, t_sector *sector);
int			pl_new_kill(t_env *env, t_player *p, t_character *player);
void		player_bullet(t_env *env, t_character *p, int damage);
int			enemies_frames(t_env *env, t_sector *sector);

int			init_doors_images(t_env *env);
int			door_neighbors(t_engine *e, const t_vtx *vertex, int s);
int			select_door(t_engine *e);
int			open_door(t_env *env);
int			handle_doors(t_env *env);
#endif

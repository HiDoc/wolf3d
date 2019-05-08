/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_gameplay.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:32:27 by abaille           #+#    #+#             */
/*   Updated: 2019/05/08 13:06:33 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_GAMEPLAY_H
# define DOOM_F_GAMEPLAY_H

int			god_mod(t_env *env);
void		gameover(t_env *e);

int			access_object(t_env *env, t_sector *sector);
int			pick_object(t_env *env, t_wrap_sect *obj);
void		drop_object(t_env *env, t_wrap_inv *object);
int			select_object(t_wrap_inv *object, t_ixy xy, t_bloc *p, int limit);
int			give_life(void *e, t_wrap_inv *object);
int			give_ammo(void *e, t_wrap_inv *obj);
int			give_jetpack(void *e, t_wrap_inv *obj);
int			check_object_type(t_wrap_inv *pack, int ref, int limit);
void		action_inventory(t_env *env, int x, int y);
int			get_inventory_place(t_env *env);

int			blue_gem(t_env *env);
int			green_gem(t_env *env);
int			red_gem(t_env *env);
int			purple_gem(t_env *env);
void		handle_gems(t_env *env);
void		action_gems(t_env *env, t_wrap_inv *shortcut, int i);

int			select_wpn(t_wrap_wpn *wpn, t_ixy xy, t_bloc *p, int limit);
int			pick_weapon(t_env *env, t_wrap_sect *obj);
int			set_current_wpn(t_env *env, t_inventory *inv, int i);
int			drop_wpn(t_env *env, t_wrap_wpn *wpn);
void		wpn_mouse_wheel(t_env *env, SDL_Event event);
void		fill_wpn_inv(t_wrap_wpn *wpn, t_weapon *rwpn, t_wrap_sect *obj);
int			check_weapon_type(t_env *env, int ref);

int			put_gun(t_env *env, t_bloc *bloc);
int			put_gun_load(t_env *env, int frame);
int			put_gun_shoot(t_env *env, int frame);
int			handle_weapon(t_env *env);
int			load_weapon(t_env *env);
int			reload_ammo(t_env *env);

void		sdl_keyhook_menu(t_env *e, SDL_Event ev, const Uint8 *k);
int			sdl_keyhook_game(t_env *env, SDL_Event event, const Uint8 *keycodes);
int			sdl_keyhook_inventory(t_env *env, SDL_Event event, const Uint8 *keycodes);
void		mouse_shoot(t_env *env);
void		access_menu(t_env *e, t_status *s, int which);
void		access_inventory(t_env *e);

int			bot_wall_collision(t_player *bot, t_sector *sect);
void		impact_player(t_env *env, t_impact *shot, t_vtx player, int damage);
void		new_bullet(t_impact *new, t_player *p, float velocity);
void		bot_status(t_env *env, t_vtx player, t_wrap_enmy *enemy, Uint8 *keycodes);
void		bot_action(t_env *env, t_sector *sector);
t_player	bot_angle(t_player e, t_player src);
t_vtx		bot_orientation(t_player *bot, t_vctr p_where, float speed);
void		bot_check_friend(t_wrap_enmy *enemy, t_wrap_enmy *next);
void		pl_new_kill(t_env *env, t_player *p, t_character *player);
void		player_bullet(t_env *env, t_character *p, int damage);
void		enemies_frames(t_env *env, t_sector *sector);
void		bot_life(t_env *e, t_wrap_enmy *en, int damage, int wpn);
void		check_isimpact(t_env *e, t_impact *b, float vel, int damage);
void		impact_bot(t_env *e, t_impact *shot, t_sector *sector, int damage);

int			init_doors_images(t_env *env);
int			door_neighbors(t_engine *e, t_vtx *vertex, int n);
int			select_door(t_engine *e);
int			access_door(t_env *env);
void		handle_doors(t_env *env);

void		bot_is_moving(t_character *e, t_wrap_enmy *enemy);
void		bot_is_hit(t_character *e, t_wrap_enmy *enemy);
void		bot_is_shootin(t_character *e, t_wrap_enmy *enemy);
void		bot_is_dying(t_env *e, t_character *ref,
			t_wrap_enmy *en, t_sector *s);
void		set_bossmidlife(t_env *e, t_wrap_enmy *en);

#endif

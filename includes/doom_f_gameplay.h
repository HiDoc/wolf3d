/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_f_gameplay.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 20:32:27 by abaille           #+#    #+#             */
/*   Updated: 2019/03/30 14:15:57 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_F_GAMEPLAY_H
# define DOOM_F_GAMEPLAY_H

int			is_pickable_object(t_env *env, t_sector *sector);
int		    pick_object(t_env *env, t_wrap_sect *obj);
int		    drop_object(t_env *env, t_wrap_inv *object);
int			select_object(t_wrap_inv *object, int x, int y, t_bloc *p);
int		    give_shield(void *e, t_wrap_inv *object);
int		    give_health(void *e, t_wrap_inv *object);
int			give_ammo(void *e, t_wrap_inv *obj);
int			give_jetpack(void *e, t_wrap_inv *obj);
int			check_object_type(t_wrap_inv *pack, int ref, int limit);
int         action_inventory(t_env *env, int x, int y);

int			action_gems(t_env *env);

int			pick_weapon(t_env *env, t_wrap_sect *obj);
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

void		bot_status(t_env *env, t_vtx player, t_wrap_enmy *enemy, Uint8 *keycodes);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 22:01:46 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/03 21:14:35 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	underscore_off_name(char *name, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		name[i] == '_' ? name[i] = ' ' : 0;
}

// // static void	set_inv_strings(t_env *env)
// // {
// // 	int			i;
// // 	t_vtx		n_size;
// // 	SDL_Surface	*tmp;
// // 	const char	*string[DSCRIP_STR_INV] = {
// // 	I_STRING_0, I_STRING_1, I_STRING_2, I_STRING_3, I_STRING_4, I_STRING_5,
// // 	I_STRING_6, I_STRING_7, I_STRING_8, I_STRING_9, I_STRING_10, I_STRING_11};

// // 	i = -1;
// // 	while (++i < DSCRIP_STR_INV)
// // 	{
// // 		tmp = make_string((t_font){
// // 			WHITE, string[i], env->hud.font.text, {0, 0}, 0, -1, -1});
// // 		n_size = (t_vtx){tmp->w / (100 / (W / 50)), tmp->h / (100 / (W / 50))};
// // 		env->hud.font.i_obj_description[i] = make_surface(n_size.x, n_size.y);
// // 		img_scaled_copy(tmp, env->hud.font.i_obj_description[i]);
// // 		lt_release(tmp);
// // 	}
// // }

// static void	set_door_strings(t_env *env)
// {
// 	const char	*string[2] = {STR_DOOR_0, STR_DOOR_1};
// 	int			i;
// 	SDL_Surface	*tmp;
// 	t_vtx		n_size;

// 	i = -1;
// 	while (++i < 2)
// 	{
// 		tmp = make_string((t_font){
// 			WHITE, string[i], env->hud.font.text, {0, 0}, 0, -1, -1});
// 		n_size = (t_vtx){tmp->w / (100 / (W / 40)), tmp->h / (100 / (W / 40))};
// 		env->hud.font.doors[i] = make_surface(n_size.x, n_size.y);
// 		img_scaled_copy(tmp, env->hud.font.doors[i]);
// 		lt_release(tmp);
// 	}
// }

// void		init_strings(t_env *env, int i)
// {
// 	TTF_Font	*font;
// 	const char	*string[UI_NB_STRING] = {
// 	STRING_0, STRING_1, STRING_2, STRING_3, STRING_4, STRING_5, STRING_6,
// 	STRING_7, STRING_8, STRING_9, STRING_10, STRING_11, STRING_12, STRING_13,
// 	STRING_14, STRING_15, STRING_16, STRING_17, STRING_18, STRING_19, STRING_20,
// 	STRING_21, STRING_22, S_CROSS, S_USE, STRING_25, STRING_26, STRING_27,
// 	STRING_28, STRING_29};

// 	while (i < UI_NB_STRING)
// 	{
// 		font = (i <= T_STATS && i >= T_INVENTORY)
// 			? env->hud.font.doom : env->hud.font.text;
// 		env->hud.font.string[i] = make_string((t_font){WHITE, string[i],
// 			font, {0, 0}, 0, -1, -1});
// 		i++;
// 	}
// 	// set_inv_strings(env);
// 	// set_door_strings(env);
// }

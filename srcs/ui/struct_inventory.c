/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_inventory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:21 by abaille           #+#    #+#             */
/*   Updated: 2019/03/23 15:26:29 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// int     init_icon(t_uinv *ui, char *res)
// {
// 	if ((ui->icon[0] = ui_img(res, "inventory/", "icons/", 0))
// 	&& (ui->icon[1] = ui_img(res, "inventory/", "icons/", 1)))
// 		return (1);
// 	return (0);
// }

// int     init_wpn_inv(t_uinv *ui, char *res)
// {
// 	int i;

// 	i = 0;
// 	while (i < 3)
// 	{
// 		if (!(ui->mini_wpn[i] = ui_img(res, "inventory/", "wpn/", i))
// 		|| !(ui->empt_wpn[i] = ui_img(res, "inventory/", "e_wpn/", i)))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int     init_inv_box(t_uinv *ui, char *res)
// {
// 	if((ui->box[0] = ui_img(res, "inventory/", "box/", 0))
// 	&& (ui->box[1] = ui_img(res, "inventory/", "box/", 1)))
// 		return (1);
// 	return (0);
// }

// int    init_inventory_ui(t_env *env, char *res)
// {
// 	env->player.inventory.ui.wwheel = 0;
// 	env->player.inventory.ui.nb_wpn = 1;
// 	env->player.inventory.nb_current_obj = 0;
// 	if ((env->player.inventory.ui.front_pic = ui_img(res, "inventory/", "fond/", 0))
// 	&& init_wpn_inv(&env->player.inventory.ui, res)
// 	&& init_icon(&env->player.inventory.ui, res)
// 	&& init_inv_box(&env->player.inventory.ui, res))
// 		return (1);
// 	return (0);
// }

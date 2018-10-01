/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:18:41 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/27 14:04:36 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_img	*img_new(t_env *env, char *filename)
{
	t_img	*new;

	if ((new = malloc(sizeof(t_img))) == NULL)
		return (NULL);
	new->iptr = mlx_xpm_file_to_image(E_MLX, filename, &new->w, &new->h);
	new->data = (int *)mlx_get_data_addr(
		new->iptr, &new->bpp, &new->size_l, &new->endian);
	return (new);
}

void	img(t_env *env)
{
	env->walls[0] = img_new(env, "./img/wall.XPM");
	env->walls[1] = img_new(env, "./img/wall_1.XPM");
	env->walls[2] = img_new(env, "./img/wall_2.XPM");
	env->walls[3] = img_new(env, "./img/wall_3.XPM");
	env->walls[4] = img_new(env, "./img/wall_4.XPM");
	env->walls[5] = img_new(env, "./img/wall_5.XPM");
	env->walls[6] = img_new(env, "./img/wall_6.XPM");
	env->walls[7] = img_new(env, "./img/wall_7.XPM");
	env->enemy = img_new(env, "./img/enemy.XPM");
	env->wall = env->walls[0];
	env->floor = img_new(env, "./img/floor.XPM");
	env->sky = img_new(env, "./img/floor.XPM");
	env->gun = img_new(env, "./img/gun.XPM");
}

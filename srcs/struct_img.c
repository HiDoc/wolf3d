/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:18:41 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/03 14:02:33 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_img	*img_new(t_env *env, char *filename)
{
	t_img	*new;

	if ((new = malloc(sizeof(t_img))) == NULL)
		return (NULL);
	new->iptr = mlx_xpm_file_to_image(E_MLX, filename, &new->w, &new->h);
	new->data = (int *)mlx_get_data_addr(new->iptr, &new->bpp, &new->size_l, &new->endian);
	return (new);
}

void	img(t_env *env)
{
	env->wall = img_new(env, "./img/wall.XPM");
	env->floor = img_new(env, "./img/floor.XPM");
	env->sky = img_new(env, "./img/sky.XPM");
}

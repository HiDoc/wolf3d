/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 17:07:53 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/01 17:52:24 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	img(t_env *env)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(E_MLX, "./img/wall.XPM", &w, &h);
	env->wall = (int *)img;
	mlx_put_image_to_window(E_MLX, E_WIN, img, 0, 0);
}

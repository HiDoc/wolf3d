/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 11:03:15 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/05 11:07:06 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		main(int ac, char **av)
{
	t_env   *env;

	(void)ac;
	(void)av;
	if (!(env = (t_env *)malloc(sizeof(t_env))))
		print_error(1, NULL);
	init_env(env);
	img(env);
	fill_tab(env);
	init_thread(env);
	mlx_do_key_autorepeaton(E_MLX);
	mlx_put_image_to_window(E_MLX, E_WIN, E_IMG, 0, 0);
	mlx_hook(E_WIN, KeyPress, KeyPressMask, &key_hook, env);
	mlx_hook(E_WIN, 6, 3, &motion_mouse, env);
	mlx_loop(E_MLX);
	return (0);
}

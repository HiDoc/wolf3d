/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerrors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2018/06/25 09:50:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void  free_env(t_env *env)
{
  int i;

  i = 0;
  if (env->w_map)
  {
    while (i < 24)
    {
      free(env->w_map[i]);
      i++;
    }
    free(env->w_map);
  }
  if (env->mlx)
    free(env->mlx);
	free(env);
}

// void  usage(void)
// {
//   ft_putstr("\n\n---- USAGE ----\n\n");
//   ft_putstr("./wolf3d\n");
//   ft_putstr("[UP][DOWN][LEFT][RIGHT] to move\n");
//   ft_putstr("1 to 6 to change colors\n\n");
// }

void  print_error(int nb, t_env *env)
{
  if (nb == 1)
    (void)nb;
    // ft_putstr("Problem with allocation memory\n");
  // else if (nb == 2)
  //   usage();
  if (env != NULL)
    free_env(env);
  exit(0);
}

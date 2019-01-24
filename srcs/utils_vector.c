/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:29:57 by fmadura           #+#    #+#             */
/*   Updated: 2019/01/24 19:45:03 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double  v_distance(t_vector *vector)
{
  double  ret;

  ret = sqrt((vector->b.x - vector->a.x) * (vector->b.x - vector->a.x)
        + (vector->b.y - vector->a.y) * (vector->b.y - vector->a.y));
  return (ret);
}

void    v_position(t_vector *vector, t_point *res, double c_time, double m_time)
{
  double percent;
  
  percent = c_time / m_time;
  res->x = vector->a.x + ((vector->b.x - vector->a.x) / percent);
  res->y = vector->a.y + ((vector->b.y - vector->a.y) / percent);
}
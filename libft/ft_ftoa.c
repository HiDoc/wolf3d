/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:26:00 by abaille           #+#    #+#             */
/*   Updated: 2017/11/22 16:26:03 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char          *ft_ftoa(double nb)
{
  double        ptr;
  int           i;
  char          *pstr;
  int           size;

  size = (nb > 0) ? 8 : 9;
  nb = (nb > 0) ? nb : -nb;
  if (!(pstr = ft_strnew(size)))
    return (NULL);
  if (size == 9)
  {
    pstr[0] = '-';
    pstr[1] = (int)(nb) + '0';
    pstr[2] = '.';
  }
  else
  {
    pstr[0] = (int)(nb) + '0';
    pstr[1] = '.';
  }
  i = (size > 8) ? 3 : 2;
  nb = nb - (int)nb;
  while (i < size)
  {
    nb = ft_modf(nb * 10, &ptr);
    pstr[i++] = (int)(ptr) + '0';
  }
  return (pstr);
}

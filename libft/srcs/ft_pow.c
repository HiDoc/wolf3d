/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:50:01 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 09:50:04 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double nb, double power)
{
	int		i;
	double	res;

	res = nb;
	if (nb == 0 || power == 0)
		return (nb);
	i = 1;
	while (i < power)
	{
		res *= nb;
		i++;
	}
	return (res);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:26:00 by abaille           #+#    #+#             */
/*   Updated: 2017/11/22 16:26:03 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_len(int n)
{
	int i;
	int nb;

	i = 0;
	nb = n;
	if (n == 0)
		return (i = 1);
	while (nb)
	{
		nb /= 10;
		i++;
	}
	if (n < 0)
		i++;
	return (i);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		nb;
	int		lennb;

	nb = n;
	lennb = nb_len(n);
	res = ft_strnew(lennb);
	if (res)
	{
		while (lennb--)
		{
			res[lennb] = (n < 0) ? ((n % 10) * -1) + 48 : (n % 10) + 48;
			n /= 10;
		}
		if (nb < 0)
			res[0] = '-';
		return (res);
	}
	return (NULL);
}

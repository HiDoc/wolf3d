/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:34:59 by sgalasso          #+#    #+#             */
/*   Updated: 2018/04/06 21:20:48 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_byten(size_t temp)
{
	int c;

	c = 0;
	while (temp > 9)
	{
		temp = temp / 10;
		c++;
	}
	return (c);
}

static void	ft_transfert_itoa(size_t temp, char *str, int c, int i)
{
	while (temp > 9)
	{
		str[i] = temp / ft_pow(c, 10) + 48;
		if (temp > 99 && (temp - ((temp / ft_pow(c, 10))
		* (ft_pow(c, 10))) < 10))
		{
			c = ft_byten(temp);
			while (c - 1 > 0)
			{
				str[++i] = 0 + 48;
				c--;
			}
			temp = temp - ((temp / ft_pow(c, 10)) * (ft_pow(c, 10)));
		}
		else
			temp = temp - ((temp / ft_pow(c, 10)) * (ft_pow(c, 10)));
		i++;
		c--;
	}
	str[i++] = temp + 48;
	str[i] = '\0';
}

char		*ft_itoa(int n)
{
	char	*str;
	size_t	temp;
	int		ng;
	int		i;
	int		c;

	ng = 0;
	i = 0;
	c = 0;
	temp = n;
	if (n < 0)
	{
		temp = -temp;
		ng = 1;
	}
	c = ft_byten(temp);
	if (!(str = (char *)(malloc(sizeof(char) * (c + 2 + ng)))))
		return (0);
	if (ng == 1)
		str[i++] = '-';
	ft_transfert_itoa(temp, str, c, i);
	return (str);
}

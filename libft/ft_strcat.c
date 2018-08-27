/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 15:43:38 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 15:43:43 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	while (dest[i] != '\0')
		i++;
	while (src[tmp] != '\0')
	{
		dest[tmp + i] = src[tmp];
		tmp++;
	}
	dest[tmp + i] = '\0';
	return (dest);
}

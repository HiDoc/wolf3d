/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:12:46 by abaille           #+#    #+#             */
/*   Updated: 2017/11/20 18:28:35 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		nb;
	char	*str;

	if (s == NULL)
		return (NULL);
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	nb = 0;
	while (len > (size_t)nb && s[start + nb])
	{
		str[nb] = s[start + nb];
		nb++;
	}
	str[nb] = '\0';
	return (str);
}

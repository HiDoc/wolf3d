/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:12:46 by abaille           #+#    #+#             */
/*   Updated: 2019/04/08 23:59:53 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		nb;
	char	*str;

	if (s == NULL)
		return (NULL);
	str = (char *)ft_memalloc(sizeof(char) * (len + 1));
	nb = 0;
	while (len > (size_t)nb && s[start + nb])
	{
		str[nb] = s[start + nb];
		nb++;
	}
	str[nb] = '\0';
	return (str);
}

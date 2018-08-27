/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 09:36:32 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 09:36:35 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		lenneed;

	lenneed = ft_strlen(needle);
	i = 0;
	if (ft_strlen(haystack) == 0 && len == 0)
		return ((char*)haystack);
	while ((i + lenneed <= len) && *haystack != '\0')
	{
		if (ft_memcmp(haystack, needle, lenneed) == 0)
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}

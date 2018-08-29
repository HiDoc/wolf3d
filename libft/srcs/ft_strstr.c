/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 17:00:16 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 17:00:17 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		lenhay;
	size_t		lenneed;

	lenhay = ft_strlen(haystack);
	lenneed = ft_strlen(needle);
	i = 0;
	if (haystack[0] == '\0' && needle[0] == '\0')
		return (&((char *)haystack)[i]);
	while (i < lenhay)
	{
		if (ft_memcmp(&haystack[i], needle, lenneed) == 0)
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}

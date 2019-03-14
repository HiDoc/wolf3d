/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 16:41:43 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 16:41:44 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;
	size_t sizesrc;

	i = 0;
	sizesrc = ft_strlen(src);
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	while (sizesrc < len)
	{
		dst[sizesrc] = '\0';
		sizesrc++;
	}
	return (dst);
}

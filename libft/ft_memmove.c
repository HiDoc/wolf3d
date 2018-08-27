/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:48:01 by abaille           #+#    #+#             */
/*   Updated: 2017/11/22 16:48:12 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char *tmp;

	tmp = src;
	if (dst > src)
	{
		while (len != 0)
		{
			((char *)dst)[len - 1] = tmp[len - 1];
			len--;
		}
	}
	else if (dst < src)
		ft_memcpy(dst, src, len);
	return (dst);
}

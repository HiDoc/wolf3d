/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:26:16 by abaille           #+#    #+#             */
/*   Updated: 2017/11/22 16:26:18 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *zonememoire;

	zonememoire = NULL;
	if (size)
	{
		zonememoire = (void*)malloc(sizeof(*zonememoire) * size);
		if (!zonememoire)
			return (NULL);
		else
			ft_bzero(zonememoire, size);
	}
	return (zonememoire);
}

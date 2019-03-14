/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:56:04 by sgalasso          #+#    #+#             */
/*   Updated: 2018/12/20 19:18:00 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbwords(char *line)
{
	int		c;

	c = 0;
	while (*line)
	{
		while (*line && (*line == ' ' || *line == '\t'))
			line++;
		if (*line)
		{
			while (*line && *line != ' ' && *line != '\t')
				line++;
			c++;
		}
	}
	return (c);
}

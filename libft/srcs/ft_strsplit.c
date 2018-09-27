/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 16:51:06 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 16:51:07 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(const char *s, char c)
{
	size_t i;
	size_t space;

	i = 0;
	space = 0;
	while (s[i] != '\0')
	{
		while ((s[i] != c) && (s[i + 1] == c))
		{
			space++;
			i++;
		}
		if ((s[i] != c) && (s[i] == '\0'))
			space++;
		i++;
	}
	return (space);
}

static char	*ft_start_end(char **ptr, const char *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		end = i;
		if (end > start)
			ptr[k++] = ft_strsub(s, start, (end - start));
	}
	ptr[k] = NULL;
	return (*ptr);
}

char		**ft_strsplit(const char *s, char c)
{
	char	**ptr;

	ptr = NULL;
	if (s && (ptr = (char**)malloc(sizeof(*ptr) * ((ft_words(s, c)) + 2))))
	{
		ft_start_end(ptr, s, c);
		return (ptr);
	}
	return (NULL);
}

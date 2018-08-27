/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 12:40:18 by abaille           #+#    #+#             */
/*   Updated: 2017/11/24 12:41:13 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *new;

	if (alst != NULL && del != NULL)
	{
		while (*alst)
		{
			new = (*alst)->next;
			del((*alst)->content, (*alst)->content_size);
			free(*alst);
			*alst = new;
		}
		*alst = NULL;
	}
}

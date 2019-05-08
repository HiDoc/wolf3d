/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_save_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:43:43 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 15:57:18 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	is_cur(int c)
{
	return (c == 'c');
}

int	is_wpn(int c)
{
	return (c == 'w');
}

int	is_gem(int c)
{
	return (c == 'g')
}

int	is_sts(int c)
{
	return (c == 't');
}

int	is_stg(int c)
{
	return (c == 'i');
}
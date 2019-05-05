/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:33:14 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 17:36:25 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	is_plr(int c)
{
	return c == 'p';
}

int	is_cmt(int c)
{
	return c == '#';
}

int	is_dgt(int c)
{
	return (c) >= '0' && (c) <= '9';
}

int	is_ptn(int c)
{
	return (c == ':');
}
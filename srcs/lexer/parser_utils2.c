/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:32:58 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 11:37:23 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	is_vtx(int c)
{
	return c == 'v';
}

int	is_obj(int c)
{
	return c == 'o';
}

int	is_txt(int c)
{
	return c == 't';
}

int	is_ent(int c)
{
	return c == 'e';
}

int	is_sky(int c)
{
	return c == 'b';
}